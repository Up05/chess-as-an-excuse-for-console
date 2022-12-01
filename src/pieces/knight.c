#include "ulti.h"


Piece knight_new(byte x, byte y){
    Piece knight;
    knight.x = x;
    knight.y = y;
    knight.type = KNIGHT;

    
    return knight; 
}

bool knight_check_move(Piece* knight, byte x, byte y){

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

void knight_show_possible_moves(Piece* piece){
    byte x = piece->x, 
         y = piece->y;

    a(x + 2, y + 1, piece->team);
    a(x + 2, y - 1, piece->team);

    a(x - 2, y + 1, piece->team);
    a(x - 2, y - 1, piece->team);

    a(x + 1, y + 2, piece->team);
    a(x - 1, y + 2, piece->team);

    a(x + 1, y - 2, piece->team);
    a(x - 1, y - 2, piece->team);

}


void knight_draw(int x, int y){
    int a = SQ_SIZE / 2,
        b = a / 2,
        c = a / 3,
        d = b / 2,
        e = d / 2;

    int _x = x + a, 
        _y = y + a;

    rect(_x - c, _y - b, b, c);
    rect(_x - c + e/2, _y - b + e*2, -e, -e);
    rect((int) _x - c + e*1.3, _y - b, d, -e/2);

    glBegin(GL_QUAD_STRIP);
    glVertex2i((int) _x + c, _y + b);
    glVertex2i(_x + c - e, _y - b);
    glVertex2i((int) _x - c, _y + b);
    glVertex2i(_x - c + d, _y - b);
    glEnd();
}