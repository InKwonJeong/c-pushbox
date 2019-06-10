#ifndef LIVECODING_BOARD_H
#define LIVECODING_BOARD_H

#define MAX_ROW 10
#define MAX_COL 10


/** State of Each NUmber **/
/** 0: Empty Space, 1: Wall, 2: Box **/
/** 3: Destination, 4: OuyBound, 5: Character **/
/** 9: Destination That completed **/



class Player{
public:
    int r, c;

    Player() {
        r = 0, c = 0;
    }
};


class Board {

private:

    // For game Sequence ===============

    int board[MAX_ROW][MAX_COL];
    int player_move = 0, box_move = 0;

    // =================================

    // For Reset Game ==================

    int first_board[MAX_ROW][MAX_COL];
    int first_r = 0, first_c = 0;

    int numBoxs = 0, correctBoxs = 0;

    // =================================


    Player player;


public:

    Board();

    Board(int arr[MAX_ROW][MAX_COL], int r, int c); // init board. arr: game board, r: player's row, c: player's col

    void make_board(int arr[MAX_ROW][MAX_COL]); //Creating Game Board using 2 Dimensional Integer Array


    void print_board_console();
    void print_board(); // Print Game Board's status. It's Needless to NCurses.


    void moving(char direction);    // Change Game Board's Status using player's Moving.

    bool isPosible(int r_move, int c_move); // Checking Player's Moving Possibility.

    int( *getBoard() )[MAX_COL] {
        return board;
    }

    void setPlayer(int r, int c);   // Set Player's Location

    bool is_end();  // Checking Is current Game Ended.

    void reset();   // Reset Game Board and It's each Status.
};


#endif //LIVECODING_BOARD_H
