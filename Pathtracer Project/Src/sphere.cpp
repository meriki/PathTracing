//sphere.cpp

#include "sphere.h"

bool Sphere::intersect(Ray& r) const
{
	Vector3D centerVector = r.getOrigin() - position;
	double a = 1.0;
	double b = 2*dotProduct(r.getDirection(), centerVector);
	double c = dotProduct(centerVector, centerVector) - radius*radius;
	double discriminant = b*b - 4.0*a*c;
	//now check if discr. is posivtive or zero, then only we have an intersection!
	if(discriminant >=0.0)
	{

		if(discriminant == 0)
		{
			double t;
			t = -b/(2.0*a);
			bool b = r.setParameter(t, this);
			Vector3D normal = r.getPosition() - position;
			normal.normalize();
			r.setNormal(normal);
			return b;
		}
		else
		{
			//Calculate both roots
			double D = sqrt(discriminant);
			double t1 = (-b +D)/(2.0*a);
			double t2 = (-b -D)/(2.0*a);

			bool b1 = r.setParameter(t1, this);
			bool b2 = r.setParameter(t2, this);

			if(b1 || b2)	{
				Vector3D normal = r.getPosition() - position;
				normal.normalize();
				r.setNormal(normal);
			}
			return b1||b2;    
		}
	}
	return false;

}
Vector3D Sphere::getTexCoord(Vector3D pos)	const	{
	Vector3D dir = position - pos;
	dir.normalize();

	double u = 0.5 + atan2(dir.Y(), dir.X())/(2*M_PI);
	double v = 0.5 - asin(dir.Z())/M_PI;

	//std::cout<<u<<' '<<v<<'\n';

	return Vector3D(u, v, 0);

}

