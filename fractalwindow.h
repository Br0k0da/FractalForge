#ifndef FRACTALWINDOW_H
#define FRACTALWINDOW_H

#include <QQuickItem>
#include <QQuickWindow>

class FractalWindowRenderer;

class FractalWindow : public QQuickItem
{
    Q_OBJECT

    // Q_PROPERTY(QQuickWindow* windowElement READ windowElement WRITE setWindowElement NOTIFY windowElementChanged REQUIRED FINAL)



    QML_ELEMENT
public:
    FractalWindow();

    void paintMandelbrot();

    QQuickWindow *windowElement() const;
    void setWindowElement(QQuickWindow *newWindowElement);

public slots:
    void sync();
    void cleanup();

signals:
    void windowElementChanged();

private slots:
    void handleWindowChanged(QQuickWindow* wnd);

private:
    void releaseResources() override;
    FractalWindowRenderer *m_renderer;
    QQuickWindow *m_windowElement = nullptr;
};

#endif // FRACTALWINDOW_H
