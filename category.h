#ifndef CATEGORY_H
#define CATEGORY_H

#include <QString>

class Category
{
public:
    Category();

    QString name() const;
    void setName(const QString &name);

    int id() const;
    void setId(int id);

private:
    int m_id = 0;
    QString m_name;

};

#endif // CATEGORY_H
