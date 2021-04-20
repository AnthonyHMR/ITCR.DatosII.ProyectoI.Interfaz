#include "Conditions.h"
#include <QFile>
#include <QJsonDocument>

QJsonObject Conditions::getConditions(QStringList queryLines, QStringList queryObjects, int line) {
    QJsonObject obj;

    if (!queryLines[line].endsWith(";")) {
        setError("Expected ';' at end of declaration");

    }else if (queryObjects[0] == "int" or queryObjects[0] == "string" or queryObjects[0] == "char") {
        obj["dataType"] = queryObjects[0];
        obj["label"] = queryObjects[1];

        if (queryObjects[2].isEmpty()) {
            obj["expression"] = "";
            obj["value"] = "0";
        } else if ((queryObjects[0] == "int" or queryObjects[0] == "char") and (queryObjects[2] == "-" or queryObjects[2] == "*" or queryObjects[2] == "/")) {
            obj["expression"] = queryObjects[2];
            obj["value"] = queryObjects[3];
        } else if (queryObjects[2] == "=" or queryObjects[2] == "+") {
            obj["expression"] = queryObjects[2];
            obj["value"] = queryObjects[3];
        } else {
            setError("Unexpected expresion");
        }

    } else {
        setError("Error data type");
    }

    return obj;
}

void Conditions::addJsonFile(QJsonArray ArrayObj, QString fileName)
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

void Conditions::setError(QString text) {
    error = text;
}
