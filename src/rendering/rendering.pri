include(raymarching/raymarching.pri)
include(concurrentraymarching/concurrentraymarching.pri)
include(shaderraymarching/shaderraymarching.pri)
include(openglrenderer/openglrenderer.pri)

HEADERS += \
  $$PWD/renderertype.h \
  $$PWD/renderingalgorithm.h \
  $$PWD/renderingfactory.h

INCLUDEPATH += $$PWD

SOURCES += \
    $$PWD/renderingfactory.cpp
