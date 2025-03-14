#include "sphere.h"

qreal Sphere::SDF(const QVector3D &pos)
{
    return (pos - m_pos).length() - m_radius;
}
