#pragma once
#include <assert.h>
#include <cstring>

class Image
{
protected:
	unsigned int m_width;
	unsigned int m_height;
	unsigned int m_components;
public:
	Image(int w, int h, int n);
	virtual ~Image() = default;

	//getter and setter
	unsigned int GetWidth()const { return m_width; }
	unsigned int GetHeight()const { return m_height; }
	unsigned int GetComponents()const { return m_components; }
	unsigned int GetSize()const { return m_width * m_height * m_components; }
};