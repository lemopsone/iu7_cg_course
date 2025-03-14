#ifndef OBJECTFACTORY_H
#define OBJECTFACTORY_H

#include "mandelbulb.h"
#include "sphere.h"
#include "cube.h"
#include "mandelbox.h"
#include "sceneobjecttype.h"

class ObjectFactory {
public:
    ObjectFactory() = delete;
    static SceneObject *create(const Object::Type &type) {
        switch (type) {
        case Object::MANDELBULB: return new Mandelbulb();
        case Object::MANDELBOX: return new Mandelbox();
        case Object::JULIA: return new Mandelbulb();
        case Object::CUBE: return new Cube();
        case Object::SPHERE: return new Sphere();
        }
    }
};

#endif // OBJECTFACTORY_H
