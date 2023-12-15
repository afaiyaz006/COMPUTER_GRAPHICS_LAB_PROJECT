#include <windows.h>  // for MS Windows
#include <GL/glut.h>  // GLUT, include glu.h and gl.h
#include<tuple>   // for representing color code
#include<iostream>
#include "bedroom.h"
#ifdef __bedroom__

using namespace std;
/* Global variables */
char title[] = "Bedroom";
int refreshMills = 15;        // refresh interval in milliseconds
int angleFanBlade = 0.0f;
bool fanSwitch = true;
int colorIndex = 0;
bool lightOn = true;
bool ambientLight = true;
bool diffuseLight = true;
bool specularLight = true;

float colors[10][4] = {
                {0.376f, 1.0f, 0.647f, 0.0f},//default color
                {1.0f, 1.0f, 0.0f, 0.0f},//yellow
                {1.0f, 0.0f, 1.0f, 0.0f},//purple
                {1.0f, 0.5f, 0.0f, 0.0f},//orange
                {0.0f, 1.0f, 1.0f, 1.0f},//light blue
                {1.0f, 1.0f, 1.0f, 0.0f},//red
                {1.0f, 1.0f, 1.0f, 0.0f},//white
                {1, 0.816, 0.576,0.0},//ada color
};

float daynight[2][4] = {
    {0, 1, 0.969,1},
    {0.0f,0.0f,0.0f,0.0f}
};


int day = 0;
int floorIndex = 0;

/* Initialize OpenGL Graphics */
void initGL() {
    glClearColor(colors[colorIndex][0], colors[colorIndex][1], colors[colorIndex][2], colors[colorIndex][3]); // Set background color to black and opaque
    glClearDepth(1.0f);                   // Set background depth to farthest
    glEnable(GL_DEPTH_TEST);   // Enable depth testing for z-culling
    glDepthFunc(GL_LEQUAL);    // Set the type of depth-test
    glShadeModel(GL_SMOOTH);   // Enable smooth shading
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Nice perspective corrections
}
float rot = 0;

static GLfloat v_cube[8][3] =
{
    {-1.0, -1.0, -1.0}, ///point index 0
    {-1.0, -1.0, 1.0}, ///point index 1
    {1.0, -1.0, 1.0}, ///point index 2
    {1.0, -1.0, -1.0}, ///point index 3
    {-1.0, 1.0, 1.0}, ///point index 4
    {-1.0, 1.0, -1.0}, ///5
    {1.0, 1.0, -1.0},///6
    {1.0, 1.0, 1.0}  ///7
};

static GLubyte c_Indices[6][4] =
{
    {1,2,7,4},
    {2,3,6,7},
    {4,6,3,0},
    {4,5,0,1},
    {4,7,6,5},
    {0,3,2,1}
};
static void getNormal3p
(GLfloat x1, GLfloat y1, GLfloat z1, GLfloat x2, GLfloat y2, GLfloat z2, GLfloat x3, GLfloat y3, GLfloat z3)
{
    GLfloat Ux, Uy, Uz, Vx, Vy, Vz, Nx, Ny, Nz;

    Ux = x2 - x1;
    Uy = y2 - y1;
    Uz = z2 - z1;

    Vx = x3 - x1;
    Vy = y3 - y1;
    Vz = z3 - z1;

    Nx = Uy * Vz - Uz * Vy;
    Ny = Uz * Vx - Ux * Vz;
    Nz = Ux * Vy - Uy * Vx;

    glNormal3f(Nx, Ny, Nz);
}
void light()
{
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    GLfloat light_position[] = { -7.0,-1.0, 1.0, 1.0 };
    GLfloat light_ambient[] = { 0.2, 0.2, 0.2, 1.0 };
    GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat no_light[] = { 0.0,0.0,0.0,0.0 };
    
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    if (ambientLight && lightOn) {
        glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    }
    else { 
        glLightfv(GL_LIGHT0, GL_AMBIENT, no_light); 
    }
    if (diffuseLight && lightOn) {
        glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    }
    else { 
        glLightfv(GL_LIGHT0, GL_DIFFUSE, no_light);
    }
    if (specularLight && lightOn) { 
        glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    }
    else { 
        glLightfv(GL_LIGHT0, GL_SPECULAR, no_light); 
    }

}


