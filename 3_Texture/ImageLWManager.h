#pragma once
#include "Image.h"
#include "UnsignedImage.h"
#include <cstring>
#include <iostream>
class ImageLoader
{
public:
	ImageLoader() = default;
	static UnsignedImage LoadImage(const std::string& filePath, int req_comp);
};

class ImageWriter
{
public:
	ImageWriter() = default;
	static int WritePNGImage(const UnsignedImage& image, const std::string& outputPath);
};