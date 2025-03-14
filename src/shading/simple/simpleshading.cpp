#include "simpleshading.h"

QColor SimpleShading::shade(Camera *cam, const QVector3D &normal, const QColor &baseColor, const QVector3D &hitPoint, LightSource *lightSource)
{
    QVector3D lightDir = lightSource->getDirection(hitPoint);
    qreal intensity = std::max(0.0f, QVector3D::dotProduct(normal, lightDir)) * lightSource->getIntensity();
    QColor color = baseColor;
    color.setRedF(color.redF() * intensity);
    color.setGreenF(color.greenF() * intensity);
    color.setBlueF(color.blueF() * intensity);
    return color;
}

