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

#include <stdbool.h>

#include <ncurses.h>

#include "render.h"
#include "lib/gap_buffer.h"

/* renders one line */
void render_line(gpointer data, gpointer screen) {
    /* cast the pointer to a screen */
    Screen s = (Screen)screen;

    /* cast the pointer to a line buffer */
    gap_T buff = ((Line)data)->buff;

    for (int i = 0 ; i <= buff->end ; ++i) {

        /* skip the gap */
        if (i < buff->gap_start || i > buff->gap_end) {
            /* omit the null characters */
            if (buff->buffer[i]) {
                /*************************************************************/
                /*     Print special characters if debug mode is enabled     */
                /*************************************************************/
                if (s->args->debug_mode) {
                    if (buff->buffer[i] == '\n') {
                        waddch(s->contents, '$' | COLOR_PAIR(1));
                        waddch(s->contents, '\n');
                    } else if (buff->buffer[i] == '\0') {
                        wprintw(s->contents, "%");
                    } else if (buff->buffer[i] == '\t') {
                        wattron(s->contents, COLOR_PAIR(2));
                        wprintw(s->contents, " -> ");
                        wattroff(s->contents, COLOR_PAIR(2));
                    } else {
                        wprintw(s->contents, "%c", buff->buffer[i]);
                    }
                }
                /*********************************************************/
                /*        Print normally if debug mode is not enabled    */
                /*********************************************************/
                else {
                    if (buff->buffer[i] == '\t')
                        wprintw(s->contents, "    ");
                    else
                        wprintw(s->contents, "%c", buff->buffer[i]);
                }
            }
        }

    }
}

/* renders the screen */
void render_contents(Screen s) {
    /* erase previous contents */
    werase(s->contents);

    /*************************************************************************/
    /*                       Render current buffer contents                  */
    /*************************************************************************/

    /* render every line */
    g_list_foreach(s->lines, render_line, s);

    /*************************************************************************/
    /*                         Render debug mode info                        */
    /*************************************************************************/

    if (s->args->debug_mode) {

        /* number of lines */
        mvwprintw(s->contents, 0, getmaxx(s->contents)-25,
                  "Number of lines: %d", s->n_lines);

        /* visual cursor coordinates */
        mvwprintw(s->contents, 1, getmaxx(s->contents)-25,
                  "Visual col: %d row: %d", s->col, s->row);

        /* actual cursor position */
        mvwprintw(s->contents, 2, getmaxx(s->contents)-25,
                  "Line cursor: %d", CURR_LBUF->cursor);

        mvwprintw(s->contents, 3, getmaxx(s->contents)-25,
                  "Visual line end: %d", ((Line)s->cur_line->data)->visual_end);

        /* end of the current line */
        mvwprintw(s->contents, 4, getmaxx(s->contents)-25,
                 "Line end: %d", CURR_LBUF->end - GAP_SIZE);

        /* gap start & end */
        mvwprintw(s->contents, 5, getmaxx(s->contents)-25,
                 "Line gap: %d - %d", CURR_LBUF->gap_start, CURR_LBUF->gap_end);

        /* TODO: refactor this into a switch */

        /* character currently under the cursor */
        if (CURR_LBUF->buffer[CURR_LBUF->cursor] == '\n')
            mvwprintw(s->contents, 6, getmaxx(s->contents)-25,
                      "Line cursor on: (\\n)");
        else if (CURR_LBUF->buffer[CURR_LBUF->cursor] == '\0')
            mvwprintw(s->contents, 6, getmaxx(s->contents)-25,
                      "Line cursor on: (\\0)");
        else if (CURR_LBUF->buffer[CURR_LBUF->cursor] == '\t')
            mvwprintw(s->contents, 6, getmaxx(s->contents)-25,
                      "Line cursor on: (\\t)");
        else
            mvwprintw(s->contents, 6, getmaxx(s->contents)-25,
                      "Line cursor on: (%c)",
                      CURR_LBUF->buffer[CURR_LBUF->cursor]);

        mvwprintw(s->contents, 7, getmaxx(s->contents)-25,
                  "File name: %s", s->args->file_name);
    }

    /*************************************************************************/
    /*                        Adjust window attributes                       */
    /*************************************************************************/

    /* move visual cursor to its proper position */
    wmove(s->contents, s->row, s->col);

    wrefresh(s->contents);
}

void render_line_numbers(Screen s) {
    /* erase previous contents */
    werase(s->line_numbers);

    /* enable color for rendering lines */
    wattron(s->line_numbers, COLOR_PAIR(3));

    /* render actual numbers */
    for (int i = 0 ; i < s->n_lines ; ++i)
        mvwprintw(s->line_numbers, i, 0, "%3d", i+1);

    /* disable the color */
    wattroff(s->line_numbers, COLOR_PAIR(3));

    /* render tildes on non-existing lines */
    for (int i = s->n_lines ; i <= LINES ; ++i)
        mvwprintw(s->line_numbers, i, 3, "~");

    wrefresh(s->line_numbers);
}
