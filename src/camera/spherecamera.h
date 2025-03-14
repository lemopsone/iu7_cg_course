#ifndef SPHERECAMERA_H
#define SPHERECAMERA_H

#include "camera.h"
#include <QDebug>

class SphereCamera : public Camera {
public:
    explicit SphereCamera(qreal radius = 4.0f, qreal fov = 45.0f)
        : Camera(fov), m_radius(radius), m_phi(M_PI / 2), m_theta(0) {
        updatePosition();
    }

    virtual Cam::Type getType() override { return Cam::SPHERE; }

    void move(const QVector3D &delta) override { Q_UNUSED(delta); }

    void rotate(qreal dTheta, qreal dPhi) override {
        m_theta += dTheta;
        // m_phi = std::clamp(m_phi + dPhi, 0.01, M_PI - 0.01); // Ограничиваем φ, чтобы избежать переворота
        m_phi = (m_phi + dPhi);
        updatePosition();
    }

    void zoom(qreal delta) override {
        m_radius = std::min(4.0, std::max(1.0, m_radius - delta)); // Ограничение минимального радиуса
        updatePosition();
    }

    QVector3D calculateRayDirection(qreal pixelX, qreal pixelY, int width, int height) const override {
        qreal aspectRatio = static_cast<qreal>(width) / height;
        qreal fovScale = std::tan(m_FOV * 0.5 * M_PI / 180.0);

        qreal screenX = (2 * pixelX / width - 1) * aspectRatio * fovScale;
        qreal screenY = (1 - 2 * pixelY / height) * fovScale;

        QVector3D forward = (m_target - m_pos).normalized();
        QVector3D right = QVector3D::crossProduct(forward, m_up).normalized();
        QVector3D up = QVector3D::crossProduct(right, forward).normalized();

        QVector3D rayDirection = (forward + screenX * right + screenY * up).normalized();
        // qDebug() << "RayDirection:" << rayDirection;
        // qDebug() << "Camera Position:" << m_pos << "Target:" << m_target;
        return rayDirection;
    }

    virtual qreal getRadius() override { return m_radius; }

private:
    void updatePosition() {
        m_pos.setX(m_radius * std::sin(m_phi) * std::cos(m_theta) + m_target.x());
        m_pos.setY(m_radius * std::cos(m_phi) + m_target.y());
        m_pos.setZ(m_radius * std::sin(m_phi) * std::sin(m_theta) + m_target.z());
    }

    qreal m_radius;
    qreal m_phi, m_theta;
};

#endif // SPHERECAMERA_H
