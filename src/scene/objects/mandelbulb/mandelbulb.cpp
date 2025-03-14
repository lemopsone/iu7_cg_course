#include "mandelbulb.h"
#include <iostream>

qreal Mandelbulb::SDF(const QVector3D &point) {
    QVector3D z = (point - m_pos);
    qreal dr = 1.0;
    qreal r = 0.0;
    for (int i = 0; i < m_iters; ++i) {
        r = z.length();
        if (r > m_rad) break;
        qreal theta = std::atan2(z.y(), z.x());
        qreal phi = std::acos(z.z() / r);
        dr = std::pow(r, m_power - 1.0) * m_power * dr + 1.0;
        qreal zr = std::pow(r, m_power);
        theta *= m_power;
        phi *= m_power;
        z = zr * QVector3D(std::sin(phi) * std::cos(theta),
                           std::sin(phi) * std::sin(theta),
                           std::cos(phi))
            + (point - m_pos);
    }
    return 0.5 * std::log(r) * r / dr; // SDF значение
}
