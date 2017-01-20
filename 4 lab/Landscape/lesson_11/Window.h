#pragma once
#include "libchapter2.h"
#include "Lights.h"
#include "Skybox.h"
#include "Decorators.h"
#include "Landscape.h"
#include "IdentitySphere.h"
#include <vector>

class CWindow : public CAbstractInputControlWindow
{
public:
    CWindow();

protected:
    // CAbstractWindow interface
    void OnWindowInit(const glm::ivec2 &size) override;
    void OnUpdateWindow(float deltaSeconds) override;
    void OnDrawWindow(const glm::ivec2 &size) override;

    // IInputEventAcceptor interface
    void OnKeyDown(const SDL_KeyboardEvent &) override;
    void OnKeyUp(const SDL_KeyboardEvent &) override;

private:
    void SetupView(const glm::ivec2 &size);

    CPhongModelMaterial m_material;
	CTexture2DUniquePtr m_pSkyTexture;
    CCamera m_camera;
    CDirectedLightSource m_sunlight;

	std::unique_ptr<CLandscape> m_pLandscape;
	std::unique_ptr<CIdentitySphere> m_pSphere;
};
