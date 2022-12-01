#ifndef ULTI_H
#define ULTI_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>

#include <glfw/glfw3.h>

#include "pieces.h"
#include "umisc.h"

#define WHITE  1
#define BLACK -1

#define EMPTY  0
#define ROOK   1
#define KNIGHT 2
#define BISHOP 3
#define KING   4
#define QUEEN  5
#define PAWN   6
#define NAT    8 // Not A Type  (NAN or Not A Number)

#define MOVE_NOT    0
#define MOVE_ATTACK 1
#define MOVE_ALL    2

extern int width, height, FRAME_COUNT, SQ_SIZE;
extern GLFWwindow* window;
extern Piece board[8][8];

void strfill(char* str, int len, char ch);
void window_repaint_public(char *here);

void board_set2(const char* config);
void board_print();
void board_draw();
byte may_move(byte x, byte y, char team);
void move(Piece* piece, byte x, byte y);

void rect(int x, int y, int w, int h);
void sq(byte x, byte y);
void line(int x, int y, int x2, int y2);
void ellipse(int x, int y, double r, double res);
void ellipse2(int x, int y, double rx, double ry, double res);

void ucolor(byte col);

void debug(Piece* piece);
void tsq(byte x, byte y);

typedef struct Move {
    byte x, y;
    bool exists;
} Move;

extern Move possible_moves[28];
extern int move_count;

void add_possible_move(Move move);
void clear_possible_moves();

extern uCommand curr_command;
extern bool unread_command;

extern char commands[MAX_COMMAND_COUNT][MAX_COMMAND_SIZE];
extern Value values[MAX_COMMAND_COUNT];

extern char current_command[MAX_COMMAND_SIZE];
extern char current_args[MAX_COMMAND_SIZE]; 
extern Value current_value;

void config_init();
Value parse2(char* cmd, char* args);

void console_init();
// void console_exec(uCommand* command);
void console_exec(Value val);

char console_color(int _color);
void console_error(char* text);


#endif
