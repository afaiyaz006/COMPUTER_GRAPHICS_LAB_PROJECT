

#include <windows.h>  // for MS Windows
#include <GL/glut.h>  // GLUT, include glu.h and gl.h
#include <tuple>
#include <iostream>
#include "bedroom.h"
#ifdef __bedroom3d__
using namespace std;
/* Global variables */
char title[] = "Bedroom";
float rotateX = 0;
float moveX = 0;

static GLfloat v_cube[8][3] =
{
    {0.0, 0.0, 0.0}, //0
    {0.0, 0.0, 1.0}, //1
    {1.0, 0.0, 1.0}, //2
    {1.0, 0.0, 0.0}, //3
    {0.0, 1.0, 0.0}, //4
    {0.0, 1.0, 1.0}, //5
    {1.0, 1.0, 1.0}, //6
    {1.0, 1.0, 0.0}  //7
};

static GLubyte quadIndices[6][4] =
{
    {0, 1, 2, 3}, //bottom
    {4, 5, 6, 7}, //top
    {5, 1, 2, 6}, //front
    {0, 4, 7, 3}, // back is clockwise
    {2, 3, 7, 6}, //right
    {1, 5, 4, 0}  //left is clockwise
};


void drawunitcube(
    tuple<float,float,float,float> bottom_color=make_tuple(0,1,0,1),
    tuple<float, float, float, float> top_color=make_tuple(0,1,0,1),
    tuple<float, float, float, float> front_color=make_tuple(1,1,0,1),
    tuple<float, float, float, float> back_color=make_tuple(1,0,1,1),
    tuple<float, float, float, float> right_color=make_tuple(0,1,1,1),
    tuple<float, float, float, float> left_color=make_tuple(1,0,0,1)

)
{


    float colors[6][4] = {
        get<0>(bottom_color),get<1>(bottom_color),get<2>(bottom_color),get<3>(bottom_color),
        get<0>(top_color),get<1>(top_color),get<2>(top_color),get<3>(top_color),
        get<0>(front_color),get<1>(front_color),get<2>(front_color),get<3>(front_color),
        get<0>(back_color),get<1>(back_color),get<2>(back_color),get<3>(back_color),
        get<0>(right_color),get<1>(right_color),get<2>(right_color),get<3>(right_color),
        get<0>(left_color),get<1>(left_color),get<2>(left_color),get<3>(left_color),
    };
    glBegin(GL_QUADS);
    for (GLint i = 0; i < 6; i++)
    {
        //glColor3fv(&colors[i][0]); // You can use colors array for each face
        glColor4fv(colors[i]);
        glVertex3fv(&v_cube[quadIndices[i][0]][0]);
        glVertex3fv(&v_cube[quadIndices[i][1]][0]);
        glVertex3fv(&v_cube[quadIndices[i][2]][0]);
        glVertex3fv(&v_cube[quadIndices[i][3]][0]);
    }
    glEnd();
}
/* Initialize OpenGL Graphics */
void initGL() {
    glClearColor(0.804, 0.961, 0.98, 0.812); // Set background color to black and opaque
    glClearDepth(1.0f);                   // Set background depth to farthest
    glEnable(GL_DEPTH_TEST);   // Enable depth testing for z-culling
    glDepthFunc(GL_LEQUAL);    // Set the type of depth-test
    glShadeModel(GL_SMOOTH);   // Enable smooth shading
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Nice perspective corrections
}




