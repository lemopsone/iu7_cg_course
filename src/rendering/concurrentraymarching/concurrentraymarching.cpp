#include "concurrentraymarching.h"

void ConcurrentRayMarching::render(QImage *img, const QColor &bgColor, Camera *cam, QList<SceneObject *> *objects, LightSource *lightSource)
{
    const qsizetype width = img->width();
    const qsizetype height = img->height();
    const QVector3D origin = cam->getPos();

    QMutex mutex;

    QImage resultImage(img->size(), img->format());

    auto renderLine = [&](qsizetype y) {
        for (qsizetype x = 0; x < width; ++x)
        {
            QVector3D rayDirection = cam->calculateRayDirection(x, y, width, height);
            QColor pixelColor = castRay(origin, rayDirection, bgColor, cam, objects, lightSource);

            QMutexLocker locker(&mutex);
            resultImage.setPixelColor(x, y, pixelColor);
        }
    };

    QList<qsizetype> rows;
    for (qsizetype y = 0; y < height; ++y)
        rows.append(y);

    QtConcurrent::blockingMap(rows, renderLine);

    *img = resultImage;
}
