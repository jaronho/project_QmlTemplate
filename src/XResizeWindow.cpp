#include "XResizeWindow.h"
#include <QQmlContext>

XResizeWindow::XQuickWidget::XQuickWidget(QWidget* parent) : QQuickWidget(parent) {
    mIsDragging = false;
    mDraggable = true;
}

void XResizeWindow::XQuickWidget::setDraggable(bool on) {
    mDraggable = on;
}

void XResizeWindow::XQuickWidget::resizeEvent(QResizeEvent* event) {
}

void XResizeWindow::XQuickWidget::mousePressEvent(QMouseEvent* event) {
    if (Qt::LeftButton == event->button()) {
        mIsDragging = true;
        mDragPosition = event->pos();
    }
}

void XResizeWindow::XQuickWidget::mouseReleaseEvent(QMouseEvent* event) {
    if (Qt::LeftButton == event->button()) {
        mIsDragging = false;
    }
}

void XResizeWindow::XQuickWidget::mouseMoveEvent(QMouseEvent* event) {
    if (mIsDragging && mDraggable) {
        move(event->globalPos() - mDragPosition);
    }
}

static const char* XRW_WIDTH = "xrw_width";
static const char* XRW_HEIGHT = "xrw_height";

XResizeWindow::XResizeWindow(const QSize& size, const QSize& minimumSize, const QSize& maximumSize, bool draggable) {
    mWidget = new XQuickWidget();
    mWidget->setAttribute(Qt::WA_TranslucentBackground, true);
    mWidget->setClearColor(QColor(Qt::transparent));
    mWidget->setFixedSize(size);
    int minimumWidth = size.width(), minimumHeight = size.height();
    if (minimumSize.width() >= 0 && minimumSize.height() >= 0) {
        minimumWidth = minimumSize.width() < size.width() ? minimumSize.width() : size.width();
        minimumHeight = minimumSize.height() < size.height() ? minimumSize.height() : size.height();
    }
    mWidget->setMinimumSize(QSize(minimumWidth, minimumHeight));
    int maximumWidth = size.width(), maximumHeight = size.height();
    if (maximumSize.width() > 0 && maximumSize.height() > 0) {
        maximumWidth = maximumSize.width() > size.width() ? maximumSize.width() : size.width();
        maximumHeight = maximumSize.height() > size.height() ? maximumSize.height() : size.height();
    }
    mWidget->setMaximumSize(QSize(maximumWidth, maximumHeight));
    mWidget->setDraggable(draggable);
    mWidget->rootContext()->setContextProperty(XRW_WIDTH, size.width());
    mWidget->rootContext()->setContextProperty(XRW_HEIGHT, size.height());
}

XResizeWindow::~XResizeWindow(void) {
    delete mWidget;
}

void XResizeWindow::setFlags(Qt::WindowFlags flags) {
    mWidget->setWindowFlags(flags);
}

void XResizeWindow::setFlag(Qt::WindowType flag, bool on) {
    mWidget->setWindowFlag(flag, on);
}

void XResizeWindow::setContextProperty(const QString& name, QObject* value) {
    if (0 == name.compare(XRW_WIDTH) || 0 == name.compare(XRW_HEIGHT)) {
        return;
    }
    mWidget->rootContext()->setContextProperty(name, value);
}

void XResizeWindow::setContextProperty(const QString& name, const QVariant& value) {
    if (0 == name.compare(XRW_WIDTH) || 0 == name.compare(XRW_HEIGHT)) {
        return;
    }
    mWidget->rootContext()->setContextProperty(name, value);
}

void XResizeWindow::setTitle(QString title) {
    mWidget->setWindowTitle(title);
}

void XResizeWindow::setIcon(QIcon icon) {
    mWidget->setWindowIcon(icon);
}

void XResizeWindow::setIconText(QString text) {
    mWidget->setWindowIconText(text);
}

void XResizeWindow::setSource(const QUrl& source) {
    mWidget->setSource(source);
}

void XResizeWindow::show(void) {
    mWidget->show();
}
