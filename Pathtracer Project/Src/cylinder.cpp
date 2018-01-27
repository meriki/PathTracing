//
// Created by siddh on 11-10-2017.
//

#include "cylinder.h"
bool Cylinder::intersect(Ray &r) const {
    Ray &tr = r;
    Vector3D o = tr.getOrigin();
    Vector3D d = tr.getDirection();
    Vector3D normal;
    bool f = false, acc = false;
    double a = d.X()*d.X() + d.Y()*d.Y();
    double b = 2*(o.X()*d.X() + o.Y()*d.Y());
    double c = o.X()*o.X() + o.Y()*o.Y() - radius*radius;

    double det = b*b - 4*a*c;
    if(det >= 0)    {
        double t1 = 0.5*(-b + sqrt(det))/a;
        double t2 = 0.5*(-b - sqrt(det))/a;

        double z1 = o.Z() + t1*d.Z();
        double z2 = o.Z() + t2*d.Z();
        double t;
        if(z1 > 0 && z1 < height || z2 >= 0 && z2 < height)    {
            if(z1 > 0 && z1 < height && z2 >= 0 && z2 < height)
                t = std::min(t1, t2);
            else if (z1 > 0 && z1 < height)
                t = t1;
            else
                t = t2;
            f = r.setParameter(t, this);
            if(f) {
                normal = o + t * d;
                normal.Z(0);
                normal.normalize();
                r.setNormal(normal);
            }
            acc |= f;
        }

        if(z1 * z2 < 0) {
            t = -o.Z()/d.Z();
            f = r.setParameter(t, this);
            if(f)   {
                normal = Vector3D(0, 0, -1);
                normal.normalize();
                r.setNormal(normal);
            }
            acc |= f;

        }

        if((z1 - height) * (z2 - height) < 0)   {
            t = (height-o.Z())/d.Z();
            f = r.setParameter(t, this);
            if(f) {
                normal = Vector3D(0, 0, 1);
                normal.normalize();
                r.setNormal(normal);
            }
            acc |= f;
        }


    }
    return acc;


}