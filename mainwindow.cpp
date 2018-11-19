#include "csvparser.h"
#include "csvparser.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QDateTime>
#include <QDebug>
#include <QLayout>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_wStartExam = new FrmConfigExam;
    ui->stackedWidget->addWidget(m_wStartExam);
    m_widgetExam = new WExam;
    ui->stackedWidget->addWidget(m_widgetExam);
    m_wExamResult = new FrmExamResult;
    ui->stackedWidget->addWidget(m_wExamResult);

    connect(m_wStartExam, &FrmConfigExam::sigStartExam, this, [this]() {
        ui->stackedWidget->setCurrentWidget(m_widgetExam);
        initTimer(m_wStartExam->totalTimeInMins());
        m_widgetExam->countdownTime(m_wStartExam->totalTimeInMins() * 60);
        m_wExamResult->setUser(m_wStartExam->user());
    });
    connect(m_widgetExam, &WExam::sigDoneExam, this, [this]() {
        m_examTimer.stop();

        int usedTime = m_wStartExam->totalTimeInMins() * 60 - m_widgetExam->durationInSecs();
        m_wExamResult->setTime(m_widgetExam->parseSecsToStr(usedTime));
        m_wExamResult->setResult(m_widgetExam->getCorrectAnsCount());
        ui->stackedWidget->setCurrentWidget(m_wExamResult);
    });
    connect(m_wExamResult, &FrmExamResult::sigReviewExam, this, [this]() {
        ui->stackedWidget->setCurrentWidget(m_widgetExam);
        m_widgetExam->reviewExam();
    });
    connect(m_wExamResult, &FrmExamResult::sigSaveResult, this, [this]() {
        m_widgetExam->saveExam(QString("D:/%1_%2.result").arg(m_wStartExam->user()).arg(QDateTime::currentDateTime().toString("yyyyMMdd_hhmmss")));
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionImportQuestions_triggered()
{
    QString file = QFileDialog::getOpenFileName(this, tr("Open CSV"), "C:/", tr("Csv Files (*.csv *.txt)"));
    qDebug() << "import file csv:" << file;

    QHash<int, Question *> allQuestions = CsvParser::parseQuestions(file);
    m_wStartExam->setQuestionCount(allQuestions.size());
    m_wExamResult->setQuestionCount(allQuestions.size());
    m_widgetExam->createQuestionsPages(allQuestions);
    ui->stackedWidget->setCurrentWidget(m_wStartExam);
}

void MainWindow::initTimer(int timeInMins)
{
    m_examTimer.setSingleShot(true);
    m_examTimer.setInterval(timeInMins * 60 * 1000);
    connect(&m_examTimer, &QTimer::timeout, this, [this]() {
        QMessageBox::information(this, tr("Info"), tr("Out of time! Exam is finished."));
        ui->stackedWidget->setCurrentWidget(m_wExamResult);
    });
    m_examTimer.start();
}
