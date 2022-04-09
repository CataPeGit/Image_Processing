#pragma once
#include "ImageProcessing.cpp"

class Gamma_correction : public ImageProcessing {
public:

    Gamma_correction() {
        m_gamma = 1;
    }

    Gamma_correction(float gamma) {
        m_gamma = gamma;
    }

    void Gamma_correction::process(const Image& src, Image& dst) override {
        for (unsigned int i = 0; i < src.height(); i++) {
            for (unsigned int j = 0; j < src.width(); j++) {
                unsigned int current_pixel_source = src.at_const(i, j);
                dst.at(i, j) = ((unsigned int)pow(current_pixel_source, m_gamma)) % 256;
            }
        }
    }

private:
    float m_gamma;

};
