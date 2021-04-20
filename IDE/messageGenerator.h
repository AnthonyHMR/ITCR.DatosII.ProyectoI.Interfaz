#ifndef JSONCONVERTER_H
#define JSONCONVERTER_H

#include <QObject>
#include <QJsonObject>
#include <QJsonArray>
#include "jsonConverter.h"

class messageGenerator : public QObject, Conditions
{
    Q_OBJECT
public:
    messageGenerator(QObject *parent = nullptr);
    QString Generate(QString);
    QString getError();

private:
    void addJsonFile(QJsonArray, QString);
    bool codeEnd();
    QStringList queryLines;
    QJsonArray ArrayObj;
    int line = 0;
    QString error = "";
};

#endif // JSONCONVERTER_H
