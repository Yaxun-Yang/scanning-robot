#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "Worker.h"
#include <rviz/visualization_frame.h>

using namespace stereye;

MainWindow::MainWindow(std::shared_ptr<Param> &param, QWidget *parent)
    : mpParam(param), QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mpWorker = std::make_shared<Worker>(param);
    mWorkerThread = new QThread();
    mpWorker->moveToThread(mWorkerThread);
    mWorkerThread->start();

    connect(this, &MainWindow::startSensorBtnClicked, mpWorker.get(), &Worker::startSensor);
    connect(this, &MainWindow::stopSensorBtnClicked, mpWorker.get(), &Worker::stopSensor);
    connect(this, &MainWindow::startRecordBtnClicked, mpWorker.get(), &Worker::startRecord);
    connect(this, &MainWindow::stopRecordBtnClicked, mpWorker.get(), &Worker::stopRecord);
    connect(this, &MainWindow::parseDataBtnClicked, mpWorker.get(), &Worker::parseData);

    connect(mpWorker.get(), &Worker::startSensorDone, this, &MainWindow::startSensorDone);
    connect(mpWorker.get(), &Worker::stopSensorDone, this, &MainWindow::stopSensorDone);
    connect(mpWorker.get(), &Worker::startRecordDone, this, &MainWindow::startRecordDone);
    connect(mpWorker.get(), &Worker::stopRecordDone, this, &MainWindow::stopRecordDone);
    connect(mpWorker.get(), &Worker::parseDataDone, this, &MainWindow::parseDataDone);

    ui->startSensorBtn->setEnabled(true);
    ui->stopSensorBtn->setEnabled(false);
    ui->startRecordBtn->setEnabled(false);
    ui->stopRecordBtn->setEnabled(false);
    // ui->parseDataBtn->setEnabled(false);
    this->setWindowTitle("录制工具");

    mpViewer = std::make_shared<rviz::VisualizationFrame>();
    mpViewer->initialize(PROJECT_SOURCE_DIR "/cartographer/demo.rviz");
	ui->viewer->layout()->addWidget(mpViewer.get());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_startSensorBtn_clicked() {
    qDebug() << "MainWindow::on_startSensorBtn_clicked";
    ui->startSensorBtn->setEnabled(false);
    ui->stopSensorBtn->setEnabled(true);
    emit startSensorBtnClicked();
}

void MainWindow::on_stopSensorBtn_clicked() {
    qDebug() << "MainWindow::on_stopSensorBtn_clicked";
    ui->stopSensorBtn->setEnabled(false);
    emit stopSensorBtnClicked();
}

void MainWindow::on_startRecordBtn_clicked() {
    qDebug() << "MainWindow::on_startRecordBtn_clicked";
    ui->startRecordBtn->setEnabled(false);
    emit startRecordBtnClicked();
}

void MainWindow::on_stopRecordBtn_clicked() {
    qDebug() << "MainWindow::on_stopRecordBtn_clicked";
    ui->stopRecordBtn->setEnabled(false);
    emit stopRecordBtnClicked();
}

void MainWindow::on_parseDataBtn_clicked() {
    qDebug() << "MainWindow::on_parseDataBtn_clicked";
    QString dir = QFileDialog::getExistingDirectory(
               this, "choose data directory",
                "/home/riger/");
    if (dir.isEmpty()) return;
    ui->parseDataBtn->setEnabled(false);
    emit parseDataBtnClicked(dir);
}

void MainWindow::startSensorDone() {
    qDebug() << "MainWindow::startSensorDone";
    ui->startRecordBtn->setEnabled(true);
}

void MainWindow::stopSensorDone() {
    qDebug() << "MainWindow::stopSensorDone";
    ui->startSensorBtn->setEnabled(true);
    ui->startRecordBtn->setEnabled(false);
}

void MainWindow::startRecordDone() {
    qDebug() << "MainWindow::startRecordDone";
    ui->stopRecordBtn->setEnabled(true);
}

void MainWindow::stopRecordDone() {
    qDebug() << "MainWindow::stopRecordDone";
    // rosbag record stopped, call carto to save data
}

void MainWindow::parseDataDone() {
    qDebug() << "MainWindow::parseDataDone";
    ui->parseDataBtn->setEnabled(true);
}
//py example https://github.com/gutsy-robot/rviz_embedder_tutorial/blob/master/rviz_custom_example.py


//https://github.com/ros-visualization/rviz/blob/a808401c5da82db5a85e8f4d277ee5d1f883dcd9/src/rviz/visualization_frame.cpp
// YamlConfigReader reader;
//   Config config;
//   reader.readFile(config, QString::fromStdString(full_path));
//   if (reader.error())
//     return false;

//   load(config);
// void VisualizationFrame::load(const Config& config)
// {
//   manager_->load(config.mapGetChild("Visualization Manager"));
//   loadPanels(config.mapGetChild("Panels"));
//   loadWindowGeometry(config.mapGetChild("Window Geometry"));
//   loadPreferences(config.mapGetChild("Preferences"));
//   configureToolbars(config.mapGetChild("Toolbars"));
// }