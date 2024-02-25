#include "fractalwindow.h"
#include "fractalwindowrenderer.h"

#include <QQuickWindow>
#include <QOpenGLShaderProgram>
#include <QOpenGLContext>
#include <QRunnable>

#include <iostream>

class CleanupJob : public QRunnable
{
public:
    CleanupJob(FractalWindowRenderer *renderer) : m_renderer(renderer) { }
    void run() override { delete m_renderer; }
private:
    FractalWindowRenderer *m_renderer;
};

FractalWindow::FractalWindow() : m_renderer(nullptr)
{
    connect(this, &QQuickItem::windowChanged, this, &FractalWindow::handleWindowChanged);
}

void FractalWindow::paintMandelbrot()
{

}

void FractalWindow::sync()
{
    if (!m_renderer) {
        m_renderer = new FractalWindowRenderer();
        connect(window(), &QQuickWindow::beforeRendering, m_renderer, &FractalWindowRenderer::initialization, Qt::DirectConnection);
        connect(window(), &QQuickWindow::afterRenderPassRecording, m_renderer, &FractalWindowRenderer::paint, Qt::DirectConnection);
    }

    m_renderer->setViewportSize(window()->size() * window()->devicePixelRatio());
    m_renderer->setWindow(window());
}

void FractalWindow::cleanup()
{
    delete m_renderer;
    m_renderer = nullptr;
}

void FractalWindow::releaseResources()
{
    window()->scheduleRenderJob(new CleanupJob(m_renderer), QQuickWindow::BeforeSynchronizingStage);
    m_renderer = nullptr;
}

void FractalWindow::handleWindowChanged(QQuickWindow *wnd)
{
    if (wnd) {
        connect(wnd, &QQuickWindow::beforeSynchronizing, this, &FractalWindow::sync, Qt::DirectConnection);
        connect(wnd, &QQuickWindow::sceneGraphInvalidated, this, &FractalWindow::cleanup, Qt::DirectConnection);

        // wnd->setColor(Qt::black);
    }
}

QQuickWindow *FractalWindow::windowElement() const
{
    return m_windowElement;
}

void FractalWindow::setWindowElement(QQuickWindow *newWindowElement)
{
    if (m_windowElement == newWindowElement)
        return;
    m_windowElement = newWindowElement;
    emit windowElementChanged();
}






