/* File Name: chess->h
 * File Description: Implementation file for chess->h->
 * Student Name: Greg Shalay
 * UoG: 1096689
 */

#include "chess.h"

void freeChessPiece(struct ChessPiece * pce){
    free(pce);
}

void freePawn(struct Pawn * pawn){
    freeChessPiece(pawn->pce);
    free(pawn);
}

void freeRook(struct Rook * rook){
    freeChessPiece(rook->pce);
    free(rook);
}

void freeKnight(struct Knight * knight){
    freeChessPiece(knight->pce);
    free(knight);
}

void freeBishop(struct Bishop * bishop){
    freeChessPiece(bishop->pce);
    free(bishop);
}

void freeQueenMoves(struct QueenMoves * moves){
    free(moves);
}

void freeQueen(struct Queen * queen){
    freeChessPiece(queen->pce);
    freeQueenMoves(queen->moves);
    free(queen);
}

void freeKing(struct King * king){
    freeChessPiece(king->pce);
    free(king);
}

void freePawns(struct Pawn * pawns[NUM_PAWNS]){
    for(int i = 0; i < NUM_PAWNS; i++){
        if(pawns[i] != NULL){
           freePawn(pawns[i]); 
        }
    }
}

void freeRooks(struct Rook * rooks[MAX_POSSIBLE_ROOKS]){
    for(int i = 0; i < MAX_POSSIBLE_ROOKS; i++){
        if(rooks[i] != NULL){
            freeRook(rooks[i]);
        }    
    }
}

void freeKnights(struct Knight * knights[MAX_POSSIBLE_KNIGHTS]){
    for(int i = 0; i < MAX_POSSIBLE_KNIGHTS; i++){
        if(knights[i] != NULL){
            freeKnight(knights[i]);
        }    
    }
}

void freeBishops(struct Bishop * bishops[MAX_POSSIBLE_BISHOPS]){
    for(int i = 0; i < MAX_POSSIBLE_BISHOPS; i++){
        if(bishops[i] != NULL){
            freeBishop(bishops[i]);
        }    
    }
}

void freeQueens(struct Queen * queens[MAX_POSSIBLE_QUEENS]){
    for(int i = 0; i < MAX_POSSIBLE_QUEENS; i++){
        if(queens[i] != NULL){
            freeQueen(queens[i]);
        }    
    }
}

void freeArmy(struct Army * army){
    // Free the other pointers first.
    freePawns(army->pawns);
    freeRooks(army->rooks);
    freeKnights(army->knights);
    freeBishops(army->bishops);
    freeQueens(army->queens);
    freeKing(army->king);

    // Now free the actual army pointer.
    free(army);
}

void freePlayer(struct Player * player){
    freeArmy(player->army);
    free(player);
}

void nl(){
    printf("\n");
}

int getMax(int val1, int val2){
    if(val1 > val2){
        return val1;
    }
    else if(val1 < val2){
        return val2;
    }
    else{ // Values equal. Return INV.
        return INV;
    }
}

int getMin(int val1, int val2){
    if(val1 < val2){
        return val1;
    }
    else if(val1 > val2){
        return val2;
    }
    else{ // Values equal. Return INV.
        return INV;
    }
}

int getFirstAvailableIndex(int moves[], int length){
    for(int i = 0; i < length; i++){
        if(moves[i] == INV){
            return i;
        }
    }

    return INV;
} 

// Simple method that gets the coordinate index for a square (i.e a1) from the lookup array so that move referennce arrays can be used.
int getCoordIdxByBoardPosition(int boardPos){
    for(int i = 0; i < MAX_SQUARES; i++){
        if(boardPos == coordsToIdx[i]){
            return i;
        }
    }

    return -1;
}

int * resetMoves(int arr[], int len){
    for(int i = 0; i < len; i++){
        arr[i] = INV;
    }

    return arr;
}

bool isEmptyArray(int arr[], int length){
    for(int i = 0; i < length; i++){
        if(arr[i] != INV){
            return false;
        }
    }

    return true;
}

struct Pawn ** writeDefaultHumanPawnMoves(struct Pawn * pawns[]){
    for(int i = 0; i < NUM_PAWNS; i++){
        switch(i){
            case 0:
                pawns[i]->pce->currentSquare = coordsToIdx[A7];
                break;
            case 1:
                pawns[i]->pce->currentSquare = coordsToIdx[B7];
                break;
            case 2:
                pawns[i]->pce->currentSquare = coordsToIdx[C7];
                break;
            case 3:
                pawns[i]->pce->currentSquare = coordsToIdx[D7];
                break;
            case 4:
                pawns[i]->pce->currentSquare = coordsToIdx[E7];
                break;
            case 5:
                pawns[i]->pce->currentSquare = coordsToIdx[F7];
                break;
            case 6:
                pawns[i]->pce->currentSquare = coordsToIdx[G7];
                break;
            case 7:
                pawns[i]->pce->currentSquare = coordsToIdx[H7];
                break;
            default:
                break;
        }
    }
    
    return pawns;
}

struct Pawn ** writeDefaultComputerPawnMoves(struct Pawn * pawns[]){
    for(int i = 0; i < NUM_PAWNS; i++){
        switch(i){
            case 0:
                pawns[i]->pce->currentSquare = coordsToIdx[A2];
                break;
            case 1:
                pawns[i]->pce->currentSquare = coordsToIdx[B2];
                break;
            case 2:
                pawns[i]->pce->currentSquare = coordsToIdx[C2];
                break;
            case 3:
                pawns[i]->pce->currentSquare = coordsToIdx[D2];
                break;
            case 4:
                pawns[i]->pce->currentSquare = coordsToIdx[E2];
                break;
            case 5:
                pawns[i]->pce->currentSquare = coordsToIdx[F2];
                break;
            case 6:
                pawns[i]->pce->currentSquare = coordsToIdx[G2];
                break;
            case 7:
                pawns[i]->pce->currentSquare = coordsToIdx[H2];
                break;
            default:
                break;
        }
    }
    
    return pawns;
}

struct Knight ** writeDefaultKnightMoves(struct Knight * knights[], int mode){
    for(int i = 0; i < NUM_KNIGHTS; i++){
        if(i == 0){
            if(mode == PLAYER_TURN){
                knights[i]->pce->currentSquare = chessBoard[coordsToIdx[B8]];
            }
            else if(mode == ENEMY_TURN){
                knights[i]->pce->currentSquare = chessBoard[coordsToIdx[G8]];
            }

        }
        else if(i == 1){
            if(mode == PLAYER_TURN){
                knights[i]->pce->currentSquare = chessBoard[coordsToIdx[B1]];
            }
            else if(mode == ENEMY_TURN){
                knights[i]->pce->currentSquare = chessBoard[coordsToIdx[G1]];
            }
        }

        memcpy(knights[i]->possibleMoves, knightMoves[getCoordIdxByBoardPosition(knights[i]->pce->currentSquare)], sizeof(knights[i]->possibleMoves));
    }

    return knights;
}

void writeDefaultBishopMoves(struct Bishop * bishop){
    int diagLen = sizeof(bishop->possibleMoves) / sizeof(bishop->possibleMoves[0]);
    int killLen = sizeof(bishop->killingMoves) / sizeof(bishop->killingMoves[0]);

    memcpy(bishop->possibleMoves, resetMoves(bishop->possibleMoves, diagLen), sizeof(bishop->possibleMoves));
    memcpy(bishop->killingMoves, resetMoves(bishop->killingMoves, killLen), sizeof(bishop->killingMoves));

    for(int i = 0; i < MAX_BISHOP_KILL_SQUARES; i++){
        int coordIdx = getCoordIdxByBoardPosition(bishop->pce->currentSquare);

        int lineMoves[NUM_LINES][MAX_LINE];

        memcpy(lineMoves, diagonals[coordIdx], sizeof(lineMoves));

        for(int i = 0; i < NUM_LINES; i++){
            int lineCoords[MAX_LINE];

            memcpy(lineCoords, lineMoves[i], sizeof(lineCoords));

            if(!isEmptyArray(lineCoords, MAX_LINE)){
                for(int j = 0; j < MAX_LINE; j++){
                    if(lineCoords[j] == INV){
                        break;
                    }
                    else{
                        bishop->possibleMoves[getFirstAvailableIndex(bishop->possibleMoves, diagLen)] = coordsToIdx[lineCoords[j]];
                    }            
                }
            }
            else{
                continue;
            }
        }
    }
}

void writeDefaultRookMoves(struct Rook * rook, int mode){
    // Write the horizontal and vertical moves from the rook move reference array.
    int linesLen = sizeof(rook->possibleMoves) / sizeof(rook->possibleMoves[0]);
    int killLen = sizeof(rook->killingMoves) / sizeof(rook->killingMoves[0]);

    memcpy(rook->possibleMoves, resetMoves(rook->possibleMoves, linesLen), sizeof(rook->possibleMoves));
    memcpy(rook->killingMoves, resetMoves(rook->killingMoves, killLen), sizeof(rook->killingMoves));

    for(int i = 0; i < MAX_ROOK_KILL_SQUARES; i++){
        int coordIdx = getCoordIdxByBoardPosition(rook->pce->currentSquare);

        int lineMoves[NUM_LINES][MAX_LINE];

        memcpy(lineMoves, horizontalsAndVerticals[coordIdx], sizeof(lineMoves));

        for(int i = 0; i < NUM_LINES; i++){
            int lineCoords[MAX_LINE];

            memcpy(lineCoords, lineMoves[i], sizeof(lineCoords));

            if(isEmptyArray(lineCoords, MAX_LINE)){
                for(int j = 0; j < MAX_LINE; j++){
                    if(lineCoords[j] == INV){
                        break;
                    }
                    else{
                        rook->possibleMoves[getFirstAvailableIndex(rook->possibleMoves, linesLen)] = coordsToIdx[lineCoords[j]];
                    }            
                }
            }
            else{
                continue;
            }
        }
    }
}

void writeDefaultQueenMoves(struct Queen * queen, int mode){
    int linesLen = sizeof(queen->moves->horizontalVerticalMoves) / sizeof(queen->moves->horizontalVerticalMoves[0]);
    int diagLen = sizeof(queen->moves->diagonalMoves) / sizeof(queen->moves->diagonalMoves[0]);
    int killLen = sizeof(queen->moves->killingMoves) / sizeof(queen->moves->killingMoves[0]);

    // Reset the movement arrays.
    memcpy(queen->moves->horizontalVerticalMoves, resetMoves(queen->moves->horizontalVerticalMoves, linesLen), sizeof(queen->moves->horizontalVerticalMoves));
    memcpy(queen->moves->diagonalMoves, resetMoves(queen->moves->diagonalMoves, diagLen), sizeof(queen->moves->diagonalMoves));
    memcpy(queen->moves->killingMoves, resetMoves(queen->moves->killingMoves, killLen), sizeof(queen->moves->killingMoves));

    if(mode == PLAYER_TURN){
        queen->pce->currentSquare = coordsToIdx[D8];
    }
    else if(mode == ENEMY_TURN){
        queen->pce->currentSquare = coordsToIdx[D1];
    }

    // Write the horizontal and vertical moves from the rook move reference array.
    for(int i = 0; i < MAX_ROOK_KILL_SQUARES; i++){
        int coordIdx = getCoordIdxByBoardPosition(queen->pce->currentSquare);
        int lineMoves[NUM_LINES][MAX_LINE];

        memcpy(lineMoves, horizontalsAndVerticals[coordIdx], sizeof(lineMoves));

        for(int i = 0; i < NUM_LINES; i++){
            int lineCoords[MAX_LINE];

            memcpy(lineCoords, lineMoves[i], sizeof(lineCoords));

            if(isEmptyArray(lineCoords, MAX_LINE)){
                for(int j = 0; j < MAX_LINE; j++){
                    if(lineCoords[j] == INV){
                        break;
                    }
                    else{
                        int availIdx = getFirstAvailableIndex(queen->moves->horizontalVerticalMoves, linesLen);

                        if(availIdx != INV){
                            queen->moves->horizontalVerticalMoves[getFirstAvailableIndex(queen->moves->horizontalVerticalMoves, linesLen)] = coordsToIdx[lineCoords[j]];
                        }
                    }            
                }
            }
            else{
                continue;
            }
        }
    }    

    // Write the diagonal moves from the bishop move reference array.
    for(int i = 0; i < MAX_BISHOP_KILL_SQUARES; i++){
        int coordIdx = getCoordIdxByBoardPosition(queen->pce->currentSquare);

        int lineMoves[NUM_LINES][MAX_LINE];

        memcpy(lineMoves, diagonals[coordIdx], sizeof(lineMoves));

        for(int i = 0; i < NUM_LINES; i++){
            int lineCoords[MAX_LINE];

            memcpy(lineCoords, lineMoves[i], sizeof(lineCoords));

            if(isEmptyArray(lineCoords, MAX_LINE)){
                for(int j = 0; j < MAX_LINE; j++){
                    if(lineCoords[j] == INV){
                        break;
                    }
                    else{
                        queen->moves->diagonalMoves[getFirstAvailableIndex(queen->moves->diagonalMoves, diagLen)] = coordsToIdx[lineCoords[j]];
                    }            
                }
            }
            else{
                continue;
            }
        }
    }
}

