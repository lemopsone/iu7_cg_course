#ifndef SHADERMANAGER_H
#define SHADERMANAGER_H

#include <QOpenGLShaderProgram>
#include <QFile>
#include <QTextStream>
#include <QDebug>

class ShaderManager {
public:
    ShaderManager() {
        program = new QOpenGLShaderProgram();
    }

    ~ShaderManager() {
        delete program;
    }

    void loadSDFShader(const QString &sdfShaderPath) {
        // Загрузка SDF-функции
        QString sdfCode = loadShaderCode(sdfShaderPath);
        if (sdfCode.isEmpty()) {
            qWarning() << "Failed to load SDF shader code!";
            return;
        }

        // Общий фрагментный шейдер
        QString fragmentShaderCode = loadShaderCode(":/fragment.glsl");
        if (fragmentShaderCode.isEmpty()) {
            qWarning() << "Failed to load fragment shader!";
            return;
        }

        // Подстановка SDF-функции
        fragmentShaderCode.replace("float sdf(vec3 p);", sdfCode);

        // Компиляция шейдеров
        program->addShaderFromSourceCode(QOpenGLShader::Vertex, loadShaderCode(":/vertex.glsl"));
        program->addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShaderCode);
        program->link();
    }

    QOpenGLShaderProgram *getProgram() { return program; }

    void useProgram() {
        program->bind();
    }

private:
    QOpenGLShaderProgram *program;

    QString loadShaderCode(const QString &filePath) {
        QFile file(filePath);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            qWarning() << "Could not open file:" << filePath;
            return "";
        }
        QTextStream in(&file);
        return in.readAll();
    }
};


#endif // SHADERMANAGER_H
