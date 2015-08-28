#include "stdio.h"
#include <gl_core_4_4.h>
#include <GLFW/glfw3.h>
#include <Gizmos.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

using glm::vec3;
using glm::vec4;
using glm::mat4;

int main()
{
	if (glfwInit() == false)	// pg 1
		return -1;

	GLFWwindow * window = glfwCreateWindow(1280, 720, "Computer Graphics", nullptr, nullptr);
	if (window == nullptr)
	{
		glfwTerminate();
		return -2;
	}
	
	glfwMakeContextCurrent(window);	
	if (ogl_LoadFunctions() == ogl_LOAD_FAILED)	
	{
		glfwDestroyWindow(window);
		glfwTerminate();
		return -3;
	}



	auto major = ogl_GetMajorVersion();		
	auto minor = ogl_GetMinorVersion();		
	printf_s("GL: %i.%i\n", major, minor);	
	glClearColor(0.25f, 0.25f, 0.25f, 1);	// Color (RGBA)
	glEnable(GL_DEPTH_TEST);

	// Creates Camera/3D space
	Gizmos::create();
	mat4 view = glm::lookAt(vec3(10, 10, 10), vec3(0), vec3(0, 1, 0));
	mat4 projection = glm::perspective(glm::pi<float>() * 0.25f, 16 / 9.f, 0.1f, 1000.f);


	while (glfwWindowShouldClose(window) == false &&
		glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		Gizmos::clear();					// take out old
		Gizmos::addTransform(glm::mat4(1)); // Make the changes
		vec4 white(1);
		vec4 black(0, 0, 0, 1);

		for (int i = 0; i < 21; ++i)
		{
			Gizmos::addLine(vec3(-10 + i, 0, 10), vec3(-10 + i, 0, -10), i == 10 ? white : black);
			Gizmos::addLine(vec3(10, 0, -10 + i), vec3(-10, 0, -10 + i), i == 10 ? white : black);
		}
		// Posisition // Rad // Rows // Columns // Color

		Gizmos::addSphere(vec3(0.0, 0.0, 0.0), 1.4f, 30, 30, vec4(0.75f, 0.35f, 0.25f, 1));	// Sun		// @Origin
		Gizmos::addSphere(vec3(1.8, 0.0, 0.0), 0.2f, 10, 10, vec4(0.25f, 0.28f, 0.25f, 1));	// Mercury	// x out 1.8
		Gizmos::addSphere(vec3(2.7, 0.0, 0.0), 0.6f, 10, 10, vec4(0.45f, 0.28f, 0.25f, 1)); // Venus	// x out 2.7
		Gizmos::addSphere(vec3(3.9, 0.0, 0.0), 0.4f, 10, 10, vec4(0.15f, 0.25f, 0.35f, 1)); // Earth	// x out 3.9
		Gizmos::addSphere(vec3(4.7, 0.0, 0.0), 0.3f, 10, 10, vec4(0.65f, 0.18f, 0.15f, 1)); // Mars		// x out 4.7

		Gizmos::addArcRing(vec3(0, 0, 0), 0, 1.79f, 1.8f, 4, 60, vec4(1, 1, 1, 1));	// Mercury/	ring
		Gizmos::addArcRing(vec3(0, 0, 0), 0, 2.69f, 2.7f, 4, 60, vec4(1, 1, 1, 1));	// Venus/	ring
		Gizmos::addArcRing(vec3(0, 0, 0), 0, 3.89f, 3.9f, 4, 60, vec4(1, 1, 1, 1));	// Earth/	ring
		Gizmos::addArcRing(vec3(0, 0, 0), 0, 4.69f, 4.7f, 4, 60, vec4(1, 1, 1, 1));	// Mars/	ring

		Gizmos::draw(projection * view);	// Draw the new stuff
		

		glfwSwapBuffers(window);	
		glfwPollEvents();			
	}
	

	Gizmos::destroy();
	glfwDestroyWindow(window);	
	glfwTerminate();
	return 0;
}