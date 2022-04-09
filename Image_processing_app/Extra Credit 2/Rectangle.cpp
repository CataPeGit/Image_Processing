#include "Rectangle.h"
#include <iostream>
#include <iomanip>

Rectangle::Rectangle() {
    m_r_x = 0;
    m_r_y = 0;
    m_r_height = 1;
    m_r_width = 1;
    m_r_data = NULL;
}

Rectangle::Rectangle(unsigned int x, unsigned int y, unsigned int height, unsigned int width) {
    m_r_x = x;
    m_r_y = y;
    m_r_height = height;
    m_r_width = width;

    m_r_data = new unsigned int* [height]();

    for (unsigned int i = 0; i < width; i++) {
        m_r_data[i] = new unsigned int[width]();
    }

    for (unsigned int i = 0; i < height; i++) {
        for (unsigned int j = 0; j < width; j++) {
            m_r_data[i][j] = 0;
        }
    }


}

Rectangle::~Rectangle() {

    //delete[] m_data;
    for (unsigned int i = 0; i < m_r_height; i++) {
        delete m_r_data[i];
    }
    delete[] m_r_data;
    m_r_data = NULL;

}

unsigned int Rectangle::get_width() const {
    return m_r_width;
}

unsigned int Rectangle::get_height() const {
    return m_r_height;
}

unsigned int Rectangle::get_x() const {
    return m_r_x;
}

unsigned int Rectangle::get_y() const {
    return m_r_y;
}