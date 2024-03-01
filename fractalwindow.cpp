#include "fractalwindow.h"
#include "fractalwindowrenderer.h"

#include <QQuickWindow>
#include <QOpenGLShaderProgram>
#include <QOpenGLContext>
#include <QRunnable>

// #include <QDebug>

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

        m_renderer->fractalType = m_fractalType;

        connect(window(), &QQuickWindow::beforeRendering, m_renderer, &FractalWindowRenderer::initialization, Qt::DirectConnection);
        connect(window(), &QQuickWindow::afterRenderPassRecording, m_renderer, &FractalWindowRenderer::paint, Qt::DirectConnection);
    }

    m_renderer->setViewportSize(window()->size() * window()->devicePixelRatio());

    // Установка значений изменяемых переменных из-под QML
    m_renderer->setFScale(m_fScale);
    m_renderer->setXOffset(m_xOffset);
    m_renderer->setYOffset(m_yOffset);

    m_renderer->fractalType = m_fractalType;

    // qInfo() << "m_fScale" << m_fScale;

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

float FractalWindow::fScale() const
{
    return m_fScale;
}

void FractalWindow::setFScale(float newFScale)
{
    if (qFuzzyCompare(m_fScale, newFScale))
        return;
    m_fScale = newFScale;
    emit fScaleChanged();
}

float FractalWindow::yOffset() const
{
    return m_yOffset;
}

void FractalWindow::setYOffset(float newYOffset)
{
    if (qFuzzyCompare(m_yOffset, newYOffset))
        return;
    m_yOffset = newYOffset;
    emit yOffsetChanged();
}

float FractalWindow::xOffset() const
{
    return m_xOffset;
}

void FractalWindow::setXOffset(float newXOffset)
{
    if (qFuzzyCompare(m_xOffset, newXOffset))
        return;
    m_xOffset = newXOffset;
    emit xOffsetChanged();
}

int FractalWindow::fractalType() const
{
    return m_fractalType;
}

void FractalWindow::setFractalType(int newFractalType)
{
    if (m_fractalType == newFractalType)
        return;
    m_fractalType = newFractalType;

    if(m_renderer)
    {
        m_renderer->fractalType = m_fractalType;
        m_renderer->resetProgram();
    }

    emit fractalTypeChanged();
}
