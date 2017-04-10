#include "confirmwindow.h"
#include "ui_confirmwindow.h"

confirmWindow::confirmWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::confirmWindow)
{
    ui->setupUi(this);
    ui->TeamNameLine->setText(NowMatch.TeamName);
    ui->NumberLine->setText(QString::number(NowMatch.Number));
    ui->TimeLine->setText(NowMatch.MatchTime.toString("mm:ss:zzz"));
    ui->FinalTimeLine->setText(NowMatch.FinalTime.toString("mm:ss:zzz"));
    ui->ChujieLine->setText(QString::number(NowMatch.Chujie));
    if(NowMatch.StopCar==true)
        ui->StopCarBox->setCurrentIndex(0);
    else
        ui->StopCarBox->setCurrentIndex(1);
    ui->TypeBox->setCurrentText(NowMatch.Type);

}

confirmWindow::~confirmWindow()
{
    delete ui;
}
