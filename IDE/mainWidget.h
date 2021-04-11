#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QTcpSocket>
#include <jsonConverter.h>

namespace Ui { class MainWidget; }

class QTcpSocket;

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = nullptr);
    ~MainWidget();

private slots:
    void on_run_button_clicked();

    void on_clear_button_clicked();

private:
    Ui::MainWidget *ui;
    QTcpSocket *mSocket;
    jsonConverter *json = NULL;

    int line = 0;
};

#endif // MAINWIDGET_H