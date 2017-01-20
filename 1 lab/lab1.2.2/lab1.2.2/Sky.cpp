#include "Sky.h"
#include "stdafx.h"
#include <GL/glew.h>
#include <GL/gl.h>
#include <glm/vec2.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace glm;

CSky::CSky(glm::ivec2 const& size)
	:m_windowSize(size)
{
	srand(time(0));
	for (size_t i = 0; i < 10; i++)
	{
		float size = (rand() % 20) + 10; // [10; 30]
		float posY = (rand() % 800);
		float posX = 30 + i * 100;
		fvec2 pos = {posX, posY};
		auto pButterfly = std::make_unique<CButterfly>(size, pos);
		m_butterflies.push_back(std::move(pButterfly));
	}
}

void CSky::Draw()
{
	DrawSun();
	DrawCloud({ m_windowSize.x * 1.f / 5.f, m_windowSize.y / 8.f }, { 60, 40 });
	DrawCloud({ m_windowSize.x / 2.f, m_windowSize.y / 6.f }, { 75, 40 });
	DrawCloud({ m_windowSize.x * 4.f / 5.f, m_windowSize.y / 7.f }, { 60, 40 });

	for (const auto &butterfly : m_butterflies)
	{
		butterfly->Draw();
	}
}

CSky::~CSky()
{
}

void CSky::DrawSun()
{
	fvec2 beginCoord = { m_windowSize.x * 2.f / 3.f, m_windowSize.y / 5.f};
	glColor3f(250.f / 255.f, 250.f / 255.f, 52.f / 255.f); //желтый цвет солнышка
	glBegin(GL_TRIANGLE_FAN);
	for (size_t i = 0; i <= 360; i++)
	{
		glVertex2d(beginCoord.x + cos(i) * 50.f, beginCoord.y + (sin(i) * 50.f));
	}
	glEnd();
}

void CSky::DrawCloud(fvec2 const& begin, ivec2 const& size)
{
	glColor3f(33.f / 255.f, 153.f / 255.f, 204.f / 255.f);
	glBegin(GL_POLYGON);
	glVertex2d(begin.x, begin.y);
	for (size_t i = 0; i < 360; i++)
	{
		glVertex2d(begin.x + cos(i) * size.x, begin.y + sin(i) * size.y);
	}
	for (size_t i = 0; i < 360; i++)
	{
		glVertex2d(begin.x - size.x + cos(i) * size.x * 2.f / 3.f, begin.y + sin(i) * size.y * 2.f / 3.f);
	}
	for (size_t i = 0; i < 360; i++)
	{
		glVertex2d(begin.x + size.x + cos(i) * size.x * 2.f / 3.f, begin.y + sin(i) * size.y * 2.f / 3.f);
	}
	glEnd();

}
