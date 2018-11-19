#ifndef CSVPARSER_H
#define CSVPARSER_H

#include <QObject>
#include <QHash>
#include "question.h"

class CsvParser
{
public:
    static QHash<int, Question *> parseQuestions(const QString &filePath);

};

#endif // CSVPARSER_H
