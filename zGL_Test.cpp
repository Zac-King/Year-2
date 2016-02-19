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

//using namespace std;
//
//using glm::vec3;
//using glm::vec4;
//using glm::mat4;
//
//#define BUFFER_OFFSET(i) ((char *)NULL + (i))
//
//struct Vertex
//{
//	float x, y, z;
//};
//
//struct Color
//{
//	float r, g, b, a;
//};
//
//class Grid
//{
//public:
//	Vertex *verts;
//	//unsigned int *indices;
//	std::vector<int> indices;
//	int width, length;
//	float displacement;
//
//	void GenGrid()
//	{
//		int index = 0;
//		int size = width * length;
//
//		for (int i = 0; i < width; i++)
//		{
//			for (int j = 0; j < length; j++)
//			{
//				verts[index] = { i * displacement, 0, j * displacement };
//				index++;
//			}
//		}
//
//		for (int k = 0; k < size; k++)
//		{
//			std::cout << "{ " << verts[k].x << ", " << verts[k].y << ", " << verts[k].z << " }\n";
//			std::cout << "Indices: \n";
//			
//			// Triangle 1 check
//			if ((verts[k].x != NULL) && (verts[k + 1].x != NULL) && (verts[k + width].x != NULL))
//			{
//				indices.push_back(k);
//				indices.push_back(k+1);
//				indices.push_back(k+width);
//			}
//			// Triangle 2 check
//			if ((verts[k].x != NULL) && (verts[k + 1].x != NULL) && (verts[(k + 1) - width].x != NULL))
//			{
//				indices.push_back(k);
//				indices.push_back(k + 1);
//				indices.push_back((k + 1) - width);
//			}
//		}
//	}
//
//	Grid(int w, int l, float d)
//	{
//		width = w;
//		length = l;
//		displacement = d;
//		verts = new Vertex[width*length];
//		GenGrid();
//	}
//
//};
//
//unsigned int	m_VAO,		// Vertex Array Object
//				m_VBO,		// Vertex Buffer Object
//				m_IBO,		// Index Buffer Object
//				m_CBO,		// Color Buffer Object
//				m_shader;	// Shader Object
//
//GLFWwindow* window;
//
//#pragma region myTestVariables
//// Test triangle
//Vertex myTri[] = {	{ -1.f, -1.f, 0.f },
//					{  0.f, -1.f, 1.f },
//					{  1.f, -1.f, 0.f },
//					{  0.f,  1.f, 0.f } };
//// Test Indices
//unsigned int Indices[] = {	0, 3, 1,
//							1, 3, 2,
//							2, 3, 0,
//							0, 1, 2 };
//// Test Color
//Color Colors[] = {	{ -1.f, -1.f, 0.f, 1.0f },
//					{  0.f, -1.f, 1.f, 1.0f },
//					{  1.f, -1.f, 0.f, 1.0f },
//					{  0.f,  1.f, 0.f, 1.0f }, };
//#pragma endregion
//
//// Loading shader file from the file name parameter passed
//std::string LoadShader(std::string file)	
//{
//	string line, shader;
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
//	printf_s("GL: %i.%i\n", ogl_GetMajorVersion(), ogl_GetMinorVersion());
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
//int setupBuffer(Vertex vert[], int indices[])
//{
//	glUseProgram(m_shader);
//	GLuint vertposition = glGetAttribLocation(m_shader, "Position");
//	GLuint vertcolor	= glGetAttribLocation(m_shader, "Color");
//
//	// Setting up Vertex Array object
//	glGenVertexArrays(1, &m_VAO);
//	glBindVertexArray(m_VAO);
//
//	// Setting up Vertex Buffer object
//	glGenBuffers(1, &m_VBO);
//	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(vert) * 4, vert, GL_STATIC_DRAW);
//	glVertexAttribPointer(vertposition, 3, GL_FLOAT, GL_FALSE, 0, ((void*)0)); // Pointer to where all the vert info is
//	glEnableVertexAttribArray(vertposition);
//
//	// Setting up Color Buffer object
//	glGenBuffers(1, &m_CBO);
//	glBindBuffer(GL_ARRAY_BUFFER, m_CBO);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(Colors), Colors, GL_STATIC_DRAW);
//	glVertexAttribPointer(vertcolor, 4, GL_FLOAT, GL_FALSE, 0, ((void*)(0)));
//	glEnableVertexAttribArray(vertcolor);
//
//	// Setting up Index buffer
//	glGenBuffers(1, &m_IBO);
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices), Indices, GL_STATIC_DRAW);
//
//	glEnableVertexAttribArray(0);
//	glBindVertexArray(0);
//
//	return 1;
//}

//int main()
//{
//	Grid plane = Grid(25, 25, 3);
//
//	setupWindow();
//	setupShader();
//	setupBuffer(plane.verts);
//
//	// Set up camera
//	mat4 model = glm::mat4();
//	mat4 view = glm::lookAt(vec3(2, 3, 5), vec3(0), vec3(0, 1, 0));						// Set up Camera in a simulated 3D enviroment
//	mat4 projection = glm::perspective(glm::pi<float>()*0.25f, 16 / 9.f, 0.1f, 1000.f);	// Camera capacity FOV (view angle) and aspect ratio(relation of width and height, how the view is stretched)
//
//	//end setup matrices
//	unsigned int projectionMatrixID	= glGetUniformLocation(m_shader, "Projection");
//	unsigned int viewMatrixID		= glGetUniformLocation(m_shader, "View");
//	unsigned int modelMatrixID		= glGetUniformLocation(m_shader, "Model");
//	unsigned int timeID				= glGetUniformLocation(m_shader, "time");
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
//		glUniform1f(timeID, glfwGetTime());
//		//draw
//		glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, ((void*)0));
//		//unbind		
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
