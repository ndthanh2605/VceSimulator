#include "category.h"

Category::Category()
{

}

QString Category::name() const
{
    return m_name;
}

void Category::setName(const QString &name)
{
    m_name = name;
}

int Category::id() const
{
    return m_id;
}

void Category::setId(int id)
{
    m_id = id;
}
