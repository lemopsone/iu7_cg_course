#ifndef SPHERE_H
#define SPHERE_H

#include "sceneobject.h"

class Sphere : public SceneObject
{
public:
    Sphere() : SceneObject(), m_radius(1.0f) {}
    Sphere(QVector3D pos, qreal radius = 1.0f, QColor color = Qt::white) : SceneObject(pos, color), m_radius(radius) {}
    virtual qreal SDF(const QVector3D &pos) override;
    virtual Object::Type getType() override { return Object::SPHERE; }

    qreal getRadius() { return m_radius; }
    void setRadius(qreal rad) { m_radius = rad; }
private:
    qreal m_radius = 1.0f;
};

#endif // SPHERE_H
