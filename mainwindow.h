#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "frmconfigexam.h"
#include "frmexamresult.h"
#include "wexam.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionImportQuestions_triggered();

private:
    Ui::MainWindow *ui;

    QTimer m_examTimer;
    FrmConfigExam *m_wStartExam;
    WExam *m_widgetExam;
    FrmExamResult *m_wExamResult;

    void initTimer(int timeInMins);

};

#endif // MAINWINDOW_H
