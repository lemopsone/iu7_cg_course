#ifndef CUBE_H
#define CUBE_H

#include "sceneobject.h"

class Cube : public SceneObject
{
public:
    Cube() : SceneObject(), m_side(1.0f) {}
    Cube(QVector3D pos, qreal side = 1.0f, QColor color = Qt::cyan) : SceneObject(pos, color), m_side(side) {}
    virtual qreal SDF(const QVector3D &pos) override;
    virtual Object::Type getType() override { return Object::CUBE; }
    qreal getSide() { return m_side; }
    void setSide(qreal side) { m_side = side; }

private:
    qreal m_side = 1.0f;
};

#endif // CUBE_H
