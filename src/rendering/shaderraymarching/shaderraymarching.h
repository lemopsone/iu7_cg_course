#ifndef SHADERBASEDRAYMARCHING_H
#define SHADERBASEDRAYMARCHING_H

#include "raymarching.h"
#include <QOpenGLShaderProgram>
#include <QOpenGLFunctions>

class ShaderRayMarching : public RayMarching, protected QOpenGLFunctions
{
public:
    ~ShaderRayMarching();
    void render(QImage *img, const QColor &bgColor, Camera *cam, QList<SceneObject *> *objects, LightSource *lightSource) override;


protected:
    ShaderRayMarching();
private:
    void initializeShaderProgram();
    void setupFrameBuffer(QImage *img);
    void transferDataToShader(Camera *cam, QList<SceneObject *> *objects);

    QOpenGLShaderProgram *m_shaderProgram = nullptr;
    GLuint m_frameBuffer = 0;
    GLuint m_texture = 0;
};

#endif // SHADERBASEDRAYMARCHING_H
