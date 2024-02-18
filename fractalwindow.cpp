#include "fractalwindow.h"

#include <qquickwindow.h>
#include <QOpenGLShaderProgram>
#include <QOpenGLContext>
#include <QRunnable>

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
        connect(window(), &QQuickWindow::beforeRenderPassRecording, m_renderer, &FractalWindowRenderer::paint, Qt::DirectConnection);
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

        wnd->setColor(Qt::black);
    }
}

FractalWindowRenderer::~FractalWindowRenderer()
{
    delete m_program;
}

void FractalWindowRenderer::initialization()
{
    if (!m_program) {
        QSGRendererInterface *rif = m_window->rendererInterface();
        Q_ASSERT(rif->graphicsApi() == QSGRendererInterface::OpenGL);

        initializeOpenGLFunctions();

        m_program = new QOpenGLShaderProgram();
        m_program->addCacheableShaderFromSourceCode(QOpenGLShader::Vertex,
                                                    "attribute highp vec4 vertices;"
                                                    "varying highp vec2 coords;"
                                                    "void main() {"
                                                    "    gl_Position = vertices;"
                                                    "    coords = vertices.xy;"
                                                    "}");
        m_program->addCacheableShaderFromSourceCode(QOpenGLShader::Fragment,
                                                    "uniform lowp float t;"
                                                    "varying highp vec2 coords;"
                                                    "void main() {"
                                                    "    lowp float i = 1. - (pow(abs(coords.x), 4.) + pow(abs(coords.y), 4.));"
                                                    "    i = smoothstep(t - 0.8, t + 0.8, i);"
                                                    "    i = floor(i * 20.) / 20.;"
                                                    "    gl_FragColor = vec4(coords * .5 + .5, i, i);"
                                                    "}");

        m_program->bindAttributeLocation("vertices", 0);
        m_program->link();

    }
}

void FractalWindowRenderer::paint()
{
    // Play nice with the RHI. Not strictly needed when the scenegraph uses
    // OpenGL directly.
    m_window->beginExternalCommands();

    m_program->bind();

    m_program->enableAttributeArray(0);

    float values[] = {
        -1, -1,
        1, -1,
        -1, 1,
        1, 1
    };

    // This example relies on (deprecated) client-side pointers for the vertex
    // input. Therefore, we have to make sure no vertex buffer is bound.
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    m_program->setAttributeArray(0, GL_FLOAT, values, 2);
    m_program->setUniformValue("t", (float) 0.0);

    glViewport(0, 0, m_viewportSize.width(), m_viewportSize.height());

    glDisable(GL_DEPTH_TEST);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);

    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    m_program->disableAttributeArray(0);
    m_program->release();

    m_window->endExternalCommands();
}
