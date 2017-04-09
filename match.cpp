#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::ReadyToRun()
{
    ui->StopFailButton->setEnabled(true);
    ui->ChuJieButton->setEnabled(true);
    PunishTimes=0;
    ui->ChujieLine->setText(QString::number(this->PunishTimes));
}

void MainWindow::FinshMatch()
{
    ui->StartButton->setText("准备!");
    ui->ChuJieButton->setEnabled(false);
    ui->StopFailButton->setEnabled(false);
    ui->StopFailButton->setText("停车失败");
    PunishTimes=0;
    ui->ChujieLine->setText(QString::number(this->PunishTimes));
}

void MainWindow::ReadyToReady()
{
    ui->ChuJieButton->setEnabled(false);
    ui->StopFailButton->setEnabled(false);
    PunishTimes=0;
    ui->ChujieLine->setText(QString::number(this->PunishTimes));
}

void MainWindow::StopFail_Slot()
{
    if(ui->StopFailButton->text()=="停车失败")
        ui->StopFailButton->setText("停车成功");
    else if(ui->StopFailButton->text()=="停车成功")
        ui->StopFailButton->setText("停车失败");
}
