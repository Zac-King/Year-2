#include "GalacticBody.h"

GalacticBody::GalacticBody(vec3 a, vec3 c, float s)
{
	pos = a;
	centerPos = c;
	speed = s;
	angle = 1;
}

void GalacticBody::Orbit()
{
	angle += speed;

	float radius = sqrt(((pos.x - centerPos.x) * (pos.x - centerPos.x)) + ((pos.z - centerPos.z) * (pos.z - centerPos.z)));
	float radian = (angle + (3.14 / 180));

	if (angle > 360)
	{
		angle = angle - 360;
	}

	pos.x = (centerPos.x + radius * sin(radian));
	pos.z = (centerPos.z + radius * cos(radian));
}

vec3 GalacticBody::getPos()
{
	return pos;
}

void GalacticBody::Draw()
{
					// Posisition // Rad // Rows // Columns // Color
	Gizmos::addSphere(pos, 0.3f, 15, 15, vec4(0.15f, 0.25f, 0.35f, 1));
}

void GalacticBody::Update()
{
	Orbit();
	Draw();
}