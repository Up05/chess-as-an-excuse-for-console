#include "ulti.h"


Piece king_new(byte x, byte y){
    Piece king;
    king.x = x;
    king.y = y;
    king.type = KING;
    
    return king; 
}

bool king_check_move(Piece* king, byte x, byte y){
    

    
    return false;
}

static bool _a(byte x, byte y, char team){
    if(may_move(x, y, team) == MOVE_NOT) // if it's out of border
        return true;
    if(may_move(x, y, team) == MOVE_ATTACK){
        sq(x, y);
        return true;
    }
    sq(x, y);
    return false;
}

static bool empty(byte x, byte y){
    if(x > 8 || x < 0 || y > 8 || y < 0) return true;
    return board[x][y].type == EMPTY;
} 

static bool has_enemy(byte x, byte y, byte type, byte type2, char team){
    return (board[x][y].type == type || board[x][y].type == type2) && board[x][y].team != team;
}

void king_show_possible_moves(Piece* piece){
    double pi = 3.1415926535897;

    for(double a = 0; a <= pi*2; a += pi/4){
        int xs = round(cos(a));
        int ys = round(sin(a));

        byte x = piece->x + xs; 
        byte y = piece->y + ys;

        // printf("xs: %d, ys: %d; ", xs, ys);

        char t = piece->team;
        // ########################## Pieces attacking king
        // Pawns
        if(has_enemy(x + 1, y + t, PAWN, NAT, t) || has_enemy(x - 1, y + t, PAWN, NAT, t)) goto Portugal;
        // Rook
        for(char _y = y + 1; _y <  8; _y ++) if(has_enemy( x, _y, ROOK, QUEEN, t)) goto Portugal; else if(!empty(x, _y)) break;
        for(char _y = y - 1; _y >= 0; _y --) if(has_enemy( x, _y, ROOK, QUEEN, t)) goto Portugal; else if(!empty(x, _y)) break;
        for(char _x = x + 1; _x <  8; _x ++) if(has_enemy(_x,  y, ROOK, QUEEN, t)) goto Portugal; else if(!empty(_x, y)) break;
        for(char _x = x - 1; _x >= 0; _x --) if(has_enemy(_x,  y, ROOK, QUEEN, t)) goto Portugal; else if(!empty(_x, y)) break;
        // Bishop
        // for(double __a = pi/4; __a < pi*2; __a += pi/2){ // might need to be " - pi/4"
        //     int _xs = round(cos(__a));
        //     int _ys = round(sin(__a));
        //     int _x = x, _y = y;
        //     for(int i = 0; i < 12; i ++){
        //         if(_x > 8 || _x < 0 || _y > 8 || _y < 0) break;
                
        //         _x += _xs; _y += _ys;
                
        //         // tsq(_x, _y);

                
        //         if(has_enemy(_x, _y, BISHOP, QUEEN, t)) 
        //             goto Portugal; 
        //         if(!empty(_x, _y)) 
        //             break;

        //     }

        // }

        char __x = x;
        for(char _y = y + 1; _y <  8; _y ++){ __x ++; if(has_enemy(__x, _y, BISHOP, QUEEN, t)) goto Portugal; if(!empty(__x, _y)) break; } __x = x;
        for(char _y = y - 1; _y >= 0; _y --){ __x ++; if(has_enemy(__x, _y, BISHOP, QUEEN, t)) goto Portugal; if(!empty(__x, _y)) break; } __x = x; // this line is just wrong. It has no reason to be wrong. It is JUST F****** WRONG!
        for(char _y = y + 1; _y <  8; _y ++){ __x --; if(has_enemy(__x, _y, BISHOP, QUEEN, t)) goto Portugal; if(!empty(__x, _y)) break; } __x = x;
        for(char _y = y - 1; _y >= 0; _y --){ __x --; if(has_enemy(__x, _y, BISHOP, QUEEN, t)) goto Portugal; if(!empty(__x, _y)) break; }
        // Knight
        if(has_enemy(x + 2, y + 1, KNIGHT, NAT, t)) goto Portugal;
        if(has_enemy(x + 2, y - 1, KNIGHT, NAT, t)) goto Portugal;
        if(has_enemy(x - 2, y + 1, KNIGHT, NAT, t)) goto Portugal;
        if(has_enemy(x - 2, y - 1, KNIGHT, NAT, t)) goto Portugal;
        if(has_enemy(x + 1, y + 2, KNIGHT, NAT, t)) goto Portugal;
        if(has_enemy(x - 1, y + 2, KNIGHT, NAT, t)) goto Portugal;
        if(has_enemy(x + 1, y - 2, KNIGHT, NAT, t)) goto Portugal;
        if(has_enemy(x - 1, y - 2, KNIGHT, NAT, t)) goto Portugal;



        _a(x, y, piece->team);
        continue;
        Portugal: // Why not?
        glColor4ub(0xff, 0, 0, 0x7f);
        rect(x * SQ_SIZE, y * SQ_SIZE, SQ_SIZE, SQ_SIZE);
    }

}


void king_draw(int x, int y){
    int a = SQ_SIZE / 2,
        b = a / 2,
        c = a / 3,
        d = b / 2,
        e = d / 2;

    int _x = x + a, 
        _y = y + a;


    rect(_x - d, _y - (b), d * 2, -e);
    rect(_x - e/2, _y - b, e, -c);

    // glBegin(GL_QUAD_STRIP);
    // glVertex2i(_x, _y - b + c);
    // glVertex2i(_x - c, _y - b);
    // glVertex2i(_x + c, _y - b);
    // glVertex2i(_x, _y + c);
    // glEnd();

    // ellipse2(_x,  _y - (b - c / 8), (int) b / 2.8, (int) b / 1.6, 12);
    ellipse2(_x, _y - (b - c),         b / 2, b / 3, 12);

    glBegin(GL_TRIANGLE_STRIP);
    glVertex2i(_x + c, _y + a - c);
    glVertex2i(_x,     _y - a + c);
    glVertex2i(_x - c, _y + a - c);
    glEnd();
}
