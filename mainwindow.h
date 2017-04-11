#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPortInfo>//串口重要头文件
#include <QSerialPort>//串口重要头文件
#include <QIODevice>
#include <QTime>
#include <QTimer>
#include <QTimerEvent>
#include <QMessageBox>
#include <QDebug>
#include "data.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void Receive_Slot();                            //接收串口信息
    void Port_Init();                               //打开串口时初始化
    void Start_Slot();                              //开始比赛的槽
    void Time_Out();                                //定时刷新
    void Punish_Slot();                             //罚时按钮槽
    void StopFail_Slot();                           //停车失败槽
    void AntiTouch_Slot();                          //防误触槽
    void Push_Slot();                               //提交比赛信息
    void AddTeam_Slot();                            //添加队伍

private:
    Ui::MainWindow *ui;

    QSerialPort Port;                               //串口对象
    QTime Time;                                     //主要计时器
    QTimer *ReNew=new QTimer(this);                 //定时刷新计时器
    int PunishTimes;                                //罚时次数

    void Port_Scan();                               //初始化串口
    void connect_init();                            //初始化各种连接
    void ReadyToRun();                              //准备比赛
    void ReadyToReady();                            //准备时间
    void FinshMatch();                              //完成比赛

};

#if _MSC_VER >= 1600                                //防止中文乱码
#pragma execution_character_set("utf-8")
#endif

#endif // MAINWINDOW_H
