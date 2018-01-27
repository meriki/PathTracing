//object.h
#ifndef _OBJECT_H_
#define _OBJECT_H_

#include "ray.h"
#include "vector3D.h"
#include "color.h"
#include "material.h"

class Object
{
protected:
	Material *material;
	bool isSolid;
public:
	Object(Material *mat): material(mat) {}
	Material* getMaterial()	const{
		return material;
	}

	Color getColor(Vector3D position)	const{
		if(material->hasTexture())	{
			Vector3D texC = getTexCoord(position);
			return material->getColor(texC.X(), texC.Y());

		}
		else
			return material->getColor();

	}
	virtual bool intersect(Ray& ray) const = 0;
	virtual Vector3D getTexCoord(Vector3D pos)	const = 0;
};

#endif
