//
// Created by sid on 29/11/17.
//

#ifndef CGPROJECT_TEXTURE_H
#define CGPROJECT_TEXTURE_H

#include "lodepng.h"
#include <vector>
#include <iostream>
#include "color.h"
class Texture {
private:
    std::vector<unsigned char>img;
    unsigned int width, height;


public:
    bool valid = false;
    Texture()   {
        valid = false;
    }
    Texture(const char* filename) {
        img = std::vector<unsigned char>();
        if(lodepng::decode(img, width, height, filename))  {
            std::cout<<"Unable to load texture\n";
        }
        else    {
            valid = true;
            std::cout<<"Loaded texture\n";
        }
    }
    Color getColor(unsigned x, unsigned y);
    Color getColor(double u, double v);

};


#endif //CGPROJECT_TEXTURE_H
