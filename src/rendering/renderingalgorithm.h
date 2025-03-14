#ifndef RENDERINGALGORITHM_H
#define RENDERINGALGORITHM_H

#include <QImage>
#include "sceneobject.h"
#include "shadingalgorithm.h"
#include "renderertype.h"

class RenderingAlgorithm
{
    friend class RenderingFactory;
public:
    ShadingAlgorithm *getShadingAlgorithm() { return m_shading; }
    void setShadingAlgorithm(ShadingAlgorithm *algo) { m_shading = algo; }

    virtual Renderer::Type getType() = 0;

    virtual void render(QImage *img, const QColor &bgColor, Camera *cam, QList<SceneObject *> *objects, LightSource *lightSource) = 0;
protected:
    RenderingAlgorithm(ShadingAlgorithm *algo) : m_shading(algo) {}
    RenderingAlgorithm() {}

    ShadingAlgorithm *m_shading;
};

#endif // RENDERINGALGORITHM_H
