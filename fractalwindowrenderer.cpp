#include "fractalwindowrenderer.h"
<<<<<<< Updated upstream
=======
#include <QDebug>
#include <QQuickWindow>
#include <QSGRendererInterface>
>>>>>>> Stashed changes


FractalWindowRenderer::~FractalWindowRenderer()
{
    delete m_program;
}

void FractalWindowRenderer::initialization()
{
    if (!m_program) {
<<<<<<< Updated upstream
        QSGRendererInterface *rif = m_window->rendererInterface();
        Q_ASSERT(rif->graphicsApi() == QSGRendererInterface::OpenGL);
=======
        // qInfo() << fractalType << "fractalType";

        // QSGRendererInterface *rif = m_window->rendererInterface();
        // Q_ASSERT(rif->graphicsApi() == QSGRendererInterface::OpenGL);
>>>>>>> Stashed changes

        initializeOpenGLFunctions();

        m_program = new QOpenGLShaderProgram();
        m_program->addCacheableShaderFromSourceCode(QOpenGLShader::Vertex,
                                                    "attribute highp vec4 vertices;"
                                                    "varying highp vec2 coords;"
                                                    "void main() {"
                                                    "    gl_Position = vertices;"
                                                    "    coords = vertices.xy;"
                                                    "}");
        //Фрактал Мандельброта
<<<<<<< Updated upstream
        /*
=======
        ///*
        if(fractalType == 1 )
>>>>>>> Stashed changes
        m_program->addCacheableShaderFromSourceCode(QOpenGLShader::Fragment, "uniform vec2 center;"
                                                                             "uniform float scale;"
                                                                             "uniform int iter;"
                                                                             "varying highp vec2 coords;"

                                                                             "void main() {"
                                                                             "  vec2 z, c;"
                                                                             "  c.x = 1.3333 * (coords.x - 0.5) * scale - center.x;"
                                                                             "  c.y = (coords.y) * scale - center.y;"
                                                                             "  z.x = 0.0;"
                                                                             "  z.y = 0.0;"

                                                                             "  int i = 0;"
                                                                             "  float x = z.x;"
                                                                             "  float y = z.y;"

                                                                             "  while(i < iter && (x * x + y * y) <= 4.0) {"
                                                                             "      x = (z.x * z.x - z.y * z.y) + c.x;"
                                                                             "      y = (2.0 * z.x * z.y) + c.y;"
                                                                             "      z.x = x;"
                                                                             "      z.y = y;"
                                                                             "      ++i;"
                                                                             "  }"

                                                                             "if(i == iter)"
                                                                             "  gl_FragColor = vec4(1.0, 1.0, 1.0, 1.0);"
                                                                             "else"
                                                                             "    gl_FragColor = vec4(0.0, 0.0, 0.0, 255.0);"
                                                                             "}");
        */

        // Фрактал Жюлье
<<<<<<< Updated upstream
        /*
=======
        if(fractalType == 2)
>>>>>>> Stashed changes
        m_program->addCacheableShaderFromSourceCode(QOpenGLShader::Fragment, "uniform vec2 center;"
                                                                             "uniform float scale;"
                                                                             "uniform float a_gulie;"
                                                                             "uniform int iter_gulie;"
                                                                             "varying highp vec2 coords;"

                                                                             "void main() {"
                                                                             "  vec2 c, z;"
                                                                             "  float r = 0.7885;"
                                                                             "  float Pi = 3.14159265358979323846;"
                                                                             "  c.x = r * cos(Pi * a_gulie);"
                                                                             "  c.y = r * sin(Pi * a_gulie);"
                                                                             "  z.x = 1.3333 * (coords.x) * scale - center.x;"
                                                                             "  z.y = (coords.y) * scale - center.y;"

                                                                             "  int i = 0;"
                                                                             "  float x = z.x;"
                                                                             "  float y = z.y;"

                                                                             "  while(i < iter_gulie && (x * x + y * y) <= 4.0) {"
                                                                             "      x = (z.x * z.x - z.y * z.y) + c.x;"
                                                                             "      y = (2.0 * z.x * z.y) + c.y;"
                                                                             "      z.x = x;"
                                                                             "      z.y = y;"
                                                                             "      ++i;"
                                                                             "  }"

                                                                             "if(i == iter_gulie)"
                                                                             "    gl_FragColor = vec4(1.0, 1.0, 1.0, 1.0);"
                                                                             "else"
                                                                             "    gl_FragColor = vec4(0.0, 0.0, 0.0, 255.0);"
                                                                             "}");
        */
        // Треугольники Серпинского
<<<<<<< Updated upstream
        ///*
=======
        if(fractalType == 3)
>>>>>>> Stashed changes
        m_program->addCacheableShaderFromSourceCode(QOpenGLShader::Fragment, "uniform vec2 center;"
                                                                             "uniform vec2 a_base_triangle;"
                                                                             "uniform vec2 b_base_triangle;"
                                                                             "uniform vec2 c_base_triangle;"
                                                                             "uniform float scale;"
                                                                             "uniform float k_serp;"
                                                                             "uniform int iter_serp_triangle;"
                                                                             "varying highp vec2 coords;"


                                                                             "bool check(vec2 a, vec2 b, vec2 c, vec2 z){"
                                                                             "  float k_ab = -k_serp, k_bc = k_serp, b_ac, b_ab, b_bc;"
                                                                             "  b_ac = c.y;"
                                                                             "  b_ab = a.y - k_ab * a.x;"
                                                                             "  b_bc = c.y - k_bc * c.x;"
                                                                             "  if(k_ab * z.x + b_ab - z.y <= 0.0 && k_bc * z.x + b_bc - z.y <= 0.0 && b_ac - z.y >= 0.0)"
                                                                             "      return true;"
                                                                             "  return false;"
                                                                             "}"

                                                                             "void main() {"
                                                                             "  vec2 z, a, b, c, a_n, b_n, c_n;"

                                                                             "  z.x = 1.3333 * (coords.x) * scale - center.x;"
                                                                             "  z.y = (coords.y) * scale - center.y;"

                                                                             "  float w = abs(c_base_triangle.x - a_base_triangle.x);"
                                                                             "  float h = w * cos(radians(30.0f));"
                                                                             "  float k_ab = k_serp, k_bc = -k_serp, b_ac, b_ab, b_bc;"

                                                                             "  b_ac = c_base_triangle.y;"
                                                                             "  b_ab = a_base_triangle.y - k_ab * a_base_triangle.x;"
                                                                             "  b_bc = c_base_triangle.y - k_bc * c_base_triangle.x;"

                                                                             "  if(k_ab * z.x + b_ab - z.y >= 0.0 && k_bc * z.x + b_bc - z.y >= 0.0 && b_ac - z.y <= 0.0){"
                                                                             "      gl_FragColor = vec4(1.0, 1.0, 1.0, 1.0);"

                                                                             "      for(int st = 1; st < iter_serp_triangle; ++st){"
                                                                             "          a_n.x = a_base_triangle.x + w / pow(2.0, float(st) + 1.0);"
                                                                             "          a_n.y = a_base_triangle.y + h / pow(2.0, float(st));"
                                                                             "          b_n.x = a_base_triangle.x + w / pow(2.0, float(st));"
                                                                             "          b_n.y = a_base_triangle.y;"
                                                                             "          c_n.x = a_n.x + w / pow(2.0, float(st));"
                                                                             "          c_n.y = a_n.y;"

                                                                             "          for(int i = 0; i < int(pow(2.0, float(st)) - 1.0); ++i){"
                                                                             "              a = a_n;"
                                                                             "              b = b_n;"
                                                                             "              c = c_n;"
                                                                             "              for(int j = i; j < int(pow(2.0, float(st)) - 1.0); ++j){"
                                                                             "                  if(check(a, b, c, z)){"
                                                                             "                      gl_FragColor = vec4(0.0, 0.0, 0.0, 1.0);"
                                                                             "                      break;"
                                                                             "                  }"
                                                                             "                  a.x += w / pow(2.0, float(st));"
                                                                             "                  b.x += w / pow(2.0, float(st));"
                                                                             "                  c.x += w / pow(2.0, float(st));"
                                                                             "              }"

                                                                             "              a_n.x = b_n.x;"
                                                                             "              a_n.y += h / pow(2.0, float(st));"
                                                                             "              b_n.x = c_n.x;"
                                                                             "              b_n.y += a_n.y;"
                                                                             "              c_n.x += w / pow(2.0, float(st) + 1.0);"
                                                                             "              c_n.y = a_n.y;"
                                                                             "          }"
                                                                             "      }"
                                                                             "  }"

                                                                             "  else{"
                                                                             "      gl_FragColor = vec4(0.0, 0.0, 0.0, 255.0);"
                                                                             "  }"
                                                                             "}");
        //*/


        // Ковёр Серпинского
<<<<<<< Updated upstream
        /*
=======
        if(fractalType == 4)
>>>>>>> Stashed changes
        m_program->addCacheableShaderFromSourceCode(QOpenGLShader::Fragment, "uniform vec2 center;"
                                                                             "uniform vec2 a_base_square;"
                                                                             "uniform vec2 b_base_square;"
                                                                             "uniform vec2 c_base_square;"
                                                                             "uniform vec2 d_base_square;"
                                                                             "uniform float scale;"
                                                                             "uniform int iter_serp_square;"
                                                                             "varying highp vec2 coords;"


                                                                             "bool check(vec2 a, vec2 b, vec2 c, vec2 d,vec2 z){"
                                                                             "  float b_ad, b_ab, b_bc, b_cd;"
                                                                             "  b_ad = a.y;"
                                                                             "  b_ab = a.x;"
                                                                             "  b_bc = b.y;"
                                                                             "  b_cd = c.x;"
                                                                             "  if(z.x - b_ab >= 0.0 && z.x - b_cd <= 0.0 && z.y - b_ad >= 0.0 && z.y - b_bc <= 0.0)"
                                                                             "      return true;"
                                                                             "  return false;"
                                                                             "}"

                                                                             "void main() {"
                                                                             "  vec2 z, a, b, c, d, a_n, b_n, c_n, d_n;"

                                                                             "  z.x = 1.3333 * (coords.x) * scale - center.x;"
                                                                             "  z.y = (coords.y) * scale - center.y;"

                                                                             "  float w = abs(a_base_square.x) + abs(d_base_square.x);"
                                                                             "  float h = abs(a_base_square.y) + abs(b_base_square.y);"
                                                                             "  float b_ad, b_ab, b_bc, b_cd;"

                                                                             "  b_ad = a_base_square.y;"
                                                                             "  b_ab = a_base_square.x;"
                                                                             "  b_bc = b_base_square.y;"
                                                                             "  b_cd = c_base_square.x;"

                                                                             "  if(z.x - b_ab >= 0.0 && z.x - b_cd <= 0.0 && z.y - b_ad >= 0.0 && z.y - b_bc <= 0.0){"
                                                                             "      gl_FragColor = vec4(1.0, 1.0, 1.0, 1.0);"
                                                                             "      for(int st = 1; st < iter_serp_square; ++st){"
                                                                             "          a_n.x = a_base_square.x + w / pow(3.0, float(st));"
                                                                             "          a_n.y = a_base_square.y + h / pow(3.0, float(st));"
                                                                             "          b_n.x = a_n.x;"
                                                                             "          b_n.y = a_n.y + h / pow(3.0, float(st));"
                                                                             "          c_n.x = b_n.x + w / pow(3.0 , float(st));"
                                                                             "          c_n.y = b_n.y;"
                                                                             "          d_n.x = a_n.x + w / pow(3.0 , float(st));"
                                                                             "          d_n.y = a_n.y;"

                                                                             "          for(int i = 0; i < int(pow(3.0, float(st)) - 1.0); ++i){"
                                                                             "              a = a_n;"
                                                                             "              b = b_n;"
                                                                             "              c = c_n;"
                                                                             "              d = d_n;"
                                                                             "              for(int j = i; j < int(pow(3.0, float(st)) - 1.0); ++j){"
                                                                             "                  if(check(a, b, c, d, z)){"
                                                                             "                      gl_FragColor = vec4(0.0, 0.0, 0.0, 1.0);"
                                                                             "                      break;"
                                                                             "                  }"
                                                                             "                  a.x += 3.0 * (w / pow(3.0, float(st)));"
                                                                             "                  b.x += 3.0 * (w / pow(3.0, float(st)));"
                                                                             "                  c.x += 3.0 * (w / pow(3.0, float(st)));"
                                                                             "                  d.x += 3.0 * (w / pow(3.0, float(st)));"

                                                                             "              }"
                                                                             "              a_n.y += 3.0 * (h / pow(3.0, float(st)));"
                                                                             "              b_n.y += 3.0 * (h / pow(3.0, float(st)));"
                                                                             "              c_n.y += 3.0 * (h / pow(3.0, float(st)));"
                                                                             "              d_n.y += 3.0 * (h / pow(3.0, float(st)));"
                                                                             "          }"
                                                                             "      }"

                                                                             "  }"
                                                                             "  else{"
                                                                             "      gl_FragColor = vec4(0.0, 0.0, 0.0, 255.0);"
                                                                             "  }"
                                                                             "}");
        */
        // Снежинка Коха (доработка)
<<<<<<< Updated upstream
        /*
=======
        if(fractalType == 5)
>>>>>>> Stashed changes
        m_program->addCacheableShaderFromSourceCode(QOpenGLShader::Fragment, "uniform vec2 center;"
                                                                             "uniform vec2 a_base;"
                                                                             "uniform vec2 b_base;"
                                                                             "uniform vec2 c_base;"
                                                                             "uniform float scale;"
                                                                             "uniform float k;"
                                                                             "uniform int iter_koh;"
                                                                             "varying highp vec2 coords;"


                                                                             "bool check(vec2 a, vec2 b, vec2 c, vec2 z){"
                                                                             "  float k_ab = k, k_bc = -k, b_ac, b_ab, b_bc;"
                                                                             "  int znak = 1;"
                                                                             "  if(b.y < a.y){"
                                                                             "      znak = -1;"
                                                                             "      k_ab = -k;"
                                                                             "      k_bc = k;"
                                                                             "  }"
                                                                             "  b_ac = c.y;"
                                                                             "  b_ab = a.y - k_ab * a.x;"
                                                                             "  b_bc = c.y - k_bc * c.x;"
                                                                             "  if(znak * (k_ab * z.x + b_ab - z.y) >= 0 && znak * (k_bc * z.x + b_bc - z.y) >= 0 && znak * (b_ac - z.y) <= 0)"
                                                                             "      return true;"
                                                                             "  return false;"
                                                                             "}"



                                                                             "vec2 l_a(vec2 a, int znak, float st, float w, float h){"
                                                                             "  a.x = a.x;"
                                                                             "  a.y = a.y + znak * (h / pow(3,st) + h / pow(3,st));"
                                                                             "  return a;"
                                                                             "}"

                                                                             "vec2 l_b(vec2 a, int znak, float st, float w, float h){"
                                                                             "  a.x = a.x + w / (2 * pow(3, st));"
                                                                             "  a.y = a.y + znak * (h / pow(3, st));"
                                                                             "  return a;"
                                                                             "}"

                                                                             "vec2 l_c(vec2 a, int znak, float st, float w, float h){"
                                                                             "  a.x = a.x + w / pow(3,st);"
                                                                             "  a.y = a.y + znak * (h / pow(3, st) + h / pow(3, st));"
                                                                             "  return a;"
                                                                             "}"



                                                                             "vec2 c_a(vec2 a, int znak, float st, float w, float h){"
                                                                             "  a.x = a.x + w / pow(3, st);"
                                                                             "  a.y = a.y;"
                                                                             "  return a;"
                                                                             "}"

                                                                             "vec2 c_b(vec2 a, int znak, float st, float w, float h){"
                                                                             "  a.x = a.x + w / (2 * pow(3, st - 0.1));"
                                                                             "  a.y = a.y - znak * (h / pow(3, st));"
                                                                             "  return a;"
                                                                             "}"

                                                                             "vec2 c_c(vec2 a, int znak, float st, float w, float h){"
                                                                             "  a.x = a.x + w / pow(3, st) + w / pow(3, st);"
                                                                             "  a.y = a.y;"
                                                                             "  return a;"
                                                                             "}"



                                                                             "vec2 r_a(vec2 c, int znak, float st, float w, float h){"
                                                                             "  c.x = c.x - w / pow(3, st);"
                                                                             "  c.y = c.y + znak * (h / pow(3, st) + h / pow(3, st));"
                                                                             "  return c;"
                                                                             "}"

                                                                             "vec2 r_b(vec2 c, int znak, float st, float w, float h){"
                                                                             "  c.x = c.x - w / (2 * pow(3, st));"
                                                                             "  c.y = c.y + znak * (h / pow(3, st));"
                                                                             "  return c;"
                                                                             "}"

                                                                             "vec2 r_c(vec2 c, int znak, float st, float w, float h){"
                                                                             "  c.x = c.x;"
                                                                             "  c.y = c.y + znak * (h / pow(3, st) + h / pow(3, st));"
                                                                             "  return c;"
                                                                             "}"




                                                                             "bool fifth(vec2 a, vec2 b, vec2 c, vec2 z){"
                                                                             "  if(check(a,b,c,z))"
                                                                             "      return true;"
                                                                             "  return false;"
                                                                             "}"


                                                                             "bool fourth(vec2 a, vec2 b, vec2 c, vec2 z){"
                                                                             "  if(check(a,b,c,z))"
                                                                             "      return true;"

                                                                             "  if(iter_koh > 4){"
                                                                             "      vec2 a_n, b_n, c_n, a_const, c_const;"
                                                                             "      float w = abs(c.x - a.x);"
                                                                             "      float h = w * cos(radians(30.0f));"
                                                                             "      float st = 1.0;"
                                                                             "      int iter = 2;"
                                                                             "      int znak = 1;"
                                                                             "      if(b.y < a.y)"
                                                                             "          znak = -1;"

                                                                             "      st = 1.0;"
                                                                             "      a_n = l_a(a, znak, st, w, h);"
                                                                             "      b_n = l_b(a, znak, st, w, h);"
                                                                             "      c_n = l_c(a, znak, st, w, h);"

                                                                             "      if(fifth(a_n, b_n, c_n,z))"
                                                                             "          return true;"


                                                                             "      st = 1.0;"
                                                                             "      a_n = c_a(a, znak, st, w, h);"
                                                                             "      b_n = c_b(a, znak, st, w, h);"
                                                                             "      c_n = c_c(a, znak, st, w, h);"

                                                                             "      if(fifth(a_n, b_n, c_n,z))"
                                                                             "          return true;"

                                                                             "      st = 1.0;"
                                                                             "      a_n = r_a(c, znak, st, w, h);"
                                                                             "      b_n = r_b(c, znak, st, w, h);"
                                                                             "      c_n = r_c(c, znak, st, w, h);"

                                                                             "      if(fifth(a_n, b_n, c_n,z))"
                                                                             "          return true;"


                                                                             "  }"
                                                                             "  return false;"
                                                                             "}"


                                                                             "bool third(vec2 a, vec2 b, vec2 c, vec2 z){"
                                                                             "  if(check(a,b,c,z))"
                                                                             "      return true;"

                                                                             "  if(iter_koh > 3){"
                                                                             "      vec2 a_n, b_n, c_n, a_const, c_const;"
                                                                             "      float w = abs(c.x - a.x);"
                                                                             "      float h = w * cos(radians(30.0f));"
                                                                             "      float st = 1.0;"
                                                                             "      int iter = 2;"
                                                                             "      int znak = 1;"
                                                                             "      if(b.y < a.y)"
                                                                             "          znak = -1;"

                                                                             "      st = 1.0;"
                                                                             "      a_n = l_a(a, znak, st, w, h);"
                                                                             "      b_n = l_b(a, znak, st, w, h);"
                                                                             "      c_n = l_c(a, znak, st, w, h);"

                                                                             "      if(fourth(a_n, b_n, c_n,z))"
                                                                             "          return true;"

                                                                             "      st = 2.0;"
                                                                             "      iter = 4;"
                                                                             "      while(iter != iter_koh){"
                                                                             "          a_const = a;"
                                                                             "          for(int i = 0; i < pow(3, st - 1.0); ++i){"
                                                                             "              a_n = l_a(a_const, znak, st, w, h);"
                                                                             "              b_n = l_b(a_const, znak, st, w, h);"
                                                                             "              c_n = l_c(a_const, znak, st, w, h);"
                                                                             "              if(iter == 4 && fifth(a_n, b_n, c_n,z))"
                                                                             "                  return true;"
                                                                             "              a_const.x = a_const.x + w / (2 * pow(3, st - 1.0));"
                                                                             "              a_const.y = a_const.y + znak * (h / pow(3, st - 1.0));"
                                                                             "          }"
                                                                             "          ++iter;"
                                                                             "          ++st;"
                                                                             "      }"

                                                                             "      st = 1.0;"
                                                                             "      a_n = c_a(a, znak, st, w, h);"
                                                                             "      b_n = c_b(a, znak, st, w, h);"
                                                                             "      c_n = c_c(a, znak, st, w, h);"

                                                                             "      if(fourth(a_n, b_n, c_n,z))"
                                                                             "          return true;"

                                                                             "      st = 2.0;"
                                                                             "      iter = 4;"
                                                                             "      while(iter != iter_koh){"
                                                                             "          a_const = a;"
                                                                             "          for(int i = 0; i < pow(3, st - 1.0); ++i){"
                                                                             "              a_n = c_a(a_const, znak, st, w, h);"
                                                                             "              b_n = c_b(a_const, znak, st, w, h);"
                                                                             "              c_n = c_c(a_const, znak, st, w, h);"
                                                                             "              if(iter == 4 && fifth(a_n, b_n, c_n,z))"
                                                                             "                  return true;"
                                                                             "              a_const.x = a_const.x + w / pow(3, st - 1.0);"
                                                                             "          }"
                                                                             "          ++iter;"
                                                                             "          ++st;"
                                                                             "      }"

                                                                             "      st = 1.0;"
                                                                             "      a_n = r_a(c, znak, st, w, h);"
                                                                             "      b_n = r_b(c, znak, st, w, h);"
                                                                             "      c_n = r_c(c, znak, st, w, h);"

                                                                             "      if(fourth(a_n, b_n, c_n,z))"
                                                                             "          return true;"

                                                                             "      st = 2.0;"
                                                                             "      iter = 4;"
                                                                             "      while(iter != iter_koh){"
                                                                             "          c_const = c;"
                                                                             "          for(int i = 0; i < pow(3, st - 1.0); ++i){"
                                                                             "              a_n = r_a(c_const, znak, st, w, h);"
                                                                             "              b_n = r_b(c_const, znak, st, w, h);"
                                                                             "              c_n = r_c(c_const, znak, st, w, h);"
                                                                             "              if(iter == 4 && fifth(a_n, b_n, c_n,z))"
                                                                             "                  return true;"
                                                                             "              c_const.x = c_const.x - w / (2 * pow(3, st - 1.0));"
                                                                             "              c_const.y = c_const.y + znak * (h / pow(3, st - 1.0));"
                                                                             "          }"
                                                                             "          ++iter;"
                                                                             "          ++st;"
                                                                             "      }"
                                                                             "  }"
                                                                             "  return false;"
                                                                             "}"



                                                                             "bool second(vec2 a, vec2 b, vec2 c, vec2 z) {"
                                                                             "  if(check(a,b,c,z))"
                                                                             "      return true;"

                                                                             "      if(iter_koh > 2){"
                                                                             "      vec2 a_n, b_n, c_n, a_const, c_const;"
                                                                             "      float w = abs(c.x - a.x);"
                                                                             "      float h = w * cos(radians(30.0f));"
                                                                             "      float st = 1.0;"
                                                                             "      int iter = 2;"
                                                                             "      int znak = 1;"
                                                                             "      if(b.y < a.y)"
                                                                             "          znak = -1;"

                                                                             "      st = 1.0;"
                                                                             "      a_n = l_a(a, znak, st, w, h);"
                                                                             "      b_n = l_b(a, znak, st, w, h);"
                                                                             "      c_n = l_c(a, znak, st, w, h);"

                                                                             "      if(third(a_n, b_n, c_n,z))"
                                                                             "          return true;"

                                                                             "      st = 2.0;"
                                                                             "      iter = 3;"
                                                                             "      while(iter != iter_koh){"
                                                                             "          a_const = a;"
                                                                             "          for(int i = 0; i < pow(3, st - 1.0); ++i){"
                                                                             "              a_n = l_a(a_const, znak, st, w, h);"
                                                                             "              b_n = l_b(a_const, znak, st, w, h);"
                                                                             "              c_n = l_c(a_const, znak, st, w, h);"
                                                                             "              if(iter == 3 && fourth(a_n, b_n, c_n,z))"
                                                                             "                  return true;"
                                                                             "              if(iter == 4 && fifth(a_n, b_n, c_n,z))"
                                                                             "                  return true;"
                                                                             "              a_const.x = a_const.x + w / (2 * pow(3, st - 1.0));"
                                                                             "              a_const.y = a_const.y + znak * (h / pow(3, st - 1.0));"
                                                                             "          }"
                                                                             "          ++iter;"
                                                                             "          ++st;"
                                                                             "      }"

                                                                             "      st = 1.0;"
                                                                             "      a_n = c_a(a, znak, st, w, h);"
                                                                             "      b_n = c_b(a, znak, st, w, h);"
                                                                             "      c_n = c_c(a, znak, st, w, h);"

                                                                             "      if(third(a_n, b_n, c_n,z))"
                                                                             "          return true;"

                                                                             "      st = 2.0;"
                                                                             "      iter = 3;"
                                                                             "      while(iter != iter_koh){"
                                                                             "          a_const = a;"
                                                                             "          for(int i = 0; i < pow(3, st - 1.0); ++i){"
                                                                             "              a_n = c_a(a_const, znak, st, w, h);"
                                                                             "              b_n = c_b(a_const, znak, st, w, h);"
                                                                             "              c_n = c_c(a_const, znak, st, w, h);"
                                                                             "              if(iter == 3 && fourth(a_n, b_n, c_n,z))"
                                                                             "                  return true;"
                                                                             "              if(iter == 4 && fifth(a_n, b_n, c_n,z))"
                                                                             "                  return true;"
                                                                             "              a_const.x = a_const.x + w / pow(3, st - 1.0);"
                                                                             "          }"
                                                                             "          ++iter;"
                                                                             "          ++st;"
                                                                             "      }"

                                                                             "      st = 1.0;"
                                                                             "      a_n = r_a(c, znak, st, w, h);"
                                                                             "      b_n = r_b(c, znak, st, w, h);"
                                                                             "      c_n = r_c(c, znak, st, w, h);"

                                                                             "      if(third(a_n, b_n, c_n,z))"
                                                                             "          return true;"

                                                                             "      st = 2.0;"
                                                                             "      iter = 3;"
                                                                             "      while(iter != iter_koh){"
                                                                             "          c_const = c;"
                                                                             "          for(int i = 0; i < pow(3, st - 1.0); ++i){"
                                                                             "              a_n = r_a(c_const, znak, st, w, h);"
                                                                             "              b_n = r_b(c_const, znak, st, w, h);"
                                                                             "              c_n = r_c(c_const, znak, st, w, h);"
                                                                             "              if(iter == 3 && fourth(a_n, b_n, c_n,z))"
                                                                             "                  return true;"
                                                                             "              if(iter == 4 && fifth(a_n, b_n, c_n,z))"
                                                                             "                  return true;"
                                                                             "              c_const.x = c_const.x - w / (2 * pow(3, st - 1.0));"
                                                                             "              c_const.y = c_const.y + znak * (h / pow(3, st - 1.0));"
                                                                             "          }"
                                                                             "          ++iter;"
                                                                             "          ++st;"
                                                                             "      }"
                                                                             "  }"
                                                                             "  return false;"
                                                                             "}"



                                                                             "bool first(vec2 a, vec2 b, vec2 c, vec2 z) {"
                                                                             "  if(check(a,b,c,z))"
                                                                             "      return true;"

                                                                             "  if(iter_koh > 1){"
                                                                             "      vec2 a_n, b_n, c_n, a_const, c_const;"
                                                                             "      float w = abs(c.x - a.x);"
                                                                             "      float h = w * cos(radians(30.0f));"
                                                                             "      float st = 1.0;"
                                                                             "      int iter = 2;"
                                                                             "      int znak = 1;"
                                                                             "      if(b.y < a.y)"
                                                                             "          znak = -1;"

                                                                             "      st = 1.0;"
                                                                             "      a_n = l_a(a, znak, st, w, h);"
                                                                             "      b_n = l_b(a, znak, st, w, h);"
                                                                             "      c_n = l_c(a, znak, st, w, h);"

                                                                             "      if(second(a_n, b_n, c_n,z))"
                                                                             "          return true;"

                                                                             "      st = 2.0;"
                                                                             "      iter = 2;"
                                                                             "      while(iter != iter_koh){"
                                                                             "          a_const = a;"
                                                                             "          for(int i = 0; i < pow(3, st - 1.0); ++i){"
                                                                             "              a_n = l_a(a_const, znak, st, w, h);"
                                                                             "              b_n = l_b(a_const, znak, st, w, h);"
                                                                             "              c_n = l_c(a_const, znak, st, w, h);"
                                                                             "              if(iter == 2 && third(a_n, b_n, c_n,z))"
                                                                             "                  return true;"
                                                                             "              if(iter == 3 && fourth(a_n, b_n, c_n,z))"
                                                                             "                  return true;"
                                                                             "              if(iter == 4 && fifth(a_n, b_n, c_n,z) && i < 27)"
                                                                             "                  return true;"
                                                                             "              a_const.x = a_const.x + w / (2 * pow(3, st - 1.0));"
                                                                             "              a_const.y = a_const.y + h / pow(3, st - 1.0);"
                                                                             "          }"
                                                                             "          ++iter;"
                                                                             "          ++st;"
                                                                             "      }"

                                                                             "      st = 1.0;"
                                                                             "      a_n = c_a(a, znak, st, w, h);"
                                                                             "      b_n = c_b(a, znak, st, w, h);"
                                                                             "      c_n = c_c(a, znak, st, w, h);"

                                                                             "      if(second(a_n, b_n, c_n,z))"
                                                                             "          return true;"

                                                                             "      st = 2.0;"
                                                                             "      iter = 2;"
                                                                             "      while(iter != iter_koh){"
                                                                             "          a_const = a;"
                                                                             "          for(int i = 0; i < pow(3, st - 1.0); ++i){"
                                                                             "              a_n = c_a(a_const, znak, st, w, h);"
                                                                             "              b_n = c_b(a_const, znak, st, w, h);"
                                                                             "              c_n = c_c(a_const, znak, st, w, h);"
                                                                             "              if(iter == 2 && third(a_n, b_n, c_n,z))"
                                                                             "                  return true;"
                                                                             "              if(iter == 3 && fourth(a_n, b_n, c_n,z))"
                                                                             "                  return true;"
                                                                             "              if(iter == 4 && fifth(a_n, b_n, c_n,z) && i < 27)"
                                                                             "                  return true;"
                                                                             "              a_const.x = a_const.x + w / pow(3, st - 1.0);"
                                                                             "          }"
                                                                             "          ++iter;"
                                                                             "          ++st;"
                                                                             "      }"

                                                                             "      st = 1.0;"
                                                                             "      a_n = r_a(c, znak, st, w, h);"
                                                                             "      b_n = r_b(c, znak, st, w, h);"
                                                                             "      c_n = r_c(c, znak, st, w, h);"

                                                                             "      if(second(a_n, b_n, c_n,z))"
                                                                             "          return true;"

                                                                             "      st = 2.0;"
                                                                             "      iter = 2;"
                                                                             "      while(iter != iter_koh){"
                                                                             "          c_const = c;"
                                                                             "          for(int i = 0; i < pow(3, st - 1.0); ++i){"
                                                                             "              a_n = r_a(c_const, znak, st, w, h);"
                                                                             "              b_n = r_b(c_const, znak, st, w, h);"
                                                                             "              c_n = r_c(c_const, znak, st, w, h);"
                                                                             "              if(iter == 2 && third(a_n, b_n, c_n,z))"
                                                                             "                  return true;"
                                                                             "              if(iter == 3 && fourth(a_n, b_n, c_n,z))"
                                                                             "                  return true;"
                                                                             "              if(iter == 4 && fifth(a_n, b_n, c_n,z) && i < 27)"
                                                                             "                  return true;"
                                                                             "              c_const.x = c_const.x - w / (2 * pow(3, st - 1.0));"
                                                                             "              c_const.y = c_const.y + znak * (h / pow(3, st - 1.0));"
                                                                             "          }"
                                                                             "          ++iter;"
                                                                             "          ++st;"
                                                                             "      }"
                                                                             "  }"
                                                                             "  return false;"
                                                                             "}"


                                                                             "void main() {"
                                                                             "  vec2 z, a = a_base, b = b_base, c = c_base;"
                                                                             "  z.x = 1.3333 * (coords.x) * scale - center.x;"
                                                                             "  z.y = (coords.y - 0.22) * scale - center.y;"

                                                                             "  if(first(a_base, b_base, c_base, z))"
                                                                             "      gl_FragColor = vec4(0.0, 120.0, 0.0, 1.0);"

                                                                             "}");
        */
        m_program->bindAttributeLocation("vertices", 0);
        m_program->link();

    }
}

