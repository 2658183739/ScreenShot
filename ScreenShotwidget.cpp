#include "QToolBar"
#include "ScreenShotwidget.h"
ScreenShotwidget::~ScreenShotwidget()
{

}

ScreenShotwidget::ScreenShotwidget(QWidget *parent)
    : QWidget(parent)
{
    widgetInit();
    isDrawing = 0;
    isDrawingMosaic = 0;
    // 创建工具栏
    tool_bar_ = new Tool_bar(this);
    tool_bar_->setWindowFlags(Qt::FramelessWindowHint); // 设置无边框窗口
    tool_bar_->setStyleSheet("background-color: white;"); // 设置背景色为白色
    QHBoxLayout *layout = new QHBoxLayout(tool_bar_);
    layout->setMargin(5); // 设置边距
    layout->setSpacing(5); // 设置间距
    tool_bar_->setStyleSheet("QWidget { background-color: white; } QPushButton { background-color: #4CAF50; }");


    // 创建按钮
    QPushButton *undo = new QPushButton("撤回", tool_bar_);
    QPushButton *text = new QPushButton("文字", tool_bar_);
    QPushButton *line = new QPushButton("线段", tool_bar_);
    QPushButton *mosaic = new QPushButton("马赛克", tool_bar_);
    QPushButton *pinchart = new QPushButton("钉图", tool_bar_);
    QPushButton *clear = new QPushButton("清空痕迹", tool_bar_);
    QPushButton *ocr = new QPushButton("OCR", tool_bar_);


    // 连接按钮点击事件到槽函数
    connect(undo, &QPushButton::clicked, this, &ScreenShotwidget::onUndoClicked);
    connect(text, &QPushButton::clicked, this, &ScreenShotwidget::onTextClicked);
    connect(line, &QPushButton::clicked, this, &ScreenShotwidget::onLineClicked);
    connect(mosaic, &QPushButton::clicked, this, &ScreenShotwidget::onMosaicClicked);
    connect(clear, &QPushButton::clicked, this, &ScreenShotwidget::onClearClicked);
    connect(pinchart, &QPushButton::clicked, this, &ScreenShotwidget::onPinchartClicked);
    connect(ocr, &QPushButton::clicked, this, &ScreenShotwidget::onOcrClicked);

    // 设置按钮样式
    QString buttonStyle = "QPushButton {"
                          "background-color: #4CAF50;"
                          "border: none;"
                          "color: white;"
                          "padding: 10px 24px;"
                          "text-align: center;"
                          "text-decoration: none;"
                          "font-size: 16px;"
                          "margin: 4px 2px;"
                          "}";
    undo->setStyleSheet(buttonStyle);
    text->setStyleSheet(buttonStyle);
    line->setStyleSheet(buttonStyle);
    mosaic->setStyleSheet(buttonStyle);
    clear->setStyleSheet(buttonStyle);
    pinchart->setStyleSheet(buttonStyle);
    ocr->setStyleSheet(buttonStyle);


    // 将按钮添加到布局
    layout->addWidget(undo);
    layout->addWidget(text);
    layout->addWidget(line);
    layout->addWidget(mosaic);
    layout->addWidget(clear);
    layout->addWidget(pinchart);
    layout->addWidget(ocr);

    // 设置工具栏布局
    tool_bar_->setLayout(layout);

}

