#ifndef PHONGSHADING_H
#define PHONGSHADING_H

#include "shadingalgorithm.h"

class PhongShading : public ShadingAlgorithm
{
    friend class ShadingFactory;
public:
    virtual QColor shade(Camera *cam, const QVector3D &normal, const QColor &baseColor, const QVector3D &hitPoint, LightSource *lightSource) override;
    virtual Shading::Type getType() override { return Shading::PHONG; }
protected:
    PhongShading() : ShadingAlgorithm() {}
};

#endif // PHONGSHADING_H
