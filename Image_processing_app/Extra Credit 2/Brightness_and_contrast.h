#pragma once
#include "ImageProcessing.cpp"

class Brightness_and_contrast :  public ImageProcessing {
public:
    
    Brightness_and_contrast() {
        m_gain = 1;
        m_bias = 0;
    }

    Brightness_and_contrast(unsigned int gain, unsigned int bias) {
        m_gain = gain;
        m_bias = bias;
    }

	void Brightness_and_contrast::process(const Image& src, Image& dst) override {
        for (unsigned int i = 0; i < src.height(); i++) {
            for (unsigned int j = 0; j < src.width(); j++) {
                unsigned int current_pixel_source = src.at_const(i, j);
                dst.at(i, j) = (m_gain * current_pixel_source + m_bias) % 256;
            }
        }
	}

private:
    unsigned int m_gain;
    unsigned int m_bias;

};