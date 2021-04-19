#include "Results.h"
#include <QFile>

Results::Results() {}

void Results::saveResults(QJsonObject message) {
    doc.setObject(message);

    data_json = doc.toJson();

    QFile output("../results.json");
    output.open(QIODevice::WriteOnly | QIODevice::Text);
    output.write(data_json);
    output.close();

    //readResults();
}
/*
void Results::readResults() {
    QJsonObject obj;

    QFile input("../results.json");
    input.open(QIODevice::ReadOnly | QIODevice::Text);

    data_json = input.readAll();
    doc = doc.fromJson(data_json);
    obj = doc.object();

    request->setMemoryAddress(obj["memoryAddress"].toString());
    request->setLabel(obj["label"].toString());
    request->setValue(obj["value"].toString());
    request->setReferences(obj["references"].toString());
}
*/
