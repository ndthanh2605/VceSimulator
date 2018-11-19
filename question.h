#ifndef QUESTION_H
#define QUESTION_H

#include <QList>
#include <QString>

struct Answer {
    int m_key;
    QString m_answer;
    QString m_desc;

    Answer(int key, QString answer, QString desc) {
        m_key = key;
        m_answer = answer;
        m_desc = desc;
    }
};

class Question
{
public:
    enum ANSWER_KEY {
        A = 0,
        B, C, D
    };

    Question();

    bool isAnsCorrect();

    QString question() const;
    void setQuestion(const QString &question);

    QString answer() const;
    void setAnswer(const QString &answer);

    QString reasion() const;
    void setReasion(const QString &reasion);

    int answerKey() const;
    void setAnswerKey(int answerKey);
    void setAnswerKey(const QString &answerKeyChar);

    QList<Answer *> answers() const;
    void setListAnswers(const QList<Answer *> &answers);

    int catId() const;
    void setCatId(int catId);

    QString category() const;
    void setCategory(const QString &category);

    int id() const;
    void setId(int id);

    int userAnsKey() const;
    void setUserAnsKey(int userAnsKey);

private:
    int m_id = 0;
    QString m_question;
    int m_answerKey = 0;          // A,B,C,D
    QList<Answer *> m_answers;
    int m_catId = 0;
    QString m_category;

    int m_userAnsKey = -1;

};

#endif // QUESTION_H
