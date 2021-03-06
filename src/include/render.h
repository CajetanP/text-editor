/************************************************************************
 * text-editor - a simple text editor                                   *
 *                                                                      *
 * Copyright (C) 2017 Kajetan Puchalski                                 *
 *                                                                      *
 * This program is free software: you can redistribute it and/or modify *
 * it under the terms of the GNU General Public License as published by *
 * the Free Software Foundation, either version 3 of the License, or    *
 * (at your option) any later version.                                  *
 *                                                                      *
 * This program is distributed in the hope that it will be useful,      *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of       *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.                 *
 * See the GNU General Public License for more details.                 *
 *                                                                      *
 * You should have received a copy of the GNU General Public License    *
 * along with this program. If not, see http://www.gnu.org/licenses/.   *
 *                                                                      *
 ************************************************************************/

#ifndef TEXT_EDITOR_UTIL_H
#define TEXT_EDITOR_UTIL_H

#include <stdbool.h>

#include "screen.h"

/*****************************************************************************/
/*                                  typedefs                                 */
/*****************************************************************************/

typedef unsigned int uint;

/*****************************************************************************/
/*                                   Macros                                  */
/*****************************************************************************/

/* accessing the current line buffer */
#define CURR_LBUF (((Line)s->cur_line->data)->buff)

#define CURR_LINE ((Line)s->cur_line->data)

/* calculating the current gap size */
#define GAP_SIZE (CURR_LBUF->gap_end - CURR_LBUF->gap_start+1)

/*****************************************************************************/
/*                                   Functions                               */
/*****************************************************************************/

/* renders buffer contents */
void render_contents(Screen);

/* renders line numbers */
void render_line_numbers(Screen);

/* render top info bar */
void render_info_bar_top(Screen);

/* render bottom info bar */
void render_info_bar_bottom(Screen);

#endif
