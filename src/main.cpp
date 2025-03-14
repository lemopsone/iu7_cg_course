#include "mainwindow.h"

#include <QApplication>
#include <QOpenGLBuffer>
#include <QOffscreenSurface>
#include <QOpenGLFramebufferObject>
#include <QOpenGLFunctions>
#include <QOpenGLFunctions_4_1_Compatibility>
#include <QOpenGLShader>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    QSurfaceFormat surfaceFormat;
    surfaceFormat.setVersion(4, 1);
    surfaceFormat.setProfile(QSurfaceFormat::CoreProfile);
    QSurfaceFormat::setDefaultFormat(surfaceFormat);

    QOffscreenSurface surface;
    surface.setFormat(surfaceFormat);
    surface.create();
    if(!surface.isValid()) qDebug("Unable to create the Offscreen surface");

    auto ctx = new QOpenGLContext();
    ctx->setFormat(surfaceFormat);
    qDebug() << "ctx created: " << ctx->create();
    if(!ctx->isValid()) qDebug("Unable to create context");

    qDebug() << "ctx made current: " << ctx->makeCurrent(&surface);



    // QOpenGLShaderProgram program;
    // program.addShaderFromSourceCode(QOpenGLShader::Vertex,
    //                                 "#version 330 core\r\n"
    //                                 "in vec2 position;\n"
    //                                 "out vec3 fragColor;\n"
    //                                 "void main() {\n"
    //                                 "    fragColor = vec3(position.x, position.y, position.y);\n"
    //                                 "    gl_Position = vec4(position, 0.0, 1.0);\n"
    //                                 "}\n"
    //                                 );
    // program.addShaderFromSourceCode(QOpenGLShader::Fragment,
    //                                 "#version 330 core\r\n"
    //                                 "in vec3 fragColor;\n"
    //                                 "out vec4 color;\n"
    //                                 "void main() {\n"
    //                                 "    color = vec4(fragColor, 1.0);\n"
    //                                 "}\n"
    //                                 );
    return a.exec();
}
