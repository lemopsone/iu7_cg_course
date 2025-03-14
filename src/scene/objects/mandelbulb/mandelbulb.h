#ifndef MANDELBULB_H
#define MANDELBULB_H

#include "sceneobject.h"

class Mandelbulb : public SceneObject
{
public:
    Mandelbulb(QColor color = QColor::fromRgb(0, 139, 139)) : SceneObject({0, 0, 0}, color), m_power(8.0), m_iters(50) {}
    Mandelbulb(qreal power, qsizetype maxIters, QVector3D pos = {0, 0, 0}, QColor color = Qt::cyan)
        : SceneObject(pos, color), m_power(power), m_iters(maxIters) {}

    qreal getRad() { return m_rad; }
    void setRad(qreal rad) { m_rad = rad; }

    qreal getPower() { return m_power; }
    void setPower(qreal power) { m_power = power; }

    qsizetype getIters() { return m_iters; }
    void setIters(qsizetype iters) { m_iters = iters; }

    virtual qreal SDF(const QVector3D &point) override;
    virtual Object::Type getType() override { return Object::MANDELBULB; }

protected:
    qreal m_power;
    qsizetype m_iters;
    qreal m_rad = 3.0f;
};

#endif // MANDELBULB_H
