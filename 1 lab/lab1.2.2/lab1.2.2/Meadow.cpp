#include "Meadow.h"
#include <GL/glew.h>
#include <GL/gl.h>
#include <glm/vec2.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>


namespace
{
	const glm::vec3 PURPLE = { 126.f / 255.f, 0.f, 138.f / 255.f };
	const glm::vec3 PINK = { 171.f / 255.f, 0.f, 34.f / 255.f };
	const glm::vec3 BLUE = { 36.f / 255.f, 151.f / 255.f, 171.f / 255.f };
	const glm::vec3 YELLOW = { 277.f / 255.f, 205.f / 255.f, 36.f / 255.f };
	std::vector<glm::vec3> COLOR_PALETTE = { PURPLE, PINK, BLUE };
	const size_t FLOWERS_COUNT = 65;
}


CMeadow::CMeadow(glm::ivec2 const& size)
	:m_land(size)
	,m_sky(size)
{
	ScatterFlowers();	
}

void CMeadow::Draw()
{
	m_land.Draw();
	
	for (const auto &flower : m_flowers)
	{
		flower->Draw();
	}
	m_sky.Draw();
}

void CMeadow::ScatterFlowers()
{
	srand(time(0));
	for (size_t i = 0; i < FLOWERS_COUNT; i++)
	{
		float minRadius = (rand() % 10) + 10; // [10; 20]
		float maxRadius = (rand() % 20) + 30; // [30; 50]
		int petalCount = (rand() % 4) + 5; //[5; 8]
		size_t centerColorIndex = (rand() % COLOR_PALETTE.size());
		size_t pentalColorIndex = (rand() % COLOR_PALETTE.size());
		float posY = (rand() % 400 + 300);
		float posX = 30 + i * 20;
		

		while (m_land.IsInRect(m_land.GetLakeRect(), {posX, posY}))
		{
			posY = (rand() % 400 + 300);
		}

		auto pFlower = std::make_unique<CFlower>(minRadius, maxRadius, petalCount);
		pFlower->SetCenterColor(COLOR_PALETTE[centerColorIndex]);
		pFlower->SetPetalColor(COLOR_PALETTE[pentalColorIndex]);
		pFlower->SetPosition({ posX, posY });
		m_flowers.push_back(std::move(pFlower));
	}
}