void ScreenShotwidget::onOcrClicked()
{
    this->hide();
    labels->close();

    ImgOcrClient * img = new ImgOcrClient();

    // 创建一个新的 pixmap 来存储截图和所有线
    QPixmap tempPixmap(CaptureRect.width(), CaptureRect.height());
    QPainter painter(&tempPixmap);
    // 绘制整个 pixmap 到 tempPixmap
    painter.drawPixmap(-CaptureRect.x(), -CaptureRect.y(), pixmap);
    // 绘制所有线到 tempPixmap
    painter.setPen(QPen(Qt::red, 2));
    foreach (const QVector<QPoint> &line, lineHistory) {
        QPainterPath path;
        path.addPolygon(QPolygon(line));
        painter.drawPath(path);
    }
    if (isDrawing) {
        QPainterPath path;
        path.addPolygon(QPolygon(linePoints));
        painter.drawPath(path);
    }
    // 绘制所有马赛克点到 tempPixmap
    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::blue); // 设置马赛克点的颜色
    for (int i = 0; i < mosaicHistory.size(); i++) {
        for (int j = 0; j < mosaicHistory[i].size(); j++) {
            painter.drawRect(mosaicHistory[i][j].x(), mosaicHistory[i][j].y(), 10, 10); // 绘制马赛克点
        }
    }
    // 绘制所有文本到 tempPixmap
    foreach (QTextEdit *textEdit, textEdits) {
        painter.save();
        painter.translate(textEdit->x(), textEdit->y());
        painter.setRenderHint(QPainter::TextAntialiasing);
        painter.setPen(Qt::black); // 设置文本颜色
        painter.drawText(0, 0, textEdit->width(), textEdit->height(), Qt::AlignCenter, textEdit->toPlainText());
        painter.restore();
    }
    QStringList strlist = img->makeOcrRequest(tempPixmap);


    QTextEdit *textEdit = new QTextEdit();
    textEdit->setReadOnly(true);
    textEdit->setWindowTitle("OCR Result");

    foreach (const QString &str, strlist) {
        textEdit->append(str);
        textEdit->append("\n"); // 添加换行符
    }

    textEdit->show();

}
void ScreenShotwidget::onPinchartClicked()
{
    this->hide();
    labels->close();

    PinChartWindow* pinChartWindow = new PinChartWindow(); // Declare and initialize the variable
    pinChartWindow->setWindowTitle("钉图");

    // 创建一个新的 pixmap 来存储截图和所有线
    QPixmap tempPixmap(CaptureRect.width(), CaptureRect.height());
    QPainter painter(&tempPixmap);
    // 绘制整个 pixmap 到 tempPixmap
    painter.drawPixmap(-CaptureRect.x(), -CaptureRect.y(), pixmap);
    // 绘制所有线到 tempPixmap
    painter.setPen(QPen(Qt::red, 2));
    foreach (const QVector<QPoint> &line, lineHistory) {
        QPainterPath path;
        path.addPolygon(QPolygon(line));
        painter.drawPath(path);
    }
    if (isDrawing) {
        QPainterPath path;
        path.addPolygon(QPolygon(linePoints));
        painter.drawPath(path);
    }
    // 绘制所有马赛克点到 tempPixmap
    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::blue); // 设置马赛克点的颜色
    for (int i = 0; i < mosaicHistory.size(); i++) {
        for (int j = 0; j < mosaicHistory[i].size(); j++) {
            painter.drawRect(mosaicHistory[i][j].x(), mosaicHistory[i][j].y(), 10, 10); // 绘制马赛克点
        }
    }
    // 绘制所有文本到 tempPixmap
    foreach (QTextEdit *textEdit, textEdits) {
        painter.save();
        painter.translate(textEdit->x(), textEdit->y());
        painter.setRenderHint(QPainter::TextAntialiasing);
        painter.setPen(Qt::black); // 设置文本颜色
        painter.drawText(0, 0, textEdit->width(), textEdit->height(), Qt::AlignCenter, textEdit->toPlainText());
        painter.restore();
    }

    pinChartWindow->setImage(tempPixmap);
    pinChartWindow->show();

}


void ScreenShotwidget::onClearClicked()
{
    // Clear all mosaic points
    mosaicHistory.clear();
    mosaicPoints.clear();
    isDrawingMosaic = false;

    // Clear all text edits
    foreach (QTextEdit *textEdit, textEdits) {
        textEdit->deleteLater();
    }
    textEdits.clear();
    textEditsStack.clear();

    // Clear all line segments
    lineHistory.clear();
    linePoints.clear();
    isDrawing = false;

    // Clear the operation stack
    operationStack.clear();

    // Update the screenshot page
    update();

}


void ScreenShotwidget::onUndoClicked() {
    if (!operationStack.isEmpty()) {
        QString opType = operationStack.pop();
        if (opType == "line") {
            lineHistory.removeLast();
        } else if (opType == "text") {
            QTextEdit* textEdit = textEditsStack.pop();
            textEdit->deleteLater();
        } else if (opType == "mosaic") {
            mosaicHistory.removeLast();
        }
        update(); // 更新小部件以反映撤销的操作
    }
}

