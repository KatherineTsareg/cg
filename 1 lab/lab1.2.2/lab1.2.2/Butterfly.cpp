#include "Butterfly.h"
#include "stdafx.h"
#include <GL/glew.h>
#include <GL/gl.h>
#include <glm/vec2.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>


using namespace glm;


CButterfly::CButterfly(size_t size, const glm::fvec2 &pos)
	:m_size(size)
	,m_position(pos)
{
}

void CButterfly::Draw()
{
	//заднее крыло
	glBegin(GL_POLYGON);
	glColor3f(277.f / 255.f, 205.f / 255.f, 120.f / 255.f);
	float posx = m_position.x + m_size / 2.f;
	float posy = m_position.y;
	glVertex2d(posx, posy);
	for (size_t i = 0; i < 360; i++)
	{
		glVertex2d(posx + cos(i) * m_size * 2.f / 4.f, posy + sin(i) * m_size * 4.f / 4.f);
	}
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(277.f / 255.f, 205.f / 255.f, 36.f / 255.f);
	posx = m_position.x + m_size * 2.f / 2.f;
	posy = m_position.y + m_size * 1.f / 8.f;
	glVertex2d(posx, posy);
	for (size_t i = 0; i < 360; i++)
	{
		glVertex2d(posx + cos(i) * m_size * 3.f / 4.f, posy + sin(i) * m_size * 4.f / 5.f);
	}
	glEnd();

	//тело
	glColor3f(0.f / 255.f, 0.f / 255.f, 0.f / 255.f);
	glBegin(GL_POLYGON);
	for (size_t i = 0; i < 360; i++)
	{
		glVertex2d(m_position.x + cos(i) * m_size + m_size, m_position.y + m_size * 3.f / 4.f + sin(i) * m_size / 4.f);
	}
	glEnd();

	//голова size = m_size / 3.f; pos = [m_pos.x, m_pos.y + 3/4 * m_size]
	glColor3f(0.f / 255.f, 0.f / 255.f, 0.f / 255.f);
	glBegin(GL_POLYGON);
	for (size_t i = 0; i < 360; i++)
	{
		glVertex2d(m_position.x + cos(i) * m_size / 3.f, m_position.y + m_size * 3.f / 4.f + sin(i) * m_size / 3.f);
	}
	glEnd();

}


CButterfly::~CButterfly()
{
}
