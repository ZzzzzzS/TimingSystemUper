#include "mainwindow.h"
#include "ui_mainwindow.h"


/*============================================
函数名：MainWindow::Port_Scan()
作用：串口可用扫描
==========================================*/
void MainWindow::Port_Scan()
{
    QList<QSerialPortInfo>  infos;
    infos.clear();
    infos=QSerialPortInfo::availablePorts();

       if(infos.isEmpty())
       {
           ui->COMBox->addItem("无串口");
           ui->ChuanKouButton->setEnabled(false);
           return;
       }
       foreach (QSerialPortInfo info, infos)
       {
           ui->COMBox->addItem(info.portName());
       }
}

/*============================================
函数名：MainWindow::Port_Init()
作用：打开串口
==========================================*/


void MainWindow::Port_Init()
{
    if(ui->ChuanKouButton->text()==tr("打开串口"))
    {
        ui->ChuanKouButton->setEnabled(false);

        Port.setPortName(ui->COMBox->currentText());
            Port.open(QIODevice::ReadWrite);
            Port.setBaudRate(ui->SpeedBox->currentText().toInt());  //设置波特率
            switch(ui->SpeedBox->currentIndex())
            {
                case 0:
                    Port.setBaudRate(QSerialPort::Baud115200);
                    break;
                case 1:
                    Port.setBaudRate(QSerialPort::Baud57600);
                    break;
                case 2:
                    Port.setBaudRate(QSerialPort::Baud38400);
                    break;
                case 3:
                    Port.setBaudRate(QSerialPort::Baud19200);
                    break;
                case 4:
                    Port.setBaudRate(QSerialPort::Baud9600);
                    break;
            }
            switch(ui->DataBox->currentIndex())                     //设置数据位
            {
                case 0:
                    Port.setDataBits(QSerialPort::Data8);
                    break;
                case 1:
                    Port.setDataBits(QSerialPort::Data7);
                    break;
                case 2:
                    Port.setDataBits(QSerialPort::Data6);
                    break;
                case 3:
                    Port.setDataBits(QSerialPort::Data5);
                    break;
            }

            switch(ui->StopBox->currentIndex())                     //设置停止位
            {
                case 0:
                    Port.setStopBits(QSerialPort::OneStop);
                    break;
                case 1:
                    Port.setStopBits(QSerialPort::TwoStop);
                    break;
            }

            switch(ui->CheckBox->currentIndex())                    //设置效验位
            {
                case 0:
                    Port.setParity(QSerialPort::NoParity);
                    break;
                case 1:
                    Port.setParity(QSerialPort::OddParity);
                    break;
                case 2:
                    Port.setParity(QSerialPort::EvenParity);
                    break;
            }

            ui->COMBox->setEnabled(false);                          //禁用按钮
            ui->DataBox->setEnabled(false);
            ui->SpeedBox->setEnabled(false);
            ui->StopBox->setEnabled(false);
            ui->CheckBox->setEnabled(false);

            ui->ChuanKouButton->setText(tr("关闭串口"));               //设置开关键
            ui->ChuanKouButton->setEnabled(true);

            QObject::connect(&Port, &QSerialPort::readyRead, this, &MainWindow::Receive_Slot);
        }

    else
        {

            ui->COMBox->setEnabled(true);                          //启用按钮
            ui->DataBox->setEnabled(true);
            ui->SpeedBox->setEnabled(true);
            ui->StopBox->setEnabled(true);
            ui->CheckBox->setEnabled(true);

            Port.clear();                                           //关闭并删除串口
            Port.close();
            ui->ChuanKouButton->setText("打开串口");
        }
}

/*============================================
函数名：MainWindow::Receive_Slot()
作用：接收串口信息
==========================================*/

void MainWindow::Receive_Slot()
{
    int data[30];
    if(Port.bytesAvailable()>=10)
    {
        QByteArray buf;
        QString temp;
        for(int i=0;i<10;i++)
        {
            buf =Port.read(1);
            bool ok=true;
            temp=buf.toHex();
            data[i]=temp.toInt(&ok,16);
            buf.clear();
            temp.clear();
        }
        for(int i=0;i<10;i++)
        {
            if(data[i]==3&&data[i+1]==252)
            {
                //TODO 时间变化
            }
        }
    }
}

