#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::ReadyToRun()
{
    ui->StopFailButton->setEnabled(true);
    ui->ChuJieButton->setEnabled(true);
    PunishTimes=0;
    ui->ChujieLine->setText(QString::number(this->PunishTimes));
    ui->ConfirmButton->setEnabled(false);
}

void MainWindow::FinshMatch()
{
    NowMatch.MatchTime=this->Time;
    bool ok=true;
    NowMatch.Chujie=ui->ChujieLine->text().toInt(&ok,10);

    if(ui->StopFailButton->text()=="停车失败")
        NowMatch.StopCar=true;
    else if(ui->StopFailButton->text()=="停车成功")
        NowMatch.StopCar=false;
    NowMatch.FinalTime=this->Time;
    NowMatch.FinalTime=NowMatch.FinalTime.addSecs(NowMatch.Chujie);
    if(NowMatch.StopCar==false)
        NowMatch.FinalTime=NowMatch.FinalTime.addSecs(1);

    ui->ChujieLine->setText(QString::number(this->PunishTimes));
}

void MainWindow::ReadyToReady()
{
    ui->ChuJieButton->setEnabled(false);
    ui->StopFailButton->setEnabled(false);
    PunishTimes=0;
    ui->ChujieLine->setText(QString::number(this->PunishTimes));
    ui->ConfirmButton->setEnabled(false);

    ui->NameLine->setText(NowMatch.TeamName);
    ui->NumberLine->setText(QString::number(NowMatch.Number));
    ui->TypeName->setText(NowMatch.Type);
}

void MainWindow::StopFail_Slot()
{
    if(ui->StopFailButton->text()=="停车失败")
        ui->StopFailButton->setText("停车成功");
    else if(ui->StopFailButton->text()=="停车成功")
        ui->StopFailButton->setText("停车失败");
}
