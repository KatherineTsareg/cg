#pragma once
#include "DispatchEvent.h"
#include "MovableFlower.h"
#include <vector>
#include "Meadow.h"

class CWindow : public CAbstractInputControlWindow
{
public:
    CWindow();

protected:
    // CAbstractWindow interface
    void OnUpdateWindow(float deltaSeconds) override;
    void OnDrawWindow(const glm::ivec2 &size) override;

private:
    void SetupView(const glm::ivec2 &size);

	CMeadow m_meadow;
};
