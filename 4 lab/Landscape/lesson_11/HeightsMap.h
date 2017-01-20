#pragma once
#define TILE_SIZE 128
#define VERTEX_TILE_SIZE (TILE_SIZE + 1)
#define	STEP 10

#include "libchapter2.h"
#include <glm/glm.hpp>


class CHeightsMap 
{
public:
	CHeightsMap();
	void Load(glm::ivec2 pos, glm::ivec2 size, GLfloat const * mapData);
	void Draw();
	~CHeightsMap();
private:
	// карта высот
	GLfloat	heightMap[VERTEX_TILE_SIZE * VERTEX_TILE_SIZE];

	glm::fvec2 m_beginPos;
	glm::ivec2 m_size;

	// номер дисплейного списка для отрисовки тайла
	GLuint	m_displayList;

	void Upload();
	void Destroy();
};