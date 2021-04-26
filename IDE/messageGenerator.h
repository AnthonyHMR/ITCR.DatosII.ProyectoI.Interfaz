#ifndef JSONCONVERTER_H
#define JSONCONVERTER_H

#include <QObject>
#include <QJsonObject>
#include <QJsonArray>
#include "jsonConverter.h"
#include "structConditions.h"

class messageGenerator : public QObject, public structConditions
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
    QStringList ArrayStruct;
    QJsonArray ArrayObj;
    int line = 0;
    QString error = "";
    bool flag = false;
};

#endif // JSONCONVERTER_H
