#include "SphereCollider.h"

SphereCollider::SphereCollider() : m_radius(0.5f)
{
}

SphereCollider::SphereCollider(float radius) : m_radius(radius)
{
}

SphereCollider SphereCollider::Normal()
{
	return SphereCollider(1.0f);
}
