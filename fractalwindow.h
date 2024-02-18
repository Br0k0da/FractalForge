#ifndef FRACTALWINDOW_H
#define FRACTALWINDOW_H

#include <QQuickItem>

class FractalWindow : public QQuickItem
{
    Q_OBJECT
    QML_ELEMENT
public:
    explicit FractalWindow();

    void paintMandelbrot();

public slots:
    void sync();
    void cleanup();

private slots:
    void handleWindowChanged(QQuickWindow* wnd);

signals:
};

#endif // FRACTALWINDOW_H
