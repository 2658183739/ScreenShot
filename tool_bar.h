#ifndef TOOL_BAR_H
#define TOOL_BAR_H

#include <QWidget>
#include <QMouseEvent>

class Tool_bar : public QWidget
{
    Q_OBJECT
public:
    explicit Tool_bar(QWidget *parent = nullptr);

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);

private:
    bool m_dragging;
    QPoint m_dragPosition;
};

#endif // TOOL_BAR_H
