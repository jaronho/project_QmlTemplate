#ifndef XRESIZEWINDOW_H
#define XRESIZEWINDOW_H

#include <QQuickWidget>

class XResizeWindow{
private:
    class XQuickWidget : public QQuickWidget {
    public:
        XQuickWidget(QWidget* parent = nullptr);
        void setDraggable(bool on);
    protected:
        void resizeEvent(QResizeEvent* event);
        void mousePressEvent(QMouseEvent* event);
        void mouseReleaseEvent(QMouseEvent* event);
        void mouseMoveEvent(QMouseEvent* event);
    private:
        bool mIsDragging;
        QPoint mDragPosition;
        bool mDraggable;
    };

public:
    XResizeWindow(const QSize& size, const QSize& minimumSize = QSize(-1, -1), const QSize& maximumSize = QSize(-1, -1), bool draggable = true);
    ~XResizeWindow(void);

public:
    void setFlags(Qt::WindowFlags flags);
    void setFlag(Qt::WindowType flag, bool on = true);
    void setContextProperty(const QString& name, QObject* value);
    void setContextProperty(const QString& name, const QVariant& value);
    void setTitle(QString title);
    void setIcon(QIcon icon);
    void setIconText(QString text);
    void setSource(const QUrl& source);
    void show(void);
    void hide(void);
    void showFullScreen(void);
    void showMaximized(void);
    void showMinimized(void);
    void showNormal(void);
    void close(void);

private:
    XQuickWidget* mWidget;
};

#endif // XRESIZEWINDOW_H