void writeDefaultKingMoves(struct King * king, int mode){
    if(mode == PLAYER_TURN){
        king->pce->currentSquare = coordsToIdx[E8];
    }
    else if(mode == ENEMY_TURN){
        king->pce->currentSquare = coordsToIdx[E1];
    }
    
    memcpy(king->possibleMoves, kingMoves[getCoordIdxByBoardPosition(king->pce->currentSquare)], sizeof(king->possibleMoves));
}

struct ChessPiece * initChessPiece(struct ChessPiece * pce){
    pce = (struct ChessPiece *) malloc(sizeof(struct ChessPiece));

    if(pce != NULL){
        pce->isAlive = true;
        pce->identity = '-';
        strcpy(pce->name, "None");
        pce->pieceWeight = INV;
        pce->currentSquare = UNOCCUPIED;
        return pce;
    }
    else{
        return NULL;
    }
}

struct Pawn * initPawn(struct Pawn * pawn, int mode){
    pawn = (struct Pawn *) malloc(sizeof(struct Pawn));

    if(pawn != NULL){
        pawn->pce = initChessPiece(pawn->pce);
        pawn->pce->identity = 'P';
        strcpy(pawn->pce->name, "Pawn");
        pawn->pce->pieceWeight = Pawn;
        
        return pawn;
    }
    else{
        return NULL;
    }

}

struct Rook * initRook(struct Rook * rook, int mode){
    rook = (struct Rook *) malloc(sizeof(struct Rook));

    if(rook != NULL){
        rook->pce = initChessPiece(rook->pce);
        rook->pce->identity = 'R';
        strcpy(rook->pce->name, "Rook");
        rook->pce->pieceWeight = Rook;
        return rook;
    }
    else{
        return NULL;
    }
}

struct Knight * initKnight(struct Knight * knight){
    knight = (struct Knight *) malloc(sizeof(struct Knight));

    if(knight != NULL){
        knight->pce = initChessPiece(knight->pce);
        knight->pce->identity = 'H';
        strcpy(knight->pce->name, "Knight");
        knight->pce->pieceWeight = Knight;
        return knight;
    }
    else{
        return NULL;
    }
}

struct Bishop * initBishop(struct Bishop * bishop){
    bishop = (struct Bishop *) malloc(sizeof(struct Bishop));

    if(bishop != NULL){
        bishop->pce = initChessPiece(bishop->pce);
        bishop->pce->identity = 'B';
        strcpy(bishop->pce->name, "Bishop");
        bishop->pce->pieceWeight = Bishop;
        return bishop;
    }
    else{
        return NULL;
    }
}

struct Pawn ** initPawns(struct Pawn * pawns[NUM_PAWNS], int mode){
    for(int i = 0; i < NUM_PAWNS; i++){
        pawns[i] = initPawn(pawns[i], mode);
    }

    if(mode == PLAYER_TURN){
        pawns = writeDefaultHumanPawnMoves(pawns);
    }
    else if(mode == ENEMY_TURN){
        pawns = writeDefaultComputerPawnMoves(pawns);
    }

    return pawns;
}

struct Rook ** initRooks(struct Rook * rooks[MAX_POSSIBLE_ROOKS], int mode){
    for(int i = 0; i < MAX_POSSIBLE_ROOKS; i++){
        if(i == 0){
            if(mode == PLAYER_TURN){
                rooks[i] = initRook(rooks[i], mode);
                rooks[i]->pce->currentSquare = coordsToIdx[A1];
            }
            else if(mode == ENEMY_TURN){
                rooks[i] = initRook(rooks[i], mode);
                rooks[i]->pce->currentSquare = coordsToIdx[H1];
            }
        }
        else if(i == 1){
            if(mode == PLAYER_TURN){
                rooks[i] = initRook(rooks[i], mode);
                rooks[i]->pce->currentSquare = coordsToIdx[A8];
            }
            else if(mode == ENEMY_TURN){
                rooks[i] = initRook(rooks[i], mode);
                rooks[i]->pce->currentSquare = coordsToIdx[H8];
            }
        }
        else{
            rooks[i] = NULL;
        }
    }

    return rooks;
}

struct Knight ** initKnights(struct Knight * knights[MAX_POSSIBLE_KNIGHTS], int mode){
    for(int i = 0; i < MAX_POSSIBLE_KNIGHTS; i++){
        if(i == 0){
            if(mode == PLAYER_TURN){
                knights[i] = initKnight(knights[i]);
                knights[i]->pce->currentSquare = coordsToIdx[B8];
            }
            else if(mode == ENEMY_TURN){
                knights[i] = initKnight(knights[i]);
                knights[i]->pce->currentSquare = coordsToIdx[B1];
            }
            else{
                knights[i] = NULL;
            }
        }
        else if(i == 1){
            if(mode == PLAYER_TURN){
                knights[i] = initKnight(knights[i]);
                knights[i]->pce->currentSquare = coordsToIdx[G8];
            }
            else if(mode == ENEMY_TURN){
                knights[i] = initKnight(knights[i]);
                knights[i]->pce->currentSquare = coordsToIdx[G1];
            }
            else{
                knights[i] = NULL;
            }
        }
        else{
            knights[i] = NULL;
        }
    }

    return knights;
}

struct Bishop ** initBishops(struct Bishop * bishops[MAX_POSSIBLE_BISHOPS], int mode){
    for(int i = 0; i < MAX_POSSIBLE_KNIGHTS; i++){
        if(i == 0){
            if(mode == PLAYER_TURN){
                bishops[i] = initBishop(bishops[i]);
                bishops[i]->pce->currentSquare = coordsToIdx[C8];
            }
            else if(mode == ENEMY_TURN){
                bishops[i] = initBishop(bishops[i]);
                bishops[i]->pce->currentSquare = coordsToIdx[F1];
            }
            else{
                bishops[i] = NULL;
            }
        }
        else if(i == 1){
            if(mode == PLAYER_TURN){
                bishops[i] = initBishop(bishops[i]);
                bishops[i]->pce->currentSquare = coordsToIdx[C8];
            }
            else if(mode == ENEMY_TURN){
                bishops[i] = initBishop(bishops[i]);
                bishops[i]->pce->currentSquare = coordsToIdx[F1];
            }
            else{
                bishops[i] = NULL;
            }
        }
        else{
            bishops[i] = NULL;
        }
    }

    return bishops;
}

struct QueenMoves * initQueenMoves(struct QueenMoves * moves){
    moves = (struct QueenMoves *) malloc(sizeof(struct QueenMoves));
    int defaultLines[MAX_ROOK_POSSIBLE_MOVES] = { INV, INV, INV, INV, INV, INV, INV, INV, INV, INV, INV, INV, INV, INV };
    int defaultDiagonals[MAX_BISHOP_POSSIBLE_MOVES] = { INV, INV, INV, INV, INV, INV, INV, INV, INV, INV, INV, INV, INV };
    int defaultKills[MAX_QUEEN_KILL_SQUARES] = { INV, INV, INV, INV, INV, INV, INV, INV };

    if(moves != NULL){
        memcpy(moves->horizontalVerticalMoves, defaultLines, sizeof(moves->horizontalVerticalMoves));
        memcpy(moves->diagonalMoves, defaultDiagonals, sizeof(moves->diagonalMoves));
        memcpy(moves->killingMoves, defaultKills, sizeof(moves->killingMoves));
        return moves;
    }
    else{
        return NULL;
    }
}

struct Queen * initQueen(struct Queen * queen, int mode){
    queen = (struct Queen *) malloc(sizeof(struct Queen));

    if(queen != NULL){
        queen->pce = initChessPiece(queen->pce);
        queen->moves = initQueenMoves(queen->moves);
        queen->pce->identity = 'Q';
        strcpy(queen->pce->name, "Queen");
        queen->pce->pieceWeight = Queen;
        writeDefaultQueenMoves(queen, mode);
        return queen;
    }
    else{
        return NULL;
    }
}

struct Queen ** initQueens(struct Queen * queens[], int mode){
    for(int i = 0; i < MAX_POSSIBLE_QUEENS; i++){
        if(i == 0){
            if(mode == PLAYER_TURN){
                queens[i] = initQueen(queens[i], mode);
                queens[i]->pce->currentSquare = coordsToIdx[D8];
            }
            else if(mode == ENEMY_TURN){
                queens[i] = initQueen(queens[i], mode);
                queens[i]->pce->currentSquare = coordsToIdx[D1];
            }
            else{
                queens[i] = initQueen(queens[i], mode);
            }
        }
        else{
            queens[i] = NULL;
        }
    }

    return queens;
}

struct King * initKing(struct King * king, int mode){
    king = (struct King *) malloc(sizeof(struct King));

    if(king != NULL){
        king->pce = initChessPiece(king->pce);
        king->pce->identity = 'K';
        strcpy(king->pce->name, "King");
        king->pce->pieceWeight = King;
        writeDefaultKingMoves(king, mode);
        return king;
    }
    else{
        return NULL;
    }
}

struct Army * initArmy(struct Army * army, int mode){
    army = (struct Army *) malloc(sizeof(struct Army));

    if(army != NULL){
        memcpy(army->pawns, initPawns(army->pawns, mode), sizeof(army->pawns));
        memcpy(army->rooks, initRooks(army->rooks, mode), sizeof(army->rooks));
        memcpy(army->knights, initKnights(army->knights, mode), sizeof(army->knights));
        memcpy(army->bishops, initBishops(army->bishops, mode), sizeof(army->bishops));
        memcpy(army->queens, initQueens(army->queens, mode), sizeof(army->queens));
        army->king = initKing(army->king, mode);
        return army;
    }
    else{
        return NULL;
    }
}

struct Player * initPlayer(struct Player * player, int mode){
    player = (struct Player *) malloc(sizeof(struct Player));

    if(player != NULL){
        player->army = initArmy(player->army, mode);
        strcpy(player->name, "None");
        return player;
    }
    else{
        return NULL;
    }
}

