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

    Conditions::setError("");

    queryLines = entry.split(lines);
    queryLines.removeAll("");

    QStringList queryObjects = queryLines[line].split(objects);
    //queryObjects.removeAll("");

    QByteArray data_json;
    QJsonDocument doc;
    QJsonObject conditions = Conditions::getConditions(queryLines, queryObjects, line);

    if (getError() != "") {
        line = 0;
        return 0;
    }

    line ++;

    ArrayObj.append(conditions);

    if (codeEnd()){
        Conditions::addJsonFile(ArrayObj, "../variables.json");
        while(!ArrayObj.isEmpty()) {
            ArrayObj.removeLast();
        }
        Conditions::setError("end");
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
    return Conditions::error;
}
