#include "mainWidget.h"
#include "ui_mainwidget.h"
#include "ui_mainwidget.h"
#include "messageGenerator.h"
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

    ui->ram_view_table->setColumnCount(4);
    QStringList titles;
    titles << "Address" << "Value" << "Label" << "References";
    ui->ram_view_table->setHorizontalHeaderLabels(titles);

    mSocket = new QTcpSocket(this);

    connect(mSocket, &QTcpSocket::readyRead, [&]() {
        QTextStream T(mSocket);
        auto text = T.readLine();

        jsonConverter *results = new jsonConverter("../results.json");

        results->saveJson(results->getJsonObjectFromString(text));
        results->readResultsJson();

        ui->ram_view_table->insertRow(ui->ram_view_table->rowCount());

        ui->ram_view_table->setItem(ui->ram_view_table->rowCount()-1, Address, new QTableWidgetItem(results->request->getMemoryAddress()));
        ui->ram_view_table->setItem(ui->ram_view_table->rowCount()-1, Value, new QTableWidgetItem(results->request->getValue()));
        ui->ram_view_table->setItem(ui->ram_view_table->rowCount()-1, Label, new QTableWidgetItem(results->request->getLabel()));
        ui->ram_view_table->setItem(ui->ram_view_table->rowCount()-1, References, new QTableWidgetItem(results->request->getReferences()));

        ui->applog_textEdit->clear();
        ui->applog_textEdit->append(results->request->getLog());
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
    if (ui->run_button->text() == "run") {
        ui->ram_view_table->setRowCount(0);
    }
    getInstance();

    QString code = ui->ide_TextEdit->toPlainText();

    if (code.isEmpty()) {
        return;
    }

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
