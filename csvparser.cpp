#include "csvparser.h"
#include <QDebug>

QHash<int, Question *> CsvParser::parseQuestions(const QString &filePath)
{
    QHash<int, Question *> rs;
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << file.errorString();
        return rs;
    }

    QStringList wordList;
    while (!file.atEnd()) {
        QString line = file.readLine();
        line.chop(3);
        line = line.right(line.length() - 1);
//        qDebug() << line;
        QStringList parts = line.split("\",\"");
        if (parts.size() == 12) {
            int idx = parts.at(0).toInt();
            Question *q = new Question;
            q->setId(idx);
            q->setQuestion(parts.at(1));
            Answer *ansA = new Answer(Question::A, parts.at(2), parts.at(3));
            Answer *ansB = new Answer(Question::B, parts.at(4), parts.at(5));
            Answer *ansC = new Answer(Question::C, parts.at(6), parts.at(7));
            Answer *ansD = new Answer(Question::D, parts.at(8), parts.at(9));
            q->setListAnswers(QList<Answer *>{ansA, ansB, ansC, ansD});
            q->setAnswerKey(parts.at(10));
            q->setCategory(parts.at(11));

            rs.insert(idx, q);
        }
    }
    file.close();
    return rs;
}
