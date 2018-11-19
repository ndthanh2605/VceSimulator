#include "frmconfigexam.h"
#include "ui_frmconfigexam.h"

FrmConfigExam::FrmConfigExam(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FrmConfigExam)
{
    ui->setupUi(this);
}

FrmConfigExam::~FrmConfigExam()
{
    delete ui;
}

void FrmConfigExam::setQuestionCount(int value)
{
    ui->spinQuestionCount->setValue(value);
}

void FrmConfigExam::on_pbStart_clicked()
{
    m_user = ui->leUser->text();
    m_totalTimeInMins = ui->spinTimeInMins->value();
    emit sigStartExam();
}

QString FrmConfigExam::user() const
{
    return m_user;
}

void FrmConfigExam::setUser(const QString &user)
{
    m_user = user;
}

int FrmConfigExam::totalTimeInMins() const
{
    return m_totalTimeInMins;
}

void FrmConfigExam::setTotalTimeInMins(int totalTimeInMins)
{
    m_totalTimeInMins = totalTimeInMins;
}
