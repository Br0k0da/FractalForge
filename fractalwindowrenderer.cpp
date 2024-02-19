#include "fractalwindowrenderer.h"


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
        // m_program->addCacheableShaderFromSourceCode(QOpenGLShader::Fragment,
        //                                             "uniform lowp float t;"
        //                                             "varying highp vec2 coords;"
        //                                             "void main() {"
        //                                             "    lowp float i = 1. - (pow(abs(coords.x), 4.) + pow(abs(coords.y), 4.));"
        //                                             "    i = smoothstep(t - 0.8, t + 0.8, i);"
        //                                             "    i = floor(i * 20.) / 20.;"
        //                                             "    gl_FragColor = vec4(coords * .5 + .5, i, i);"
        //                                             "}");



        m_program->addCacheableShaderFromSourceCode(QOpenGLShader::Fragment, "uniform vec2 center;"
                                                                             "uniform float scale;"
                                                                             "uniform int iter;"
                                                                             "varying highp vec2 coords;"

                                                                             "void main() {"
                                                                             "    vec2 z, c;"

                                                                             "    c.x = 1.3333 * (coords.x - 0.5) * scale - center.x;"
                                                                             "    c.y = (coords.y) * scale - center.y;"

                                                                             "    int i;"
                                                                             "    z = c;"
                                                                             "    for(i=0; i<iter; i++) {"
                                                                             "        float x = (z.x * z.x - z.y * z.y) + c.x;"
                                                                             "        float y = (z.y * z.x + z.x * z.y) + c.y;"

                                                                             "        if((x * x + y * y) > 4.0) break;"
                                                                             "        z.x = x;"
                                                                             "        z.y = y;"
                                                                             "    }"

                                                                             "if(i == iter)"
                                                                             "    gl_FragColor = vec4(144.0, 144.0, 144.0, 255.0);"
                                                                             "else"
                                                                             "    gl_FragColor = vec4(0.0, 0.0, 0.0, 255.0);"
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

    // glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_program->enableAttributeArray(0);

    float values[] = {
        -1, -1, // left-bottom
        1, -1, // right-bottom
        -1, 1, // left-upper
        1, 1 // right-upper
    };

    // This example relies on (deprecated) client-side pointers for the vertex
    // input. Therefore, we have to make sure no vertex buffer is bound.
    glBindBuffer(GL_ARRAY_BUFFER, 0);


    m_program->setAttributeArray(0, GL_FLOAT, values, 2);
    // m_program->setUniformValue("t", (float) 0.0);
    m_program->setUniformValue("scale", (float)1);
    m_program->setUniformValue("center", QPointF(0.0, 0.0));
    m_program->setUniformValue("iter", 512);

    glViewport(m_viewportSize.width() * 0.333, m_viewportSize.height() * 0.01, m_viewportSize.width() * 0.663, m_viewportSize.height() * 0.98);

    glDisable(GL_DEPTH_TEST);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);

    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    m_program->disableAttributeArray(0);
    m_program->release();

    m_window->endExternalCommands();
}
