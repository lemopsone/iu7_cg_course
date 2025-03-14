#ifndef SHADINGFACTORY_H
#define SHADINGFACTORY_H

#include "shadingtype.h"
#include "gouraudshading.h"
#include "phongshading.h"
#include "simpleshading.h"

class ShadingFactory {
public:
    static ShadingAlgorithm *create(const Shading::Type &type) {
        switch (type) {
        case Shading::SIMPLE: return new SimpleShading();
        case Shading::PHONG: return new PhongShading();
        case Shading::GOURAUD: return new GouraudShading();
        }
    }
};

#endif // SHADINGFACTORY_H
