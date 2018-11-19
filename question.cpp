#include "question.h"

Question::Question()
{

}

bool Question::isAnsCorrect()
{
    if (m_userAnsKey >= 0 && m_userAnsKey == m_answerKey)
        return true;
    return false;
}

QString Question::question() const
{
    return m_question;
}

void Question::setQuestion(const QString &question)
{
    m_question = question;
}

int Question::answerKey() const
{
    return m_answerKey;
}

void Question::setAnswerKey(int answerKey)
{
    m_answerKey = answerKey;
}

void Question::setAnswerKey(const QString &answerKeyChar)
{
    if (answerKeyChar.toUpper() == "A") {
        m_answerKey = A;
    } else if (answerKeyChar.toUpper() == "B") {
        m_answerKey = B;
    } else if (answerKeyChar.toUpper() == "C") {
        m_answerKey = C;
    } else if (answerKeyChar.toUpper() == "D") {
        m_answerKey = D;
    }
}

QList<Answer *> Question::answers() const
{
    return m_answers;
}

void Question::setListAnswers(const QList<Answer *> &answers)
{
    m_answers = answers;
}

int Question::catId() const
{
    return m_catId;
}

void Question::setCatId(int catId)
{
    m_catId = catId;
}

QString Question::category() const
{
    return m_category;
}

void Question::setCategory(const QString &category)
{
    m_category = category;
}

int Question::id() const
{
    return m_id;
}

void Question::setId(int id)
{
    m_id = id;
}

int Question::userAnsKey() const
{
    return m_userAnsKey;
}

void Question::setUserAnsKey(int userAnsKey)
{
    m_userAnsKey = userAnsKey;
}
