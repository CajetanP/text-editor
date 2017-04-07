/*
 * text-editor - a simple text editor
 * Copyright (C) 2017 Kajetan Puchalski
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see http://www.gnu.org/licenses/.
 */

#include <ncurses.h>
#include <glib-2.0/glib.h>

#include "screen.h"
#include "input.h"

int main () {
    /* ncurses initialization */
    initscr();
    raw();
    noecho();
    keypad(stdscr, TRUE);

    /* colors */
    start_color();
    init_pair(1, COLOR_YELLOW, COLOR_BLACK);

    /* create new "screen" */
    Screen s = screen_init();

    /* start input loop */
    input_loop(s);

    /* the program should never get here */
    return 1;
}
