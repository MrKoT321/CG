#pragma once

#include "../../shader/Program.h"
#include <GL/glew.h>
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

class Transformation
{
public:
	Transformation()
		: m_program(vertexShaderSource, fragmentShaderSource)
	{
	}

	void Update()
	{
		m_progress += m_direction * m_speed;
		if (m_progress >= 1.0f)
		{
			m_direction = -1;
		}
		else if (m_progress <= 0.0f)
		{
			m_direction = 1;
		}
	}

	void Render()
	{
		__glewUseProgram(m_program.GetId());

		GLint loc = glGetUniformLocation(m_program.GetId(), "progress");
		glUniform1f(loc, m_progress);
		DrawSurface();

		__glewUseProgram(0);
	}

private:
	void DrawSurface() const
	{
		const int rows = 100;
		const int cols = 100;

		glBegin(GL_TRIANGLES);
		for (int i = 0; i < rows - 1; ++i)
		{
			for (int j = 0; j < cols - 1; ++j)
			{
				float x0 = -1.0f + 2.0f * i / (rows - 1);
				float y0 = -1.0f + 2.0f * j / (cols - 1);
				float x1 = -1.0f + 2.0f * (i + 1) / (rows - 1);
				float y1 = -1.0f + 2.0f * (j + 1) / (cols - 1);

				auto morph = [&](float x, float y) -> glm::vec3 {
					float z1 = x * x + y * y;
					float z2 = x * x * x - 3 * x * y * y;
					float z = (1.0f - m_progress) * z1 + m_progress * z2;
					return { x, y, z };
				};

				glm::vec3 p00 = morph(x0, y0);
				glm::vec3 p10 = morph(x1, y0);
				glm::vec3 p11 = morph(x1, y1);
				glm::vec3 p01 = morph(x0, y1);

				glVertex3d(p00.x, p00.y, p00.z);
				glVertex3d(p10.x, p10.y, p10.z);
				glVertex3d(p11.x, p11.y, p11.z);

				glVertex3d(p11.x, p11.y, p11.z);
				glVertex3d(p01.x, p01.y, p01.z);
				glVertex3d(p00.x, p00.y, p00.z);
			}
		}
		glEnd();
	}

private:
	Program m_program;

	float m_progress = 0.0f;
	int m_direction = 1;
	float m_speed = 0.01f;

	static constexpr const char* vertexShaderSource = R"(
uniform float progress;

float z1(float x, float y) {
	return x * x + y * y;
}

float z2(float x, float y) {
	return x * x * x - 3.0 * x * y * y;
}

void main()
{
	vec4 pos = gl_Vertex;

	float morphZ = mix(z1(pos.x, pos.y), z2(pos.x, pos.y), progress);
	pos.z = morphZ;

	gl_Position = gl_ModelViewProjectionMatrix * pos;

	float r = 0.5 + 0.5 * sin(pos.z * pos.y);
	float g = 0.5 + 0.5 * cos(pos.z * pos.x);
	float b = 0.5 + 0.5 * sin(pos.x + pos.y);

	gl_FrontColor = vec4(r, g, b, 1.0);
}
	)";

	static constexpr const char* fragmentShaderSource = R"(
void main()
{
	gl_FragColor = gl_Color;
}
	)";
};
