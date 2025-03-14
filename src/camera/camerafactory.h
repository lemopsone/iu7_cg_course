#ifndef CAMERAFACTORY_H
#define CAMERAFACTORY_H

#include "freecamera.h"
#include "spherecamera.h"
#include "camera.h"

class CameraFactory
{
public:
    static Camera *create(const Cam::Type &type)
    {
        switch (type)
        {
        case Cam::SPHERE:
            return new SphereCamera();
        case Cam::FREE:
            return new FreeCamera();
        }
    }
};

#endif // CAMERAFACTORY_H
