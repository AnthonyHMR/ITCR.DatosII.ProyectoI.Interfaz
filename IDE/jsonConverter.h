#ifndef RESULTS_H
#define RESULTS_H

#include "Conditions.h"
#include <QString>
#include "Request.h"
#include <QJsonObject>
#include <QJsonDocument>

class jsonConverter : public Conditions
{
public:
    jsonConverter(QString);
    void saveJson(QJsonObject);
    QJsonObject getJsonObjectFromString(const QString);
    void readResultsJson();
    Request *request = new Request();
private:
    QString fileName;
};

#endif // RESULTS_H