void ScreenShotwidget::onTextClicked()
{

    // 创建一个文本编辑框
    QTextEdit *textEdit = new QTextEdit(this);

    // 设置文本编辑框的初始位置到截图范围的中心
    int centerX = CaptureRect.x() + CaptureRect.width() / 2;
    int centerY = CaptureRect.y() + CaptureRect.height() / 2;
    textEdit->setGeometry(centerX - 100, centerY - 25, 200, 50); // 设置初始位置和大小

    textEdit->setStyleSheet("background-color: transparent; border: 1px solid red; font-size: 25px;");
    textEdit->setFocus(); // 设置焦点

    // 添加文本编辑框到列表
    textEdits.append(textEdit);
    textEditsStack.push(textEdit);
    operationStack.push("text");

    // 设置文本编辑框可移动
    textEdit->setMouseTracking(true);
    textEdit->installEventFilter(this);

    // 显示文本编辑框
    textEdit->show();
}


bool ScreenShotwidget::eventFilter(QObject *object, QEvent *event)
{

    if (event->type() == QEvent::MouseMove) {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
        for (QTextEdit *textEdit : textEdits) {
            if (object == textEdit && mouseEvent->buttons() & Qt::LeftButton) {
                // 移动文本编辑框
                textEdit->move(textEdit->x() + mouseEvent->x(), textEdit->y() + mouseEvent->y());
                return true;
            }
        }
    }
    return false;
}
void ScreenShotwidget::onMosaicClicked()
{
    // 设置鼠标跟踪模式以启用鼠标移动事件
    setMouseTracking(true);
    isDrawingMosaic = true; // 添加一个标志来指示是否正在绘制马赛克
    mosaicPoints.clear();
    operationStack.push("mosaic");

}

void ScreenShotwidget::onLineClicked()
{
    // 设置鼠标跟踪模式以启用鼠标移动事件
    setMouseTracking(true);
    isDrawing = true; // 添加一个标志来指示是否正在绘制
    linePoints.clear();
    operationStack.push("line");
}


void ScreenShotwidget::mousePressEvent(QMouseEvent *event) {
    if (isDrawing && event->button() == Qt::LeftButton) {
        // 开始绘制一条新线
        linePoints.clear();
        linePoints.append(event->pos());
    }
    if (isDrawingMosaic && event->button() == Qt::LeftButton) {
        // 开始绘制一块马赛克
        mosaicPoints.clear();
        mosaicPoints.append(event->pos());
    }
}

void ScreenShotwidget::mouseMoveEvent(QMouseEvent *event) {
    if (isDrawing && event->buttons() & Qt::LeftButton) {
        linePoints.append(event->pos());
        update(); // Trigger a repaint
    }

    if (isDrawingMosaic && event->buttons() & Qt::LeftButton) {
        // 添加一个新点到马赛克中
        mosaicPoints.append(event->pos());
        update(); // 更新小部件以重绘马赛克
    }
}

void ScreenShotwidget::mouseReleaseEvent(QMouseEvent *event) {
    if (isDrawing && event->button() == Qt::LeftButton) {
        // 完成绘制线
        isDrawing = false;
        lineHistory.append(linePoints); // 将当前线添加到历史记录中
        update(); // 触发重绘
    }
    if (isDrawingMosaic && event->button() == Qt::LeftButton) {
        isDrawingMosaic = false;
        mosaicHistory.append(mosaicPoints); // Add the finished mosaicPoints vector to the history
        update(); // Trigger a repaint
    }
}


void ScreenShotwidget::initToolBar()
{
    QPoint toolBarMove;
    // 获取截图区域的几何范围
    QRect captureRect = CaptureRect;
    // 获取工具栏的尺寸
    int toolBarWidth = tool_bar_->width();
    int toolBarHeight = tool_bar_->height();
    // 计算工具栏的位置，放置在截图的右上角
    int toolBarX = captureRect.x() + captureRect.width() - toolBarWidth;
    int toolBarY = captureRect.y();
    // 设置工具栏的位置
    toolBarMove = QPoint(toolBarX, toolBarY);
    tool_bar_->move(toolBarMove);
    tool_bar_->show();
    this->update();
}


