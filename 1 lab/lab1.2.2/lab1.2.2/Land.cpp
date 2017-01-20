#include "Land.h"
#include <GL/glew.h>
#include <GL/gl.h>
#include <glm/vec2.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace glm;
using namespace std;


void DrawSimpleGrass(fvec2 const& beginPos, float size)
{
	glColor3f(3.f/255.f, 36.f / 255.f, 0.f);
	glLineWidth(2.f);
	glBegin(GL_LINE_STRIP);
	float end = beginPos.x;
	float new_end;

	for (size_t count = 3; count > 0; count--)
	{
		for (float i = float(M_PI) / 1.f; i >= float(M_PI) / 2.f; i -= float(M_PI) / 90.f)
		{
			float dx = end + count * cos(i - float(M_PI) / 2.f) * size / 2;
			float dy = beginPos.y - count * sin(1.f * i) * size;
			glVertex2f(dx, dy);
			new_end = dx;
			
		} 
		end = new_end;
		for (float i = float(2.f * M_PI) / 3.f; i > float(M_PI) / 2.f; i -= float(M_PI) / 90.f)
		{
			float dx = end - count * cos(i - float(M_PI) / 6.f) * size / 2;
			float dy = beginPos.y - count * sin(3.f * i + float(M_PI) / 2.f) * size;
			glVertex2f(dx, dy);
		}
		end = new_end;

	}
	glEnd();
}

CLand::CLand(glm::ivec2 const& windowSize)
	:m_landRect({ 0, float(windowSize.y * 2.f / 5.f), (float)windowSize.x, (float)windowSize.y - (float)windowSize.y * 2.f / 5.f })
	,m_windowSize(windowSize)
{
	fvec2 coefficient = { 200.f, 200.f / 3.f };
	float x = m_windowSize.x * 2.f / 3.f;
	float y = m_landRect.y + (m_windowSize.y - m_landRect.y) / 3.f;
	m_lakeCoordinates = { x - coefficient.x, y - coefficient.y, coefficient.x * 2.f, coefficient.y * 2.f };

}

void CLand::Draw()
{
	DrawMainField();
	DrawALake();
}

bool CLand::IsInRect(const fvec4 & rect, const fvec2 & coord)
{
	if ((coord.x >= rect.x) && (coord.x <= rect.x + rect.z))
	{
		if ((coord.y >= rect.y) && (coord.y <= rect.y + rect.w))
		{
			return true;
		}
	}
	return false;
}

glm::fvec4 CLand::GetLakeRect()
{
	return m_lakeCoordinates;
}

CLand::~CLand()
{
}

void CLand::DrawMainField()
{
	//рисуем темно-зеленый холм справа
	glColor3f(16 / 255.f, 43 / 255.f, 4 / 255.f);
	glBegin(GL_POLYGON);
	for (size_t i = 0; i < m_windowSize.x * 0.4f; i++)
	{
		glVertex2d(i, (int)m_landRect.y - (sin(i / 120.f) * 110.f - 10.f));
	}
	glEnd();
	
	//рисуем основное поле светло-зеленое
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(14.f / 255.f, 48.f / 255.f, 0.f / 255.f);//темно-зеленый 
	
	glVertex2d(m_windowSize.x / 2.f, m_windowSize.y);
	glVertex2d(1, m_windowSize.y);
	for (size_t i = 1; i <= m_windowSize.x; i++)
	{
		glColor3f(9 / 255.f, 135 / 255.f, 14 / 255.f);//светло-зеленый
		glVertex2d(i, (int)m_landRect.y + cos(i / 70.0f) * 10);
	}
	glVertex2d(m_windowSize.x, m_windowSize.y);
	glEnd();
}


void CLand::DrawALake()
{
	fvec2 coefficient = {200.f, 200.f /3.f};
	float x = m_windowSize.x * 2.f / 3.f;
	float y = m_landRect.y + (m_windowSize.y - m_landRect.y) / 3.f;
	
	//рисуем "заднюю" часть - земля
	glColor3f(59 / 255.f, 38 / 255.f, 11 / 255.f);//коричневый цвет земли
	glBegin(GL_TRIANGLE_FAN);
	glVertex2d(x, y);
	for (float i = 0; i < (float)M_PI; i += (float)M_PI/180.f)
	{
		glVertex2d(x + cos(i) * coefficient.x, y - sin(i) * coefficient.y);
	}
	glEnd();

	//рисуем озеро
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(18 / 255.f, 46 / 255.f, 107 / 255.f);//синий цвет
	glVertex2d(x, y);
	for (size_t i = 1; i <= 360; i++)
	{
		glColor3f(7 / 255.f, 32 / 255.f, 87 / 255.f); //темно-синий цвет
		glVertex2d(x + cos(i) * coefficient.x, y + sin(i) * coefficient.y * 8.f / 9.f);
	}
	glEnd();
}

