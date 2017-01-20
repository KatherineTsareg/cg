#pragma once

#include <vector>
#include <glm/glm.hpp>

class CPolarCoordinateSystem
{
public:
	CPolarCoordinateSystem(const glm::ivec2 & windowSize);
	void DisplayGraphOfFunction();
	~CPolarCoordinateSystem();

private:
	void StrokeAxes();
	void DrawAdditionalAxes();

	glm::ivec2 m_begin;
	std::vector<glm::fvec2> m_axes;
	glm::ivec2 m_scale;
	const int m_line_count = 6;
	const int m_circleStep = 45;
};

