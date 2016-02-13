#define GLM_FORCE_PURE
#include <vector>
#include "stdio.h"
#include <gl_core_4_4.h>
#include <GLFW/glfw3.h> 
#include <glm/fwd.hpp>
#include <glm\glm.hpp>
#include <glm\ext.hpp>
#include <iostream>
#include <fstream>
#include <string>
using glm::vec3;
using glm::vec4;
using glm::mat4;
using namespace std;



#define BUFFER_OFFSET(i) ((char *)NULL + (i))

unsigned int m_VAO, m_VBO, m_IBO;
unsigned int m_shader;

string LoadShader(std::string file)
{
	string line, shader;
	ifstream inFile(file);
	if (inFile.is_open())
		while (getline(inFile, line))
		{
			shader.append(line);
			shader.append("\n");
		}
	inFile.close();
	return shader;
}

void DrawSquare(glm::mat4 translate, unsigned int vbo, unsigned int ibo, unsigned int vao)
{
	unsigned int modelID = glGetUniformLocation(m_shader, "Model");
	glUniformMatrix4fv(modelID, 1, false, glm::value_ptr(translate));
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBindVertexArray(vao); 
	//draw
	glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, BUFFER_OFFSET(0));
	//unbind
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

struct Vertex
{
	float x, y, z ;        //Vertex	 
};

struct Color
{
	float r, g, b, a;
};

int main()
{
	//initialize the opengl window
	if (glfwInit() == false)
		return -1;

	GLFWwindow* window = glfwCreateWindow(1280, 720, "Computer Graphics", nullptr, nullptr);

	if (window == nullptr)
	{
		glfwTerminate();
		return -2;
	}

	glfwMakeContextCurrent(window);

	//the rest of our code goes here!
	if (ogl_LoadFunctions() == ogl_LOAD_FAILED)
	{
		glfwDestroyWindow(window);
		glfwTerminate();
		return -3;
	}

	//testing what version of OpenGL we are running
	auto major = ogl_GetMajorVersion();
	auto minor = ogl_GetMinorVersion();
	printf_s("GL: %i.%i\n", major, minor);
	//done initialize window and OpenGL

	//BEGIN SHADER SETUP
	string vshader = LoadShader("vertex_shader.vert");
	string fshader = LoadShader("fragment_shader.frag");
	const char* vsSource = vshader.c_str();
	const char* fsSource = fshader.c_str();
	unsigned int vs = glCreateShader(GL_VERTEX_SHADER);
	unsigned int fs = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(vs, 1, (const char**)&vsSource, 0);
	glCompileShader(vs);

	glShaderSource(fs, 1, (const char**)&fsSource, 0);
	glCompileShader(fs);

	m_shader = glCreateProgram();
	glAttachShader(m_shader, vs);
	glAttachShader(m_shader, fs);
	glBindAttribLocation(m_shader, 0, "Position");
	glBindAttribLocation(m_shader, 1, "Color");
	glLinkProgram(m_shader);

	int success = GL_FALSE;
	glGetProgramiv(m_shader, GL_LINK_STATUS, &success);
	if (success == GL_FALSE)
	{
		int infoLogLength = 0;
		glGetShaderiv(m_shader, GL_INFO_LOG_LENGTH, &infoLogLength);
		char* infoLog = new char[infoLogLength];

		glGetShaderInfoLog(m_shader, infoLogLength, 0, infoLog);
		printf("Error: Failed to link Gizmo shader program!\n%s\n", infoLog);
		delete[] infoLog;
	}
	//END SHADER SETUP

	//Setup some geometry to draw
	//MyVertex will be the storage container for our vertex information
	Vertex Vertices[] =
	{
		{-1.f,-1.f,0.f},
		{0.f,-1.f,1.f},
		{1.f,-1.f,0.f},
		{0.f,1.f,0.f},
		

	};

	Color Colors[] =
	{
		{ -1.f,-1.f,0.f, 1.0f },
		{ 0.f,-1.f,1.f, 1.0f },
		{ 1.f,-1.f,0.f, 1.0f },
		{ 0.f,1.f,0.f, 1.0f },


	};

	unsigned int Indices[] = 
	{
		0, 3, 1,
		1, 3, 2,
		2, 3, 0,
		0, 1, 2 
	};
	


	//done setup with geometry information

	GLuint m_CBO;
	

	//Now we put it on the graphics card
	//generate your buffer on the graphics card
	//this contains all the vertices
	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);

		glGenBuffers(1, &m_VBO);
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
	
		glGenBuffers(1, &m_CBO);
		glBindBuffer(GL_ARRAY_BUFFER, m_CBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Colors), Colors, GL_STATIC_DRAW);
	
		glGenBuffers(1, &m_IBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices), Indices, GL_STATIC_DRAW);

	 
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0); 		 
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);
	//unbind now that we have generated and populated
 
	glEnableVertexAttribArray(0);
	
	glBindVertexArray(0); 
	

	//setup some matrices
	mat4 m_model = glm::mat4();
	mat4 m_view = glm::lookAt(vec3(2, 3, 10), vec3(0), vec3(0, 1, 0));
	mat4 m_projection = glm::perspective(glm::pi<float>()*0.25f, 16 / 9.f, 0.1f, 1000.f);
	mat4 m_projectionViewMatrix = m_projection * m_view;
	//end setup matrices

	unsigned int projectionViewUniform = glGetUniformLocation(m_shader, "ProjectionView");
	//start using shader...
	glUseProgram(m_shader);
	//because we are sending it to the uniform with this function
	glUniformMatrix4fv(projectionViewUniform, 1, false, glm::value_ptr(m_projectionViewMatrix));

	while (glfwWindowShouldClose(window) == false && glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS)
	{
		glClearColor(0.25f, 0.25f, 0.25f, 1);
		glEnable(GL_DEPTH_TEST);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		unsigned int modelID = glGetUniformLocation(m_shader, "Model"); 
		glUniformMatrix4fv(modelID, 1, false, glm::value_ptr(m_model));
	 
		glBindVertexArray(m_VAO); 
		//draw
		glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, BUFFER_OFFSET(0));
		//unbind
		
		glBindVertexArray(0); 
 
		glfwSwapBuffers(window);
		glfwPollEvents();
	}



	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}

