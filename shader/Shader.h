#pragma once
#include <GL/glew.h>
#include <cassert>
#include <stdexcept>
#include <string>
#include <utility>

class Shader
{
public:
	explicit Shader(GLenum type)
		: m_shader{ __glewCreateShader(type) }
	{
		if (!m_shader)
		{
			throw std::runtime_error("Failed to create shader");
		}
	}

	Shader(const Shader&) = delete;
	Shader& operator=(const Shader&) = delete;

	Shader(Shader&& other) noexcept
		: m_shader(std::exchange(other.m_shader, 0))
	{
	}

	Shader& operator=(Shader&& rhs) noexcept
	{
		std::swap(m_shader, rhs.m_shader);
		return *this;
	}

	~Shader()
	{
		__glewDeleteShader(m_shader);
	}

	void SetSource(const char* text) const noexcept
	{
		assert(text);
		assert(m_shader);
		__glewShaderSource(m_shader, 1, &text, nullptr);
	}

	void Compile() const noexcept
	{
		assert(m_shader);
		__glewCompileShader(m_shader);
	}

	void GetParameter(GLenum paramName, GLint* p) const noexcept
	{
		__glewGetShaderiv(m_shader, paramName, p);
	}

	[[nodiscard]] std::string GetInfoLog() const
	{
		int infoLogLength = 0;
		GetParameter(GL_INFO_LOG_LENGTH, &infoLogLength);
		std::string log(static_cast<size_t>(infoLogLength), ' ');
		GLsizei actualSize = 0;
		__glewGetShaderInfoLog(m_shader, infoLogLength, &actualSize, log.data());
		log.resize(static_cast<size_t>(actualSize));
		return log;
	}

	[[nodiscard]] bool IsCompiled() const noexcept
	{
		int compileStatus = GL_FALSE;
		GetParameter(GL_COMPILE_STATUS, &compileStatus);
		return compileStatus == GL_TRUE;
	}

	operator GLuint() const noexcept
	{
		return m_shader;
	}

private:
	GLuint m_shader = 0u;
};

static_assert(!std::is_copy_constructible_v<Shader> && !std::is_copy_assignable_v<Shader>);