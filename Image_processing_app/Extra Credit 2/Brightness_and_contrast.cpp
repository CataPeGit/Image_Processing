/*
#pragma once
#include "Brightness_and_contrast.h"

Brightness_and_contrast::Brightness_and_contrast() {
	m_gain = 1;
	m_bias = 0;
}

Brightness_and_contrast::Brightness_and_contrast(unsigned int gain, unsigned int bias) {
	m_gain = gain;
	m_bias = bias;
}



void Brightness_and_contrast::process(const Image& src, Image& dst) {

	for (unsigned int i = 0; i < src.m_height; i++) {
		for (unsigned int j = 0; j < src.m_width; j++) {
			src.m_data[i][j] = (src.m_data[i][j] + m_gain + m_bias) % 256;
		}
	}

	dst = src;

}

*/
