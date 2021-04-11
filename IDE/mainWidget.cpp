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

    if (json == NULL) {
        json = new jsonConverter(this);
    }

    QString text = json->Convert(code);
    QString error = json->getError();

    if (error != "") {
        ui->applog_textEdit->append(error);
        QMessageBox::information(this, tr("Information"), tr("Your code has failed!"));
        ui->run_button->setText("run");

    }else if (json->lineBreak()) {
        QMessageBox::information(this, tr("Information"), tr("Your code has been executed successfully!"));
        ui->run_button->setText("run");

    } else {
        ui->run_button->setText("Next");
    }

    QTextStream T(mSocket);
    T << text;
    mSocket->flush();
}

void MainWidget::on_clear_button_clicked()
{
    ui->applog_textEdit->clear();
}
