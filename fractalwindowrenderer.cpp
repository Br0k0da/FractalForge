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


        // Множество Мандельброта
         /*
        m_program->addCacheableShaderFromSourceCode(QOpenGLShader::Fragment, "uniform vec2 center;"
                                                                             "uniform float scale;"
                                                                             "uniform int iter;"
                                                                             "varying highp vec2 coords;"

                                                                             "void main() {"
                                                                             "    vec2 z, c;"
                                                                             "    c.x = 1.3333 * (coords.x - 0.5) * scale - center.x;"
                                                                             "    c.y = (coords.y) * scale - center.y;"

                                                                             "    int i = 0;"
                                                                             "    float x = c.x;"
                                                                             "    float y = c.y;"
                                                                             "    z.x = 0;"
                                                                             "    z.y = 0;"
                                                                             "    while(i < iter && (x * x + y * y) <= 4.0) {"
                                                                             "        x = (z.x * z.x - z.y * z.y) + c.x;"
                                                                             "        y = (z.y * z.x + z.x * z.y) + c.y;"
                                                                             "        z.x = x;"
                                                                             "        z.y = y;"
                                                                             "        ++i;"
                                                                             "    }"

                                                                             "if(i == iter)"
                                                                             "    gl_FragColor = vec4(144.0, 144.0, 144.0, 255.0);"
                                                                             "else"
                                                                             "    gl_FragColor = vec4(0.0, 0.0, 0.0, 255.0);"

                                                                             "}");
         */
        // Фрактал Жулья
        /*
        m_program->addCacheableShaderFromSourceCode(QOpenGLShader::Fragment, "uniform vec2 center;"
                                                                             "uniform float scale;"
                                                                             "uniform int iter;"
                                                                             "varying highp vec2 coords;"

                                                                             "void main() {"
                                                                             "    vec2 c, z;"
                                                                             "    z.x = 1.3333 * (coords.x - 0.5) * scale - center.x;"
                                                                             "    z.y = (coords.y) * scale - center.y;"

                                                                             "    int i = 0;"
                                                                             "    float x = z.x;"
                                                                             "    float y = z.y;"
                                                                             "    c.x = -0.5;"
                                                                             "    c.y = 0;"

                                                                             "    while(i < iter && (x * x + y * y) <= 4.0) {"
                                                                             "        x = (z.x * z.x - z.y * z.y) + c.x;"
                                                                             "        y = (z.y * z.x + z.x * z.y) + c.y;"
                                                                             "        z.x = x;"
                                                                             "        z.y = y;"
                                                                             "        ++i;"
                                                                             "    }"

                                                                             "if(i == iter)"
                                                                             "    gl_FragColor = vec4(144.0, 0.0, 0.0, 1.0);"
                                                                             "else"
                                                                             "    gl_FragColor = vec4(0.0, 0.0, 0.0, 1.0);"
                                                                             "}");
        */
        m_program->addCacheableShaderFromSourceCode(QOpenGLShader::Fragment, "uniform vec2 center;"
                                                                             "uniform vec2 a_koh;"
                                                                             "uniform vec2 b_koh;"
                                                                             "uniform vec2 c_koh;"
                                                                             "uniform float scale;"
                                                                             "uniform float k;"
                                                                             "uniform int iter_koh;"
                                                                             "varying highp vec2 coords;"

                                                                             "void f(vec2 a, vec2 b, vec2 c, int iter) {"
                                                                             "    vec2 z;"
                                                                             "    z.x = 1.3333 * (coords.x - 0.5) * scale - center.x;"
                                                                             "    z.y = (coords.y) * scale - center.y;"

                                                                             "    float k_ab = k, k_bc = -k, b_ac, b_b;"
                                                                             "    int znak = 1;"
                                                                             "    if(b.x < a.x){"
                                                                             "        znak = -1;"
                                                                             "        k_ab = -k;"
                                                                             "        k_bc = k;"
                                                                             "    }"
                                                                             "    b_ac = a.y;"
                                                                             "    b_b = a.y - k_ab * a.x;"

                                                                             "    if(znak * (k_ab * z.x + b_b - z.y) >= 0 && znak * (k_bc * z.x + b_b - z.y) >= 0 && znak * (b_ac - z.y) <= 0)"
                                                                             "        gl_FragColor = vec4(144.0, 0.0, 0.0, 1.0);"
                                                                             "    else"
                                                                             "        gl_FragColor = vec4(0.0, 0.0, 0.0, 1.0);"

                                                                             "    --iter;"
                                                                             /*"    if(iter != 0){"
                                                                             "      vec2 a_n, b_n, c_n;"
                                                                             "      float w = abs(c.x - a.x);"
                                                                             "      float h = w * cos(30.0);"
                                                                             "      if(znak == 1){"
                                                                             "          b_n.x = a.x + w / 6;"
                                                                             "          b_n.y = a.y + h / 3;"
                                                                             "          c_n.x = a.x + w / 3;"
                                                                             "          c_n.y = b.y - h / 3;"
                                                                             "          a_n.x = c.x - w / 3;"
                                                                             "          a_n.y = c.y;"
                                                                             "          f(a_n, b_n, c_n, iter);"
                                                                             "      }"
                                                                             "      "
                                                                             "    }"*/
                                                                             "}"

                                                                             "void main() {"
                                                                             "    f(a_koh,b_koh,c_koh,iter_koh);"
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
    m_program->setUniformValue("scale", (float)2);
    m_program->setUniformValue("center", QPointF(0.0, 0.0));
    m_program->setUniformValue("iter", 1000);
    m_program->setUniformValue("iter_koh", 2);
    m_program->setUniformValue("k", (float)1.75);
    m_program->setUniformValue("a_koh", QPointF(-0.8, 0.7));
    m_program->setUniformValue("b_koh", QPointF(0.0, 0.7));
    m_program->setUniformValue("c_koh", QPointF(0.8, -0.7));


    glViewport(m_viewportSize.width() * 0.333, m_viewportSize.height() * 0.01, m_viewportSize.width() * 0.663, m_viewportSize.height() * 0.98);

    glDisable(GL_DEPTH_TEST);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);

    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    m_program->disableAttributeArray(0);
    m_program->release();

    m_window->endExternalCommands();
}
