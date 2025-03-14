#ifndef RAYMARCHING_H
#define RAYMARCHING_H

#include "renderingalgorithm.h"

#define MAX_STEPS 200
#define MAX_DIST 10.0f
#define EPS 0.0015f

class RayMarching : public RenderingAlgorithm
{
    friend class RenderingFactory;
public:
    virtual void render(QImage *img, const QColor &bgColor, Camera *cam, QList<SceneObject *> *objects, LightSource *lightSource) override;
    virtual Renderer::Type getType() override { return Renderer::RAYMARCHER; }

    QColor castRay(	const QVector3D &origin, const QVector3D &direction,
                    const QColor &bgColor,
                    Camera *cam, QList<SceneObject *> *objects, LightSource *lightSource);

    QVector3D normal(const QVector3D &point, SceneObject *obj);
protected:
    RayMarching(ShadingAlgorithm *algo) : RenderingAlgorithm(algo) {}
    RayMarching() : RenderingAlgorithm() {}
    qreal adjustedEPS;
};

#endif // RAYMARCHING_H
