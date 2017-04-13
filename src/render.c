#include <ncurses.h>

#include "render.h"
#include "lib/gap_buffer.h"

/* TODO: make debug mode optional using a second parameter */
/* renders one line in debug mode */
void render_line_debug(gpointer data, gpointer user_data) {
    /* cast the void pointer to line buffer */
    gap_T buff = (gap_T)data;

    for (int i = 0 ; i <= buff->end ; ++i) {

        /* skip the gap */
        if (i < buff->gap_start || i > buff->gap_end) {

            /* omit the null characters */
            if (buff->buffer[i]) {
                /* print special characters */
                if (buff->buffer[i] == '\n') {
                    addch('$' | COLOR_PAIR(1));
                    addch('\n');
                } else if (buff->buffer[i] == '\0') {
                    printw("%");
                } else {
                    printw("%c", buff->buffer[i]);
                }
            }

        }

    }

    /* for now just skip the parameter */
    if (user_data) {}
}

/* renders the screen in debug mode */
void render_screen_debug(Screen s) {
    /*************************************************************************/
    /*                       Render the current screen                       */
    /*************************************************************************/

    /* render every line */
    g_list_foreach(s->lines, render_line_debug, NULL);

    /*************************************************************************/
    /*                         Render Debug Mode Info                        */
    /*************************************************************************/

    /* temporary pointer to a buffer */
    gap_T cur_buf = (gap_T)s->cur_line->data;

    /* number of lines */
    mvprintw(0, getmaxx(stdscr)-15, "n_lines :%d", s->n_lines);

    /* visual cursor coordinates */
    mvprintw(1, getmaxx(stdscr)-15, "C: %d R: %d", s->col, s->row);

    /* actual cursor position */
    mvprintw(2, getmaxx(stdscr)-15, "LCur: %d", cur_buf->cursor);

    /* gap start & end */
    mvprintw(3, getmaxx(stdscr)-15, "LG: %d - %d", cur_buf->gap_start,
             cur_buf->gap_end);

    /* end of the current line */
    mvprintw(4, getmaxx(stdscr)-15, "LE: %d", cur_buf->end);

    /* character currently under the cursor */
    if (cur_buf->buffer[cur_buf->cursor] == '\n')
        mvprintw(5, getmaxx(stdscr)-15, "C on: (\\n)");
    else if (cur_buf->buffer[cur_buf->cursor] == '\0')
        mvprintw(5, getmaxx(stdscr)-15, "C on: (\\0)");
    else
        mvprintw(5, getmaxx(stdscr)-15, "C on: (%c)",
                 cur_buf->buffer[cur_buf->cursor]);

    /*************************************************************************/
    /*                        Adjust window attributes                       */
    /*************************************************************************/

    /* move visual cursor to its proper position */
    move(s->row, s->col);
}