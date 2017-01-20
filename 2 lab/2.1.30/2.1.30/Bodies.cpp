#include "stdafx.h"
#include "Bodies.h"
#include <stdint.h>


namespace
{

typedef glm::vec3 Vertex;
const glm::vec3 DARK_GREEN = { 0.05f, 0.45f, 0.1f };
const glm::vec3 LIGHT_GREEN = { 0.1f, 0.8f, 0.15f };
const glm::vec3 BLACK = { 0.f, 0.f, 0.f };
const glm::vec3 RED = { 1.f, 0.f, 0.f };
const glm::vec3 WHITE = { 1.f, 1.f, 1.f };

const glm::vec3 BLUE = { 55.f / 255.f, 191.f / 255.f, 164.f / 255.f };
const glm::vec3 TURQUOISE = { 64.f / 255.f, 201.f / 255.f , 85.f / 255.f };
const glm::vec3 PINK = { 194.f / 255.f, 62.f / 255.f , 134.f / 255.f };
const glm::vec3 YELLOW = { 216.f / 255.f, 227.f / 255.f , 57.f / 255.f };
const glm::vec3 GREEN = { 61.f / 255.f, 145.f / 255.f , 69.f / 255.f };
const glm::vec3 LIGHT_PINK = { 228.f / 255.f, 209.f / 255.f , 230.f / 255.f };


const double PHI = static_cast<double>(1.f + static_cast<double>(std::sqrt(5))) / 2.f;
const double X_COORDINATE = std::cbrt((PHI + std::sqrt(PHI - 5.f / 27.f)) / 2.f) + std::cbrt((PHI - std::sqrt(PHI - 5.f / 27.f)) / 2.f);
const std::vector<double> COEFICIENTS = {
	PHI * std::sqrt(3.f - std::pow(X_COORDINATE, 2.f)) / 2.f,
	PHI * std::sqrt((X_COORDINATE - 1.f - (1.f / X_COORDINATE)) * PHI) / (2.f * X_COORDINATE),
	PHI * std::sqrt((X_COORDINATE - 1.f - (1.f / X_COORDINATE)) * PHI) / 2.f,
	std::pow(X_COORDINATE, 2.f) * PHI * std::sqrt(3 - std::pow(X_COORDINATE, 2.f)) / 2.f,
	PHI * std::sqrt(1.f - X_COORDINATE + (PHI + 1.f) / X_COORDINATE) / 2.f,
	std::sqrt(X_COORDINATE * (X_COORDINATE + PHI) + 1.f) / (2.f * X_COORDINATE),
	std::sqrt((X_COORDINATE + 2.f) * PHI + 2.f) / (2.f * X_COORDINATE),
	std::sqrt(-std::pow(X_COORDINATE, 2.f) * (PHI + 2.f) + X_COORDINATE * (3 * PHI + 1.f) + 4) / 2.f,
	(PHI + 1.f) * std::sqrt(1.f + (1.f / X_COORDINATE)) / (2.f * X_COORDINATE),
	std::sqrt(3 * PHI + 2.f - 2.f * X_COORDINATE + (3 / X_COORDINATE)) / 2.f,
	std::sqrt(std::pow(X_COORDINATE, 2.f)*(225.f * PHI + 392.f) + X_COORDINATE*(670.f * PHI + 249.f) + (157.f * PHI + 470)) / 62.f,
	PHI * std::sqrt(X_COORDINATE * (X_COORDINATE + PHI) + 1.f) / (2.f * X_COORDINATE),
	PHI * std::sqrt(std::pow(X_COORDINATE, 2.f) + X_COORDINATE + PHI + 1.f) / (2.f * X_COORDINATE),
	PHI * std::sqrt(std::pow(X_COORDINATE, 2.f) + 2.f * X_COORDINATE * PHI + 2.f) / (2.f * X_COORDINATE),
	std::sqrt(std::pow(X_COORDINATE, 2.f) * (2.f * PHI + 1.f) - PHI) / 2.f,
	PHI * std::sqrt(std::pow(X_COORDINATE, 2.f) + X_COORDINATE) / 2.f,
	std::pow(PHI, 3) * std::sqrt(X_COORDINATE * (X_COORDINATE + PHI) + 1.f) / (2.f * std::pow(X_COORDINATE, 2.f)),
	std::sqrt(std::pow(X_COORDINATE, 2.f)*(842.f * PHI + 617.f) + X_COORDINATE*(189.f * PHI + 919.f) + (784 * PHI + 627.f)) / 62.f,
	std::pow(PHI, 2.f) * std::sqrt(X_COORDINATE * (X_COORDINATE + PHI) + 1.f) / (2.f * X_COORDINATE),
	PHI * std::sqrt(X_COORDINATE * (X_COORDINATE + PHI) + 1.f) / 2.f
};

// Вершины куба служат материалом для формирования треугольников,
// составляющих грани куба.
const Vertex CUBE_VERTICIES[] = {
	{ COEFICIENTS[0],  COEFICIENTS[1],  COEFICIENTS[19] },
	{ COEFICIENTS[0],  -COEFICIENTS[1], -COEFICIENTS[19] },
	{ -COEFICIENTS[0],  -COEFICIENTS[1],  COEFICIENTS[19] },
	{ -COEFICIENTS[0],  COEFICIENTS[1], -COEFICIENTS[19] },
	{ COEFICIENTS[19],  COEFICIENTS[0],  COEFICIENTS[1] },
	{ COEFICIENTS[19],  -COEFICIENTS[0],  -COEFICIENTS[1] },
	{ -COEFICIENTS[19],  -COEFICIENTS[0],  COEFICIENTS[1] },
	{ -COEFICIENTS[19],  COEFICIENTS[0],  -COEFICIENTS[1] },
	{ COEFICIENTS[1],  COEFICIENTS[19],  COEFICIENTS[0] },
	{ COEFICIENTS[1], -COEFICIENTS[19],  -COEFICIENTS[0] },
	{ -COEFICIENTS[1], -COEFICIENTS[19],  COEFICIENTS[0] },
	{ -COEFICIENTS[1],  COEFICIENTS[19],  -COEFICIENTS[0] },
	{ 0.f,  COEFICIENTS[5],  COEFICIENTS[18] },
	{ 0.f,  COEFICIENTS[5], -COEFICIENTS[18] },
	{ 0.f,  -COEFICIENTS[5],  COEFICIENTS[18] },
	{ 0.f,  -COEFICIENTS[5], -COEFICIENTS[18] },
	{ COEFICIENTS[18],  0.f,  COEFICIENTS[5] },
	{ COEFICIENTS[18],  0.f,  -COEFICIENTS[5] },
	{ -COEFICIENTS[18],  0.f,  COEFICIENTS[5] },
	{ -COEFICIENTS[18],  0.f,  -COEFICIENTS[5] },
	{ COEFICIENTS[5],  COEFICIENTS[18],  0.f },
	{ COEFICIENTS[5], -COEFICIENTS[18],  0.f },
	{ -COEFICIENTS[5],  COEFICIENTS[18],  0.f },
	{ -COEFICIENTS[5], -COEFICIENTS[18],  0.f },
	{ COEFICIENTS[10],  0.f,  COEFICIENTS[17] },
	{ COEFICIENTS[10],  0.f, -COEFICIENTS[17] },
	{ -COEFICIENTS[10],  0.f,  COEFICIENTS[17] },
	{ -COEFICIENTS[10],  0.0f, -COEFICIENTS[17] },
	{ COEFICIENTS[17],  COEFICIENTS[10],  0.f },
	{ COEFICIENTS[17], -COEFICIENTS[10],  0.f },
	{ -COEFICIENTS[17],  COEFICIENTS[10],  0.f },
	{ -COEFICIENTS[17], -COEFICIENTS[10],  0.f },
	{ 0.f,  COEFICIENTS[17],  COEFICIENTS[10] },
	{ 0.f,  COEFICIENTS[17], -COEFICIENTS[10] },
	{ 0.f, -COEFICIENTS[17],  COEFICIENTS[10] },
	{ 0.f, -COEFICIENTS[17], -COEFICIENTS[10] },
	{ COEFICIENTS[3],  -COEFICIENTS[6],  COEFICIENTS[16] },
	{ COEFICIENTS[3],  COEFICIENTS[6], -COEFICIENTS[16] },
	{ -COEFICIENTS[3],  COEFICIENTS[6],  COEFICIENTS[16] },
	{ -COEFICIENTS[3],  -COEFICIENTS[6], -COEFICIENTS[16] },
	{ COEFICIENTS[16],  -COEFICIENTS[3],  COEFICIENTS[6] },
	{ COEFICIENTS[16],  COEFICIENTS[3],  -COEFICIENTS[6] },
	{ -COEFICIENTS[16],  COEFICIENTS[3],  COEFICIENTS[6] },
	{ -COEFICIENTS[16],  -COEFICIENTS[3],  -COEFICIENTS[6] },
	{ COEFICIENTS[6], -COEFICIENTS[16],  COEFICIENTS[3] },
	{ COEFICIENTS[6],  COEFICIENTS[16],  -COEFICIENTS[3] },
	{ -COEFICIENTS[6],  COEFICIENTS[16],  COEFICIENTS[3] },
	{ -COEFICIENTS[6], -COEFICIENTS[16],  -COEFICIENTS[3] },
	{ COEFICIENTS[2],  COEFICIENTS[9],  COEFICIENTS[15] },
	{ COEFICIENTS[2],  -COEFICIENTS[9], -COEFICIENTS[15] },
	{ -COEFICIENTS[2],  -COEFICIENTS[9],  COEFICIENTS[15] },
	{ -COEFICIENTS[2],  COEFICIENTS[9], -COEFICIENTS[15] },
	{ COEFICIENTS[15],  COEFICIENTS[2],  COEFICIENTS[9] },
	{ COEFICIENTS[15],  -COEFICIENTS[2],  -COEFICIENTS[9] },
	{ -COEFICIENTS[15],  -COEFICIENTS[2],  COEFICIENTS[9] },
	{ -COEFICIENTS[15],  COEFICIENTS[2],  -COEFICIENTS[9] },
	{ COEFICIENTS[9],  COEFICIENTS[15],  COEFICIENTS[2] },
	{ COEFICIENTS[9], -COEFICIENTS[15],  -COEFICIENTS[2] },
	{ -COEFICIENTS[9], -COEFICIENTS[15],  COEFICIENTS[2] },
	{ -COEFICIENTS[9],  COEFICIENTS[15],  -COEFICIENTS[2] },
	{ COEFICIENTS[7],  COEFICIENTS[8],  COEFICIENTS[14] },
	{ COEFICIENTS[7],  -COEFICIENTS[8], -COEFICIENTS[14] },
	{ -COEFICIENTS[7],  -COEFICIENTS[8],  COEFICIENTS[14] },
	{ -COEFICIENTS[7],  COEFICIENTS[8], -COEFICIENTS[14] },
	{ COEFICIENTS[14],  COEFICIENTS[7],  COEFICIENTS[8] },
	{ COEFICIENTS[14],  -COEFICIENTS[7],  -COEFICIENTS[8] },
	{ -COEFICIENTS[14],  -COEFICIENTS[7],  COEFICIENTS[8] },
	{ -COEFICIENTS[14],  COEFICIENTS[7],  -COEFICIENTS[8] },
	{ COEFICIENTS[8],  COEFICIENTS[14],  COEFICIENTS[7] },
	{ COEFICIENTS[8], -COEFICIENTS[14],  -COEFICIENTS[7] },
	{ -COEFICIENTS[8], -COEFICIENTS[14],  COEFICIENTS[7] },
	{ -COEFICIENTS[8],  COEFICIENTS[14],  -COEFICIENTS[7] },
	{ COEFICIENTS[4], -COEFICIENTS[12],  COEFICIENTS[13] },
	{ COEFICIENTS[4],  COEFICIENTS[12], -COEFICIENTS[13] },
	{ -COEFICIENTS[4],  COEFICIENTS[12],  COEFICIENTS[13] },
	{ -COEFICIENTS[4], -COEFICIENTS[12], -COEFICIENTS[13] },
	{ COEFICIENTS[13],  -COEFICIENTS[4],  COEFICIENTS[12] },
	{ COEFICIENTS[13],  COEFICIENTS[4], -COEFICIENTS[12] },
	{ -COEFICIENTS[13],  COEFICIENTS[4],  COEFICIENTS[12] },
	{ -COEFICIENTS[13],  -COEFICIENTS[4], -COEFICIENTS[12] },
	{ COEFICIENTS[12], -COEFICIENTS[13],  COEFICIENTS[4] },
	{ COEFICIENTS[12],  COEFICIENTS[13],  -COEFICIENTS[4] },
	{ -COEFICIENTS[12],  COEFICIENTS[13],  COEFICIENTS[4] },
	{ -COEFICIENTS[12], -COEFICIENTS[13],  -COEFICIENTS[4] },
	{ COEFICIENTS[11],  COEFICIENTS[11],  COEFICIENTS[11] },
	{ COEFICIENTS[11],  COEFICIENTS[11], -COEFICIENTS[11] },
	{ COEFICIENTS[11], -COEFICIENTS[11],  COEFICIENTS[11] },
	{ COEFICIENTS[11], -COEFICIENTS[11], -COEFICIENTS[11] },
	{ -COEFICIENTS[11],  COEFICIENTS[11],  COEFICIENTS[11] },
	{ -COEFICIENTS[11],  COEFICIENTS[11], -COEFICIENTS[11] },
	{ -COEFICIENTS[11], -COEFICIENTS[11],  COEFICIENTS[11] },
	{ -COEFICIENTS[11], -COEFICIENTS[11], -COEFICIENTS[11] },
};

struct STriangleFace
{
    uint16_t vertexIndex1;
    uint16_t vertexIndex2;
    uint16_t vertexIndex3;
	glm::vec3 color;
};

// Привыкаем использовать 16-битный unsigned short,
// чтобы экономить память на фигурах с тысячами вершин.
const STriangleFace CUBE_FACES[] = {
	{ 36, 14, 2, BLUE },
	{ 36, 2, 0, BLUE },
	{ 36, 0, 24, BLUE },
	{ 76, 86, 72, TURQUOISE },
	{ 76, 72, 36, TURQUOISE },
	{ 76, 36, 24, TURQUOISE },
	{ 52, 16, 40, PINK },
	{ 52, 40, 76, PINK },
	{ 52, 76, 24, PINK },
	{ 60, 84, 64, GREEN },
	{ 60, 64, 52, GREEN },
	{ 60, 52, 24, GREEN },
	{ 0, 12, 48, RED },
	{ 0, 48, 60, RED },
	{ 0, 60, 24, RED },
	{ 37, 13, 3, YELLOW },
	{ 37, 3, 1, YELLOW },
	{ 37, 1, 25, YELLOW },
	{ 77, 85, 73, LIGHT_PINK },
	{ 77, 73, 37, LIGHT_PINK },
	{ 77, 37, 25, LIGHT_PINK },
	{ 53, 17, 41, LIGHT_GREEN },
	{ 53, 41, 77, LIGHT_GREEN },
	{ 53, 77, 25, LIGHT_GREEN },
	{ 61, 87, 65, BLUE },
	{ 61, 65, 53, BLUE },
	{ 61, 53, 25, BLUE },
	{ 1, 15, 49, TURQUOISE },
	{ 1, 49, 61, TURQUOISE },
	{ 1, 61, 25, TURQUOISE },
	{ 38, 12, 0, PINK },
	{ 38, 0, 2, PINK },
	{ 38, 2, 26, PINK },
	{ 78, 88, 74, GREEN },
	{ 78, 74, 38, GREEN },
	{ 78, 38, 26, GREEN },
	{ 54, 18, 42, RED },
	{ 54, 42, 78, RED },
	{ 54, 78, 26, RED },
	{ 62, 90, 66, YELLOW },
	{ 62, 66, 54, YELLOW },
	{ 62, 54, 26, YELLOW },
	{ 2, 14, 50, LIGHT_PINK },
	{ 2, 50, 62, LIGHT_PINK },
	{ 2, 62, 26, LIGHT_PINK },
	{ 39, 15, 1, LIGHT_GREEN },
	{ 39, 1, 3, LIGHT_GREEN },
	{ 39, 3, 27, LIGHT_GREEN },
	{ 79, 91, 75, BLUE },
	{ 79, 75, 39, BLUE },
	{ 79, 39, 27, BLUE },
	{ 55, 19, 43, TURQUOISE },
	{ 55, 43, 79, TURQUOISE },
	{ 55, 79, 27, TURQUOISE },
	{ 63, 89, 67, PINK },
	{ 63, 67, 55, PINK },
	{ 63, 55, 27, PINK },
	{ 3, 13, 51, GREEN },
	{ 3, 51, 63, GREEN },
	{ 3, 63, 27, GREEN },
	{ 41, 17, 5, RED },
	{ 41, 5, 4, RED },
	{ 41, 4, 28, RED },
	{ 81, 85, 77, YELLOW },
	{ 81, 77, 41, YELLOW },
	{ 81, 41, 28, YELLOW },
	{ 56, 20, 45, LIGHT_PINK },
	{ 56, 45, 81, LIGHT_PINK },
	{ 56, 81, 28, LIGHT_PINK },
	{ 64, 84, 68, LIGHT_GREEN },
	{ 64, 68, 56, LIGHT_GREEN },
	{ 64, 56, 28, LIGHT_GREEN },
	{ 4, 16, 52, BLUE },
	{ 4, 52, 64, BLUE },
	{ 4, 64, 28, BLUE },
	{ 40, 16, 4, TURQUOISE },
	{ 40, 4, 5, TURQUOISE },
	{ 40, 5, 29, TURQUOISE },
	{ 80, 86, 76, PINK },
	{ 80, 76, 40, PINK },
	{ 80, 40, 29, PINK },
	{ 57, 21, 44, GREEN },
	{ 57, 44, 80, GREEN },
	{ 57, 80, 29, GREEN },
	{ 65, 87, 69, RED },
	{ 65, 69, 57, RED },
	{ 65, 57, 29, RED },
	{ 5, 17, 53, YELLOW },
	{ 5, 53, 65, YELLOW },
	{ 5, 65, 29, YELLOW },
	{ 42, 18, 6, LIGHT_PINK },
	{ 42, 6, 7, LIGHT_PINK },
	{ 42, 7, 30, LIGHT_PINK },
	{ 82, 88, 78, LIGHT_GREEN },
	{ 82, 78, 42, LIGHT_GREEN },
	{ 82, 42, 30, LIGHT_GREEN },
	{ 59, 22, 46, BLUE },
	{ 59, 46, 82, BLUE },
	{ 59, 82, 30, BLUE },
	{ 67, 89, 71, TURQUOISE },
	{ 67, 71, 59, TURQUOISE },
	{ 67, 59, 30, TURQUOISE },
	{ 7, 19, 55, PINK },
	{ 7, 55, 67, PINK },
	{ 7, 67, 30, PINK },
	{ 43, 19, 7, GREEN },
	{ 43, 7, 6, GREEN },
	{ 43, 6, 31, GREEN },
	{ 83, 91, 79, RED },
	{ 83, 79, 43, RED },
	{ 83, 43, 31, RED },
	{ 58, 23, 47, YELLOW },
	{ 58, 47, 83, YELLOW },
	{ 58, 83, 31, YELLOW },
	{ 66, 90, 70, LIGHT_PINK },
	{ 66, 70, 58, LIGHT_PINK },
	{ 66, 58, 31, LIGHT_PINK },
	{ 6, 18, 54, LIGHT_GREEN },
	{ 6, 54, 66, LIGHT_GREEN },
	{ 6, 66, 31, LIGHT_GREEN },
	{ 46, 22, 11, BLUE },
	{ 46, 11, 8, BLUE },
	{ 46, 8, 32, BLUE },
	{ 74, 88, 82, TURQUOISE },
	{ 74, 82, 46, TURQUOISE },
	{ 74, 46, 32, TURQUOISE },
	{ 48, 12, 38, PINK },
	{ 48, 38, 74, PINK },
	{ 48, 74, 32, PINK },
	{ 68, 84, 60, GREEN },
	{ 68, 60, 48, GREEN },
	{ 68, 48, 32, GREEN },
	{ 8, 20, 56, RED },
	{ 8, 56, 68, RED },
	{ 8, 68, 32, RED },
	{ 45, 20, 8, YELLOW },
	{ 45, 8, 11, YELLOW },
	{ 45, 11, 33, YELLOW },
	{ 73, 85, 81, LIGHT_PINK },
	{ 73, 81, 45, LIGHT_PINK },
	{ 73, 45, 33, LIGHT_PINK },
	{ 51, 13, 37, LIGHT_GREEN },
	{ 51, 37, 73, LIGHT_GREEN },
	{ 51, 73, 33, LIGHT_GREEN },
	{ 71, 89, 63, BLUE },
	{ 71, 63, 51, BLUE },
	{ 71, 51, 33, BLUE },
	{ 11, 22, 59, TURQUOISE },
	{ 11, 59, 71, TURQUOISE },
	{ 11, 71, 33, TURQUOISE },
	{ 44, 21, 9, PINK },
	{ 44, 9, 10, PINK },
	{ 44, 10, 34, PINK },
	{ 72, 86, 80, GREEN },
	{ 72, 80, 44, GREEN },
	{ 72, 44, 34, GREEN },
	{ 50, 14, 36, RED },
	{ 50, 36, 72, RED },
	{ 50, 72, 34, RED },
	{ 70, 90, 62, YELLOW },
	{ 70, 62, 50, YELLOW },
	{ 70, 50, 34, YELLOW },
	{ 10, 23, 58, LIGHT_PINK },
	{ 10, 58, 70, LIGHT_PINK },
	{ 10, 70, 34, LIGHT_PINK },
	{ 47, 23, 10, LIGHT_GREEN },
	{ 47, 10, 9, LIGHT_GREEN },
	{ 47, 9, 35, LIGHT_GREEN },
	{ 75, 91, 83, BLUE },
	{ 75, 83, 47, BLUE },
	{ 75, 47, 35, BLUE },
	{ 49, 15, 39, TURQUOISE },
	{ 49, 39, 75, TURQUOISE },
	{ 49, 75, 35, TURQUOISE },
	{ 69, 87, 61, PINK },
	{ 69, 61, 49, PINK },
	{ 69, 49, 35, PINK },
	{ 9, 21, 57, GREEN },
	{ 9, 57, 69, GREEN },
	{ 9, 69, 35, GREEN },


};

/// @param phase - Фаза анимации на отрезке [0..1]
glm::mat4 GetRotateZTransfrom(float phase)
{
    // угол вращения вокруг оси Z лежит в отрезке [0...2*pi].
    const float angle = float(2 * M_PI) * phase;

    return glm::rotate(glm::mat4(), angle, {0, 0, 1});
}

/// @param phase - Фаза анимации на отрезке [0..1]
glm::mat4 GetScalingPulseTransform(float phase)
{
    // число пульсаций размера - произвольная константа.
    const int pulseCount = 4;
    float scale = fabsf(cosf(float(pulseCount * M_PI) * phase));

    return glm::scale(glm::mat4(), {scale, scale, scale});
}

/// @param phase - Фаза анимации на отрезке [0..1]
glm::mat4 GetBounceTransform(float phase)
{
    // начальная скорость и число отскоков - произвольные константы.
    const int bounceCount = 4;
    const float startSpeed = 15.f;
    // "время" пробегает bounceCount раз по отрезку [0...1/bounceCount].
    const float time = fmodf(phase, 1.f / float(bounceCount));
    // ускорение подбирается так, чтобы на 0.25с скорость стала
    // противоположна начальной.
    const float acceleration = - (startSpeed * 2.f * float(bounceCount));
    // расстояние - результат интегрирования функции скорости:
    //  speed = startSpeed + acceleration * time;
    float offset = time * (startSpeed + 0.5f * acceleration * time);

    // для отскоков с нечётным номером меняем знак.
    const int bounceNo = int(phase * bounceCount);
    if (bounceNo % 2)
    {
        offset = -offset;
    }

    return glm::translate(glm::mat4(), {offset, 0.f, 0.f});
}

}

