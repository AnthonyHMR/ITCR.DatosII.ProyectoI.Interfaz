#ifndef REQUEST_H
#define REQUEST_H

#include <QString>

class Request
{
public:
    QString getMemoryAddress();
    void setMemoryAddress(QString);
    QString getLabel();
    void setLabel(QString);
    QString getValue();
    void setValue(QString);
    QString getReferences();
    void setReferences(QString);
    QString getLog();
    void setLog(QString);
private:
    QString memoryAddress;
    QString label;
    QString value;
    QString references;
};

#endif // REQUEST_H
