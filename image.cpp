#include "image.h"
#include <algorithm>
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb/stb_image_write.h>


Image::Image()
	: width_(0), height_(0), channels_(0)
	, pData_(nullptr)
{

}


Image::~Image()
{
	if (pData_)
	{
		STBI_FREE(pData_);
	}
}


bool Image::load(std::string const & filePath)
{
	int w, h, chnl;
	int const reqComp = 0;
	pData_ = stbi_load(filePath.c_str(), &w, &h, &chnl, reqComp);

	if (nullptr == pData_)
	{
		return false;
	}
	width_ = static_cast<decltype(width_)>(w);
	height_ = static_cast<decltype(height_)>(h);
	channels_ = static_cast<decltype(channels_)>(chnl);

	sizeInByte_ = width_ * height_ * channels_;

	
	return true;
}


float Image::sample(float fU, float fV, size_t nth) const
{
	//u = std::min(1.f, std::max(0.f, u));
	//v = std::min(1.f, std::max(0.f, v));
	fU *= width_ - 1;
	fV *= height_ - 1;
	int iU = static_cast<int>(fU);
	int iV = static_cast<int>(fV);
	int iU1 = std::min(iU + 1, int(width_ - 1));
	int iV1 = std::min(iV + 1, int(height_ - 1));

	auto c0 = at(iU, iV);
	auto c1 = at(iU1, iV);
	auto c2 = at(iU, iV1);
	auto c3 = at(iU1, iV1);

	float dU = fU - iU;
	float dV = fV - iV;
	float pm3 = dU * dV;
	float pm2 = dU * (1.f - dV);
	float pm1 = dV * (1.f - dU);
	float pm0 = (1.f - dU) * (1.f - dV);

	float ret = pm0 * c0 + pm1 * c1 + pm2 * c2 + pm3 * c3;
	return ret;
}


bool Image::save(std::string const & filePath, TEX_FMT texFmt)
{
	if (!pData_)
		return false;

	if (eTexFmt_BMP == texFmt)
		stbi_write_bmp(filePath.c_str(), width_, height_, channels_, pData_);
	else if (eTexFmt_TGA == texFmt)
		stbi_write_tga(filePath.c_str(), width_, height_, channels_, pData_);
	else if (eTexFmt_PNG == texFmt)
		stbi_write_png(filePath.c_str(), width_, height_, channels_, pData_, width_*4);

	return true;
}


bool Image::create(int w, int h, int chnl)
{
	if (pData_)
	{
		STBI_FREE(pData_);
	}

	width_ = static_cast<decltype(width_)>(w);
	height_ = static_cast<decltype(height_)>(h);
	channels_ = static_cast<decltype(channels_)>(chnl);

	sizeInByte_ = width_ * height_ * channels_;

	pData_ = (decltype(pData_))STBI_MALLOC(sizeInByte_);

	return true;
}


void Image::bltFrom(Image const & src, int x, int y)
{
	if (x < 0)
	{
		x = 0;
	}
	if (y < 0)
	{
		y = 0;
	}

	int const srcLine = src.channels_ * src.width_;
	int const dstLine = channels_ * width_;

	for (int i = 0; i < src.height_; ++i)
	{
		byte *pSrcI = src.pData_ + srcLine * i;
		byte *pDstI = pData_ + dstLine * (i + y);
		if (i + y >= height_)
			break;
		for (int j = 0; j < src.width_; ++j)
		{
			byte *pSrcJ = pSrcI + src.channels_ * j;
			byte *pDstJ = pDstI + channels_ * (j + x);
			if (j + x >= width_)
				break;
			for (int k = 0; k < src.channels_; ++k)
			{
				*(pDstJ + k) = *(pSrcJ + k);
			}
		}
	}
}


void Image::transpose()
{
	std::swap(width_, height_);
	if (!pData_)
		return;
	for (int i = 0; i < height_; ++i)
	{
		for (int j = 0; j < width_; ++j)
		{
			for (int k = 0; k < channels_; ++k)
			{
				std::swap(at(i, j, k), at(j, i, k));
			}
		}
	}
}
