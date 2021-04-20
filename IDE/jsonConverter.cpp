#include "jsonConverter.h"
#include <QFile>
#include <QDebug>

jsonConverter::jsonConverter(QString entry) : fileName(entry){}

void jsonConverter::saveJson(QJsonObject message) {
    QByteArray data_json;
    QJsonDocument doc;

    doc.setObject(message);

    data_json = doc.toJson();

    QFile output(fileName);
    output.open(QIODevice::WriteOnly | QIODevice::Text);
    output.write(data_json);
    output.close();
}

void jsonConverter::readResultsJson() {
    QByteArray data_json;
    QJsonDocument doc;
    QJsonObject obj;

    QFile input(fileName);
    input.open(QIODevice::ReadOnly | QIODevice::Text);

    data_json = input.readAll();
    doc = doc.fromJson(data_json);
    obj = doc.object();

    request->setMemoryAddress(obj["memoryAddress"].toString());
    request->setLabel(obj["label"].toString());
    request->setValue(obj["value"].toString());
    request->setReferences(obj["references"].toString());
}

QJsonObject jsonConverter::getJsonObjectFromString(const QString jsonString) {
    QJsonDocument jsonDocument = QJsonDocument::fromJson(jsonString.toLocal8Bit().data());
    if (jsonDocument.isNull()) {
        qDebug()<< "===> please check the string" << jsonString.toLocal8Bit().data();
    }
    QJsonObject jsonObject = jsonDocument.object();
    return jsonObject;
}
