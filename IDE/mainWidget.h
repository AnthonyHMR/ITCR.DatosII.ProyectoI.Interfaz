#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include "jsonConverter.h"
#include <QTcpSocket>
#include <messageGenerator.h>

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
    void getInstance();
    void showError();
    QTcpSocket *mSocket;
    messageGenerator *json;
    enum Columna {
        Address, Value, Label, References
    };
};

#endif // MAINWIDGET_H
