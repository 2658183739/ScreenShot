#include "tool_bar.h"
#include <QPainter>

Tool_bar::Tool_bar(QWidget *parent) : QWidget(parent)
{
    setWindowFlags(Qt::FramelessWindowHint);
    setStyleSheet("background-color: white; border: 1px solid gray;");
    m_dragging = false;
}

void Tool_bar::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        m_dragging = true;
        m_dragPosition = event->globalPos();
    }
}

void Tool_bar::mouseMoveEvent(QMouseEvent *event)
{
    if (m_dragging) {
        QPoint delta = event->globalPos() - m_dragPosition;
        this->move(this->x() + delta.x(), this->y() + delta.y());
        m_dragPosition = event->globalPos();
    }
}

void Tool_bar::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        m_dragging = false;
    }
}

void Tool_bar::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);
    QPainter painter(this);
    painter.setPen(QPen(Qt::gray, 1));
    painter.drawRect(rect().adjusted(10, 10, -10, -10));
}
