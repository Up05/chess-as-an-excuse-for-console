#include "ulti.h"


Piece bishop_new(byte x, byte y){
    Piece bishop;
    bishop.x = x;
    bishop.y = y;
    bishop.type = BISHOP;
    
    return bishop; 
}

bool bishop_check_move(Piece* bishop, byte x, byte y){
    

    // check for teamate collision
    // ent passant, I'll need the board for that!
    return false;
}

static bool a(byte x, byte y, char team){
    if(may_move(x, y, team) == MOVE_NOT) // if it's out of border
        return true;
    if(may_move(x, y, team) == MOVE_ATTACK){
        sq(x, y);
        return true;
    }
    sq(x, y);
    return false;
}

void bishop_show_possible_moves(Piece* piece){
    byte x = piece->x, y = 0;

    for(y = piece->y + 1; y < 8; y ++){
        x ++;
        if(a(x, y, piece->team))
            break;
    }
    x = piece->x;
    for(y = piece->y - 1; y >= 0; y --){
        x ++;
        if(a(x, y, piece->team))
            break;
    }
    x = piece->x;
    for(y = piece->y + 1; y < 8; y ++){
        x --;
        if(a(x, y, piece->team))
            break;
    }
    x = piece->x;
    for(y = piece->y - 1; y >= 0; y --){
        x --;
        if(a(x, y, piece->team))
            break;
    }


}

void bishop_draw(int x, int y){
    int a = SQ_SIZE / 2,
        b = a / 2,
        c = a / 3;

    int _x = x + a, 
        _y = y + a;


    ellipse2(_x,  _y - (b - c / 8), (int) b / 2.8, (int) b / 1.6, 12);
    ellipse2(_x, _y - (b - c),         b / 2, b / 4, 12);

    glBegin(GL_TRIANGLE_STRIP);
    glVertex2i(_x + c, _y + a - c);
    glVertex2i(_x,     _y - a + c);
    glVertex2i(_x - c, _y + a - c);
    glEnd();
}


