#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "confirmwindow.h"
#include "ui_confirmwindow.h"
#include "addteam.h"
#include "ui_addteam.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect_init();//初始化连接
    Port_Scan();//端口扫描
    FinshMatch();//让系统处于上一场比赛结束状态，相当于初始化
    ui->ConfirmButton->setEnabled(false);
    ui->ChuJieButton->setEnabled(false);
    ui->StopFailButton->setEnabled(false);
    this->PunishTimes=0;
    ui->ChujieLine->setText("0");

    this->setMaximumSize(1440,810);
    this->setMinimumSize(1440,810);
}

MainWindow::~MainWindow()
{
    delete ui;

}

void MainWindow::connect_init()
{
    QObject::connect(ui->ChuanKouButton,SIGNAL(clicked(bool)),this,SLOT(Port_Init()));
    QObject::connect(ui->StartButton,SIGNAL(clicked()),this,SLOT(Start_Slot()));//开始按钮的槽
    QObject::connect(ui->ChuJieButton,SIGNAL(clicked()),this,SLOT(Punish_Slot()));
    QObject::connect(ui->StopFailButton,SIGNAL(clicked()),this,SLOT(StopFail_Slot()));
    QObject::connect(ui->AboutQtButton,SIGNAL(clicked()),qApp,SLOT(aboutQt()));
    QObject::connect(ui->ConfirmButton,SIGNAL(clicked()),this,SLOT(Push_Slot()));
    QObject::connect(ui->AddButton,SIGNAL(clicked(bool)),this,SLOT(AddTeam_Slot()));
}

void MainWindow::Push_Slot()
{
    this->FinshMatch();//完成比赛
    confirmWindow window;
    window.exec();
}

void MainWindow::AddTeam_Slot()
{
    AddTeam NewTeam;
    NewTeam.exec();
}
