QT       += core gui concurrent opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets openglwidgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
QMAKE_LFLAGS += -L/opt/homebrew/opt/icu4c@76/lib
QMAKE_CXXFLAGS += -I/opt/homebrew/opt/icu4c@76/include

include(scene/scene.pri)
include(camera/camera.pri)
include(shading/shading.pri)
include(rendering/rendering.pri)
include(lighting/lighting.pri)

contains(CONFIG, measure) {
  SOURCES += time_main.cpp
} else {
    SOURCES += \
        main.cpp \

    # DEFINES += QT_NO_DEBUG_OUTPUT

}

SOURCES += \
        mainwindow.cpp \

    HEADERS += \
        mainwindow.h \

    FORMS += \
        mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
