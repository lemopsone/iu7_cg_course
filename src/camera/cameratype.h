#ifndef CAMERATYPE_H
#define CAMERATYPE_H

#include <QString>

namespace Cam
{
enum Type
{
    SPHERE,
    FREE
};

const Type allTypes[] = { SPHERE, FREE };
inline QString typeToString(const Type &type) {
    switch (type) {
    case SPHERE: return "Вращение вокруг объекта";
    case FREE: return "Свободное перемещение";
    }
}
}

#endif // CAMERATYPE_H
