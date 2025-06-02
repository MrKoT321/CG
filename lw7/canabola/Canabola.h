#pragma once

#include "../../shader/Program.h"
#include <cmath>

class Canabola
{
public:
	Canabola()
		: m_program(R"(
float calculateCanabolaR(float x)
{
	return (1.0 + sin(x)) * (1.0 + 0.9 * cos(8.0 * x)) * (1.0 + 0.1 * cos(24.0 * x)) * (0.5 + 0.2 * cos(140.0 * x));
}

const vec4 color1 = vec4(0.3, 0.6, 0.3, 1.0);
const vec4 color2 = vec4(0, 1.0, 0, 1.0);

void main()
{
	vec4 pos = gl_Vertex;
	float x = pos.x;
	float canabolaR = calculateCanabolaR(x);

	pos.y = canabolaR * sin(x) - 1.0;
	pos.x = canabolaR * cos(x);

	gl_Position = gl_ModelViewProjectionMatrix * pos;
	gl_FrontColor = mix(color1, color2, mod(pos.y, 0.1) * 10.0);
}
)",
			  R"(
void main()
{
	gl_FragColor = gl_Color;
}
)")
	{
	}

	void Render()
	{
		__glewUseProgram(m_program.GetId());

		glBegin(GL_LINE_STRIP);
		{
			for (int i = 0; i < 2000; i++)
			{
				double x = 2.0 * M_PI * i / 2000.0;
				glVertex3d(x, 1, 0);
			}
		}
		glEnd();

		__glewUseProgram(0);
	}

private:
	Program m_program;
};