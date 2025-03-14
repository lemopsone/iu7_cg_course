#include "phongshading.h"

QColor PhongShading::shade(Camera *cam,
                           const QVector3D &normal,
                           const QColor &baseColor,
                           const QVector3D &hitPoint,
                           LightSource *lightSource)
{
    QVector3D cameraPos = cam->getPos();
    QVector3D ambientLight(0.1f, 0.1f, 0.1f);
    qreal ambientStrength = 0.1f;
    QVector3D lightDir = lightSource->getDirection(hitPoint);
    QVector3D viewDir = (cameraPos - hitPoint).normalized();
    qreal diffuseStrength = 0.7f;
    qreal specularStrength = 0.2f;
    qreal shininess = 32.0f;
    QVector3D ambient = ambientStrength * ambientLight;
    qreal diff = std::max(0.0f, QVector3D::dotProduct(normal, lightDir));
    QVector3D diffuse = diff * diffuseStrength * QVector3D(baseColor.redF(), baseColor.greenF(), baseColor.blueF());
    QVector3D reflectDir = 2 * QVector3D::dotProduct(normal, lightDir) * normal - lightDir;
    qreal spec = std::pow(std::max(0.0f, QVector3D::dotProduct(viewDir, reflectDir)), shininess);
    QVector3D specular = spec * specularStrength * QVector3D(1.0f, 1.0f, 1.0f);
    QVector3D result = (ambient + diffuse + specular) * lightSource->getIntensity();
    QColor color;
    color.setRedF(std::min(result.x(), 1.0f));
    color.setGreenF(std::min(result.y(), 1.0f));
    color.setBlueF(std::min(result.z(), 1.0f));

    return color;
}