CIdentityCube::CIdentityCube()
{
}

void CIdentityCube::Update(float deltaTime)
{
    (void)deltaTime;
}

void CIdentityCube::Draw() const
{
	glFrontFace(GL_CW);
	SetVertexes();
	glFrontFace(GL_CCW);
	SetVertexes();
	
}


void CIdentityCube::SetVertexes() const
{
	glBegin(GL_TRIANGLES);
	for (const STriangleFace &face : CUBE_FACES)
	{
		const Vertex &v1 = CUBE_VERTICIES[face.vertexIndex1];
		const Vertex &v2 = CUBE_VERTICIES[face.vertexIndex2];
		const Vertex &v3 = CUBE_VERTICIES[face.vertexIndex3];
		glm::vec3 normal = glm::normalize(glm::cross(v2 - v1, v3 - v1));

		glColor4f(face.color.x, face.color.y, face.color.z, 0.9f);
		glNormal3fv(glm::value_ptr(normal));
		glVertex3fv(glm::value_ptr(v1));
		glVertex3fv(glm::value_ptr(v2));
		glVertex3fv(glm::value_ptr(v3));
	}
	glEnd();

	uint16_t triangleCount = 0;
	for (const STriangleFace &face : CUBE_FACES)
	{
		if (triangleCount == 0)
		{
			glColor4f(BLACK.x, BLACK.y, BLACK.z, 0.9f);
			glLineWidth(2);
			glBegin(GL_LINE_LOOP);
			const Vertex &v1 = CUBE_VERTICIES[face.vertexIndex1];
			const Vertex &v2 = CUBE_VERTICIES[face.vertexIndex2];
			const Vertex &v3 = CUBE_VERTICIES[face.vertexIndex3];
			glVertex3fv(glm::value_ptr(v1));
			glVertex3fv(glm::value_ptr(v2));
			glVertex3fv(glm::value_ptr(v3));
		}
		else if (triangleCount == 2)
		{
			const Vertex &v2 = CUBE_VERTICIES[face.vertexIndex2];
			const Vertex &v3 = CUBE_VERTICIES[face.vertexIndex3];
			glVertex3fv(glm::value_ptr(v2));
			glVertex3fv(glm::value_ptr(v3));
			glEnd();
		}
		triangleCount = (triangleCount == 2 ? 0 : ++triangleCount);
	}

}

