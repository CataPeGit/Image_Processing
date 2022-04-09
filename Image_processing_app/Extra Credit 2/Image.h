#pragma once
#include <string>
#include <fstream>
#include "Size.h"
#include "Point.h"
#include "Rectangle.h"

class Image {
public:
	Image();
	Image(unsigned int width, unsigned int height);

	Image(const Image& other);

	~Image();

	unsigned int width() const;
	unsigned int height() const;

	void set_point(unsigned int value, unsigned int x, unsigned int y);

	bool load(std::string imagePath);
	bool save(std::string imagePath);

	Size size() const;

	friend std::ostream& operator<<(std::ostream& os, const Image& dt);

	void operator=(const Image& other);

	Image operator+(const Image& i);
	Image operator-(const Image& i);
	Image operator*(const Image& i);

	Image operator+(const unsigned int scalar);
	Image operator-(const unsigned int scalar);
	Image operator*(const unsigned int scalar);

	bool isEmpty() const;

	unsigned int at_const(unsigned int x, unsigned int y) const;
	unsigned int& at(unsigned int x, unsigned int y);
	unsigned int& at(Point pt);

	unsigned int* row(int y);

	void release();
	void add_img_to_scalar(unsigned int scalar);

	Image getROI(unsigned int x, unsigned int y, unsigned int width, unsigned int height);
	Image getROI(Rectangle roiRect);

	static Image zeros(unsigned int width, unsigned int height);
	static Image ones(unsigned int width, unsigned int height);

	

private:
	unsigned int** m_data;
	unsigned int m_width;
	unsigned int m_height;
};

