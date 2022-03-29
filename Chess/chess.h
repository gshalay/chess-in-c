/* File Name: chess.h
 * File Description: Header file for chess.c. Defines some constants as well as the data structures to use.
 * Student Name: Greg Shalay
 * UoG: 1096689
 */

#ifndef _CHESS_H // Prevents duplicate linking and compiling errors if this file has already been loaded.
    #define _CHESS_H
    
    #include <unistd.h>
    #include <stdio.h>
    #include <stdbool.h>
    #include <stdlib.h>
    #include <string.h>
    #include <ctype.h>
    #include "colours.h"
    
    #define COORD_LEN 3 // Square coord + null terminator.
    #define PIECE_NAME_LEN 10 // String length for piece name.
    #define EQUAL_STRINGS 0 // Used to compare string equality.

    #define MAX_NAME_LEN 76 // Support for a name up to 75 characters + the null terminator.
    #define BOARD_SIZE 800 // Character size of the board string + the null terminator.
    #define MAX_SQUARES 64 // Total number of squares on the board. (8 x 8 = 64)
    #define UNOCCUPIED -1 // Represents an unoccupied square.
    #define INV -2 // Represents an INV move in the moves array.

    #define NORMAL_MOVE 1 // Represents a normal move taking place. (Piece moved to an unoccupied square).
    #define CAPTURE_MOVE 2 // Represents a capture move taking place. (Piece moved to an occupied square and captured an enemy piece).
    #define CORNERS 4

    // Amount of spaces (at most) a piece can potentially kill another piece on.
    #define MAX_PAWN_KILL_SQUARES 2 // Upper left and right diagonals.
    #define MAX_BISHOP_KILL_SQUARES 4 // Diagonals
    #define MAX_KNIGHT_KILL_SQUARES 8 // L-Shaped Configurations
    #define MAX_ROOK_KILL_SQUARES 4 // Verticals and Horizontals
    #define MAX_QUEEN_KILL_SQUARES 8 // Verticals, Horizontals, and Diagonals
    #define MAX_KING_KILL_SQUARES 8 // 1-square radius

    // Maximum number of squares the rook can move to from any given position. 
    #define MAX_ROOK_POSSIBLE_MOVES 14

    // Maximum number of squares the rook can move to from any given position.
    #define MAX_BISHOP_POSSIBLE_MOVES 13
    
    // Maximum number of squares the queen can move to from any given position.
    #define MAX_QUEEN_POSSIBLE_MOVES 27
    
    // Constants containing the number of each piece each team should have. (If the amount is more than 1).
    #define NUM_PAWNS 8
    #define NUM_PAWN_MOVE_TYPES 4
    #define NUM_ROOKS 2
    #define NUM_KNIGHTS 2
    #define NUM_BISHOPS 2
    #define MAX_POSSIBLE_ROOKS 10
    #define MAX_POSSIBLE_KNIGHTS 10
    #define MAX_POSSIBLE_BISHOPS 10
    #define MAX_POSSIBLE_QUEENS 9

    #define PAWN_REGULAR_MOVES 48
    #define MAX_LINE 7
    #define NUM_LINES 4
    #define PLAYER_TURN 4
    #define ENEMY_TURN 3
    #define EMPTY_STR '\0'


    char chessBoard[BOARD_SIZE] = { "     A   B   C   D   E   F   G   H     \n   + - + - + - + - + - + - + - + - +   \n1  |   |   |   |   |   |   |   |   |  1\n   + - + - + - + - + - + - + - + - +   \n2  |   |   |   |   |   |   |   |   |  2\n   + - + - + - + - + - + - + - + - +   \n3  |   |   |   |   |   |   |   |   |  3\n   + - + - + - + - + - + - + - + - +   \n4  |   |   |   |   |   |   |   |   |  4\n   + - + - + - + - + - + - + - + - +   \n5  |   |   |   |   |   |   |   |   |  5\n   + - + - + - + - + - + - + - + - +   \n6  |   |   |   |   |   |   |   |   |  6\n   + - + - + - + - + - + - + - + - +   \n7  |   |   |   |   |   |   |   |   |  7\n   + - + - + - + - + - + - + - + - +   \n8  |   |   |   |   |   |   |   |   |  8\n   + - + - + - + - + - + - + - + - +   \n     A   B   C   D   E   F   G   H     \n\0" };

    // Values given to chess pieces. A higher value means a more important piece.
    enum Weights { Pawn, Bishop, Knight, Rook, Queen, King };

    // Values given to the available colours.
    enum colours { Green, Cyan, Blue, Red, Yellow, Purple, Black, White };

    // Used as a lookup for board postion. the enum value will resemble an integer value that points 
    // to a specific index in another integer array that will hold a char position for a particular square on the chess board.
    enum boardCoordinates { A1, A2, A3, A4, A5, A6, A7, A8, 
                            B1, B2, B3, B4, B5, B6, B7, B8, 
                            C1, C2, C3, C4, C5, C6, C7, C8, 
                            D1, D2, D3, D4, D5, D6, D7, D8, 
                            E1, E2, E3, E4, E5, E6, E7, E8, 
                            F1, F2, F3, F4, F5, F6, F7, F8, 
                            G1, G2, G3, G4, G5, G6, G7, G8, 
                            H1, H2, H3, H4, H5, H6, H7, H8 };

    // A simple lookup for the special pawn move indices. 
    // 0 = regular vertical move, 1 = left diag capture, 2 = right diag capture. 3 = The two square move. (Can only be done on each pawn's first move)
    enum pawnMovesIdx { P_REG_MOVE, P_CAP_LEFT, P_CAP_RIGHT, P_DBL };

    // A lookup for the positions where a knight can move / capture. Defined by clockwise orientation.
    enum knightMovesIdx { ONE_OCLOCK, TWO_OCLOCK, FOUR_OCLOCK, FIVE_OCLOCK, SEVEN_OCLOCK, EIGHT_OCLOCK, TEN_OCLOCK, ELEVEN_OCLOCK };

    enum lineOrientations {NORTH, EAST, SOUTH, WEST};
    enum diagonalOrientations {LEFT_UPPER, RIGHT_UPPER, RIGHT_LOWER, LEFT_LOWER};

    char coordStrs[MAX_SQUARES][COORD_LEN] = {
        "a1", "a2", "a3", "a4", "a5", "a6", "a7", "a8",  // 1st column
        "b1", "b2", "b3", "b4", "b5", "b6", "b7", "b8",  // 2nd column
        "c1", "c2", "c3", "c4", "c5", "c6", "c7", "c8",  // 3rd column
        "d1", "d2", "d3", "d4", "d5", "d6", "d7", "d8",  // 4th column
        "e1", "e2", "e3", "e4", "e5", "e6", "e7", "e8",  // 5th column
        "f1", "f2", "f3", "f4", "f5", "f6", "f7", "f8",  // 6th column
        "g1", "g2", "g3", "g4", "g5", "g6", "g7", "g8",  // 7th column
        "h1", "h2", "h3", "h4", "h5", "h6", "h7", "h8",  // 8th column
    };


    // Accompanying integer array used in conjunction with the enum above to coordinate the correct changing of the board state after each move. 
    int coordsToIdx[MAX_SQUARES] = { 85, 165, 245, 325, 405, 485, 565, 645,    // A's 
                                     89, 169, 249, 329, 409, 489, 569, 649,    // B's
                                     93, 173, 253, 333, 413, 493, 573, 653,    // C's
                                     97, 177, 257, 337, 417, 497, 577, 657,    // D's
                                     101, 181, 261, 341, 421, 501, 581, 661,   // E's
                                     105, 185, 265, 345, 425, 505, 585, 665,   // F's
                                     109, 189, 269, 349, 429, 509, 589, 669,   // G's
                                     113, 193, 273, 353, 433, 513, 593, 673 }; // H's

    int crosshairCoords[MAX_SQUARES][CORNERS] = {
                                    { 43, 47, 123, 127 },   { 123, 127, 203, 207 }, { 203, 207, 283, 287 }, { 283, 287, 363, 367 },  // A's
                                    { 363, 367, 443, 447 }, { 443, 447, 523, 527 }, { 523, 527, 603, 607 }, { 603, 607, 683, 687 },  //
                                    
                                    { 47, 51, 127, 131 },   { 127, 131, 207, 211 }, { 207, 211, 287, 291 }, { 287, 291, 367, 371 },  // B's
                                    { 367, 371, 447, 451 }, { 447, 451, 527, 531 }, { 527, 531, 607, 611 }, { 607, 611, 687, 691 },  //
                                    
                                    { 51, 55, 131, 135 },   { 131, 135, 211, 215 }, { 211, 215, 291, 295 }, { 291, 295, 371, 375 },  // C's
                                    { 371, 375, 451, 455 }, { 451, 455, 531, 535 }, { 531, 535, 611, 615 }, { 611, 615, 691, 695 },  // 
                                    
                                    { 55, 59, 135, 139 },   { 135, 139, 215, 219 }, { 215, 219, 295, 299 }, { 295, 299, 375, 379 },  // D's
                                    { 375, 379, 455, 459 }, { 455, 459, 535, 539 }, { 535, 539, 615, 619 }, { 615, 619, 695, 699 },  //

                                    { 59, 63, 139, 143 },   { 139, 143, 219, 223 }, { 219, 223, 299, 303 }, { 299, 303, 379, 383 },  // E's
                                    { 379, 383, 459, 463 }, { 459, 463, 539, 543 }, { 539, 543, 619, 623 }, { 619, 623, 689, 703 },  // 
                                    
                                    { 63, 67, 143, 147 },   { 143, 147, 223, 227 }, { 223, 227, 303, 307 }, { 303, 307, 383, 387 },  // F's
                                    { 383, 387, 463, 467 }, { 463, 467, 543, 547 }, { 543, 547, 623, 627 }, { 623, 627, 703, 707 },  //

                                    { 67, 71, 147, 151 },   { 147, 151, 227, 231 }, { 227, 231, 307, 311 }, { 307, 311, 387, 391 },  // G's
                                    { 387, 391, 467, 471 }, { 467, 471, 547, 551 }, { 547, 551, 627, 631 }, { 627, 631, 707, 711 },  // 
                                    
                                    { 71, 75, 151, 155 },   { 151, 155, 231, 235 }, { 231, 235, 311, 315 }, { 311, 315, 391, 395 },  // H's
                                    { 391, 395, 471, 475 }, { 471, 475, 551, 555 }, { 551, 555, 631, 635 }, { 631, 635, 711, 715 }   //    
    }; 

    // This array records the normal movement of computer pawns and their diagonal capture squares.
    int computerPawnMoves[PAWN_REGULAR_MOVES][NUM_PAWN_MOVE_TYPES] = {
                            { H3, INV, G3, A4 },  { G3, H3, F3, B4 },  { F3, G3, E3, C4 },  { E3, F3, D3, D4 },  { D3, E3, C3, E4 },  { C3, D3, B3, F4 },  { B3, C3, A3, G4 },  { A3, B3, INV, H4 },     // 2's
                            { H4, INV, G4, INV }, { G4, H4, F4, INV }, { F4, G4, E4, INV }, { E4, F4, D4, INV }, { D4, E4, C4, INV }, { C4, D4, B4, INV }, { B4, C4, A4, INV }, { A4, B4, INV, INV },    // 3's
                            { H5, INV, G5, INV }, { G5, H5, F5, INV }, { F5, G5, E5, INV }, { E5, F5, D5, INV }, { D5, E5, C5, INV }, { C5, D5, B5, INV }, { B5, C5, A5, INV }, { A5, B5, INV, INV },    // 4's
                            { H6, INV, G6, INV }, { G6, H6, F6, INV }, { F6, G6, E6, INV }, { E6, F6, D6, INV }, { D6, E6, C6, INV }, { C6, D6, B6, INV},  { B6, C6, A6, INV }, { A6, B6, INV, INV },    // 5's 
                            { H7, INV, G7, INV }, { G7, H7, F7, INV }, { F7, G7, E7, INV }, { E7, F7, D7, INV }, { D7, E7, C7, INV }, { C7, D7, B7, INV }, { B7, C7, A7, INV }, { A7, B7, INV, INV },    // 6's
                            { H8, INV, G8, INV }, { G8, H8, F8, INV }, { F8, G8, E8, INV }, { E8, F8, D8, INV }, { D8, E8, C8, INV }, { C8, D8, B8, INV }, { B8, C8, A8, INV }, { A8, B8, INV, INV }     // 7's
                    };   

    // This array records the normal movement of player pawns and their diagonal capture squares.
    int humanPawnMoves[PAWN_REGULAR_MOVES][NUM_PAWN_MOVE_TYPES] = {
                            { H6, INV, G6, INV }, { G6, H6, F6, INV }, { F6, G6, E6, INV }, { E6, F6, D6, INV }, { D6, E6, C6, INV }, { C6, D6, B6, INV }, { B6, C6, A6, INV }, { A6, B6, INV, INV },    // 2's
                            { H5, INV, G5, INV }, { G5, H5, F5, INV }, { F5, G5, E5, INV }, { E5, F5, D5, INV }, { D5, E5, C5, INV }, { C5, D5, B5, INV }, { B5, C5, A5, INV }, { A5, B5, INV, INV },    // 3's
                            { H4, INV, G4, INV }, { G4, H4, F4, INV }, { F4, G4, E4, INV }, { E4, F4, D4, INV }, { D4, E4, C4, INV }, { C4, D4, B4, INV }, { B4, C4, A4, INV }, { A4, B4, INV, INV },    // 4's
                            { H3, INV, G3, INV }, { G3, H3, F3, INV }, { F3, G3, E3, INV }, { E3, F3, D3, INV }, { D3, E3, C3, INV }, { C3, D3, B3, INV }, { B3, C3, A3, INV }, { A3, B3, INV, INV },    // 5's 
                            { H2, INV, G2, INV }, { G2, H2, F2, INV }, { F2, G2, E2, INV }, { E2, F2, D2, INV }, { D2, E2, C2, INV }, { C2, D2, B2, INV }, { B2, C2, A2, INV }, { A2, B2, INV, INV },    // 6's
                            { H1, INV, G1, A5 },  { G1, H1, F1, B5 },  { F1, G1, E1, C5 },  { E1, F1, D1, D5 },  { D1, E1, C1, E5 },  { C1, D1, B1, F5 },  { B1, C1, A1, G5 },  { A1, B1, INV , H5}      // 7's
                    };   

    int knightMoves[MAX_SQUARES][MAX_KNIGHT_KILL_SQUARES] = {

                                { INV, INV, C2, B3, INV, INV, INV, INV }, { INV, C1, C3, B4, INV, INV, INV, INV },  // A1 & A2
                                { B1, C2, C4, B5, INV, INV, INV, INV },   { B2, C3, C5, B6, INV, INV, INV, INV },   // A3 & A4
                                { B3, C4, C6, B7, INV, INV, INV, INV },   { B4, C5, C7, B8, INV, INV, INV, INV },   // A5 & A6
                                { B5, C6, C8, INV, INV, INV, INV, INV },  { B6, C7, INV, INV, INV, INV, INV, INV }, // A7 & A8
                                
                                { INV, INV, D2, C3, A3, INV, INV, INV },  { INV, D1, D3, C4, A4, INV, INV, INV },   // B1 & B2
                                { C1, D2, D4, C5, A5, INV, INV, A1 },     { C2, D3, D5, C6, A6, INV, INV, A2 },     // B3 & B4
                                { C3, D4, D6, C7, A7, INV, INV, A3 },     { C4, D5, D7, C8, A8, INV, INV, A4 },     // B5 & B6
                                { C5, D6, D8, INV, INV, INV, INV, A5 },   { C6, D7, INV, INV, INV, INV, INV, A6 },  // B7 & B8

                                { INV, INV, E2, D3, B3, A2, INV, INV },   { INV, E1, E3, D4, B4, A3, A1, INV },     // C1 & C2
                                { D1, E2, E4, D5, B5, A4, A2, B1 },       { D2, E3, E5, D6, B6, A5, A3, B2 },       // C3 & C4
                                { D3, E4, E6, D7, B7, A6, A4, B3 },       { D4, E5, E7, D8, B8, A7, A5, B4 },       // C5 & C6
                                { D5, E6, E7, INV, INV, A8, A6, B5 },     { D6, E7, INV, INV, INV, INV, A7, B6 },   // C7 & C8

                                { INV, INV, F2, E3, C3, B2, INV, INV },   { INV, F1, F3, E4, C4, B3, B1, INV },     // D1 & D2
                                { E1, F2, F4, E5, C5, B4, B2, C1 },       { E2, F3, F5, E6, C6, B5, B3, C2 },       // D3 & D4
                                { E3, F4, F6, E7, C7, B6, B4, C3 },       { E4, F5, F7, E8, C8, B7, B5, C4 },       // D5 & D6
                                { E5, F6, F8, INV, INV, B8, B6, C5 },     { E6, F7, INV, INV, INV, INV, B7, C6 },   // D7 & D8

                                { INV, INV, G2, F3, D3, C2, INV, INV },   { INV, G1, G3, F4, D4, C3, C1, INV },     // E1 & E2
                                { F1, G2, G4, F5, D5, C4, C2, D1 },       { F2, G3, G5, F6, D6, C5, C3, D2 },       // E3 & E4
                                { F3, G4, G6, F7, D7, C6, C4, D3 },       { F4, G5, G7, F8, D8, C7, C5, D4 },       // E5 & E6
                                { F5, G6, G8, INV, INV, C8, C6, D5 },     { F6, G7, INV, INV, INV, INV, C7, D6 },   // E7 & E8

                                { INV, INV, H2, G3, E3, D2, INV, INV },   { INV, H1, H3, G4, E4, D3, D1, INV },     // F1 & F2
                                { G1, H2, H4, G5, E5, D4, D2, E1 },       { G2, H3, H5, G6, E6, D5, D3, E2 },       // F3 & F4
                                { G3, H4, H6, G7, E7, D6, D4, E3 },       { G4, H5, H7, G8, E8, D7, D5, E4 },       // F5 & F6
                                { G5, H6, H8, INV, INV, D8, D6, E5 },     { G6, H7, INV, INV, INV, INV, D7, E6 },   // F7 & F8

                                { INV, INV, H3, F3, E2, INV, INV, INV },  { INV, INV, INV, H4, F4, E3, E1, INV },   // G1 & G2
                                { H1, INV, INV, H5, F5, E4, E2, F1 },     { H2, INV, INV, H6, F6, E5, E3, F2 },     // G3 & G4
                                { H3, INV, INV, H7, F7, E6, E4, F3 },     { H4, INV, INV, H8, F8, E7, E5, F4 },     // G5 & G6
                                { H5, INV, INV, INV, INV, E8, E6, F5 },   { INV, INV, E2, F3, H3, INV, INV, INV },  // G7 & G8

                                { INV, INV, INV, INV, G3, F2, INV, INV }, { INV, INV, INV, INV, G4, F3, F1, INV },  // H1 & H2
                                { INV, INV, INV, INV, G5, F4, F2, G1 },   { INV, INV, INV, INV, G6, F5, F4, G2 },   // H3 & H4
                                { INV, INV, INV, INV, G7, F6, F4, G3 },   { INV, INV, INV, INV, G8, F7, F5, G4 },   // H5 & H6
                                { INV, INV, INV, INV, INV, F8, F6, G5 },  { INV, INV, INV, INV, INV, INV, F7, G6 }, // H7 & H8

    };

    int kingMoves[MAX_SQUARES][MAX_KING_KILL_SQUARES] = {
                    { B1, B2, A2, INV, INV, INV, INV, INV }, { A1, A3, B1, B2, B3, INV, INV, INV },    // A1 & A2
                    { A2, A4, B2, B3, B4, INV, INV, INV },   { A3, A5, B3, B4, B5, INV, INV, INV },    // A3 & A4
                    { A4, A6, B4, B5, B6, INV, INV, INV },   { A5, A7, B5, B6, B7, INV, INV, INV },    // A5 & A6
                    { A6, A8, B6, B7, B8, INV, INV, INV },   { A7, B7, B8, INV, INV, INV, INV, INV },  // A7 & A8

                    { A1, A2, B2, C1, C2, INV, INV, INV },   { A1, B1, C1, A2, C2, A3, B3, C3 },       // B1 & B2
                    { A2, B2, C2, A3, C3, A4, B4, C4 },      { A3, B3, C3, A4, C4, A5, B5, C5 },       // B3 & B4
                    { A4, B4, C4, A5, C5, A6, B6, C6 },      { A5, A5, B5, A6, C6, A7, B7, C7 },       // B5 & B6
                    { A6, B6, C6, A7, C7, A8, B8, C8 },      { A7, A8, B7, C7, C8, INV, INV, INV },    // B7 & B8

                    { B1, B2, C2, D1, D2, INV, INV, INV }, { B1, C1, D1, B2, D2, B3, C3, D3 },         // C1 & C2
                    { B2, C2, C3, B3, D3, B4, C4, D4 },    { B3, C3, D3, B4, D4, B5, C5, D5 },         // C3 & C4
                    { B4, C4, D4, B5, D5, B6, C6, C6 },    { B5, C5, D5, B6, D6, B7, C7, D7 },         // C5 & C6
                    { B6, C6, D6, B7, D7, B8, C8, D8 },    { B7, B8, C7, D7, D8, INV, INV, INV },      // C7 & C8

                    { C1, C2, D2, E1, E2, INV, INV, INV }, { C1, D1, E1, C2, E2, C3, D3, E3 },         // D1 & D2
                    { C2, D2, E2, C3, E3, C4, D4, E4 },    { C3, D3, E3, C4, E4, C5, D5, E5 },         // D3 & D4
                    { C4, D4, E4, C5, E5, C6, D6, E6 },    { C5, D5, E5, C6, E6, C7, D7, E7 },         // D5 & D6
                    { C6, D6, E6, C7, E7, C8, D8, E8 },    { C7, D7, E7, C8, E8, INV, INV, INV },      // D7 & D8

                    { D1, D2, E2, F1, F2, INV, INV, INV },   { D1, E1, F1, D2, E2, D3, E3, F3 },       // E1 & E2
                    { D2, E2, F2, D3, E3, D4, E4, F4 },      { D3, E3, F3, D4, E4, D5, E5, F5 },       // E3 & E4
                    { D4, E4, F4, D5, E5, D6, E6, F6 },      { D5, E5, F5, D6, E6, D7, E7, F7 },       // E5 & E6
                    { D6, E6, F6, D7, E7, D8, E8, F8 },      { D7, D8, E7, F7, F8, INV, INV, INV },    // E7 & E8

                    { E1, E2, F2, G1, G2, INV, INV, INV },   { E1, F1, G1, E2, G2, E3, F3, G3 },       // F1 & F2
                    { E2, F2, G2, E3, G3, E4, F4, G4 },      { E3, F3, G3, E4, G4, E5, F5, G5 },       // F3 & F4
                    { E4, F4, G4, E5, G5, E6, F6, G6 },      { E5, F5, G5, E6, G6, E7, F7, G7 },       // F5 & F6
                    { E6, F6, G6, E7, G7, E8, F8, G8 },      { E7, E8, F7, G7, G8, INV, INV, INV },    // F7 & F8

                    { F1, F2, G2, H1, H2, INV, INV, INV },   { F1, G1, H1, F2, H2, F3, G3, H3 },       // G1 & G2
                    { F2, G2, H2, F3, H3, F4, G4, H4 },      { F3, G3, H3, F4, H4, F5, G5, H5 },       // G3 & G4
                    { F4, G4, H4, F5, H5, F6, G6, H6 },      { F5, G5, H5, F6, H6, F7, G7, H7 },       // G5 & G6
                    { F6, G6, H6, F7, H7, F8, G8, H8 },      { F7, F8, G7, H7, H8, INV, INV, INV },    // G7 & G8

                    { G1, G2, H2, INV, INV, INV, INV, INV }, { G1, H1, G2, G3, H3, INV, INV, INV },    // H1 & H2
                    { G2, H2, G3, G4, H4, INV, INV, INV },   { G3, H3, G4, G5, H5, INV, INV, INV },    // H3 & H4
                    { G4, H4, G5, G6, H6, INV, INV, INV },   { G5, H5, G6, G7, H7, INV, INV, INV },    // H5 & H6
                    { G6, H6, G7, G8, H8, INV, INV, INV },   { G7, H7, G8, INV, INV, INV, INV, INV },  // H7 & H8
    };

    int horizontalsAndVerticals[MAX_SQUARES][NUM_LINES][MAX_LINE] = {
        { {INV, INV, INV, INV, INV, INV, INV},  {B1, C1, D1, E1, F1, G1, H1},  {A2, A3, A4, A5, A6, A7, A8},         {INV, INV, INV, INV, INV, INV, INV} }, // A's
        { {A1, INV, INV, INV, INV, INV, INV},   {B2, C2, D2, E2, F2, G2, H2},  {A3, A4, A5, A6, A7, A8, INV},        {INV, INV, INV, INV, INV, INV, INV} }, // 
        { {A2, A1, INV, INV, INV, INV, INV},    {B3, C3, D3, E3, F3, G3, H3},  {A4, A5, A6, A7, A8, INV, INV},       {INV, INV, INV, INV, INV, INV, INV} }, // 
        { {A3, A2, A1, INV, INV, INV, INV},     {B4, C4, D4, E4, F4, G4, H4},  {A5, A6, A7, A8, INV, INV, INV},      {INV, INV, INV, INV, INV, INV, INV} }, // 
        { {A4, A3, A2, A1, INV, INV, INV},      {B5, C5, D5, E5, F5, G5, H5},  {A6, A7, A8, INV, INV, INV, INV},     {INV, INV, INV, INV, INV, INV, INV} }, // 
        { {A5, A4, A3, A2, A1, INV, INV},       {B6, C6, D6, E6, F6, G6, H6},  {A7, A8, INV, INV, INV, INV, INV},    {INV, INV, INV, INV, INV, INV, INV} }, // 
        { {A6, A5, A4, A3, A2, A1, INV},        {B7, C7, D7, E7, F7, G7, H7},  {A8, INV, INV, INV, INV, INV, INV},   {INV, INV, INV, INV, INV, INV, INV} }, // 
        { {A7, A6, A5, A4, A3, A2, A1},         {B8, C8, D8, E8, F8, G8, H8},  {INV, INV, INV, INV, INV, INV, INV},  {INV, INV, INV, INV, INV, INV, INV} }, //

        { {INV, INV, INV, INV, INV, INV, INV},  {C1, D1, E1, F1, G1, H1, INV},  {B2, B3, B4, B5, B6, B7, B8},         {A1, INV, INV, INV, INV, INV, INV} }, // B's
        { {B1, INV, INV, INV, INV, INV, INV},   {C2, D2, E2, F2, G2, H2, INV},  {B3, B4, B5, B6, B7, B8, INV},        {A2, INV, INV, INV, INV, INV, INV} }, // 
        { {B2, B1, INV, INV, INV, INV, INV},    {C3, D3, E3, F3, G3, H3, INV},  {B4, B5, B6, B7, B8, INV, INV},       {A3, INV, INV, INV, INV, INV, INV} }, // 
        { {B3, B2, B1, INV, INV, INV, INV},     {C4, D4, E4, F4, G4, H4, INV},  {B5, B6, B7, B8, INV, INV, INV},      {A4, INV, INV, INV, INV, INV, INV} }, //
        { {B4, B3, B2, B1, INV, INV, INV},      {C5, D5, E5, F5, G5, H5, INV},  {B6, B7, B8, INV, INV, INV, INV},     {A5, INV, INV, INV, INV, INV, INV} }, //
        { {B5, B4, B3, B2, B1, INV, INV},       {C6, D6, E6, F6, G6, H6, INV},  {B7, B8, INV, INV, INV, INV, INV},    {A6, INV, INV, INV, INV, INV, INV} }, // 
        { {B6, B5, B4, B3, B2, B1, INV},        {C7, D7, E7, F7, G7, H7, INV},  {B8, INV, INV, INV, INV, INV, INV},   {A7, INV, INV, INV, INV, INV, INV} }, // 
        { {B7, B6, B5, B4, B3, B2, B1},         {C8, D8, E8, F8, G8, H8, INV},  {INV, INV, INV, INV, INV, INV, INV},  {A8, INV, INV, INV, INV, INV, INV} }, //

        { {INV, INV, INV, INV, INV, INV, INV},  {D1, E1, F1, G1, H1, INV, INV},  {C2, C3, C4, C5, C6, C7, C8},         {B1, A1, INV, INV, INV, INV, INV} }, // C's
        { {C1, INV, INV, INV, INV, INV, INV},   {D2, E2, F2, G2, H2, INV, INV},  {C3, C4, C5, C6, C7, C8, INV},        {B2, A2, INV, INV, INV, INV, INV} }, // 
        { {C2, C1, INV, INV, INV, INV, INV},    {D3, E3, F3, G3, H3, INV, INV},  {C4, C5, C6, C7, C8, INV, INV},       {B3, A3, INV, INV, INV, INV, INV} }, // 
        { {C3, C2, C1, INV, INV, INV, INV},     {D4, E4, F4, G4, H4, INV, INV},  {C5, C6, C7, C8, INV, INV, INV},      {B4, A4, INV, INV, INV, INV, INV} }, //
        { {C4, C3, C2, C1, INV, INV, INV},      {D5, E5, F5, G5, H5, INV, INV},  {C6, C7, C8, INV, INV, INV, INV},     {B5, A5, INV, INV, INV, INV, INV} }, //
        { {C5, C4, C3, C2, C1, INV, INV},       {D6, E6, F6, G6, H6, INV, INV},  {C7, C8, INV, INV, INV, INV, INV},    {B6, A6, INV, INV, INV, INV, INV} }, // 
        { {C6, C5, C4, C3, C2, C1, INV},        {D7, E7, F7, G7, H7, INV, INV},  {C8, INV, INV, INV, INV, INV, INV},   {B7, A7, INV, INV, INV, INV, INV} }, // 
        { {C7, C6, C5, C4, C3, C2, C1},         {D8, E8, F8, G8, H8, INV, INV},  {INV, INV, INV, INV, INV, INV, INV},  {B8, A8, INV, INV, INV, INV, INV} }, //

        { {INV, INV, INV, INV, INV, INV, INV},  {E1, F1, G1, H1, INV, INV, INV},  {D2, D3, D4, D5, D6, D7, D8},         {C1, B1, A1, INV, INV, INV, INV} }, // D's
        { {D1, INV, INV, INV, INV, INV, INV},   {E2, F2, G2, H2, INV, INV, INV},  {D3, D4, D5, D6, D7, D8, INV},        {C2, B2, A2, INV, INV, INV, INV} }, // 
        { {D2, D1, INV, INV, INV, INV, INV},    {E3, F3, G3, H3, INV, INV, INV},  {D4, D5, D6, D7, D8, INV, INV},       {C3, B3, A3, INV, INV, INV, INV} }, // 
        { {D3, D2, D1, INV, INV, INV, INV},     {E4, F4, G4, H4, INV, INV, INV},  {D5, D6, D7, D8, INV, INV, INV},      {C4, B4, A4, INV, INV, INV, INV} }, //
        { {D4, D3, D2, D1, INV, INV, INV},      {E5, F5, G5, H5, INV, INV, INV},  {D6, D7, D8, INV, INV, INV, INV},     {B5, B5, A5, INV, INV, INV, INV} }, //
        { {D5, D4, D3, D2, D1, INV, INV},       {E6, F6, G6, H6, INV, INV, INV},  {D7, D8, INV, INV, INV, INV, INV},    {C6, B6, A6, INV, INV, INV, INV} }, // 
        { {D6, D5, D4, D3, D2, D1, INV},        {E7, F7, G7, H7, INV, INV, INV},  {D8, INV, INV, INV, INV, INV, INV},   {C7, B7, A7, INV, INV, INV, INV} }, // 
        { {D7, D6, D5, D4, D3, D2, D1},         {E8, F8, G8, H8, INV, INV, INV},  {INV, INV, INV, INV, INV, INV, INV},  {C8, B8, A8, INV, INV, INV, INV} }, //

        { {INV, INV, INV, INV, INV, INV, INV},  {F1, G1, H1, INV, INV, INV, INV},  {E2, E3, E4, E5, E6, E7, E8},         {D1, C1, B1, A1, INV, INV, INV} }, // E's
        { {E1, INV, INV, INV, INV, INV, INV},   {F2, G2, H2, INV, INV, INV, INV},  {E3, E4, E5, E6, E7, E8, INV},        {D2, C2, B2, A2, INV, INV, INV} }, // 
        { {E2, E1, INV, INV, INV, INV, INV},    {F3, G3, H3, INV, INV, INV, INV},  {E4, E5, E6, E7, E8, INV, INV},       {D3, C3, B3, A3, INV, INV, INV} }, // 
        { {E3, E2, E1, INV, INV, INV, INV},     {F4, G4, H4, INV, INV, INV, INV},  {E5, E6, E7, E8, INV, INV, INV},      {D4, C4, B4, A4, INV, INV, INV} }, //
        { {E4, E3, E2, E1, INV, INV, INV},      {F5, G5, H5, INV, INV, INV, INV},  {E6, E7, E8, INV, INV, INV, INV},     {D5, B5, B5, A5, INV, INV, INV} }, //
        { {E5, E4, E3, E2, E1, INV, INV},       {F6, G6, H6, INV, INV, INV, INV},  {E7, E8, INV, INV, INV, INV, INV},    {D6, C6, B6, A6, INV, INV, INV} }, // 
        { {E6, E5, E4, E3, E2, E1, INV},        {F7, G7, H7, INV, INV, INV, INV},  {E8, INV, INV, INV, INV, INV, INV},   {D7, C7, B7, A7, INV, INV, INV} }, // 
        { {E7, E6, E5, E4, E3, E2, E1},         {F8, G8, H8, INV, INV, INV, INV},  {INV, INV, INV, INV, INV, INV, INV},  {D8, C8, B8, A8, INV, INV, INV} }, //
        
        { {INV, INV, INV, INV, INV, INV, INV},  {G1, H1, INV, INV, INV, INV, INV},  {F2, F3, F4, F5, F6, F7, F8},         {E1, D1, C1, B1, A1, INV, INV} }, // F's
        { {F1, INV, INV, INV, INV, INV, INV},   {G2, H2, INV, INV, INV, INV, INV},  {F3, F4, F5, F6, F7, F8, INV},        {E2, D2, C2, B2, A2, INV, INV} }, // 
        { {F2, F1, INV, INV, INV, INV, INV},    {G3, H3, INV, INV, INV, INV, INV},  {F4, F5, F6, F7, F8, INV, INV},       {E3, D3, C3, B3, A3, INV, INV} }, // 
        { {F3, F2, F1, INV, INV, INV, INV},     {G4, H4, INV, INV, INV, INV, INV},  {F5, F6, F7, F8, INV, INV, INV},      {E4, D4, C4, B4, A4, INV, INV} }, //
        { {F4, F3, F2, F1, INV, INV, INV},      {G5, H5, INV, INV, INV, INV, INV},  {F6, F7, F8, INV, INV, INV, INV},     {E5, D5, B5, B5, A5, INV, INV} }, //
        { {F5, F4, F3, F2, F1, INV, INV},       {G6, H6, INV, INV, INV, INV, INV},  {F7, F8, INV, INV, INV, INV, INV},    {E6, D6, C6, B6, A6, INV, INV} }, // 
        { {F6, F5, F4, F3, F2, F1, INV},        {G7, H7, INV, INV, INV, INV, INV},  {F8, INV, INV, INV, INV, INV, INV},   {E7, D7, C7, B7, A7, INV, INV} }, // 
        { {F7, F6, F5, F4, F3, F2, F1},         {G8, H8, INV, INV, INV, INV, INV},  {INV, INV, INV, INV, INV, INV, INV},  {E8, D8, C8, B8, A8, INV, INV} }, //

        { {INV, INV, INV, INV, INV, INV, INV},  {H1, INV, INV, INV, INV, INV, INV},  {G2, G3, G4, G5, G6, G7, G8},         {F1, E1, D1, C1, B1, A1, INV} }, // G's
        { {G1, INV, INV, INV, INV, INV, INV},   {H2, INV, INV, INV, INV, INV, INV},  {G3, G4, G5, G6, G7, G8, INV},        {F2, E2, D2, C2, B2, A2, INV} }, // 
        { {G2, G1, INV, INV, INV, INV, INV},    {H3, INV, INV, INV, INV, INV, INV},  {G4, G5, G6, G7, G8, INV, INV},       {F3, E3, D3, C3, B3, A3, INV} }, // 
        { {G3, G2, G1, INV, INV, INV, INV},     {H4, INV, INV, INV, INV, INV, INV},  {G5, G6, G7, G8, INV, INV, INV},      {F4, E4, D4, C4, B4, A4, INV} }, //
        { {G4, G3, G2, G1, INV, INV, INV},      {H5, INV, INV, INV, INV, INV, INV},  {G6, G7, G8, INV, INV, INV, INV},     {F5, E5, D5, B5, B5, A5, INV} }, //
        { {G5, G4, G3, G2, G1, INV, INV},       {H6, INV, INV, INV, INV, INV, INV},  {G7, G8, INV, INV, INV, INV, INV},    {F6, E6, D6, C6, B6, A6, INV} }, // 
        { {G7, G6, G5, G4, G3, G2, G1},         {H8, INV, INV, INV, INV, INV, INV},  {INV, INV, INV, INV, INV, INV, INV},  {F8, E8, D8, C8, B8, A8, INV} }, //

        { {INV, INV, INV, INV, INV, INV, INV},  {INV, INV, INV, INV, INV, INV, INV},  {H2, H3, H4, H5, H6, H7, H8},         {G1, F1, E1, D1, C1, B1, A1} }, // H's
        { {H1, INV, INV, INV, INV, INV, INV},   {INV, INV, INV, INV, INV, INV, INV},  {H3, H4, H5, H6, H7, H8, INV},        {G2, F2, E2, D2, C2, B2, A2} }, // 
        { {H2, H1, INV, INV, INV, INV, INV},    {INV, INV, INV, INV, INV, INV, INV},  {H4, H5, H6, H7, H8, INV, INV},       {G3, F3, E3, D3, C3, B3, A3} }, // 
        { {H3, H2, H1, INV, INV, INV, INV},     {INV, INV, INV, INV, INV, INV, INV},  {H5, H6, H7, H8, INV, INV, INV},      {G5, F4, E4, D4, C4, B4, A4} }, //
        { {H4, H3, H2, H1, INV, INV, INV},      {INV, INV, INV, INV, INV, INV, INV},  {H6, H7, H8, INV, INV, INV, INV},     {G6, F5, E5, D5, B5, B5, A5} }, //
        { {H5, H4, H3, H2, H1, INV, INV},       {INV, INV, INV, INV, INV, INV, INV},  {H7, H8, INV, INV, INV, INV, INV},    {G7, F6, E6, D6, C6, B6, A6} }, // 
        { {H7, H6, H5, H4, H3, H2, H1},         {INV, INV, INV, INV, INV, INV, INV},  {INV, INV, INV, INV, INV, INV, INV},  {G8, F8, E8, D8, C8, B8, A8} }, //
    };


    int diagonals[MAX_SQUARES][NUM_LINES][MAX_LINE] = {
        { {INV, INV, INV, INV, INV, INV, INV}, {INV, INV, INV, INV, INV, INV, INV}, {B2, C3, D4, D5, E6, F7, H8},        {INV, INV, INV, INV, INV, INV, INV} },     // A's
        { {INV, INV, INV, INV, INV, INV, INV}, {B1, INV, INV, INV, INV, INV, INV},  {B3, C4, D5, E6, F7, G8, INV},       {INV, INV, INV, INV, INV, INV, INV} },     // 
        { {INV, INV, INV, INV, INV, INV, INV}, {B2, C1, INV, INV, INV, INV, INV},   {B4, C5, D6, E7, G8, INV, INV},      {INV, INV, INV, INV, INV, INV, INV} },     // 
        { {INV, INV, INV, INV, INV, INV, INV}, {B3, C2, D1, INV, INV, INV, INV},    {B5, C6, D7, E8, INV, INV, INV},     {INV, INV, INV, INV, INV, INV, INV} },     // 
        { {INV, INV, INV, INV, INV, INV, INV}, {B4, C3, D2, E1, INV, INV, INV},     {B6, C7, D8, INV, INV, INV, INV},    {INV, INV, INV, INV, INV, INV, INV} },     // 
        { {INV, INV, INV, INV, INV, INV, INV}, {B5, C4, D3, E2, F1, INV, INV},      {B7, C8, INV, INV, INV, INV, INV},   {INV, INV, INV, INV, INV, INV, INV} },     // 
        { {INV, INV, INV, INV, INV, INV, INV}, {B6, C5, D4, E3, F2, G1, INV},       {B8, INV, INV, INV, INV, INV, INV},  {INV, INV, INV, INV, INV, INV, INV} },     // 
        { {INV, INV, INV, INV, INV, INV, INV}, {B7, C6, D5, E4, F3, G2, H1},        {INV, INV, INV, INV, INV, INV, INV}, {INV, INV, INV, INV, INV, INV, INV} },     //

        { {INV, INV, INV, INV, INV, INV, INV}, {INV, INV, INV, INV, INV, INV, INV}, {C2, D3, E4, F5, G6, H7, INV},       {A2, INV, INV, INV, INV, INV, INV} },      // B's
        { {A1, INV, INV, INV, INV, INV, INV},  {C1, INV, INV, INV, INV, INV, INV},  {C3, D4, E5, F6, G7, H8, INV},       {A3, INV, INV, INV, INV, INV, INV} },      // 
        { {A2, INV, INV, INV, INV, INV, INV},  {C2, D1, INV, INV, INV, INV, INV},   {C4, D5, E6, F7, G8, INV, INV},      {A4, INV, INV, INV, INV, INV, INV} },      // 
        { {A3, INV, INV, INV, INV, INV, INV},  {C3, D2, E1, INV, INV, INV, INV},    {C5, D6, E7, F8, INV, INV, INV},     {A5, INV, INV, INV, INV, INV, INV} },      // 
        { {A4, INV, INV, INV, INV, INV, INV},  {C4, D3, E2, F1, INV, INV, INV},     {C6, D7, E8, INV, INV, INV, INV},    {A6, INV, INV, INV, INV, INV, INV} },      // 
        { {A5, INV, INV, INV, INV, INV, INV},  {C5, D4, E3, F2, G1, INV, INV},      {C7, D8, INV, INV, INV, INV, INV},   {A7, INV, INV, INV, INV, INV, INV} },      // 
        { {A6, INV, INV, INV, INV, INV, INV},  {C6, D5, E4, F3, G2, H1, INV},       {C8, INV, INV, INV, INV, INV, INV},  {A8, INV, INV, INV, INV, INV, INV} },      // 
        { {A7, INV, INV, INV, INV, INV, INV},  {C7, D6, E5, F4, G3, H2, INV},       {INV, INV, INV, INV, INV, INV, INV}, {INV, INV, INV, INV, INV, INV, INV} },     //

        { {INV, INV, INV, INV, INV, INV, INV}, {INV, INV, INV, INV, INV, INV, INV}, {D2, E3, F4, G5, H6, INV, INV},      {B2, A3, INV, INV, INV, INV, INV} },       // C's
        { {B1, INV, INV, INV, INV, INV, INV},  {D1, INV, INV, INV, INV, INV, INV},  {D3, E4, F5, G6, H7, INV, INV},      {B3, A4, INV, INV, INV, INV, INV} },       // 
        { {B2, A1, INV, INV, INV, INV, INV},   {D2, E1, INV, INV, INV, INV, INV},   {D4, E5, F6, G7, H8, INV, INV},      {B4, A5, INV, INV, INV, INV, INV} },       // 
        { {B3, A2, INV, INV, INV, INV, INV},   {D3, E2, F1, INV, INV, INV, INV},    {D5, E6, F7, G8, INV, INV, INV},     {B5, A6, INV, INV, INV, INV, INV} },       // 
        { {B4, A3, INV, INV, INV, INV, INV},   {D4, E3, F2, G1, INV, INV, INV},     {D6, E7, F8, INV, INV, INV, INV},    {B6, A7, INV, INV, INV, INV, INV} },       // 
        { {B5, A4, INV, INV, INV, INV, INV},   {D5, E4, F3, G2, H1, INV, INV},      {D7, E8, INV, INV, INV, INV, INV},   {B7, A8, INV, INV, INV, INV, INV} },       // 
        { {B6, A5, INV, INV, INV, INV, INV},   {D6, E5, F4, G3, H2, INV, INV},      {D8, INV, INV, INV, INV, INV, INV},  {B8, INV, INV, INV, INV, INV, INV} },      // 
        { {B7, A6, INV, INV, INV, INV, INV},   {D7, E6, F5, G4, H3, INV, INV},      {INV, INV, INV, INV, INV, INV, INV}, {INV, INV, INV, INV, INV, INV, INV} },     //

        { {INV, INV, INV, INV, INV, INV, INV}, {INV, INV, INV, INV, INV, INV, INV}, {E2, F3, G4, H5, INV, INV, INV},      {C2, B3, A4, INV, INV, INV, INV} },       // D's
        { {C1, INV, INV, INV, INV, INV, INV},  {E1, INV, INV, INV, INV, INV, INV},  {E3, F4, G5, H6, INV, INV, INV},      {C3, B4, A3, INV, INV, INV, INV} },       // 
        { {C2, B1, INV, INV, INV, INV, INV},   {E2, F1, INV, INV, INV, INV, INV},   {E4, F5, G6, H7, INV, INV, INV},      {C4, B5, A4, INV, INV, INV, INV} },       // 
        { {C3, B2, A1, INV, INV, INV, INV},    {E3, F2, G1, INV, INV, INV, INV},    {E5, F6, G7, H8, INV, INV, INV},      {C5, B6, A5, INV, INV, INV, INV} },       // 
        { {C4, B3, A2, INV, INV, INV, INV},    {E4, F3, G2, H1, INV, INV, INV},     {E6, F7, G8, INV, INV, INV, INV},     {C6, B7, A6, INV, INV, INV, INV} },       // 
        { {C5, B4, A3, INV, INV, INV, INV},    {E5, F4, G3, H2, INV, INV, INV},     {E7, F8, INV, INV, INV, INV, INV},    {C7, B8, INV, INV, INV, INV, INV} },      // 
        { {C6, B5, A4, INV, INV, INV, INV},    {E6, F5, G4, H3, INV, INV, INV},     {E8, INV, INV, INV, INV, INV, INV},   {C8, INV, INV, INV, INV, INV, INV} },     // 
        { {C7, B6, A5, INV, INV, INV, INV},    {E7, F6, G5, H4, INV, INV, INV},     {INV, INV, INV, INV, INV, INV, INV},  {INV, INV, INV, INV, INV, INV, INV} },    //

        { {INV, INV, INV, INV, INV, INV, INV}, {INV, INV, INV, INV, INV, INV, INV}, {F2, G3, H4, INV, INV, INV, INV},     {D2, C3, B4, A5, INV, INV, INV} },        // E's
        { {D1, INV, INV, INV, INV, INV, INV},  {F1, INV, INV, INV, INV, INV, INV},  {F3, G4, H5, INV, INV, INV, INV},     {D3, C4, B5, A6, INV, INV, INV} },        // 
        { {D2, C1, INV, INV, INV, INV, INV},   {F2, G1, INV, INV, INV, INV, INV},   {F4, G5, H6, INV, INV, INV, INV},     {D4, C5, B6, A7, INV, INV, INV} },        // 
        { {D3, C2, B1, INV, INV, INV, INV},    {F3, G2, H1, INV, INV, INV, INV},    {F5, G6, H7, INV, INV, INV, INV},     {D5, C6, B7, A8, INV, INV, INV} },        // 
        { {D4, C3, B2, A1, INV, INV, INV},     {F4, G3, H2, INV, INV, INV, INV},    {F6, G7, H8, INV, INV, INV, INV},     {D6, C7, B8, INV, INV, INV, INV} },       // 
        { {D5, C4, B3, A2, INV, INV, INV},     {F5, G4, H3, INV, INV, INV, INV},    {F7, G8, INV, INV, INV, INV, INV},    {D7, C8, INV, INV, INV, INV, INV} },      // 
        { {D6, C5, B4, A3, INV, INV, INV},     {F6, G5, H4, INV, INV, INV, INV},    {F8, INV, INV, INV, INV, INV, INV},   {D8, INV, INV, INV, INV, INV, INV} },     // 
        { {D7, C6, B5, A4, INV, INV, INV},     {F7, G6, H5, INV, INV, INV, INV},    {INV, INV, INV, INV, INV, INV, INV},  {INV, INV, INV, INV, INV, INV, INV} },    //
        
        { {INV, INV, INV, INV, INV, INV, INV}, {INV, INV, INV, INV, INV, INV, INV}, {G2, H3, INV, INV, INV, INV, INV},    {E2, D3, C4, B5, A6, INV, INV} },         // F's
        { {E1, INV, INV, INV, INV, INV, INV},  {G1, INV, INV, INV, INV, INV, INV},  {G3, H4, INV, INV, INV, INV, INV},    {E3, D4, C5, B6, A7, INV, INV} },         // 
        { {E2, D1, INV, INV, INV, INV, INV},   {G2, H1, INV, INV, INV, INV, INV},   {G4, H5, INV, INV, INV, INV, INV},    {E4, D5, C6, B7, A8, INV, INV} },         // 
        { {E3, D2, C1, INV, INV, INV, INV},    {G3, H2, INV, INV, INV, INV, INV},   {G5, H6, INV, INV, INV, INV, INV},    {E5, D6, C7, B8, INV, INV, INV} },        // 
        { {E4, D3, C2, B1, INV, INV, INV},     {G4, H3, INV, INV, INV, INV, INV},   {G6, H7, INV, INV, INV, INV, INV},    {E6, D7, C8, INV, INV, INV, INV} },       // 
        { {E5, D4, C3, B2, A1, INV, INV},      {G5, H4, INV, INV, INV, INV, INV},   {G7, H8, INV, INV, INV, INV, INV},    {E7, D8, INV, INV, INV, INV, INV} },      // 
        { {E6, D5, C4, B3, A2, INV, INV},      {G6, H5, INV, INV, INV, INV, INV},   {G8, INV, INV, INV, INV, INV, INV},   {E8, INV, INV, INV, INV, INV, INV} },     // 
        { {E7, D6, C5, B4, A3, INV, INV},      {G7, H6, INV, INV, INV, INV, INV},   {INV, INV, INV, INV, INV, INV, INV},  {INV, INV, INV, INV, INV, INV, INV} },    //

        { {INV, INV, INV, INV, INV, INV, INV}, {INV, INV, INV, INV, INV, INV, INV},  {H2, INV, INV, INV, INV, INV, INV},  {F2, E3, D4, C5, B6, A7, INV} },          // G's
        { {F1, INV, INV, INV, INV, INV, INV},  {H1, INV, INV, INV, INV, INV, INV},   {H3, INV, INV, INV, INV, INV, INV},  {F3, E4, D5, C6, B7, A8, INV} },          // 
        { {F2, E1, INV, INV, INV, INV, INV},   {H2, INV, INV, INV, INV, INV, INV},   {H4, INV, INV, INV, INV, INV, INV},  {F4, E5, D6, C7, B8, INV, INV} },         // 
        { {F3, E2, D1, INV, INV, INV, INV},    {H3, INV, INV, INV, INV, INV, INV},   {H5, INV, INV, INV, INV, INV, INV},  {F5, E6, D7, C8, INV, INV, INV} },        // 
        { {F4, E3, D2, C1, INV, INV, INV},     {H4, INV, INV, INV, INV, INV, INV},   {H6, INV, INV, INV, INV, INV, INV},  {F6, E7, D8, INV, INV, INV, INV} },       // 
        { {F5, E4, D3, C2, B1, INV, INV},      {H5, INV, INV, INV, INV, INV, INV},   {H7, INV, INV, INV, INV, INV, INV},  {F7, E8, INV, INV, INV, INV, INV} },      // 
        { {F6, E5, D4, C3, B2, A1, INV},       {H6, INV, INV, INV, INV, INV, INV},   {H8, INV, INV, INV, INV, INV, INV},  {F8, INV, INV, INV, INV, INV, INV} },     // 
        { {F7, E6, D5, C4, B3, A2, INV},       {H7, INV, INV, INV, INV, INV, INV},   {INV, INV, INV, INV, INV, INV, INV}, {INV, INV, INV, INV, INV, INV, INV} },    //

        { {INV, INV, INV, INV, INV, INV, INV}, {INV, INV, INV, INV, INV, INV, INV},  {INV, INV, INV, INV, INV, INV, INV}, {G2, F3, E4, D5, C6, B7, A8} },           // H's
        { {G1, INV, INV, INV, INV, INV, INV},  {INV, INV, INV, INV, INV, INV, INV},  {INV, INV, INV, INV, INV, INV, INV}, {G3, F4, E5, D6, C7, B8, INV} },          // 
        { {G2, F1, INV, INV, INV, INV, INV},   {INV, INV, INV, INV, INV, INV, INV},  {INV, INV, INV, INV, INV, INV, INV}, {G4, F5, E6, D7, C8, INV, INV} },         // 
        { {G3, F2, E1, INV, INV, INV, INV},    {INV, INV, INV, INV, INV, INV, INV},  {INV, INV, INV, INV, INV, INV, INV}, {G5, F6, E7, D8, INV, INV, INV} },        // 
        { {G4, F3, E2, D1, INV, INV, INV},     {INV, INV, INV, INV, INV, INV, INV},  {INV, INV, INV, INV, INV, INV, INV}, {G6, F7, E8, INV, INV, INV, INV} },       // 
        { {G5, F4, E3, D2, C1, INV, INV},      {INV, INV, INV, INV, INV, INV, INV},  {INV, INV, INV, INV, INV, INV, INV}, {G7, F8, INV, INV, INV, INV, INV} },      // 
        { {G6, F5, E4, D3, C2, B1, INV},       {INV, INV, INV, INV, INV, INV, INV},  {INV, INV, INV, INV, INV, INV, INV}, {G8, INV, INV, INV, INV, INV, INV} },     // 
        { {G7, F6, E5, D4, C3, B2, A1},        {INV, INV, INV, INV, INV, INV, INV},  {INV, INV, INV, INV, INV, INV, INV}, {INV, INV, INV, INV, INV, INV, INV} }     //
    };


    // Structures for the individual chess pieces.
    struct ChessPiece{
        char identity;
        char name[PIECE_NAME_LEN];
        int currentSquare;
        int pieceWeight;
        bool isAlive;
    };

    struct Pawn{
        struct ChessPiece * pce;
        int killingMoves[NUM_PAWN_MOVE_TYPES];
        int possibleMoves[NUM_PAWN_MOVE_TYPES];
    };

    struct Bishop {
        struct ChessPiece * pce;
        int killingMoves[MAX_BISHOP_KILL_SQUARES];
        int possibleMoves[MAX_BISHOP_KILL_SQUARES];
    };

    struct Knight {
        struct ChessPiece * pce;
        int killingMoves[MAX_KNIGHT_KILL_SQUARES];
        int possibleMoves[MAX_KNIGHT_KILL_SQUARES];
    };

    struct Rook {
        struct ChessPiece * pce;
        int killingMoves[MAX_ROOK_KILL_SQUARES];
        int possibleMoves[MAX_ROOK_KILL_SQUARES];
    };

    struct QueenMoves {
        int horizontalVerticalMoves[MAX_ROOK_POSSIBLE_MOVES];
        int diagonalMoves[MAX_BISHOP_POSSIBLE_MOVES];
        int killingMoves[MAX_QUEEN_KILL_SQUARES];
    };

    struct Queen {
        struct ChessPiece * pce;
        struct QueenMoves * moves;
    };

    struct King {
        struct ChessPiece * pce;
        int killingMoves[MAX_KING_KILL_SQUARES];
        int possibleMoves[MAX_KING_KILL_SQUARES];
    };

    // The assembled team each player will have.
    struct Army {
        struct Pawn * pawns[NUM_PAWNS];
        struct Rook * rooks[MAX_POSSIBLE_ROOKS];
        struct Knight * knights[MAX_POSSIBLE_KNIGHTS];
        struct Bishop * bishops[MAX_POSSIBLE_BISHOPS];
        struct Queen * queens[MAX_POSSIBLE_QUEENS];
        struct King * king;
        int colour;
    };

    // The actual player structure that will contain the army.
    struct Player {
        char name[MAX_NAME_LEN];
        struct Army * army;
    };

#endif