#include "ulti.h"


Piece queen_new(byte x, byte y){
    Piece queen;
    queen.x = x;
    queen.y = y;
    queen.type = QUEEN;


    return queen; 
}

bool queen_check_move(Piece* queen, byte x, byte y){


    // check for teamate collision
    // ent passant, I'll need the board for that!
    return false;
}

void queen_show_possible_moves(Piece* piece){
    rook_show_possible_moves(piece);
    bishop_show_possible_moves(piece);

}

void queen_draw(int x, int y){
    int a = SQ_SIZE / 2,
        b = a / 2,
        c = a / 3;

    int _x = x + a, 
        _y = y + a;


    glBegin(GL_QUAD_STRIP);
    glVertex2i(_x, _y - b + c);
    glVertex2i(_x - c, _y - b);
    glVertex2i(_x + c, _y - b);
    glVertex2i(_x, _y + c);
    glEnd();

    ellipse2(_x,  _y - (b - c / 8), (int) b / 2.8, (int) b / 1.6, 12);
    ellipse2(_x, _y - (b - c),         b / 2, b / 4, 12);

    glBegin(GL_TRIANGLE_STRIP);
    glVertex2i(_x + c, _y + a - c);
    glVertex2i(_x,     _y - a + c);
    glVertex2i(_x - c, _y + a - c);
    glEnd();
}
