#include "ulti.h"

GLFWwindow* window;
int width = 520, height = 520, FRAME_COUNT = 0, SQ_SIZE = 65;
// static void mouse_position_callback(GLFWwindow* window, double x, double y);
static void mouse_button_callback  (GLFWwindow* window, int button, int action, int mods);
// static void keyboard_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
static void draw();

static Piece* selected = NULL;

int move_count = 0;

int main(){
    puts("Program started!");

    // board_set2("wRkBKQBkR/pppppppp/// K//b pppppp /RkBKQBk ");
    board_set2("_______bB//_b//_wK//b_pppppp_/RkB_QBk_");

    if (!glfwInit())
        return -1;

    window = glfwCreateWindow(width, height, "Chess", NULL, NULL);
    glfwMakeContextCurrent(window);
    // #################################################################

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glOrtho(0, width, height, 0, 1.0, -1.0); // p5 proj mat thing yeap

    // #################################################################
    glfwSetMouseButtonCallback(window, mouse_button_callback);

    // Piece temp = {2, 2, 2, 2, false, 2};
    // king_show_possible_moves(&temp);

    glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    draw();

    config_init();
    console_init();

    while (!glfwWindowShouldClose(window)){
        // glfwSetCursorPosCallback(window, mouse_position_callback);
        // glfwSetKeyCallback(window, keyboard_callback);
        // board_draw();

        

            // puts("###########################################################################################");
            // for(int i = 0; i < 28; i ++){
            //     printf("x: %d, y: %d\n", possible_moves[i].x, possible_moves[i].y);
            // }
            // return 0;

        if(unread_command){
            // console_exec(&curr_command);
            console_exec(current_value);
            unread_command = false;

        }
        

        int tw, th;
        glfwGetWindowSize(window, &tw, &th);
        if(tw != width || th != height){
            width = tw; height = th;
            glViewport(0, 0, width, height);

            // window size update event-ish here
            
            SQ_SIZE = fminl(width, height) / 8;

            glLoadIdentity();
            glOrtho(0, width, height, 0, 1.0, -1.0); // p5 proj mat thing yeap
            glMatrixMode(GL_MODELVIEW);
        }

        FRAME_COUNT ++;
        glfwPollEvents();
        // glfwWaitEvents(); // ! ?????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????
    }

    glfwTerminate();

    // board_print();



    return(0);
}

static void draw(){
    clear_possible_moves();

        board_draw();

        if(selected != NULL){
            glColor4ub(0xee, 0xee, 0x55, 0x44); // col_selected_square
            rect(selected->x * SQ_SIZE, selected->y * SQ_SIZE, SQ_SIZE, SQ_SIZE);

            switch(selected->type){
                case PAWN:
                    pawn_show_possible_moves(selected);
                    break;
                case ROOK:
                    rook_show_possible_moves(selected);
                    break;
                case KNIGHT:
                    knight_show_possible_moves(selected);
                    break;
                case BISHOP:
                    bishop_show_possible_moves(selected);
                    break;
                case KING:
                    king_show_possible_moves(selected);
                    break;
                case QUEEN:
                    queen_show_possible_moves(selected);
                    break;
            }
        }
    glfwSwapBuffers(window);
    
}

void window_repaint_public(char* here){
    draw();    
    // puts(here);
} // ctrl + f  / find usages ... 


static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE){
        double x, y;
        glfwGetCursorPos(window, &x, &y);

        int _x = (int) x / SQ_SIZE, 
            _y = (int) y / SQ_SIZE;

        Piece piece = board[_x][_y];
        // printf("piece: %d, x: %d, y: %d\n", piece.type, _x, _y);
        
        if(piece.type != EMPTY && selected == NULL){
            selected = &board[_x][_y];
            goto draw_label;
        }

        for(int i = 0; i < 28; i ++){
            // printf("x: %d, y: %d\n", possible_moves[i].x, possible_moves[i].y);
            
            if(possible_moves[i].x == _x && possible_moves[i].y == _y){
                move(selected, _x, _y);
                clear_possible_moves();
                selected = NULL;
                goto draw_label;
            }
        }
        // ! else
        selected = NULL;
        clear_possible_moves();
        
        draw_label:

        draw();
        
    }
}


// board
//  maybe It'd be useful to read the board of of a "starting_board.txt" file or smth like that?
// pieces
//   promotion window/gui/selection thing
// check for king


// cl_highlight_possible_moves