#include "BoxCollider.h"

BoxCollider::BoxCollider():
	m_length(1.0f),
	m_width(1.0f),
	m_height(1.0f)
{
}

BoxCollider::BoxCollider(float length, float width, float height): 
	m_length(length),
	m_width(width),
	m_height(height)
{
}

BoxCollider BoxCollider::Normal()
{
	return BoxCollider(0.5f, 0.5f, 0.5f);
}
