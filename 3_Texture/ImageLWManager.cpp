#include "ImageLWManager.h"
#include <iostream>
#include "stb_image.h"
#include "stb_image_write.h"

UnsignedImage ImageLoader::LoadImage(const std::string& filePath, int req_comp)
{
	int x, y, n;
	auto data = stbi_load(filePath.c_str(), &x, &y, &n, req_comp);

	if (req_comp != 0 && n > req_comp)
		n = req_comp;
	if (nullptr == data)
	{
		std::cerr << "Can't open the file.\n";
		exit(-1);
	}
	UnsignedImage image(x, y, n, data);

	return image;
}

int ImageWriter::WritePNGImage(const UnsignedImage& image, const std::string& outputPath)
{
	return stbi_write_png(outputPath.c_str(),
		image.GetWidth(),
		image.GetHeight(),
		image.GetComponents(),
		&(image.GetData()[0]),
		0);
}