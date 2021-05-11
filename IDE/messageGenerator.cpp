#include "messageGenerator.h"
#include "QRegExp"
#include <QFile>
#include <QJsonDocument>
#include <QMessageBox>
#include <QDebug>

messageGenerator::messageGenerator(QObject *parent) : QObject(parent) {}

QString messageGenerator::Generate(QString entry)
{
    QRegExp lines("(\\\n)");
    QRegExp objects("(\\ |\\;|\\{|\\}|\\\t|\\(|\\)|\\<)");

    variablesConditions::setError("");

    queryLines = entry.split(lines);
    queryLines.removeAll("");

    QStringList queryObjects = queryLines[line].split(objects);
    //queryObjects.removeAll("");

    QByteArray data_json;
    QJsonDocument doc;
    QJsonObject conditions;

    if (queryLines[line].endsWith("{") and flag == false) {
        flag = true;
    } else if (!queryLines[line].endsWith(";")) {
        variablesConditions::setError("Expected ';' at the end of declaration");
        while(!ArrayStruct.isEmpty()) {
            ArrayStruct.removeFirst();
        }
        flag = false;
        line = 0;
        return 0;
    }

    if (flag) {

        if (queryLines[line].contains("}")){
            qDebug()<< "===> please check the string" << queryObjects;
            conditions = structConditions::getConditions(ArrayStruct, line+1 == queryLines.length());
            conditions["label"] = queryObjects[1];
            while(!ArrayStruct.isEmpty()) {
                ArrayStruct.removeFirst();
            }
            flag = false;
        } else {
            ArrayStruct.append(queryObjects);
            line ++;
            return 0;
        }
    } else {
        conditions = variablesConditions::getConditions(queryObjects, line+1 == queryLines.length());
    }

    //Verifica si hubo un error en una linea de codigo
    if (getError() != "") {
        line = 0;
        flag = false;
        doc.setObject(conditions);

        data_json = doc.toJson();

        return data_json;
    }

    line ++;

    ArrayObj.append(conditions);

    if (codeEnd()){
        variablesConditions::addJsonFile(ArrayObj, "../variables.json");
        while(!ArrayObj.isEmpty()) {
            ArrayObj.removeLast();
        }
        variablesConditions::setError("end");
        line = 0;
    }

    doc.setObject(conditions);

    data_json = doc.toJson();

    return data_json;
}

bool messageGenerator::codeEnd()
{
    if (line == queryLines.length()) {
        return true;
    }
    return false;
}

QString messageGenerator::getError() {
    return variablesConditions::error;
}
