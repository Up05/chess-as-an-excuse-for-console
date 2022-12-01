#include "ulti.h"


Piece pawn_new(byte x, byte y){
    Piece pawn;
    pawn.x = x;
    pawn.y = y;
    pawn.type = PAWN;
    
    return pawn; 
}

bool pawn_check_move(Piece* pawn, byte x, byte y){
    if(pawn->x == x && pawn->y + pawn->team == y) 
        return true;
    if(pawn->x == x && pawn->y + 2*pawn->team == y && !pawn->has_moved)
        return true;

    // check for teamate collision
    // ent passant, I'll need the board for that!
    return false;
}


void promotion(Piece* pawn){
    if(pawn->y == 0 || pawn->y == 7)
        puts("can promote!");
}

void pawn_show_possible_moves(Piece* piece){


    int x = piece->x, y = piece->y, t = piece->team;

    if(may_move(x, y + t, t) == MOVE_ALL){
        sq(x, y + t);
        
        if(!piece->has_moved && may_move(x, y + t * 2, t) == MOVE_ALL) // this is inside of if(), because you can't just skip a piece with a pawn, this isn't a horse
            sq(x, y + t * 2);
    }

    if(may_move(x + 1, y + t, t) == MOVE_ATTACK)
        sq(x + 1, y + t);
    
    if(may_move(x - 1, y + t, t) == MOVE_ATTACK)
        sq(x - 1, y + t);
    

    Piece ep; // enemy pawn
    if(x + 1 < 8 && board[x + 1][y].type == PAWN){
        ep = board[x + 1][y];
        if(ep.double_moved_on_turn == move_count % 256 - 1)
            sq(x + 1, y + t);
    }
    if(x - 1 > -1 && board[x - 1][y].type == PAWN){
        ep = board[x - 1][y];
        if(ep.double_moved_on_turn == move_count % 256 - 1)
            sq(x - 1, y + t);
    }
}


void pawn_draw(int x, int y){
    int a = SQ_SIZE / 2,
        b = a / 2,
        c = a / 3;

    int _x = x + a, 
        _y = y + a;

    ellipse(_x, _y - c, (int) a / 3.5, 12);
    rect(_x - c, _y, c * 2, c / 4);

    glBegin(GL_TRIANGLE_STRIP);
    glVertex2i((int) _x + a / 2.5, _y + b);
    glVertex2i(_x,                 _y - b);
    glVertex2i((int) _x - a / 2.5, _y + b);
    glEnd();

}