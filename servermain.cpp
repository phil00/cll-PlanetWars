#include "servermain.h"
#include "ui_servermain.h"

ServerMain::ServerMain(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ServerMain)
{
    ui->setupUi(this);
    TcpServ = new QTcpServer();
    TcpServ->listen(QHostAddress::Any, 35994);
    time = new QTimer();
    connect(time, SIGNAL(timeout()), this, SLOT(on_time_TimeOut()));
    connect(TcpServ,SIGNAL(newConnection()), this, SLOT(on_TcpServ_NewConnection()));
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
        time->start(42);
    }
    else
    {
        ui->btnStartStop->setText("Start");
        time->stop();
    }
}

void ServerMain::on_time_TimeOut()
{
    emit(newTime());
}

void ServerMain::on_TcpServ_NewConnection()
{
    m_thServeur = new thServeur();
    connect(this, SIGNAL(newTime()), m_thServeur, SLOT(on_time_newTime()));
    ui->sbNbUtilisateur->setValue(ui->sbNbUtilisateur->value() + 1);
    m_thServeur->sockServeur = TcpServ->nextPendingConnection();
    m_thServeur->start();
}

void ServerMain::on_pushButton_clicked()
{
    int yo[30];
    for(int i; i<30;i++)
    {
        yo[i]=QString(ui->lineEdit_3->text()[i]).toInt();
    }
    Paquet *p = new Paquet(50, 49,yo);
    QByteArray b = p->ToByteArray();
    p->FromByteArray(b);
}
