#ifndef WQUESTION_H
#define WQUESTION_H

#include <QWidget>
#include <QButtonGroup>
#include <QLabel>
#include <QJsonObject>
#include "question.h"

namespace Ui {
class WQuestion;
}

class WQuestion : public QWidget
{
    Q_OBJECT

public:
    explicit WQuestion(QWidget *parent = nullptr);
    ~WQuestion();

    void setQuestion(Question *q, bool isShowAns = false);
    void setShowAns(bool isShowAns = true);
    void setIsFirst(bool first);
    void setIsLast(bool last);

    QJsonObject getData();

    bool isAnsCorrect();

signals:
    void sigNextQuestion();
    void sigPrevQuestion();

private slots:
    void onRadioToggled(int rbIdx, bool checked);

    void on_pbNext_clicked();

    void on_pbPrev_clicked();

private:
    Ui::WQuestion *ui;

    Question *m_question = 0;
    QButtonGroup *m_groupRadios;
    QList<QLabel *> m_ansLabels;

};

#endif // WQUESTION_H