void draw_cube(
    tuple<float, float, float, float> top_color,
    tuple<float, float, float, float> bottom_face_color,
    tuple<float, float, float, float> front_face_color,
    tuple<float, float, float, float> back_face_color,
    tuple<float, float, float, float> left_face_color,
    tuple<float, float, float, float> right_face_color
)
{
    GLfloat v_cube_color[8][4] = {
        { get<0>(top_color), get<1>(top_color), get<2>(top_color), get<3>(top_color) },
        { get<0>(bottom_face_color), get<1>(bottom_face_color), get<2>(bottom_face_color), get<3>(bottom_face_color) },
        { get<0>(front_face_color), get<1>(front_face_color), get<2>(front_face_color), get<3>(front_face_color) },
        { get<0>(back_face_color), get<1>(back_face_color), get<2>(back_face_color), get<3>(back_face_color) },
        { get<0>(left_face_color), get<1>(left_face_color), get<2>(left_face_color), get<3>(left_face_color) },
        { get<0>(right_face_color), get<1>(right_face_color), get<2>(right_face_color), get<3>(right_face_color) }
    };
   
     light();


    glBegin(GL_QUADS);
    for (GLint i = 0; i < 6; i++)
    {
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, v_cube_color[i]);
        GLfloat white[] = { 1.0f, 1.0f, 1.0f, 1.0f };
        glMaterialfv(GL_FRONT, GL_SPECULAR, white);
        glMaterialf(GL_FRONT, GL_SHININESS, 80.0f);
        for (GLint j = 0; j < 4; j++)
        {
            glVertex3fv(v_cube[c_Indices[i][j]]);
        }
    }
    glEnd();
   
    glDisable(GL_LIGHTING);
    glDisable(GL_LIGHT0);
}



/*
void draw_cube(tuple<float, float, float, float> top_color,
    tuple<float, float, float, float> bottom_face_color,
    tuple<float, float, float, float> front_face_color,
    tuple<float, float, float, float> back_face_color,
    tuple<float, float, float, float> left_face_color,
    tuple<float, float, float, float> right_face_color) {

    //function to draw  a unit cube given color of its six side
    // Render a unit cube consisting of 6 quads


    glBegin(GL_QUADS);                // Begin drawing the color cube
    // Top face (y = 1.0f)
    // Define vertices in counter-clockwise (CCW) order with normal pointing out
    glColor3f(get<0>(top_color), get<1>(top_color), get<1>(top_color));
    glVertex3f(1.0f, 1.0f, -1.0f);
    glVertex3f(-1.0f, 1.0f, -1.0f);
    glVertex3f(-1.0f, 1.0f, 1.0f);
    glVertex3f(1.0f, 1.0f, 1.0f);

    // Bottom face (y = -1.0f)
    glColor3f(get<0>(bottom_face_color), get<1>(bottom_face_color), get<2>(bottom_face_color));
    glVertex3f(1.0f, -1.0f, 1.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);

    // Front face  (z = 1.0f)
    glColor3f(get<0>(front_face_color), get<1>(front_face_color), get<2>(front_face_color));
    glVertex3f(1.0f, 1.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, 1.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);

    // Back face (z = -1.0f)
    glColor3f(get<0>(back_face_color), get<1>(back_face_color), get<2>(back_face_color));
    glVertex3f(1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f, 1.0f, -1.0f);
    glVertex3f(1.0f, 1.0f, -1.0f);

    // Left face (x = -1.0f)
    glColor3f(get<0>(left_face_color), get<1>(left_face_color), get<2>(left_face_color));
    glVertex3f(-1.0f, 1.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, -1.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);

    // Right face (x = 1.0f)
    glColor3f(get<0>(right_face_color), get<1>(right_face_color), get<2>(right_face_color));
    glVertex3f(1.0f, 1.0f, -1.0f);
    glVertex3f(1.0f, 1.0f, 1.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);
    glEnd();  // End of drawing color-cube
}*/

