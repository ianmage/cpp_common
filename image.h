#pragma once

#include <string>
//#include <cassert>


typedef unsigned char	byte;


enum TEX_FMT
{
	eTexFmt_BMP = 0,
	eTexFmt_TGA,
	eTexFmt_PNG,
};


class Image
{
public:
	Image();
	~Image();

	bool create(int w, int h, int chnl);
	bool load(std::string const & filePath);
	bool save(std::string const & filePath, TEX_FMT texFmt);

	int width() const { return width_; }
	int height() const { return height_; }
	int channels() const { return channels_; }
	size_t sizeInByte() const { return sizeInByte_; }

	byte * pData() const { return pData_; }

	byte const & at(int row, int col, size_t nth = 0) const {
		//assert(row <= height_ && col <= width_ && nth < channels_);
		return pData_[(row*width_ + col) * channels_ + nth];
	}
	byte & at(int row, int col, size_t nth = 0) {
		//assert(row <= height_ && col <= width_ && nth < channels_);
		return pData_[(row*width_ + col) * channels_ + nth];
	}
	float sample(float fU, float fV, size_t nth = 0) const;

	void transpose();

	void bltFrom(Image const & src, int x, int y);

protected:
	int width_;
	int height_;
	int channels_;
	size_t sizeInByte_;

	byte * pData_;
};
