#ifndef FRMCONFIGEXAM_H
#define FRMCONFIGEXAM_H

#include <QWidget>

namespace Ui {
class FrmConfigExam;
}

class FrmConfigExam : public QWidget
{
    Q_OBJECT

public:
    explicit FrmConfigExam(QWidget *parent = nullptr);
    ~FrmConfigExam();

    void setQuestionCount(int value);

    int totalTimeInMins() const;
    void setTotalTimeInMins(int totalTimeInMins);

    QString user() const;
    void setUser(const QString &user);

signals:
    void sigStartExam();

private slots:
    void on_pbStart_clicked();

private:
    Ui::FrmConfigExam *ui;

    int m_totalTimeInMins;
    QString m_user;

};

#endif // FRMCONFIGEXAM_H
