#ifndef SCREENSHOT_H
#define SCREENSHOT_H
#include <QMainWindow>
#pragma execution_character_set("utf-8")
QT_BEGIN_NAMESPACE
namespace Ui {
class ScreenShot;
}
QT_END_NAMESPACE

class ScreenShot : public QMainWindow
{
    Q_OBJECT

public:
    ScreenShot(QWidget *parent = nullptr);
    ~ScreenShot();
private slots:
    void on_pushButton_clicked();
signals:
    void shot();
private:
    Ui::ScreenShot *ui;
};
#endif // SCREENSHOT_H
