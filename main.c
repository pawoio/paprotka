
#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include <GL/glut.h>




void render(void);
void keyboard(unsigned char c,int x, int y);


void fern(long int , long int ,long int ,long int );
long int p1=85,p2=7,p3=7,p4=1;
long int p12,p123;
int width, hight;
long int iterations=500;
void putPixel(double x, double y);
int main(int argc, char**argv)
{
    //unsigned long num;

   // printf("Enter number of iterations : ");
   // scanf("%ld",&num)
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    width =hight= 500;
    glutInitWindowSize(width,hight);
    glutCreateWindow("paprotka");


    glutDisplayFunc(render);

    glutKeyboardFunc(keyboard);

    glutMainLoop();

    return 0;
}

void keyboard(unsigned char c, int x, int y)
{
    if(c == 27)
        exit(0);
    if(c == 'a')
    {
        printf("introduce 4 numbers which sum to 100 after spacebar :");
        //scanf("%d %d %d %d",&p1,&p2,&p3,&p4);
        glutPostRedisplay();
    }
    if(c == 'd')
    {

        if(iterations >= 100000) iterations-=100000;
        else if (iterations == 0) iterations=0;
        else if (iterations <= 1000) iterations-=100;
        else if(iterations <= 20000) iterations-=1000;
        else iterations-=10000;

        if (iterations <= 0) iterations=0;

        glutPostRedisplay();
    }
    if(c == 'u')
    {

        if(iterations > 100000) iterations+=100000;
        else if(iterations >= 20000) iterations+=10000;
        else if (iterations >= 1000) iterations+=1000;
        else iterations+=100;
        glutPostRedisplay();
    }

}


void render(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
   // gluOrtho2D(0.0, 500.0, 0.0, 500.0);
    glBegin(GL_POINTS);
    glColor3f(0,1,0);
    p12=p1+p2;
    p123=p12+p3;
   // fern(0,p1,p12,p123);
    glVertex2d(0.1,0.2);
    for(int i = 0; i < 50; i++) {
        glVertex2d(i/100, i/50);
    }

    glEnd();
    glFlush();
    glutSwapBuffers();
}


 void putPixel(double x, double y)
{
    printf("%lf %lf",x,y);
    glVertex2d(x, y);
}
