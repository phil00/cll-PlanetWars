#ifndef SERVERMAIN_H
#define SERVERMAIN_H

#include <QMainWindow>

namespace Ui {
    class ServerMain;
}

class ServerMain : public QMainWindow
{
    Q_OBJECT

public:
    explicit ServerMain(QWidget *parent = 0);
    ~ServerMain();

private slots:
    void on_btnStartStop_clicked();

private:
    Ui::ServerMain *ui;
};

#endif // SERVERMAIN_H
