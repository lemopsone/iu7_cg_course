#include "shaderraymarching.h"
#include <QOpenGLTexture>

ShaderRayMarching::ShaderRayMarching() : RayMarching()
{
    initializeOpenGLFunctions();
    initializeShaderProgram();
}

ShaderRayMarching::~ShaderRayMarching()
{
    delete m_shaderProgram;
    glDeleteFramebuffers(1, &m_frameBuffer);
    glDeleteTextures(1, &m_texture);
}

void ShaderRayMarching::initializeShaderProgram()
{
    m_shaderProgram = new QOpenGLShaderProgram();

    // Загрузите и компилируйте шейдеры
    m_shaderProgram->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/vertex_shader.glsl");
    m_shaderProgram->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/fragment_shader.glsl");
    if (!m_shaderProgram->link()) {
        qCritical() << "Shader linking failed:" << m_shaderProgram->log();
    }
}

void ShaderRayMarching::setupFrameBuffer(QImage *img)
{
    // Создаем текстуру для хранения результата рендеринга
    glGenTextures(1, &m_texture);
    glBindTexture(GL_TEXTURE_2D, m_texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, img->width(), img->height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Создаем фреймбуфер и привязываем текстуру
    glGenFramebuffers(1, &m_frameBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, m_frameBuffer);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_texture, 0);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        qCritical() << "Frame buffer is not complete!";
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void ShaderRayMarching::render(QImage *img, const QColor &bgColor, Camera *cam, QList<SceneObject *> *objects, LightSource *lightSource)
{
    setupFrameBuffer(img);
    glBindFramebuffer(GL_FRAMEBUFFER, m_frameBuffer);

    glViewport(0, 0, img->width(), img->height());
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_shaderProgram->bind();

    // Передача данных в шейдер
    transferDataToShader(cam, objects);

    // Отрисовка полноэкранного прямоугольника
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    m_shaderProgram->release();

    // Копируем результат в QImage
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glBindTexture(GL_TEXTURE_2D, m_texture);
    glGetTexImage(GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE, img->bits());
}

void ShaderRayMarching::transferDataToShader(Camera *cam, QList<SceneObject *> *objects)
{
    // Передача параметров камеры
    QVector3D cameraPos = cam->getPos();
    m_shaderProgram->setUniformValue("cameraPos", cameraPos);
    m_shaderProgram->setUniformValue("fov", (int)cam->getFOV());

    // Передача объектов сцены
    for (int i = 0; i < objects->size(); ++i) {
        SceneObject *obj = objects->at(i);
        // Передавайте данные объектов в виде массивов (зависит от вашей реализации)
        // Например: позиции, размеры, цвета объектов
    }
}