/* Handler for window-repaint event. Called back when the window first appears and
   whenever the window needs to be re-painted. */
void display() {
    glClearColor(colors[colorIndex][0], colors[colorIndex][1], colors[colorIndex][2], colors[colorIndex][3]);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color and depth buffers
    glMatrixMode(GL_MODELVIEW);     // To operate on model-view matrix

    ///Khola door
    glLoadIdentity();                 // Reset the model-view matrix
    glTranslatef(5.0f, -0.1f, -9.0f);  // Move right and into the screen
    glScalef(0.85f / 2, 0.85f, 0.01f);
    /*draw_cube(
        make_tuple(0.667f, 1.0f, 0.957f, 0.0f),//Blue
        make_tuple(0.667f, 1.0f, 0.957f, 0.0f),//Blue
        make_tuple(0.667f, 1.0f, 0.957f, 0.0),//red
        make_tuple(0.667f, 1.0f, 0.957f, 0.0f),//Black
        make_tuple(0.667f, 1.0f, 0.957f, 0.0f),//Blue
        make_tuple(0.667f, 1.0f, 0.957f, 0.0f)//Orange
    );*/
    draw_cube(
        make_tuple(daynight[day][0], daynight[day][1], daynight[day][2], daynight[day][3]),//day
        make_tuple(daynight[day][0], daynight[day][1], daynight[day][2], daynight[day][3]),//day
        make_tuple(daynight[day][0], daynight[day][1], daynight[day][2], daynight[day][3]),//day
        make_tuple(daynight[day][0], daynight[day][1], daynight[day][2], daynight[day][3]),//day
        make_tuple(daynight[day][0], daynight[day][1], daynight[day][2], daynight[day][3]),//day
        make_tuple(daynight[day][0], daynight[day][1], daynight[day][2], daynight[day][3])//day
    );


    glLoadIdentity();                 // Reset the model-view matrix
    glTranslatef(4.2f, -0.1f, -9.0f);  // Move right and into the screen
    glScalef(0.85f / 2, 0.85f, 0.1f);

    draw_cube(
        make_tuple(0.27f, 0.275f, 0.267f, 0.0f),//brown
        make_tuple(0.667f, 1.0f, 0.957f, 0.0),//brown
        make_tuple(0.82f, 0.412f, 0.0f, 0.0f),//brown
        make_tuple(0.27f, 0.275f, 0.267f, 0.0f),//brown
        make_tuple(0.27f, 0.275f, 0.267f, 0.0f),//brown
        make_tuple(0.27f, 0.275f, 0.267f, 0.0f)//brown
    );
    glLoadIdentity();                 // Reset the model-view matrix
    glTranslatef(4.0f, -0.1f, -9.0f);  // Move right and into the screen
    glScalef(0.1f, 0.1f, 0.1f);

    draw_cube(
        make_tuple(0.27f, 0.275f, 0.267f, 0.0f),//brown
        make_tuple(0.27f, 0.275f, 0.267f, 0.0f),//brown
        make_tuple(0.27f, 0.275f, 0.267f, 0.0f),//brown
        make_tuple(0.27f, 0.275f, 0.267f, 0.0f),//brown
        make_tuple(0.27f, 0.275f, 0.267f, 0.0f),//brown
        make_tuple(0.27f, 0.275f, 0.267f, 0.0f)//brown
    );


    //render bed er body 
    glLoadIdentity();
    glTranslatef(-2.0f, -1.0f, -7.0f);
    glScalef(1.0f, 0.3f, 2.5f);
    draw_cube(
        make_tuple(1.0f, 1.0f, 0.0f, 0.0f), //yellow

        make_tuple(1.0f, 1.0f, 0.0f, 0.0f), //yellow

        make_tuple(1.0f, 1.0f, 0.0f, 0.0f), //yellow

        make_tuple(1.0f, 1.0f, 0.0f, 0.0f), //yellow

        make_tuple(1.0f, 1.0f, 0.0f, 0.0f), //yellow

        make_tuple(1.0f, 1.0f, 0.0f, 0.0f) //yellow
    );

    //render bed er bottom
    glLoadIdentity();
    glTranslatef(-2.0f, -1.5f, -7.0f);
    glScalef(1.0f, 0.3f, 2.5f);


    draw_cube(
        make_tuple(0.38f, 0.102f, 0.0f, 0.0f), //brown
        make_tuple(0.38f, 0.102f, 0.0f, 0.0f), //brown
        make_tuple(0.38f, 0.102f, 0.0f, 0.0f), //brown
        make_tuple(0.38f, 0.102f, 0.0f, 0.0f), //brown
        make_tuple(0.38f, 0.102f, 0.0f, 0.0f), //brown
        make_tuple(0.38f, 0.102f, 0.0f, 0.0f) //brown

    );


    //render bed balish
    glLoadIdentity();
    glTranslatef(-2.0f, -1.5f, -7.0f);
    glScalef(0.5f, 0.3f, -0.5f);
    glTranslatef(0.1f, 2.0f, 1.5f);


    draw_cube(

        make_tuple(0.675f, 0.498f, 1.0f, 0.0f), //violet
        make_tuple(0.675f, 0.498f, 1.0f, 0.0f), //violet
        make_tuple(0.675f, 0.498f, 1.0f, 0.0f), //violet
        make_tuple(0.675f, 0.498f, 1.0f, 0.0f), //violet
        make_tuple(0.675f, 0.498f, 1.0f, 0.0f), //violet
        make_tuple(0.675f, 0.498f, 1.0f, 0.0f) //violet


    );




    //deyal er design
    glLoadIdentity();
    glTranslatef(0.0f, -1.0f, -20.0f);
    glScalef(20.0f, 1.0f, 1.0f);
    draw_cube(
        make_tuple(1.0f, 0.5f, 0.0f, 0.0f), //orange
        make_tuple(1.0f, 0.5f, 0.0f, 0.0f), //orange
        make_tuple(1.0f, 0.5f, 0.0f, 0.0f), //orange
        make_tuple(1.0f, 0.5f, 0.0f, 0.0f), //orange
        make_tuple(1.0f, 0.5f, 0.0f, 0.0f), //orange
        make_tuple(1.0f, 0.5f, 0.0f, 0.0f)  //orange
    );

    //floor er design
    glLoadIdentity();
    glTranslatef(0.0f, -2.0f, -20.0f);
    glScalef(20.0f, 5.0f, 1.0f);
    glTranslatef(0.0f, -1.0f, 0.0f);

    /*draw_cube(
        make_tuple(2.0f, 0.5f, 1.0f, 0.0f), //lilac
        make_tuple(2.0f, 0.5f, 1.0f, 0.0f), //lilac
        make_tuple(2.0f, 0.5f, 1.0f, 0.0f), //lilac
        make_tuple(2.0f, 0.5f, 1.0f, 0.0f), //lilac
        make_tuple(2.0f, 0.5f, 1.0f, 0.0f), //lilac
        make_tuple(2.0f, 0.5f, 1.0f, 0.0f)  //lilac
    );*/
    draw_cube(
        make_tuple(colors[floorIndex][0], colors[floorIndex][1], colors[floorIndex][2], colors[floorIndex][3]),

        make_tuple(colors[floorIndex][0], colors[floorIndex][1], colors[floorIndex][2], colors[floorIndex][3]),

        make_tuple(colors[floorIndex][0], colors[floorIndex][1], colors[floorIndex][2], colors[floorIndex][3]),

        make_tuple(colors[floorIndex][0], colors[floorIndex][1], colors[floorIndex][2], colors[floorIndex][3]),

        make_tuple(colors[floorIndex][0], colors[floorIndex][1], colors[floorIndex][2], colors[floorIndex][3]),


        make_tuple(colors[floorIndex][0], colors[floorIndex][1], colors[floorIndex][2], colors[floorIndex][3])
    );


    //wadrobe
    glLoadIdentity();
    glTranslatef(2.0f, 0.0f, -9.0f);
    glScalef(1.0f, 2.3f, 1.0f);
    glTranslatef(2.0f, 0.0f, -9.0f);
    draw_cube(
        make_tuple(1.0f, 0.302f, 0.0f, 0.0f),///khoyeri color
        make_tuple(1.0f, 0.302f, 0.0f, 0.0f),
        make_tuple(1.0f, 0.302f, 0.0f, 0.0f),
        make_tuple(1.0f, 0.302f, 0.0f, 0.0f),
        make_tuple(1.0f, 0.302f, 0.0f, 0.0f),
        make_tuple(1.0f, 0.302f, 0.0f, 0.0f)
    );
    glLoadIdentity();
    glTranslatef(4.0f, 0.0f, -9.0f);
    glScalef(0.01f, 2.3f, 1.0f);
    glTranslatef(1.0f, 0.0f, -9.0f);
    draw_cube(
        make_tuple(0.129, 0.125, 0.125, 0.0),
        make_tuple(0.129, 0.125, 0.125, 0.0),
        make_tuple(0.129, 0.125, 0.125, 0.0),
        make_tuple(0.129, 0.125, 0.125, 0.0),
        make_tuple(0.129, 0.125, 0.125, 0.0),
        make_tuple(0.129, 0.125, 0.125, 0.0)
    );
    glLoadIdentity();
    glTranslatef(3.0f, 0.0f, -9.0f);
    glScalef(0.01f, 2.3f, 1.0f);
    glTranslatef(1.0f, 0.0f, -9.0f);
    draw_cube(
        make_tuple(0.129, 0.125, 0.125, 0.0),
        make_tuple(0.129, 0.125, 0.125, 0.0),
        make_tuple(0.129, 0.125, 0.125, 0.0),
        make_tuple(0.129, 0.125, 0.125, 0.0),
        make_tuple(0.129, 0.125, 0.125, 0.0),
        make_tuple(0.129, 0.125, 0.125, 0.0)
    );


    //Janala
    glLoadIdentity();
    glTranslatef(-3.0f, 0.0f, -9.0f);
    glScalef(-0.6f, 0.6f, 0.01f);
    glTranslatef(2.0f, 2.5f, -5.0f);
    draw_cube(
        make_tuple(daynight[day][0], daynight[day][1], daynight[day][2], daynight[day][3]),//day
        make_tuple(daynight[day][0], daynight[day][1], daynight[day][2], daynight[day][3]),//day
        make_tuple(daynight[day][0], daynight[day][1], daynight[day][2], daynight[day][3]),//day
        make_tuple(daynight[day][0], daynight[day][1], daynight[day][2], daynight[day][3]),//day
        make_tuple(daynight[day][0], daynight[day][1], daynight[day][2], daynight[day][3]),//day
        make_tuple(daynight[day][0], daynight[day][1], daynight[day][2], daynight[day][3])//day
    );
    glLoadIdentity();
    glTranslatef(-3.0f, 0.0f, -9.0f);
    glScalef(-0.03f, 0.6f, 0.01f);
    glTranslatef(43.5f, 2.5f, -5.0f);
    draw_cube(
        make_tuple(0.122f, 0.141f, 0.141f, 0.0f), //black
        make_tuple(0.122f, 0.141f, 0.141f, 0.0f), //black
        make_tuple(0.122f, 0.141f, 0.141f, 0.0f), //black
        make_tuple(0.122f, 0.141f, 0.141f, 0.0f), //black
        make_tuple(0.122f, 0.141f, 0.141f, 0.0f), //black
        make_tuple(0.122f, 0.141f, 0.141f, 0.0f) //black

    );
    glLoadIdentity();
    glTranslatef(-3.0f, 0.0f, -9.0f);
    glScalef(-0.03f, 0.6f, 0.01f);
    glTranslatef(31.5f, 2.5f, -5.0f);

    draw_cube(
        make_tuple(0.122f, 0.141f, 0.141f, 0.0f), //black
        make_tuple(0.122f, 0.141f, 0.141f, 0.0f), //black
        make_tuple(0.122f, 0.141f, 0.141f, 0.0f), //black
        make_tuple(0.122f, 0.141f, 0.141f, 0.0f), //black
        make_tuple(0.122f, 0.141f, 0.141f, 0.0f), //black
        make_tuple(0.122f, 0.141f, 0.141f, 0.0f) //black

    );


    //render paposh
    glLoadIdentity();
    glTranslatef(-2.0f, -1.5f, -7.0f);
    glScalef(0.5f, 0.01f, -0.5f);
    glTranslatef(5.3f, 2.0f, -5.5f);


    draw_cube(
        make_tuple(0.961f, 0.039f, 0.039f, 0.878f), //red
        make_tuple(0.961f, 0.039f, 0.039f, 0.878f), //red
        make_tuple(0.961f, 0.039f, 0.039f, 0.878f), //red
        make_tuple(0.961f, 0.039f, 0.039f, 0.878f), //red
        make_tuple(0.961f, 0.039f, 0.039f, 0.878f), //red
        make_tuple(0.961f, 0.039f, 0.039f, 0.878f) //red
    );

    glLoadIdentity();
    glTranslatef(-2.0f, -1.5f, -7.0f);
    glScalef(0.4f, 0.01f, -0.5f);
    glTranslatef(5.3f, 2.0f, -5.5f);


    draw_cube(
        make_tuple(0, 0.271, 0.008, 0.98), //green
        make_tuple(0, 0.271, 0.008, 0.98), //green
        make_tuple(0, 0.271, 0.008, 0.98), //green
        make_tuple(0, 0.271, 0.008, 0.98), //green
        make_tuple(0, 0.271, 0.008, 0.98), //green
        make_tuple(0, 0.271, 0.008, 0.98) //green

    );


    //render simple trunk
    glLoadIdentity();
    glTranslatef(-2.0f, -1.5f, -7.0f);
    glScalef(0.5f, 0.3f, -0.5f);
    glTranslatef(3.8f, 2.0f, 1.3f);
    draw_cube(
        make_tuple(1.0f, 0.302f, 0.0f, 0.0f), //khoyeri
        make_tuple(1.0f, 0.302f, 0.0f, 0.0f), //khoyeri
        make_tuple(1.0f, 0.302f, 0.0f, 0.0f), //khoyeri
        make_tuple(1.0f, 0.302f, 0.0f, 0.0f), //khoyeri
        make_tuple(1.0f, 0.302f, 0.0f, 0.0f), //khoyeri
        make_tuple(0.282, 0.275, 0.29f, 0.0f)//khoyeri
    );
    glLoadIdentity();
    glTranslatef(-2.0f, -1.5f, -7.0f);
    glScalef(0.5f, 0.01f, -0.5f);
    glTranslatef(3.8f, 50.3f, 1.3f);
    draw_cube(
        make_tuple(0.141, 0.141, 0.137, 0.98), //black
        make_tuple(0.141, 0.141, 0.137, 0.98), //black
        make_tuple(0.141, 0.141, 0.137, 0.98), //black
        make_tuple(0.141, 0.141, 0.137, 0.98), //black
        make_tuple(0.141, 0.141, 0.137, 0.98), //black
        make_tuple(0.141, 0.141, 0.137, 0.98)  //black
    );

    glLoadIdentity();
    glTranslatef(-2.0f, -1.5f, -7.0f);
    glScalef(0.5f, 0.01f, -0.5f);
    glTranslatef(3.8f, 65.0f, 1.3f);
    glScalef(0.1f, 2.0f, 1.0f);
    draw_cube(
        make_tuple(0.141, 0.141, 0.137, 0.98), //black
        make_tuple(0.141, 0.141, 0.137, 0.98), //black
        make_tuple(0.141, 0.141, 0.137, 0.98), //black
        make_tuple(0.141, 0.141, 0.137, 0.98), //black
        make_tuple(0.141, 0.141, 0.137, 0.98), //black
        make_tuple(0.141, 0.141, 0.137, 0.98)  //black
    );

    //render fan
    glLoadIdentity();
    glTranslatef(2.5f, -1.5f, -7.0f);
    glScalef(0.1f, 2.0f, 0.1f);


    draw_cube(
        make_tuple(0.435, 0.451, 0.451, 0.98), //white
        make_tuple(0.435, 0.451, 0.451, 0.98), //white
        make_tuple(0.435, 0.451, 0.451, 0.98), //white
        make_tuple(0.435, 0.451, 0.451, 0.98), //white
        make_tuple(0.435, 0.451, 0.451, 0.98), //white
        make_tuple(0.435, 0.451, 0.451, 0.98) //white


    );
    glLoadIdentity();
    glTranslatef(2.5f, -1.5f, -7.0f);
    glScalef(0.1f, 2.0f, 0.01f);
    glScalef(1.0f, 0.1f, 1.0f);
    glTranslatef(0.3f, 10.0f, 1.0f);
    glScalef(1.0f, 3.0f, 1.0f);
    glTranslatef(-1.0f, -1.0f, 1.0f);
    glTranslatef(-2.0f, 1.0f, 1.0f);
    glRotatef(angleFanBlade, 1, 0, 0);

    draw_cube(
        make_tuple(0.961, 0.961, 0.961, 0.98), //white
        make_tuple(0.808, 0.831, 0.831, 0.98), //white
        make_tuple(0.675, 0.678, 0.678, 0.98), //white
        make_tuple(0.773, 0.851, 0.851, 0.98), //white
        make_tuple(0.855, 0.961, 0.961, 0.98), //white
        make_tuple(0.969, 1, 1, 0.98) //white
    );




    glutSwapBuffers();  // Swap the front and back frame buffers (double buffering)


    ///fan choltase
    if (fanSwitch) {
        angleFanBlade += 10.0f;
    }
    else {
        angleFanBlade += 0.0f;
    }



}



