#pragma once
#include "Image.h"
#include <vector>

class UnsignedImage : public Image
{
private:
	std::vector<unsigned char> m_data;
public:
	UnsignedImage(int w, int h, int n, const unsigned char* data);
	~UnsignedImage() = default;

	std::vector<unsigned char> GetData()const { return m_data; }
	const unsigned char& At(int row, int col, int nth)const;
	unsigned char& At(int row, int col, int nth);
};