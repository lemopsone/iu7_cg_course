#ifndef CAMERA_H
#define CAMERA_H

#include <QtCore>
#include <QVector3D>
#include "cameratype.h"



class Camera {
public:
    const qreal DEFAULT_RADIUS = 4.0f;
    explicit Camera(qreal fov = 45.0f) : m_FOV(fov) {}
    virtual ~Camera() = default;

    virtual void move(const QVector3D &delta) = 0;
    virtual void rotate(qreal dTheta, qreal dPhi) = 0;
    virtual void zoom(qreal delta) = 0;

    virtual QVector3D calculateRayDirection(qreal pixelX, qreal pixelY, int width, int height) const = 0;

    qreal getFOV() const { return m_FOV; }
    void setFOV(qreal fov) { m_FOV = fov; }

    QVector3D getPos() const { return m_pos; }
    void setPos(const QVector3D &pos) { m_pos = pos; }

    QVector3D getTargetPos() const { return m_target; }
    void setTargetPos(const QVector3D &target) { m_target = target; }

    virtual qreal getRadius() = 0;

    virtual Cam::Type getType() = 0;

    QVector3D getForward() const { return (m_target - m_pos).normalized(); }
    QVector3D getUp() const { return m_up; }

protected:
    qreal m_FOV;
    QVector3D m_pos = {4.0f, 0.0f, 0.0f};
    QVector3D m_target = {0.0f, 0.0f, 0.0f};
    QVector3D m_up = {0.0f, 1.0f, 0.0f};
};

#endif // CAMERA_H
