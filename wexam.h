#ifndef WEXAM_H
#define WEXAM_H

#include "question.h"

#include <QTimer>
#include <QWidget>

namespace Ui {
class WExam;
}

class WExam : public QWidget
{
    Q_OBJECT

public:
    explicit WExam(QWidget *parent = nullptr);
    ~WExam();

    void clearStackQuestions();
    void createQuestionsPages(const QHash<int, Question *> &questions);
    void countdownTime(int durationInSecs);
    QString parseSecsToStr(int seconds);
    int getCorrectAnsCount();
    void reviewExam();
    void saveExam(const QString &filePath);

    int durationInSecs() const;
    void setDurationInSecs(int durationInSecs);

signals:
    void sigDoneExam();

private slots:
    void on_spinIdx_valueChanged(int idx);

    void on_pbEnd_clicked();

    void on_pbViewMarks_clicked();

    void on_chbMark_clicked(bool checked);

private:
    Ui::WExam *ui;

    QTimer m_timer;
    int m_durationInSecs;
    QList<int> m_markedIndexes;
    QList<int> m_wrongAnswerIndexes;

    void setQuestionIdx(int idx);
    void refreshCbMarkedIndexes();

};

#endif // WEXAM_H
