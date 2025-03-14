#ifndef RENDERINGFACTORY_H
#define RENDERINGFACTORY_H

#include "renderertype.h"
#include "raymarching.h"
#include "concurrentraymarching.h"
#include "openglrenderer.h"
#include <QHash>

class RenderingFactory {
public:
    static RenderingAlgorithm *create(const Renderer::Type &type) {
        if (!cache.contains(type)) {
            RenderingAlgorithm *n;
            switch (type) {
            case Renderer::RAYMARCHER: n = new RayMarching(); break;
            case Renderer::CONCURRENT_RAYMARCHER: n = new ConcurrentRayMarching(); break;
            case Renderer::OPENGL: n = new OpenGLRenderer(); break;
            }
            cache[type] = n;
        }
        return cache[type];
    }
    static QHash<Renderer::Type, RenderingAlgorithm *> cache;
};



#endif // RENDERINGFACTORY_H
