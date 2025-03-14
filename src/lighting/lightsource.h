#ifndef LIGHTSOURCE_H
#define LIGHTSOURCE_H

#include <QVector3D>
#include <QColor>

class LightSource
{
public:
    LightSource() {}
    LightSource(QVector3D pos, qreal intensity) : m_position(pos), m_intensity(intensity) {}

    QVector3D getPosition() { return m_position; }
    void setPosition(QVector3D pos) { m_position = pos; }

    qreal getIntensity() { return m_intensity; }
    void setIntensity(qreal intensity) { m_intensity = intensity; }

    QVector3D getDirection(QVector3D point) { return (point - m_position).normalized(); }

protected:
    QVector3D m_position = {4, 0, 0};
    qreal m_intensity = 1.0f;
};

#endif // LIGHTSOURCE_H
