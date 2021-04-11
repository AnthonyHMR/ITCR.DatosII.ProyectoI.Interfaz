#include "mainWidget.h"
#include "ui_mainwidget.h"
#include "ui_mainwidget.h"
#include "jsonConverter.h"

#include "QRegExp"
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMessageBox>

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget)
{
    ui->setupUi(this);
    setWindowTitle("C! IDE");
    mSocket = new QTcpSocket(this);

    connect(mSocket, &QTcpSocket::readyRead, [&]() {
        QTextStream T(mSocket);
        auto text = T.readAll();
        ui->stdout_textEdit->append(text);
    });

    mSocket->connectToHost("localhost", 54000);
}

MainWidget::~MainWidget()
{
    delete json;
    delete ui;
}

void MainWidget::on_run_button_clicked()
{
    QString code = ui->ide_TextEdit->toPlainText();

    /*
    QRegExp lines("(\\\n)");
    QRegExp objects("(\\ |\\;)");

    QStringList queryLines = code.split(lines);
    queryLines.removeAll("");

    QStringList queryObjects = queryLines[line].split(objects);
    queryObjects.removeAll("");

    if (line == queryLines.length()-1) {
        QMessageBox::information(this, tr("Message"), tr("Your code has been executed successfully!"));
        ui->run_button->setText("run");
        line = 0;
    } else {
        ui->run_button->setText("Next");
        line++;
    }

    QByteArray data_json;
    QJsonDocument doc;
    QJsonObject obj;

    obj["dataType"] = queryObjects[0];
    obj["label"] = queryObjects[1];
    if (!queryObjects[2].isEmpty()) {
        obj["expression"] = queryObjects[2];
        obj["value"] = queryObjects[3];
    } else {
        obj["expression"] = "";
        obj["value"] = "";
    }

    doc.setObject(obj);


    data_json = doc.toJson();
    */
    if (json == NULL) {
        json = new jsonConverter(this);
    }

    QTextStream T(mSocket);
    T << json->Convert(code);
    mSocket->flush();

    if (json->lineBreak()) {
        QMessageBox::information(this, tr("Message"), tr("Your code has been executed successfully!"));
        ui->run_button->setText("run");
    } else {
        ui->run_button->setText("Next");
    }
}

void MainWidget::on_clear_button_clicked()
{
    ui->applog_textEdit->clear();
}