void writeInitEnemyPositions(struct Player * computer){
    // Write Pawns to board.
    for(int i = 0; i < NUM_PAWNS; i++){
        switch(i){
            case 0:
                computer->army->pawns[i]->pce->currentSquare = coordsToIdx[A2];
                chessBoard[coordsToIdx[A2]] = computer->army->pawns[i]->pce->identity;
                memcpy(computer->army->pawns[i]->possibleMoves, computerPawnMoves[0], sizeof(computer->army->pawns[i]->possibleMoves));
                break;
            case 1:
                computer->army->pawns[i]->pce->currentSquare = coordsToIdx[B2];
                chessBoard[coordsToIdx[B2]] = computer->army->pawns[i]->pce->identity;
                memcpy(computer->army->pawns[i]->possibleMoves, computerPawnMoves[1], sizeof(computer->army->pawns[i]->possibleMoves));
                break;
            case 2:
                computer->army->pawns[i]->pce->currentSquare = coordsToIdx[C2];
                chessBoard[coordsToIdx[C2]] = computer->army->pawns[i]->pce->identity;
                memcpy(computer->army->pawns[i]->possibleMoves, computerPawnMoves[2], sizeof(computer->army->pawns[i]->possibleMoves));
                break;
            case 3:
                computer->army->pawns[i]->pce->currentSquare = coordsToIdx[D2];
                chessBoard[coordsToIdx[D2]] = computer->army->pawns[i]->pce->identity;
                memcpy(computer->army->pawns[i]->possibleMoves, computerPawnMoves[3], sizeof(computer->army->pawns[i]->possibleMoves));
                break;
            case 4:
                computer->army->pawns[i]->pce->currentSquare = coordsToIdx[E2];
                chessBoard[coordsToIdx[E2]] = computer->army->pawns[i]->pce->identity;
                memcpy(computer->army->pawns[i]->possibleMoves, computerPawnMoves[4], sizeof(computer->army->pawns[i]->possibleMoves));
                break;
            case 5:
                computer->army->pawns[i]->pce->currentSquare = coordsToIdx[F2];
                chessBoard[coordsToIdx[F2]] = computer->army->pawns[i]->pce->identity;
                memcpy(computer->army->pawns[i]->possibleMoves, computerPawnMoves[5], sizeof(computer->army->pawns[i]->possibleMoves));
                break;
            case 6:
                computer->army->pawns[i]->pce->currentSquare = coordsToIdx[G2];
                chessBoard[coordsToIdx[G2]] = computer->army->pawns[i]->pce->identity;
                memcpy(computer->army->pawns[i]->possibleMoves, computerPawnMoves[6], sizeof(computer->army->pawns[i]->possibleMoves));
                break;
            case 7:
                computer->army->pawns[i]->pce->currentSquare = coordsToIdx[H2];
                chessBoard[coordsToIdx[H2]] = computer->army->pawns[i]->pce->identity;
                memcpy(computer->army->pawns[i]->possibleMoves, computerPawnMoves[7], sizeof(computer->army->pawns[i]->possibleMoves));
                break;
        }
    }

    //Write Rooks to board.
    for(int i = 0; i < NUM_ROOKS; i++){
        if(i == 0){
            computer->army->rooks[i]->pce->currentSquare = coordsToIdx[A1];
            chessBoard[coordsToIdx[A1]] = computer->army->rooks[i]->pce->identity;
            memcpy(computer->army->rooks[i]->possibleMoves, horizontalsAndVerticals[A1], sizeof(computer->army->rooks[i]->possibleMoves));
        }
        else{
            computer->army->rooks[i]->pce->currentSquare = coordsToIdx[H1];
            chessBoard[coordsToIdx[H1]] = computer->army->rooks[i]->pce->identity;
            memcpy(computer->army->rooks[i]->possibleMoves, horizontalsAndVerticals[H1], sizeof(computer->army->rooks[i]->possibleMoves));
        }
    }

    // Write Knights to board.
    for(int i = 0; i < NUM_KNIGHTS; i++){
        if(i == 0){
            computer->army->knights[i]->pce->currentSquare = coordsToIdx[B1];
            chessBoard[coordsToIdx[B1]] = computer->army->knights[i]->pce->identity;
            memcpy(computer->army->knights[i]->possibleMoves, knightMoves[B1], sizeof(computer->army->knights[i]->possibleMoves));
        }
        else{
            computer->army->knights[i]->pce->currentSquare = coordsToIdx[G1];
            chessBoard[coordsToIdx[G1]] = computer->army->knights[i]->pce->identity;
            memcpy(computer->army->knights[i]->possibleMoves, knightMoves[G1], sizeof(computer->army->knights[i]->possibleMoves));
        }
    }

    // Write Bishops to board.
    for(int i = 0; i < NUM_BISHOPS; i++){
        if(i == 0){
            computer->army->bishops[i]->pce->currentSquare = coordsToIdx[C1];
            chessBoard[coordsToIdx[C1]] = computer->army->bishops[i]->pce->identity;
            memcpy(computer->army->bishops[i]->possibleMoves, diagonals[C1], sizeof(computer->army->bishops[i]->possibleMoves));
        }
        else{
            computer->army->bishops[i]->pce->currentSquare = coordsToIdx[F1];
            chessBoard[coordsToIdx[F1]] = computer->army->bishops[i]->pce->identity;
            memcpy(computer->army->bishops[i]->possibleMoves, diagonals[F1], sizeof(computer->army->bishops[i]->possibleMoves));
        }
    }

    // Write Queen to board.
    computer->army->queens[0]->pce->currentSquare = coordsToIdx[D1];
    chessBoard[coordsToIdx[D1]] = computer->army->queens[0]->pce->identity;
    memcpy(computer->army->queens[0]->moves->horizontalVerticalMoves, horizontalsAndVerticals[D1], sizeof(computer->army->queens[0]->moves->horizontalVerticalMoves));
    memcpy(computer->army->queens[0]->moves->diagonalMoves, diagonals[D1], sizeof(computer->army->queens[0]->moves->diagonalMoves));

    // Write King to board.
    computer->army->king->pce->currentSquare = coordsToIdx[E1];
    chessBoard[coordsToIdx[E1]] = computer->army->king->pce->identity;
    memcpy(computer->army->king->possibleMoves, kingMoves[E1], sizeof(computer->army->king->possibleMoves));
}

void writeInitHumanPositions(struct Player * human){
    // Write Pawns to board.
    for(int i = 0; i < NUM_PAWNS; i++){
        switch(i){
            case 0:
                human->army->pawns[i]->pce->currentSquare = coordsToIdx[A7];
                chessBoard[coordsToIdx[A7]] = human->army->pawns[i]->pce->identity;
                memcpy(human->army->pawns[i]->possibleMoves, humanPawnMoves[40], sizeof(human->army->pawns[i]->possibleMoves));
                break;
            case 1:
                human->army->pawns[i]->pce->currentSquare = coordsToIdx[B7];
                chessBoard[coordsToIdx[B7]] = human->army->pawns[i]->pce->identity;
                memcpy(human->army->pawns[i]->possibleMoves, humanPawnMoves[41], sizeof(human->army->pawns[i]->possibleMoves));
                break;
            case 2:
                human->army->pawns[i]->pce->currentSquare = coordsToIdx[C7];
                chessBoard[coordsToIdx[C7]] = human->army->pawns[i]->pce->identity;
                memcpy(human->army->pawns[i]->possibleMoves, humanPawnMoves[42], sizeof(human->army->pawns[i]->possibleMoves));
                break;
            case 3:
                human->army->pawns[i]->pce->currentSquare = coordsToIdx[D7];
                chessBoard[coordsToIdx[D7]] = human->army->pawns[i]->pce->identity;
                memcpy(human->army->pawns[i]->possibleMoves, humanPawnMoves[43], sizeof(human->army->pawns[i]->possibleMoves));
                break;
            case 4:
                human->army->pawns[i]->pce->currentSquare = coordsToIdx[E7];
                chessBoard[coordsToIdx[E7]] = human->army->pawns[i]->pce->identity;
                memcpy(human->army->pawns[i]->possibleMoves, humanPawnMoves[44], sizeof(human->army->pawns[i]->possibleMoves));
                break;
            case 5:
                human->army->pawns[i]->pce->currentSquare = coordsToIdx[F7];
                chessBoard[coordsToIdx[F7]] = human->army->pawns[i]->pce->identity;
                memcpy(human->army->pawns[i]->possibleMoves, humanPawnMoves[45], sizeof(human->army->pawns[i]->possibleMoves));
                break;
            case 6:
                human->army->pawns[i]->pce->currentSquare = coordsToIdx[G7];
                chessBoard[coordsToIdx[G7]] = human->army->pawns[i]->pce->identity;
                memcpy(human->army->pawns[i]->possibleMoves, humanPawnMoves[46], sizeof(human->army->pawns[i]->possibleMoves));
                break;
            case 7:
                human->army->pawns[i]->pce->currentSquare = coordsToIdx[H7];
                chessBoard[coordsToIdx[H7]] = human->army->pawns[i]->pce->identity;
                memcpy(human->army->pawns[i]->possibleMoves, humanPawnMoves[47], sizeof(human->army->pawns[i]->possibleMoves));
                break;
        }
    }

    //Write Rooks to board.
    for(int i = 0; i < NUM_ROOKS; i++){
        if(i == 0){
            human->army->rooks[i]->pce->currentSquare = coordsToIdx[A8];
            chessBoard[coordsToIdx[A8]] = human->army->rooks[i]->pce->identity;
            memcpy(human->army->rooks[i]->possibleMoves, horizontalsAndVerticals[A8], sizeof(human->army->rooks[i]->possibleMoves));
        }
        else{
            human->army->rooks[i]->pce->currentSquare = coordsToIdx[H8];
            chessBoard[coordsToIdx[H8]] = human->army->rooks[i]->pce->identity;
            memcpy(human->army->rooks[i]->possibleMoves, horizontalsAndVerticals[H8], sizeof(human->army->rooks[i]->possibleMoves));
        }
    }

    // Write knights to board.
    for(int i = 0; i < NUM_KNIGHTS; i++){
        if(i == 0){
            human->army->knights[i]->pce->currentSquare = coordsToIdx[B8];
            chessBoard[coordsToIdx[B8]] = human->army->knights[i]->pce->identity;
            memcpy(human->army->knights[i]->possibleMoves, knightMoves[B8], sizeof(human->army->knights[i]->possibleMoves));
        }
        else{
            human->army->knights[i]->pce->currentSquare = coordsToIdx[G8];
            chessBoard[coordsToIdx[G8]] = human->army->knights[i]->pce->identity;
            memcpy(human->army->knights[i]->possibleMoves, knightMoves[G8], sizeof(human->army->knights[i]->possibleMoves));
        }
    }

    //Write bishops to board.
    for(int i = 0; i < NUM_BISHOPS; i++){
        if(i == 0){
            human->army->bishops[i]->pce->currentSquare = coordsToIdx[C8];
            chessBoard[coordsToIdx[C8]] = human->army->bishops[i]->pce->identity;
            memcpy(human->army->bishops[i]->possibleMoves, diagonals[C8], sizeof(human->army->bishops[i]->possibleMoves));
        }
        else{
            human->army->bishops[i]->pce->currentSquare = coordsToIdx[F8];
            chessBoard[coordsToIdx[F8]] = human->army->bishops[i]->pce->identity;
            memcpy(human->army->bishops[i]->possibleMoves, diagonals[F8], sizeof(human->army->bishops[i]->possibleMoves));
        }
    }

    //Write Queen to board.
    human->army->queens[0]->pce->currentSquare = coordsToIdx[D8];
    chessBoard[coordsToIdx[D8]] = human->army->queens[0]->pce->identity;
    memcpy(human->army->queens[0]->moves->horizontalVerticalMoves, horizontalsAndVerticals[D8], sizeof(human->army->king->possibleMoves));
    memcpy(human->army->queens[0]->moves->diagonalMoves, horizontalsAndVerticals[D8], sizeof(human->army->king->possibleMoves));

    //Write King to board.
    human->army->king->pce->currentSquare = coordsToIdx[E8];
    chessBoard[coordsToIdx[E8]] = human->army->king->pce->identity;
    memcpy(human->army->king->possibleMoves, kingMoves[E8], sizeof(human->army->king->possibleMoves));
}

// Populate the board with the initial player armies.
void initBoard(struct Player * human, struct Player * computer){
    // Set the colour for the computer army.
    computer->army->colour = White;
    // Write the computer's and human's pieces to the board.
    writeInitEnemyPositions(computer);
    writeInitHumanPositions(human);
}

// Gets the army colour occupying the space and returns it. If a army doesn't occupy that space, -1 is returned.
int getOccupyingArmyColour(struct Player * human, struct Player * computer, int currentSquare){
    // Check Pawns.
    for(int i = 0; i < NUM_PAWNS; i++){
        if(currentSquare == human->army->pawns[i]->pce->currentSquare){
            return human->army->colour;
        }
        else if(currentSquare == computer->army->pawns[i]->pce->currentSquare){
            return computer->army->colour;
        }
    }

    // Check Rooks.
    for(int i = 0; i < NUM_ROOKS; i++){
        if(currentSquare == human->army->rooks[i]->pce->currentSquare){
            return human->army->colour;
        }
        else if(currentSquare == computer->army->rooks[i]->pce->currentSquare){
            return computer->army->colour;
        }
    }

    // Check Knights.
    for(int i = 0; i < NUM_KNIGHTS; i++){
        if(currentSquare == human->army->knights[i]->pce->currentSquare){
            return human->army->colour;
        }
        else if(currentSquare == computer->army->knights[i]->pce->currentSquare){
            return computer->army->colour;
        }
    }

    // Check Bishops.
    for(int i = 0; i < NUM_BISHOPS; i++){
        if(currentSquare == human->army->bishops[i]->pce->currentSquare){
            return human->army->colour;
        }
        else if(currentSquare == computer->army->bishops[i]->pce->currentSquare){
            return computer->army->colour;
        }
    }

    // Check Queens.
    if(currentSquare == human->army->queens[0]->pce->currentSquare){
        return human->army->colour;
    }
    else if(currentSquare == computer->army->queens[0]->pce->currentSquare){
        return computer->army->colour;
    }

    // Check Kings.
    if(currentSquare == human->army->king->pce->currentSquare){
        return human->army->colour;
    }
    else if(currentSquare == computer->army->king->pce->currentSquare){
        return computer->army->colour;
    }

    // Square unoccupied. Return.
    return UNOCCUPIED;
}

