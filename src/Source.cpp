#include "Application.h"

int main()
{
	GLfloat cube_vertices[] =
	{
		// front
		-1.0, -1.0, 1.0,
		1.0, -1.0, 1.0,
		1.0, 1.0, 1.0,
		-1.0, 1.0, 1.0,
		// back
		-1.0, -1.0, -1.0,
		1.0, -1.0, -1.0,
		1.0, 1.0, -1.0,
		-1.0, 1.0, -1.0,
	};

	GLfloat cube_colors[] = {
		// front colors
		1.0, 0.0, 0.0,
		0.0, 1.0, 0.0,
		0.0, 0.0, 1.0,
		1.0, 1.0, 1.0,
		// back colors
		1.0, 0.0, 0.0,
		0.0, 1.0, 0.0,
		0.0, 0.0, 1.0,
		1.0, 1.0, 1.0,
	};

	/* init_resources */
	GLushort cube_elements[] = {
		// front
		0, 1, 2,
		2, 3, 0,
		// top
		1, 5, 6,
		6, 2, 1,
		// back
		7, 6, 5,
		5, 4, 7,
		// bottom
		4, 0, 3,
		3, 7, 4,
		// left
		4, 5, 1,
		1, 0, 4,
		// right
		3, 2, 6,
		6, 7, 3,
	};

	char string[] = { 'h','e','l','\0' };
	int vs = sizeof(cube_vertices)/sizeof(GLfloat);
	
	GLfloat* v = cube_vertices;	
	GLfloat* c = cube_colors;
	GLushort* e = cube_elements;

	
	
	int size = sizeof(int);
	int nums[] = {1,2,3,4};
	GLfloat glnums[] = { 1.f,2.f,3.f};

	GLfloat *iter = glnums;
	int value;
	int * numnew = new int[1000];
	while (*iter != NULL)
	{		
		value = *iter;
		int size = sizeof(GLfloat);
		iter = iter + sizeof(GLfloat)/sizeof(GLfloat*);
	}

	/*Application * app = new Application(c, v, e);
	if (app->startup())
		while (app->update())
			app->draw();
	app->shutdown();*/

	return 0;
}

