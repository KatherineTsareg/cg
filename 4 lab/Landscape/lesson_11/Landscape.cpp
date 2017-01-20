#include "stdafx.h"
#include "Landscape.h"
#include "HeightsMap.h"
#include <stdint.h>

namespace
{
	const char HIGHT_MAP_PATH[] = "res/height.raw";
	const float HEIGHT_SCALE = 2.f;
	const float HEIGHT_OFFSET = HEIGHT_SCALE * 120;
	const char EARTH_TEX_PATH[] = "res/gc.bmp";
}
using namespace std;

CLandscape::CLandscape()
{
	LoadMap();

	CTexture2DLoader loader;
	loader.SetWrapMode(TextureWrapMode::REPEAT);
	m_pEarthTexture = loader.Load(EARTH_TEX_PATH);
}


void CLandscape::Draw()
{
	m_pEarthTexture->DoWhileBinded([&] {
		m_map.Draw();
	});
}


void CLandscape::LoadMap()
{
	ifstream inputFile(HIGHT_MAP_PATH, ios_base::binary);
	
	if (!inputFile.is_open())
	{
		throw std::runtime_error("Cannot open file for reading: " + string(HIGHT_MAP_PATH, sizeof(HIGHT_MAP_PATH)));
	}


	GLfloat heightMap[VERTEX_TILE_SIZE*VERTEX_TILE_SIZE];
	char depth;
	size_t i = 0;
	while (inputFile.get(depth) && (i < VERTEX_TILE_SIZE*VERTEX_TILE_SIZE))
	{
		heightMap[i++] = static_cast<BYTE>(depth) * HEIGHT_SCALE - HEIGHT_OFFSET;
	}
	
	inputFile.close();

	m_map.Load(glm::fvec2(-VERTEX_TILE_SIZE * STEP / 2.f, -VERTEX_TILE_SIZE * STEP / 2.f), glm::ivec2(VERTEX_TILE_SIZE, VERTEX_TILE_SIZE), &heightMap[0]);
}
