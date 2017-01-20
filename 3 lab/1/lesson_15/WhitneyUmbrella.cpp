#include "stdafx.h"
#include "WhitneyUmbrella.h"
#include <algorithm>

namespace
{
const unsigned MIN_PRECISION = 4;
const float UV_DELTA = 0.05f;

void CalculateTriangleStripIndicies(std::vector<uint32_t> &indicies,
                                    unsigned count)
{
    indicies.clear();
    indicies.reserve(count);
    // вычисляем индексы вершин.
    for (unsigned ci = 0; ci < count; ++ci)
    {
		indicies.push_back(ci);
    }
}

/// Привязывает вершины к состоянию OpenGL,
/// затем вызывает 'callback'.
template <class T>
void DoWithBindedArrays(const std::vector<SVertexP3N> &vertices, T && callback)
{
    // Включаем режим vertex array и normal array.
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);

    // Выполняем привязку vertex array и normal array
    const size_t stride = sizeof(SVertexP3N);
    glNormalPointer(GL_FLOAT, stride, glm::value_ptr(vertices[0].normal));
    glVertexPointer(3, GL_FLOAT, stride, glm::value_ptr(vertices[0].position));

    // Выполняем внешнюю функцию.
    callback();

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
}

glm::vec3 GetSurfacePoint(float x)
{
    return { x, 0.f, 0.f };
}
}

CWhitneyUmbrella::CWhitneyUmbrella(unsigned count)
{
	glLineWidth(2);
    Tesselate(count);
}

void CWhitneyUmbrella::Draw() const
{
    DoWithBindedArrays(m_vertices, [this] {
        glDrawElements(GL_TRIANGLE_STRIP, GLsizei(m_indicies.size()),
                       GL_UNSIGNED_INT, m_indicies.data());
    });
}

void CWhitneyUmbrella::Tesselate(unsigned count)
{
    m_vertices.reserve(count);

	glm::vec3 normal = { 0.f, 0.f, 1.f };
    // вычисляем позиции вершин.
    for (float i = -10; i <= 10; i += 0.02f)
    {
           SVertexP3N vertex;
           vertex.position = GetSurfacePoint(i);

		   vertex.normal = normal;
           m_vertices.push_back(vertex);
    }
    CalculateTriangleStripIndicies(m_indicies, count);
}