void ScreenShotwidget::paintEvent(QPaintEvent *){

    QPainter painter(this);
    painter.drawPixmap(this->rect(), pixmap); // 画出原画
    painter.fillRect(this->rect(), QColor(0, 0, 0, TranslateBit)); // 填充透明黑色 透明度默认80
    if (CaptureRect.isValid()) { // isValid()是Qt自带函数 == 用于判断区域是否有效（即区域面积为空就无效）
        painter.drawPixmap(CaptureRect, pixmap.copy(CaptureRect)); // 画局部图
        painter.setPen(QPen(QColor(0, 180, 180), Qt::SolidLine)); // 绿色实线
        painter.drawRect(CaptureRect); // 画矩形框
        for (QRect rect : adjustAreaRects) // 画八个小正方形 这是调整截图区大小的区域
            painter.fillRect(rect, QColor(0, 180, 180));
    }


    // 绘制马赛克
    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::blue); // 设置马赛克的颜色
    for (int i = 0; i < mosaicHistory.size(); i++) {
        for (int j = 0; j < mosaicHistory[i].size(); j++) {
            painter.drawRect(mosaicHistory[i][j].x(), mosaicHistory[i][j].y(), 10, 10); // 绘制马赛克点
        }
    }
    if (isDrawingMosaic) {
        painter.setPen(Qt::NoPen);
        painter.setBrush(Qt::blue); // 设置马赛克的颜色
        for (int i = 0; i < mosaicPoints.size(); i++) {
            painter.drawRect(mosaicPoints[i].x(), mosaicPoints[i].y(), 10, 10); // 绘制一个小方块
        }
    }

    // 绘制红色线
    painter.setPen(QPen(Qt::red, 2));
    foreach (const QVector<QPoint> &line, lineHistory) {
        painter.drawPolyline(line);
    }

    if (isDrawing) {
        painter.drawPolyline(linePoints);
        // 绘制线条路径
        painter.drawPath(linePath);
    }

}


// 处理键盘按下事件
void ScreenShotwidget::keyPressEvent(QKeyEvent *event){
    int value = event->key();
    cout<<event->key();
    // 左上右下分别为：16777234 16777235 16777236 16777237 都减去16777234后 变成1 2 3 4
    ScreenShotwidget::directionKeyspressDeal(value - 16777234);
    if(!event->isAutoRepeat()) keys.append(value);          // 非重复键入栈
    ScreenShotwidget::CTRLOrCPressDeal(value);
}

// 处理键盘释放事件
void ScreenShotwidget::keyReleaseEvent(QKeyEvent *event)
{
    if(!event->isAutoRepeat()) keys.removeOne(event->key());// 松开的键出栈
    if(16777216==event->key())          // Esc
        ScreenShotwidget::exitScreenshot(false);
}

// 处理鼠标事件
bool ScreenShotwidget::event(QEvent *event){
    QMouseEvent *e = static_cast<QMouseEvent*>(event);
    if(event->type()==QEvent::MouseButtonDblClick){
        ScreenShotwidget::doubleClickDeal();
    }
    else if(event->type()==QEvent::MouseButtonPress){
        PressPoint = e->pos();
        if(e->button()==Qt::LeftButton){
            mouse_pressed = true;     // 按下标志置为真
            ScreenShotwidget::leftMouseButtonDeal();
        }
    }
    else if (event->type()==QEvent::MouseMove) {
        now = e->pos();
        ScreenShotwidget::moveMouseButtonDeal();
    }
    else if (event->type()==QEvent::MouseButtonRelease && e->button()==Qt::LeftButton) {
        mouse_pressed = false;    // 按下标志置为假
    }
    return QWidget::event(event);
}

void ScreenShotwidget::doubleClickDeal()
{
    // 获取系统剪切板对象
    QClipboard *clipboard = QGuiApplication::clipboard();
    // 创建一个新的 pixmap 来存储截图和所有线
    QPixmap tempPixmap(CaptureRect.width(), CaptureRect.height());
    QPainter painter(&tempPixmap);
    // 绘制整个 pixmap 到 tempPixmap
    painter.drawPixmap(-CaptureRect.x(), -CaptureRect.y(), pixmap);
    // 绘制所有线到 tempPixmap
    painter.setPen(QPen(Qt::red, 2));
    foreach (const QVector<QPoint> &line, lineHistory) {
        QPainterPath path;
        path.addPolygon(QPolygon(line));
        painter.drawPath(path);
    }
    if (isDrawing) {
        QPainterPath path;
        path.addPolygon(QPolygon(linePoints));
        painter.drawPath(path);
    }
    // 绘制所有马赛克点到 tempPixmap
    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::blue); // 设置马赛克点的颜色
    for (int i = 0; i < mosaicHistory.size(); i++) {
        for (int j = 0; j < mosaicHistory[i].size(); j++) {
            painter.drawRect(mosaicHistory[i][j].x(), mosaicHistory[i][j].y(), 10, 10); // 绘制马赛克点
        }
    }
    // 绘制所有文本到 tempPixmap
    foreach (QTextEdit *textEdit, textEdits) {
        painter.save();
        painter.translate(textEdit->x(), textEdit->y());
        painter.setRenderHint(QPainter::TextAntialiasing);
        painter.setPen(Qt::black); // 设置文本颜色
        painter.drawText(0, 0, textEdit->width(), textEdit->height(), Qt::AlignCenter, textEdit->toPlainText());
        painter.restore();
    }
    // 将 tempPixmap 设置到剪切板
    clipboard->setPixmap(tempPixmap);
    // 退出截图模式
    ScreenShotwidget::exitScreenshot(true);
}

