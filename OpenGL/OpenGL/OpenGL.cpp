// OpenGL.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <stdio.h>
#include <stdarg.h>
#include <math.h>
#include <GL/glut.h>
#include <gl/GL.h>
#include <time.h>
#include <Stdlib.h>


#define DisplayWidth 800
#define DisplayHeight 600 //высота окна
#define PI 3.141592
#define DropsCount 30 // количество капель



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
	for (float radius = (DisplayHeightNew > DisplayWidthNew ? DisplayWidthNew / 80 * 6 : DisplayHeightNew / 10), i = 0; i <= 2 * PI; i += 0.05)
	{
		glVertex2f(radius * cos(i) + DisplayWidthNew / 8 * 6.5, radius * sin(i) + DisplayHeightNew / 6 * 5);
	}
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