/* Handler for window-repaint event. Called back when the window first appears and
   whenever the window needs to be re-painted. */
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color and depth buffers
    glMatrixMode(GL_MODELVIEW);     // To operate on model-view matrix
    glLoadIdentity();                 // Reset the model-view matrix

    glRotatef(rotateX, 0, 1, 0);
    glTranslatef(0, 0, moveX);

    //house
    glPushMatrix();
    glTranslatef(-0.5f, -0.5f, -8.0f);  
    glScalef(10, 10, 10);
    glTranslatef(-0.5f, 0.0f, 0.0f);
    //glScalef(1, -0.5f, 7.0f);
    drawunitcube();
    glPopMatrix();


    //bichana
    glPushMatrix();
    glTranslatef(-1.5, -0.5f, -3.0f);
    glScalef(1.0f, 0.3f, 1.0f);
    drawunitcube(
        make_tuple(1, 0.957, 0.549,1),
        make_tuple(1, 0.957, 0.549, 1),
        make_tuple(1, 0.957, 0.549, 1),
        make_tuple(1, 0.957, 0.549, 1),
        make_tuple(1, 0.957, 0.549, 1),
        make_tuple(1, 0.957, 0.549, 1)

    );
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-1.5f, -0.2f, -3.0f);
    glScalef(1.0f, 0.15f, 1.0f);

    drawunitcube(
        make_tuple(0.8, 0.337, 1,1),
        make_tuple(0.8, 0.337, 1,1),
        make_tuple(0.8, 0.337, 1,1),
        make_tuple(0.8, 0.337, 1,1),
        make_tuple(0.8, 0.337, 1,1),
        make_tuple(0.8, 0.337, 1,1)

    );
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(-1.5f, -0.05f, -3.0f);
    glScalef(0.35f, 0.05f, 0.2f);
    
    drawunitcube(
        make_tuple(0.984, 0.953, 1,1),
        make_tuple(0.984, 0.953, 1, 1),
        make_tuple(0.984, 0.953, 1, 1),
        make_tuple(0.984, 0.953, 1, 1),
        make_tuple(0.984, 0.953, 1, 1),
        make_tuple(0.984, 0.953, 1, 1)


    );
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-1.2f, -0.05f, -3.0f);
    glScalef(0.35f, 0.05f, 0.2f);

    drawunitcube(
        make_tuple(0.984, 0.953, 1, 1),
        make_tuple(0.984, 0.953, 1, 1),
        make_tuple(0.984, 0.953, 1, 1),
        make_tuple(0.984, 0.953, 1, 1),
        make_tuple(0.984, 0.953, 1, 1),
        make_tuple(0.984, 0.953, 1, 1)


    );
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-1.0f, -0.05f, -3.0f);
    glScalef(0.35f, 0.05f, 0.2f);

    drawunitcube(
        make_tuple(0.984, 0.953, 1, 1),
        make_tuple(0.984, 0.953, 1, 1),
        make_tuple(0.984, 0.953, 1, 1),
        make_tuple(0.984, 0.953, 1, 1),
        make_tuple(0.984, 0.953, 1, 1),
        make_tuple(0.984, 0.953, 1, 1)


    );
    glPopMatrix();



    glutSwapBuffers();  // Swap the front and back frame buffers (double buffering)
}
void myKeyboardFunc(unsigned char key, int x, int y)
{

    switch (key)
    {
        case 'd':
            std::cout << "Rotate: " << rotateX << '\n';
            rotateX = rotateX + 10.0f;
            break;
        case 'a':
            std::cout << "Rotate: " << rotateX << '\n';
           
            rotateX = rotateX - 10.0f;
            break;
        case 'w':
            std::cout << "Move: " << moveX << '\n';
            moveX = moveX + 0.1f;
            break;
        case 's':
            std::cout << "Move: " << moveX << '\n';
            moveX = moveX - 0.1f;
            break;
        default:
            break;
    }
    glutPostRedisplay();

}
/* Handler for window re-size event. Called back when the window first appears and
   whenever the window is re-sized with its new width and height */
void reshape(GLsizei width, GLsizei height) {  // GLsizei for non-negative integer
    // Compute aspect ratio of the new window
    if (height == 0) height = 1;                // To prevent divide by 0
    GLfloat aspect = (GLfloat)width / (GLfloat)height;

    // Set the viewport to cover the new window
    glViewport(0, 0, width, height);

    // Set the aspect ratio of the clipping volume to match the viewport
    glMatrixMode(GL_PROJECTION);  // To operate on the Projection matrix
    glLoadIdentity();             // Reset
    // Enable perspective projection with fovy, aspect, zNear and zFar
    gluPerspective(45.0f, aspect, 0.1f, 100.0f);
}


/* Main function: GLUT runs as a console application starting at main() */

int main(int argc, char** argv) {
    glutInit(&argc, argv);            // Initialize GLUT
    glutInitDisplayMode(GLUT_DOUBLE); // Enable double buffered mode
    glutInitWindowSize(640, 480);   // Set the window's initial width & height
    glutInitWindowPosition(50, 50); // Position the window's initial top-left corner
    glutCreateWindow(title);          // Create window with the given title
    glutKeyboardFunc(myKeyboardFunc);
    glutDisplayFunc(display);       // Register callback handler for window re-paint event
    glutReshapeFunc(reshape);       // Register callback handler for window re-size event
    
    initGL();                       // Our own OpenGL initialization
    glutMainLoop();                 // Enter the infinite event-processing loop
    return 0;
}
#endif