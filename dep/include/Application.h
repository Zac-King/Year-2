#pragma once
#include "stdio.h"
#define GLM_FORCE_PURE
#include <glm/fwd.hpp>
#include <glm\glm.hpp>
#include <glm\ext.hpp>
#include <gl_core_4_4.h>
#include <GLFW/glfw3.h>  
#include <iostream>
#include <fstream>
#include <string>

using glm::mat4;
using glm::vec4;
using glm::vec3;
using glm::vec2;
class Application
{

public:
	Application(GLfloat*, GLfloat *, GLushort *);
	int startup();
	int update();
	void draw();
	void shutdown();
	std::string LoadShader(std::string);
private:

	struct Time
	{
		unsigned int currentTime;
		unsigned int deltaTime;
	};

	//end setup matrices
	unsigned int projectionMatrixID;
	unsigned int viewMatrixID ;
	unsigned int modelMatrixID;
	unsigned int timeFloatID;
	GLfloat * cube_vertices;
	GLfloat * cube_colors;
	GLushort * cube_elements;

	Time Time;
	GLuint timeID; //id to send to shader	
	GLFWwindow *window;
	mat4 m_view;
	mat4 m_projection;
	mat4 m_model;
	GLuint m_VAO, m_VBO, m_IBO, m_CBO, m_shader; 
};