#ifndef FRMEXAMRESULT_H
#define FRMEXAMRESULT_H

#include <QWidget>

namespace Ui {
class FrmExamResult;
}

class FrmExamResult : public QWidget
{
    Q_OBJECT

public:
    explicit FrmExamResult(QWidget *parent = nullptr);
    ~FrmExamResult();

    void setQuestionCount(int value);
    void setUser(const QString &user);
    void setTime(const QString &timeStr);
    void setResult(int correctCount);

signals:
    void sigReviewExam();
    void sigSaveResult();

private slots:
    void on_pbViewAns_clicked();

    void on_pbSaveResult_clicked();

private:
    Ui::FrmExamResult *ui;
};

#endif // FRMEXAMRESULT_H
