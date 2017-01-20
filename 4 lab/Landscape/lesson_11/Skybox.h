#pragma once

#include "IdentityCube.h"
#include "IdentitySphere.h"
#include "libchapter2.h"
#include <boost/noncopyable.hpp>

class CSkybox final : public ISceneObject
{
public:
    CSkybox();
    void Update(float dt) final;
    void Draw()const final;

private:
    CIdentityCube m_cube;
	//CIdentitySphere m_sphere;

    CTexture2DAtlas m_atlas;
};
