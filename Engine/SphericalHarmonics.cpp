#include "SphericalHarmonics.h"
#include <cmath>

SphericalHarmonics::SphericalHarmonics(int degree) : _degree(degree)
{
}

void SphericalHarmonics::Evaluate(const std::vector<std::tuple<glm::vec3, glm::vec3>>& posColor)
{
	int n = (_degree + 1) * (_degree + 1);
	coefs = std::vector<glm::vec3>(n, glm::vec3());
	for (auto& pc : posColor)
	{
		glm::vec3 pos = std::get<0>(pc);
		glm::vec3 color = std::get<1>(pc);
		std::vector<float> Y = Basis(pos);
		for (int i = 0; i < n; i++)
		{
			coefs[i] = coefs[i] + Y[i] * color;
		}
	}
	for (auto& coef : coefs)
	{
		coef = 4 * PI * coef / (float)posColor.size();
	}
}

std::vector<float> SphericalHarmonics::Basis(const glm::vec3& pos)
{
	int n = (_degree + 1) * (_degree + 1);
	std::vector<float> Y(n);
	glm::vec3 normal = glm::normalize(pos);
	float x = normal.x;
	float y = normal.y;
	float z = normal.z;
	// break « ≤√¥£ø
	switch (_degree)
	{
	case 0:
		Y[0] = 1.f / 2.f * sqrt(1.f / PI);
	case 1:
		Y[1] = sqrt(3.f / (4.f * PI)) * z;
		Y[2] = sqrt(3.f / (4.f * PI)) * y;
		Y[3] = sqrt(3.f / (4.f * PI)) * x;
	case 2:
		Y[4] = 1.f / 2.f * sqrt(15.f / PI) * x * z;
		Y[5] = 1.f / 2.f * sqrt(15.f / PI) * z * y;
		Y[6] = 1.f / 4.f * sqrt(5.f / PI) * (-x * x - z * z + 2 * y * y);
		Y[7] = 1.f / 2.f * sqrt(15.f / PI) * y * x;
		Y[8] = 1.f / 4.f * sqrt(15.f / PI) * (x * x - z * z);
	case 3:
		Y[9] = 1.f / 4.f * sqrt(35.f / (2.f * PI)) * (3 * x * x - z * z) * z;
		Y[10] = 1.f / 2.f * sqrt(105.f / PI) * x * z * y;
		Y[11] = 1.f / 4.f * sqrt(21.f / (2.f * PI)) * z * (4 * y * y - x * x - z * z);
		Y[12] = 1.f / 4.f * sqrt(7.f / PI) * y * (2 * y * y - 3 * x * x - 3 * z * z);
		Y[13] = 1.f / 4.f * sqrt(21.f / (2.f * PI)) * x * (4 * y * y - x * x - z * z);
		Y[14] = 1.f / 4.f * sqrt(105.f / PI) * (x * x - z * z) * y;
		Y[15] = 1.f / 4.f * sqrt(35.f / (2 * PI)) * (x * x - 3 * z * z) * x;
	default:
	}
	return Y;
}
