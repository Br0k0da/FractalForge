#ifndef FRACTALWINDOW_H
#define FRACTALWINDOW_H

#include <QQuickItem>
#include <QQuickWindow>
#include <QOpenGLShaderProgram>
#include <QOpenGLFunctions>

class FractalWindowRenderer : public QObject, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    ~FractalWindowRenderer();

    void setViewportSize(const QSize &size) { m_viewportSize = size; }
    void setWindow(QQuickWindow *window) { m_window = window; }

public slots:
    void initialization();
    void paint();

private:
    QSize m_viewportSize;
    QQuickWindow *m_window = nullptr;
    QOpenGLShaderProgram *m_program = nullptr;
};

class FractalWindow : public QQuickItem
{
    Q_OBJECT
    QML_ELEMENT
public:
    FractalWindow();

    void paintMandelbrot();

public slots:
    void sync();
    void cleanup();

private slots:
    void handleWindowChanged(QQuickWindow* wnd);

private:
    void releaseResources() override;
    FractalWindowRenderer *m_renderer;
};

#endif // FRACTALWINDOW_H