bool isBoardPosCrosshair(int pos){
    for(int i = 0; i < MAX_SQUARES; i++){
        for(int j = 0; j < CORNERS; j++){
            if(crosshairCoords[i][j] == pos){
                return true;
            }
        }
    }

    return false;
}

// Prints the current board's state as well as the correct colour of each player's army.
void printChessBoard(struct Player * human, struct Player * computer){
    int boardChars = strlen(chessBoard);

    for(int i = 0; i < boardChars; i++){
        // Determine if the square is occupied by an army, if so, return what one.
        int occupied = getOccupyingArmyColour(human, computer, i);

        switch(occupied){
            case Green:
                setGreenPrint();
                break;
            case Cyan:
                setCyanPrint();
                break;
            case Blue:
                setBluePrint();
                break;
            case Red:
                setRedPrint();
                break;
            case Yellow:
                setYellowPrint();
                break;
            case Purple:
                setPurplePrint();
                break;
            case Black:
                setBlackPrint();
                break;
            case White:
                setWhitePrint();
                break;
            case UNOCCUPIED:
                resetPrintColour();
                break;
        }

        printf("%c", chessBoard[i]);
    }
}

int getTurn(int turn){
    if((turn % 2) == 0){
        return PLAYER_TURN;
    }
    else{
        return ENEMY_TURN;
    }
}

bool isValidCoordinate(char coord[5]){
    for(int i = 0; i < MAX_SQUARES; i++){
        if(strcmp(coord, coordStrs[i]) == EQUAL_STRINGS){
            return true;
        }
    }

    return false;
}

bool isValidDestination(int destSquare, struct Player * movingPlayer){
    return true;
}

int coordToBoardPosition(char coord[COORD_LEN]){
    for(int i = 0; i < MAX_SQUARES; i++){
        if(strcmp(coord, coordStrs[i]) == EQUAL_STRINGS){
            return coordsToIdx[i];
        }
    }

    return INV;
}

int boardPositionToCoord(int boardPos){
    for(int i = 0; i < MAX_SQUARES; i++){
        if(coordsToIdx[i] == boardPos){
            return i;
        }
    }

    return INV;
}

char * getPieceNameByIdx(struct Player * player, int boardIdx){
    // Loop through each set of pieces and return the name of the piece if it resides at the board index.
    for(int i = 0; i < NUM_PAWNS; i++){
        if(player->army->pawns[i] != NULL){
            if(player->army->pawns[i]->pce->isAlive){
                if(player->army->pawns[i]->pce->currentSquare == boardIdx){
                    return player->army->pawns[i]->pce->name;
                }
            }
        }
    }

    for(int i = 0; i < MAX_POSSIBLE_ROOKS; i++){
        if(player->army->rooks[i] != NULL){
            if(player->army->rooks[i]->pce->isAlive){
                if(player->army->rooks[i]->pce->currentSquare == boardIdx){
                    return player->army->rooks[i]->pce->name;
                }
            }
        }

    }
        
    for(int i = 0; i < MAX_POSSIBLE_BISHOPS; i++){
        if(player->army->bishops[i] != NULL){
            if(player->army->bishops[i]->pce->isAlive){
                if(player->army->bishops[i]->pce->currentSquare == boardIdx){
                    return player->army->bishops[i]->pce->name;
                }
            }
        }
    }
    
    for(int i = 0; i < MAX_POSSIBLE_KNIGHTS; i++){
        if(player->army->knights[i] != NULL){    
            if(player->army->knights[i]->pce->isAlive){
                if(player->army->knights[i]->pce->currentSquare == boardIdx){
                    return player->army->knights[i]->pce->name;
                }
            }
        }
    }

    for(int i = 0; i < MAX_POSSIBLE_QUEENS; i++){
        if(player->army->queens[i] != NULL){    
            if(player->army->queens[i]->pce->isAlive){
                if(player->army->queens[i]->pce->currentSquare == boardIdx){
                    return player->army->queens[i]->pce->name;
                }
            }
        }
    }

    if(player->army->king->pce->isAlive){
        if(player->army->king->pce->currentSquare == boardIdx){
            return player->army->king->pce->name;
        }
    }

    return "Not Found";
}

struct Pawn * getPawnByBoardPosition(struct Player * player, int boardIdx){
    for(int i = 0; i < NUM_PAWNS; i++){
        if(player->army->pawns[i]->pce->isAlive){
            if(player->army->pawns[i]->pce->currentSquare == boardIdx){
                return player->army->pawns[i];
            }
        }
    }

    return NULL;
}

struct Pawn * getPawnByPossibleMove(struct Player * player, int possibleMove){
    for(int i = 0; i < NUM_PAWNS; i++){
        int size = sizeof(player->army->pawns[i]->possibleMoves) / sizeof(player->army->pawns[i]->possibleMoves[0]);

        for(int j = 0; j < size; j++){
            if(coordsToIdx[player->army->pawns[i]->possibleMoves[j]] == possibleMove){
                return player->army->pawns[i];
            }    
        }
    }
    
    return NULL;
}

struct Rook * getRookByBoardPosition(struct Player * player, int boardIdx){
    for(int i = 0; i < MAX_POSSIBLE_ROOKS; i++){
        if(player->army->rooks[i]->pce->isAlive){
            if(player->army->rooks[i]->pce->currentSquare == boardIdx){
                return player->army->rooks[i];
            }
        }
    }

    return NULL;
}

struct Rook * getRookByPossibleMove(struct Player * player, int possibleMove){
    for(int i = 0; i < MAX_POSSIBLE_ROOKS; i++){
        if(player->army->rooks[i] != NULL){
            int size = sizeof(player->army->rooks[i]->possibleMoves) / sizeof(player->army->rooks[i]->possibleMoves[0]);

            for(int j = 0; j < size; j++){
                if(coordsToIdx[player->army->rooks[i]->possibleMoves[j]] == possibleMove){
                    return player->army->rooks[i];
                }    
            }
        }
    }
    
    return NULL;
}

struct Knight * getKnightByBoardPosition(struct Player * player, int boardIdx){
    for(int i = 0; i < MAX_POSSIBLE_KNIGHTS; i++){
        if(player->army->knights[i]->pce->isAlive){
            if(player->army->knights[i]->pce->currentSquare == boardIdx){
                return player->army->knights[i];
            }
        }
    }

    return NULL;
}

struct Knight * getKnightByPossibleMove(struct Player * player, int possibleMove){
    for(int i = 0; i < MAX_POSSIBLE_KNIGHTS; i++){
        if(player->army->knights[i] != NULL){
            int size = sizeof(player->army->knights[i]->possibleMoves) / sizeof(player->army->knights[i]->possibleMoves[0]);

            for(int j = 0; j < size; j++){
                if(coordsToIdx[player->army->knights[i]->possibleMoves[j]] == possibleMove){
                    return player->army->knights[i];
                }    
            }
        }
    }
    
    return NULL;
}

struct Bishop * getBishopByBoardPosition(struct Player * player, int boardIdx){
    for(int i = 0; i < MAX_POSSIBLE_BISHOPS; i++){
        if(player->army->bishops[i]->pce->isAlive){
            if(player->army->bishops[i]->pce->currentSquare == boardIdx){
                return player->army->bishops[i];
            }
        }
    }

    return NULL;
}

struct Queen * getQueenByBoardPosition(struct Player * player, int boardIdx){
    for(int i = 0; i < MAX_POSSIBLE_QUEENS; i++){
        if(player->army->queens[i]->pce->isAlive){
            if(player->army->queens[i]->pce->currentSquare == boardIdx){
                return player->army->queens[i];
            }
        }
    }
    
    return NULL;
}

struct Bishop * getBishopByPossibleMove(struct Player * player, int possibleMove){
    for(int i = 0; i < MAX_POSSIBLE_ROOKS; i++){
        if(player->army->bishops[i] != NULL){
            int size = sizeof(player->army->bishops[i]->possibleMoves) / sizeof(player->army->bishops[i]->possibleMoves[0]);

            for(int j = 0; j < size; j++){
                if(coordsToIdx[player->army->bishops[i]->possibleMoves[j]] == possibleMove){
                    return player->army->bishops[i];
                }    
            }
        }
    }
    
    return NULL;
}

struct King * getKing(struct Player * player){
    return player->army->king;
}

struct Queen * getQueenByPossibleMove(struct Player * player, int possibleMove){
    for(int i = 0; i < MAX_POSSIBLE_QUEENS; i++){
        if(player->army->queens[i] != NULL){
            int hSize = sizeof(player->army->queens[i]->moves->horizontalVerticalMoves) / sizeof(player->army->queens[i]->moves->horizontalVerticalMoves[0]);
            int dSize = sizeof(player->army->queens[i]->moves->diagonalMoves) / sizeof(player->army->queens[i]->moves->diagonalMoves[0]);

            for(int j = 0; j < hSize; j++){
                if(coordsToIdx[player->army->queens[i]->moves->horizontalVerticalMoves[j]] == possibleMove){
                    return player->army->queens[i];
                }    
            }

            for(int k = 0; k < dSize; k++){
                if(coordsToIdx[player->army->queens[i]->moves->diagonalMoves[k]] == possibleMove){
                    return player->army->queens[i];
                }    
            }
        }
    }
    
    return NULL;
}

void updateHumanPawnMoves(struct Player * human, struct Player * computer, struct Pawn * pawn){
    for(int i = 0; i < NUM_PAWN_MOVE_TYPES; i++){
        printf("i: %d\n", pawn->possibleMoves[i]);

        if(pawn->possibleMoves[i] != INV){
            int occupied = getOccupyingArmyColour(human, computer, chessBoard[coordsToIdx[pawn->possibleMoves[i]]]);

            if(i == 0){ // Ergo, checking the regular move.
                if(occupied != UNOCCUPIED){ // The square is occupied, and therefore invalid so update the array.
                    pawn->possibleMoves[i] = INV;
                }
            }
            else{
                if(occupied == UNOCCUPIED){
                    pawn->possibleMoves[i] = INV;
                }
                else if(occupied != computer->army->colour){
                    pawn->possibleMoves[i] = INV;
                }
                else{
                    int length = sizeof(pawn->killingMoves) / sizeof(pawn->killingMoves[0]);
                    pawn->killingMoves[getFirstAvailableIndex(pawn->killingMoves, length)] = pawn->possibleMoves[i];
                }
            }
        }
    }
}

void updateComputerPawnMoves(struct Player * human, struct Player * computer, struct Pawn * pawn){
    for(int i = 0; i < NUM_PAWN_MOVE_TYPES; i++){
        int occupied = getOccupyingArmyColour(human, computer, chessBoard[coordsToIdx[pawn->possibleMoves[i]]]);

        if(i == 0){ // Ergo, checking the regular move.
            if(occupied != UNOCCUPIED){ // The square is occupied, and therefore invalid so update the array.
                pawn->possibleMoves[i] = INV;
            }
        }
        else{
            if(occupied == UNOCCUPIED){
                pawn->possibleMoves[i] = INV;
            }
            else if(occupied != human->army->colour){
                pawn->possibleMoves[i] = INV;
            }
            else{
                int length = sizeof(pawn->killingMoves) / sizeof(pawn->killingMoves[0]);
                pawn->killingMoves[getFirstAvailableIndex(pawn->killingMoves, length)] = pawn->possibleMoves[i];
            }
        }
    }
}

void updateKnightMoves(struct Player * movingPlayer, struct Player * defendingPlayer, struct Knight * knight){
    for(int i = 0; i < MAX_KNIGHT_KILL_SQUARES; i++){
        int occupied = getOccupyingArmyColour(movingPlayer, defendingPlayer, chessBoard[coordsToIdx[knight->possibleMoves[i]]]);

        if(occupied == movingPlayer->army->colour){
            knight->possibleMoves[i] = INV;
        }
        else if(occupied == defendingPlayer->army->colour){
            int length = sizeof(knight->killingMoves) / sizeof(knight->killingMoves[0]);
            knight->killingMoves[getFirstAvailableIndex(knight->killingMoves, length)] = knight->possibleMoves[i];
        }
    }
}

