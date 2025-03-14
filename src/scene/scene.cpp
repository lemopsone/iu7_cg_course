#include "scene.h"

void Scene::update()
{
    if (m_combineLightAndCamera)
    {
        auto cameraPos = m_cameraPtr->getPos();
        auto lightPos = -cameraPos;// + up * dist / 2 + forwardDir * dist / 2;
        m_lightSource->setPosition(lightPos);
    }
    m_rendererPtr->render(m_imagePtr, m_bgColor, m_cameraPtr, &m_objects, m_lightSource);
    addPixmap(QPixmap::fromImage(*m_imagePtr));
}

#include <QDebug>
void Scene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        m_isDragging = true;
        m_lastMousePosition = event->scenePos();
    }
}

void Scene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (m_isDragging) {
        QPointF currentPos = event->scenePos();
        QPointF delta = currentPos - m_lastMousePosition;

        qreal dTheta = M_PI * delta.x() / m_imagePtr->width();
        qreal dPhi = -M_PI * delta.y() / m_imagePtr->height();

        m_cameraPtr->rotate(dTheta, dPhi);

        m_lastMousePosition = currentPos; // Обновляем последнюю позицию мыши
        update();
    }
}

void Scene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        m_isDragging = false;
    }
}

void Scene::wheelEvent(QGraphicsSceneWheelEvent *event)
{
    if (qAbs(event->delta()) < 10) return;
    qreal zoomFactor;
    if (event->delta() > 0) {
        zoomFactor = 0.1;
    } else if (event->delta() < 0) {
        zoomFactor = -0.1;
    } else {
        zoomFactor = 0.0;
    }
    m_cameraPtr->zoom(zoomFactor);
    update();
}

void Scene::keyPressEvent(QKeyEvent *event)
{
    m_pressedKeys.insert(event->key());
    updateCamera();
}

void Scene::keyReleaseEvent(QKeyEvent *event)
{
    m_pressedKeys.remove(event->key());
}

void Scene::focusOutEvent(QFocusEvent *event)
{
    Q_UNUSED(event);
    m_pressedKeys.clear(); // Сбросить состояние клавиш при потере фокуса
}

void Scene::updateCamera()
{
    QVector3D forward = m_cameraPtr->getForward();
    QVector3D right = QVector3D::crossProduct(forward, m_cameraPtr->getUp()).normalized();

    // Перемещение
    if (m_pressedKeys.contains(Qt::Key_W))
        m_cameraPtr->move(forward * m_movementSpeed);
    if (m_pressedKeys.contains(Qt::Key_S))
        m_cameraPtr->move(-forward * m_movementSpeed);
    if (m_pressedKeys.contains(Qt::Key_A))
        m_cameraPtr->move(-right * m_movementSpeed);
    if (m_pressedKeys.contains(Qt::Key_D))
        m_cameraPtr->move(right * m_movementSpeed);

    // Вращение
    if (m_pressedKeys.contains(Qt::Key_Up))
        m_cameraPtr->rotate(0, -m_rotationSpeed);
    if (m_pressedKeys.contains(Qt::Key_Down))
        m_cameraPtr->rotate(0, m_rotationSpeed);
    if (m_pressedKeys.contains(Qt::Key_Left))
        m_cameraPtr->rotate(-m_rotationSpeed, 0);
    if (m_pressedKeys.contains(Qt::Key_Right))
        m_cameraPtr->rotate(m_rotationSpeed, 0);

    update(); // Перерисовка сцены
}
