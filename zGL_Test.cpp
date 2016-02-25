#define GLM_FORCE_PURE
#include <vector>
#include "stdio.h"
#include <gl_core_4_4.h>
#include <Gizmos.h>
#include <GLFW/glfw3.h> 
#include <glm\glm.hpp>
#include <glm\ext.hpp>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

//using glm::vec3;
//using glm::vec4;
//using glm::mat4;
//
//#define BUFFER_OFFSET(i) ((char *)NULL + (i))
//
//struct Vertex
//{
//	vec4 position;	// X,Y,Z,W
//};
//
//struct Color
//{
//	float r, g, b, a;
//};
//
//unsigned int	m_VAO,		// Vertex Array Object
//				m_VBO,		// Vertex Buffer Object
//				m_IBO,		// Index Buffer Object
//				m_CBO,		// Color Buffer Object
//				m_shader;	// All the shaders	(?)
//
//GLFWwindow* window;
//
//#pragma region myTestVariables
//// Test triangle
//Vertex myTri[] = {
//	{ { -1.f, -1.f, 0.f, 1.0f } },
//	{ {  0.f, -1.f, 1.f, 1.0f } },
//	{ {  1.f, -1.f, 0.f, 1.0f } },
//	{ {  0.f,  1.f, 0.f, 1.0f } },
//};
//// Test Indices
//unsigned int Indices[] =  { 0, 3, 1,	
//							1, 3, 2,
//							2, 3, 0,
//							0, 1, 2 };
//// Test Color
//Color Colors[] = { { -1.f,-1.f,0.f, 1.0f },
//{ 0.f,-1.f,1.f, 1.0f },
//{ 1.f,-1.f,0.f, 1.0f },
//{ 0.f,1.f,0.f, 1.0f }, };
//#pragma endregion
//
//static const GLfloat cube_colors[] =
//{
//	// front colors
//	1.0, 0.0, 0.0,//0
//	0.0, 1.0, 0.0,//1
//	0.0, 0.0, 1.0,//2
//	1.0, 1.0, 1.0,//3
//				  // back colors
//	1.0, 0.0, 0.0,//4
//	0.0, 1.0, 0.0,//5
//	0.0, 0.0, 1.0,//6
//	1.0, 1.0, 1.0,//7
//};
//
//std::string LoadShader(std::string file)	// Loading shader file from the file name parameter passed
//{
//	string	line,	
//			shader; // Return value
//	ifstream inFile(file);
//	if (inFile.is_open())
//		while (std::getline(inFile, line))
//		{
//			shader.append(line);
//			shader.append("\n");
//		}
//	inFile.close();
//	return shader;
//}
//
//int setupWindow()
//{
//	// Intialize GLFW window
//	if (glfwInit() == false)
//		return -1;
//
//	// Setting up the window				resolution		Name		GLFWmonitor(?) GLFWwindow(?)
//	window = glfwCreateWindow(1280, 720, "Computer Graphics", nullptr, nullptr);
//
//	// Null check for the newly made window
//	if (window == nullptr)
//	{
//		glfwTerminate();
//		return -2;
//	}
//
//	// (?) "Makes the context of the specified window current for the calling thread"
//	glfwMakeContextCurrent(window);
//
//	// (Check) if OpenGL functions dont load correctly it shuts everything
//	if (ogl_LoadFunctions() == ogl_LOAD_FAILED)
//	{
//		glfwDestroyWindow(window);
//		glfwTerminate();
//		return -3;
//	}
//
//	// Prints the OpenGL version we are running
//	//printf_s("GL: %i.%i\n", ogl_GetMajorVersion(), ogl_GetMinorVersion());
//
//	return 1;
//}
//
//int setupShader()
//{
//	// Get shader info from the files
//	std::string vshader = LoadShader("vertex_shader.vert");
//	std::string fshader = LoadShader("fragment_shader.frag");
//	// Get the pointers to the character arrays
//	const char* vsSource = vshader.c_str();
//	const char* fsSource = fshader.c_str();
//
//
//
//	// Creating the individual shader objects 
//	unsigned int vs = glCreateShader(GL_VERTEX_SHADER);		// Our Vertex shader object
//	unsigned int fs = glCreateShader(GL_FRAGMENT_SHADER);	// Our Fragment shader Object
//
//	// Vertex Shader setup
//	glShaderSource(vs, 1, (const char**)&vsSource, 0);
//	glCompileShader(vs);
//	// Fragment Shader setup
//	glShaderSource(fs, 1, (const char**)&fsSource, 0);
//	glCompileShader(fs);
//
//	// The Attaching shaders to our m_shader variable
//	m_shader = glCreateProgram();
//	glAttachShader(m_shader, vs);					// Attaching Vertex Shader
//	glBindAttribLocation(m_shader, 0, "Position");	// Add telling m_shader what this info is
//	glAttachShader(m_shader, fs);					// Attaching Fragment Shader
//	glBindAttribLocation(m_shader, 1, "Colour");	// Add telling m_shader what this info is
//	glLinkProgram(m_shader); // specifies handle for our shader
//
//	// (Check) if m_shader was linked sucessfully
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
//
//	return 1;
//}
//
//int setupBuffer(vector<int> ind, vector<vec3> vert, int vOffset, int cOffset)
//{
//	glUseProgram(m_shader);
//	GLuint vertposition = glGetAttribLocation(m_shader, "Position");
//	GLuint vertcolor = glGetAttribLocation(m_shader, "Color");
//
//	// Setting up Index buffer
//	glGenBuffers(1, &m_IBO);
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, ind.size() * sizeof(int), ind.data(), GL_STATIC_DRAW);
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
//
//	// Setting up Vertex Array object
//	glGenVertexArrays(1, &m_VAO);
//	glBindVertexArray(m_VAO);
//
//	// Setting up Vertex Buffer object
//	glGenBuffers(1, &m_VBO);
//	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
//	glBufferData(GL_ARRAY_BUFFER, vOffset + cOffset, NULL, GL_STATIC_DRAW);
//
//	glBufferSubData(GL_ARRAY_BUFFER, 0, vert.size() * sizeof(vec3), vert.data());
//	glBufferSubData(GL_ARRAY_BUFFER, vOffset, cOffset, &cube_colors[0]);
//
//	glVertexAttribPointer(vertposition, 3, GL_FLOAT, GL_FALSE, 0, ((void*)0)); // Pointer to where all the vert info is
//	glEnableVertexAttribArray(vertposition);
//
//	//// Setting up Color Buffer object
//	//glGenBuffers(1, &m_CBO);
//	//glBindBuffer(GL_ARRAY_BUFFER, m_CBO);
//	//glBufferData(GL_ARRAY_BUFFER, sizeof(Colors), Colors, GL_STATIC_DRAW);
//	//glVertexAttribPointer(vertcolor, 4, GL_FLOAT, GL_FALSE, 0, ((void*)(0)));
//	//glEnableVertexAttribArray(vertcolor);
//
//
//	glEnableVertexAttribArray(0);
//	glBindVertexArray(0);
//
//	return 1;
//}
//
//// function to create a grid
//void generateGrid(unsigned int rows, unsigned int cols, std::vector<vec3> &verts, std::vector<int> &indices)
//{
//	Vertex* aoVertices = new Vertex[rows * cols];
//	for (unsigned int r = 0; r < rows; ++r) {
//		for (unsigned int c = 0; c < cols; ++c)
//		{
//			aoVertices[r * cols + c].position = vec4((float)c, 0, (float)r, 1);
//			verts.push_back(vec3((float)c, 0, (float)r));
//		}
//	}
//}
//
//
//
//int main()
//{
//	setupWindow();
//	setupShader();
//
//	// Now we put it on the graphics card
//	//generate your buffer on the graphics card
//	//this contains all the vertices
//	vector<vec3> plane;
//	vector<int> indices;
//	generateGrid(5, 5, plane, indices);
//	int numVertices		= plane.size();
//	int numColors		= sizeof(cube_colors) / sizeof(GLfloat);
//	int vertOffset		= plane.size() * sizeof(vec3);
//	int colorOffset		= numColors * sizeof(cube_colors);
//	int numIndices		= indices.size();
//
//	setupBuffer(indices, plane, vertOffset, colorOffset);
//
//	// Setup matrices
//	mat4 model = glm::mat4();
//	mat4 view = glm::lookAt(vec3(2, 3, 10), vec3(0), vec3(0, 1, 0));					// Setup Camera in a simulated 3D enviroment
//	mat4 projection = glm::perspective(glm::pi<float>()*0.25f, 16 / 9.f, 0.1f, 1000.f);	// Camera capacity FOV (view angle) and aspect ratio(relation of width and height, how the view is stretched)
//	mat4 projectionViewMatrix = projection * view;
//
//	unsigned int projectionViewUniform = glGetUniformLocation(m_shader, "ProjectionView");
//    unsigned int timeID = glGetUniformLocation(m_shader, "time");
//
//	//start using shader...
//	glUseProgram(m_shader);
//	// Setting up Camera and 3D enviroment
//	glUniformMatrix4fv(projectionViewUniform, 1, false, value_ptr(projectionViewMatrix));
//
//	while (glfwWindowShouldClose(window) == false && glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS)
//	{
//		glClearColor(0.25f, 0.25f, 0.25f, 1);
//		glEnable(GL_DEPTH_TEST);
//		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//		unsigned int modelID = glGetUniformLocation(m_shader, "Model");
//
//		glUniformMatrix4fv(modelID, 1, false, value_ptr(model));
//
//		glBindVertexArray(m_VAO);
//		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
//		glUniform1f(timeID, glfwGetTime());
//		// Draw
//		glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, BUFFER_OFFSET(0));
//		// Unbind		
//		glBindVertexArray(0);
//
//		glfwSwapBuffers(window);
//		glfwPollEvents();
//	}
//
//	glfwDestroyWindow(window);	// Close the Display window we created at the start
//	glfwTerminate();			// Closes everything
//
//	return 0;
//}


