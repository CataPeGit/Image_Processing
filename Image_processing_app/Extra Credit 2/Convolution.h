#pragma once
#include "ImageProcessing.cpp"

class Convolution : public ImageProcessing {
public:

    Convolution() {
        m_range = 256;
        for (unsigned int i = 0; i < 3; i++)
            for (unsigned int j = 0; j < 3; j++)
                m_kernel[i][j] = 0;
    };

    Convolution(unsigned int range, int kernel[3][3]) {
        m_range = range;
        for (unsigned int i = 0; i < 3; i++)
            for (unsigned int j = 0; j < 3; j++) {
                m_kernel[i][j] = kernel[i][j];
                //std::cout << m_kernel[i][j] << " ";
            }
    };

    void Convolution::process(const Image& src, Image& dst) {

        unsigned int margin = 0;
        unsigned int height = src.height();
        unsigned int width = src.width();

        int mean_blur_kernel[3][3]{ {1, 1, 1}, {1, 1, 1}, {1, 1, 1} };
        int Gaussian_blur_kernel[3][3]{ {1, 2, 1}, {2, 4, 2}, {1, 2, 1} };
        int Horizontal_Sobel_kernel[3][3]{ {1, 2, 1}, {0, 0, 0}, {-1, -2, -1} };
        int Vertical_Sobel_kernel[3][3]{ {-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1} };
        //unsigned int kernel_origin = m_kernel[1][1];

        for (unsigned int i = 0; i < height; i++) {
            for (unsigned int j = 0; j < width; j++) {

                int new_pixel = 0;

                if ((i == 0 || j == 0 || (width - 1 == j) || (height - 1 == i)))
                    margin = 1;

                for (unsigned int y = 0; y <= 2; y++)
                    for (unsigned int x = 0; x <= 2; x++)
                        if (margin == 1 && ((x == 0 || y == 0) || (x == 2 || y == 2))) {
                            new_pixel = new_pixel + (m_kernel[y][x] * src.at_const(i, j));
                            //std::cout << m_kernel[y][x] << " ";
                        }
                        else {
                            new_pixel = new_pixel + (m_kernel[y][x] * src.at_const(i + y - 1, j + x - 1));
                        }
                //std::cout << new_pixel << "  ";
                //std::cout << "\n";


                // the following if statements will turn the image back to it's initial state
                if (compare(m_kernel, mean_blur_kernel))
                    new_pixel /= 9;
                if (compare(m_kernel, Gaussian_blur_kernel))
                    new_pixel /= 16;
                if (compare(m_kernel, Horizontal_Sobel_kernel)) {
                    if (new_pixel < 0)
                        new_pixel /= -4;
                    else
                        new_pixel /= 4;
                }
                if (compare(m_kernel, Vertical_Sobel_kernel)) {
                    if (new_pixel < 1)
                        new_pixel /= -4;
                    else
                        new_pixel /= 4;
                }

                new_pixel = new_pixel % m_range;
                //if (new_pixel > 255) new_pixel = 255;
                //std::cout << new_pixel << "  ";
                dst.at(i, j) = new_pixel;

                //std::cout << dst.at(i, j) << "  ";

            }
        }
    };

    bool compare(int ker1[3][3], int ker2[3][3]) {
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                if (ker1[i][j] != ker2[i][j])
                    return false;
        return true;
    }
private:
    unsigned int m_range;
    int m_kernel[3][3];
};

