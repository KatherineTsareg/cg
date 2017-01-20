#pragma once

#include "libchapter2.h"
#include "HeightsMap.h"


class CLandscape
{
public:
	CLandscape();
	void Draw();
	~CLandscape() = default;

private:
	CHeightsMap m_map;
	CTexture2DUniquePtr m_pEarthTexture;

	void LoadMap();
};
