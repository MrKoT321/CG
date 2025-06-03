#pragma once
#include "../../texture/Texture.h"
#include <memory>
#include <string>
#include <vector>
#include <glm/vec3.hpp>

class Labyrinth
{
public:
	Labyrinth();
	void Draw() const;
	[[nodiscard]] bool CanMove(float x, float z) const;

private:
	void DrawFloor() const;
	void DrawWalls() const;
	void DrawCeiling() const;
	static void DrawWall(float x1, float z1, float x2, float z2);
	void LoadTextures() const;

	glm::vec3 m_floorColor = { 0.2f, 0.2f, 0.2f };
	glm::vec3 m_ceilingColor = { 0.2f, 0.2f, 0.8f };

	std::vector<std::vector<int>> m_walls;
	float m_width, m_height;

	mutable std::vector<std::unique_ptr<Texture2D>> m_textures;
	mutable bool m_texturesLoaded{ false };

	static inline const std::vector<std::string> TEXTURE_NAMES{
		"../public/dream.png",
		"../public/from_laker.png",
		"../public/girl_with_the_pearl_earring.png",
		"../public/memory_persistence.png",
		"../public/monalisa.png",
		"../public/starry_night.png",
	};
};