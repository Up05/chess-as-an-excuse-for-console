#include "ulti.h"


Piece rook_new(byte x, byte y){
    Piece rook;
    rook.x = x;
    rook.y = y;
    rook.type = ROOK;
    
    return rook; 
}

bool rook_check_move(Piece* rook, byte x, byte y){


    // check for teamate collision
    // ent passant, I'll need the board for that!
    return false;
}

static bool a (byte x, byte y, char team){
    if(may_move(x, y, team) == MOVE_NOT) // if it's out of border
        return true;
    if(may_move(x, y, team) == MOVE_ATTACK){
        sq(x, y);
        return true;
    }
    sq(x, y);
    return false;
}

void rook_show_possible_moves(Piece* piece) {
    byte x = piece->x, 
         y = 0;

    for(y = piece->y + 1; y < 8; y ++){
        if(a(x, y, piece->team))
            break;
    }
    x = piece->x;
    for(y = piece->y - 1; y >= 0; y --){
        if(a(x, y, piece->team))
            break;
    }
    y = piece->y;
    for(x = piece->x + 1; x < 8; x ++){
        if(a(x, y, piece->team))
            break;
    }
    for(x = piece->x - 1; x >= 0; x --){
        if(a(x, y, piece->team))
            break;
    }

}

void rook_draw(int x, int y){
    int a = SQ_SIZE / 2,
        b = a / 2,
        c = a / 3,
        d = b / 2;

    int _x = x + a, 
        _y = y + a;


    rect(_x + c - d/2, _y - b, d, -d);
    rect(_x     - d/2, _y - b, d, -d);
    rect(_x - c - d/2, _y - b, d, -d);

    rect(_x - c - d/3, _y - b + d/2, c * 2 + d/3 * 2, -d);

    glBegin(GL_QUAD_STRIP);
    glVertex2i((int) _x + a / 2.5, _y + b);
    glVertex2i(_x + c, _y - b);
    glVertex2i((int) _x - a / 2.5, _y + b);
    glVertex2i(_x - c, _y - b);
    glEnd();


}