// 鼠标移动处理 - 更新放大镜、RGB、截图区长宽显示信息 and 移动截图区\调整截图区 and 设置鼠标样式
void ScreenShotwidget::moveMouseButtonDeal()
{
    if (mouse_pressed &&!tool_bar_->isHidden()) {
        QRect toolBarRect = tool_bar_->geometry();
        int dx = now.x() - toolBarRect.x();
        int dy = now.y() - toolBarRect.y();
        if (qAbs(dx) < 10 && qAbs(dy) < 10) {
            // Cursor is within 10 pixels of the tool bar boundary, ignore event
            return;
        }
    }

    if (!lineHistory.isEmpty() || isDrawing || !textEdits.isEmpty() || isDrawingMosaic || !mosaicHistory.isEmpty()) {
        // 如果有红色的痕迹路径，不允许拖动图像
        return;
    }

    // Rest of the code remains the same
    ScreenShotwidget::displayCaptureInfo(now);
    if (mouse_pressed) {
        ScreenShotwidget::adjustCurrentRect(now);
        ScreenShotwidget::updateAdjustAreaRects();
        repaint();
    } else {
        ScreenShotwidget::setCurrentCursor(pressAreaContains(now));
    }

}

// 鼠标左键点击处理 - 创建截图区 或 标记截图区
void ScreenShotwidget::leftMouseButtonDeal()
{
    if(!CaptureRect.isValid()){                     // 若截取图不存在 则先创建截图区
        LeftTop = PressPoint;
        CaptureRect = QRect(LeftTop,LeftTop);       // 等同于左上角与右下角重合在鼠标按下的位置
        mouseArea = 8;                              // 等同于按在了右下角（调节区域第8个方框）
        ScreenShotwidget::displayCaptureInfo(LeftTop);
        if(!labels->isVisible()) labels->show();

        //initToolBar();
    }
    else {
        ScreenShotwidget::markCurrentRect();                  // 标记当前窗口四个角
        mouseArea = pressAreaContains(PressPoint);  // 返回0代表在截图区中间按下 返回1-8代表在对应的调节区域按下
    }
}


// 键盘按下C或ctrl或其组合的处理 - 复制10进制RGB 显示16进制RGB 复制16进制RGB
void ScreenShotwidget::CTRLOrCPressDeal(int value)
{
    QColor color = pixmap.toImage().pixelColor(now);
    if(67==value) {// 按下了 'c'
        QClipboard *clipboard = QGuiApplication::clipboard();
        if(!keys.contains(16777249)){   // 如果是按下了组合键 ctrl+c 则复制 十六进制的rgb值
            clipboard->setText(QString("%1,%2,%3").arg(color.red()).arg(color.green()).arg(color.blue()));
        } else{
            clipboard->setText(QString("#%1%2%3").arg(color.red(),2,16,QLatin1Char('0')).arg(color.green(),2,16,QLatin1Char('0')).arg(color.blue(),2,16,QLatin1Char('0')));
        }
    }
    else if(16777249==value){ // 按下了 'ctrl'
        QString str1 = QString("长×宽:%1×%2\n").arg(CaptureRect.width()).arg(CaptureRect.height());
        QString str2 = QString("RGB:#%1%2%3\n按C复制RGB色号\n右键返回或退出截图").arg(color.red(),2,16,QLatin1Char('0')).arg(color.green(),2,16,QLatin1Char('0')).arg(color.blue(),2,16,QLatin1Char('0'));
        labels->setTextLabel(str1+str2);
    }
}

