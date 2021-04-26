#ifndef STRUCTCONDITIONS_H
#define STRUCTCONDITIONS_H

#include "variablesConditions.h"
#include <QJsonObject>
#include <QJsonArray>
#include <QString>

class structConditions : public variablesConditions
{
public:
    structConditions();
    QJsonObject getConditions(QStringList);
    QJsonArray ArrayObj;
};

#endif // STRUCTCONDITIONS_H
