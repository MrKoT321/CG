#pragma once
#include "../../base/BaseWindow.h"
#include "Labyrinth.h"
#include <glm/ext/matrix_transform.hpp>
#include <glm/mat4x4.hpp>

class Window : public BaseWindow
{
public:
	Window(int w, int h, const char* title);

private:
	void OnResize(int width, int height) override;
	void OnRunStart() override;
	void Draw(int width, int height) override;

	void ProcessInput();
	void SetupCamera() const;

private:
	Labyrinth m_labyrinth;
	glm::vec3 m_playerPos = { 1.5f, 0.2f, 1.5f };
	float m_playerYaw = 0.0f;
	glm::dmat4x4 m_cameraMatrix = glm::lookAt(
		glm::dvec3{ 1.0, 1.0, 1.0 },
		glm::dvec3{ 0.0, 0.0, 0.0 },
		glm::dvec3{ 0.0, 0.0, 1.0 });
};