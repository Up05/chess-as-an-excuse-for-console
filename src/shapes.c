#include "ulti.h"

void rect(int x, int y, int w, int h){
    
    int x2 = x + w,
        y2 = y + h; 

    glBegin(GL_QUADS);
        glVertex3i(x,  y,  0);
        glVertex3i(x2, y,  0);
        glVertex3i(x2, y2, 0);
        glVertex3i(x,  y2, 0);
    glEnd();
}

void sq(byte x, byte y){
    glColor4ub(0, 0xff, 0, 0x6f);

    int _x = x * SQ_SIZE;
    int _y = y * SQ_SIZE;

    glBegin(GL_QUADS);
        glVertex3i(_x,           _y,  0);
        glVertex3i(_x + SQ_SIZE, _y,  0);
        glVertex3i(_x + SQ_SIZE, _y + SQ_SIZE, 0);
        glVertex3i(_x,           _y + SQ_SIZE, 0);
    glEnd();

    add_possible_move((Move) {x, y, true});
}


void line(int x, int y, int x2, int y2){
    glBegin(GL_LINE_STRIP);
        glVertex2i(x, y);
        glVertex2i(x2, y2);
    glEnd();

}

void ellipse(int x, int y, double r, double res){
    int vertN = res + 2; 
    // it's supposed to be 1, but it works with 2 and not 1, so I'll just forget about it. I'm pretty sure this is how the mathematicians do it.
    double TWO_PI = 6.283185;

    int* verts = malloc(sizeof(int) * vertN * 2);

    verts[0] = x;
    verts[1] = y;

    for (int i = 1; i < vertN; i ++){
        verts[i * 2]     = (int) round(x + ( r * cos( i * TWO_PI / res ) ));
        verts[i * 2 + 1] = (int) round(y + ( r * sin( i * TWO_PI / res ) ));
    }

    glPushMatrix();
    glBegin(GL_TRIANGLE_FAN);
    for(int i = 0; i < vertN * 2; i += 2)
        glVertex2d(verts[i], verts[i + 1]);
    glEnd();
    glPopMatrix();

    free(verts);
}

void ellipse2(int x, int y, double rx, double ry, double res){
    int vertN = res + 2; 
    // it's supposed to be 1, but it works with 2 and not 1, so I'll just forget about it. I'm pretty sure this is how the mathematicians do it.
    double TWO_PI = 6.283185;

    int* verts = malloc(sizeof(int) * vertN * 2);

    verts[0] = x;
    verts[1] = y;

    for (int i = 1; i < vertN; i ++){
        verts[i * 2]     = (int) round(x + ( rx * cos( i * TWO_PI / res ) ));
        verts[i * 2 + 1] = (int) round(y + ( ry * sin( i * TWO_PI / res ) ));
    }

    glPushMatrix();
    glBegin(GL_TRIANGLE_FAN);
    for(int i = 0; i < vertN * 2; i += 2)
        glVertex2d(verts[i], verts[i + 1]);
    glEnd();
    glPopMatrix();

    free(verts);
}

void ucolor(byte col){
    glColor3ub(col, col, col);
}

void tsq(byte x, byte y){ // test square
    glColor4ub(0xff, 0, 0xff, 0x40);
    rect(x * SQ_SIZE, y * SQ_SIZE, SQ_SIZE, SQ_SIZE);

}