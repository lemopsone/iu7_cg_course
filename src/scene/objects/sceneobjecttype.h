#ifndef SCENEOBJECTTYPE_H
#define SCENEOBJECTTYPE_H

#include <QString>

namespace Object {
enum Type {
    MANDELBULB,
    JULIA,
    SPHERE,
    CUBE,
    MANDELBOX
};

const Type allTypes[] = { MANDELBULB, SPHERE, CUBE, MANDELBOX };

inline QString typeToString(const Type &type) {
    switch(type) {
    case MANDELBULB: return "Оболочка Мандельброта";
    case MANDELBOX: return "Mandelbox";
    case JULIA: return "Множество Джулия";
    case SPHERE: return "Сфера";
    case CUBE: return "Куб";
    }
}
}

#endif // SCENEOBJECTTYPE_H
