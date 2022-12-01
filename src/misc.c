#include "ulti.h"


void add_possible_move(Move move){
    for(int i = 0; i < 28; i ++)
        if(!possible_moves[i].exists){
            possible_moves[i].exists = true;
            possible_moves[i].x = move.x;
            possible_moves[i].y = move.y;
            break;
        }
}

void clear_possible_moves(){
    for(int i = 0; i < 28; i ++){
        possible_moves[i].exists = false;
    }
}

void debug(Piece* piece){
    printf("piece: %d (%d; %d), team: %d, has_moved: %d\n", piece->type, piece->team, piece->x, piece->y, piece->has_moved);
}

void strfill(char* str, int len, char ch){
    for(int i = 0; i < len; i ++)
        str[i] = ch;
}