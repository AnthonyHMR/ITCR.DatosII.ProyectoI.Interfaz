#ifndef JSONCONVERTER_H
#define JSONCONVERTER_H

#include <QObject>

class jsonConverter : public QObject
{
    Q_OBJECT
public:
    explicit jsonConverter(QObject *parent = nullptr);
    QString Convert(QString entry);
    bool lineBreak();

private:
    QStringList queryLines;
    int line = 0;
};

#endif // JSONCONVERTER_H
