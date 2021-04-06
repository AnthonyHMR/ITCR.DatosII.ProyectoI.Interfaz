#include "mainwidget.h"
#include "ui_mainwidget.h"
#include "ui_mainwidget.h"

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
    delete ui;
}

void MainWidget::on_run_button_clicked()
{
    QTextStream T(mSocket);
    QString text = ui->ide_plainTextEdit->toPlainText();
    T << text;
    mSocket->flush();
}

void MainWidget::on_clear_button_clicked()
{
    ui->applog_textEdit->clear();
}
