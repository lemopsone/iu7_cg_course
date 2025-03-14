#ifndef MANDELBOX_H
#define MANDELBOX_H

#include "sceneobject.h"
#include <QVector3D>

class Mandelbox : public SceneObject {
public:
    Mandelbox(float scale = 2.0f, int iterations = 20)
        : m_scale(scale), m_iterations(iterations) {}

    qreal SDF(const QVector3D& p) override {
        auto z = QVector3D(p);
        QVector3D offset = p * 1.6;
        double dr = 1.0;
        for (int n = 0; n < m_iterations; n++)
        {
            boxFold(z);
            ballFold(z, &dr);
            z = m_scale * z + offset;
            dr = dr * qAbs(m_scale) + 1.0;
        }
        float r = z.length();
        return r / qAbs(dr);
    }

    Object::Type getType() override {
        return Object::Type::MANDELBOX;
    }

private:
    void ballFold(QVector3D &vec, double *dz)
    {
        qreal z_sq = QVector3D::dotProduct(vec, vec);
        qreal z_sqrt = qSqrt(z_sq);
        if (z_sqrt < 0.5)
        {
            qreal temp = 2.0;
            vec *= temp;
            *dz *= temp;
        }
        else if (z_sqrt < 1.0)
        {
            qreal temp = 1.0 / z_sq;
            vec *= temp;
            *dz *= temp;
        }
    }

    void boxFold(QVector3D &vec)
    {
        vec = clampVec(vec, -1.0, 1.0) * 2.0 - vec;
    }

    QVector3D clampVec(QVector3D &vec, double a, double b)
    {
        return QVector3D(
            std::clamp((double)vec.x(), a, b),
            std::clamp((double)vec.y(), a, b),
            std::clamp((double)vec.z(), a, b)
            );
    }

    float m_scale;
    int m_iterations;
};

#endif // MANDELBOX_H
