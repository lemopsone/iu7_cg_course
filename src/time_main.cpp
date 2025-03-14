#include <QString>
#include "scenefactory.h"
#include "mandelbulb.h"
#include <QElapsedTimer>
#include <iostream>
#include <QDebug>
#include <QApplication>
#include <QOpenGLWidget>
#include <QWindow>
#include "objectfactory.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Q_UNUSED(argc);
    QString sizeStr = argv[1];
    QString itersStr = argv[2];
    QString algoStr = argv[3];
    const int SIZE = sizeStr.toInt();
    const int ITERS = itersStr.toInt();

    QWindow window;
    window.setSurfaceType(QWindow::OpenGLSurface);
    auto format = QSurfaceFormat();
    format.setVersion(4, 1);
    format.setProfile(QSurfaceFormat::CoreProfile);
    window.setFormat(format);
    window.create();
    QOpenGLContext context;
    context.setFormat(format);
    if (!context.create()) {
        qFatal("Failed to create OpenGL context");
        return -1;
    }

    // Привязываем контекст к окну
    if (!context.makeCurrent(&window)) {
        qFatal("Failed to make context current");
        return -1;
    }

    Renderer::Type type;
    if (algoStr == "single")
    {
        type = Renderer::RAYMARCHER;
    }
    else if (algoStr == "concurrent")
    {
        type = Renderer::CONCURRENT_RAYMARCHER;
    }
    else
    {
        type = Renderer::OPENGL;
    }
    auto scene = SceneFactory::create(SIZE, SIZE, type);
    auto mandelbulb = dynamic_cast<Mandelbulb *>(ObjectFactory::create(Object::MANDELBULB));
    mandelbulb->setIters(ITERS);
    mandelbulb->setRad(3);
    scene->addObject(mandelbulb);
    QElapsedTimer timer;
    timer.start();
    scene->update();
    std::cout << timer.nsecsElapsed() << std::endl;

    return 0;
}
