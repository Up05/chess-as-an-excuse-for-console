#define MAX_COMMAND_COUNT 128
#define MAX_COMMAND_SIZE  128

typedef struct uColor {
    byte r;
    byte g;
    byte b;
    byte a;
} uColor;

typedef union Value {
    uColor color;
    int integer;
    // ! char board_config[128]; I'll want to make an exception for this!
} Value;


typedef struct uCommand {
    int type;
    Value value;
} uCommand;

typedef struct SplitStrings {
    int count;

    char** strings;
} SplitStrings;

SplitStrings split(char* string, int length, char delimiter);
Value parse_command_arguments(char* string, int offset);