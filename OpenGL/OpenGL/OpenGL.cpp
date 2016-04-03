// OpenGL.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <stdio.h>
#include <stdarg.h>
#include <math.h>
#include <Stdlib.h>
#include <GL/glut.h>
#include <gl/GL.h>
#include <time.h>



#define DisplayWidth 800
#define DisplayHeight 600 //высота окна
#define PI 3.141592
#define DropsCount 120 // количество капель


float axisx = 0;
float axisy = 0;
float beacon = 0;
int p = 0;
int v = 0;




int DisplayWidthNew; //новая ширина окна
int DisplayHeightNew; //новая высота окна
void display();
struct drop{
	int x;
	int y;
};
typedef struct drop DROP;
DROP drops[DropsCount];

void display()
{
	glBegin(GL_QUADS);

	glColor3f(0.0, 1.0, 1.0);// синий
	glVertex2f(0.0, 0.0);
	glVertex2f(DisplayWidthNew, 0.0);
	glVertex2f(DisplayWidthNew, DisplayHeightNew / 6);
	glVertex2f(0.0, DisplayHeightNew / 6);
	

	glColor3f(0.26, 0.67, 1.0);// голубой
	glVertex2f(0.0, DisplayHeightNew / 6);
	glVertex2f(DisplayWidthNew, DisplayHeightNew / 6);
	glVertex2f(DisplayWidthNew, DisplayHeightNew);
	glVertex2f(0.0, DisplayHeightNew);
	
	 glEnd();
	 glBegin(GL_QUAD_STRIP);
	 glColor3f(0.6, 0.3, 0.0);
	 glVertex2f(100, 125); 
	 glVertex2f(150, 75);       
	 glVertex2f(350, 125);
	 glVertex2f(300, 75);   
	 glEnd();
	 
	 glBegin(GL_QUAD_STRIP);
	 glColor3f(1.0, 0.0, 1.0);
	 glVertex2f(235, 250);
	 glVertex2f(300, 250);
	 glVertex2f(300, 220);
	 glVertex2f(235, 220);
	 glEnd();
	 glBegin(GL_TRIANGLES);
	 glColor3f(1.0, 1.0, 1.0);
	 glVertex2f(228, 220);
	 glVertex2f(300, 125);
	 glVertex2f(150, 125);
	 glEnd();
	 glBegin(GL_QUAD_STRIP);
	 glColor3f(0.6, 0.2, 0.0);
	 glVertex2f(220, 125);
	 glVertex2f(235, 125);
	 glVertex2f(220, 250);
	 glVertex2f(235, 250);
	 glEnd();
	 



	 
	 


		 
	
	 
	 

	 glBegin(GL_POLYGON);// солнце
	glColor3f(1.0, 1.0, 0.0);// желтый
	if (beacon != -1){
		if (axisy <= 350){
			axisy = axisy + 1;
			axisx = axisx + 2;
			p++;
			if (axisx == 350){
				beacon = -1;
			}
		}
	}
	else{
		if (v <= p){
			axisy = axisy - 1;
			axisx = axisx + 2;
			v++;
		}
	}
	if (v==p)
	{
		beacon = 0;
		axisx = 0;
		axisy = 0;
	}


		
	for (float radius = (DisplayHeightNew > DisplayWidthNew ? DisplayWidthNew / 80 * 6 : DisplayHeightNew / 10), i = 0; i <= 2 * PI; i += 0.1)


	{
		
    



				glVertex2f(radius * cos(i) + DisplayWidthNew / 8 * 6.5 - axisx, radius * sin(i) + DisplayHeightNew / 6 * 5 + axisy);
				
			}
		

	



//for (p = 0; p >= 0; p++){

		

/*
			for (axisy = 100; axisy <= 0; axisy = axisy + 0.1){
				axisx = axisx + 0.2;

			}

			for (axisy = 100; axisy >= 0; axisy = axisy - 0.1){
				axisx = axisx + 0.2;

			}*/
			//axisx = 0;
	//}


	//if (beacon != -1){
	//	if (axisx <= 100){//50

	//		
	//		axisx = axisx + 2;//100
	//		axisy = axisy + 1;//50
	//		v++;
	//		}
	//		else
	//		{
	//			for (int t = 0; t < v; t++) {//50
	//				axisx = axisx + 2;
	//				axisy = axisy - 1; 
	//			}
	//			if (p==0)
	//			{
	//				beacon = -1;
	//			}
	//		}

	//	}

	
	glEnd();
	

	

}
void rain(int numDrops)
{
	glClear(GL_COLOR_BUFFER_BIT);
	display();

	glLineWidth(3);

	glBegin(GL_LINES); //капельки
	glColor3f(0.54, 0.57, 0.51); // серый

	for (int i = 0; i < DropsCount; ++i)
	{
		if (drops[i].x < 0)
			drops[i].x = DisplayWidthNew;
		if (drops[i].y < 0)
			drops[i].y = DisplayHeightNew;

		glVertex2f(drops[i].x, drops[i].y);
		glVertex2f(drops[i].x + 5, drops[i].y + 5);

		drops[i].x -= 15;
		drops[i].y -= 15;
	}
	glEnd();
	glFlush();
	glutTimerFunc(10, rain, 0);
}

void Reshape(int Width, int Height)
{
	if (Height == 0)
	{
		Height = 1;
	}
	
	DisplayWidthNew = Width;
	DisplayHeightNew = Height;
	glViewport(0, 0, (GLsizei)Width, (GLsizei)Height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, (GLdouble)Width, 0.0, (GLdouble)Height);
	display();
	glFlush();
}
void init()
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
}


int main(int argc, char **argv)
{
	srand(time(NULL));
	for (int i = 0; i < DropsCount; ++i)
	{
		drops[i].x = rand() % DisplayWidth;
		drops[i].y = rand() % DisplayHeight;
	}

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(DisplayWidth, DisplayHeight);
	glutCreateWindow("Main window");
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(Reshape);

	glutTimerFunc(200, rain, 0);

	glutMainLoop();

	return 0;
}
