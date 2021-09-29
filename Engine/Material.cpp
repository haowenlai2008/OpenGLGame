#include "Material.h"

Material::Material() : m_specular(0.5f, 0.5f, 0.5f), m_shininess(64.0f)
{
}

Material::Material(const vec3& specular, float shininess) : m_specular(specular), m_shininess(shininess)
{
}

Material::Material(vec3&& specular, float shininess) : m_specular(specular), m_shininess(shininess)
{
}
