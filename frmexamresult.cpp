#include "frmexamresult.h"
#include "ui_frmexamresult.h"

FrmExamResult::FrmExamResult(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FrmExamResult)
{
    ui->setupUi(this);
}

FrmExamResult::~FrmExamResult()
{
    delete ui;
}

void FrmExamResult::setQuestionCount(int value)
{
    ui->lblQuestionCount->setText(QString::number(value));
}

void FrmExamResult::setUser(const QString &user)
{
    ui->lblUser->setText(user);
}

void FrmExamResult::setTime(const QString &timeStr)
{
    ui->lblTime->setText(timeStr);
}

void FrmExamResult::setResult(int correctCount)
{
    ui->lblCorrects->setText(QString::number(correctCount));
    double mark = correctCount * 10.0 / ui->lblQuestionCount->text().toInt();
    ui->lblMark->setText(QString::number(mark));
}

void FrmExamResult::on_pbViewAns_clicked()
{
    emit sigReviewExam();
}

void FrmExamResult::on_pbSaveResult_clicked()
{
    emit sigSaveResult();
}
