#include "wexam.h"
#include "ui_wexam.h"
#include "wquestion.h"

#include <QJsonArray>
#include <QJsonDocument>
#include <QMessageBox>
#include <QTime>
#include <QDebug>
#include <QProgressDialog>

WExam::WExam(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WExam)
{
    ui->setupUi(this);

    connect(&m_timer, &QTimer::timeout, this, [this]() {
        m_durationInSecs--;
        ui->lblTime->setText(parseSecsToStr(m_durationInSecs));
    });
}

WExam::~WExam()
{
    delete ui;
}

void WExam::clearStackQuestions()
{
    while (ui->stackedWidget->count() > 0) {
        QWidget *w = ui->stackedWidget->widget(0);
        ui->stackedWidget->removeWidget(w);
        w->deleteLater();
    }
}

void WExam::createQuestionsPages(const QHash<int, Question *> &questions)
{
    QProgressDialog dlg;
    dlg.setRange(0, questions.size());
    dlg.setValue(0);
    dlg.show();
    QApplication::processEvents();

    clearStackQuestions();
    ui->lblTotal->setText(QString::number(questions.size()));
    ui->spinIdx->setValue(1);
    ui->spinIdx->setMaximum(questions.size());
    for (auto itr = questions.begin(); itr != questions.end(); itr++) {
        WQuestion *w = new WQuestion;
        w->setQuestion(itr.value());
        ui->stackedWidget->addWidget(w);
        if (itr == questions.begin()) {
            w->setIsFirst(true);
        }
        dlg.setValue(dlg.value() + 1);
        QApplication::processEvents();

        connect(w, &WQuestion::sigNextQuestion, this, [this, questions]() {
            int curIdx = ui->stackedWidget->currentIndex();
            ui->spinIdx->setValue(curIdx + 2);
        });
        connect(w, &WQuestion::sigPrevQuestion, this, [this, questions]() {
            int curIdx = ui->stackedWidget->currentIndex();
            ui->spinIdx->setValue(curIdx);

        });
    }
    dlg.close();
}

void WExam::countdownTime(int durationInSecs)
{
    m_durationInSecs = durationInSecs;
    ui->lblTime->setText(parseSecsToStr(m_durationInSecs));
    m_timer.stop();
    m_timer.start(1000);
}

void WExam::on_spinIdx_valueChanged(int idx)
{
    setQuestionIdx(idx-1);
}

void WExam::on_pbEnd_clicked()
{
    QMessageBox::StandardButton ans = QMessageBox::question(this, tr("Confirm"), tr("Are you really want to end your exam?"));
    if (ans == QMessageBox::Yes) {
        emit sigDoneExam();
    }
}

void WExam::on_pbViewMarks_clicked()
{
    int markedIdx = ui->cbMarkedIdx->currentData().toInt();
    ui->spinIdx->setValue(markedIdx);
}

void WExam::on_chbMark_clicked(bool checked)
{
    int curIdx = ui->stackedWidget->currentIndex();
    if (checked) {
        if (!m_markedIndexes.contains(curIdx))
            m_markedIndexes.append(curIdx);
    } else {
        m_markedIndexes.removeAll(curIdx);
    }
    refreshCbMarkedIndexes();
}

int WExam::durationInSecs() const
{
    return m_durationInSecs;
}

void WExam::setDurationInSecs(int durationInSecs)
{
    m_durationInSecs = durationInSecs;
}

void WExam::setQuestionIdx(int idx)
{
    if (idx >= 0 && idx < ui->stackedWidget->count()) {
        ui->stackedWidget->setCurrentIndex(idx);
        ui->chbMark->setChecked(m_markedIndexes.contains(idx));
        WQuestion *w = dynamic_cast<WQuestion *>(ui->stackedWidget->currentWidget());
        if (w) {
            if (idx == 0) {
                w->setIsFirst(true);
            } else if (idx == ui->stackedWidget->count()-1) {
                w->setIsLast(true);
            }
        }
    }
}

void WExam::refreshCbMarkedIndexes()
{
    ui->cbMarkedIdx->clear();
    qSort(m_markedIndexes);
    for (int i = 0; i < m_markedIndexes.size(); i++) {
        ui->cbMarkedIdx->addItem(QString::number(m_markedIndexes.at(i) + 1), m_markedIndexes.at(i));
    }
}

QString WExam::parseSecsToStr(int seconds)
{
    QTime t(0,0,0);
    t = t.addSecs(seconds);
    return t.toString("hh:mm:ss");
}

int WExam::getCorrectAnsCount()
{
    m_wrongAnswerIndexes.clear();
    for (int i = 0; i < ui->stackedWidget->count(); ++i) {
        WQuestion *w = dynamic_cast<WQuestion *>(ui->stackedWidget->widget(i));
        if (w && !w->isAnsCorrect()) {
            m_wrongAnswerIndexes.append(i);
        }
    }
    return (ui->stackedWidget->count() - m_wrongAnswerIndexes.size());
}

void WExam::reviewExam()
{
    for (int i = 0; i < ui->stackedWidget->count(); ++i) {
        WQuestion *w = dynamic_cast<WQuestion *>(ui->stackedWidget->widget(i));
        if (w) {
            w->setShowAns(true);
        }
    }
    ui->stackedWidget->setCurrentIndex(0);
}

void WExam::saveExam(const QString &filePath)
{
    QFile file(filePath);
    if (!file.open(QIODevice::ReadWrite)) {
        qDebug() << file.errorString();
        return;
    }

    QJsonArray arr;
    for (int i = 0; i < ui->stackedWidget->count(); ++i) {
        WQuestion *w = dynamic_cast<WQuestion *>(ui->stackedWidget->widget(i));
        if (w) {
            QJsonObject obj = w->getData();
            arr.append(obj);
        }
    }
    QJsonDocument doc(arr);
    QByteArray bytes = doc.toJson(QJsonDocument::Compact);

    file.write(bytes);
    file.close();
    qDebug() << "save exam done!";
}
