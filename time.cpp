#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::Start_Slot()
{
    if(ui->StartButton->text()=="准备!")
    {
        this->ReNew->start(10);//1000毫秒刷新一次界面
        QObject::disconnect(this->ReNew,SIGNAL(timeout()),this,SLOT(Time_Out()));//先断开连接防止错误
        QObject::connect(this->ReNew,SIGNAL(timeout()),this,SLOT(Time_Out()));
        this->Time.setHMS(0,1,0,0);
        ui->TimeLine->setText("00:01:00");//先刷一次图
        ui->StartButton->setText(tr("就绪!"));
    }
    else if(ui->StartButton->text()=="就绪!")
    {
        this->ReNew->start(10);//1000毫秒刷新一次界面
        QObject::disconnect(this->ReNew,SIGNAL(timeout()),this,SLOT(Time_Out()));//connect前先断开连接，防止错误
        QObject::connect(this->ReNew,SIGNAL(timeout()),this,SLOT(Time_Out()));
        this->Time.setHMS(0,0,30,0);
        ui->TimeLine->setText("00:00:30");//先刷一次图
        ui->StartButton->setText(tr("发车!"));

    }
    else if(ui->StartButton->text()=="发车!")
    {
        this->ReNew->start(10);//10ms刷新界面
        QObject::disconnect(this->ReNew,SIGNAL(timeout()),this,SLOT(Time_Out()));//connect前先断开连接，防止错误
        QObject::connect(this->ReNew,SIGNAL(timeout()),this,SLOT(Time_Out()));
        this->Time.setHMS(0,0,0,0);
        ui->TimeLine->setText(this->Time.toString("m:ss:zz"));
        ui->StartButton->setText(tr("完成!"));
    }
    else if(ui->StartButton->text()=="完成!")
    {

    }
}

void MainWindow::Time_Out()
{
    if(ui->StartButton->text()=="就绪!")
    {
        this->Time=this->Time.addMSecs(-10);
        if(this->Time<=QTime(0,0,0,0))
        {
            Start_Slot();
            return;
        }
        ui->TimeLine->setText(this->Time.toString("mm:ss:"));
        ui->TimeLine_MS->setText(this->Time.toString("zzz"));

    }
    else if(ui->StartButton->text()=="发车!")
    {
        this->Time=this->Time.addMSecs(-10);
        if(this->Time<=QTime(0,0,0,0))
        {
            //TODO罚时并开始比赛
            return;
        }
        ui->TimeLine->setText(this->Time.toString("mm:ss:"));
        ui->TimeLine_MS->setText(this->Time.toString("zzz"));
    }
    else if(ui->StartButton->text()=="完成!")
    {
        this->Time=this->Time.addMSecs(10);
        ui->TimeLine->setText(this->Time.toString("mm:ss:"));
        ui->TimeLine_MS->setText(this->Time.toString("zzz"));
    }
}
