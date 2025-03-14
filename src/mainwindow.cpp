#include "mainwindow.h"
#include <QObject>
#include <QStandardItemModel>
#include "camerafactory.h"
#include "ui_mainwindow.h"
#include "scenefactory.h"
#include "objectfactory.h"
// #include "gradientrenderer.h"

#include <QColorDialog>
#include <QTimer>
#include <QRandomGenerator>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    m_scene1 = SceneFactory::create(800, 800);
    ui->setupUi(this);

    // // m_scene1 = new Scene(600, 600, new ConcurrentRayMarching(new GouraudShading()));
    ui->graphicsView->setScene(m_scene1);


    m_scene1->addObject(ObjectFactory::create(Object::MANDELBULB));
    ui->graphicsView->show();

    setupMenu();
}

void MainWindow::animateCamera() {
    qreal degree = qDegreesToRadians(2);

    m_scene1->getCamera()->rotate(degree, 0);

    m_scene1->update();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupMenu()
{
    setupObjectList();
    setupRenderList();
    setupShadingList();
    setupCameraList();
    setupLightingSettings();
    setupSettingsLayouts();
    setupColors();
}

void MainWindow::setupSettingsLayouts()
{
    connect(ui->mandelbulbPowerLE, &QLineEdit::editingFinished, this, &MainWindow::onMandelbulbPowerChanged);
    connect(ui->mandelbulbItersLE, &QLineEdit::editingFinished, this, &MainWindow::onMandelbulbItersChanged);
    connect(ui->mandelbulbRadLE, &QLineEdit::editingFinished, this, &MainWindow::onMandelbulbRadChanged);
    connect(ui->sphereRadiusLE, &QLineEdit::editingFinished, this, &MainWindow::onSphereRadiusChanged);
    connect(ui->cubeSideLE, &QLineEdit::editingFinished, this, &MainWindow::onCubeSideChanged);
}

#include <QDebug>
void MainWindow::onMandelbulbItersChanged()
{
    QString s = ui->mandelbulbItersLE->text();
    qDebug() << s;
    Mandelbulb *m = dynamic_cast<Mandelbulb *>(m_scene1->firstObject());
    Q_ASSERT(m != nullptr);
    bool isNum;
    qsizetype iters = s.toInt(&isNum);
    if (isNum && iters <= 1000 && iters > 0) m->setIters(iters);
    else ui->mandelbulbItersLE->setText(QString::number(m->getIters()));
    m_scene1->update();
}

void MainWindow::onMandelbulbRadChanged()
{
    QString s = ui->mandelbulbRadLE->text();
    qDebug() << s;
    Mandelbulb *m = dynamic_cast<Mandelbulb *>(m_scene1->firstObject());
    Q_ASSERT(m != nullptr);
    bool isNum;
    qreal rad = s.toDouble(&isNum);
    if (isNum && rad < 5 && rad > 0) m->setRad(rad);
    else ui->mandelbulbRadLE->setText(QString::number(m->getRad()));
    m_scene1->update();
}

void MainWindow::setAdditionalParameters(SceneObject *obj)
{
    if (obj->getType() == Object::MANDELBULB)
    {
        auto *m = dynamic_cast<Mandelbulb *>(obj);
        m->setIters(ui->mandelbulbItersLE->text().toInt());
        m->setPower(ui->mandelbulbPowerLE->text().toDouble());
        m->setRad(ui->mandelbulbRadLE->text().toDouble());
    }
}

void MainWindow::setupLightingSettings()
{
    connect(ui->lightCamCheckBox, &QCheckBox::clicked, this, &MainWindow::onCheckBoxClicked);
    connect(ui->changeLightPosButton, &QPushButton::clicked, this, &MainWindow::onChangeLightPosClicked);
    connect(ui->intensityLineEdit, &QLineEdit::editingFinished, this, &MainWindow::onIntensityChanged);
}

void MainWindow::onCheckBoxClicked(bool active)
{
    bool editsActive = !active;
    m_scene1->setCombineLightAndCamera(active);
    ui->lightXEdit->setEnabled(editsActive);
    ui->lightYEdit->setEnabled(editsActive);
    ui->lightZEdit->setEnabled(editsActive);
    ui->changeLightPosButton->setEnabled(editsActive);
    m_scene1->update();
}

void MainWindow::onChangeLightPosClicked()
{
    bool xOk, yOk, zOk;
    double x, y, z;
    x = ui->lightXEdit->text().toDouble(&xOk);
    y = ui->lightYEdit->text().toDouble(&yOk);
    z = ui->lightZEdit->text().toDouble(&zOk);

    if ((xOk * yOk * zOk != 1) ||
        (qAbs(x) > 4 || qAbs(y) > 4 || qAbs(z) > 4))
    {
        QVector3D current = m_scene1->getLightSource()->getPosition();
        ui->lightXEdit->setText(QString::number(current.x(), 'g', 1));
        ui->lightXEdit->setText(QString::number(current.y(), 'g', 1));
        ui->lightXEdit->setText(QString::number(current.z(), 'g', 1));
    }
    else
    {
        QVector3D n(x, y, z);
        m_scene1->getLightSource()->setPosition(n);
    }
    m_scene1->update();
}

void MainWindow::onSphereRadiusChanged()
{
    QString text = ui->sphereRadiusLE->text();
    Sphere *s = dynamic_cast<Sphere *>(m_scene1->firstObject());
    bool ok;
    qreal rad = text.toDouble(&ok);
    if (!ok || rad < 0.1 || rad > 1.5)
    {
        ui->sphereRadiusLE->setText(QString::number(s->getRadius(), 'g', 1));
    }
    else
    {
        s->setRadius(rad);
        m_scene1->update();
    }
}

void MainWindow::onCubeSideChanged()
{
    QString text = ui->cubeSideLE->text();
    Cube *c = dynamic_cast<Cube *>(m_scene1->firstObject());
    bool ok;
    qreal side = text.toDouble(&ok);
    if (!ok || side< 0.1 || side > 2.5)
    {
        ui->cubeSideLE->setText(QString::number(c->getSide(), 'g', 1));
    }
    else
    {
        c->setSide(side);
        m_scene1->update();
    }
}

void MainWindow::onMandelbulbPowerChanged()
{
    QString s = ui->mandelbulbPowerLE->text();
    qDebug() << s;
    Mandelbulb *m = dynamic_cast<Mandelbulb *>(m_scene1->firstObject());
    Q_ASSERT(m != nullptr);
    bool isNum;
    qreal power = s.toDouble(&isNum);
    if (isNum && power <= 30 && power >= 3) m->setPower(power);
    else ui->mandelbulbPowerLE->setText(QString::number(m->getPower()));
    m_scene1->update();
}

void MainWindow::setupCameraList()
{
    int index = 0;
    for (const auto &option : Cam::allTypes)
    {
        ui->cameraSelectionMenu->addItem(Cam::typeToString(option), QVariant::fromValue(option));
        if (option == Cam::SPHERE) ui->cameraSelectionMenu->setCurrentIndex(index);
        ++index;
    }
    connect(ui->cameraSelectionMenu, &QComboBox::currentIndexChanged, this, &MainWindow::onCameraSelectionChanged);
}

void MainWindow::setupObjectList()
{
    settingsWidgets[Object::MANDELBULB] = ui->mandelbulbLayout;
    settingsWidgets[Object::CUBE] = ui->cubeLayout;
    settingsWidgets[Object::SPHERE] = ui->sphereLayout;
    for (auto i = settingsWidgets.cbegin(), end = settingsWidgets.cend(); i != end; i++)
    {
        i.value()->setVisible(i.key() == Object::MANDELBULB);
    }
    int index = 0;
    for (const auto &option : Object::allTypes) {
        ui->objectSelectionMenu->addItem(Object::typeToString(option), QVariant::fromValue(option));
        if (option == Object::MANDELBULB) ui->renderSelectionMenu->setCurrentIndex(index);
        ++index;
    }
    connect(ui->objectSelectionMenu, &QComboBox::currentIndexChanged, this, &MainWindow::onObjectSelectionChanged);
}

void MainWindow::setupRenderList()
{
    int index = 0;
    for (const auto &option : Renderer::allTypes) {
        ui->renderSelectionMenu->addItem(Renderer::typeToString(option), QVariant::fromValue(option));
        if (option == Renderer::CONCURRENT_RAYMARCHER) ui->renderSelectionMenu->setCurrentIndex(index);
        ++index;
    }
    connect(ui->renderSelectionMenu, &QComboBox::currentIndexChanged, this, &MainWindow::onRenderSelectionChanged);
}

void MainWindow::setupShadingList()
{
    int index = 0;
    for (const auto &option : Shading::allTypes) {
        ui->shadingSelectionMenu->addItem(Shading::typeToString(option), QVariant::fromValue(option));
    }
    index = ui->shadingSelectionMenu->findData(Shading::PHONG);
    ui->shadingSelectionMenu->setCurrentIndex(index);
    connect(ui->shadingSelectionMenu, &QComboBox::currentIndexChanged, this, &MainWindow::onShadingSelectionChanged);
}


void MainWindow::onObjectSelectionChanged(int index)
{
    QVariant variant = ui->objectSelectionMenu->itemData(index);
    auto typePtr = static_cast<Object::Type *>(variant.data());
    SceneObject *newObject = ObjectFactory::create(*typePtr);
    newObject->setColor(ui->objectColor->palette().button().color());
    setAdditionalParameters(newObject);
    m_scene1->clear(false);
    for (auto i = settingsWidgets.cbegin(), end = settingsWidgets.cend(); i != end; i++)
    {
        i.value()->setVisible(i.key() == *typePtr);
    }


    ui->objectSelectionMenu->setFocus();
    m_scene1->addObject(newObject);
}

void MainWindow::onCameraSelectionChanged(int index)
{
    QVariant variant = ui->cameraSelectionMenu->itemData(index);
    auto typePtr = static_cast<Cam::Type *>(variant.data());
    Camera *newCam = CameraFactory::create(*typePtr);
    m_scene1->setCamera(newCam);
    m_scene1->update();
}

void MainWindow::onIntensityChanged()
{
    bool ok;
    double intensity;
    intensity = ui->intensityLineEdit->text().toDouble(&ok);
    if (!ok || 0.1 > intensity || 1 < intensity)
    {
        ui->intensityLineEdit->setText(QString::number(m_scene1->getLightSource()->getIntensity(), 'g', 1));
    }
    else
    {
        m_scene1->getLightSource()->setIntensity(intensity);
        m_scene1->update();
    }
}

void MainWindow::onRenderSelectionChanged(int index)
{
    QVariant variant = ui->renderSelectionMenu->itemData(index);
    auto typePtr = static_cast<Renderer::Type *>(variant.data());
    RenderingAlgorithm *newAlgo = RenderingFactory::create(*typePtr);
    newAlgo->setShadingAlgorithm(m_scene1->getShadingAlgorithm());
    m_scene1->setRenderingAlgorithm(newAlgo);
    QStandardItemModel *model = qobject_cast<QStandardItemModel *>(ui->shadingSelectionMenu->model());
    if (*typePtr == Renderer::OPENGL)
    {
        for (const auto &type : Shading::allTypes)
        {
            int index = ui->shadingSelectionMenu->findData(type);
            QStandardItem *item = model->item(index);
            if (type != Shading::PHONG)
            {
                item->setFlags(Qt::NoItemFlags);
            }
            else
            {
                item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
                ui->shadingSelectionMenu->setCurrentIndex(index);
            }
        }
        m_scene1->setShadingAlgorithm(ShadingFactory::create(Shading::PHONG));
    }
    else
    {
        for (const auto &type : Shading::allTypes)
        {
            int index = ui->shadingSelectionMenu->findData(type);
            QStandardItem *item = model->item(index);
            item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        }
    }
    m_scene1->update();
}

void MainWindow::onShadingSelectionChanged(int index)
{
    QVariant variant = ui->shadingSelectionMenu->itemData(index);
    auto typePtr = static_cast<Shading::Type *>(variant.data());
    ShadingAlgorithm *newAlgo = ShadingFactory::create(*typePtr);
    m_scene1->setShadingAlgorithm(newAlgo);
    m_scene1->update();
}

void MainWindow::setupColors()
{
    QPalette bgPal;
    bgPal.setColor(QPalette::Button, m_scene1->getBGColor());
    ui->backgroundColor->setPalette(bgPal);

    QPalette objPal;
    QColor objColor;
    auto obj = m_scene1->firstObject();
    qDebug() << obj;
    if (obj != nullptr) {
        qDebug() << "objColor" << obj->getColor().toRgb();
        objColor = obj->getColor();
    } else { objColor = Qt::red; }
    objPal.setColor(QPalette::Button, objColor);
    ui->objectColor->setPalette(objPal);

    connect(ui->backgroundColor, &QPushButton::clicked, this, &MainWindow::onBGColorChangeClicked);
    connect(ui->objectColor, &QPushButton::clicked, this, &MainWindow::onObjectColorChangeClicked);
}

void MainWindow::onBGColorChangeClicked()
{
    QColor newColor = QColorDialog::getColor(Qt::white, this);
    if (newColor.isValid())
    {
        m_scene1->setBGColor(newColor);
        ui->backgroundColor->setPalette(QPalette(newColor));
    }
}

void MainWindow::onObjectColorChangeClicked()
{
    QColor newColor = QColorDialog::getColor(Qt::red, this);
    if (newColor.isValid())
    {
        m_scene1->updateObjectColor(newColor);
        ui->objectColor->setPalette(QPalette(newColor));
    }
}
