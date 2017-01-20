#pragma once
#include <glm/glm.hpp>

class CButterfly
{
public:
	CButterfly(size_t size, const glm::fvec2 &pos);
	void Draw();
	~CButterfly();
private:
	size_t m_size;
	glm::fvec2 m_position;
};