void myKeyboardFunc(unsigned char key, int x, int y)
{

    switch (key) {
    case 'f':
        if (fanSwitch) {
            fanSwitch = false;
            std::cout << "Fan off hoise\n";
        }
        else if (!fanSwitch) {
            fanSwitch = true;
            std::cout << "Fan on hoise.\n";
        }
        break;
    case 'c':
        //cout << colorIndex << '\n';
        colorIndex++;
        colorIndex = colorIndex % 7;
        break;

    case 'd':
        
        if (day == 0) {
            day += 1;
            cout << "Switched to night.\n";
        }
        else if (day == 1) {
            cout << "Switched to day.\n";
            day -= 1;
        }
        break;
    case 'g':
        floorIndex += 1;
        floorIndex = floorIndex % 8;
        break;

    case '1':
        lightOn ^= 1;
        break;
    case '2':
        ambientLight ^= 1;
        break;
    case '3':
        diffuseLight ^= 1;
        break;
    case '4':
        specularLight ^= 1;
        break;
    default:
        break;

    }
    glutPostRedisplay();


}







/* Called back when timer expired [NEW] */
void timer(int value) {
    glutPostRedisplay();      // Post re-paint request to activate display()
    glutTimerFunc(refreshMills, timer, 0); // next timer call milliseconds later
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
    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    glEnable(GL_LIGHTING);
    //light();
    cout << "Press c to change color\nPress f to turn the fan on/off\nPress g to change floor color\nPress d to switch day and night\n1 to toggle light\n2 to toggle ambient light\n3 to toggle diffuse light\n4 to toggle specular light\n";
    glutDisplayFunc(display);       // Register callback handler for window re-paint event
    glutKeyboardFunc(myKeyboardFunc); //keyboard

    glutReshapeFunc(reshape);       // Register callback handler for window re-size event
    initGL();                       // Our own OpenGL initialization
    glutTimerFunc(0, timer, 0);     // First timer call immediately
    glutMainLoop();                 // Enter the infinite event-processing loop
    return 0;
}
#endif