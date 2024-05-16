#ifndef SCREENSHOTWIDGET_H
#define SCREENSHOTWIDGET_H
#include "QToolBar"
#include <QWidget>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QGuiApplication>
#include <QScreen>
#include <QPainter>
#include <QMouseEvent>
#include <QEvent>
#include <QLabel>
#include <QKeyEvent>
#include <QClipboard>
#include <QApplication>
#include "infolabel.h"
#include <QDebug>
#include "QPushButton"
#include <QtGui/QScreen>
#include <QMainWindow>
#include <QLabel>
#include <QDesktopWidget>
#include "QHBoxLayout"
#include <QWidget>
#include <QMenu>
#include <QPoint>
#include <QSize>
#include "QLineEdit"
#include "QPainterPath"
#include "tool_bar.h"
#include "QTextEdit"
#include "QUndoStack"
#include "QPainter"
#include "QStack"
#include "pinchartwindow.h"
#include "QMessageBox"
#include "imgocrclient.h"

// 一个宏，用于输出调试信息
#define Marge 5
#define cout qDebug() << "[文件:" << __FILE__<<"的第"<< __LINE__ << "行]输出:"

// Widget类，继承自QWidget
class ScreenShotwidget : public QWidget
{
    Q_OBJECT

public:
    // 构造函数
    ScreenShotwidget(QWidget *parent = nullptr);
    // 析构函数
    ~ScreenShotwidget();

private:
    // 初始化Widget
    void widgetInit();
    //工具栏
    void initToolBar();
    // 判断点是否在截图区域内
    int8_t pressAreaContains(QPoint p);
    // 边缘检测
    uint8_t edgeCheck(QPoint &nowPoint);
    // 标记当前截图区域
    void markCurrentRect();
    // 更新调整截图区域的矩形
    void updateAdjustAreaRects();
    // 退出截图
    void exitScreenshot(bool exit);
    // 设置当前光标
    void setCurrentCursor(uint8_t p);
    // 调整当前截图区域
    void adjustCurrentRect(QPoint now);
    // 显示截图信息
    void displayCaptureInfo(QPoint &p);


protected:
    // 绘制事件
    void paintEvent(QPaintEvent *event) override;
    // 键盘按下事件
    void keyPressEvent(QKeyEvent *event) override;
    // 键盘释放事件
    void keyReleaseEvent(QKeyEvent *event) override;
    // 事件处理
    bool event(QEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;



private:
    // 双击事件处理
    void doubleClickDeal();
    // 移动鼠标按钮事件处理
    void moveMouseButtonDeal();
    // 左键鼠标按钮事件处理
    void leftMouseButtonDeal();
    // Ctrl或C按键事件处理
    void CTRLOrCPressDeal(int value);
    // 方向键事件处理
    void directionKeyspressDeal(uint8_t value);
    bool eventFilter(QObject *object, QEvent *event);

public slots:
    //写字
    void onTextClicked();
    //画画
    void onLineClicked();
    //撤回
    void onUndoClicked();
    //马赛克
    void onMosaicClicked();
    //清空
    void onClearClicked();
    //钉图
    void onPinchartClicked();
    //ocr识别
    void onOcrClicked();

private:
    // 透明度
    uint8_t TranslateBit = 80;
    // 截图区域
    QRect CaptureRect;
    // 全屏图
    QPixmap pixmap;
    // 截取图
    QPixmap captruePixmap;
    // 调整截图区域
    QRect adjustAreaRects[8];
    // 按下的坐标
    QPoint PressPoint;
    // 原截图区的四个坐标
    QPoint LeftTop,RightBottom,LeftBottom,RightTop;
    // 鼠标是否按下
    bool mouse_pressed=false;
    // 鼠标点击的区域（这里指调节截图区大小的八个小正方形）
    uint8_t mouseArea;
    // 自定义Label（放大镜，取色器，文本显示）
    InfoLabel *labels;
    // 当前鼠标坐标
    QPoint now;
    // 按键检测栈
    QList<int> keys;

    Tool_bar *tool_bar_;//工具栏
    bool isDrawing; // 是否正在绘制
    // 马赛克点
    QVector<QPoint> mosaicPoints;
    // 是否正在绘制马赛克
    bool isDrawingMosaic;

    QVector<QPoint> linePoints; // 当前线的点
    QPainterPath linePath; // 线的路径
    QVector<QTextEdit*> textEdits;
    QStack<QString> operationStack;

    QStack<QVector<QPoint>> lineHistory;
    QStack<QTextEdit*> textEditsStack;
    QStack<QVector<QPoint>> mosaicHistory;


};
#endif // SCREENSHOTWIDGET_H
