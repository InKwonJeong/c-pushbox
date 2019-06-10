//
// Created by angheng on 19. 6. 8.
//

#include "board.h"
#include <iostream>
#include <ncurses.h>

using namespace std;


int *stageArr[6]; // To Binding Stages. Index start at 1.
int start_point[2]; // idx 0: row, idx 1: col.

int map1[MAX_ROW][MAX_COL] = {{1, 1, 1, 1, 4, 4, 4, 4, 4, 4},
                              {1, 3, 0, 1, 1, 4, 4, 4, 4, 4},
                              {1, 3, 5, 0, 1, 4, 4, 4, 4, 4},
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
                              {4, 4, 1, 0, 5, 0, 0, 1, 4, 4},
                              {4, 4, 1, 1, 1, 1, 1, 1, 4, 4},
                              {4, 4, 4, 4, 4, 4, 4, 4, 4, 4}};

int map3[MAX_ROW][MAX_COL] = {{4, 4, 4, 4, 4, 4, 4, 4, 4, 4},
                              {4, 4, 4, 4, 4, 4, 4, 4, 4, 4},
                              {4, 4, 4, 4, 4, 4, 4, 4, 4, 4},
                              {4, 4, 4, 4, 4, 4, 4, 4, 4, 4},
                              {4, 1, 1, 1, 1, 1, 1, 1, 1, 4},
                              {4, 1, 3, 0, 0, 0, 0, 0, 1, 4},
                              {4, 1, 0, 3, 2, 2, 2, 5, 1, 4},
                              {4, 1, 3, 0, 0, 0, 0, 0, 1, 4},
                              {4, 1, 1, 1, 1, 1, 0, 0, 1, 4},
                              {4, 4, 4, 4, 4, 1, 1, 1, 1, 4}};

int map4[MAX_ROW][MAX_COL] = {{4, 4, 4, 4, 4, 4, 4, 4, 4, 4},
                              {4, 4, 4, 4, 4, 4, 4, 4, 4, 4},
                              {4, 4, 1, 1, 1, 1, 1, 1, 1, 4},
                              {4, 4, 1, 0, 0, 0, 0, 0, 1, 4},
                              {4, 4, 1, 0, 3, 2, 3, 0, 1, 4},
                              {4, 4, 1, 0, 2, 3, 2, 0, 1, 4},
                              {4, 4, 1, 0, 3, 2, 3, 0, 1, 4},
                              {4, 4, 1, 0, 2, 3, 2, 0, 1, 4},
                              {4, 4, 1, 0, 0, 5, 0, 0, 1, 4},
                              {4, 4, 1, 1, 1, 1, 1, 1, 1, 4}};

int map5[MAX_ROW][MAX_COL] = {{4, 4, 4, 4, 4, 4, 4, 4, 4, 4},
                              {4, 4, 4, 4, 4, 4, 4, 4, 4, 4},
                              {4, 1, 1, 1, 1, 4, 4, 4, 4, 4},
                              {4, 1, 0, 0, 1, 1, 1, 1, 4, 4},
                              {4, 1, 0, 0, 0, 0, 0, 1, 1, 4},
                              {1, 1, 0, 1, 1, 0, 0, 4, 1, 4},
                              {1, 3, 0, 3, 1, 0, 5, 2, 1, 1},
                              {1, 0, 0, 0, 1, 0, 2, 2, 0, 1},
                              {1, 0, 0, 3, 1, 0, 0, 0, 0, 1},
                              {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};


void init_ncurses();
void enterance();
void selectStage();
void mappingStage(int (*targ)[MAX_COL], int stage);
void test_in_NC(int map[MAX_ROW][MAX_COL], int start_r, int start_c);


void init_ncurses() {
    initscr();
    resize_term(50, 70);
    keypad(stdscr, TRUE);
    curs_set(0);
    echo();

    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(2, COLOR_BLACK, COLOR_WHITE); // for player
    init_pair(3, COLOR_RED, COLOR_RED); // for Wall
    init_pair(4, COLOR_YELLOW, COLOR_YELLOW);   // for Box
    init_pair(5, COLOR_BLUE, COLOR_BLUE);   // for Destination
    init_pair(6, COLOR_GREEN, COLOR_GREEN); // for Null Space

    bkgd(COLOR_PAIR(1));
    attron(COLOR_PAIR(1));

    stageArr[1] = reinterpret_cast<int *>(&map1);
    stageArr[2] = reinterpret_cast<int *>(&map2);
    stageArr[3] = reinterpret_cast<int *>(&map3);
    stageArr[4] = reinterpret_cast<int *>(&map4);
    stageArr[5] = reinterpret_cast<int *>(&map5);

    enterance();
}

void enterance() {
    attron(COLOR_PAIR(2));
    mvprintw(10, 28, "Push Box Game");
    mvprintw(12, 28, "PRESS ANY KEY");
    attroff(COLOR_PAIR(2));

    attron(COLOR_PAIR(1));
    border('*', '*', '*', '*', '*', '*', '*', '*');
    attroff(COLOR_PAIR(1));

    refresh();
    getch();
    clear();

    selectStage();
}

void selectStage() {
    const int idx = sizeof(stageArr) / sizeof(int*) - 1;

    int current = 1;
    char input;

    do {
        clear();
        mvprintw(1, 30, "[SELECT STAGE]");

        for (int i = 1; i <= idx; i ++) {

            if (current == i) {
                attron(COLOR_PAIR(2));
                mvprintw(7 + i, 32, "Stage %d", i);
                attroff(COLOR_PAIR(2));
            } else
                mvprintw(7 + i, 32, "Stage %d", i);

        }
        mvprintw(22, 1, "[UP: w, DOWN: s, QUIT: q]");

        attron(COLOR_PAIR(1));
        border('*', '*', '*', '*', '*', '*', '*', '*');
        attroff(COLOR_PAIR(1));

        refresh();

        input = getch();

        if (input == 's') {
            if (current + 1 <= idx)
                current ++;
            else
                current = 1;
        } else if(input == 'w') {
            if (current - 1 < 1)
                current = idx;
            else
                current = (current - 1) % idx;
        } else if(input == 'q')
            break;

    } while (input != '\n');

    if (input == 'q') {
        endwin();
    } else {
        clear();

        int current_map[MAX_ROW][MAX_COL];
        mappingStage(current_map, current);

        test_in_NC(current_map, start_point[0], start_point[1]);
    }

}

// make 1D array "stageArr" to 2D array "targ".
// if Find 5, starting point set to there row & col. And there value set to 0.
void mappingStage(int (*targ)[MAX_COL], int stage) {

    for (int i = 0; i < MAX_ROW; i ++) {

        for (int j = 0; j < MAX_COL; j ++) {

            if (stageArr[stage][i * 10 + j] == 5) {
                targ[i][j] = 0;
                start_point[0] = i; start_point[1] = j;
            } else
                targ[i][j] = stageArr[stage][i * 10 + j];

        }

    }

}

void test_in_NC(int map[MAX_ROW][MAX_COL], int start_r, int start_c) {
    Board board(map, start_r ,start_c);

    board.print_board();

    char input;

    do {
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
            attron(COLOR_PAIR(2));
            mvprintw(20, 2, "<< CLEAR. PRESS ANY KEY.>>");
            attroff(COLOR_PAIR(2));
            getch();
            clear();
            break;
        }

    } while (input != 'q');

    attroff(COLOR_PAIR(1));

    selectStage();
}


int main() {
    init_ncurses();
}
