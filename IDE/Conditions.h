#ifndef CONDITIONS_H
#define CONDITIONS_H

#include <QJsonObject>
#include <QJsonArray>


class Conditions
{
protected:
    QJsonObject getConditions(QStringList, QStringList, int);
    void addJsonFile(QJsonArray, QString);
    void setError(QString);
    QString error = "";
};

#endif // CONDITIONS_H
