#include "stdio.h"
#include <gl_core_4_4.h>
#include <GLFW/glfw3.h>
#include <Gizmos.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include "GalacticBody.h"

using glm::vec3;
using glm::vec4;
using glm::mat4;

void orbit(vec3 a, vec3 gravCen)
{
	//a.x = cos();
}

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

	float dt = 0;

	// GalacticBodies
	//GalacticBody sun		= GalacticBody(vec3{ 0.0f, 0.0f ,0.0f }, vec3{ 0.0f, 0.0f ,0.0f }, 0);
	//GalacticBody mercury	= GalacticBody(vec3{ 0.5f, 0.0f, 0.0f }, sun.getPos(), 0.01f);
	//GalacticBody venus		= GalacticBody(vec3{ 1.0f, 0.0f, 0.0f }, sun.getPos(), 0.02f);
	//GalacticBody earth		= GalacticBody(vec3{ 1.5f, 0.0f ,0.0f }, sun.getPos(), 0.03f);
	//GalacticBody mars		= GalacticBody(vec3{ 2.0f, 0.0f ,0.0f }, sun.getPos(), 0.04f);
	//GalacticBody jupiter	= GalacticBody(vec3{ 2.5f, 0.0f ,0.0f }, sun.getPos(), 0.05f);

	GalacticBody planet1  = GalacticBody(vec3{ 0.0f, 0.0f ,0.0f }, vec3{ 0.0f, 0.0f ,0.0f }, 0);
	GalacticBody planet2  = GalacticBody(vec3{ 0.5f, 0.0f, 0.0f }, planet1.getPos(), 0.01f);
	GalacticBody planet3  = GalacticBody(vec3{ 1.0f, 0.0f, 0.0f }, planet2.getPos(), 0.02f);
	GalacticBody planet4  = GalacticBody(vec3{ 1.5f, 0.0f ,0.0f }, planet3.getPos(), 0.03f);
	GalacticBody planet5  = GalacticBody(vec3{ 2.0f, 0.0f ,0.0f }, planet4.getPos(), 0.04f);
	GalacticBody planet6  = GalacticBody(vec3{ 2.5f, 0.0f ,0.0f }, planet5.getPos(), 0.05f);
	GalacticBody planet7  = GalacticBody(vec3{ 3.0f, 0.0f ,0.0f }, planet6.getPos(), 0.06f);
	GalacticBody planet8  = GalacticBody(vec3{ 3.5f, 0.0f, 0.0f }, planet7.getPos(), 0.07f);
	GalacticBody planet9  = GalacticBody(vec3{ 4.0f, 0.0f, 0.0f }, planet8.getPos(), 0.08f);
	GalacticBody planet10 = GalacticBody(vec3{ 4.5f, 0.0f ,0.0f }, planet9.getPos(), 0.09f);
	GalacticBody planet11 = GalacticBody(vec3{ 5.0f, 0.0f ,0.0f }, planet10.getPos(), 0.10f);
	GalacticBody planet12 = GalacticBody(vec3{ 5.5f, 0.0f ,0.0f }, planet11.getPos(), 0.11f);

	// Game Loop
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
		
		//sun.Update();
		//mercury.Update();
		//venus.Update();
		//earth.Update();
		//mars.Update();
		//jupiter.Update();
		planet1.Update();
		planet2.Update();
		planet3.Update();
		planet4.Update();
		planet5.Update();
		planet6.Update();
		planet7.Update();
		planet8.Update();
		planet9.Update();
		planet10.Update();
		planet10.Update();
		planet12.Update();


		Gizmos::draw(projection * view);	// Draw the new stuff

		glfwSwapBuffers(window);	
		glfwPollEvents();			
	}
	

	Gizmos::destroy();
	glfwDestroyWindow(window);	
	glfwTerminate();
	return 0;
}