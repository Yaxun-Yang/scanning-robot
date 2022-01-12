#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <memory>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
namespace rviz {class VisualizationFrame;}
namespace stereye { class Worker;class Param;}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(std::shared_ptr<stereye::Param> &param, QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void on_startSensorBtn_clicked();
    void on_stopSensorBtn_clicked();
    void on_startRecordBtn_clicked();
    void on_stopRecordBtn_clicked();
    void on_parseDataBtn_clicked();

    void startSensorDone();
    void stopSensorDone();
	void startRecordDone();
	void stopRecordDone();
    void parseDataDone();

signals:
	void startSensorBtnClicked(void);
    void stopSensorBtnClicked(void);
	void startRecordBtnClicked(void);
	void stopRecordBtnClicked(void);
    void parseDataBtnClicked(QString);

private:
    Ui::MainWindow *ui;
    std::shared_ptr<stereye::Worker> mpWorker;
    QThread *mWorkerThread;
    std::shared_ptr<rviz::VisualizationFrame> mpViewer;
    std::shared_ptr<stereye::Param> mpParam;
};
#endif // MAINWINDOW_H
