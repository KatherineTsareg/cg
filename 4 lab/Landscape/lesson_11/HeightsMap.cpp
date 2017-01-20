#include "stdafx.h"
#include "HeightsMap.h"
#include <stdint.h>

using namespace std;
using namespace glm;

CHeightsMap::CHeightsMap()
{
}

void CHeightsMap::Load(glm::ivec2 pos, glm::ivec2 size, GLfloat const * mapData)
{
	m_beginPos = pos;
	m_size = size;
	m_displayList = 0;

	memcpy(heightMap, mapData, m_size.x * m_size.y * sizeof(GLfloat));
}

void CHeightsMap::Upload()
{
	m_displayList = glGenLists(1);

	glNewList(m_displayList, GL_COMPILE);
	float y0 = m_beginPos.y;
	float du = 1.0f / m_size.x;
	float dv = 1.0f / m_size.y;
	float v = 0;
	for (int row = 0; row < m_size.x - 1; ++row, y0 += STEP, v += dv)
	{
		float u = 0;
		float x = m_beginPos.x;
		glBegin(GL_TRIANGLE_STRIP);
		for (int column = 0; column < m_size.y; ++column, x += STEP, u += du)
		{
			float y1 = (y0 + STEP);
			float z1 = heightMap[(row + 1) * m_size.x + column];
			float y2 = y0;
			float z2 = heightMap[row * m_size.y + column];
			glTexCoord2f(v + dv, u);
			glVertex3f(x, z1, -y1);
			glTexCoord2f(v, u);
			glVertex3f(x, z2, -y2);
		}
		glEnd();
	}
	glEndList();

}

void CHeightsMap::Draw()
{
	if (!m_displayList)
	{
		Upload();
	}
	glCallList(m_displayList);
}

void CHeightsMap::Destroy()
{
	if (m_displayList != 0)
	{
		glDeleteLists(m_displayList, 1);
		m_displayList = 0;
	}
}

CHeightsMap::~CHeightsMap()
{
}