// 键盘方向键按下处理 - 微调截图区
void ScreenShotwidget::directionKeyspressDeal(uint8_t value)
{
    switch (value) {
    case 0:
        if(CaptureRect.x()>0)
            CaptureRect.adjust(-1,0,-1,0);
        break;
    case 1:
        if(CaptureRect.y()>0)
            CaptureRect.adjust(0,-1,0,-1);
        break;
    case 2:
        if(CaptureRect.x()<this->width()-CaptureRect.width())
            CaptureRect.adjust(1,0,1,0);
        break;
    case 3:
        if(CaptureRect.y()<this->height()-CaptureRect.height())
            CaptureRect.adjust(0,1,0,1);
        break;
    }
    ScreenShotwidget::displayCaptureInfo(now);
    ScreenShotwidget::updateAdjustAreaRects();
    repaint();
}

// widget 初始化
void ScreenShotwidget::widgetInit()
{
    /*      窗体样式     */
    this->setWindowFlags(Qt::FramelessWindowHint|Qt::Tool|Qt::WindowStaysOnTopHint); // 无边框
    this->setAttribute(Qt::WA_TranslucentBackground, true); // 透明背景
    this->setMouseTracking(true);
    this->showFullScreen();
    pixmap = QGuiApplication::primaryScreen()->grabWindow(0);   // 获取全局截图
    labels = new InfoLabel(this);
    labels->move(-1,-1);
}


// 重选截图区 或 退出截图     参数true直接退出
void ScreenShotwidget::exitScreenshot(bool exit)
{
    if(!exit){  // 不直接退出就看是否返回截图 不然还是直接退
        if(CaptureRect.isValid()) CaptureRect = QRect();
        else this->hide();
    } else{
        CaptureRect = QRect();
        this->hide();
    }
    labels->hide();
    tool_bar_->hide();
    repaint();
}

// 更新调节区域
void ScreenShotwidget::updateAdjustAreaRects()
{
    adjustAreaRects[0] = QRect(QPoint(CaptureRect.topLeft()-QPoint(Marge/2,Marge/2)),QSize(Marge,Marge));
    adjustAreaRects[1] = adjustAreaRects[0].translated(CaptureRect.width()/2,0);
    adjustAreaRects[2] = adjustAreaRects[1].translated((CaptureRect.width()+1)/2,0);
    adjustAreaRects[3] = adjustAreaRects[0].translated(0,CaptureRect.height()/2);
    adjustAreaRects[4] = adjustAreaRects[2].translated(0,CaptureRect.height()/2);
    adjustAreaRects[5] = adjustAreaRects[3].translated(0,(CaptureRect.height()+1)/2);
    adjustAreaRects[6] = adjustAreaRects[5].translated(CaptureRect.width()/2,0);
    adjustAreaRects[7] = adjustAreaRects[4].translated(0,(CaptureRect.height()+1)/2);
}

// 鼠标所点击的区域
int8_t ScreenShotwidget::pressAreaContains(QPoint p)
{
    for(int i=0;i<8;i++){
        if(adjustAreaRects[i].contains(p))
            return i+1;
    }
    if(CaptureRect.contains(p)) return 0;
    return 9;
}

// 标记CaptureRect四个角
void ScreenShotwidget::markCurrentRect()
{
    LeftTop = CaptureRect.topLeft();
    LeftBottom = QPoint(CaptureRect.x(),CaptureRect.y()+CaptureRect.height());
    RightTop = QPoint(CaptureRect.x()+CaptureRect.width(),CaptureRect.y());
    RightBottom = LeftTop + QPoint(CaptureRect.width(),CaptureRect.height());
}

