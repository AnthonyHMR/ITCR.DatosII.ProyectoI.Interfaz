#include "structConditions.h"
#include <QDebug>

structConditions::structConditions() {}

QJsonObject structConditions::getConditions(QStringList ArrayStruct, bool end) {
    QJsonObject obj;
    QJsonObject conditions;
    QStringList variable;

    ArrayStruct.removeAll("");

    if (ArrayStruct[0] == "struct") {
        obj["dataType"] = ArrayStruct[0];
        ArrayStruct.removeFirst();

        while(!ArrayStruct.isEmpty()) {
            if (ArrayStruct.length() == 2 or ArrayStruct[2] == "int") {
                for (int i=0; i <= 1; i++) {
                    variable.append(ArrayStruct[0]);
                    ArrayStruct.removeFirst();
                }
                variable.append("");
                variable.append("");
            } else {
                for (int i=0; i <= 3; i++) {
                    variable.append(ArrayStruct[0]);
                    ArrayStruct.removeFirst();
                }
            }

            conditions = variablesConditions::getConditions(variable, false);
            ArrayObj.append(conditions);

            while(!variable.isEmpty()) {
                variable.removeLast();
            }
        }

        obj["value"] = ArrayObj;
        obj["expression"] = "";

        while(!ArrayObj.isEmpty()) {
            ArrayObj.removeLast();
        }

    } else {
        variablesConditions::setError("Error data type");
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
