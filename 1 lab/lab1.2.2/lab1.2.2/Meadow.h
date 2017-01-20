#pragma once
#include "stdafx.h"
#include "Land.h"
#include "Sky.h"
#include "Flower.h"
#include <glm/glm.hpp>

class CMeadow
{
public:
	CMeadow(glm::ivec2 const& size);
	void Draw();
	~CMeadow() = default;
private:
	CLand m_land;
	CSky m_sky;
	std::vector<std::unique_ptr<CFlower>> m_flowers;

	void ScatterFlowers();
};

