include(mandelbulb/mandelbulb.pri)
include(sphere/sphere.pri)
include(cube/cube.pri)
include(mandelbox/mandelbox.pri)

HEADERS += \
  $$PWD/objectfactory.h \
  $$PWD/sceneobject.h \
  $$PWD/sceneobjecttype.h

INCLUDEPATH += $$PWD
