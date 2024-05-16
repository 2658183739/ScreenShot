#include "screenshot.h"
#include "ui_screenshot.h"
#include "ScreenShotwidget.h"
ScreenShot::ScreenShot(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ScreenShot)
{
    ui->setupUi(this);

}

ScreenShot::~ScreenShot()
{
    delete ui;
}

void ScreenShot::on_pushButton_clicked()
{
    ScreenShotwidget *screen = new ScreenShotwidget();
    screen->show();


}

