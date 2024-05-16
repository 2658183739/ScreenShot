#include "infolabel.h"
#include <QEvent>

InfoLabel::InfoLabel(QWidget *parent) : QWidget(parent)
{
    this->setWindowFlags(Qt::FramelessWindowHint|Qt::Tool);
    this->setAttribute(Qt::WA_TranslucentBackground, true); //透明背景
    hblayout = new QHBoxLayout(this);
    hblayout->setMargin(0);
    hblayout->setSpacing(0);
    TextLabel = new MyTextLabel(this);
    TextLabel->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    PixmapLabel = new MyPixmapLabel(this);
    PixmapLabel->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    PixmapLabel->setScaledContents(true);
    hblayout->addWidget(PixmapLabel);
    hblayout->addWidget(TextLabel);
    hblayout->setStretch(0,5);
    hblayout->setStretch(1,6);
    this->setFixedSize(275,125);            //125 : 150 == 5 : 6
    PixmapLabel->installEventFilter(this);
}

void InfoLabel::setTextLabel(QString text)
{
    TextLabel->setText(text);
}

void InfoLabel::setPixmapLabel(QPixmap pixmap)
{
    PixmapLabel->setPixmap(pixmap);
}

void InfoLabel::paintEvent(QPaintEvent *){
    QPainter painter(this);
    painter.setCompositionMode(QPainter::CompositionMode_Source);   //覆盖模式（包括透明度）
    painter.fillRect(this->rect(),QColor(0,0,0,0));                 //填充透明黑色背景
}
