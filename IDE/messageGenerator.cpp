#include "messageGenerator.h"
#include "QRegExp"
#include <QFile>
#include <QJsonDocument>
#include <QMessageBox>

messageGenerator::messageGenerator(QObject *parent) : QObject(parent)
{
}

QString messageGenerator::Generate(QString entry)
{
    QRegExp lines("(\\\n)");
    QRegExp objects("(\\ |\\;)");

    error = "";

    queryLines = entry.split(lines);
    queryLines.removeAll("");

    queryObjects = queryLines[line].split(objects);
    //queryObjects.removeAll("");

    QByteArray data_json;
    QJsonDocument doc;
    QJsonObject conditions = getConditions();

    if (getError() != "") {
        return 0;
    }

    line ++;

    ArrayObj.append(conditions);

    if (codeEnd()){
        addJsonFile(ArrayObj, "variables");
        while(!ArrayObj.isEmpty()) {
            ArrayObj.removeLast();
        }
        setError("end");
    }

    doc.setObject(conditions);

    data_json = doc.toJson();

    return data_json;
}

QJsonObject messageGenerator::getConditions() {
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

void messageGenerator::addJsonFile(QJsonArray ArrayObj, QString fileName)
{
    QByteArray data_json;
    QJsonDocument doc;

    doc.setArray(ArrayObj);
    data_json = doc.toJson();

    QFile output("../" + fileName + ".json");
    output.open(QIODevice::WriteOnly | QIODevice::Text);
    output.write(data_json);
    output.close();
}

bool messageGenerator::codeEnd()
{
    if (line == queryLines.length()) {
        return true;
    }
    return false;
}

QString messageGenerator::getError() {
    return error;
}

void messageGenerator::setError(QString text) {
    error = text;
    line = 0;
}
