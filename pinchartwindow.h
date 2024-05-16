#ifndef PINCHARTWINDOW_H
#define PINCHARTWINDOW_H

#include <QWidget>
#include <QPixmap>
#include <QMouseEvent>
#include <QMenu>
#include <QAction>

class PinChartWindow : public QWidget {
    Q_OBJECT
public:
    explicit PinChartWindow();
    ~PinChartWindow();
    bool setImage(QPixmap pixmap);

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);

private:
    QPixmap m_pixmap;
    bool m_dragging;
    QPoint m_dragPos;
    QMenu *m_contextMenu;
};

#endif // PINCHARTWINDOW_H
