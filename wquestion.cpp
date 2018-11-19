#include "wquestion.h"
#include "ui_wquestion.h"
#include <QDebug>
#include <QJsonArray>

WQuestion::WQuestion(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WQuestion)
{
    ui->setupUi(this);

    ui->lblA->setText("");
    ui->lblB->setText("");
    ui->lblC->setText("");
    ui->lblD->setText("");
    ui->lblA->setVisible(false);
    ui->lblB->setVisible(false);
    ui->lblC->setVisible(false);
    ui->lblD->setVisible(false);

    m_groupRadios = new QButtonGroup;
    m_groupRadios->addButton(ui->rbA, 0);
    m_groupRadios->addButton(ui->rbB, 1);
    m_groupRadios->addButton(ui->rbC, 2);
    m_groupRadios->addButton(ui->rbD, 3);
    connect(m_groupRadios, SIGNAL(buttonToggled(int,bool)), this, SLOT(onRadioToggled(int,bool)));
}

WQuestion::~WQuestion()
{
    delete ui;
}

void WQuestion::setQuestion(Question *q, bool isShowAns)
{
    m_question = q;
    ui->lblQuestion->setText(q->question());
    if (q->answers().size() != 4) {
        return;
    }
    ui->lblAnsA->setText(q->answers().at(0)->m_answer);
    ui->lblAnsB->setText(q->answers().at(1)->m_answer);
    ui->lblAnsC->setText(q->answers().at(2)->m_answer);
    ui->lblAnsD->setText(q->answers().at(3)->m_answer);

    m_ansLabels.clear();
    m_ansLabels.append(ui->lblAnsA);
    m_ansLabels.append(ui->lblAnsB);
    m_ansLabels.append(ui->lblAnsC);
    m_ansLabels.append(ui->lblAnsD);

    ui->lblA->setText(q->answers().at(0)->m_desc);
    ui->lblB->setText(q->answers().at(1)->m_desc);
    ui->lblC->setText(q->answers().at(2)->m_desc);
    ui->lblD->setText(q->answers().at(3)->m_desc);

    if (isShowAns && q->answerKey() >= 0 && q->answerKey() < 4) {
        m_groupRadios->buttons().at(q->answerKey())->setChecked(true);

        ui->lblA->setVisible(true);
        ui->lblB->setVisible(true);
        ui->lblC->setVisible(true);
        ui->lblD->setVisible(true);
    }
}

void WQuestion::setShowAns(bool isShowAns)
{
    ui->lblA->setVisible(isShowAns);
    ui->lblB->setVisible(isShowAns);
    ui->lblC->setVisible(isShowAns);
    ui->lblD->setVisible(isShowAns);

    m_groupRadios->button(m_question->answerKey())->setChecked(true);
    if (!m_question->isAnsCorrect()) {
        QLabel * lbl = m_ansLabels.at(m_question->userAnsKey());
        if (lbl) {
            lbl->setStyleSheet("color: red;");
        }
    }
}

void WQuestion::setIsFirst(bool first)
{
    ui->pbPrev->setDisabled(first);
}

void WQuestion::setIsLast(bool last)
{
    ui->pbNext->setDisabled(last);
}

QJsonObject WQuestion::getData()
{
    QJsonObject obj;
    if (m_question) {
        obj["id"] = m_question->id();
        obj["question"] = m_question->question();
        obj["answer_key"] = m_question->answerKey();
        obj["category"] = m_question->category();
        obj["user_answer"] = m_question->userAnsKey();

        QJsonArray arrAns;
        for (int j = 0; j < m_question->answers().size(); ++j) {
            Answer * ans = m_question->answers().at(j);
            QJsonObject objAns;
            obj["key"] = ans->m_key;
            obj["answer"] = ans->m_answer;
            obj["desc"] = ans->m_desc;
            arrAns.append(objAns);
        }
        obj["list_answers"] = arrAns;
    }
    return obj;
}

bool WQuestion::isAnsCorrect()
{
    if (m_question)
        return m_question->isAnsCorrect();
    return false;
}

void WQuestion::onRadioToggled(int rbIdx, bool checked)
{
    if (checked && m_question) {
        qDebug() << "question" << m_question->id() << "ans" << m_question->answerKey();
        m_question->setUserAnsKey(rbIdx);
    }
}

void WQuestion::on_pbNext_clicked()
{
    ui->pbPrev->setEnabled(true);
    emit sigNextQuestion();
}

void WQuestion::on_pbPrev_clicked()
{
    ui->pbNext->setEnabled(true);
    emit sigPrevQuestion();
}
