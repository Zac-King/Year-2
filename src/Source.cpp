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
//using glm::vec3;
//using glm::vec4;
//using glm::mat4;
//using namespace std;
// 
//GLuint m_VAO, m_VBO, m_IBO, m_CBO, m_shader;
//GLFWwindow* window;
//
//struct Vertex
//{
//	float x, y, z;        //Vertex	 
//};
//
//struct Color
//{
//	float r, g, b, a;
//};
//
////Setup some geometry to draw
////MyVertex will be the storage container for our vertex information
//Vertex Vertices[] = {
//	{ -1.f,-1.f,0.f },
//	{ 0.f,-1.f,1.f },
//	{ 1.f,-1.f,0.f },
//	{ 0.f,1.f,0.f },
//
//
//};
//
//Color Colors[] = {
//	{ -1.f,-1.f,0.f, 1.0f },
//	{ 0.f,-1.f,1.f, 1.0f },
//	{ 1.f,-1.f,0.f, 1.0f },
//	{ 0.f,1.f,0.f, 1.0f },
//
//
//};
//
//unsigned int Indices[] = {
//	0, 3, 1,
//	1, 3, 2,
//	2, 3, 0,
//	0, 1, 2
//};
//
//
//
//string LoadShader(std::string file)
//{
//	string line, shader;
//	ifstream inFile(file);
//	if (inFile.is_open())
//		while (getline(inFile, line))
//		{
//			shader.append(line);
//			shader.append("\n");
//		}
//	inFile.close();
//	return shader;
//}
//
//int setup_window()
//{
//
//	//initialize the opengl window
//	if (glfwInit() == false)
//		return -1;
//
//	window = glfwCreateWindow(1280, 720, "Computer Graphics", nullptr, nullptr);
//
//	if (window == nullptr)
//	{
//		glfwTerminate();
//		return -2;
//	}
//
//	glfwMakeContextCurrent(window);
//
//	//the rest of our code goes here!
//	if (ogl_LoadFunctions() == ogl_LOAD_FAILED)
//	{
//		glfwDestroyWindow(window);
//		glfwTerminate();
//		return -3;
//	}
//
//	//testing what version of OpenGL we are running
//	auto major = ogl_GetMajorVersion();
//	auto minor = ogl_GetMinorVersion();
//	printf_s("GL: %i.%i\n", major, minor);
//	//done initialize window and OpenGL
//
//	return 1;
//}
//
//int setup_shader()
//{
//	//BEGIN SHADER SETUP
//	string vshader = LoadShader("vertex_shader.vert");
//	string fshader = LoadShader("fragment_shader.frag");
//	const char* vsSource = vshader.c_str();
//	const char* fsSource = fshader.c_str();
//	unsigned int vs = glCreateShader(GL_VERTEX_SHADER);
//	unsigned int fs = glCreateShader(GL_FRAGMENT_SHADER);
//
//	// setup Shaders
//	glShaderSource(vs, 1, (const char**)&vsSource, 0);
//	glCompileShader(vs);
//
//	glShaderSource(fs, 1, (const char**)&fsSource, 0);
//	glCompileShader(fs);
//
//	m_shader = glCreateProgram();
//	glAttachShader(m_shader, vs);
//	glAttachShader(m_shader, fs);
//	glBindAttribLocation(m_shader, 0, "Position");
//	glBindAttribLocation(m_shader, 1, "Color");
//	glLinkProgram(m_shader);
//
//	int success = GL_FALSE;
//	glGetProgramiv(m_shader, GL_LINK_STATUS, &success);
//	if (success == GL_FALSE)
//	{
//		int infoLogLength = 0;
//		glGetShaderiv(m_shader, GL_INFO_LOG_LENGTH, &infoLogLength);
//		char* infoLog = new char[infoLogLength];
//
//		glGetShaderInfoLog(m_shader, infoLogLength, 0, infoLog);
//		printf("Error: Failed to link Gizmo shader program!\n%s\n", infoLog);
//		delete[] infoLog;
//	}
//	//END SHADER SETUP
//
//	return 1;
//}
//
//int setup_buffers()
//{
//	glUseProgram(m_shader);
//	GLuint vertposition = glGetAttribLocation(m_shader, "Position");
//	GLuint vertcolor = glGetAttribLocation(m_shader, "Color");
//	//Now we put it on the graphics card
//	//generate your buffer on the graphics card
//	//this contains all the vertices
//	glGenVertexArrays(1, &m_VAO);
//	glBindVertexArray(m_VAO);
//
//	glGenBuffers(1, &m_VBO);
//	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
//	glVertexAttribPointer(vertposition,
//		3,
//		GL_FLOAT,
//		GL_FALSE,
//		0,
//		((void*)0));
//	glEnableVertexAttribArray(vertposition);
//	glGenBuffers(1, &m_CBO);
//	glBindBuffer(GL_ARRAY_BUFFER, m_CBO);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(Colors), Colors, GL_STATIC_DRAW);
//	glVertexAttribPointer(vertcolor,
//		4,
//		GL_FLOAT,
//		GL_FALSE,
//		0,
//		((void*)(0)));
//	glEnableVertexAttribArray(vertcolor);
//
//	glGenBuffers(1, &m_IBO);
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices), Indices, GL_STATIC_DRAW);
//	//unbind now that we have generated and populated
//
//	glEnableVertexAttribArray(0);
//	glBindVertexArray(0);
//
//	return 1;
//}
//
//int main()
//{ 
//	setup_window();
//	setup_shader();
//	setup_buffers();
//	
//	//setup some matrices
//	mat4 model = glm::mat4();
//	mat4 view = glm::lookAt(vec3(2, 3, 10), vec3(0), vec3(0, 1, 0));
//	mat4 projection = glm::perspective(glm::pi<float>()*0.25f, 16 / 9.f, 0.1f, 1000.f);
//
//	//end setup matrices
//	unsigned int projectionMatrixID = glGetUniformLocation(m_shader, "Projection");
//	unsigned int viewMatrixID = glGetUniformLocation(m_shader, "View");
//	unsigned int modelMatrixID = glGetUniformLocation(m_shader, "Model");
//	//because we are sending it to the uniform with this function
//	glUniformMatrix4fv(projectionMatrixID, 1, false, &projection[0][0]);
//	glUniformMatrix4fv(viewMatrixID, 1, false, &view[0][0]);
//	glUniformMatrix4fv(modelMatrixID, 1, false, &model[0][0]);
//
//	while (glfwWindowShouldClose(window) == false && glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS)
//	{
//		glClearColor(0.25f, 0.25f, 0.25f, 1);
//		glEnable(GL_DEPTH_TEST);
//		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//	 
//		glBindVertexArray(m_VAO); 
//		//draw
//		glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, ((void*)0));
//		//unbind		
//		glBindVertexArray(0); 
// 
//		glfwSwapBuffers(window);
//		glfwPollEvents();
//	}
//
//
//
//	glfwDestroyWindow(window);
//	glfwTerminate();
//	return 0;
//}
//
