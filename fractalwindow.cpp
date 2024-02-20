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

    std::cout << "X: " << m_xCoord << std::endl;
    std::cout << "Y: " << m_yCoord << std::endl;
    std::cout << "Z: " << m_zCoord << std::endl;
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

int FractalWindow::xCoord() const
{
    return m_xCoord;
}

void FractalWindow::setXCoord(int newXCoord)
{
    std::cout << "X: " << newXCoord << std::endl;
    if (m_xCoord == newXCoord)
        return;
    m_xCoord = newXCoord;
    emit xCoordChanged();
}

int FractalWindow::yCoord() const
{
    return m_yCoord;
}

void FractalWindow::setYCoord(int newYCoord)
{
    std::cout << "Y: " << newYCoord << std::endl;
    if (m_yCoord == newYCoord)
        return;
    m_yCoord = newYCoord;
    emit yCoordChanged();
}

int FractalWindow::zCoord() const
{
    return m_zCoord;
}

void FractalWindow::setZCoord(int newZCoord)
{
    std::cout << "Z: " << newZCoord << std::endl;
    if (m_zCoord == newZCoord)
        return;
    m_zCoord = newZCoord;
    emit zCoordChanged();
}
