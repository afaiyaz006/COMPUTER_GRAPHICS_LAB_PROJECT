#include <windows.h>  // for MS Windows
#include <GL/glut.h>  // GLUT, include glu.h and gl.h
#include<tuple>   // for representing color code
using namespace std;
/* Global variables */
char title[] = "Bedroom";

/* Initialize OpenGL Graphics */
void initGL() {
    glClearColor(0.376f, 1.0f, 0.647f,0.0f); // Set background color to black and opaque
    glClearDepth(1.0f);                   // Set background depth to farthest
    glEnable(GL_DEPTH_TEST);   // Enable depth testing for z-culling
    glDepthFunc(GL_LEQUAL);    // Set the type of depth-test
    glShadeModel(GL_SMOOTH);   // Enable smooth shading
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Nice perspective corrections
}
void draw_cube(tuple<float, float, float, float> top_color,
    tuple<float, float, float, float> bottom_face_color,
    tuple<float, float, float, float> front_face_color,
    tuple<float, float, float, float> back_face_color,
    tuple<float, float, float, float> left_face_color,
    tuple<float, float, float, float> right_face_color) {
    // Render a color-cube consisting of 6 quads with different colors


    glBegin(GL_QUADS);                // Begin drawing the color cube with 6 quads
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
}

/* Handler for window-repaint event. Called back when the window first appears and
   whenever the window needs to be re-painted. */
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color and depth buffers
    glMatrixMode(GL_MODELVIEW);     // To operate on model-view matrix

    ///Khola door
    glLoadIdentity();                 // Reset the model-view matrix
    glTranslatef(5.0f, -0.1f, -9.0f);  // Move right and into the screen
    glScalef(0.85f/2, 0.85f, 0.01f);
    draw_cube(
        make_tuple(0.667f, 1.0f, 0.957f,0.0f),//Blue
        make_tuple(0.667f, 1.0f, 0.957f, 0.0f),//Blue
        make_tuple(0.667f, 1.0f, 0.957f, 0.0),//red
        make_tuple(0.667f, 1.0f, 0.957f, 0.0f),//Black
        make_tuple(0.667f, 1.0f, 0.957f, 0.0f),//Blue
        make_tuple(0.667f, 1.0f, 0.957f, 0.0f)//Orange
    );
    glLoadIdentity();                 // Reset the model-view matrix
    glTranslatef(4.2f, -0.1f, -9.0f);  // Move right and into the screen
    glScalef(0.85f / 2, 0.85f, 0.1f);
    
    draw_cube(
        make_tuple(0.27f, 0.275f, 0.267f,0.0f),//brown
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
        make_tuple(0.38f, 0.102f, 0.0f,0.0f), //brown
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
        
        make_tuple(0.675f, 0.498f, 1.0f,0.0f), //violet
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

    draw_cube(
        make_tuple(2.0f, 0.5f, 1.0f,0.0f), //lilac
        make_tuple(2.0f, 0.5f, 1.0f, 0.0f), //lilac
        make_tuple(2.0f, 0.5f, 1.0f, 0.0f), //lilac
        make_tuple(2.0f, 0.5f, 1.0f, 0.0f), //lilac
        make_tuple(2.0f, 0.5f, 1.0f, 0.0f), //lilac
        make_tuple(2.0f, 0.5f, 1.0f,0.0f)  //lilac
    );

   
    //wadrobe
    glLoadIdentity();
    glTranslatef(2.0f, 0.0f,-9.0f);
    glScalef(1.0f,2.3f, 1.0f);
    glTranslatef(2.0f, 0.0f, -9.0f);
    draw_cube(
        make_tuple(1.0f, 0.302f, 0.0f,0.0f),///khoyeri color
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
        make_tuple(0.129, 0.125, 0.125,0.0),
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
        make_tuple(0.122f, 0.141f, 0.141f, 0.0f), //sky
        make_tuple(0.122f, 0.141f, 0.141f, 0.0f),//sky
        make_tuple(0.816f, 1.0f, 1.0, 0.0f),//sky
        make_tuple(0.122f, 0.141f, 0.141f, 0.0f),//sky
        make_tuple(0.122f, 0.141f, 0.141f, 0.0f),//sky
        make_tuple(0.122f, 0.141f, 0.141f, 0.0f)//sky
    );
    glLoadIdentity();
    glTranslatef(-3.0f, 0.0f, -9.0f);
    glScalef(-0.03f, 0.6f, 0.01f);
    glTranslatef(43.5f, 2.5f, -5.0f);
    draw_cube(
        make_tuple(0.122f, 0.141f, 0.141f,0.0f), //black
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
        make_tuple(0.0f, 0.89f, 0.8f, 0.878f), //cyan
        make_tuple(0.0f, 0.89f, 0.8f, 0.878f), //cyan
        make_tuple(0.0f, 0.89f, 0.8f, 0.878f), //cyan
        make_tuple(0.0f, 0.89f, 0.8f, 0.878f), //cyan
        make_tuple(0.0f, 0.89f, 0.8f, 0.878f), //cyan
        make_tuple(0.0f, 0.89f, 0.8f, 0.878f) //cyan

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
    









    glutSwapBuffers();  // Swap the front and back frame buffers (double buffering)
    


    
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
    glutDisplayFunc(display);       // Register callback handler for window re-paint event
    glutReshapeFunc(reshape);       // Register callback handler for window re-size event
    initGL();                       // Our own OpenGL initialization
    glutMainLoop();                 // Enter the infinite event-processing loop
    return 0;
}