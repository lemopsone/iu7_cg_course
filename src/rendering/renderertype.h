#ifndef RENDERERTYPE_H
#define RENDERERTYPE_H

#include <QString>

namespace Renderer {
enum Type {
    RAYMARCHER,
    CONCURRENT_RAYMARCHER,
    OPENGL,
};

const Type allTypes[] = { RAYMARCHER, CONCURRENT_RAYMARCHER, OPENGL };

inline QString typeToString(const Type &type) {
    switch (type) {
    case RAYMARCHER: return "Марширование лучей (однопоточное)";
    case CONCURRENT_RAYMARCHER: return "Марширование лучей (многопоточное)";
    case OPENGL: return "Марширование лучей (OpenGL)";
    }
}
}

#endif // RENDERERTYPE_H
