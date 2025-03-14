#ifndef SCENEFACTORY_H
#define SCENEFACTORY_H

#include "scene.h"
#include "renderingfactory.h"
#include "camerafactory.h"
#include "shadingfactory.h"

#include <QDebug>
class SceneFactory
{
public:
    static Scene *create(qsizetype w, qsizetype h, Renderer::Type &type)
    {
        Scene *scene = new Scene(w, h);
        Camera *camera = CameraFactory::create(Cam::SPHERE);

        ShadingAlgorithm *shading = ShadingFactory::create(Shading::PHONG);

        RenderingAlgorithm *renderer = RenderingFactory::create(type);

        QImage *image = new QImage(w, h, QImage::Format_RGB32);

        LightSource *src = new LightSource();

        scene->setCamera(camera);
        scene->setLightSource(src);
        renderer->setShadingAlgorithm(shading);
        scene->setRenderingAlgorithm(renderer);
        scene->setImage(image);
        scene->setBGColor(Qt::gray, false);

        return scene;
    }

    static Scene *create(qsizetype w, qsizetype h)
    {
        Scene *scene = new Scene(w, h);
        Camera *camera = CameraFactory::create(Cam::SPHERE);

        ShadingAlgorithm *shading = ShadingFactory::create(Shading::GOURAUD);

        RenderingAlgorithm *renderer = RenderingFactory::create(Renderer::CONCURRENT_RAYMARCHER);

        QImage *image = new QImage(w, h, QImage::Format_RGB32);

        LightSource *src = new LightSource();

        scene->setCamera(camera);
        scene->setLightSource(src);
        renderer->setShadingAlgorithm(shading);
        scene->setRenderingAlgorithm(renderer);
        scene->setImage(image);
        scene->setBGColor(Qt::gray, false);

        return scene;
    }
};

#endif // SCENEFACTORY_H
