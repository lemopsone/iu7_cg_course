#ifndef SHADINGALGORITHM_H
#define SHADINGALGORITHM_H

#include <QVector3D>
#include <QColor>
#include "shadingtype.h"
#include "lightsource.h"
#include "spherecamera.h"

class ShadingAlgorithm
{
    friend class ShadingFactory;
public:
    virtual QColor shade(Camera *cam, const QVector3D &normal, const QColor &baseColor, const QVector3D &hitPoint, LightSource *lightSource) = 0;

    virtual Shading::Type getType() = 0;
protected:
    ShadingAlgorithm() {}
};

#endif // SHADINGALGORITHM_H
