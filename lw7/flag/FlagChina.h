#pragma once

#include "../../shader/Program.h"
#include <cmath>
#include <iostream>

class FlagChina
{
public:
	FlagChina()
		: m_backgroundProgram(R"(
void main()
{
	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
}
)",
			  R"(
void main()
{
	gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);
}
)"),
		m_starProgram(R"(
void main()
{
	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
}
)",
			R"(
#version 120

bool IsInsideStar(vec2 uv, vec2 center, float scale)
{
	vec2 p = uv - center;
	float r = length(p);
	float a = atan(p.y, p.x);
	float spokes = 5.0;
	float star = cos(spokes * a) * 0.3 + 0.7;
	return r < scale * star;
}

void main()
{
	vec2 uv = gl_FragCoord.xy / vec2(800, 600);

	vec4 color = vec4(0.0, 0.0, 0.0, 0.0);

	vec2 bigStarCenter = vec2(0.1, 0.85);
	vec2 smallStars[4];
	smallStars[0] = vec2(0.2, 0.95);
	smallStars[1] = vec2(0.25, 0.88);
	smallStars[2] = vec2(0.25, 0.78);
	smallStars[3] = vec2(0.2, 0.72);

	if (IsInsideStar(uv, bigStarCenter, 0.04))
	{
		color = vec4(1.0, 1.0, 0.0, 1.0);
	}

	for (int i = 0; i < 4; ++i)
	{
		if (IsInsideStar(uv, smallStars[i], 0.015))
		{
			color = vec4(1.0, 1.0, 0.0, 1.0);
		}
	}

	gl_FragColor = color;
}
)")
	{
	}

	void Render()
	{
		__glewUseProgram(m_backgroundProgram.GetId());
		DrawQuad(0.0f);
		__glewUseProgram(0);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		__glewUseProgram(m_starProgram.GetId());
		DrawQuad(0.1f);
		__glewUseProgram(0);

		glDisable(GL_BLEND);
	}

private:
	static void DrawQuad(float z)
	{
		glBegin(GL_QUADS);
		glVertex3f(-1.0f, -1.0f, z);
		glVertex3f(1.0f, -1.0f, z);
		glVertex3f(1.0f, 1.0f, z);
		glVertex3f(-1.0f, 1.0f, z);
		glEnd();
	}

private:
	Program m_backgroundProgram;
	Program m_starProgram;
};
