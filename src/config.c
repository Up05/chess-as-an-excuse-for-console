#include "ulti.h"
#include "ulti.h"


static FILE* file;

static void config_read();
static void config_read2();

void config_init(){

    for(int i = 0; i < MAX_COMMAND_COUNT; i ++)
        values->integer = 0;

    file = fopen("C:\\Users\\Augustas\\Desktop\\c_C\\chess\\config.cfg", "r");

    // config_read();
    config_read2();
}

SplitStrings split(char* string, int length, char delimiter){
    SplitStrings out;
    out.count = 0;
    out.strings = malloc(length);
    // for(int i = 0; i < length; i ++)
    //     out.strings[0][i] = '\0';
    int pi = 0; // past i
    for(int i = 0; i < length; i ++){
        if(string[i] == delimiter || string[i] == '\0'){
            for(int j = pi; j < i - 1; j ++)
                out.strings[out.count][j] = string[j];
            out.count ++;
            pi = i;
            if(string[i] == '\0') {
                return out;
            }
        }
    }

    return out;
}

Value parse_command_arguments(char* string, int offset){
    // puts(string);
    
    // SplitStrings vals = split(string, MAX_COMMAND_SIZE, ' ');
    Value value;

    char* ptoken = NULL;
    char* token = strtok(string, " ");
    if(token == NULL) value.integer = 0;

    int i = 0;
    while(token != NULL){
        switch(i){
            case 0:
                value.integer = atoi(token);
                break;
            case 1:
                value.color.g = atoi(token);
                break;
            case 2:
                value.color.b = atoi(token);
                break;
            case 3:
                value.color.a = atoi(token);
                break;
        }

        token = strtok(NULL, " ");
        i ++;
    }

    // printf("value.integer: %d\n", value.integer);
    // printf("value.colors: [%d, %d, %d, %d]\n", value.color.r, value.color.g, value.color.b, value.color.a);

    return value;
}

Value parse2(char* cmd, char* args){
    Value value;
    value.integer = -1;

    if(strcmp(cmd, "board_config") == 0){ // if it's board config command thingy!
        if(args[0] == '\0' || args[0] == '\n') {
            console_error("board_config needs arguments, please read the config.cfg file for more information!");
            value.integer = -1;
            return value;
        }
        board_set2(args);
            
    } else
        value = parse_command_arguments(args, 0);
    
    return value;
}



#include <commands.h>
#ifdef SOMETHING_RANDOM
static void config_read(){
    char args[MAX_COMMAND_SIZE];
    int line = 1, j = 0; // +/-  int i, j;
    int arg_start = -1;
    bool comment = false;
    char ch;
    do {
        ch = fgetc(file);

        if(ch == '\n') {
            // if(j < 2) line --;
            line ++; j = 0;
            comment = false;

            if(arg_start != -1){
                if(line != cmd_board_config + 1)
                    values[line] = parse_command_arguments(args, 0);
                else {
                    board_set2(args);
                    window_repaint_public("config#read()");
                }
            }
            arg_start = -1;
            for(int i = 0; i < MAX_COMMAND_SIZE; i ++)
                args[i] = '\0';
            continue;
        }

        if(comment) continue;
        if(ch == ' ' && arg_start == -1) {
            arg_start = j;
            continue;
        }
        if(ch == '#' && j < 2) {
            comment = true;
            line --;
            continue;
        }

        if(arg_start != -1)
            args[j - arg_start] = ch;
        else 
            commands[line][j] = ch;
        
        j ++;

    
    } while(ch != EOF);
    fclose(file);
}
#endif

static void config_read2(){
    char arg[MAX_COMMAND_SIZE];
    char cmd[MAX_COMMAND_SIZE];
    strfill(cmd, MAX_COMMAND_SIZE, '\0');
    strfill(arg, MAX_COMMAND_SIZE, '\0');
    byte state = 0; // COMMAND(0), ARGS(1); 

    int i_arg = 0, i_cmd = 0;
    int type = -1;

    bool comment = false;

    char ch;
    do {
        ch = fgetc(file);

        if(ch == '#'){
            comment = true;
            continue;
        }

        if(ch == '\n' || ch == ';' || ch == ' '){
            state = 0; type = -1;
            i_arg = 0; i_cmd = 0;
            if(comment){
                comment = false;
                continue;
            }
            strfill(cmd, MAX_COMMAND_SIZE, '\0');
            strfill(arg, MAX_COMMAND_SIZE, '\0');

            if(ch == ' '){
                state = 1;
            } else {
                for(int i = 0; i < MAX_COMMAND_COUNT; i ++){
                    if(strcmp(commands[i], cmd) == 0){ // strcmp returns 0 when TRUE (strs are eq)
                        values[i] = parse_command_arguments(arg, 0);
                        type = i;

                        strcpy_s(current_command, MAX_COMMAND_SIZE, cmd);
                        strcpy_s(current_args, MAX_COMMAND_SIZE, arg);
                        console_exec(parse2(current_command, current_args));
                    }
                }

            }
        } else if(!comment) {
            if(state == 0){
                cmd[i_cmd] = ch;


                i_cmd ++;
            } else if(state == 1){
                arg[i_arg] = ch;


                i_arg ++;
            }
        }

    } while(ch != EOF);
    fclose(file);
}