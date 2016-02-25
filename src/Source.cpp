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
using glm::vec2;
using glm::vec3;
using glm::vec4;
using glm::mat4;
using namespace std;

#define BUFFER_OFFSET(i) ((char *)NULL + (i))

unsigned int m_VAO, m_VBO, m_IBO;
unsigned int m_shader;
float *m_perlinData;
int m_perlinDimensions;
GLuint m_perlinTexture;

struct Vertex {
	vec4 position;
	vec2 texCoord;
};

void generateGrid(unsigned int rows, unsigned int cols, std::vector<vec3> &, std::vector<int>&);
// function to create a grid
void generateGrid(unsigned int rows, unsigned int cols, std::vector<vec3> &verts, std::vector<int> &indices)
{
	Vertex* aoVertices = new Vertex[rows * cols];
	for (unsigned int r = 0; r < rows; ++r) {
		for (unsigned int c = 0; c < cols; ++c)
		{
			aoVertices[r * cols + c].position = vec4((float)c, 0, (float)r, 1);
			verts.push_back(vec3((float)c, 0, (float)r));
		}
	}

	// defining index count based off quad count (2 triangles per quad)
	unsigned int* auiIndices = new unsigned int[(rows - 1) * (cols - 1) * 6];
	unsigned int index = 0;
	for (unsigned int r = 0; r < (rows - 1); ++r)
	{
		for (unsigned int c = 0; c < (cols - 1); ++c)
		{
			int p0 = r * cols + c;
			int p1 = (r + 1) * cols + c;
			int p2 = (r + 1) * cols + (c + 1);
			int p3 = r * cols + c;
			int p4 = (r + 1) * cols + (c + 1);
			int p5 = r * cols + (c + 1);
			indices.push_back(p0);
			indices.push_back(p1);
			indices.push_back(p2);
			indices.push_back(p3);
			indices.push_back(p4);
			indices.push_back(p5);

		}
	}

 

	// we’ll do more here soon!
	delete[] aoVertices;
	delete[] auiIndices;
}

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
 
void PerlinPop()
{
	
}

int main()
{
#pragma region Window Swtup
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
#pragma endregion

#pragma region Shader Setup
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
	glBindAttribLocation(m_shader, 1, "TexCoord");
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
#pragma endregion

#pragma region Buffer


	//Now we put it on the graphics card
	//generate your buffer on the graphics card
	//this contains all the vertices
	
	
	int rows = 64;
	int cols = rows;
	int m_indexCount = 0;

	// create opengl data for a grid
	Vertex* vertices = new Vertex[rows * cols];
	for (int r = 0; r < rows; ++r) {
		for (int c = 0; c < cols; ++c) {

			// offset position so that the terrain is centered
			vertices[r * cols + c].position = vec4(c - cols * 0.5f, 0, r - rows * 0.5f, 1);

			// setting up UVs
			vertices[r * cols + c].texCoord = vec2(c * (1.f / cols), r * (1.f / rows));
		}
	}

	// keep track of number of indices for rendering
	m_indexCount = (rows - 1) * (cols - 1) * 6;

	unsigned int* indices = new unsigned int[m_indexCount];

	unsigned int index = 0;
	for (int r = 0; r < (rows - 1); ++r) {
		for (int c = 0; c < (cols - 1); ++c) {
			// triangle 1
			indices[index++] = r * cols + c;
			indices[index++] = (r + 1) * cols + c;
			indices[index++] = (r + 1) * cols + (c + 1);
			// triangle 2
			indices[index++] = r * cols + c;
			indices[index++] = (r + 1) * cols + (c + 1);
			indices[index++] = r * cols + (c + 1);
		}
	}

	/*
	To start with, we will be using glm’s perlin noise function to generate our noise instead of
	implementing our own. The glm function simply takes in a vec2 and returns a float between -1 and 1.
	Before just passing in our x and y we want to make some changes to them. First, we scale our point
	down, in this case by 10. This is because Perlin noise always returns 0 on integer boundaries. The
	Perlin noise function also returns a number between -1 and 1. For our height map we want a
	number between 0 and 1 so we can later multiply it by our max height. To do this we multiply by 0.5
	and then add by 0.5.
	*/
	m_perlinDimensions = 64;
	m_perlinData = new float[m_perlinDimensions * m_perlinDimensions];

	// scale helps to control the noise
	float scale = (1.0f / m_perlinDimensions) * 3;

	int octaves = 6;
	for (unsigned int x = 0; x < m_perlinDimensions; ++x) {
		for (unsigned int y = 0; y < m_perlinDimensions; ++y) {

			float amplitude = 1.f;
			float persistence = 0.3f;

			m_perlinData[x * m_perlinDimensions + y] = 0;

			for (int o = 0; o < octaves; ++o)
			{
				float freq = powf(2, (float)o);

				float perlin_sample = glm::perlin(vec2((float)x, (float)y) * scale * freq) * 0.5f + 0.5f;

				m_perlinData[x * m_perlinDimensions + y] += perlin_sample * amplitude;

				amplitude *= persistence;
			}
		}
	}
 


	
	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);

	glGenBuffers(1, &m_IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indexCount * sizeof(unsigned int), indices, GL_STATIC_DRAW);
	
	
	glGenBuffers(1, &m_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, (rows * cols) * sizeof(Vertex), vertices, GL_STATIC_DRAW); 

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)sizeof(vec4));


	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); /// emotional support
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	//unbind now that we have generated and populated

	
	
	
	
	
	

#pragma endregion

#pragma region Perlin

	glGenTextures(1, &m_perlinTexture);
	glBindTexture(GL_TEXTURE_2D, m_perlinTexture);

	// bind data as float for a single channel
	glTexImage2D(GL_TEXTURE_2D, 0, GL_R32F,
		m_perlinDimensions, m_perlinDimensions, 0, GL_RED, GL_FLOAT, m_perlinData);

	// enable blending else samples must be "exact" centre of texels
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// set wrap to stop errors at edge of noise sampling
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	// unbind texture
	glBindTexture(GL_TEXTURE_2D, 0);

#pragma endregion



	//setup some matrices
	
	mat4 m_view = lookAt(vec3(0.0, 60.0, 60.0), vec3(5.0, 0.0, 0.0), vec3(0.0, 1.0, 0.0));
	mat4 m_projection = glm::perspective(glm::pi<float>()*0.25f, 16 / 9.f, 0.1f, 1000.f);
	mat4 m_projectionViewMatrix = m_projection * m_view;
	//end setup matrices

	unsigned int projectionViewUniform = glGetUniformLocation(m_shader, "ProjectionViewModel");
	//start using shader...
	glUseProgram(m_shader);
	//because we are sending it to the uniform with this function
	glUniformMatrix4fv(projectionViewUniform, 1, false, value_ptr(m_projectionViewMatrix));

	while (glfwWindowShouldClose(window) == false && glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS)
	{
		glClearColor(0.25f, 0.25f, 0.25f, 1);
		glEnable(GL_DEPTH_TEST);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		
		
		
		int texUniform = glGetUniformLocation(m_shader, "noiseTexture");
		glUniform1i(texUniform, 0);
		
		glBindVertexArray(m_VAO); 

			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, m_perlinTexture);
			
			//draw
			glDrawElements(GL_TRIANGLES, m_indexCount, GL_UNSIGNED_INT, 0);
		//unbind

		glBindVertexArray(0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}
