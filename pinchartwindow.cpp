#include "PinChartWindow.h"
#include <QKeyEvent>
#include <QPainter>
#include <QMimeData>
#include <QDrag>
#include <QMenu>
#include <QAction>

PinChartWindow::PinChartWindow()
{
    //setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowStaysOnTopHint);
    setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowStaysOnTopHint | Qt::Tool);

    m_pixmap = QPixmap();
    m_dragging = false;

    // Create a context menu
    m_contextMenu = new QMenu(this);
    QAction *closeAction = new QAction("Close", this);
    connect(closeAction, &QAction::triggered, this, &PinChartWindow::close);
    m_contextMenu->addAction(closeAction);
}

PinChartWindow::~PinChartWindow()
{
    delete m_contextMenu;
}

bool PinChartWindow::setImage(QPixmap pixmap)
{
    if(pixmap.isNull())
    {
        return false;
    }
    m_pixmap = pixmap;
    setFixedSize(m_pixmap.size()); // set window size to pixmap size
    update();
    return true;
}

void PinChartWindow::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
    QPainter painter(this);
    painter.eraseRect(rect());
    painter.drawPixmap(0, 0, m_pixmap);
}

void PinChartWindow::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        m_dragging = true;
        m_dragPos = event->globalPos() - frameGeometry().topLeft();
    }
    else if(event->button() == Qt::RightButton)
    {
        // Show context menu on right-click
        m_contextMenu->exec(event->globalPos());
    }
}

void PinChartWindow::mouseMoveEvent(QMouseEvent *event)
{
    if(m_dragging)
    {
        move(event->globalPos() - m_dragPos);
    }
}
