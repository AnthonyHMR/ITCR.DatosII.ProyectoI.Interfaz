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

    error = "";

    queryLines = entry.split(lines);
    queryLines.removeAll("");

    if (!queryLines[line].endsWith(";")) {
        setError("Expected ';' at end of declaration");
        return 0;
    }

    QStringList queryObjects = queryLines[line].split(objects);
    //queryObjects.removeAll("");

    QByteArray data_json;
    QJsonDocument doc;
    QJsonObject obj;

    if (queryObjects[0] == "int" or queryObjects[0] == "string") {
        obj["dataType"] = queryObjects[0];
        obj["label"] = queryObjects[1];

        if (queryObjects[2].isEmpty()) {
            obj["expression"] = "";
            obj["value"] = "";
        } else if ((queryObjects[0] == "int") and (queryObjects[2] == "=" or queryObjects[2] == "+" or queryObjects[2] == "-" or queryObjects[2] == "*" or queryObjects[2] == "/")) {
            obj["expression"] = queryObjects[2];
            obj["value"] = queryObjects[3];
        } else if (queryObjects[0] == "string" and queryObjects[2] == "=") {
            obj["expression"] = queryObjects[2];
            obj["value"] = queryObjects[3];
        } else {
            setError("Unexpected expresion");
            return 0;
        }

    } else {
        setError("Error data type");
        return 0;
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

QString jsonConverter::getError() {
    return error;
}

void jsonConverter::setError(QString text) {
    error = text;
    line = 0;
}