//#pragma region Setup OpenGL
//	// Set up Camera in a simulated 3D enviroment
//	mat4 m_view = glm::lookAt(vec3(10, 10, 10), vec3(0), vec3(0, 1, 0));
//	// Camera capacity FOV (view angle) and aspect ratio(relation of width and height, how the view is stretched)
//	mat4 m_projection = glm::perspective(glm::pi<float>()*0.25f, 16 / 9.f, 0.1f, 1000.f);
//	// Resulting view
//	mat4 m_projectionViewMatrix = m_projection * m_view;
//
//	// Intialize GLFW library 
//	if (glfwInit() == false)
//		return -1;	// (Check)
//
//	
//	// Setting up the window				resolution		Name		GLFWmonitor(?) GLFWwindow(?)
//	GLFWwindow* window = glfwCreateWindow(1280, 720, "Computer Graphics", nullptr, nullptr);
//
//	// Null check for the newly made window
//	if (window == nullptr)
//	{
//		glfwTerminate();
//		return -2;	// (Check)
//	}
//
//	// (?) "Makes the context of the specified window current for the calling thread"
//	glfwMakeContextCurrent(window);
//
//	// (Check) if OpenGL functions dont load correctly it shuts everything
//	if (ogl_LoadFunctions() == ogl_LOAD_FAILED)
//	{
//		glfwDestroyWindow(window);
//		glfwTerminate();
//		return -3;
//	}
//
//	// Prints the OpenGL version we are running
//	printf_s("GL: %i.%i\n", ogl_GetMajorVersion(), ogl_GetMinorVersion());
//#pragma endregion

