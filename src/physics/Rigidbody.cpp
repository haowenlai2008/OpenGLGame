#include "Rigidbody.h"

Rigidbody::Rigidbody() : m_mass(10.0f), m_frict(0.5f)
{
}

Rigidbody::Rigidbody(float mass, float frict) : m_mass(mass), m_frict(frict)
{
}
