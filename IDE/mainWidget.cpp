#include "mainWidget.h"
#include "ui_mainwidget.h"
#include "ui_mainwidget.h"
#include "messageGenerator.h"
#include "QRegExp"
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMessageBox>
#include <QDebug>

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget)
{
    ui->setupUi(this);

    setWindowTitle("C! IDE");
    mSocket = new QTcpSocket(this);

    connect(mSocket, &QTcpSocket::readyRead, [&]() {
        QTextStream T(mSocket);
        auto text = T.readLine();

        jsonConverter *results = new jsonConverter("../results.json");

        results->saveJson(results->getJsonObjectFromString(text));
        results->readResultsJson();

        ui->stdout_textEdit->append(text);
    });

    mSocket->connectToHost("localhost", 54000);
}

MainWidget::~MainWidget()
{
    delete json;
    delete ui;
}

void MainWidget::getInstance()
{
    if (json == NULL) {
        json = new messageGenerator(this);
    }
}

void MainWidget::showError()
{
    QString error = json->getError();

    if (error == "end") {
        QMessageBox::information(this, tr("Information"), tr("Your code has been executed successfully!"));
        ui->run_button->setText("run");

    }else if (error != "") {
        ui->applog_textEdit->append(error);
        QMessageBox::information(this, tr("Information"), tr("Your code has failed!"));
        ui->run_button->setText("run");

    } else {
        ui->run_button->setText("Next");
    }
}

void MainWidget::on_run_button_clicked()
{
    getInstance();

    QString code = ui->ide_TextEdit->toPlainText();

    QString text = json->Generate(code);

    showError();

    QTextStream T(mSocket);
    T << text;
    mSocket->flush();
}

void MainWidget::on_clear_button_clicked()
{
    ui->applog_textEdit->clear();
}
