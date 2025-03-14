#ifndef FREECAMERA_H
#define FREECAMERA_H

#include <QMatrix4x4>
#include "camera.h"

class FreeCamera : public Camera {
public:
    explicit FreeCamera(qreal fov = 45.0f) : Camera(fov) {}

    virtual Cam::Type getType() override { return Cam::FREE; }

    void move(const QVector3D &delta) override {
        auto dist = (m_pos + delta).length();
        if (dist <= 10.0 && dist >= 1.05)
        {
            m_pos += delta;
            m_target += delta;
        }
    }

    void rotate(qreal dTheta, qreal dPhi) override {
        QVector3D forward = (m_target - m_pos).normalized();
        QVector3D right = QVector3D::crossProduct(forward, m_up).normalized();

        // Поворот по азимуту (dTheta) вокруг оси up
        QMatrix4x4 rotationTheta;
        rotationTheta.rotate(-dTheta * 180.0 / M_PI, m_up);
        forward = rotationTheta.map(forward);

        // Поворот по углу высоты (dPhi) вокруг оси right
        QMatrix4x4 rotationPhi;
        rotationPhi.rotate(dPhi * 180.0 / M_PI, right);
        forward = rotationPhi.map(forward);

        m_target = m_pos + forward;
    }

    void zoom(qreal delta) override {
        // QVector3D forward = (m_target - m_pos).normalized();
        // m_pos += forward * delta;
        Q_UNUSED(delta);
    }

    virtual qreal getRadius() override { return m_pos.length(); }

    QVector3D calculateRayDirection(qreal pixelX, qreal pixelY, int width, int height) const override {
        qreal aspectRatio = static_cast<qreal>(width) / height;
        qreal fovScale = std::tan(m_FOV * 0.5 * M_PI / 180.0);

        qreal screenX = (2 * pixelX / width - 1) * aspectRatio * fovScale;
        qreal screenY = (1 - 2 * pixelY / height) * fovScale;

        QVector3D forward = (m_target - m_pos).normalized();
        QVector3D right = QVector3D::crossProduct(forward, m_up).normalized();
        QVector3D up = QVector3D::crossProduct(right, forward).normalized();

        QVector3D rayDirection = (forward + screenX * right + screenY * up).normalized();
        return rayDirection;
    }
};

#endif // FREECAMERA_H
