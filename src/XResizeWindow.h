#ifndef XRESIZEWINDOW_H
#define XRESIZEWINDOW_H

#include <QQuickWidget>

class XResizeWindow{
private:
    class XQuickWidget : public QQuickWidget {
    public:
        XQuickWidget(QWidget* parent = nullptr);
        void setIsCanMove(bool on);
    protected:
        void resizeEvent(QResizeEvent* resize);
        void mousePressEvent(QMouseEvent* mouse);
        void mouseReleaseEvent(QMouseEvent* mouse);
        void mouseMoveEvent(QMouseEvent* mouse);
    private:
        bool mIsPressed;
        QPoint mPrePosition;
        bool mIsCanMove;
    };

public:
    XResizeWindow(bool sysframe, const QSize& size, const QSize& minimumSize = QSize(-1, -1), const QSize& maximumSize = QSize(-1, -1));
    ~XResizeWindow(void);

public:
    void setMoveFlag(bool on);
    void setContextProperty(const QString& name, QObject* value);
    void setContextProperty(const QString& name, const QVariant& value);
    void setSource(const QUrl& source);
    void show(void);

private:
    XQuickWidget* mWidget;
};

#endif // XRESIZEWINDOW_H
