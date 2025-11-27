#include <Windows.h>
#include <Ole2.h>

#include <gl/GL.h>
#include <gl/GLU.h>
#include <gl/glut.h>

#include <Kinect.h>

#include <iostream>

float screenWidth = 960;
float screenHeight = 640;



static void drawPoint()
{
	glColor3f(1, 0, 0);
	glPointSize(10.0f);
	glBegin(GL_POINTS);
	glVertex2i(screenWidth / 2, screenHeight / 2);
	glEnd();
}


static void display()
{

	glutPostRedisplay();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	drawPoint();

	glutSwapBuffers();
}


static void init()
{
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	gluOrtho2D(0, screenWidth, screenHeight, 0);
}

int main(int argc, char** argv) 
{

	IKinectSensor* sensor = nullptr;

	HRESULT hr = GetDefaultKinectSensor(&sensor);
	if (FAILED(hr) || !sensor)
	{
		std::cout << "No sensor object\n";
		return -1;
	}

	BOOLEAN isConnected = FALSE;
	sensor->get_IsAvailable(&isConnected);

	if (!isConnected)
	{
		std::cout << "No Kinect device connected\n";
	}
	else
	{
		std::cout << "Kinect device IS connected\n";
	}

	sensor->Release();
	return 0;


	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

	glutInitWindowSize(static_cast<int>(screenWidth), static_cast<int>(screenHeight));
	
	glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH) - screenWidth)/2, (glutGet(GLUT_SCREEN_HEIGHT) - screenHeight) /2);

	glutCreateWindow("OpenGL Window");
	

	init();
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}
