#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect_init();//初始化连接
    Port_Scan();//端口扫描
    FinshMatch();//让系统处于上一场比赛结束状态，相当于初始化
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
}

