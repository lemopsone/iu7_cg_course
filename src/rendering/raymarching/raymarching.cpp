#include "raymarching.h"

void RayMarching::render(QImage *img, const QColor &bgColor, Camera *cam, QList<SceneObject *> *objects, LightSource *lightSource)
{
    const qsizetype width = img->width();
    const qsizetype height = img->height();
    const QVector3D origin = cam->getPos();

    for (qsizetype y = 0; y < height; ++y)
    {
        for (qsizetype x = 0; x < width; ++x)
        {
            QVector3D rayDirection = cam->calculateRayDirection(x, y, width, height);
            QColor pixelColor = castRay(origin, rayDirection, bgColor ,cam, objects, lightSource);
            img->setPixelColor(x, y, pixelColor);
        }
    }
}

QColor RayMarching::castRay(const QVector3D &origin, const QVector3D &direction, const QColor &bgColor, Camera *cam, QList<SceneObject *> *objects, LightSource *lightSource)
{
    qreal totalDist = 0.0f;
    qreal k = cam->getRadius() / cam->DEFAULT_RADIUS;
    qreal adjustedEPS = qMax(0.0001f, EPS * k);
    int adjustedSteps = MAX_STEPS + static_cast<int>(k / 50);
    qreal adjustedMaxDist = MAX_DIST * k;

    for (qsizetype step = 0; step < adjustedSteps; ++step)
    {
        QVector3D point = origin + direction * totalDist;
        qreal minDist = adjustedMaxDist;
        SceneObject *closestObj = nullptr;

        for (SceneObject *obj : *objects) {
            qreal dist = obj->SDF(point);
            if (dist < minDist) { minDist = dist; closestObj = obj; }
        }

        if (minDist < adjustedEPS) {
            if (closestObj) {
                QVector3D normal = this->normal(point, closestObj);
                return m_shading->shade(cam, normal, closestObj->getColor(), direction, lightSource);
            }
        }
        if (totalDist > adjustedMaxDist) break;
        totalDist += std::min(minDist * 0.8, (double)adjustedMaxDist);
    }
    return bgColor;
}


#include <QDebug>
QVector3D RayMarching::normal(const QVector3D &point, SceneObject *object) {
    qreal dx = object->SDF(point + QVector3D(EPS, 0, 0)) - object->SDF(point - QVector3D(EPS, 0, 0));
    qreal dy = object->SDF(point + QVector3D(0, EPS, 0)) - object->SDF(point - QVector3D(0, EPS, 0));
    qreal dz = object->SDF(point + QVector3D(0, 0, EPS)) - object->SDF(point - QVector3D(0, 0, EPS));
    return QVector3D(dx, dy, dz).normalized();
}


