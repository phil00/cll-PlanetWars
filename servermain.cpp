#include "servermain.h"
#include "ui_servermain.h"

ServerMain::ServerMain(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ServerMain)
{
    ui->setupUi(this);
    connect(time, SIGNAL(timeout()), this, SLOT(on_time_TimeOut()));
    connect(this, SIGNAL(newTime()), m_thServeur, SLOT(on_time_newTime()));
}

ServerMain::~ServerMain()
{
    delete ui;
}

void ServerMain::on_btnStartStop_clicked()
{
    if(ui->btnStartStop->text() == "Start")
    {
        ui->btnStartStop->setText("Stop");
        m_thServeur->start();
        time->start(42);
    }
    else
    {
        ui->btnStartStop->setText("Start");
        m_thServeur->terminate();
        m_thServeur->wait();
        time->stop();
    }
}

void ServerMain::on_time_TimeOut()
{
    emit(newTime());
}