void updateRookMoves(struct Player * movingPlayer, struct Player * defendingPlayer, struct Rook * rook){
    for(int i = 0; i < MAX_ROOK_KILL_SQUARES; i++){
        int coordIdx = getCoordIdxByBoardPosition(rook->pce->currentSquare);

        int lineMoves[NUM_LINES][MAX_LINE];

        memcpy(lineMoves, horizontalsAndVerticals[coordIdx], sizeof(lineMoves));

        for(int i = 0; i < NUM_LINES; i++){
            int lineCoords[MAX_LINE];

            memcpy(lineCoords, lineMoves[i], sizeof(lineCoords));

            if(isEmptyArray(lineCoords, MAX_LINE)){
                for(int j = 0; j < MAX_LINE; j++){
                    if(lineCoords[j] == INV){
                        break;
                    }
                    else{
                        int squareOccupied = getOccupyingArmyColour(movingPlayer, defendingPlayer, chessBoard[coordsToIdx[lineCoords[j]]]);

                        if(squareOccupied != UNOCCUPIED){
                            if(squareOccupied == defendingPlayer->army->colour){
                                int possibleLen = sizeof(rook->possibleMoves) / sizeof(rook->possibleMoves[0]);
                                int killingLen = sizeof(rook->killingMoves) / sizeof(rook->killingMoves[0]);

                                rook->possibleMoves[getFirstAvailableIndex(rook->possibleMoves, possibleLen)] = coordsToIdx[lineCoords[j]];
                                rook->killingMoves[getFirstAvailableIndex(rook->killingMoves, killingLen)] = coordsToIdx[lineCoords[j]]; 
                            }
                        }
                    }            
                }
            }
            else{
                continue;
            }
        }
    }
}

void updateBishopMoves(struct Player * movingPlayer, struct Player * defendingPlayer, struct Bishop * bishop){
    for(int i = 0; i < MAX_BISHOP_KILL_SQUARES; i++){
        //int occupied = getOccupyingArmyColour(movingPlayer, defendingPlayer, chessBoard[coordsToIdx[bishop->possibleMoves[i]]]);
        int coordIdx = getCoordIdxByBoardPosition(bishop->pce->currentSquare);

        int diagonalMoves[NUM_LINES][MAX_LINE];

        memcpy(diagonalMoves, diagonals[coordIdx], sizeof(diagonalMoves));

        for(int i = 0; i < NUM_LINES; i++){
            int diagonalCoords[MAX_LINE];

            memcpy(diagonalCoords, diagonalMoves[i], sizeof(diagonalCoords));

            if(isEmptyArray(diagonalCoords, MAX_LINE)){
                for(int j = 0; j < MAX_LINE; j++){
                    if(diagonalCoords[j] == INV){
                        break;
                    }
                    else{
                        int squareOccupied = getOccupyingArmyColour(movingPlayer, defendingPlayer, chessBoard[coordsToIdx[diagonalCoords[j]]]);

                        if(squareOccupied != UNOCCUPIED){
                            if(squareOccupied == defendingPlayer->army->colour){
                                int possibleLen = sizeof(bishop->possibleMoves) / sizeof(bishop->possibleMoves[0]);
                                int killingLen = sizeof(bishop->killingMoves) / sizeof(bishop->killingMoves[0]);

                                bishop->possibleMoves[getFirstAvailableIndex(bishop->possibleMoves, possibleLen)] = coordsToIdx[diagonalCoords[j]];
                                bishop->killingMoves[getFirstAvailableIndex(bishop->killingMoves, killingLen)] = coordsToIdx[diagonalCoords[j]]; 
                            }
                        }
                    }            
                }
            }
            else{
                continue;
            }
        }
    }
}

void updateQueenMoves(struct Player * movingPlayer, struct Player * defendingPlayer, struct Queen * queen){ 
    // Horizontal and Verticals updates.
    for(int i = 0; i < MAX_ROOK_KILL_SQUARES; i++){
        int coordIdx = getCoordIdxByBoardPosition(queen->pce->currentSquare);

        int lineMoves[NUM_LINES][MAX_LINE];

        memcpy(lineMoves, horizontalsAndVerticals[coordIdx], sizeof(lineMoves));

        for(int i = 0; i < NUM_LINES; i++){
            int lineCoords[MAX_LINE];

            memcpy(lineCoords, lineMoves[i], sizeof(lineCoords));

            if(isEmptyArray(lineCoords, MAX_LINE)){
                bool blockLine = false;
                for(int j = 0; j < MAX_LINE; j++){
                    if(blockLine){
                        break;
                    }
                    else{
                        int squareOccupied = getOccupyingArmyColour(movingPlayer, defendingPlayer, chessBoard[coordsToIdx[lineCoords[j]]]);
                        int lineLen = sizeof(queen->moves->horizontalVerticalMoves) / sizeof(queen->moves->horizontalVerticalMoves[0]);
                        int killLen = sizeof(queen->moves->killingMoves) / sizeof(queen->moves->killingMoves[0]);

                        if(squareOccupied != UNOCCUPIED){
                            if(squareOccupied == defendingPlayer->army->colour){
                                queen->moves->horizontalVerticalMoves[getFirstAvailableIndex(queen->moves->horizontalVerticalMoves, lineLen)] = coordsToIdx[lineCoords[j]];
                                queen->moves->killingMoves[getFirstAvailableIndex(queen->moves->killingMoves, killLen)] = coordsToIdx[lineCoords[j]]; 
                            }
                            
                            blockLine = true;
                        }
                        else{
                            queen->moves->horizontalVerticalMoves[getFirstAvailableIndex(queen->moves->horizontalVerticalMoves, lineLen)] = coordsToIdx[lineCoords[j]];
                        }
                    }            
                }
            }
            else{
                continue;
            }
        }
    }

    // Diagonal updates.
    for(int i = 0; i < MAX_ROOK_KILL_SQUARES; i++){
        int coordIdx = getCoordIdxByBoardPosition(queen->pce->currentSquare);

        int lineMoves[NUM_LINES][MAX_LINE];

        memcpy(lineMoves, diagonals[coordIdx], sizeof(lineMoves));

        for(int i = 0; i < NUM_LINES; i++){
            int lineCoords[MAX_LINE];

            memcpy(lineCoords, lineMoves[i], sizeof(lineCoords));

            if(isEmptyArray(lineCoords, MAX_LINE)){
                bool blockLine = false;
                for(int j = 0; j < MAX_LINE; j++){
                    if(blockLine){
                        break;
                    }
                    else{
                        int squareOccupied = getOccupyingArmyColour(movingPlayer, defendingPlayer, chessBoard[coordsToIdx[lineCoords[j]]]);
                        int diagLen = sizeof(queen->moves->diagonalMoves) / sizeof(queen->moves->diagonalMoves[0]);
                        int killLen = sizeof(queen->moves->killingMoves) / sizeof(queen->moves->killingMoves[0]);

                        if(squareOccupied != UNOCCUPIED){
                            if(squareOccupied == defendingPlayer->army->colour){
                                queen->moves->diagonalMoves[getFirstAvailableIndex(queen->moves->diagonalMoves, diagLen)] = coordsToIdx[lineCoords[j]];
                                queen->moves->killingMoves[getFirstAvailableIndex(queen->moves->killingMoves, killLen)] = coordsToIdx[lineCoords[j]]; 
                            }
                            
                            blockLine = true;
                        }
                        else{
                            queen->moves->diagonalMoves[getFirstAvailableIndex(queen->moves->diagonalMoves, diagLen)] = coordsToIdx[lineCoords[j]];
                        }
                    }            
                }
            }
            else{
                continue;
            }
        }
    }
}

void updateKingMoves(struct Player * movingPlayer, struct Player * defendingPlayer, struct King * king){
    for(int i = 0; i < MAX_KING_KILL_SQUARES; i++){
        int occupied = getOccupyingArmyColour(movingPlayer, defendingPlayer, chessBoard[coordsToIdx[king->possibleMoves[i]]]);
        if(occupied == movingPlayer->army->colour){
            king->possibleMoves[i] = INV;
        }
        else if(occupied == defendingPlayer->army->colour){
            int length = sizeof(king->killingMoves) / sizeof(king->killingMoves[0]);
            king->killingMoves[getFirstAvailableIndex(king->killingMoves, length)] = king->possibleMoves[i];
        }
    }
}

void removeInvalidPieceMoves(struct Player * movingPlayer, struct Player * defendingPlayer, int srcSquare, int currentTurn){
    switch(chessBoard[srcSquare]){
        case 'P':
            for(int i = 0; i < NUM_PAWNS; i++){
                if(movingPlayer->army->pawns[i]->pce->isAlive == true){
                    if(movingPlayer->army->pawns[i]->pce->currentSquare == srcSquare){
                        struct Pawn * currentPawn = NULL;
                        currentPawn = getPawnByBoardPosition(movingPlayer, srcSquare);

                        if(currentTurn == PLAYER_TURN){
                            updateHumanPawnMoves(movingPlayer, defendingPlayer, currentPawn);
                        }
                        else if(currentTurn == ENEMY_TURN){
                            updateComputerPawnMoves(movingPlayer, defendingPlayer, currentPawn);
                        }  
                    }
                }
            }
            break;
        case 'R':
            for(int i = 0; i < MAX_POSSIBLE_ROOKS; i++){
                if(movingPlayer->army->rooks[i]->pce->isAlive == true){
                    if(movingPlayer->army->rooks[i]->pce->currentSquare == srcSquare){
                        struct Rook * rook = getRookByBoardPosition(movingPlayer, srcSquare);
                        updateRookMoves(movingPlayer, defendingPlayer, rook);
                    }
                }
            }
            break;
        case 'H':
            for(int i = 0; i < MAX_POSSIBLE_KNIGHTS; i++){
                if(movingPlayer->army->knights[i]->pce->isAlive == true){
                    if(movingPlayer->army->knights[i]->pce->currentSquare == srcSquare){
                        struct Knight * knight = getKnightByBoardPosition(movingPlayer, srcSquare);
                        updateKnightMoves(movingPlayer, defendingPlayer, knight);
                    }
                }
            }
            break;
        case 'B':
            for(int i = 0; i < MAX_POSSIBLE_BISHOPS; i++){
                if(movingPlayer->army->bishops[i]->pce->isAlive == true){
                    if(movingPlayer->army->bishops[i]->pce->currentSquare == srcSquare){
                        struct Bishop * bishop = getBishopByBoardPosition(movingPlayer, srcSquare);
                        updateBishopMoves(movingPlayer, defendingPlayer, bishop);
                    }
                }
            }
            break;
        case 'Q':
            for(int i = 0; i < MAX_POSSIBLE_QUEENS; i++){
                if(movingPlayer->army->queens[i]->pce->isAlive == true){
                    if(movingPlayer->army->queens[i]->pce->currentSquare == srcSquare){
                        struct Queen * queen = getQueenByBoardPosition(movingPlayer, srcSquare);
                        updateQueenMoves(movingPlayer, defendingPlayer, queen);
                    }
                }
            }
            break;
        case 'K':
            updateKingMoves(movingPlayer, defendingPlayer, movingPlayer->army->king);
            break;
    }
}

