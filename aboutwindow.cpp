#include "aboutwindow.h"
#include "ui_aboutwindow.h"
#include <QDesktopServices>
#include <QUrl>
#include <QPixmap>

AboutWindow::AboutWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutWindow)
{
    ui->setupUi(this);

    this->setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint|Qt::Popup);

    this->setMinimumSize(360,120);
    this->setMaximumSize(360,120);
    this->setWindowTitle("718 Innovation Lab");

    this->pix->load("logo.jpg");
    ui->label->setPixmap(this->pix->scaled(ui->label->size()));
    ui->label->show();

    QObject::connect(ui->pushButton_2,SIGNAL(clicked()),this,SLOT(close()));
    QObject::connect(ui->pushButton,SIGNAL(clicked(bool)),this,SLOT(webslot()));
    QObject::connect(ui->QtButton,SIGNAL(clicked(bool)),qApp,SLOT(aboutQt()));
}

AboutWindow::~AboutWindow()
{
    delete ui;
}

void AboutWindow::webslot()
{
    QDesktopServices::openUrl(QUrl(QLatin1String("https://git.oschina.net/code.zzs/opto-electronic_timing_system")));
}
