#ifndef FRACTALWINDOWRENDERER_H
#define FRACTALWINDOWRENDERER_H

#include <QSize>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QQuickWindow>

class FractalWindowRenderer : public QObject, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    ~FractalWindowRenderer();

    void setViewportSize(const QSize &size) { m_viewportSize = size; }
    void setWindow(QQuickWindow *window) { m_window = window; }

    float fScale() const;
    void setFScale(float newFScale);

    float yOffset() const;
    void setYOffset(float newYOffset);

    float xOffset() const;
    void setXOffset(float newXOffset);

public slots:
    void initialization();
    void paint();

private:
    QSize m_viewportSize;
    QQuickWindow *m_window = nullptr;
    QOpenGLShaderProgram *m_program = nullptr;
    float m_fScale = 1.0;
    float m_xOffset = 0.0;
    float m_yOffset = 0.0;
};

#endif // FRACTALWINDOWRENDERER_H
