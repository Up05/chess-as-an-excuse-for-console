#include "ulti.h"
#include "commands.h"

#undef byte
#include <windows.system.threading.h>

char commands[MAX_COMMAND_COUNT][MAX_COMMAND_SIZE] = { // I'll need to redo indexes?
    "help",
    "exit",
    "clear",
    "cls",
    "cfg_reload" // config
    "bd_config", // board
    "something"
};
Value values[MAX_COMMAND_COUNT];


char current_command[MAX_COMMAND_SIZE];
char current_args[MAX_COMMAND_SIZE]; 
Value current_value;
static char board_config_text[MAX_COMMAND_SIZE];


uCommand curr_command;
bool unread_command = false;

#define yo_momma unsigned long int

// static __attribute__((const)) yo_momma hash(char* str) {
//     yo_momma a = 0;
//     for(int i = 0; i < 32; i ++){
//         if(str[i] == '\0' || str[i] == ':' || str[i] == ' ' || str[i] == '\n') break;
//         a += str[i] * i;
//     }
//     return a;
// }


HANDLE hConsole;

char console_color(int _color){
    SetConsoleTextAttribute(hConsole, _color);
}

void console_error(char* text){
    console_color(4);
    puts(text);
    console_color(15);
}


uCommand parse(char* string){
    uCommand command;
    command.type = -1;

    int j;
    for(int i = 0; i < MAX_COMMAND_COUNT; i ++){
        bool matching = true;
        for(j = 0; j < MAX_COMMAND_SIZE; j ++){
            if(string[j] == '\0' || string[j] == ' ' || string[j] == '\n' || string[j] == ';') break;
            if(string[j] != commands[i][j]) {
                matching = false;
                break;
            }
        }
        if(matching){
            // command.type = i;
            break;
        }
    }

    if(strcmp(commands[command.type], "board_config") == 0){ // if it's board config command thingy!
        if(string[j] == '\0' || string[j] == '\n') {
            console_error("board_config needs arguments, please read the config.cfg file for more information!");
            command.value.integer = -1;
            return command;
        }
        puts(board_config_text);
        for(int i = j; i < MAX_COMMAND_SIZE; i ++)
            board_config_text[i - j] = string[i];
            
    } else
        command.value = parse_command_arguments(string, 1);
    

    return command;
}

#undef yo_momma

static DWORD WINAPI input_thread(void* data) { // I wrote the console an hour ago and I can't say I remember how it works WHAT SO EVER...

    while(true){
        char string[MAX_COMMAND_SIZE];

        fgets(string, MAX_COMMAND_SIZE, stdin);
        if(string[0] == ' ')
            for(int i = 1; i < MAX_COMMAND_SIZE; i ++)
                string[i - 1] = string[i];
        // curr_command = parse(string);

        unread_command = true;

        bool args_yet = false;
        for(int i = 0; i < MAX_COMMAND_SIZE; i ++){
            if(i == '\0' || i == '\n' || i == ';') 
                return 0;
            if(args_yet)
                current_args[i] = string[i];
            else 
                if(i == ' ') args_yet = true;
                else current_command[i] = string[i];
        }

        current_value = parse2(current_command, current_args);


    }


  return 0;
}

void console_init(){
    curr_command.type = -1;
    HANDLE thread = CreateThread(NULL, 0, input_thread, NULL, 0, NULL);
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
}

// void console_exec(uCommand* cmd){
void console_exec(Value val){
    
    #define cmp(index, str) (strcmp(commands[index], str) == 0)
    #define cmp2(str1, str2) (strcmp(str1, str2) == 0)
    // if(strcmp(commands[cmd->type], "help") == 0){

    if(cmp2(current_command, "help")){
        puts
            (
                "Ult1's Chess\n\n"
                "Commands: \n"
                "  - help : gives this information\n"
                "  - exit : closes the game\n"
            );
    } else if(cmp2(current_command, "exit")){
        glfwSetWindowShouldClose(window, TRUE);
    } else if(cmp2(current_command, "clear") || cmp2(current_command, "cls")){
        system("cls");
    } else if(cmp2(current_command, "cfg_reload")){
        config_init();
        puts("Configuration file reloaded");
    } else if(cmp2(current_command, "bd_config")){
        if(val.integer != -1) {
            board_set2(board_config_text);
            window_repaint_public("console#exec()");
        }
    } else if(cmp2(current_command, "exit")){
    } else {
        console_error("Invalid command!");
    }


    // if(cmp(cmd->type, "help")){
    //     puts
    //         (
    //             "Ult1's Chess\n\n"
    //             "Commands: \n"
    //             "  - help : gives this information\n"
    //             "  - exit : closes the game\n"
    //         );
    // } else if(cmp(cmd->type, "exit")){
    //     glfwSetWindowShouldClose(window, TRUE);
    // } else if(cmp(cmd->type, "clear") || cmp(cmd->type, "cls")){
    //     system("cls");
    // } else if(cmp(cmd->type, "cfg_reload")){
    //     config_init();
    //     puts("Configuration file reloaded");
    // } else if(cmp(cmd->type, "bd_config")){
    //     if(cmd->value.integer != -1) {
    //         board_set2(board_config_text);
    //         window_repaint_public("console#exec()");
    //     }
    // } else if(cmp(cmd->type, "exit")){
    // } else {
    //     console_error("Invalid command!");
    // }

    #undef cmp
    #undef cmp2

}