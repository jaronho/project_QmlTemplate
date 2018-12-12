#include "XResizeWindow.h"
#include <QQmlContext>
#include <QQuickItem>

XResizeWindow::XQuickView::XQuickView(QWindow* parent) : QQuickView(parent) {
    mIsDragging = false;
    mDraggable = true;
}

void XResizeWindow::XQuickView::setDraggable(bool on) {
    mDraggable = on;
}

void XResizeWindow::XQuickView::resizeEvent(QResizeEvent* event) {
    QQuickView::resizeEvent(event);
}

void XResizeWindow::XQuickView::mousePressEvent(QMouseEvent* event) {
    if (Qt::LeftButton == event->button()) {
        mIsDragging = true;
        mDragPosition = event->pos();
    }
    QQuickView::mousePressEvent(event);
}

void XResizeWindow::XQuickView::mouseReleaseEvent(QMouseEvent* event) {
    if (Qt::LeftButton == event->button()) {
        mIsDragging = false;
    }
    QQuickView::mouseReleaseEvent(event);
}

void XResizeWindow::XQuickView::mouseMoveEvent(QMouseEvent* event) {
    if (mIsDragging && mDraggable) {
        setPosition(event->globalPos() - mDragPosition);
    }
    QQuickView::mouseMoveEvent(event);
}

XResizeWindow::XResizeWindow(const QSize& size, const QSize& minimumSize, const QSize& maximumSize, bool draggable) {
    mView = new XQuickView();
    mView->setColor(QColor(Qt::transparent));
    mView->setWidth(size.width());
    mView->setHeight(size.height());
    int minimumWidth = size.width(), minimumHeight = size.height();
    if (minimumSize.width() >= 0 && minimumSize.height() >= 0) {
        minimumWidth = minimumSize.width() < size.width() ? minimumSize.width() : size.width();
        minimumHeight = minimumSize.height() < size.height() ? minimumSize.height() : size.height();
    }
    mView->setMinimumSize(QSize(minimumWidth, minimumHeight));
    int maximumWidth = size.width(), maximumHeight = size.height();
    if (maximumSize.width() > 0 && maximumSize.height() > 0) {
        maximumWidth = maximumSize.width() > size.width() ? maximumSize.width() : size.width();
        maximumHeight = maximumSize.height() > size.height() ? maximumSize.height() : size.height();
    }
    mView->setMaximumSize(QSize(maximumWidth, maximumHeight));
    mView->setDraggable(draggable);
}

XResizeWindow::~XResizeWindow(void) {
    delete mView;
}

void XResizeWindow::setFlags(Qt::WindowFlags flags) {
    mView->setFlags(flags);
}

void XResizeWindow::setFlag(Qt::WindowType flag, bool on) {
    mView->setFlag(flag, on);
}

void XResizeWindow::setContextProperty(const QString& name, QObject* value) {
    mView->rootContext()->setContextProperty(name, value);
}

void XResizeWindow::setContextProperty(const QString& name, const QVariant& value) {
    mView->rootContext()->setContextProperty(name, value);
}

void XResizeWindow::setTitle(QString title) {
    mView->setTitle(title);
}

void XResizeWindow::setIcon(QIcon icon) {
    mView->setIcon(icon);
}

void XResizeWindow::setSource(const QUrl& source) {
    mView->setSource(source);
}

void XResizeWindow::show(void) {
    mView->show();
}

void XResizeWindow::hide(void) {
    mView->hide();
}

void XResizeWindow::showFullScreen(void) {
    mView->showFullScreen();
}

void XResizeWindow::showMaximized(void) {
    mView->showMaximized();
}

void XResizeWindow::showMinimized(void) {
    mView->showMinimized();
}

void XResizeWindow::showNormal(void) {
    mView->showNormal();
}

void XResizeWindow::close(void) {
    mView->close();
}
