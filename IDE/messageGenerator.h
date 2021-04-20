#ifndef JSONCONVERTER_H
#define JSONCONVERTER_H

#include <QObject>
#include <QJsonObject>
#include <QJsonArray>
#include "jsonConverter.h"

class messageGenerator : public QObject
{
    Q_OBJECT
public:
    explicit messageGenerator(QObject *parent = nullptr);
    QString Generate(QString);
    QString getError();

private:
    QJsonObject getConditions();
    void addJsonFile(QJsonArray, QString);
    bool codeEnd();
    void setError(QString);
    QStringList queryLines, queryObjects;
    QJsonArray ArrayObj;
    int line = 0;
    QString error = "";
    //jsonConverter *converter;
};

#endif // JSONCONVERTER_H
