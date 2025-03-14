#ifndef OPENGLRENDERER_H
#define OPENGLRENDERER_H
#include "mandelbulb.h"
#include "sphere.h"
#include "cube.h"

#include "renderingalgorithm.h"
#include "shadermanager.h"
#include <QOpenGLContext>
#include <QOpenGLBuffer>
#include <QOffscreenSurface>
#include <QOpenGLFramebufferObject>
#include <QOpenGLFunctions>
#include <QOpenGLFunctions_4_1_Compatibility>
#include <QOpenGLShader>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>

class OpenGLRenderer : public RenderingAlgorithm
{
    constexpr static const GLfloat vertices[] = {
        -1.0f,  1.0f,  1.0f,  1.0f,  1.0f, -1.0f,
        1.0f,  -1.0f, -1.0f, -1.0f, -1.0f,  1.0f
    };
public:
    OpenGLRenderer() : RenderingAlgorithm() {
           }

    virtual Renderer::Type getType() { return Renderer::OPENGL; }

    virtual void render(QImage *img, const QColor &bgColor, Camera *cam, QList<SceneObject *> *objects, LightSource *lightSource)
    {
        ctx = QOpenGLContext::currentContext();
        // qDebug() << "render start";

        setManager(objects->first());

        drawToImage(img, bgColor, cam, objects, lightSource);
        // qDebug() << "done render";
    }

private:
    QOpenGLContext *ctx;
    QHash<Object::Type, ShaderManager *> cache;
    ShaderManager *currentManager = nullptr;

    void setManager(SceneObject *obj)
    {
        if (!cache.contains(obj->getType()))
        {
            QString sdfShaderPath = getSDFShaderPath(obj->getType());
            ShaderManager *m = new ShaderManager();
            m->loadSDFShader(sdfShaderPath);
            cache[obj->getType()] = m;
        }
        currentManager = cache[obj->getType()];
    }

    QString getSDFShaderPath(const Object::Type &type)
    {
        switch (type) {
        case Object::SPHERE:
            return ":/sphere_sdf.glsl";
        case Object::MANDELBULB:
            return ":/mandelbulb_sdf.glsl";
        case Object::CUBE:
            return ":/cube_sdf.glsl";
        case Object::MANDELBOX:
            return ":/mandelbox_sdf.glsl";
        default:
            return ":/default_sdf.glsl";
        }
    }

    void drawToImage(QImage *img, const QColor &bgColor, Camera *cam, QList<SceneObject *> *objects, LightSource *lightSource)
    {
        QSize vpSize = img->size();
        auto functions = ctx->functions();
        QOpenGLFramebufferObjectFormat fboFormat;
        fboFormat.setAttachment(QOpenGLFramebufferObject::CombinedDepthStencil);
        QOpenGLFramebufferObject fbo(vpSize, fboFormat);
        functions->glViewport(0,0,vpSize.width(), vpSize.height());
        fbo.bind();

        QOpenGLBuffer vertexPositionBuffer(QOpenGLBuffer::VertexBuffer);
        vertexPositionBuffer.create();
        vertexPositionBuffer.setUsagePattern(QOpenGLBuffer::StaticDraw);
        vertexPositionBuffer.bind();
        vertexPositionBuffer.allocate(vertices, 12 * sizeof(GLfloat));

        auto program = currentManager->getProgram();
        program->bind();

        QOpenGLVertexArrayObject vao;
        vao.create();
        vao.bind();

        vertexPositionBuffer.bind();
        program->enableAttributeArray("pos");
        program->setAttributeBuffer("pos", GL_FLOAT, 0, 2, 0);

        // GLint cameraLocation = program->uniformLocation("cameraPos");
        auto objClr = objects->first()->getColor();
        QVector3D objColor = {objClr.redF(), objClr.greenF(), objClr.blueF()};
        // qDebug() << "camera pos: " << cameraLocation;

        program->setUniformValue("cameraPos", cam->getPos());
        program->setUniformValue("cameraTargetPos", cam->getTargetPos());
        program->setUniformValue("lightPos", lightSource->getPosition());
        program->setUniformValue("lightColor", QVector3D(0.1, 0.1, 0.1));
        program->setUniformValue("objectColor", objColor);
        program->setUniformValue("bgColor", QVector3D(bgColor.redF(), bgColor.greenF(), bgColor.blueF()));
        program->setUniformValue("cameraUp", cam->getUp());
        program->setUniformValue("fov", (float)cam->getFOV());
        program->setUniformValue("resolution", img->size());
        program->setUniformValue("intensity", (float)lightSource->getIntensity());


        Mandelbulb *bulb = dynamic_cast<Mandelbulb *>(objects->first());
        if (bulb)
        {
            program->setUniformValue("power", (float)bulb->getPower());
            program->setUniformValue("iters", (int)bulb->getIters());
            program->setUniformValue("rad", (float)bulb->getRad());
        }

        Sphere *sphere = dynamic_cast<Sphere *>(objects->first());
        if (sphere)
        {
            program->setUniformValue("radius", (float)sphere->getRadius());
        }

        Cube *cube = dynamic_cast<Cube *>(objects->first());
        if (cube)
        {
            program->setUniformValue("side", (float)cube->getSide());
        }

        functions->glClearColor(0.3f, 0.0f, 0.7f, 1.0f);
        GLenum err = glGetError();
        if (err != GL_NO_ERROR) {
            qDebug() << "OpenGL Error 1: " << err;
        }
        functions->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        err = glGetError();
        if (err != GL_NO_ERROR) {
            qDebug() << "OpenGL Error 2: " << err;
        }
        functions->glDrawArrays(GL_TRIANGLES, 0, 6);
        err = glGetError();
        if (err != GL_NO_ERROR) {
            qDebug() << "OpenGL Error 3: " << err;
        }

        program->release();
        fbo.release();


        QImage im = fbo.toImage();
        *img = im;
    }
};

#endif // OPENGLRENDERER_H
