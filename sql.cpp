#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMainWindow>
#include <QSerialPortInfo>//串口重要头文件
#include <QSerialPort>//串口重要头文件
#include <QIODevice>
#include <QTime>
#include <QTimer>
#include <QTimerEvent>
#include <QMessageBox>
#include <QDebug>
#include <QStandardItemModel>
#include <QtSql>
#include "data.h"
#include "addteam.h"
#include "ui_addteam.h"

void TeamInformation::SQLOpen()
{
    db=QSqlDatabase::addDatabase("QMYSQL");
    //db.setHostName("");
}