// 调节当前窗口大小或位置
void ScreenShotwidget::adjustCurrentRect(QPoint now)
{
    switch(mouseArea)               // 检测按下区域
    {
    case 0:// 中间
        CaptureRect.moveCenter(now);
        ScreenShotwidget::edgeCheck(now);
        break;
    case 1:// 左上
        //CaptureRect = QRect(now.x(),now.y(),RightBottom.x()-now.x(),RightBottom.y()-now.y()).normalized();
        CaptureRect = QRect(now,RightBottom).normalized();
        break;
    case 8:// 右下
        //CaptureRect = QRect(LeftTop.x(),LeftTop.y(),now.x()-LeftTop.x(),now.y()-LeftTop.y()).normalized();
        CaptureRect = QRect(LeftTop,now).normalized();
        break;
    case 2:// 上
        //CaptureRect = QRect(LeftTop.x(),now.y(),RightBottom.x()-LeftTop.x(),RightBottom.y()-now.y()).normalized();
        CaptureRect = QRect(QPoint(LeftTop.x(),now.y()),RightBottom).normalized();
        break;
    case 7:// 下
        //CaptureRect = QRect(LeftTop.x(),LeftTop.y(),RightBottom.x()-LeftTop.x(),now.y()-LeftTop.y()).normalized();
        CaptureRect = QRect(LeftTop,QPoint(RightBottom.x(),now.y())).normalized();
        break;
    case 3:// 右上
        //CaptureRect = QRect(LeftBottom.x(),now.y(),now.x()-LeftBottom.x(),LeftBottom.y()-now.y()).normalized();
        CaptureRect = QRect(QPoint(LeftBottom.x(),now.y()),QPoint(now.x(),RightBottom.y())).normalized();
        break;
    case 6:// 左下
        //CaptureRect = QRect(now.x(),RightTop.y(),RightTop.x()-now.x(),now.y()-RightTop.y()).normalized();
        CaptureRect = QRect(QPoint(now.x(),LeftTop.y()),QPoint(RightBottom.x(),now.y())).normalized();
        break;
    case 4:// 左
        //CaptureRect = QRect(now.x(),LeftTop.y(),RightTop.x()-now.x(),RightBottom.y()-RightTop.y()).normalized();
        CaptureRect = QRect(QPoint(now.x(),LeftTop.y()),RightBottom).normalized();
        break;
    case 5:// 右
        //CaptureRect = QRect(LeftTop.x(),LeftTop.y(),now.x()-LeftTop.x(),RightBottom.y()-RightTop.y()).normalized();
        CaptureRect = QRect(LeftTop,QPoint(now.x(),RightBottom.y())).normalized();
        break;
    }
}

// 显示截图窗口信息到Label上
void ScreenShotwidget::displayCaptureInfo(QPoint &now)
{
    QPoint m = CaptureRect.topLeft();
    if(m.y()>=labels->height()) labels->move(m.x(),m.y()-labels->height());
    else labels->move(m.x(),m.y()+CaptureRect.height());
    QColor color = pixmap.toImage().pixelColor(now);
    QString str1 = QString("长×宽:%1×%2\n").arg(CaptureRect.width()).arg(CaptureRect.height());
    QString str2 = QString("RGB:%1,%2,%3\n按C复制RGB色号\n右键返回或退出截图").arg(color.red()).arg(color.green()).arg(color.blue());
    labels->setTextLabel(str1+str2);
    labels->setPixmapLabel(pixmap.copy(now.x()-20,now.y()-20,40,40));

    initToolBar();
}

// Capture窗口的边界检测
uint8_t ScreenShotwidget::edgeCheck(QPoint &nowPoint)
{
    uint8_t r = 0;
    if(nowPoint.x()<0) {nowPoint.rx()=0;r = 1;}  // 左超界
    if(nowPoint.x()+CaptureRect.width()>this->width()) {nowPoint.rx()=this->width()-CaptureRect.width();r = 2;}    // 右超界
    if(nowPoint.y()<0) {nowPoint.ry()=0;r = 3;}  // 上
    if(nowPoint.y()+CaptureRect.height()>this->height()) {nowPoint.ry()=this->height()-CaptureRect.height();r = 4;}// 下
    return r;   // 没超界
}


// 设置当前光标样式
void ScreenShotwidget::setCurrentCursor(uint8_t p)
{
    switch(p){
    case 1:
    case 8:
        this->setCursor(Qt::SizeFDiagCursor);
        break;
    case 2:
    case 7:
        this->setCursor(Qt::SizeVerCursor);
        break;
    case 3:
    case 6:
        this->setCursor(Qt::SizeBDiagCursor);
        break;
    case 4:
    case 5:
        this->setCursor(Qt::SizeHorCursor);
        break;
    case 9:
        this->setCursor(Qt::ArrowCursor);
        break;
    default:
        this->setCursor(Qt::SizeAllCursor);
    }
}
