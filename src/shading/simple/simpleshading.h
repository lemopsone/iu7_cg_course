#ifndef SIMPLESHADING_H
#define SIMPLESHADING_H

#include "shadingalgorithm.h"

class SimpleShading : public ShadingAlgorithm
{
    friend class ShadingFactory;
public:
    virtual QColor shade(Camera *cam, const QVector3D &normal, const QColor &baseColor, const QVector3D &hitPoint, LightSource *lightSource) override;
    virtual Shading::Type getType() override { return Shading::SIMPLE; }
protected:
    SimpleShading() : ShadingAlgorithm() {}
};

#endif // SIMPLESHADING_H
