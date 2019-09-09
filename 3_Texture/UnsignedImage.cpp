#include "UnsignedImage.h"

UnsignedImage::UnsignedImage(int w, int h, int n, const unsigned char* data) :
	Image(w, h, n)
{
	m_data.resize(this->GetSize());
	memcpy(&m_data[0], data, sizeof(unsigned char) * this->GetSize());
}

const unsigned char& UnsignedImage::At(int row, int col, int nth)const
{
	assert(row <= m_height && col <= m_width && nth <= m_components);
	return m_data[row * m_width * m_components + col * m_components + nth];
}
unsigned char& UnsignedImage::At(int row, int col, int nth)
{
	assert(row <= m_height && col <= m_width && nth <= m_components);
	return m_data[row * m_width * m_components + col * m_components + nth];
}