//
// Created by siddh on 2/11/17.
//

#ifndef ASSIGNMENT4_TRANSFORMEDSURFACE_H
#define ASSIGNMENT4_TRANSFORMEDSURFACE_H

#include "object.h"

class TransformedSurface : public Object{
private:
    Object* model;
    glm::mat4 trans, inv;
public:
    TransformedSurface(glm::mat4 _t, Object* model, Material *m):
    Object(m), trans(_t)   {
        inv = glm::inverse(trans);
        this->model = model;
    }

    virtual bool intersect(Ray &r) const;

};


#endif //ASSIGNMENT4_TRANSFORMEDSURFACE_H
