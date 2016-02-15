#include "Application.h" 
#include <gl_core_4_4.h>
#define GLM_SWIZZLE
#define GLM_FORCE_PURE
#include <glm/glm.hpp>

#include <glm/ext.hpp>
Application::Application(GLfloat *v, GLfloat *c, GLushort *e) 
{ 
	unsigned int len = 0;
	GLfloat* iter = v;	
	GLfloat* ptr;
	//& is the address-of operator, and can be read simply as "address of"
	//*is the dereference operator, and can be read as "value pointed to by"
	while (true)
	{
		GLfloat value = *iter;
		iter += sizeof(GLfloat);

		len++;
	}

	for (int i = 0; i < sizeof(v); ++i)
		printf("%f,", &v[i]);
	
	cube_vertices = v;
	for (int i = 0; i < sizeof(cube_vertices); ++i)
		printf("%f,", cube_vertices[i]);
	cube_colors = c;
	cube_elements = e;
}

int Application::startup()
{
	if (glfwInit() == false)
		return -1;

	window = glfwCreateWindow(1280, 720, "Computer Graphics", nullptr, nullptr);

	if (window == nullptr)
		glfwTerminate();

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

	glDeleteShader(vs);
	glDeleteShader(fs);

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
	glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices), cube_vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(vertposition,
		3,
		GL_FLOAT,
		GL_FALSE,
		0,
		((void*)0));
	glEnableVertexAttribArray(vertposition);
	glGenBuffers(1, &m_CBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_CBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cube_colors), cube_colors, GL_STATIC_DRAW);
	glVertexAttribPointer(vertcolor,
		4,
		GL_FLOAT,
		GL_FALSE,
		0,
		((void*)(0)));
	glEnableVertexAttribArray(vertcolor);

	glGenBuffers(1, &m_IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_elements), cube_elements, GL_STATIC_DRAW);
	//unbind now that we have generated and populated

	glEnableVertexAttribArray(0);
	glBindVertexArray(0);
	m_model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 0.0, -4.0));
	m_view = glm::lookAt(vec3(1, 5, 10), vec3(0), vec3(0, 1, 0));
	m_projection = glm::perspective(glm::pi<float>()*0.25f, 16 / 9.f, 0.1f, 1000.f);

	//end setup matrices
	projectionMatrixID = glGetUniformLocation(m_shader, "Projection");
	viewMatrixID = glGetUniformLocation(m_shader, "View");
	modelMatrixID = glGetUniformLocation(m_shader, "Model");
	timeFloatID = glGetUniformLocation(m_shader, "Time");
	return 1;
}

int Application::update()
{ 
	
	glUniformMatrix4fv(projectionMatrixID, 1, GL_FALSE, &m_projection[0][0]);
	glUniformMatrix4fv(viewMatrixID, 1, GL_FALSE, &m_view[0][0]);
	while (glfwWindowShouldClose(window) == false && glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS)
	{
		glClearColor(0.25f, 0.25f, 0.25f, 1);
		glEnable(GL_DEPTH_TEST);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUniform1f(timeFloatID, glfwGetTime());
		glUniformMatrix4fv(modelMatrixID, 1, GL_FALSE, &m_model[0][0]);
		glBindVertexArray(m_VAO);
		//draw
		int size;

		glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &size); //bc lazy to count how many indices

		glDrawElements(GL_TRIANGLES, size / sizeof(GLushort), GL_UNSIGNED_SHORT, ((void*)0));
		//unbind		
		glBindVertexArray(0);

		glfwSwapBuffers(window);
		glfwPollEvents();
		
		return 1;
	}
	return 0;

}

void Application::draw()
{
	glfwSwapBuffers(window);
	glfwPollEvents();
}

void Application::shutdown()
{
	std::printf("shutting down...");
	delete cube_colors;
	delete cube_elements;
	delete cube_vertices;
	glfwDestroyWindow(window);
	glfwTerminate();
} 
 
std::string Application::LoadShader(std::string file)
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