int movePieces(struct Player * movingPlayer, struct Player * defendingPlayer, int startCoord, int destCoord){
    if(getOccupyingArmyColour(movingPlayer, defendingPlayer, destCoord) == UNOCCUPIED){
        struct Pawn * pawn  = getPawnByBoardPosition(movingPlayer, startCoord);
        if(pawn != NULL){ // Then piece moving is a pawn and it moves to an unoccupied space. Update its current square.
            pawn->pce->currentSquare = destCoord;
            chessBoard[destCoord] = 'P';
            chessBoard[startCoord] = ' ';
            return NORMAL_MOVE;
        }

        struct Rook * rook = getRookByBoardPosition(movingPlayer, startCoord);
        if(rook != NULL){
            rook->pce->currentSquare = destCoord;
            chessBoard[destCoord] = 'R';
            chessBoard[startCoord] = ' ';
            return NORMAL_MOVE;
        }

        struct Knight * knight = getKnightByBoardPosition(movingPlayer, startCoord);
        if(knight != NULL){
            knight->pce->currentSquare = destCoord;
            chessBoard[destCoord] = 'H';
            chessBoard[startCoord] = ' ';
            return NORMAL_MOVE;
        }

        struct Bishop * bishop = getBishopByBoardPosition(movingPlayer, startCoord);
        if(bishop != NULL){
            bishop->pce->currentSquare = destCoord;
            chessBoard[destCoord] = 'B';
            chessBoard[startCoord] = ' ';
            return NORMAL_MOVE;
        }    

        struct Queen * queen = getQueenByBoardPosition(movingPlayer, startCoord);
        if(queen != NULL){
            queen->pce->currentSquare = destCoord;
            chessBoard[destCoord] = 'Q';
            chessBoard[startCoord] = ' ';
            return NORMAL_MOVE;
        }

        if(movingPlayer->army->king->pce->currentSquare == startCoord){
            movingPlayer->army->king->pce->currentSquare = destCoord;
            chessBoard[destCoord] = 'K';
            chessBoard[startCoord] = ' ';
            return NORMAL_MOVE;
        }  
    }
    else if(getOccupyingArmyColour(movingPlayer, defendingPlayer, destCoord) == defendingPlayer->army->colour){
        struct Pawn * pawn = getPawnByBoardPosition(movingPlayer, startCoord);
        struct Rook * rook = getRookByBoardPosition(movingPlayer, startCoord);
        struct Knight * knight = getKnightByBoardPosition(movingPlayer, startCoord);
        struct Bishop * bishop = getBishopByBoardPosition(movingPlayer, startCoord);
        struct Queen * queen = getQueenByBoardPosition(movingPlayer, startCoord);

        struct Pawn * enemyPawn = getPawnByBoardPosition(defendingPlayer, destCoord);
        struct Rook * enemyRook = getRookByBoardPosition(defendingPlayer, destCoord);
        struct Knight * enemyKnight = getKnightByBoardPosition(defendingPlayer, destCoord);
        struct Bishop * enemyBishop = getBishopByBoardPosition(defendingPlayer, destCoord);
        struct Queen * enemyQueen = getQueenByBoardPosition(defendingPlayer, destCoord);

        if(pawn != NULL){
            if(enemyPawn != NULL){
                pawn->pce->currentSquare = enemyPawn->pce->currentSquare;
                chessBoard[destCoord] = 'P';
                chessBoard[startCoord] = ' ';
                enemyPawn->pce->currentSquare = INV;
                enemyPawn->pce->isAlive = false;
                return CAPTURE_MOVE;
            }
            else if(enemyRook != NULL){
                pawn->pce->currentSquare = enemyRook->pce->currentSquare;
                chessBoard[destCoord] = 'P';
                chessBoard[startCoord] = ' ';
                enemyRook->pce->currentSquare = INV;
                enemyRook->pce->isAlive = false;
                return CAPTURE_MOVE;
            }
            else if(enemyKnight != NULL){
                pawn->pce->currentSquare = enemyKnight->pce->currentSquare;
                chessBoard[destCoord] = 'P';
                chessBoard[startCoord] = ' ';
                enemyKnight->pce->currentSquare = INV;
                enemyKnight->pce->isAlive = false;
                return CAPTURE_MOVE;
            }
            else if(enemyBishop != NULL){
                pawn->pce->currentSquare = enemyBishop->pce->currentSquare;
                chessBoard[destCoord] = 'P';
                chessBoard[startCoord] = ' ';
                enemyBishop->pce->currentSquare = INV;
                enemyBishop->pce->isAlive = false;
                return CAPTURE_MOVE;
            }
            else if(enemyQueen != NULL){
                pawn->pce->currentSquare = enemyKnight->pce->currentSquare;
                chessBoard[destCoord] = 'P';
                chessBoard[startCoord] = ' ';
                enemyQueen->pce->currentSquare = INV;
                enemyQueen->pce->isAlive = false;
                return CAPTURE_MOVE;
            }
            else if(defendingPlayer->army->king->pce->currentSquare == destCoord){
                pawn->pce->currentSquare = defendingPlayer->army->king->pce->currentSquare;
                chessBoard[destCoord] = 'P';
                chessBoard[startCoord] = ' ';
                defendingPlayer->army->king->pce->currentSquare = INV;
                defendingPlayer->army->king->pce->isAlive = false;
                return CAPTURE_MOVE;
            }
        }
        else if(rook != NULL){
            if(enemyPawn != NULL){
                rook->pce->currentSquare = enemyPawn->pce->currentSquare;
                chessBoard[destCoord] = 'R';
                chessBoard[startCoord] = ' ';
                enemyPawn->pce->currentSquare = INV;
                enemyPawn->pce->isAlive = false;
                return CAPTURE_MOVE;
            }
            else if(enemyRook != NULL){
                rook->pce->currentSquare = enemyRook->pce->currentSquare;
                chessBoard[destCoord] = 'R';
                chessBoard[startCoord] = ' ';
                enemyRook->pce->currentSquare = INV;
                enemyRook->pce->isAlive = false;
                return CAPTURE_MOVE;
            }
            else if(enemyKnight != NULL){
                rook->pce->currentSquare = enemyKnight->pce->currentSquare;
                chessBoard[destCoord] = 'R';
                chessBoard[startCoord] = ' ';
                enemyKnight->pce->currentSquare = INV;
                enemyKnight->pce->isAlive = false;
                return CAPTURE_MOVE;
            }
            else if(enemyBishop != NULL){
                rook->pce->currentSquare = enemyBishop->pce->currentSquare;
                chessBoard[destCoord] = 'R';
                chessBoard[startCoord] = ' ';
                enemyBishop->pce->currentSquare = INV;
                enemyBishop->pce->isAlive = false;
                return CAPTURE_MOVE;
            }
            else if(enemyQueen != NULL){
                rook->pce->currentSquare = enemyKnight->pce->currentSquare;
                chessBoard[destCoord] = 'R';
                chessBoard[startCoord] = ' ';
                enemyQueen->pce->currentSquare = INV;
                enemyQueen->pce->isAlive = false;
                return CAPTURE_MOVE;
            }
            else if(defendingPlayer->army->king->pce->currentSquare == destCoord){
                rook->pce->currentSquare = defendingPlayer->army->king->pce->currentSquare;
                chessBoard[destCoord] = 'R';
                chessBoard[startCoord] = ' ';
                defendingPlayer->army->king->pce->currentSquare = INV;
                defendingPlayer->army->king->pce->isAlive = false;
                return CAPTURE_MOVE;
            }
        }
        else if(knight != NULL){
            if(enemyPawn != NULL){
                knight->pce->currentSquare = enemyPawn->pce->currentSquare;
                chessBoard[destCoord] = 'H';
                chessBoard[startCoord] = ' ';
                enemyPawn->pce->currentSquare = INV;
                enemyPawn->pce->isAlive = false;
                return CAPTURE_MOVE;
            }
            else if(enemyRook != NULL){
                knight->pce->currentSquare = enemyRook->pce->currentSquare;
                chessBoard[destCoord] = 'H';
                chessBoard[startCoord] = ' ';
                enemyRook->pce->currentSquare = INV;
                enemyRook->pce->isAlive = false;
                return CAPTURE_MOVE;
            }
            else if(enemyKnight != NULL){
                knight->pce->currentSquare = enemyKnight->pce->currentSquare;
                chessBoard[destCoord] = 'H';
                chessBoard[startCoord] = ' ';
                enemyKnight->pce->currentSquare = INV;
                enemyKnight->pce->isAlive = false;
                return CAPTURE_MOVE;
            }
            else if(enemyBishop != NULL){
                knight->pce->currentSquare = enemyBishop->pce->currentSquare;
                chessBoard[destCoord] = 'H';
                chessBoard[startCoord] = ' ';
                enemyBishop->pce->currentSquare = INV;
                enemyBishop->pce->isAlive = false;
                return CAPTURE_MOVE;
            }
            else if(enemyQueen != NULL){
                knight->pce->currentSquare = enemyKnight->pce->currentSquare;
                chessBoard[destCoord] = 'H';
                chessBoard[startCoord] = ' ';
                enemyQueen->pce->currentSquare = INV;
                enemyQueen->pce->isAlive = false;
                return CAPTURE_MOVE;
            }
            else if(defendingPlayer->army->king->pce->currentSquare == destCoord){
                knight->pce->currentSquare = defendingPlayer->army->king->pce->currentSquare;
                chessBoard[destCoord] = 'H';
                chessBoard[startCoord] = ' ';
                defendingPlayer->army->king->pce->currentSquare = INV;
                defendingPlayer->army->king->pce->isAlive = false;
                return CAPTURE_MOVE;
            }
        }
        else if(bishop != NULL){
            if(enemyPawn != NULL){
                bishop->pce->currentSquare = enemyPawn->pce->currentSquare;
                chessBoard[destCoord] = 'B';
                chessBoard[startCoord] = ' ';
                enemyPawn->pce->currentSquare = INV;
                enemyPawn->pce->isAlive = false;
                return CAPTURE_MOVE;
            }
            else if(enemyRook != NULL){
                bishop->pce->currentSquare = enemyRook->pce->currentSquare;
                chessBoard[destCoord] = 'B';
                chessBoard[startCoord] = ' ';
                enemyRook->pce->currentSquare = INV;
                enemyRook->pce->isAlive = false;
                return CAPTURE_MOVE;
            }
            else if(enemyKnight != NULL){
                bishop->pce->currentSquare = enemyKnight->pce->currentSquare;
                chessBoard[destCoord] = 'B';
                chessBoard[startCoord] = ' ';
                enemyKnight->pce->currentSquare = INV;
                enemyKnight->pce->isAlive = false;
                return CAPTURE_MOVE;
            }
            else if(enemyBishop != NULL){
                bishop->pce->currentSquare = enemyBishop->pce->currentSquare;
                chessBoard[destCoord] = 'B';
                chessBoard[startCoord] = ' ';
                enemyBishop->pce->currentSquare = INV;
                enemyBishop->pce->isAlive = false;
                return CAPTURE_MOVE;
            }
            else if(enemyQueen != NULL){
                bishop->pce->currentSquare = enemyKnight->pce->currentSquare;
                chessBoard[destCoord] = 'B';
                chessBoard[startCoord] = ' ';
                enemyQueen->pce->currentSquare = INV;
                enemyQueen->pce->isAlive = false;
                return CAPTURE_MOVE;
            }
            else if(defendingPlayer->army->king->pce->currentSquare == destCoord){
                bishop->pce->currentSquare = defendingPlayer->army->king->pce->currentSquare;
                chessBoard[destCoord] = 'B';
                chessBoard[startCoord] = ' ';
                defendingPlayer->army->king->pce->currentSquare = INV;
                defendingPlayer->army->king->pce->isAlive = false;
                return CAPTURE_MOVE;
            }
        }
        else if(queen != NULL){
            if(enemyPawn != NULL){
                queen->pce->currentSquare = enemyPawn->pce->currentSquare;
                chessBoard[destCoord] = 'Q';
                chessBoard[startCoord] = ' ';
                enemyPawn->pce->currentSquare = INV;
                enemyPawn->pce->isAlive = false;
                return CAPTURE_MOVE;
            }
            else if(enemyRook != NULL){
                queen->pce->currentSquare = enemyRook->pce->currentSquare;
                chessBoard[destCoord] = 'Q';
                chessBoard[startCoord] = ' ';
                enemyRook->pce->currentSquare = INV;
                enemyRook->pce->isAlive = false;
                return CAPTURE_MOVE;
            }
            else if(enemyKnight != NULL){
                queen->pce->currentSquare = enemyKnight->pce->currentSquare;
                chessBoard[destCoord] = 'Q';
                chessBoard[startCoord] = ' ';
                enemyKnight->pce->currentSquare = INV;
                enemyKnight->pce->isAlive = false;
                return CAPTURE_MOVE;
            }
            else if(enemyBishop != NULL){
                queen->pce->currentSquare = enemyBishop->pce->currentSquare;
                chessBoard[destCoord] = 'Q';
                chessBoard[startCoord] = ' ';
                enemyBishop->pce->currentSquare = INV;
                enemyBishop->pce->isAlive = false;
                return CAPTURE_MOVE;
            }
            else if(enemyQueen != NULL){
                queen->pce->currentSquare = enemyKnight->pce->currentSquare;
                chessBoard[destCoord] = 'Q';
                chessBoard[startCoord] = ' ';
                enemyQueen->pce->currentSquare = INV;
                enemyQueen->pce->isAlive = false;
                return CAPTURE_MOVE;
            }
            else if(defendingPlayer->army->king->pce->currentSquare == destCoord){
                queen->pce->currentSquare = defendingPlayer->army->king->pce->currentSquare;
                chessBoard[destCoord] = 'Q';
                chessBoard[startCoord] = ' ';
                defendingPlayer->army->king->pce->currentSquare = INV;
                defendingPlayer->army->king->pce->isAlive = false;
                return CAPTURE_MOVE;
            }
        }
        else if(movingPlayer->army->king->pce->currentSquare == startCoord){
            if(enemyPawn != NULL){
                movingPlayer->army->king->pce->currentSquare = enemyPawn->pce->currentSquare;
                chessBoard[destCoord] = 'K';
                chessBoard[startCoord] = ' ';
                enemyPawn->pce->currentSquare = INV;
                enemyPawn->pce->isAlive = false;
                return CAPTURE_MOVE;
            }
            else if(enemyRook != NULL){
                movingPlayer->army->king->pce->currentSquare = enemyRook->pce->currentSquare;
                chessBoard[destCoord] = 'K';
                chessBoard[startCoord] = ' ';
                enemyRook->pce->currentSquare = INV;
                enemyRook->pce->isAlive = false;
                return CAPTURE_MOVE;
            }
            else if(enemyKnight != NULL){
                movingPlayer->army->king->pce->currentSquare = enemyKnight->pce->currentSquare;
                chessBoard[destCoord] = 'K';
                chessBoard[startCoord] = ' ';
                enemyKnight->pce->currentSquare = INV;
                enemyKnight->pce->isAlive = false;
                return CAPTURE_MOVE;
            }
            else if(enemyBishop != NULL){
                movingPlayer->army->king->pce->currentSquare = enemyBishop->pce->currentSquare;
                chessBoard[destCoord] = 'K';
                chessBoard[startCoord] = ' ';
                enemyBishop->pce->currentSquare = INV;
                enemyBishop->pce->isAlive = false;
                return CAPTURE_MOVE;
            }
            else if(enemyQueen != NULL){
                movingPlayer->army->king->pce->currentSquare = enemyKnight->pce->currentSquare;
                chessBoard[destCoord] = 'K';
                chessBoard[startCoord] = ' ';
                enemyQueen->pce->currentSquare = INV;
                enemyQueen->pce->isAlive = false;
                return CAPTURE_MOVE;
            }
            else if(defendingPlayer->army->king->pce->currentSquare == destCoord){
                movingPlayer->army->king->pce->currentSquare = defendingPlayer->army->king->pce->currentSquare;
                chessBoard[destCoord] = 'K';
                chessBoard[startCoord] = ' ';
                defendingPlayer->army->king->pce->currentSquare = INV;
                defendingPlayer->army->king->pce->isAlive = false;
                return CAPTURE_MOVE;
            }
        }
    }

    return INV;
}

