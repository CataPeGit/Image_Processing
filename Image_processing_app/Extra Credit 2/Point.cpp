#include "Point.h"



Point::Point() {
	m_x = 0;
	m_y = 0;
}
Point::Point(unsigned int x, unsigned y) {
	m_x = x;
	m_y = y;
}

unsigned int Point::get_p_x() const {
	return m_x;
}

unsigned int Point::get_p_y() const {
	return m_y;
}