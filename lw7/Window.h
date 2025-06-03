#pragma once
#include "canabola/Canabola.h"

#include "../base/BaseWindow.h"
#include "../base/GLEWInitializer.h"
#include "flag/FlagChina.h"
#include "transformation/Transformation.h"

#include <glm/ext/matrix_transform.hpp>
#include <glm/mat4x4.hpp>
#include <optional>

class Window final : public BaseWindow
{
public:
	Window(int w, int h, const char* title);

private:
	void OnMouseButton(int button, int action, [[maybe_unused]] int mods) override;
	void OnMouseMove(double x, double y) override;
	void RotateCamera(double xAngleRadians, double yAngleRadians);
	void OnResize(int width, int height) override;
	void OnRunStart() override;
	void InitShaders();
	void Draw(int width, int height) override;
	void SetupCameraMatrix();
	void OnKey(int /*key*/, int /*scanCode*/, int /*action*/, int /*mods*/) override;
	void OnIdle(double deltaTime) override;

	std::optional<GLEWInitializer> m_glewInitializer;
	std::optional<Canabola> m_canabola;
	std::optional<Transformation> m_transform;
	std::optional<FlagChina> m_flag;

	static constexpr double DISTANCE_TO_ORIGIN = 4;
	bool m_leftButtonPressed = false;
	glm::dvec2 m_mousePos = {};
	glm::dmat4x4 m_cameraMatrix = glm::lookAt(
		glm::dvec3{ 0.0, 0.0, DISTANCE_TO_ORIGIN },
		glm::dvec3{ 0.0, 0.0, 0.0 },
		glm::dvec3{ 0.0, 1.0, 0.0 });
};