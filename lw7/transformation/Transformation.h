#pragma once

#include "../../shader/Program.h"
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include <cmath>

class Transformation
{
public:
	Transformation()
		: m_program(vertexShaderSource, fragmentShaderSource)
	{
		m_progress = 0.0f;
		m_direction = 1;
		m_speed = 0.01f;

		m_scale = 1.0f;
		m_rotationX = 0.0f;
		m_rotationY = 0.0f;

		m_view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
		m_projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);
	}

	void Update()
	{
		m_progress += m_direction * m_speed;
		if (m_progress >= 1.0f) m_direction = -1;
		else if (m_progress <= 0.0f) m_direction = 1;
	}

	void Render()
	{
		glUseProgram(m_program.GetId());

		glm::mat4 model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(m_scale));
		model = glm::rotate(model, glm::radians(m_rotationY), glm::vec3(0, 1, 0));
		model = glm::rotate(model, glm::radians(m_rotationX), glm::vec3(1, 0, 0));

		glUniform1f(glGetUniformLocation(m_program.GetId(), "progress"), m_progress);
		glUniformMatrix4fv(glGetUniformLocation(m_program.GetId(), "model"), 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(glGetUniformLocation(m_program.GetId(), "view"), 1, GL_FALSE, glm::value_ptr(m_view));
		glUniformMatrix4fv(glGetUniformLocation(m_program.GetId(), "projection"), 1, GL_FALSE, glm::value_ptr(m_projection));

		DrawSurface();

		glUseProgram(0);
	}

private:
	void DrawSurface()
	{
		const int rows = 100;
		const int cols = 100;

		glBegin(GL_LINES);
		for (int i = 0; i < rows - 1; ++i)
		{
			for (int j = 0; j < cols - 1; ++j)
			{
				float x0 = -1.0f + 2.0f * i / (rows - 1);
				float y0 = -1.0f + 2.0f * j / (cols - 1);
				float z0 = x0 * x0 + y0 * y0;

				float x1 = -1.0f + 2.0f * (i + 1) / (rows - 1);
				float y1 = y0;
				float z1 = x1 * x1 + y1 * y1;

				float x2 = x0;
				float y2 = -1.0f + 2.0f * (j + 1) / (cols - 1);
				float z2 = x2 * x2 + y2 * y2;

				glVertex3f(x0, y0, z0);
				glVertex3f(x1, y1, z1);

				glVertex3f(x1, y1, z1);
				glVertex3f(x2, y2, z2);

				glVertex3f(x2, y2, z2);
				glVertex3f(x0, y0, z0);
			}
		}
		glEnd();
	}

private:
	Program m_program;

	float m_progress;
	int m_direction;
	float m_speed;

	float m_scale;
	float m_rotationX, m_rotationY;

	glm::mat4 m_view;
	glm::mat4 m_projection;

	static constexpr const char* vertexShaderSource = R"(
		#version 330 core
		layout(location = 0) in vec3 position;

		uniform float progress;
		uniform mat4 model;
		uniform mat4 view;
		uniform mat4 projection;

		void main()
		{
			vec3 initial_position = vec3(position.x, position.y, position.x * position.x + position.y * position.y);
			vec3 final_position = vec3(position.x, position.y, position.x * position.x - position.y * position.y);
			vec3 morphed_position = mix(initial_position, final_position, progress);

			gl_Position = projection * view * model * vec4(morphed_position, 1.0);
		}
	)";

	static constexpr const char* fragmentShaderSource = R"(
		#version 330 core
		out vec4 color;

		void main()
		{
			color = vec4(1.0, 1.0, 1.0, 1.0);
		}
	)";
};
