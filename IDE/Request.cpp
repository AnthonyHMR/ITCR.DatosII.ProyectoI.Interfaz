#include "Request.h"

QString Request::getMemoryAddress() {
    return memoryAddress;
}

void Request::setMemoryAddress(QString entry) {
    memoryAddress = entry;
}

QString Request::getLabel() {
    return label;
}

void Request::setLabel(QString entry) {
    label = entry;
}

QString Request::getValue() {
    return value;
}

void Request::setValue(QString entry) {
    value = entry;
}

QString Request::getReferences() {
    return references;
}

void Request::setReferences(QString entry) {
    references = entry;
}