void FractalWindowRenderer::paint()
{
    m_window->beginExternalCommands();

<<<<<<< Updated upstream
    m_program->bind();
=======
    if(m_program)
    {


        m_window->beginExternalCommands();
>>>>>>> Stashed changes

    // glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_program->enableAttributeArray(0);

    float values[] = {
        -1, -1,
        1,  -1,
        -1,  1,
        1,   1
    };

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    //Общие переменные
    m_program->setAttributeArray(0, GL_FLOAT, values, 2);
    m_program->setUniformValue("scale", (float)1);
    m_program->setUniformValue("center", QPointF(0.0, 0.0));
    m_program->setUniformValue("iter", 1000);
    // Для Жюлье
    m_program->setUniformValue("iter_gulie", 40);
    m_program->setUniformValue("a_gulie", (float)0.53);
    // Для Треугольника Серписнского
    m_program->setUniformValue("iter_serp_triangle", 7);
    m_program->setUniformValue("k_serp", (float)1.75);
    m_program->setUniformValue("a_base_triangle", QPointF(-0.8, -0.7));
    m_program->setUniformValue("b_base_triangle", QPointF(0.0, 0.7));
    m_program->setUniformValue("c_base_triangle", QPointF(0.8, -0.7));
    // Для Ковра Серписнского
    m_program->setUniformValue("iter_serp_square", 5);
    m_program->setUniformValue("a_base_square", QPointF(-0.6, -0.6));
    m_program->setUniformValue("b_base_square", QPointF(-0.6, 0.6));
    m_program->setUniformValue("c_base_square", QPointF(0.6, 0.6));
    m_program->setUniformValue("d_base_square", QPointF(0.6, -0.6));
    // Для Снежинки Коха (На доработку)
    m_program->setUniformValue("iter_koh", 5);
    m_program->setUniformValue("k_koh", (float)1.75);
    m_program->setUniformValue("a_base_koh", QPointF(-0.8, -0.7));
    m_program->setUniformValue("b_base_koh", QPointF(0.0, 0.7));
    m_program->setUniformValue("c_base_koh", QPointF(0.8, -0.7));



    glViewport(m_viewportSize.width() * 0.333, m_viewportSize.height() * 0.01, m_viewportSize.width() * 0.663, m_viewportSize.height() * 0.98);

    glDisable(GL_DEPTH_TEST);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);

    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    m_program->disableAttributeArray(0);
    m_program->release();

    m_window->endExternalCommands();
}
