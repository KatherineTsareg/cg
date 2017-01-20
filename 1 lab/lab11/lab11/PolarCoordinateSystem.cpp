#include "PolarCoordinateSystem.h"
#include <GL/glew.h>
#include <GL/gl.h>
#include <glm/vec2.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>

using namespace std;

CPolarCoordinateSystem::CPolarCoordinateSystem(const glm::ivec2 & windowSize)
	:m_begin({ windowSize.x / 2 , windowSize.y / 2 })
	,m_scale({ 2 * windowSize.x / 5 , 2 * windowSize.y / 5 }) //в совокупности график будет занимать 4/5 части экрана
{
	for (int i = 0; i <= m_line_count; i++)
	{
		// TODO: use local variable "angle"
		// TODO: simplify expressions
		float angle = (float(M_PI) / 6) * i;
		m_axes.push_back({ m_begin.x + cos(angle) * m_scale.x,
		                   m_begin.y + sin(angle) * m_scale.y });
		angle += float(M_PI);
		m_axes.push_back({ m_begin.x + cos(angle) * m_scale.x,
			               m_begin.y + sin(angle) * m_scale.y });
	}
}

void CPolarCoordinateSystem::DisplayGraphOfFunction()
{
	DrawAdditionalAxes();
	StrokeAxes();

	glColor3f(1, 0, 0);
	glLineWidth(2);
	glBegin(GL_LINE_STRIP);
	float k = 7.1f;
	for (float angle = 0; angle <= float(10 * M_PI); angle += (float(M_PI / 360.0f)))
	{
		const float dx = k * angle * cosf(angle);
		const float dy = -angle * sinf(angle) * k;
		glVertex2f(dx + m_begin.x, dy + m_begin.y);
	}
	glEnd();
}


void CPolarCoordinateSystem::StrokeAxes()
{
	// дополнительные оси (серые)
	glColor3f(0.5f, 0.5f, 0.5f);
	glBegin(GL_LINES);
	for (size_t i = 0; i < m_axes.size(); i++)
	{
		if ((i != 6) || (i != 7))
		{
			glVertex2f(m_axes[i].x, m_axes[i].y);
		}
	}
	glEnd();

	// главные оси (черные)
	glColor3f(0, 0, 0);
	glBegin(GL_LINES);
	// TODO: replace 8 with size or constant, use size_t for i
	for (size_t i = 0; i < m_axes.size(); i++)
	{
		if ((i < 2) || (i == 6) || (i == 7))
		{
			glVertex2f(m_axes[i].x, m_axes[i].y);
		}
	}
	glEnd();

	// стрелочки у осей
	glColor3f(0, 0, 0);
	glBegin(GL_TRIANGLES);
	glVertex2f(m_axes[0].x, m_axes[0].y);
	glVertex2f(m_axes[0].x - 20, m_axes[0].y - 5);
	glVertex2f(m_axes[0].x - 20, m_axes[0].y + 5);

	glVertex2f(m_axes[7].x, m_axes[7].y);
	glVertex2f(m_axes[7].x - 5, m_axes[7].y + 20);
	glVertex2f(m_axes[7].x + 5, m_axes[7].y + 20);
	glEnd();
}

// Рисует дополнительные оси (шкала) круговые
void CPolarCoordinateSystem::DrawAdditionalAxes()
{
	int pointCount = 360;
	const float step = float(2 * M_PI / pointCount);

	glColor3f(0.5f, 0.5f, 0.5f);
	glLineWidth(1);
	for (int i = m_circleStep; (i < m_scale.x) && (i < m_scale.y); i += m_circleStep)
	{
		glBegin(GL_LINE_LOOP);
		for (float angle = 0; angle < float(2 * M_PI); angle += step)
		{
			const float dx = i * cosf(angle);
			const float dy = i * sinf(angle);
			glVertex2f(dx + m_begin.x, dy + m_begin.y);
		}
		glEnd();
	}
}

CPolarCoordinateSystem::~CPolarCoordinateSystem()
{
}
