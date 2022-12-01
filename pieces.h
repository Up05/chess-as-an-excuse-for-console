#define byte unsigned char

typedef struct Piece {
    byte x, y;
    byte type;
    
    char team;
    bool has_moved;
    short double_moved_on_turn; // will need to cast the current turn to byte, I guess...

} Piece;

Piece pawn_new(byte x, byte y);
bool pawn_check_move(Piece* pawn, byte x, byte y);
void pawn_draw(int x, int y);
void pawn_show_possible_moves(Piece* piece);
void promotion(Piece* pawn);

Piece knight_new(byte x, byte y);
bool knight_check_move(Piece* pawn, byte x, byte y);
void knight_draw(int x, int y);
void knight_show_possible_moves(Piece* piece);

Piece rook_new(byte x, byte y);
bool rook_check_move(Piece* pawn, byte x, byte y);
void rook_draw(int x, int y);
void rook_show_possible_moves(Piece* piece);

Piece bishop_new(byte x, byte y);
bool bishop_check_move(Piece* pawn, byte x, byte y);
void bishop_draw(int x, int y);
void bishop_show_possible_moves(Piece* piece);

Piece queen_new(byte x, byte y);
bool queen_check_move(Piece* pawn, byte x, byte y);
void queen_draw(int x, int y);
void queen_show_possible_moves(Piece* piece);

Piece king_new(byte x, byte y);
bool king_check_move(Piece* pawn, byte x, byte y);
void king_draw(int x, int y);
void king_show_possible_moves(Piece* piece);