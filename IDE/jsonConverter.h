#ifndef JSONCONVERTER_H
#define JSONCONVERTER_H

#include <QObject>
#include <QJsonObject>
#include <QJsonArray>

class jsonConverter : public QObject
{
    Q_OBJECT
public:
    explicit jsonConverter(QObject *parent = nullptr);
    QString Convert(QString);
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
};

#endif // JSONCONVERTER_H
