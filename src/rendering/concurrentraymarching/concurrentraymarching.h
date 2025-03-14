#ifndef CONCURRENTRAYMARCHING_H
#define CONCURRENTRAYMARCHING_H

#include <QtConcurrent/QtConcurrent>
#include <QMutex>

#include "raymarching.h"

class ConcurrentRayMarching : public RayMarching
{
    friend class RenderingFactory;
public:
    virtual void render(QImage *img, const QColor &bgColor, Camera *cam, QList<SceneObject *> *objects, LightSource *lightSource) override;
    virtual Renderer::Type getType() override { return Renderer::CONCURRENT_RAYMARCHER; }
protected:
    ConcurrentRayMarching(ShadingAlgorithm *algo) : RayMarching(algo) {}
    ConcurrentRayMarching() : RayMarching() {}
};

#endif // CONCURRENTRAYMARCHING_H
