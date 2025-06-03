#include "Labyrinth.h"

#include "../../texture/TextureLoader.h"

#include <GL/gl.h>

Labyrinth::Labyrinth()
{
	m_walls = {
		{ 3, 1, 6, 4, 2, 6, 5, 3, 1, 5, 2, 4, 6, 1, 5, 1 },
		{ 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 2 },
		{ 5, 0, 2, 5, 4, 3, 6, 6, 4, 1, 4, 5, 2, 0, 6, 3 },
		{ 6, 0, 4, 6, 6, 5, 1, 1, 6, 4, 6, 6, 3, 0, 1, 4 },
		{ 1, 0, 3, 1, 1, 2, 2, 5, 2, 2, 5, 1, 5, 0, 2, 5 },
		{ 2, 0, 5, 2, 3, 4, 3, 2, 3, 3, 0, 3, 1, 0, 3, 6 },
		{ 3, 0, 6, 3, 5, 6, 4, 4, 5, 5, 0, 6, 4, 0, 4, 1 },
		{ 4, 0, 1, 4, 6, 1, 5, 3, 6, 1, 0, 2, 6, 0, 5, 2 },
		{ 5, 0, 4, 5, 2, 4, 3, 6, 1, 4, 0, 5, 1, 0, 6, 3 },
		{ 6, 0, 6, 0, 5, 3, 6, 2, 4, 6, 0, 1, 2, 0, 1, 4 },
		{ 1, 1, 1, 0, 3, 5, 1, 1, 3, 1, 1, 4, 3, 0, 2, 5 },
		{ 2, 0, 3, 0, 4, 2, 4, 4, 5, 5, 5, 0, 5, 0, 3, 6 },
		{ 3, 0, 5, 0, 2, 6, 5, 2, 6, 6, 6, 0, 4, 0, 4, 1 },
		{ 4, 0, 2, 0, 5, 1, 6, 3, 2, 2, 1, 0, 6, 0, 5, 2 },
		{ 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 3 },
		{ 6, 5, 1, 3, 4, 2, 4, 3, 1, 3, 2, 1, 5, 1, 4, 6 }
	};
	m_width = m_walls[0].size();
	m_height = m_walls.size();
}

void Labyrinth::Draw() const
{
	if (!m_texturesLoaded)
	{
		LoadTextures();
	}
	DrawFloor();
	DrawCeiling();
	DrawWalls();
}

bool Labyrinth::CanMove(float x, float z) const
{
	if (x < 0 || x >= m_width || z < 0 || z >= m_height)
	{
		return false;
	}

	return m_walls[static_cast<int>(x)][static_cast<int>(z)] == 0;
}

void Labyrinth::DrawFloor() const
{
	glDisable(GL_TEXTURE_2D);
	glColor3f(m_floorColor.r, m_floorColor.g, m_floorColor.b);
	glBegin(GL_QUADS);
	glVertex3f(0, 0, 0);
	glVertex3f(m_width, 0, 0);
	glVertex3f(m_width, 0, m_height);
	glVertex3f(0, 0, m_height);
	glEnd();
}

void Labyrinth::DrawCeiling() const
{
	glDisable(GL_TEXTURE_2D);
	glColor3f(m_ceilingColor.r, m_ceilingColor.g, m_ceilingColor.b);
	glBegin(GL_QUADS);
	glVertex3f(0, 1, 0);
	glVertex3f(m_width, 1, 0);
	glVertex3f(m_width, 1, m_height);
	glVertex3f(0, 1, m_height);
	glEnd();
}

void Labyrinth::DrawWalls() const
{
	glEnable(GL_TEXTURE_2D);
	glColor3f(1, 1, 1);
	for (int x = 0; x < static_cast<int>(m_width); x++)
	{
		for (int z = 0; z < static_cast<int>(m_height); z++)
		{
			const auto value = m_walls[x][z];
			if (value)
			{
				const auto xf = static_cast<float>(x);
				const auto zf = static_cast<float>(z);

				m_textures[value - 1]->Bind();

				DrawWall(xf, zf, xf, zf + 1);
				DrawWall(xf + 1, zf, xf + 1, zf + 1);
				DrawWall(xf, zf, xf + 1, zf);
				DrawWall(xf, zf + 1, xf + 1, zf + 1);
			}
		}
	}
}

void Labyrinth::DrawWall(float x1, float z1, float x2, float z2)
{
	glBegin(GL_TRIANGLE_STRIP);

	glTexCoord2f(0, 1);
	glVertex3f(x1, 0, z1);

	glTexCoord2f(0, 0);
	glVertex3f(x1, 1, z1);

	glTexCoord2f(1, 1);
	glVertex3f(x2, 0, z2);

	glTexCoord2f(1, 0);
	glVertex3f(x2, 1, z2);

	glEnd();
}

void Labyrinth::LoadTextures() const
{
	m_textures.reserve(TEXTURE_NAMES.size());
	TextureLoader loader;
	for (const auto& name : TEXTURE_NAMES)
	{
		m_textures.emplace_back(std::make_unique<Texture2D>());
		m_textures.back()->Attach(loader.LoadTexture2D(name));
	}
	m_texturesLoaded = true;
}
