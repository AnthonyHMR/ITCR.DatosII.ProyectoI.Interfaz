#include "jsonConverter.h"
#include "QRegExp"
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMessageBox>

jsonConverter::jsonConverter(QObject *parent) : QObject(parent)
{
}

QString jsonConverter::Convert(QString entry)
{
    QRegExp lines("(\\\n)");
    QRegExp objects("(\\ |\\;)");

    queryLines = entry.split(lines);
    queryLines.removeAll("");

    QStringList queryObjects = queryLines[line].split(objects);
    queryObjects.removeAll("");

    QByteArray data_json;
    QJsonDocument doc;
    QJsonObject obj;

    obj["dataType"] = queryObjects[0];
    obj["label"] = queryObjects[1];
    if (!queryObjects[2].isEmpty()) {
        obj["expression"] = queryObjects[2];
        obj["value"] = queryObjects[3];
    } else {
        obj["expression"] = "";
        obj["value"] = "";
    }

    doc.setObject(obj);


    data_json = doc.toJson();

    return data_json;
}

bool jsonConverter::lineBreak()
{
    if (line == queryLines.length()-1) {
        line = 0;
        return true;
    }
    line++;
    return false;
}
