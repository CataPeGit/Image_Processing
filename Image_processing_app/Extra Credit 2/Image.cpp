#include "Image.h"
#include <iostream>
#include <iomanip>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>


using namespace std;

bool Image::load(std::string imagePath) {
    fstream imageFile;
    imageFile.open(imagePath);
    imageFile.get();
   
    int max_grey_value = 0;
    if (imageFile.is_open()) {
        string line;
        getline(imageFile, line); // reading magic number (P2)
        //cout << "Magic number: " << line << endl;
        getline(imageFile, line); // reading comment
        //cout << "Comment: " << line << endl;

        imageFile >> this->m_width;
        imageFile >> this->m_height;
        imageFile >> max_grey_value; // maximum gray value -> 255 in our case
        //cout << max_grey_value;

        for (unsigned int i = 0; i < m_height; i++) {
            for (unsigned int j = 0; j < m_width; j++) {
                imageFile >> m_data[i][j];
                //cout << m_data[i][j] << " ";
            }
            //cout << endl;
        }

        imageFile.close();
        return 1;
    }
    else {
        cout << "File did not open. Please make sure the correct path is provided.";
    }
    imageFile.close();
    return 0;
}

bool Image::save(std::string imagePath) {
    fstream outFile;
    outFile.open(imagePath, ios::out);
    
    if (outFile.is_open()) {

        outFile << "P2\n";
        outFile << m_width << "  ";
        outFile << m_height << "\n";
        outFile << "255" << "\n"; // maximum gray value -> 255 in our case

        for (unsigned int i = 0; i < m_height; i++) {
            for (unsigned int j = 0; j < m_width; j++) {
                outFile << m_data[i][j] << "  ";
            }
            outFile << "\n";
        }
        

        outFile.close();
        return 1;
    }
    outFile.close();
    return 0;
}



Image::Image() {
    this->m_data = new unsigned int*[256]();
	this->m_width = 0;
	this->m_height = 0;
}

Image::Image(unsigned int width, unsigned int height) {

	this->m_width = width;
	this->m_height = height;
    this->m_data = new unsigned int* [m_height]();
    for (unsigned int i = 0; i < m_width; i++) {
        m_data[i] = new unsigned int[m_width]();
    }

}

Image::Image(const Image& other) {
    this->m_width = other.m_width;
    this->m_height = other.m_height;

    this->m_data = new unsigned int* [m_height]();
    for (unsigned int i = 0; i < m_width; i++) {
        m_data[i] = new unsigned int[m_width]();
    }

    for (unsigned int i = 0; i < m_height; i++) {
        for (unsigned int j = 0; j < m_width; j++) {
            m_data[i][j] = other.m_data[i][j];
        }
    }
}

Image::~Image() {

    release();

}

unsigned int Image::width() const {
    return this->m_width;
}
unsigned int Image::height() const {
    return this->m_height;
}

void Image::set_point(unsigned int value, unsigned int y, unsigned int x) {
    m_data[y][x] = value;
}

Size Image::size() const {
    return Size(this->m_width * this->m_height);
}

bool Image::isEmpty() const {
    
    if (m_width == 0 || m_height == 0) {
        return 1;
    }

    for (unsigned int i = 0; i < m_height; i++) {
        for (unsigned int j = 0; j < m_width; j++) {
            if (m_data[i][j] != NULL)
                return 0;
        }
    }

    return 1;
}

unsigned int& Image::at(unsigned int x, unsigned int y) {
    unsigned int& at = m_data[x][y];
    return at;
}

unsigned int Image::at_const(unsigned int x, unsigned int y) const {
    return m_data[x][y];
}

unsigned int& Image::at(Point pt) {
    return m_data[pt.get_p_x()][pt.get_p_y()];
}

unsigned int* Image::row(int y) {
    return m_data[y];
}

void Image::release() {

    //delete[] m_data;
    for (unsigned int i = 0; i < m_height; i++) {
        delete m_data[i];
    }
    delete[] m_data;
    m_data = NULL;

}

Image Image::getROI(Rectangle roiRect) {

    // Coordinates x and y will specify the top left point of the rectangle

    if (!(roiRect.get_x() >= 0 && roiRect.get_x() < roiRect.get_width() && roiRect.get_y() >= 0 && roiRect.get_y() < roiRect.get_height())) {
        cout << "ROI not valid.";
        return Image();
    }

    Image new_image = Image(roiRect.get_width(), roiRect.get_height());
    for (unsigned int i = roiRect.get_x(); i < new_image.m_height + roiRect.get_x(); i++) {
        for (unsigned int j = roiRect.get_y(); j < new_image.m_width + roiRect.get_y(); j++) {
            new_image.m_data[i][j] = m_data[i][j];
            //cout << new_image.m_data[i][j] << " ";
        }
        //cout << endl;
    }


    return new_image; // ROI valid
}