const float CAnimatedCube::ANIMATION_STEP_SECONDS = 2.f;

void CAnimatedCube::Update(float deltaTime)
{
    // Вычисляем фазу анимации по времени на отрезке [0..1].
    m_animationPhase += (deltaTime / ANIMATION_STEP_SECONDS);
    if (m_animationPhase >= 1)
    {
        m_animationPhase = 0;
        switch (m_animation)
        {
        case Rotating:
            m_animation = Pulse;
            break;
        case Pulse:
            m_animation = Bounce;
            break;
        case Bounce:
            m_animation = Rotating;
            break;
        }
    }
}

void CAnimatedCube::Draw() const
{
    const glm::mat4 matrix = GetAnimationTransform();
    glPushMatrix();
    glMultMatrixf(glm::value_ptr(matrix));
    CIdentityCube::Draw();
    glPopMatrix();
}

// Документация по функциям для модификации матриц:
// http://glm.g-truc.net/0.9.2/api/a00245.html
glm::mat4 CAnimatedCube::GetAnimationTransform() const
{
    switch (m_animation)
    {
    case Rotating:
        return GetRotateZTransfrom(m_animationPhase);
    case Pulse:
        return GetScalingPulseTransform(m_animationPhase);
    case Bounce:
        return GetBounceTransform(m_animationPhase);
    }
    // Недостижимый код - вернём единичную матрицу.
    return glm::mat4();
}
