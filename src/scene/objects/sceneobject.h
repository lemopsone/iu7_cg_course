#ifndef SCENEOBJECT_H
#define SCENEOBJECT_H

#include <QVector3D>
#include <QColor>
#include "sceneobjecttype.h"

class SceneObject
{
public:
    SceneObject(QVector3D pos = {0, 0, 0}, QColor color = Qt::red) : m_pos(pos), m_color(color) {}

    QVector3D getPos(){ return m_pos; }
    void setPos(QVector3D pos){ m_pos = pos; }

    QColor getColor() { return m_color; }
    void setColor(QColor color) { m_color = color; }

    virtual qreal SDF(const QVector3D &point) = 0;
    virtual Object::Type getType() = 0;

protected:
    QVector3D m_pos = {0, 0, 0};
    QColor m_color;
};

#endif // SCENEOBJECT_H
