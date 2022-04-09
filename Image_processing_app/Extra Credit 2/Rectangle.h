#pragma once

class Rectangle {
public:
	Rectangle();
	Rectangle(unsigned int x, unsigned int y, unsigned int height, unsigned int width);
	unsigned int get_width() const;
	unsigned int get_height() const;
	unsigned int get_x() const;
	unsigned int get_y() const;
	~Rectangle();
protected:
	unsigned int** m_r_data;
	unsigned int m_r_x;
	unsigned int m_r_y;
	unsigned int m_r_height;
	unsigned int m_r_width;
};