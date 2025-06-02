#pragma once

#include "../../shader/Program.h"
#include <GL/glew.h>
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

class Transformation
{
public:
	Transformation()
		: m_program(vertexShaderSource, fragmentShaderSource)
	{
		m_view = glm::lookAt(glm::vec3(4, 3, -2), glm::vec3(1, 0, 0), glm::vec3(0, 1, 0));
		m_projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);
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
					float z2 = x * x - y * y;
					float z = (1.0f - m_progress) * z1 + m_progress * z2;
					return {x, y, z};
				};

				glm::vec3 p00 = morph(x0, y0);
				glm::vec3 p10 = morph(x1, y0);
				glm::vec3 p11 = morph(x1, y1);
				glm::vec3 p01 = morph(x0, y1);

				glVertexAttrib3f(0, p00.x, p00.y, p00.z);
				glVertexAttrib3f(0, p10.x, p10.y, p10.z);
				glVertexAttrib3f(0, p11.x, p11.y, p11.z);

				glVertexAttrib3f(0, p11.x, p11.y, p11.z);
				glVertexAttrib3f(0, p01.x, p01.y, p01.z);
				glVertexAttrib3f(0, p00.x, p00.y, p00.z);
			}
		}
		glEnd();
	}

private:
	Program m_program;

	float m_progress = 0.0f;
	int m_direction = 1;
	float m_speed = 0.01f;

	float m_scale = 1.0f;
	float m_rotationX, m_rotationY{};

	glm::mat4 m_view{};
	glm::mat4 m_projection{};

	static constexpr const char* vertexShaderSource = R"(
		#version 330 core
		layout(location = 0) in vec3 position;

		uniform float progress;
		uniform mat4 model;
		uniform mat4 view;
		uniform mat4 projection;

		out vec3 fragPosition;

		void main()
		{
			vec3 initial_position = vec3(position.x, position.y, position.x * position.x + position.y * position.y);
			vec3 final_position = vec3(position.x, position.y, position.x * position.x - position.y * position.y);
			vec3 morphed_position = mix(initial_position, final_position, progress);

			fragPosition = morphed_position;
			gl_Position = projection * view * model * vec4(morphed_position, 1.0);
		}
	)";

	static constexpr const char* fragmentShaderSource = R"(
		#version 330 core

		in vec3 fragPosition;
		out vec4 color;

		void main()
		{
			float r = 0.5 + 0.5 * sin(10.0 * fragPosition.x * fragPosition.y);
			float g = 0.5 + 0.5 * cos(10.0 * fragPosition.y * fragPosition.z);
			float b = 0.5 + 0.5 * sin(10.0 * fragPosition.z * fragPosition.x);

			color = vec4(r, g, b, 1.0);
		}
	)";
};
