#ifndef ABOUTWINDOW_H
#define ABOUTWINDOW_H

#include <QDialog>
#include <QPixmap>

namespace Ui {
class AboutWindow;
}

class AboutWindow : public QDialog
{
    Q_OBJECT

public:
    explicit AboutWindow(QWidget *parent = 0);
    ~AboutWindow();

private slots:
    void webslot();
private:
    Ui::AboutWindow *ui;
    QPixmap *pix=new QPixmap;
};

#endif // ABOUTWINDOW_H