int getFirstEmptyPointerIdx(void * arr[], int len){
    for(int i = 0; i < len; i++){
        if(arr[i] == NULL){ // Empty index. Return i.
            return i;
        }
    }

    return INV; // Return a negative value. There are no empty spaces in the array.
}

void pawnToRook(struct Player * player, struct Pawn * promotedPawn, int mode){
    int size = sizeof(player->army->rooks) / sizeof(player->army->rooks[0]);
    int idx = getFirstEmptyPointerIdx((void **) player->army->rooks, size);

    player->army->rooks[idx] = initRook(player->army->rooks[idx], mode);
    player->army->rooks[idx]->pce->currentSquare = promotedPawn->pce->currentSquare;
    promotedPawn->pce->isAlive = false;
    chessBoard[player->army->rooks[idx]->pce->currentSquare] = 'R';
    freePawn(promotedPawn);
}

void pawnToKnight(struct Player * player, struct Pawn * promotedPawn){
    int size = sizeof(player->army->knights) / sizeof(player->army->knights[0]);
    int idx = getFirstEmptyPointerIdx((void **) player->army->knights, size);

    player->army->knights[idx] = initKnight(player->army->knights[idx]);
    player->army->knights[idx]->pce->currentSquare = promotedPawn->pce->currentSquare;
    promotedPawn->pce->isAlive = false;
    chessBoard[player->army->knights[idx]->pce->currentSquare] = 'H';
    freePawn(promotedPawn);
}

void pawnToBishop(struct Player * player, struct Pawn * promotedPawn){
    int size = sizeof(player->army->bishops) / sizeof(player->army->bishops[0]);
    int idx = getFirstEmptyPointerIdx((void **) player->army->bishops, size);

    player->army->bishops[idx] = initBishop(player->army->bishops[idx]);
    player->army->bishops[idx]->pce->currentSquare = promotedPawn->pce->currentSquare;
    promotedPawn->pce->isAlive = false;
    chessBoard[player->army->bishops[idx]->pce->currentSquare] = 'H';
    freePawn(promotedPawn);
}

void pawnToQueen(struct Player * player, struct Pawn * promotedPawn, int mode){
    int size = sizeof(player->army->queens) / sizeof(player->army->queens[0]);
    int idx = getFirstEmptyPointerIdx((void **) player->army->queens, size);

    player->army->queens[idx] = initQueen(player->army->queens[idx], mode);
    player->army->queens[idx]->pce->currentSquare = promotedPawn->pce->currentSquare;
    promotedPawn->pce->isAlive = false;
    chessBoard[player->army->queens[idx]->pce->currentSquare] = 'H';
    freePawn(promotedPawn);
}

void doPromotion(struct Player * movingPlayer, int destCoord, int mode){
    struct Pawn * promotedPawn = getPawnByBoardPosition(movingPlayer, destCoord);

    bool valid = true;

    if(promotedPawn == NULL){
        printf("There was an error getting the pawn's info while attempting to promote it. Terminating program...\n");
    }
    else{
        do{
            valid = true;
            printf("Congrats %s! Your pawn is promoted. Select one of the following options to turn your pawn into that piece:\n1. Rook\n2. Knight\n3. Bishop\n4. Queen\n", movingPlayer->name);
            
            int choice = INV;
            scanf("%d", &choice);

            switch(choice){
                case 1:
                    pawnToRook(movingPlayer, promotedPawn, mode);
                    break;
                case 2:
                    pawnToRook(movingPlayer, promotedPawn, mode);
                    break;
                case 3:
                    pawnToRook(movingPlayer, promotedPawn, mode);
                    break;
                case 4:
                    pawnToRook(movingPlayer, promotedPawn, mode);
                    break;
                default:
                    printf("There was an error with your input, reprompting...");
                    valid = false;
                    break;
            }
        } while(valid == false);
    }
}

bool isCoordInPossibleMoves(struct Player * player, int coord){
    // Check Pawns
    for(int i = 0; i < NUM_PAWNS; i++){
        if(player->army->pawns[i] != NULL){
            if(player->army->pawns[i]->pce->isAlive){
                int possibleMovesSize = sizeof(player->army->pawns[i]->possibleMoves) / sizeof(player->army->pawns[i]->possibleMoves[0]);
                
                for(int j = 0; j < possibleMovesSize; j++){
                    if(coordsToIdx[player->army->pawns[i]->possibleMoves[j]] == coord){
                        return true;
                    }
                }

            }
        }
    }

    // Check Rooks
    for(int i = 0; i < MAX_POSSIBLE_ROOKS; i++){
        if(player->army->rooks[i] != NULL){
            if(player->army->rooks[i]->pce->isAlive){
                int possibleMovesSize = sizeof(player->army->rooks[i]->possibleMoves) / sizeof(player->army->rooks[i]->possibleMoves[0]);
                
                for(int j = 0; j < possibleMovesSize; j++){
                    if(coordsToIdx[player->army->rooks[i]->possibleMoves[j]] == coord){
                        return true;
                    }
                }

            }
        }
    }

    // Check Knights
    for(int i = 0; i < MAX_POSSIBLE_KNIGHTS; i++){
        if(player->army->knights[i] != NULL){
            if(player->army->knights[i]->pce->isAlive){
                int possibleMovesSize = sizeof(player->army->knights[i]->possibleMoves) / sizeof(player->army->knights[i]->possibleMoves[0]);
                
                for(int j = 0; j < possibleMovesSize; j++){
                    if(coordsToIdx[player->army->knights[i]->possibleMoves[j]] == coord){
                        return true;
                    }
                }

            }
        }
    }

    // Check Bishops
    for(int i = 0; i < MAX_POSSIBLE_BISHOPS; i++){
        if(player->army->bishops[i] != NULL){
            if(player->army->bishops[i]->pce->isAlive){
                int possibleMovesSize = sizeof(player->army->bishops[i]->possibleMoves) / sizeof(player->army->bishops[i]->possibleMoves[0]);
                
                for(int j = 0; j < possibleMovesSize; j++){
                    if(coordsToIdx[player->army->bishops[i]->possibleMoves[j]] == coord){
                        return true;
                    }
                }

            }
        }
    }

    // Check Queens
    for(int i = 0; i < MAX_POSSIBLE_QUEENS; i++){
        if(player->army->queens[i] != NULL){
            if(player->army->queens[i]->pce->isAlive){
                int diagonalMovesSize = sizeof(player->army->queens[i]->moves->diagonalMoves) / sizeof(player->army->queens[i]->moves->diagonalMoves[0]);
                int linearMovesSize = sizeof(player->army->queens[i]->moves->horizontalVerticalMoves) / sizeof(player->army->queens[i]->moves->horizontalVerticalMoves[0]);

                for(int j = 0; j < diagonalMovesSize; j++){
                    if(coordsToIdx[player->army->queens[i]->moves->diagonalMoves[j]] == coord){
                        return true;
                    }
                }

                for(int j = 0; j < linearMovesSize; j++){
                    if(coordsToIdx[player->army->queens[i]->moves->horizontalVerticalMoves[j]] == coord){
                        return true;
                    }
                }
            }
        }
    }

    return false;
}

bool canDefendingPieceBlockRook(struct Rook * rook, struct Player * defendingPlayer, int startIdx, int kingIdx){
    int boardCoord = boardPositionToCoord(rook->pce->currentSquare);
    
    // Convert board string indices into board coordinate indices.
    int startPos = boardPositionToCoord(startIdx);
    int kingPos = boardPositionToCoord(kingIdx);

    int rookDirections[NUM_LINES][MAX_LINE];

    memcpy(rookDirections, horizontalsAndVerticals[boardCoord], sizeof(rookDirections));

    int startPosPathIdx = INV;
    int kingPosPathIdx = INV;
 
    // Find the rook path that contains both the king's current square and the threatening rook's current square.
    for(int i = 0; i < NUM_LINES; i++){
        int rookPath[MAX_LINE];

        memcpy(rookPath, rookDirections[i], sizeof(rookDirections[i])); // Get the current path (will cycle through all if necessary).

        for(int j = 0; j < MAX_LINE; j++){
            if(rookPath[j] == startPos){ // Then current path contains the rook's current board position.
                startPosPathIdx = j; // Record the index of the current square.
            }
            else if(rookPath[j] == kingPos){
                kingPosPathIdx = j;
            }
        }

        if(startPosPathIdx != INV && kingPosPathIdx != INV){ // Then both pieces exist on this path.
            int diff = startPosPathIdx - kingPosPathIdx;
            if(diff > 1 || diff < -1){ // Then there is a difference of at least one space. Check defending player's pieces to see if they can move to block.
                int min = getMin(startPosPathIdx, kingPosPathIdx);
                int max = getMin(startPosPathIdx, kingPosPathIdx);

                if(min != INV && max != INV){
                    for(int i = min + 1; i < max; i++){
                        if(isCoordInPossibleMoves(defendingPlayer, coordsToIdx[i])){
                            return true;
                        }
                    }
                    
                    return false;
                }
            }
            else{
                return false;
            }
        }
        else{ // Reset values after each path is analyzed.
            startPosPathIdx = INV;
            kingPosPathIdx = INV;
        }

    }

    return false;
}

