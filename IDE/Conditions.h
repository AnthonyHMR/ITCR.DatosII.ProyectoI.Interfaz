#ifndef CONDITIONS_H
#define CONDITIONS_H

#include <QJsonObject>
#include <QJsonArray>


class Conditions
{
public:
    Conditions();
    QString getError();
    QString error = "";

protected:
    QJsonObject getConditions(QStringList, QStringList, int);
    void addJsonFile(QJsonArray, QString);
    void setError(QString);

private:

};

#endif // CONDITIONS_H
