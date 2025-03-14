include(phong/phong.pri)
include(gouraud/gouraud.pri)
include(simple/simpleshading.pri)

HEADERS += \
  $$PWD/shadingalgorithm.h \
  $$PWD/shadingfactory.h \
  $$PWD/shadingtype.h

INCLUDEPATH += $$PWD
