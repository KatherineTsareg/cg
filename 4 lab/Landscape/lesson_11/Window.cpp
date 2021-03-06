#include "stdafx.h"
#include "Window.h"
#include "IdentitySphere.h"
#include <boost/range/algorithm/find_if.hpp>
#include <boost/range/adaptor/reversed.hpp>
#include <glm/gtc/matrix_transform.hpp>


using glm::mat4;
using glm::vec3;
using glm::vec4;

namespace
{
const char SKY_TEX_PATH[] = "res/sky.bmp";

const glm::vec4 BLACK = {0, 0, 0, 1};
const glm::vec4 WHITE = { 0.8f, 0.8f, 0.8f, 0 };
const float MATERIAL_SHININESS = 30.f;
const glm::vec4 FADED_WHITE_RGBA = {0.3f, 0.3f, 0.3f, 1.f};
const glm::vec4 LIGHT_YELLOW_RGBA = { 1.f, 1.f, 0.5f, 1.f };
const glm::vec3 SUNLIGHT_DIRECTION = {-1.f, 0.2f, 0.7f};
const unsigned SPHERE_PRECISION = 100;
const float SPHERE_RADIUS = VERTEX_TILE_SIZE * STEP / 1.8f;
const float CAMERA_INITIAL_ROTATION = 0;
const float CAMERA_INITIAL_DISTANCE = 900.f;


void SetupOpenGLState()
{
    // включаем механизмы трёхмерного мира.
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CCW);
    glCullFace(GL_BACK);

    // включаем систему освещения
    glEnable(GL_LIGHTING);

    // включаем текстурирование в старом стиле (OpenGL 1.1)
    glEnable(GL_TEXTURE_2D);
}

glm::mat4 MakeProjectionMatrix(const glm::ivec2 &size)
{
	// Матрица перспективного преобразования вычисляется функцией
	// glm::perspective, принимающей угол обзора, соотношение ширины
	// и высоты окна, расстояния до ближней и дальней плоскостей отсечения.
	const float fieldOfView = glm::radians(70.f);
	const float aspect = float(size.x) / float(size.y);
	const float zNear = 0.01f;
	const float zFar = 100.f;

	return glm::perspective(fieldOfView, aspect, zNear, zFar);
}

}


CWindow::CWindow()
    : m_camera(CAMERA_INITIAL_ROTATION, CAMERA_INITIAL_DISTANCE)
    , m_sunlight(GL_LIGHT0)
{
    SetBackgroundColor(WHITE);

    const glm::vec4 WHITE_RGBA = {1, 1, 1, 1};
    m_material.SetAmbient(WHITE_RGBA);
    m_material.SetDiffuse(WHITE_RGBA);
    m_material.SetSpecular(FADED_WHITE_RGBA);
    m_material.SetShininess(MATERIAL_SHININESS);

    m_sunlight.SetDirection(SUNLIGHT_DIRECTION);
    m_sunlight.SetDiffuse(WHITE_RGBA);
    m_sunlight.SetAmbient(0.1f * WHITE_RGBA);
    m_sunlight.SetSpecular(WHITE_RGBA);
}

void CWindow::OnWindowInit(const glm::ivec2 &size)
{
    (void)size;
    SetupOpenGLState();

	m_pSphere = std::make_unique<CIdentitySphere>(SPHERE_PRECISION, SPHERE_PRECISION, SPHERE_RADIUS);
	m_pLandscape = std::make_unique<CLandscape>();

    CTexture2DLoader loader;
    loader.SetWrapMode(TextureWrapMode::REPEAT);
	m_pSkyTexture = loader.Load(SKY_TEX_PATH);
}

void CWindow::OnUpdateWindow(float deltaSeconds)
{
    m_camera.Update(deltaSeconds);
}

void CWindow::OnDrawWindow(const glm::ivec2 &size)
{
    SetupView(size);
	SetupFog();
    m_sunlight.Setup();
    m_material.Setup();
	m_pLandscape->Draw();

	m_pSkyTexture->DoWhileBinded([&] {
		m_pSphere->Draw();
	});
}

void CWindow::SetupView(const glm::ivec2 &size)
{
    glViewport(0, 0, size.x, size.y);

    // Матрица вида возвращается камерой и составляет
    // начальное значение матрицы GL_MODELVIEW.
    glLoadMatrixf(glm::value_ptr(m_camera.GetViewTransform()));

    // Матрица перспективного преобразования вычисляется функцией
    // glm::perspective, принимающей угол обзора, соотношение ширины
    // и высоты окна, расстояния до ближней и дальней плоскостей отсечения.
    const float fieldOfView = glm::radians(70.f);
    const float aspect = float(size.x) / float(size.y);
    const float zNear = 0.01f;
    const float zFar = 40000.f;
    const glm::mat4 proj = glm::perspective(fieldOfView, aspect, zNear, zFar);
    glMatrixMode(GL_PROJECTION);
    glLoadMatrixf(glm::value_ptr(proj));
    glMatrixMode(GL_MODELVIEW);
}

void CWindow::OnKeyDown(const SDL_KeyboardEvent &event)
{
    m_camera.OnKeyDown(event);

	if (event.keysym.sym == SDLK_f)
	{
		m_isFogEnabled = !m_isFogEnabled;
	}
}

void CWindow::OnKeyUp(const SDL_KeyboardEvent &event)
{
    m_camera.OnKeyUp(event);
}

void CWindow::SetupFog()
{
	if (m_isFogEnabled)
	{
		const float density = 0.002f;
		glEnable(GL_FOG);
		glFogi(GL_FOG_MODE, GL_EXP2);
		glFogfv(GL_FOG_COLOR, glm::value_ptr(WHITE));
		glFogf(GL_FOG_DENSITY, density);
	}
	else
	{
		glDisable(GL_FOG);
	}
}