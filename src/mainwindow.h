#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "scene.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void setupMenu();
    Scene *m_scene1, *m_scene2, *m_scene3;
    Ui::MainWindow *ui;
    void animateCamera();
    void setupObjectList();
    void setupColors();
    void setupRenderList();
    void setupShadingList();
    void setupCameraList();
    void onObjectSelectionChanged(int index);
    void onShadingSelectionChanged(int index);
    void onRenderSelectionChanged(int index);
    void onCameraSelectionChanged(int index);
    void onIntensityChanged();
    void onBGColorChangeClicked();
    void onObjectColorChangeClicked();
    void setupSettingsLayouts();
    void onMandelbulbPowerChanged();
    void onMandelbulbItersChanged();
    void onMandelbulbRadChanged();
    void setAdditionalParameters(SceneObject *obj);
    void setupLightingSettings();
    void onCheckBoxClicked(bool active);
    void onChangeLightPosClicked();
    void onSphereRadiusChanged();
    void onCubeSideChanged();
    QMap<Object::Type, QWidget *> settingsWidgets;
};
#endif // MAINWINDOW_H
