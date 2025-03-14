#include "gouraudshading.h"

QColor GouraudShading::shade(Camera *cam,
                             const QVector3D &normal,
                             const QColor &baseColor,
                             const QVector3D &hitPoint,
                             LightSource *lightSource)
{
    QVector3D cameraPos = cam->getPos();

    // Ambient light
    QVector3D ambientLight(0.1f, 0.1f, 0.1f);  // Color of ambient light
    qreal ambientStrength = 0.1f;  // Ambient light strength

    // Light source position
    QVector3D lightDir = lightSource->getDirection(hitPoint);

    // Lighting strengths
    qreal diffuseStrength = 0.6f;  // Diffuse lighting strength
    qreal specularStrength = 0.2f;  // Specular lighting strength
    qreal shininess = 32.0f;  // Shininess parameter for specular reflection

    // 1. Calculate the components of lighting

    // Ambient lighting (doesn't depend on position)
    QVector3D ambient = ambientStrength * ambientLight;

    // Diffuse lighting (depends on angle between normal and light direction)
    qreal diff = std::max(0.0f, QVector3D::dotProduct(normal, lightDir));
    QVector3D diffuse = diff * diffuseStrength * QVector3D(baseColor.redF(), baseColor.greenF(), baseColor.blueF());

    // Specular lighting (depends on angle between reflected light and view direction)
    QVector3D reflectDir = 2 * QVector3D::dotProduct(normal, lightDir) * normal - lightDir;
    QVector3D viewDir = (cameraPos - hitPoint).normalized();
    qreal spec = std::pow(std::max(0.0f, QVector3D::dotProduct(viewDir, reflectDir)), shininess);
    QVector3D specular = spec * specularStrength * QVector3D(1.0f, 1.0f, 1.0f);  // White for specular highlights

    // 2. Combine lighting components
    QVector3D result = (ambient + diffuse + specular) * lightSource->getIntensity();

    // 3. Ensure the final color doesn't exceed a value of 1
    // result = result.normalized();

    // 4. Return final color
    QColor color;
    color.setRedF(std::min(result.x(), 1.0f));
    color.setGreenF(std::min(result.y(), 1.0f));
    color.setBlueF(std::min(result.z(), 1.0f));

    return color;
}
