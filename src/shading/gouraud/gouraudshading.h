#ifndef GOURAUDSHADING_H
#define GOURAUDSHADING_H

#include "shadingalgorithm.h"

class GouraudShading : public ShadingAlgorithm
{
    friend class ShadingFactory;
public:
    virtual QColor shade(Camera *cam, const QVector3D &normal, const QColor &baseColor, const QVector3D &hitPoint, LightSource *lightSource) override;
    virtual Shading::Type getType() override { return Shading::GOURAUD; }
protected:
    GouraudShading() : ShadingAlgorithm() {}
};

#endif // GOURAUDSHADING_H
