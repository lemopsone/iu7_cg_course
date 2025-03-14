#ifndef SHADINGTYPE_H
#define SHADINGTYPE_H

#include <QString>
namespace Shading {
enum Type {
    SIMPLE,
    PHONG,
    GOURAUD
};

const Type allTypes[] = { SIMPLE, PHONG, GOURAUD };

inline QString typeToString(const Type &type) {
    switch (type) {
    case SIMPLE: return "Простое затенение";
    case PHONG: return "Затенение по Фонгу";
    case GOURAUD: return "Затенение по Гуро";
    }
}

}

#endif // SHADINGTYPE_H
