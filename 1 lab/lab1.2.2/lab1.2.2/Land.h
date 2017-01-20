#pragma once
#include "stdafx.h"
#include <glm/glm.hpp>

class CLand
{
public:
	CLand(glm::ivec2 const& windowSize);
	void Draw();
	bool IsInRect(const glm::fvec4 & rect, const glm::fvec2 & coord);
	glm::fvec4 GetLakeRect();
	~CLand();
private:
	glm::fvec4 m_landRect;
	glm::ivec2 m_windowSize;
	glm::fvec4 m_lakeCoordinates;
	std::vector<glm::fvec2> m_grassCoordinates;
	
	void DrawMainField();
	void DrawALake();
};

