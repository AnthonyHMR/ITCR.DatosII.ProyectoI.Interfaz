#include "variablesConditions.h"
#include <QFile>
#include <QJsonDocument>

QJsonObject variablesConditions::getConditions(QStringList queryObjects, bool end) {
    QJsonObject obj;

    if (queryObjects[0] == "int" or queryObjects[0] == "string" or queryObjects[0] == "char" or queryObjects[0] == "long" or queryObjects[0] == "short" or queryObjects[0] == "double" or queryObjects[0] == "float") {
        obj["dataType"] = queryObjects[0];
        obj["label"] = queryObjects[1];

        if (queryObjects[2].isEmpty()) {
            obj["expression"] = "";
            obj["value"] = "0";
        } else if ((queryObjects[0] == "int" or queryObjects[0] == "char" or queryObjects[0] == "long" or queryObjects[0] == "short" or queryObjects[0] == "double" or queryObjects[0] == "float") and (queryObjects[2] == "-" or queryObjects[2] == "*" or queryObjects[2] == "/")) {
            obj["expression"] = queryObjects[2];
            obj["value"] = queryObjects[3];
        } else if (queryObjects[2] == "=" or queryObjects[2] == "+") {
            obj["expression"] = queryObjects[2];
            obj["value"] = queryObjects[3];
        } else {
            setError("Unexpected expresion");
        }

    } else if(queryObjects[0] == "print" or queryObjects[0] == "printf" or queryObjects[0] == "cout") {
        queryObjects.removeAll("");
        obj["dataType"] = "print";
        obj["label"] = "";
        obj["expression"] = "";
        obj["value"] = queryObjects[1];
    } else if(queryObjects[0] == "reference") {
        queryObjects.removeAll("");
        obj["dataType"] = queryObjects[0];
        obj["value"] = queryObjects[5];
        obj["expression"] = queryObjects[1];
        obj["label"] = queryObjects[2];
    }else {
        setError("Error data type");
    }

    if (end == true or error != "") {
        obj["reset"] = "true";
        if (error != "") {
            obj["dataType"] = "";
            obj["value"] = "";
            obj["expression"] = "";
            obj["label"] = "";
        }
    } else {
        obj["reset"] = "false";
    }

    return obj;
}

void variablesConditions::addJsonFile(QJsonArray ArrayObj, QString fileName)
{
    QByteArray data_json;
    QJsonDocument doc;

    doc.setArray(ArrayObj);
    data_json = doc.toJson();

    QFile output(fileName);
    output.open(QIODevice::WriteOnly | QIODevice::Text);
    output.write(data_json);
    output.close();
}

void variablesConditions::setError(QString text) {
    error = text;
}
