#ifndef RESULTS_H
#define RESULTS_H

#include <QString>
#include "Request.h"
#include <QJsonObject>
#include <QJsonDocument>

class Results
{
public:
    Results();
protected:
    void saveResults(QJsonObject);
    Request *request = new Request();
private:
    void readResults();
    QByteArray data_json;
    QJsonDocument doc;
};

#endif // RESULTS_H
