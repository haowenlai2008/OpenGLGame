#pragma once
#include "glm/glm.hpp"
#include <vector>
#include <tuple>


constexpr float PI = 3.14159265358979323846;
class SphericalHarmonics
{
public:
	SphericalHarmonics(int degree);
	void Evaluate(const std::vector<std::tuple<glm::vec3, glm::vec3>>& posColor);
	std::vector<glm::vec3> getCoefficients()
	{
		return coefs;
	}
private:
	int _degree;
	std::vector<glm::vec3> coefs;
	std::vector<float> Basis(const glm::vec3& pos);
};

