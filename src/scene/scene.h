#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>
#include <QObject>
#include <QPixmap>
#include <QPaintEvent>
#include <QSurfaceFormat>
#include <QOpenGLContext>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QGraphicsSceneWheelEvent>
#include "lightsource.h"
#include "renderingalgorithm.h"

class Scene : public QGraphicsScene
{
    friend class SceneFactory;
public:
    explicit Scene(qsizetype w, qsizetype h,  RenderingAlgorithm *algo, QObject *parent = nullptr) :
        QGraphicsScene(parent), m_width(w), m_height(h), m_rendererPtr(algo)
    {
        m_imagePtr = new QImage(w, h, QImage::Format_RGB32);
        m_imagePtr->fill(Qt::green);
        // QSurfaceFormat format;
        // format.setProfile(QSurfaceFormat::CoreProfile);
        // format.setVersion(3, 3);

        // QOpenGLContext *context = new QOpenGLContext();
        // context->setFormat(format);
        // context->create();
        // context->makeCurrent(this);

    }

    Camera *getCamera() { return m_cameraPtr; }
    void setCamera(Camera *cam) { m_cameraPtr = cam; }

    RenderingAlgorithm *getRenderingAlgorithm() { return m_rendererPtr; }
    void setRenderingAlgorithm(RenderingAlgorithm *algorithm) { m_rendererPtr = algorithm; }

    ShadingAlgorithm *getShadingAlgorithm() { return m_rendererPtr->getShadingAlgorithm(); }
    void setShadingAlgorithm(ShadingAlgorithm *algorithm) { m_rendererPtr->setShadingAlgorithm(algorithm); }

    QImage *getImage() { return m_imagePtr; }
    void setImage(QImage *image) { m_imagePtr = image; }

    QColor getBGColor() { return m_bgColor; }
    void setBGColor(QColor color, bool shouldUpdate = true) { m_bgColor = color; if (shouldUpdate) update(); }

    LightSource *getLightSource() { return m_lightSource; }
    void setLightSource(LightSource *ls) { m_lightSource = ls; }

    SceneObject *firstObject() { if (m_objects.empty()) return nullptr; return m_objects.first(); }

    void update();

    void updateObjectColor(const QColor &color) {
        if (!m_objects.empty()) {
            for (const auto &obj : m_objects) {
                obj->setColor(color);
            }
        }

        update();
    }

    bool getCombineLightAndCamera() { return m_combineLightAndCamera; }
    void setCombineLightAndCamera(bool s) { m_combineLightAndCamera = s; }

    void addObject(SceneObject *obj){ m_objects.append(obj); update(); }
    void clear(bool shouldUpdate = true) { m_objects.clear(); if (shouldUpdate) update(); }
protected:
    explicit Scene(qsizetype w, qsizetype h) : QGraphicsScene(nullptr), m_width(w), m_height(h) {}

    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void wheelEvent(QGraphicsSceneWheelEvent *event) override;
    virtual void keyPressEvent(QKeyEvent *event) override;
    virtual void keyReleaseEvent(QKeyEvent *event) override;
    virtual void focusOutEvent(QFocusEvent *event) override;

    qsizetype m_width, m_height;
    QImage *m_imagePtr;
    RenderingAlgorithm *m_rendererPtr;
    QList<SceneObject *> m_objects;
    Camera *m_cameraPtr;
    LightSource *m_lightSource;

    void updateCamera();

private:
    bool m_isDragging = false;
    QPointF m_lastMousePosition;
    bool m_combineLightAndCamera = true;

    QColor m_bgColor;
    QSet<int> m_pressedKeys;
    qreal m_movementSpeed = 0.1f; // Скорость перемещения
    qreal m_rotationSpeed = 0.05f; // Скорость вращения
};

#endif // SCENE_H
