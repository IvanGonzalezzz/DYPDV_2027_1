
//#include <windows.h> //the windows include file, required by all windows applications
#include <GL/glut.h> //the glut file for windows operations
                     // it also includes gl.h and glu.h for the openGL library calls
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#define PI 3.1415926535898 
//Variables 
double bx, by, bdx, bdy;        
double ball_speed;

GLfloat paddleWidth = 3.f;
GLfloat paddleHeight = 20.f;
GLfloat paddleSpeed = 1.5f;
double p1y, p2y;
double p1x = 8.0;
double p2x = 152.0;

bool upPressed = false, downPressed = false;
bool wPressed = false, sPressed = false;

int score1 = 0, score2 = 0;

GLint circle_points = 100; 
void MyCircle2f(GLfloat centerx, GLfloat centery, GLfloat radius){
  GLint i;
  GLdouble angle;
  glBegin(GL_POLYGON); 
  for (i = 0; i < circle_points; i++) {    
    angle = 2*PI*i/circle_points; 
    glVertex2f(centerx+radius*cos(angle), centery+radius*sin(angle)); 
  } 
  glEnd();
}

GLfloat RadiusOfBall = 3.;
// Draw the ball, centered at the origin
void draw_ball() {
  glColor3f(0.6,0.3,0.);
  MyCircle2f(0.,0.,RadiusOfBall);
  
}

void draw_paddle(double x, double y) {
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_QUADS);
        glVertex2f((GLfloat)(x - paddleWidth / 2), (GLfloat)(y - paddleHeight / 2));
        glVertex2f((GLfloat)(x + paddleWidth / 2), (GLfloat)(y - paddleHeight / 2));
        glVertex2f((GLfloat)(x + paddleWidth / 2), (GLfloat)(y + paddleHeight / 2));
        glVertex2f((GLfloat)(x - paddleWidth / 2), (GLfloat)(y + paddleHeight / 2));
    glEnd();
}

void update_paddles() {
    // Jugador 1: W (arriba) / S (abajo)
    if (wPressed) p1y += paddleSpeed;
    if (sPressed) p1y -= paddleSpeed;
 
    // Jugador 2: flecha arriba / flecha abajo
    if (upPressed) p2y += paddleSpeed;
    if (downPressed) p2y -= paddleSpeed;
 
    // Limitar paletas para que no salgan de la pantalla (mundo 0-120 en Y)
    double halfP = paddleHeight / 2.0;
    if (p1y - halfP < 0) p1y = halfP;
    if (p1y + halfP > 120) p1y = 120 - halfP;
    if (p2y - halfP < 0) p2y = halfP;
    if (p2y + halfP > 120) p2y = 120 - halfP;
}

void reset_ball(int direccion) {
    bx = 80.0;
    by = 60.0;
    bdx = direccion;
    bdy = (rand() % 2 == 0) ? 1 : -1;
}

void update_ball() {
    bx += bdx * ball_speed;
    by += bdy * ball_speed;
 
    // Rebote arriba / abajo
    if (by + RadiusOfBall >= 120) {
        by = 120 - RadiusOfBall;
        bdy = -1;
    } else if (by - RadiusOfBall <= 0) {
        by = RadiusOfBall;
        bdy = 1;
    }
 
    double halfP = paddleHeight / 2.0;
 
    // Colision conjugador 1 (izquierda)
    if (bdx < 0 &&
        bx - RadiusOfBall <= p1x + paddleWidth / 2 &&
        bx - RadiusOfBall >= p1x - paddleWidth / 2 &&
        by >= p1y - halfP && by <= p1y + halfP)
    {
        bdx = 1;
        bx = p1x + paddleWidth / 2 + RadiusOfBall;
    }
 
    // Colision con jugador 2 (derecha)
    if (bdx > 0 &&
        bx + RadiusOfBall >= p2x - paddleWidth / 2 &&
        bx + RadiusOfBall <= p2x + paddleWidth / 2 &&
        by >= p2y - halfP && by <= p2y + halfP)
    {
        bdx = -1;
        bx = p2x - paddleWidth / 2 - RadiusOfBall;
    }
 
    // Score para el jugador 2
    if (bx - RadiusOfBall < 0) {
        score2++;
        printf("Score para Jugador 2 \nScores: J1: %d  J2: %d\n", score1, score2);
        reset_ball(1);
    }
 
    // Score para el jugador 1 
    if (bx + RadiusOfBall > 160) {
        score1++;
        printf("Score para Jugador 1 \nScores: J1: %d  J2: %d\n", score1, score2);
        reset_ball(-1);
    }
}


void Display(void)
{
  // swap the buffers
  glutSwapBuffers(); 
  //clear all pixels with the specified clear color
  glClear(GL_COLOR_BUFFER_BIT);

  update_paddles();
  update_ball();
  glLoadIdentity();

  glPushMatrix();
  glTranslatef((GLfloat)bx, (GLfloat)by, 0.f);
  draw_ball();
  glPopMatrix();

  draw_paddle(p1x, p1y);
  draw_paddle(p2x, p2y);
  glutPostRedisplay(); 

  

}


void reshape (int w, int h)
{
   // on reshape and on startup, keep the viewport to be the entire size of the window
   glViewport (0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();

   // keep our logical coordinate system constant
   gluOrtho2D(0.0, 160.0, 0.0, 120.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity ();

}

void keyDown(unsigned char key, int x, int y) {
    if (key == 'w' || key == 'W') wPressed = true;
    if (key == 's' || key == 'S') sPressed = true;
}

void keyUp(unsigned char key, int x, int y) {
    if (key == 'w' || key == 'W') wPressed = false;
    if (key == 's' || key == 'S') sPressed = false;
}

void specialKeyDown(int key, int x, int y) {
    if (key == GLUT_KEY_UP) upPressed = true;
    if (key == GLUT_KEY_DOWN) downPressed = true;
}

void specialKeyUp(int key, int x, int y) {
    if (key == GLUT_KEY_UP) upPressed = false;
    if (key == GLUT_KEY_DOWN) downPressed = false;
}

void init(void){
    glClearColor(0.0,0.8,0.0,1.0);

    bx = 80.0;
    by = 60.0;
    bdx = 1.0;
    bdy = 1.0;

    p1y = 60.0;
    p2y = 60.0;

    ball_speed = 1.5;
}


int main(int argc, char* argv[])
{

  glutInit( & argc, argv );
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize (320, 240);   
  glutCreateWindow("Pong");
  init();
  glutDisplayFunc(Display);
  glutReshapeFunc(reshape);
  glutKeyboardFunc(keyDown);
  glutKeyboardUpFunc(keyUp);
  glutSpecialFunc(specialKeyDown);
  glutSpecialUpFunc(specialKeyUp);
  glutMainLoop();

  return 1;
}