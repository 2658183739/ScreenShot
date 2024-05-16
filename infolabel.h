#ifndef INFOLABEL_H
#define INFOLABEL_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QPainter>

class MyPixmapLabel;
class MyTextLabel;
class InfoLabel : public QWidget
{
    Q_OBJECT
public:
    explicit InfoLabel(QWidget *parent = nullptr);
    void setTextLabel(QString text);
    void setPixmapLabel(QPixmap pixmap);
    void paintPixmapLabel();
    MyTextLabel *TextLabel;
    MyPixmapLabel *PixmapLabel;
private:
    QHBoxLayout *hblayout;
protected:
    //bool eventFilter(QObject *watched, QEvent *event) override;
    void paintEvent(QPaintEvent *e) override;
signals:

};

class MyPixmapLabel : public QLabel
{
    Q_OBJECT
public:
    explicit MyPixmapLabel(QWidget *parent = nullptr):QLabel(parent){}
protected:
    void paintEvent(QPaintEvent *e) override{
        QLabel::paintEvent(e);
        QPainter painter(this);
        QPen pen(QColor(0,0,0));
        pen.setWidth(3);
        painter.setPen(pen);
        painter.drawLine((this->width()+1)/2,0,(this->width()+1)/2,this->height());
        painter.drawLine(0,(this->height()+1)/2,this->width(),(this->height()+1)/2);
        painter.setBrush(QColor(Qt::white));
        painter.drawEllipse(this->width()/2-1,this->height()/2-1,5,5);
    };
};

class MyTextLabel : public QLabel
{
    Q_OBJECT
public:
    explicit MyTextLabel(QWidget *parent = nullptr):QLabel(parent){this->setFont(QFont("宋体",9,QFont::Bold));}

protected:
    void paintEvent(QPaintEvent *) override{
        QPainter painter(this);
        painter.fillRect(this->rect(),QColor(0,0,0,180));
        painter.setPen(QColor(255,255,255));
        painter.drawText(this->rect(),Qt::AlignCenter,this->text());
    };
};

#endif // INFOLABEL_H
