#ifndef CONDITIONS_H
#define CONDITIONS_H

#include <QJsonObject>
#include <QJsonArray>


class variablesConditions
{
protected:
    QJsonObject getConditions(QStringList, bool);
    void addJsonFile(QJsonArray, QString);
    void setError(QString);
    QString error = "";
};

#endif // CONDITIONS_H
