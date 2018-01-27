//
// Created by sid on 29/11/17.
//

#include <cmath>
#include "texture.h"
#include "color.h"

Color Texture::getColor(unsigned x, unsigned y) {
    int idx = x + width*y*4;
    if(valid)
        return Color(img[idx]/255., img[idx+1]/255., img[idx+2]/255.);
    else
        return Color();
}

Color Texture::getColor(double u, double v) {
    //return getColor(unsigned(u*(width-1)), unsigned(v*(height-1)));
    unsigned x = fmod(fabs(u), 1.0)*(width - 1);
    unsigned y = (1-fmod(fabs(v), 1.0))*(height -1);
    return getColor(x, y);
}
