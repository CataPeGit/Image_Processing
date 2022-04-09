// Extra Credit 2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include "Image.h"
#include "ImageProcessing.cpp"
#include "Size.h"
#include "Point.h"
#include "Rectangle.h"
#include "Brightness_and_contrast.h"
#include "Gamma_correction.h"
#include "Convolution.h"

using namespace std;

namespace draw {

    void drawCircle(Image& img, Point center, unsigned int radius, unsigned int color) {

        for (unsigned int i = center.get_p_y() - radius; i <= center.get_p_y() + radius; i++) {
            for (unsigned int j = center.get_p_x() - radius; j <= center.get_p_x() + radius; j++) {
                if ((i - center.get_p_y()) * (i - center.get_p_y()) + (j - center.get_p_x()) * (j - center.get_p_x()) <= radius * radius)
                    img.set_point(color, i, j);
            }
        }

    }

    void drawLine(Image& img, Point p1, Point p2, unsigned int color) {

        unsigned int max_y = 0;
        unsigned int min_y = 0;
        unsigned int max_x = 0;
        unsigned int min_x = 0;

        if (p1.get_p_y() >= p2.get_p_y()) {
            max_y = p1.get_p_y();
            min_y = p2.get_p_y();
        }
        else if (p1.get_p_y() < p2.get_p_y()) {
            max_y = p2.get_p_y();
            min_y = p1.get_p_y();
        }

        if (p1.get_p_x() >= p2.get_p_x()) {
            max_x = p1.get_p_x();
            min_x = p2.get_p_x();
        }
        else {
            max_x = p2.get_p_x();
            min_x = p1.get_p_x();
        }

        if (min_y == max_y) {
            for (unsigned int i = min_x; i <= max_x; i++)
                img.set_point(color, max_y, i);
        }
        else {
            if (max_x < max_y && (max_x != min_x)) {
                max_x = max_y;
            }

            unsigned int j = min_x;
            for (unsigned int i = min_y; i <= max_y; i++) {
                if (j < max_x)
                    j++;
                img.set_point(color, i, j);
            }
        }
    }

    void drawRectangle(Image& img, Point topleft, Point bottomright, unsigned char color) {
        for (unsigned int i = topleft.get_p_y(); i <= bottomright.get_p_y(); i++) {
            for (unsigned int j = topleft.get_p_x(); j <= bottomright.get_p_x(); j++) {
                img.set_point(color, i, j);
            }
        }
    }
}


int main()
{

    Image a = Image(512, 512);
    Image c = Image(512, 512);
    Image b = Image(512, 512);
    Image d = b.ones(512, 512);

    int identity_kernel[3][3]{ {0, 0, 0}, {0, 1, 0}, {0, 0, 0} };
    int mean_blur_kernel[3][3]{ {1, 1, 1}, {1, 1, 1}, {1, 1, 1} };
    int Gaussian_blur_kernel[3][3]{ {1, 2, 1}, {2, 4, 2}, {1, 2, 1} };
    int Horizontal_Sobel_kernel[3][3]{ {1, 2, 1}, {0, 0, 0}, {-1, -2, -1} };
    int Vertical_Sobel_kernel[3][3]{ {-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1} };
    int kernel[3][3]{ {2, 2, 2}, {1, 1, 1}, {2, 2, 2} };

    cout << "Starting process...";
    cout << endl;

    string path = "baboon.ascii.pgm"; // ADD THE PROPER PATH
    a.load(path);
    c.load("lena.ascii.pgm"); // ADD THE PROPER PATH

    Point p1(200, 300);
    Point p2(256, 300);
    Point p3(400, 50);
    Point p4(300, 456);
    Point p5(500, 500);
    Point p6(40, 30);
    Point p7(40, 80);

    ImageProcessing* process_img = new Gamma_correction(0.6);
    //ImageProcessing* process_img = new Brightness_and_contrast(1, 75);
    //ImageProcessing* process_img = new Convolution(256, identity_kernel);

    process_img->process(a, b);

    /*
    draw::drawLine(b, p1, p2, 255);
    draw::drawCircle(b, p3, 34, 200);
    draw::drawRectangle(b, p4, p5, 255);
    draw::drawLine(b, p6, p7, 255);     
    */
    
    b.save("result_image.ascii.pgm"); // ADD THE PROPER PATH
    cout << "Done!";
    a.~Image();
    b.~Image();
    c.~Image();
    d.~Image();
    return 0;
}
