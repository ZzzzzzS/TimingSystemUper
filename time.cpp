﻿#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::Start_Slot()
{
    if(ui->StartButton->text()=="准备!")
    {
        if(ui->ChuanKouButton->text()=="打开串口")
        {
            if(QMessageBox::No==QMessageBox::question(this,"串口可能未打开","串口未打开，您确定不需要打开吗",QMessageBox::Yes,QMessageBox::No))
                return;
        }


        this->ReNew->start(10);//1000毫秒刷新一次界面

        QObject::disconnect(this->ReNew,SIGNAL(timeout()),this,SLOT(Time_Out()));//先断开连接防止错误
        QObject::connect(this->ReNew,SIGNAL(timeout()),this,SLOT(Time_Out()));

        this->Time.setHMS(0,1,0,0);
        ui->TimeLine->setText("00:01:00");//先刷一次图

        this->ReadyToReady();//准备时间
        ui->AddButton->setEnabled(false);
        ui->NextTeamButton->setEnabled(false);
        ui->LastTeamButton->setEnabled(false);
        ui->StartButton->setText(tr("就绪!"));
    }
    else if(ui->StartButton->text()=="就绪!"||ui->StartButton->text()=="重跑!")
    {
        this->ReNew->start(10);//10毫秒刷新一次界面

        QObject::disconnect(this->ReNew,SIGNAL(timeout()),this,SLOT(Time_Out()));//connect前先断开连接，防止错误
        QObject::connect(this->ReNew,SIGNAL(timeout()),this,SLOT(Time_Out()));

        this->Time.setHMS(0,0,30,0);
        ui->TimeLine->setText("00:00:30");//先刷一次图

        this->ReadyToReady();//准备时间
        ui->StartButton->setText(tr("发车!"));

    }
    else if(ui->StartButton->text()=="发车!")
    {
        this->ReNew->start(10);//10ms刷新界面

        QObject::disconnect(this->ReNew,SIGNAL(timeout()),this,SLOT(Time_Out()));//connect前先断开连接，防止错误
        QObject::connect(this->ReNew,SIGNAL(timeout()),this,SLOT(Time_Out()));

        this->Time.setHMS(0,0,0,0);
        ui->TimeLine->setText(this->Time.toString("mm:ss:zz"));

        this->ReadyToRun();//初始化各连接，准备比赛
        ui->StartButton->setText(tr("完成!"));
    }
    else if(ui->StartButton->text()=="完成!")
    {
        this->ReNew->stop();
        QObject::disconnect(this->ReNew,SIGNAL(timeout()),this,SLOT(Time_Out()));
        ui->TimeLine->setText(this->Time.toString("mm:ss:"));//再刷一次图
        ui->TimeLine_MS->setText(this->Time.toString("zzz"));//再刷一次图

        ui->StartButton->setText("重跑!");
        ui->StartButton->setEnabled(false);//放误触发
        ui->ConfirmButton->setEnabled(true);
        ui->AddButton->setEnabled(true);

        this->ReNew->start(2000);
        QObject::connect(this->ReNew,SIGNAL(timeout()),this,SLOT(AntiTouch_Slot()));

    }
}

void MainWindow::Time_Out()
{
    if(ui->StartButton->text()=="就绪!")
    {
        if(ui->PauseButton->text()=="继续")
            return;//暂停功能

        this->Time=this->Time.addMSecs(-10);
        if(this->Time<=QTime(0,0,0,0))
        {
            Start_Slot();
            return;
        }
        ui->TimeLine->setText(this->Time.toString("mm:ss:"));
        ui->TimeLine_MS->setText(this->Time.toString("zzz"));

        if(this->Time>QTime(0,0,58,0))
            ui->StartButton->setEnabled(false);//防止误触发
        else
            ui->StartButton->setEnabled(true);

    }
    else if(ui->StartButton->text()=="发车!")
    {
        if(ui->PauseButton->text()=="继续")
            return;//暂停功能

        this->Time=this->Time.addMSecs(-10);
        if(this->Time<=QTime(0,0,0,0))
        {

            Start_Slot();
            PunishTimes++;//超时不发车自动发车，并罚时
            ui->ChujieLine->setText(QString::number(this->PunishTimes));//刷新显示
            return;
        }
        ui->TimeLine->setText(this->Time.toString("mm:ss:"));
        ui->TimeLine_MS->setText(this->Time.toString("zzz"));

        if(this->Time>QTime(0,0,28,0))
            ui->StartButton->setEnabled(false);//防止误触发
        else
            ui->StartButton->setEnabled(true);

    }
    else if(ui->StartButton->text()=="完成!")
    {
        if(ui->PauseButton->text()=="继续")
            return;//暂停功能

        this->Time=this->Time.addMSecs(10);
        ui->TimeLine->setText(this->Time.toString("mm:ss:"));
        ui->TimeLine_MS->setText(this->Time.toString("zzz"));

        if(this->Time<=QTime(0,0,2,0))
            ui->StartButton->setEnabled(false);//防止误触发
        else
            ui->StartButton->setEnabled(true);
    }
}

void MainWindow::AntiTouch_Slot()
{
    ui->StartButton->setEnabled(true);
    this->ReNew->stop();
    QObject::disconnect(this->ReNew,SIGNAL(timeout()),this,SLOT(AntiTouch_Slot()));
}
