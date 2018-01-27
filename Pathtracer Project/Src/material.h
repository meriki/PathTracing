//matrial.h
#ifndef _MATERIAL_H_
#define _MATERIAL_H_

#include "color.h"
#include "ray.h"
#include "texture.h"

class Material
{
private:
	Color color, emit;
    Texture *tex;
public:

	Material(Color c, Color e=Color(), Texture *t=NULL): color(c), emit(e), tex(t) { }

	Color getColor()	{
		return color;
	}

    Color getColor(double u, double v)  {
        return tex->getColor(u, v);
    }

	Color getEmit()	{
		return emit;
	}

    bool hasTexture()   {
        return tex != NULL && tex->valid;
    }

	virtual Ray getNextRay(Ray& incident);
};
#endif
