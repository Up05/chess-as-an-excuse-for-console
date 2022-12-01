#include "ulti.h"


Piece board[8][8];

Move possible_moves[28] = {{0, 0, false}};

void board_set2(const char* config){
    int i = 0, x = 0, y = 0;
    char team = 0;
    
    for(int _x = 0; _x < 8; _x ++)
        for(int _y = 0; _y < 8; _y ++)
            board[_x][_y].type = EMPTY;


    while(config[i] != '\0'){
        switch(config[i]){
            case '_':
                x ++;
                break;
            case '/':
                y ++;
                x = 0;
                break;
            case 'w':
                team = 1;
                break;
            case 'b': 
                team = -1;
                break;
            default:
                switch(config[i]){
                    case 'p':
                        board[x][y] = pawn_new(x, y);
                        break;
                    case 'k':
                        board[x][y] = knight_new(x, y);
                        break;
                    case 'R':
                        board[x][y] = rook_new(x, y);
                        break;
                    case 'B':
                        board[x][y] = bishop_new(x, y);
                        break;
                    case 'Q':
                        board[x][y] = queen_new(x, y);
                        break;
                    case 'K':
                        board[x][y] = king_new(x, y);
                        break;
                }
                board[x][y].team = team;
                board[x][y].double_moved_on_turn = -7;
                board[x][y].has_moved = false;
                x ++;
            }
        
        i ++;

    }


}


void board_print(){
    for(int y = 0; y < 8; y ++){
        for(int x = 0; x < 8; x ++){


            if(board[x][y].type == 0) printf("  ");
            else
                printf("%d ", board[x][y].type);
        }
        puts("");
    }
} 

void board_draw(){


    glColor3ub(0x77, 0x77, 0x77);

    // for(int x = 0; x < 8; x ++)
    //     line(x * SQ_SIZE, 0, x * SQ_SIZE, height);

    // for(int y = 0; y < 8; y ++)
    //     line(0, y * SQ_SIZE, width, y * SQ_SIZE);

    for(int y = 0; y < 8; y ++){
        for(int x = 0; x < 8; x ++){
            if((x + y) % 2 == 0)
                ucolor(0x88);
            else 
                ucolor(0xcc);

            int _x = x * SQ_SIZE, 
                _y = y * SQ_SIZE;

            rect(_x, _y, SQ_SIZE, SQ_SIZE);

            byte col;
            if(board[x][y].team == WHITE) col = 0xee;
            else                          col = 0x4f;
            
            ucolor(0); // shadow color
            switch(board[x][y].type){
                case PAWN:
                    pawn_draw(_x + 1, _y + 1);
                    ucolor(col);
                    pawn_draw(_x, _y);
                    break;
                case KNIGHT:
                    knight_draw(_x + 1, _y + 1);
                    ucolor(col);
                    knight_draw(_x, _y);
                    break;
                case ROOK:
                    rook_draw(_x + 1, _y + 1);
                    ucolor(col);
                    rook_draw(_x, _y);
                    break;
                case BISHOP:
                    bishop_draw(_x + 1, _y + 1);
                    ucolor(col);
                    bishop_draw(_x, _y);
                    break;
                case QUEEN:
                    queen_draw(_x + 1, _y + 1);
                    ucolor(col);
                    queen_draw(_x, _y);
                    break;
                case KING:
                    king_draw(_x + 1, _y + 1);
                    ucolor(col);
                    king_draw(_x, _y);
                    break;
                
            }

        }
    }


}


byte may_move(byte x, byte y, char team){
    byte may = MOVE_NOT;
    if(x < 0 || x > 7 || y < 0 || y > 7) return MOVE_NOT;
    if(board[x][y].type != EMPTY && board[x][y].team == team) return MOVE_NOT;
    if(board[x][y].type == EMPTY)
        may = MOVE_ALL;
    else if(board[x][y].team != team)
        may = MOVE_ATTACK;
    return may;
}

void move(Piece* piece, byte x, byte y){
    board[x][y] = board[piece->x][piece->y];

    board[x][y].has_moved = true;
    if(piece->type == PAWN && piece->y + piece->team*2 == y)
        board[x][y].double_moved_on_turn = move_count % 256;
    
    if(piece->type == PAWN && piece->x != x && board[piece->x + (x - piece->x)][piece->y].double_moved_on_turn == move_count % 256 - 1)
        board[piece->x + (x - piece->x)][piece->y].type = EMPTY;
    
    board[piece->x][piece->y].type = EMPTY;
    board[x][y].x = x;
    board[x][y].y = y;

    if(board[x][y].type == PAWN)
        promotion(&board[x][y]);

    move_count ++;
}