bool canDefendingPieceBlockBishop(struct Bishop * bishop, struct Player * defendingPlayer, int startIdx, int kingIdx){
    int boardCoord = boardPositionToCoord(bishop->pce->currentSquare);
    
    // Convert board string indices into board coordinate indices.
    int startPos = boardPositionToCoord(startIdx);
    int kingPos = boardPositionToCoord(kingIdx);

    int bishopDirections[NUM_LINES][MAX_LINE];

    memcpy(bishopDirections, diagonals[boardCoord], sizeof(bishopDirections));

    int startPosPathIdx = INV;
    int kingPosPathIdx = INV;
 
    // Find the rook path that contains both the king's current square and the threatening rook's current square.
    for(int i = 0; i < NUM_LINES; i++){
        int rookPath[MAX_LINE];

        memcpy(rookPath, bishopDirections[i], sizeof(bishopDirections[i])); // Get the current path (will cycle through all if necessary).

        for(int j = 0; j < MAX_LINE; j++){
            if(rookPath[j] == startPos){ // Then current path contains the rook's current board position.
                startPosPathIdx = j; // Record the index of the current square.
            }
            else if(rookPath[j] == kingPos){
                kingPosPathIdx = j;
            }
        }

        if(startPosPathIdx != INV && kingPosPathIdx != INV){ // Then both pieces exist on this path.
            int diff = startPosPathIdx - kingPosPathIdx;
            if(diff > 1 || diff < -1){ // Then there is a difference of at least one space. Check defending player's pieces to see if they can move to block.
                int min = getMin(startPosPathIdx, kingPosPathIdx);
                int max = getMin(startPosPathIdx, kingPosPathIdx);

                if(min != INV && max != INV){
                    for(int i = min + 1; i < max; i++){
                        if(isCoordInPossibleMoves(defendingPlayer, coordsToIdx[i])){
                            return true;
                        }
                    }
                    
                    return false;
                }
            }
            else{
                return false;
            }
        }
        else{ // Reset values after each path is analyzed.
            startPosPathIdx = INV;
            kingPosPathIdx = INV;
        }

    }

    return false;
}

bool canDefendingPieceBlockQueen(struct Queen * queen, struct Player * defendingPlayer, int startIdx, int kingIdx){
    int boardCoord = boardPositionToCoord(queen->pce->currentSquare);
    
    // Convert board string indices into board coordinate indices.
    int startPos = boardPositionToCoord(startIdx);
    int kingPos = boardPositionToCoord(kingIdx);

    int linearDirections[NUM_LINES][MAX_LINE];
    int diagonalDirections[NUM_LINES][MAX_LINE];

    memcpy(linearDirections, horizontalsAndVerticals[boardCoord], sizeof(linearDirections));
    memcpy(diagonalDirections, diagonals[boardCoord], sizeof(diagonalDirections));

    int startPosPathIdx = INV;
    int kingPosPathIdx = INV;
 
    // Find the rook path that contains both the king's current square and the threatening rook's current square.
    for(int i = 0; i < NUM_LINES; i++){
        int linearPath[MAX_LINE];
        int diagonalPath[MAX_LINE];

        // Get the current horizontal & vertical path (will cycle through all if necessary).
        memcpy(linearPath, linearDirections[i], sizeof(linearPath)); 
        memcpy(diagonalPath, diagonals[i], sizeof(diagonalPath)); 

        // Check linear path.
        for(int j = 0; j < MAX_LINE; j++){
            if(linearPath[j] == startPos){ // Then current path contains the queen's current board position.
                startPosPathIdx = j; // Record the index of the current square.
            }
            else if(linearPath[j] == kingPos){
                kingPosPathIdx = j;
            }
        }

        if(startPosPathIdx != INV && kingPosPathIdx != INV){ // Then both pieces exist on this path.
            int diff = startPosPathIdx - kingPosPathIdx;
            if(diff > 1 || diff < -1){ // Then there is a difference of at least one space. Check defending player's pieces to see if they can move to block.
                int min = getMin(startPosPathIdx, kingPosPathIdx);
                int max = getMin(startPosPathIdx, kingPosPathIdx);

                if(min != INV && max != INV){
                    for(int i = min + 1; i < max; i++){
                        if(isCoordInPossibleMoves(defendingPlayer, coordsToIdx[i])){
                            return true;
                        }
                    }
                }
            }
        }
        else{ // Reset values after each path is analyzed.
            startPosPathIdx = INV;
            kingPosPathIdx = INV;
        }

        // Check diagonal path.
        for(int j = 0; j < MAX_LINE; j++){
            if(diagonalPath[j] == startPos){ // Then current path contains the queen's current board position.
                startPosPathIdx = j; // Record the index of the current square.
            }
            else if(diagonalPath[j] == kingPos){
                kingPosPathIdx = j;
            }
        }

        if(startPosPathIdx != INV && kingPosPathIdx != INV){ // Then both pieces exist on this path.
            int diff = startPosPathIdx - kingPosPathIdx;
            if(diff > 1 || diff < -1){ // Then there is a difference of at least one space. Check defending player's pieces to see if they can move to block.
                int min = getMin(startPosPathIdx, kingPosPathIdx);
                int max = getMin(startPosPathIdx, kingPosPathIdx);

                if(min != INV && max != INV){
                    for(int i = min + 1; i < max; i++){
                        if(isCoordInPossibleMoves(defendingPlayer, coordsToIdx[i])){
                            return true;
                        }
                    }
                }
            }
        }
        else{ // Reset values after each path is analyzed.
            startPosPathIdx = INV;
            kingPosPathIdx = INV;
        }
    }

    return false;
}

// Checks if the last move put the defending army's king at risk of capture.
bool isKingInCheck(struct Player * movingPlayer, struct Player * defendingPlayer, int destCoord){    
    if(isCoordInPossibleMoves(movingPlayer, defendingPlayer->army->king->pce->currentSquare)){
        return true;
    }

    return false;
}

// Determines if the king is checkmated (game is over).
bool isKingCheckmated(struct Player * movingPlayer, struct Player * defendingPlayer, int destCoord){
    struct Pawn * checkPawn = getPawnByBoardPosition(defendingPlayer, destCoord);
    struct Rook * checkRook = getRookByBoardPosition(defendingPlayer, destCoord);;
    struct Knight * checkKnight = getKnightByBoardPosition(defendingPlayer, destCoord);;
    struct Bishop * checkBishop = getBishopByBoardPosition(defendingPlayer, destCoord);;
    struct Queen * checkQueen = getQueenByBoardPosition(defendingPlayer, destCoord);;

    // First check if the king has any valid moves. (Check enemy piece possible moves to see if they coincide with the king's).
    int kingMovesSize = sizeof(defendingPlayer->army->king->possibleMoves) / sizeof(defendingPlayer->army->king->possibleMoves[0]);
    
    if(isKingInCheck(movingPlayer, defendingPlayer, destCoord)){
        if(isEmptyArray(defendingPlayer->army->king->possibleMoves, kingMovesSize)){ // King has no valid moves. Determine if a piece the defending player has piece can kill it.
            if (isCoordInPossibleMoves(defendingPlayer, destCoord)){ // A piece of the defending player can move to kill the piece that checked the king. 
                return false; // King not checkmated.
            }
        }
        else{ // Defending player cannot kill the king and the king has no possible moves. The only way to not be checkmated is if the defending player can block the path to the threatened king.
            // If the piece threatening the king is anything other than a rook, bishop, or queen. The board is in a checkmate state.
            if(checkPawn != NULL || checkKnight != NULL){ // Checkmate
                return true;
            }
            else { // Determine the piece type that moved. And then check if there are free spaces between the threatening piece and the defending king, check if any of the defending player's pieces can move there to block.
                if(checkRook != NULL){ 
                    if(canDefendingPieceBlockRook(checkRook, defendingPlayer, destCoord, defendingPlayer->army->king->pce->currentSquare)){
                        return false;
                    }
                    else{
                        return true;
                    }
                }
                else if(checkBishop != NULL){
                    if(canDefendingPieceBlockBishop(checkBishop, defendingPlayer, destCoord, defendingPlayer->army->king->pce->currentSquare)){
                        return false;
                    }
                    else{
                        return true;
                    }
                }
                else if(checkQueen != NULL){
                    if(canDefendingPieceBlockQueen(checkQueen, defendingPlayer, destCoord, defendingPlayer->army->king->pce->currentSquare)){
                        return false;
                    }
                    else{
                        return true;
                    }
                }
            }
        }
    }
    else{
        return false; // King not checkmated.
    }

    // If the king has no moves left, check if a friendly piece can block the threat path. (Should do this in order of piece weight from smallest to largest, that way the lower value pieces are moved to
    // block first, and therefore provide least consequence for blocking the king if the piece is lost).



    return false;
}

void doPlayerTurn(struct Player * human, struct Player * computer){
    bool moveComplete = false;
    char * dummyInput = (char *) malloc(sizeof(char));
    char * pieceName = (char *) malloc(sizeof(char) * MAX_NAME_LEN);

    do{
        printf("Hey %s, it's your turn! Enter the coordinate of the piece you want to move (ex. a7): \n", human->name);
        char pieceCoords[COORD_LEN];
        scanf("%s", pieceCoords);

        for(int i = 0; i < strlen(pieceCoords); i++){
            pieceCoords[i] = tolower(pieceCoords[i]);
        }

        if(isValidCoordinate(pieceCoords)){
            int startCoord = coordToBoardPosition(pieceCoords);

            strcpy(pieceName, getPieceNameByIdx(human, startCoord));
            
            if(human->army->colour == getOccupyingArmyColour(human, computer, startCoord)){
                char destCoordStr[COORD_LEN];

                printf("idx: %d\n", startCoord);
                // Update the moves here instead.
                removeInvalidPieceMoves(human, computer, startCoord, PLAYER_TURN);

                printf("Where would you like to move your %s (at %s)?\n", pieceName, pieceCoords);
                scanf("%s", destCoordStr);

                if(isValidCoordinate(destCoordStr)){
                    int destCoord = coordToBoardPosition(destCoordStr);
                    
                    printf("dest: %d\n", destCoord);

                    char capturePieceName[PIECE_NAME_LEN]; 
                    strcpy(capturePieceName, getPieceNameByIdx(computer, destCoord));
                    
                    // Execute move here.
                    int moveType = movePieces(human, computer, startCoord, destCoord);    

                    pieceCoords[0] = toupper(pieceCoords[0]);
                    destCoordStr[0] = toupper(destCoordStr[0]);

                    if(moveType == NORMAL_MOVE){
                        printChessBoard(human, computer);    
                        printf("Your %s (at %s) moves to %s.\n", pieceName, pieceCoords, destCoordStr);
                        sleep(5);                                           
                    }
                    else if(moveType == CAPTURE_MOVE){
                        printChessBoard(human, computer);
                        printf("Your %s (at %s) captured enemy's %s (at %s).\n", pieceName, pieceCoords, capturePieceName, destCoordStr);
                        sleep(5);
                    }
                    else{
                        printf("There was an error moving pieces.");
                    }

                    moveComplete = true;
                }
                else{
                    printf("You cannot move your piece there. Please enter a valid move.\n");
                    sleep(5);
                    continue;
                }
            }
            else{
                printf("The coordinate you entered does not contain a piece you can control. Provide another coordinate when prompted.\n");
                sleep(5);
                continue;
            }
        }
        else{
            printf("The coordinate entered does not exist. Enter a new coordinate when prompted.\n");
            sleep(5);
            continue; // The coordinate entered does not exist-> Press enter to renter a valid coordinate.
        }
    } while(moveComplete == false);
    
    free(pieceName);
    free(dummyInput);

    printf("Player move finished.\n");
}

bool doEnemyTurn(struct Player * human, struct Player * computer){
    return true;
}

void run(struct Player * human, struct Player * computer){
    bool gameWon = false;
    int turn = 0;

    do{
        printChessBoard(human, computer);
        
        if(getTurn(turn) == PLAYER_TURN){
            doPlayerTurn(human, computer);
        }
        else if (getTurn(turn) == ENEMY_TURN) {
            gameWon = doEnemyTurn(human, computer);
        }

        turn++;
    } while(gameWon == false);
}

int main(){
    struct Player * human = NULL;
    struct Player * computer = NULL;
    
    human = initPlayer(human, PLAYER_TURN);
    computer = initPlayer(computer, ENEMY_TURN);

    printf("\nWelcome to Chess! What colour do you want your pieces to be? (Enter the corresponding number beside the colour)\n");
    setGreenPrint();
    printf("1. Green\n");
    setCyanPrint();
    printf("2. Cyan\n");
    setBluePrint();
    printf("3. Blue\n");
    setRedPrint();
    printf("4. Red\n");
    setYellowPrint();
    printf("5. Yellow\n");
    setPurplePrint();
    printf("6. Purple\n");
    resetPrintColour();

    int colourChoice;

    initBoard(human, computer);

    scanf("%d", &colourChoice);
    nl();
    human->army->colour = colourChoice - 1;

    char playerName[MAX_NAME_LEN];

    printf("Please enter your name: \n");
    scanf("%s", playerName);

    strcpy(human->name, playerName);
    run(human, computer);

    // Free the player object's memory.
    freePlayer(computer);
    freePlayer(human);

    printf("Terminated.\n");
}