Image Image::getROI( unsigned int x, unsigned int y, unsigned int width, unsigned int height) {
    
    // Coordinates x and y will specify the top left point of the rectangle

    if (!(x >= 0 && x < width && y >= 0 && y < height)) {
        cout << "ROI not valid.";
        return Image();
    }

    Image new_image = Image(width, height);

    for (unsigned int i = y; i < height + y; i++) {
        for (unsigned int j = x; j < width + x; j++) {
            new_image.m_data[i][j] = m_data[i][j];
            //cout << new_image.m_data[i][j] << " ";
        }
        //cout << endl;
    }

    return new_image; // ROI valid

}

Image Image::zeros(unsigned int width, unsigned int height) {

    Image result = Image(width, height);
    //cout << height;
    for (unsigned int i = 0; i < height ; i++) {
        for (unsigned int j = 0; j < width ; j++) {
            result.m_data[i][j] = 0;
            //cout << result.m_data[i][j] << " ";
        }
        //cout << endl;
    }

    return result;
}
Image Image::ones(unsigned int width, unsigned int height) {

    Image result = Image(width, height);

    for (unsigned int i = 0; i < height; i++) {
        for (unsigned int j = 0; j < width; j++) {
            result.m_data[i][j] = 1;
        }
    }

    return result;
}

void Image::add_img_to_scalar(unsigned int scalar) {

    for (unsigned int h = 0; h < m_height; h++) {
        for (unsigned int j = 0; j < m_width; j++) {
           m_data[h][j] = (m_data[h][j] + scalar) % 256;
        }
    }
}



void Image::operator=(const Image& other) {
    m_height = other.m_height;
    m_width = other.m_width;
    for (unsigned int h = 0; h < other.m_height; h++) {
        for (unsigned int j = 0; j < other.m_width; j++) {
            m_data[h][j] = other.m_data[h][j];
            //cout << m_data[h][j] << " ";
        }
    }

}


std::ostream& operator<<(std::ostream& os, const Image& dt) {

    for (unsigned int i = 0; i < dt.m_height; i++) {
        os << setw(3);
        for (unsigned int j = 0; j < dt.m_width; j++) {
            os << setw(3);
            os << dt.m_data[i][j] << "  ";
        }
        os << "\n";
    }

    return os;
}

Image Image::operator+(const Image& i) {

    if (!(this->size().isSizeEqual(i.size()))) {
        cout << ("Images size must be equal.");
    }
    Image result(i.m_width, i.m_height);
    for (unsigned int h = 0; h < result.m_height; h++) {
        for (unsigned int j = 0; j < result.m_width; j++) {
            result.m_data[h][j] = (this->m_data[h][j] + i.m_data[h][j]) % 256;
        }
    }

    return result;
}

Image Image::operator-(const Image& i) {

    if (!(this->size().isSizeEqual(i.size()))) {
        cout << ("Images size must be equal.");
    }
    Image result(i.m_width, i.m_height);
    for (unsigned int h = 0; h < result.m_height; h++) {
        for (unsigned int j = 0; j < result.m_width; j++) {
            int result_to_check = (this->m_data[h][j] - i.m_data[h][j]);
            if (result_to_check <= 0) 
                result.m_data[h][j] = 0;
            else 
                result.m_data[h][j] = result_to_check % 256;
        }
    }

    return result;
}

Image Image::operator*(const Image& i) {

    if (!(this->size().isSizeEqual(i.size()))) {
        cout << ("Images size must be equal.");
    }
    Image result(i.m_width, i.m_height);
    for (unsigned int h = 0; h < result.m_height; h++) {
        for (unsigned int j = 0; j < result.m_width; j++) {
            result.m_data[h][j] = (this->m_data[h][j] * i.m_data[h][j]) % 256;
        }
    }

    return result;
}


Image Image::operator+(const unsigned int scalar) {

    Image result(m_width, m_height);
    for (unsigned int i = 0; i < result.m_height; i++) {
        for (unsigned int j = 0; j < result.m_width; j++) {
            result.m_data[i][j] = (this->m_data[i][j] + scalar) % 256;
        }
    }

    return result;
}

Image Image::operator-(const unsigned int scalar) {

    Image result(m_width, m_height);
    for (unsigned int i = 0; i < result.m_height; i++) {
        for (unsigned int j = 0; j < result.m_width; j++) {
            int result_to_check = (this->m_data[i][j] - scalar);
            if (result_to_check <= 0)
                result.m_data[i][j] = 0;
            else
                result.m_data[i][j] = result_to_check;
        
        }
    }

    return result;
}


Image Image::operator*(const unsigned int scalar) {

    Image result(m_width, m_height);
    for (unsigned int i = 0; i < result.m_height; i++) {
        for (unsigned int j = 0; j < result.m_width; j++) {
            result.m_data[i][j] = (this->m_data[i][j] * scalar) % 256;
        }
    }

    return result;
}



/*
// Function to ignore any comments in file
void ignoreComments(FILE* fp)
{
    int ch;
    char line[100];

    // Ignore any blank lines
    while ((ch = fgetc(fp)) != EOF
        && isspace(ch))
        ;

    // Recursively ignore comments
    // in a PGM image commented lines
    // start with a '#'
    if (ch == '#') {
        fgets(line, sizeof(line), fp);
        ignoreComments(fp);
    }
    else
        fseek(fp, -1, SEEK_CUR);
}
*/
