#include "fractalwindowrenderer.h"
#include <iostream>

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
                                                                             "  vec2 z, c;"
                                                                             "  c.x = 1.3333 * (coords.x - 0.5) * scale - center.x;"
                                                                             "  c.y = (coords.y) * scale - center.y;"
                                                                             "  z.x = 0;"
                                                                             "  z.y = 0;"

                                                                             "  int i = 0;"
                                                                             "  float x = z.x;"
                                                                             "  float y = z.y;"

                                                                             "  while(i < iter && (x * x + y * y) <= 4.0) {"
                                                                             "      x = (z.x * z.x - z.y * z.y) + c.x;"
                                                                             "      y = (2 * z.x * z.y) + c.y;"
                                                                             "      z.x = x;"
                                                                             "      z.y = y;"
                                                                             "      ++i;"
                                                                             "  }"

                                                                             "if(i == iter)"
                                                                             "  gl_FragColor = vec4(0.0, 120.0, 0.0, 1.0);"
                                                                             "}");
        */
        // Фрактал Жулья
        /*
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
                                                                             "      y = (2 * z.x * z.y) + c.y;"
                                                                             "      z.x = x;"
                                                                             "      z.y = y;"
                                                                             "      ++i;"
                                                                             "  }"

                                                                             "if(i == iter_gulie)"
                                                                             "  gl_FragColor = vec4(0.0, 122.0, 0.0, 1.0);"
                                                                             "}");
        */

        // Треугольники Серпинского
        ///*
        m_program->addCacheableShaderFromSourceCode(QOpenGLShader::Fragment, "uniform vec2 center;"
                                                                             "uniform vec2 a_base;"
                                                                             "uniform vec2 b_base;"
                                                                             "uniform vec2 c_base;"
                                                                             "uniform float scale;"
                                                                             "uniform float k;"
                                                                             "uniform int iter_serp;"
                                                                             "varying highp vec2 coords;"


                                                                             "bool check(vec2 a, vec2 b, vec2 c, vec2 z){"
                                                                             "  float k_ab = -k, k_bc = k, b_ac, b_ab, b_bc;"
                                                                             "  b_ac = c.y;"
                                                                             "  b_ab = a.y - k_ab * a.x;"
                                                                             "  b_bc = c.y - k_bc * c.x;"
                                                                             "  if(k_ab * z.x + b_ab - z.y <= 0 && k_bc * z.x + b_bc - z.y <= 0 && b_ac - z.y >= 0)"
                                                                             "      return true;"
                                                                             "  return false;"
                                                                             "}"


                                                                             "void main() {"
                                                                             "  vec2 z, a, b, c, a_n, b_n, c_n;"
                                                                             "  z.x = 1.3333 * (coords.x) * scale - center.x;"
                                                                             "  z.y = (coords.y) * scale - center.y;"
                                                                             "  float w = abs(c_base.x - a_base.x);"
                                                                             "  float h = w * cos(radians(30.0f));"

                                                                             "  float k_ab = k, k_bc = -k, b_ac, b_ab, b_bc;"
                                                                             "  b_ac = c_base.y;"
                                                                             "  b_ab = a_base.y - k_ab * a_base.x;"
                                                                             "  b_bc = c_base.y - k_bc * c_base.x;"
                                                                             "  if(k_ab * z.x + b_ab - z.y >= 0 && k_bc * z.x + b_bc - z.y >= 0 && b_ac - z.y <= 0){"
                                                                             "      gl_FragColor = vec4(0.0, 120.0, 0.0, 1.0);"

                                                                             "      for(float st = 1.0; st < iter_serp; ++st){"
                                                                             "          a_n.x = a_base.x + w / pow(2.0, st + 1.0);"
                                                                             "          a_n.y = a_base.y + h / pow(2.0, st);"
                                                                             "          b_n.x = a_base.x + w / pow(2.0, st);"
                                                                             "          b_n.y = a_base.y;"
                                                                             "          c_n.x = a_n.x + w / pow(2.0, st);"
                                                                             "          c_n.y = a_n.y;"

                                                                             "          for(int i = 0; i < pow(2, st) - 1; ++i){"
                                                                             "              a = a_n;"
                                                                             "              b = b_n;"
                                                                             "              c = c_n;"
                                                                             "              for(int j = i; j < pow(2, st) - 1; ++j){"
                                                                             "                  if(check(a, b, c, z)){"
                                                                             "                      gl_FragColor = vec4(0.0, 0.0, 0.0, 1.0);"
                                                                             "                      break;"
                                                                             "                  }"
                                                                             "                  a.x += w / pow(2.0, st);"
                                                                             "                  b.x += w / pow(2.0, st);"
                                                                             "                  c.x += w / pow(2.0, st);"
                                                                             "              }"

                                                                             "              a_n.x = b_n.x;"
                                                                             "              a_n.y += h / pow(2, st);"
                                                                             "              b_n.x = c_n.x;"
                                                                             "              b_n.y += a_n.y;"
                                                                             "              c_n.x += w / pow(2.0, st + 1.0);"
                                                                             "              c_n.y = a_n.y;"
                                                                             "          }"
                                                                             "      }"
                                                                             "  }"
                                                                             "}");
        //*/

        // Снежинка Коха
        /*
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
    m_program->setUniformValue("a_gulie", (float)0.5);
    m_program->setUniformValue("center", QPointF(0.0, 0.0));
    m_program->setUniformValue("iter", 1000);
    m_program->setUniformValue("iter_gulie", 81);
    m_program->setUniformValue("iter_serp", 7);
    m_program->setUniformValue("iter_koh", 5);
    m_program->setUniformValue("k", (float)1.75);
    m_program->setUniformValue("a_base", QPointF(-0.8, -0.7));
    m_program->setUniformValue("b_base", QPointF(0.0, 0.7));
    m_program->setUniformValue("c_base", QPointF(0.8, -0.7));
    //std::cout<<'1' << std::endl;
    glViewport(m_viewportSize.width() * 0.333, m_viewportSize.height() * 0.01, m_viewportSize.width() * 0.663, m_viewportSize.height() * 0.98);

    glDisable(GL_DEPTH_TEST);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);

    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    m_program->disableAttributeArray(0);
    m_program->release();

    m_window->endExternalCommands();
}
