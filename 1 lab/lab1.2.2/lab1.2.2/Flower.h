#pragma once

#include <glm/vec3.hpp>
#include <boost/noncopyable.hpp>

class CFlower : private boost::noncopyable
{
public:
    CFlower(float minRadius, float maxRadius, int petalCount);
    virtual ~CFlower();

    void SetCenterColor(const glm::vec3 &centerColor);
    void SetPetalColor(const glm::vec3 &petalColor);
	void SetPosition(const glm::fvec2 & position);

    virtual void Draw()const;
    virtual bool HitTest(const glm::vec2 &point)const;

private:
    void DeleteList();
    void Redraw()const;
    float GetRadiusByAngle(float angle) const;

    mutable unsigned m_displayList = 0;
    float m_minRadius = 0;
    float m_maxRadius = 0;
    int m_petalCount = 0;
    glm::vec3 m_centerColor;
    glm::vec3 m_petalColor;
	glm::fvec2 m_position;
};
