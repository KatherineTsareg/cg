#pragma once
#include "stdafx.h"
#include "Butterfly.h"
#include <glm/glm.hpp>
#include <vector>

class CSky
{
public:
	CSky(glm::ivec2 const& size);
	void Draw();
	~CSky();
private:
	glm::ivec2 m_windowSize;
	std::vector<std::unique_ptr<CButterfly>> m_butterflies;

	void DrawSun();
	void DrawCloud(glm::fvec2 const& begin, glm::ivec2 const& size);
};

