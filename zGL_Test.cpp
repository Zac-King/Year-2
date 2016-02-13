#include <vector>
#include "stdio.h"
#include <gl_core_4_4.h>
#include <Gizmos.h>
#include <GLFW/glfw3.h> 
#include <glm\glm.hpp>
#include <glm\ext.hpp>
#include <iostream>

using glm::vec3;
using glm::vec4;
using glm::mat4;

#define BUFFER_OFFSET(i) ((char *)NULL + (i))

struct Vertex
{
	vec3 position;	// X,Y,Z
	vec4 color;		// R,G,B,A
};

//class Vertex
//{
//public:
//	vec3 position;
//	vec4 color;
//	Vertex(vec3 p, vec4 c)
//	{
//		position = p;
//		color = c;
//	}
//};

unsigned int	m_VAO,		// Vertex Array Object
				m_VBO,		// Vertex Buffer Object
				m_IBO;		// Index Buffer Object
unsigned int	m_shader;	// All the shaders	(?)


int main()
{
#pragma region Setup OpenGL
	// Set up Camera in a simulated 3D enviroment
	mat4 m_view = glm::lookAt(vec3(10, 10, 10), vec3(0), vec3(0, 1, 0));
	// Camera capacity FOV (view angle) and aspect ratio(relation of width and height, how the view is stretched)
	mat4 m_projection = glm::perspective(glm::pi<float>()*0.25f, 16 / 9.f, 0.1f, 1000.f);
	// Resulting view
	mat4 m_projectionViewMatrix = m_projection * m_view;

	// Intialize GLFW library 
	if (glfwInit() == false)
		return -1;	// (Check)

	
	// Setting up the window				resolution		Name		GLFWmonitor(?) GLFWwindow(?)
	GLFWwindow* window = glfwCreateWindow(1280, 720, "Computer Graphics", nullptr, nullptr);

	// Null check for the newly made window
	if (window == nullptr)
	{
		glfwTerminate();
		return -2;	// (Check)
	}

	// (?) "Makes the context of the specified window current for the calling thread"
	glfwMakeContextCurrent(window);

	// (Check) if OpenGL functions dont load correctly it shuts everything
	if (ogl_LoadFunctions() == ogl_LOAD_FAILED)
	{
		glfwDestroyWindow(window);
		glfwTerminate();
		return -3;
	}

	// Prints the OpenGL version we are running
	printf_s("GL: %i.%i\n", ogl_GetMajorVersion(), ogl_GetMinorVersion());
#pragma endregion

#pragma region Shaders
	// Vertex Shader source (?) Shader from a file?
	const char* vsSource = "#version 150\n \
							in vec4 Position; \
							in vec4 Colour; \
							out vec4 vColour; \
							uniform mat4 ProjectionView; \
							void main() { vColour = Colour; gl_Position = ProjectionView * Position; }";
	// Fragment Shader source (?) Shader from a file?
	const char* fsSource = "#version 150\n \
							in vec4 vColour; \
							out vec4 FragColor; \
							void main()	{ FragColor = vColour; }";

	// Vertex Shader
	unsigned int vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs, 1, (const char**)&vsSource, 0);
	glCompileShader(vs);

	// Fragment Shader
	unsigned int fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, (const char**)&fsSource, 0);
	glCompileShader(fs);

	// The Attaching shaders to our m_shader variable
	m_shader = glCreateProgram();
	glAttachShader(m_shader, vs);					// Attaching Vertex Shader
	glBindAttribLocation(m_shader, 0, "Position");	// Add telling m_shader what this info is
	glAttachShader(m_shader, fs);					// Attaching Fragment Shader
	glBindAttribLocation(m_shader, 1, "Colour");	// Add telling m_shader what this info is
	glLinkProgram(m_shader); // specifies handle for our shader
	
	// (Check) if m_shader was linked sucessfully
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
#pragma endregion

#pragma region Vertices
	// Test triangle
	Vertex myTri[3];
	myTri[0] = { { 0,0,0 },{ 20,0,0,0 } };
	myTri[1] = { { 1,0,0 },{ 0,20,0,0 } };
	myTri[2] = { { 1,0,0 },{ 0,0,20,0 } };


#pragma endregion

	// Setting up Vertex Array object
	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);
	// Setting up Vertex Buffer object
	glGenBuffers(1, &m_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * 3, &myTri[0].position.x, GL_STATIC_DRAW);
													// why only the one verts x pos?
	
	
	// Setting up Index object
	unsigned int pindices[3];
	pindices[0] = 0;
	pindices[1] = 1;
	pindices[2] = 2;
	// Setting up Index buffer
	glGenBuffers(1, &m_IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * 3, pindices, GL_STATIC_DRAW);

	// (?)
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), BUFFER_OFFSET(0));
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);

	//
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), BUFFER_OFFSET(0));
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


	glClearColor(0.25f, 0.25f, 0.25f, 1);
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(m_shader);
	unsigned int projectionViewUniform = glGetUniformLocation(m_shader, "ProjectionView");
	glUniformMatrix4fv(projectionViewUniform, 1, false, glm::value_ptr(m_projectionViewMatrix));


	glBindVertexArray(m_VAO);
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, BUFFER_OFFSET(0));
	glBindVertexArray(0);

	//











	glfwSwapBuffers(window);	// (?) Swaps front and back buffers. Not sure why we do that
	glfwPollEvents();			// (?)
	system("Pause");
	glfwDestroyWindow(window);	// Close the Display window we created at the start
	glfwTerminate();			// Closes everything

	return 0;
}