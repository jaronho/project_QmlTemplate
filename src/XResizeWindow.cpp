#include "XResizeWindow.h"
#include <QQmlContext>

static const char* XRW_WIDTH = "xrw_width";
static const char* XRW_HEIGHT = "xrw_height";

XResizeWindow::XQuickWidget::XQuickWidget(QWidget* parent) : QQuickWidget(parent) {
    mIsPressed = false;
    mIsCanMove = true;
}

void XResizeWindow::XQuickWidget::setIsCanMove(bool on) {
    mIsCanMove = on;
}

void XResizeWindow::XQuickWidget::resizeEvent(QResizeEvent* resize) {
}

void XResizeWindow::XQuickWidget::mousePressEvent(QMouseEvent* mouse) {
    mIsPressed = true;
    mPrePosition = mouse->globalPos();
}

void XResizeWindow::XQuickWidget::mouseReleaseEvent(QMouseEvent* mouse) {
    mIsPressed = false;
}

void XResizeWindow::XQuickWidget::mouseMoveEvent(QMouseEvent* mouse) {
    if (!mIsPressed) {
        return;
    }
    QPoint delta = mouse->globalPos() - mPrePosition;
    mPrePosition = mouse->globalPos();
    if (mIsCanMove) {
        move(pos() + delta);
    }
}

XResizeWindow::XResizeWindow(bool sysframe, const QSize& size, const QSize& minimumSize, const QSize& maximumSize) {
    mWidget = new XQuickWidget();
    mWidget->setAttribute(Qt::WA_TranslucentBackground, true);
    mWidget->setClearColor(QColor(Qt::transparent));
    if (sysframe) {
        mWidget->setWindowFlags(Qt::Dialog);
    } else {
        mWidget->setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
    }
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
    mWidget->rootContext()->setContextProperty(XRW_WIDTH, size.width());
    mWidget->rootContext()->setContextProperty(XRW_HEIGHT, size.height());
}

XResizeWindow::~XResizeWindow(void) {
    delete mWidget;
}

void XResizeWindow::setMoveFlag(bool on) {
    mWidget->setIsCanMove(on);
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

void XResizeWindow::setSource(const QUrl& source) {
    mWidget->setSource(source);
}

void XResizeWindow::show(void) {
    mWidget->show();
}
