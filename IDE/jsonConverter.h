#ifndef JSONCONVERTER_H
#define JSONCONVERTER_H

#include <QObject>

class jsonConverter : public QObject
{
    Q_OBJECT
public:
    explicit jsonConverter(QObject *parent = nullptr);
    QString Convert(QString);
    bool lineBreak();
    QString getError();

private:
    void setError(QString);
    QString error = "";
    QStringList queryLines;
    int line = 0;
};

#endif // JSONCONVERTER_H
