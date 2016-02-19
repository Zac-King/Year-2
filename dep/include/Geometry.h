#pragma once
#include <vector>
#include <gl_core_4_4.h>
#define GLM_SWIZZLE
#define GLM_FORCE_PURE
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <string>
#include "stdio.h"
#include <fstream>

using glm::mat4;
using glm::vec3;
using glm::vec2;





class Geometry
{
public:
	Geometry();
	void Draw(glm::mat4 model, glm::mat4 view, glm::mat4 projection);
	~Geometry();
private:
	struct Vertex
	{
		float x, y, z;        //Vertex	 
	};

	struct Color
	{
		float r, g, b, a;
	};
	GLuint m_VAO;
	GLuint m_VBO;
	GLuint m_IBO;
	GLuint m_CBO;
	GLuint m_index_count;
	GLuint m_shader; 
	 
	std::string LoadShader(std::string file);
};