//#pragma region Shaders
//	// Vertex Shader source (?) Shader from a file?
//	const char* vsSource = "#version 150\n \
//							in vec4 Position; \
//							in vec4 Colour; \
//							out vec4 vColour; \
//							uniform mat4 ProjectionView; \
//							void main() { vColour = Colour; gl_Position = ProjectionView * Position; }";
//	// Fragment Shader source (?) Shader from a file?
//	const char* fsSource = "#version 150\n \
//							in vec4 vColour; \
//							out vec4 FragColor; \
//							void main()	{ FragColor = vColour; }";
//
//	// Vertex Shader
//	unsigned int vs = glCreateShader(GL_VERTEX_SHADER);
//	glShaderSource(vs, 1, (const char**)&vsSource, 0);
//	glCompileShader(vs);
//
//	// Fragment Shader
//	unsigned int fs = glCreateShader(GL_FRAGMENT_SHADER);
//	glShaderSource(fs, 1, (const char**)&fsSource, 0);
//	glCompileShader(fs);
//
//	// The Attaching shaders to our m_shader variable
//	m_shader = glCreateProgram();
//	glAttachShader(m_shader, vs);					// Attaching Vertex Shader
//	glBindAttribLocation(m_shader, 0, "Position");	// Add telling m_shader what this info is
//	glAttachShader(m_shader, fs);					// Attaching Fragment Shader
//	glBindAttribLocation(m_shader, 1, "Colour");	// Add telling m_shader what this info is
//	glLinkProgram(m_shader); // specifies handle for our shader
//	
//	// (Check) if m_shader was linked sucessfully
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
//#pragma endregion

//// Setting up Vertex Array object
//glGenVertexArrays(1, &m_VAO);
//glBindVertexArray(m_VAO);
//// Setting up Vertex Buffer object
//glGenBuffers(1, &m_VBO);
//glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
//glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * 3, &myTri[0].position.x, GL_STATIC_DRAW);
//												// why only the one verts x pos?
//
//
//// Setting up Index object
//unsigned int pindices[3];
//pindices[0] = 0;
//pindices[1] = 1;
//pindices[2] = 2;
//// Setting up Index buffer
//glGenBuffers(1, &m_IBO);
//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * 3, pindices, GL_STATIC_DRAW);
//// (?)
//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), BUFFER_OFFSET(0));
//glEnableVertexAttribArray(0);
//glBindVertexArray(0);
////
//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), BUFFER_OFFSET(0));
//glEnableVertexAttribArray(0);
//glBindVertexArray(0);
//
//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
//glBindVertexArray(0);
//glBindBuffer(GL_ARRAY_BUFFER, 0);
//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
//
//glClearColor(0.25f, 0.25f, 0.25f, 1);
//glEnable(GL_DEPTH_TEST);
//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//glUseProgram(m_shader);
//unsigned int projectionViewUniform = glGetUniformLocation(m_shader, "ProjectionView");
//glUniformMatrix4fv(projectionViewUniform, 1, false, glm::value_ptr(m_projectionViewMatrix));
//
//glBindVertexArray(m_VAO);
//glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, BUFFER_OFFSET(0));
//glBindVertexArray(0);