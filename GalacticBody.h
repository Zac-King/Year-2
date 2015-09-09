#pragma once
#include <Gizmos.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

using glm::vec3;
using glm::vec4;
using glm::mat4;


class GalacticBody
{
private:

	vec3 pos;
	vec3 centerPos;
	float speed;
	float angle;

public:
	GalacticBody(vec3 a, vec3 c, float s);

	vec3 getPos();
	void Orbit();
	void Draw();
	void Update();
};