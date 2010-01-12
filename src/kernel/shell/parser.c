/*
 * kernel/shell/parser.c
 *
 *
 * Copyright (c) 2007-2008  jianjun jiang <jjjstudio@gmail.com>
 * website: http://xboot.org
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */

#include <configs.h>
#include <default.h>
#include <types.h>
#include <ctype.h>
#include <string.h>
#include <malloc.h>
#include <shell/env.h>
#include <xboot/printk.h>
#include <shell/readline.h>
#include <shell/parser.h>

/*
 * All the possible state transitions on the command line.  If a
 * transition can not be found, it is assumed that there is no
 * transition and keep_value is assumed to be 1.
 */
static struct parser_state_transition state_transitions[] = {
	{ PARSER_STATE_TEXT, PARSER_STATE_QUOTE, '\'', 0},
	{ PARSER_STATE_TEXT, PARSER_STATE_DQUOTE, '\"', 0},
	{ PARSER_STATE_TEXT, PARSER_STATE_VAR, '$', 0},
	{ PARSER_STATE_TEXT, PARSER_STATE_ESC, '\\', 0},
	{ PARSER_STATE_ESC, PARSER_STATE_TEXT, 0, 1},
	{ PARSER_STATE_QUOTE, PARSER_STATE_TEXT, '\'', 0},
	{ PARSER_STATE_DQUOTE, PARSER_STATE_TEXT, '\"', 0},
	{ PARSER_STATE_DQUOTE,PARSER_STATE_QVAR, '$', 0},
	{ PARSER_STATE_VAR, PARSER_STATE_VARNAME2, '{', 0},
	{ PARSER_STATE_VAR, PARSER_STATE_VARNAME, 0, 1},
	{ PARSER_STATE_VARNAME, PARSER_STATE_TEXT, ' ', 1},
	{ PARSER_STATE_VARNAME2, PARSER_STATE_TEXT, '}', 0},
	{ PARSER_STATE_QVAR, PARSER_STATE_QVARNAME2, '{', 0},
	{ PARSER_STATE_QVAR, PARSER_STATE_QVARNAME, 0, 1},
	{ PARSER_STATE_QVARNAME, PARSER_STATE_DQUOTE, ' ', 1},
	{ PARSER_STATE_QVARNAME, PARSER_STATE_TEXT, '\"', 0},
	{ PARSER_STATE_QVARNAME2, PARSER_STATE_DQUOTE, '}', 0},
	{ 0, 0, 0, 0}
};

/*
 * determines the state following STATE, determined by C.
 */
static enum paser_state get_parser_state(enum paser_state state, x_s8 c, x_s8 *result)
{
	struct parser_state_transition *transition;
	struct parser_state_transition *next_match = 0;
	struct parser_state_transition default_transition;
	x_s32 found = 0;

	default_transition.to_state = state;
	default_transition.keep_value = 1;

	/* look for a good translation.  */
	for (transition = state_transitions; transition->from_state; transition++)
	{
		/* an exact match was found, use it. */
		if (transition->from_state == state && transition->input == c)
		{
			found = 1;
			break;
		}

		/* a less perfect match was found, use this one if no exact
	 	match can be found. */
		if (transition->from_state == state && transition->input == 0)
			next_match = transition;
	}

	if(!found)
	{
		if(next_match)
			transition = next_match;
		else
			transition = &default_transition;
	}

	if (transition->keep_value)
		*result = c;
	else
		*result = 0;
	return transition->to_state;
}

/*
 * check the the parser state, return true for var,
 * otherwise return false
 */
static x_bool is_varstate(enum paser_state s)
{
	if(s == PARSER_STATE_VARNAME || s == PARSER_STATE_VARNAME2 ||
		s == PARSER_STATE_QVARNAME || s == PARSER_STATE_QVARNAME2)
		return TRUE;
	else
		return FALSE;
}

/*
 * parser command line.
 * the cmdline's last character must be a space for running right
 */
x_bool parser(const x_s8 *cmdline, x_s32 *argc, x_s8 ***argv, x_s8 **pos)
{
	enum paser_state state = PARSER_STATE_TEXT;
	enum paser_state newstate;
	x_s8 *rd = (x_s8 *)cmdline;
	x_s8 c, *args, *val;
	x_s8 *buffer, *bp;
	x_s8 *varname, *vp;
	x_s32 i;

	*argc = 1;
	*pos = 0;

	bp = buffer = malloc(CONFIG_CMDLINE_LENGTH);
	if(!buffer)
	{
		*argc = 0;
		return FALSE;
	}

	vp = varname = malloc(CONFIG_VARNAME_LENGTH);
	if(!varname)
	{
		*argc = 0;
		return FALSE;
	}

	do{
		if( !(*rd) )
		{
			break;
		}

		for(; *rd; rd++)
		{
			newstate = get_parser_state(state, *rd, &c);

			/* If a variable was being processed and this character does
			not describe the variable anymore, write the variable to the buffer */
			if(is_varstate (state) && !is_varstate (newstate))
			{
			    *(vp++) = '\0';
			    val = (x_s8*)env_get((const char *)varname);
			    vp = varname;
			    if(val)
			    {
			    	for(; *val; val++)
			    		*(bp++) = *val;
			    }
			}

			if(is_varstate(newstate))
			{
				if(c)
					*(vp++) = c;
			}
			else
			{
				if(newstate == PARSER_STATE_TEXT && state != PARSER_STATE_ESC && c == ' ')
				{
					/* don't add more than one argument if multiple spaces are used. */
					if(bp != buffer && *(bp - 1))
					{
						*(bp++) = '\0';
						(*argc)++;
					}
				}
				else if(newstate == PARSER_STATE_TEXT && state != PARSER_STATE_ESC && c == ';')
				{
					if(bp != buffer && *(bp - 1))
					{
						*(bp++) = '\0';
						(*argc)++;
					}
					*pos = rd+1;
					break;
				}
				else if(c)
				{
					*(bp++) = c;
				}
			}
			state = newstate;
		}
	} while (state != PARSER_STATE_TEXT && !is_varstate(state));

	*(bp++) = '\0';

	/* A special case for when the last character was part of a variable. */
	if(is_varstate(state) && !is_varstate (PARSER_STATE_TEXT))
	{
	    *(vp++) = '\0';
	    val = (x_s8*)env_get((const char *)varname);
	    vp = varname;
	    if(val)
	    {
	    	for(; *val; val++)
	    		*(bp++) = *val;
	    }
	}

	/* reserve memory for the return values.  */
	args = malloc(bp - buffer);
	if(!args)
	{
		*argc = 0;
		return FALSE;
	}

	memcpy(args, buffer, bp - buffer);

	*argv = malloc (sizeof (x_s8 *) * (*argc + 1));
	if (! *argv)
	{
		*argc = 0;
		free(args);
		return FALSE;
	}

	/* the arguments are separated with 0's, setup argv so it points to the right values.  */
	bp = args;
	for (i = 0; i < *argc; i++)
	{
		(*argv)[i] = bp;
		while (*bp)
			bp++;
		bp++;
	}
	(*argc)--;

	free(buffer);
	free(varname);

	return TRUE;
}