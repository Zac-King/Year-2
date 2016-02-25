#include <GLFW/glfw3.h> 
#include <glm\glm.hpp>
#include <glm\ext.hpp>
#include <iostream>

using glm::vec3;

class Grid
{
public:
	vec3 *p;
	int width, length;
	float displacement;

	Grid(int w, int l, float d)
	{
		width = w;
		length = l;
		displacement = d;
	}
	void GenGrid()
	{
		int index = 0;
		for (int i = 0; i < width; i++)
		{
			for (int j = 0; j < length; j++)
			{
				p[index] = {i,0,j};
				index++;
				std::cout << index;
			}
		}
		for (int k = 0; k < (width * length); k++)
		{
			std::cout << "{ " << p[k].x << ", "<< p[k].y << ", " << p[k].z << " }\n";
		}
	}
};
