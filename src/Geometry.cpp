#include "Geometry.h"

Geometry *self = nullptr;
Geometry::Geometry()
{
	//Setup some geometry to draw
	//MyVertex will be the storage container for our vertex information
	Vertex Vertices[] = {
		{ -1.f,-1.f,0.f },
		{ 0.f,-1.f,1.f },
		{ 1.f,-1.f,0.f },
		{ 0.f,1.f,0.f }, 
	};

	Color Colors[] = {
		{ -1.f,-1.f,0.f, 1.0f },
		{ 0.f,-1.f,1.f, 1.0f },
		{ 1.f,-1.f,0.f, 1.0f },
		{ 0.f,1.f,0.f, 1.0f }, 
	};

	GLuint Indices[] = {
		0, 3, 1,
		1, 3, 2,
		2, 3, 0,
		0, 1, 2
	};


	//BEGIN SHADER SETUP
	std::string vshader = LoadShader("vertex_shader.vert");
	std::string fshader = LoadShader("fragment_shader.frag");
	const char * vsSource = vshader.c_str();
	const char * fsSource = fshader.c_str();
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
	glUseProgram(m_shader);
	GLuint vertposition = glGetAttribLocation(m_shader, "Position");
	GLuint vertcolor = glGetAttribLocation(m_shader, "Color");
	//Now we put it on the graphics card
	//generate your buffer on the graphics card
	//this contains all the vertices
	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);

	glGenBuffers(1, &m_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(vertposition,
		3,
		GL_FLOAT,
		GL_FALSE,
		0,
		((void*)0));
	glEnableVertexAttribArray(vertposition);
	glGenBuffers(1, &m_CBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_CBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Colors), Colors, GL_STATIC_DRAW);
	glVertexAttribPointer(vertcolor,
		4,
		GL_FLOAT,
		GL_FALSE,
		0,
		((void*)(0)));
	glEnableVertexAttribArray(vertcolor);

	glGenBuffers(1, &m_IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices), Indices, GL_STATIC_DRAW);
	//unbind now that we have generated and populated

	glEnableVertexAttribArray(0);
	glBindVertexArray(0);

	glDeleteShader(vs);
	glDeleteShader(fs);
}

void Geometry::Draw(glm::mat4 model, glm::mat4 view, glm::mat4 projection)
{
	glUseProgram(m_shader);
	GLuint projectionMatrixID = glGetUniformLocation(m_shader, "Projection");
	GLuint viewMatrixID = glGetUniformLocation(m_shader, "View");
	GLuint modelMatrixID = glGetUniformLocation(m_shader, "Model");
	
	glUniformMatrix4fv(projectionMatrixID, 1, false, &projection[0][0]);
	glUniformMatrix4fv(viewMatrixID, 1, false, &view[0][0]);
	glUniformMatrix4fv(modelMatrixID, 1, false, &model[0][0]);
	glBindVertexArray(m_VAO);
	//draw
	glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, ((void*)0));
	//unbind		
	glBindVertexArray(0);
}

std::string Geometry::LoadShader(std::string file)
{
	std::ifstream source(file);
	char shader[1024];
	int i = 0;
	char c;
	while (source.get(c))
	{
		shader[i] = c;
		i++;
	}
	shader[i] = '\0'; 
	source.close();

	return shader;
}

Geometry::~Geometry()
{
	
}
