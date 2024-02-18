#ifndef FRACTALWINDOWRENDERER_H
#define FRACTALWINDOWRENDERER_H

#include "qsize.h"
#include <QObject>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QQuickWindow>

class FractalWindowRenderer : public QObject, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    explicit FractalWindowRenderer(QObject *parent = nullptr);
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

#endif // FRACTALWINDOWRENDERER_H
