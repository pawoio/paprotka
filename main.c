
#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include <GL/glut.h>



void render(void);
void keyboard(unsigned char c,int x, int y);
void mouse(int button, int state, int x, int y);
void barnsleyFern( unsigned long iter);
void count(int diceThrow, float* x0, float* y0, float* x1, float* y1);
long int i =0;
int p1=85,p2=7,p3=7,p4=1;
int width, hight;
int iterations=100;

void fern(long int, long int, long int,long int);

int main(int argc, char**argv)
{
    //unsigned long num;

    // printf("Enter number of iterations : ");
    // scanf("%ld",&num);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    width =hight= 500;
    glutInitWindowSize(width,hight);
    glutCreateWindow("paprotka");


    glutDisplayFunc(render);

    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    glutMainLoop();






    // barnsleyFern(500,num);



    return 0;
}

void keyboard(unsigned char c, int x, int y)
{
    if(c == 27)
        exit(0);
    if(c == 'a')
    {
        printf("introduce 4 numbers which sum to 100 after spacebar :");
        scanf("%d %d %d %d",&p1,&p2,&p3,&p4);
        //iterations+=1000;
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
void putPixel(double x, double y) {


        printf("%lf, %lf",x, y);

        glVertex2d(x, y);


}
void mouse(int button, int state, int x, int y)
{
    if(button == GLUT_RIGHT_BUTTON)
    {
        /*if(iterations >= 100000) iterations-=100000;
        else if (iterations == 0) iterations=0;
        else if (iterations <= 1000) iterations-=100;
        else if(iterations <= 20000) iterations-=1000;
        else iterations-=10000;

        if (iterations <= 0) iterations=0;*/

    }
    if(button == GLUT_LEFT_BUTTON)
    {
        /*if(iterations > 100000) iterations+=100000;
        else if(iterations >= 20000) iterations+=10000;
        else if (iterations >= 1000) iterations+=1000;
        else iterations+=100;*/
        //glutDisplayFunc(render);
    }
}
void test(long int x) {

    printf("-----%ld-----%ld&&&&&", x,i);

}

void render(void)
{
    ++i;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glBegin(GL_POINTS);
    glColor3f(0,1,0);
    fern(iterations, p1, (p1+p2), p1+p2+p3);
    sleep(1);

    glEnd();
    //glFlush();
    glutSwapBuffers();
}

void barnsleyFern( unsigned long iter){

    float x0=0,y0=0,x1,y1;
    int diceThrow;
    time_t t;
    srand((unsigned)time(&t));

    while(iter>0){
        diceThrow = rand()%100;
        //count(diceThrow,&x0,&y0,&x1,&y1);
        if(diceThrow<p4){
            x1 = 0;
            y1 = 0.16*y0;
        }

        else if(diceThrow>=p4 && diceThrow<=p3){
            x1 = -0.15*x0 + 0.28*y0;
            y1 = 0.26*x0 + 0.24*y0 + 0.44;
        }

        else if(diceThrow>=(p4+p3) && diceThrow<=(p4+p3+p2)){
            x1 = 0.2*x0 - 0.26*y0;
            y1 = 0.23*x0 + 0.22*y0 + 1.6;
        }

        else{
            x1 = 0.85*x0 + 0.04*y0;
            y1 = -0.04*x0 + 0.85*y0 + 1.6;
        }

        glVertex2f(x1/2.6558 ,y1/5.01-1);

        x0 = x1;
        y0 = y1;

        iter--;
    }

}
/*void count(int diceThrow, float* x0, float* y0, float* x1, float* y1)
{
    if(diceThrow<p4){
        *x1 = 0;

        *y1 = 0.16 * (*y0);
    }

    else if(diceThrow>=p4 && diceThrow<=p3){
        *x1 = -0.15*(*x0) + 0.28*(*y0);
        *y1 = 0.26*(*x0) + 0.24*(*y0) + 0.44;
    }

    else if(diceThrow>=(p4+p3) && diceThrow<=(p4+p3+p2)){
        *x1 = 0.2*(*x0) - 0.26*(*y0);
        *y1 = 0.23*(*x0) + 0.22*(*y0) + 1.6;
    }

    else{
        *x1 = 0.85*(*x0) + 0.04*(*y0);
        *y1 = -0.04*(*x0) + 0.85*(*y0) + 1.6;
    }

}*/