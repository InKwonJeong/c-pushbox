#include "board.h"
#include <iostream>
#include <ncurses.h>

using namespace std;

int map1[MAX_ROW][MAX_COL] = {{1, 1, 1, 1, 4, 4, 4, 4, 4, 4},
                              {1, 3, 0, 1, 1, 4, 4, 4, 4, 4},
                              {1, 3, 0, 0, 1, 4, 4, 4, 4, 4},
                              {1, 3, 0, 2, 1, 4, 4, 4, 4, 4},
                              {1, 1, 2, 0, 1, 4, 4, 4, 4, 4},
                              {1, 1, 0, 2, 1, 1, 1, 4, 4, 4},
                              {4, 1, 0, 0, 0, 0, 1, 4, 4, 4},
                              {4, 1, 0, 0, 0, 0, 1, 4, 4, 4},
                              {4, 1, 0, 0, 1, 1, 1, 4, 4, 4},
                              {4, 1, 1, 1, 1, 4, 4, 4, 4, 4}};

int map2[MAX_ROW][MAX_COL] = {{4, 4, 4, 4, 4, 4, 4, 4, 4, 4},
                              {4, 4, 4, 4, 4, 4, 4, 4, 4, 4},
                              {4, 4, 1, 1, 1, 1, 1, 4, 4, 4},
                              {4, 4, 1, 0, 0, 0, 1, 4, 4, 4},
                              {4, 4, 1, 3, 3, 3, 1, 4, 4, 4},
                              {4, 4, 1, 2, 2, 2, 1, 1, 4, 4},
                              {4, 4, 1, 0, 0, 0, 0, 1, 4, 4},
                              {4, 4, 1, 0, 0, 0, 0, 1, 4, 4},
                              {4, 4, 1, 1, 1, 1, 1, 1, 4, 4},
                              {4, 4, 4, 4, 4, 4, 4, 4, 4, 4}};

int map3[MAX_ROW][MAX_COL] = {{4, 4, 4, 4, 4, 4, 4, 4, 4, 4},
                              {4, 4, 4, 4, 4, 4, 4, 4, 4, 4},
                              {4, 4, 4, 4, 4, 4, 4, 4, 4, 4},
                              {4, 4, 4, 4, 4, 4, 4, 4, 4, 4},
                              {4, 1, 1, 1, 1, 1, 1, 1, 1, 4},
                              {4, 1, 3, 0, 0, 0, 0, 0, 1, 4},
                              {4, 1, 0, 3, 2, 2, 2, 0, 1, 4},
                              {4, 1, 3, 0, 0, 0, 0, 0, 1, 4},
                              {4, 1, 1, 1, 1, 1, 0, 0, 1, 4},
                              {4, 4, 4, 4, 4, 1, 1, 1, 1, 4}};

void test_in_console(int map[MAX_ROW][MAX_COL], int start_r, int start_c) {
    Board board(map, start_r ,start_c);

    board.print_board();

    char input;

    do {
        printw("\ninput  W(up), A(Left), S(Down), D(Right) to Move. > ");
        input = getch();
        clear();

        switch (input) {
            case 'w':
                board.moving('u');
                board.print_board();
                break;

            case 'a':
                board.moving('l');
                board.print_board();
                break;

            case 's':
                board.moving('d');
                board.print_board();
                break;

            case 'd':
                board.moving('r');
                board.print_board();
                break;

            case 'r':
                board.reset();
                board.print_board();
                break;

            case 'q':
                printw("\n<< Quit >>\n");
                break;

            default:
                board.print_board();
                printw("\nPlease input based in \"WASD\" \n");
        }

        if (board.is_end()) {
            printw("\n\n<< You WIN!!! >>\n");
            getch();
            clear();
            break;
        }

    } while (input != 'q');
}

void test_in_NC(int map[MAX_ROW][MAX_COL], int start_r, int start_c) {
}

int main() {

    initscr();
    keypad(stdscr, TRUE);
    curs_set(0);
    echo();

    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(2, COLOR_BLACK, COLOR_WHITE);
    init_pair(3, COLOR_WHITE, COLOR_RED);
    init_pair(4, COLOR_WHITE, COLOR_YELLOW);
    init_pair(5, COLOR_WHITE, COLOR_BLUE);
    init_pair(6, COLOR_WHITE, COLOR_GREEN);

    bkgd(COLOR_PAIR(1));
    attron(COLOR_PAIR(1));
    test_in_console(map1, 2, 2);
    test_in_console(map2, 7, 4);
    test_in_console(map3, 6, 7);
    attroff(COLOR_PAIR(1));

    getch();
    endwin();

}
