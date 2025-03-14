#include "cube.h"

qreal Cube::SDF(const QVector3D &pos)
{
    QVector3D d = QVector3D(qAbs(pos.x()), qAbs(pos.y()), qAbs(pos.z())) - QVector3D(m_side/2, m_side/2, m_side/2);
    return qMin(
             qMax(
                 d.x(), qMax(d.y(), d.z())
             ), 0.0
         ) + QVector3D(qMax(d.x(), 0.0), qMax(d.y(), 0.0), qMax(d.z(), 0.0)).length();
}
