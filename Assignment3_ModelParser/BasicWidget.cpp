#include "BasicWidget.h"
#include "Parser.h"
#include <vector>
#include <iostream>

using namespace std;

//////////////////////////////////////////////////////////////////////
// Publics
BasicWidget::BasicWidget(QWidget* parent) : QOpenGLWidget(parent), 
m_vbo_(QOpenGLBuffer::VertexBuffer), 
m_ibo_(QOpenGLBuffer::IndexBuffer), 
b_vbo_(QOpenGLBuffer::VertexBuffer), 
b_ibo_(QOpenGLBuffer::IndexBuffer)
{
  setFocusPolicy(Qt::StrongFocus);
  is_bunny = true;
  show_wireframe = false;
}

BasicWidget::~BasicWidget()
{
  b_vbo_.release();
  b_vbo_.destroy();
  b_ibo_.release();
  b_ibo_.destroy();
  m_vbo_.release();
  m_vbo_.destroy();
  m_ibo_.release();
  m_ibo_.destroy();
  vao_.release();
  vao_.destroy();
}

//////////////////////////////////////////////////////////////////////
// Privates
QString BasicWidget::vertexShaderString() const
{
  QString str =
	"#version 330\n"
	"layout(location = 0) in vec3 position;\n"
    "layout(location = 1) in vec4 color;\n"
    "out vec4 vertColor;\n"
	"void main()\n"
	"{\n"
	"  gl_Position = vec4(position, 1.0);\n"
    "  vertColor = color;\n"
    "}\n";
  return str;
}

QString BasicWidget::fragmentShaderString() const
{
  QString str =
	"#version 330\n"
    "in vec4 vertColor;\n"
	"out vec4 color;\n"
	"void main()\n"
	"{\n"
	"  color = vec4(1.0f, 1.0f, 1.0f, 1.0f);\n"
	"}\n";
  return str;
}

///////////////////////////////////////////////////////////////////////
// Protected
void BasicWidget::keyReleaseEvent(QKeyEvent* keyEvent)
{
  if (keyEvent->key() == Qt::Key_1) {
    qDebug() << "1 - Bunny";
    is_bunny = true;
    update();  
  } else if (keyEvent->key() == Qt::Key_2) {
    qDebug() << "2 - Monkey";
    is_bunny = false;
    update();
  } else if (keyEvent->key() == Qt::Key_Q) {
    exit(0);
  } else if (keyEvent->key() == Qt::Key_W) {
    show_wireframe = !show_wireframe;
    update();
  } else {
  qDebug() << "You Pressed an unsupported Key!";
  }
}

void BasicWidget::createShader()
{
  QOpenGLShader vert(QOpenGLShader::Vertex);
  vert.compileSourceCode(vertexShaderString());
  QOpenGLShader frag(QOpenGLShader::Fragment);
  frag.compileSourceCode(fragmentShaderString());

  bool ok = shaderProgram_.addShader(&vert);
  if (!ok) {
    qDebug() << shaderProgram_.log();
  }

  ok = shaderProgram_.addShader(&frag);
  if (!ok) {
    qDebug() << shaderProgram_.log();
  }

  ok = shaderProgram_.link();
  if (!ok) {
	  qDebug() << shaderProgram_.log();
  }
}

void BasicWidget::initializeGL()
{
  makeCurrent();
  initializeOpenGLFunctions();

  QOpenGLContext* curContext = this->context();
  qDebug() << "[BasicWidget]::initializeGL() -- Context Information:";
  qDebug() << "  Context Valid: " << std::string(curContext->isValid() ? "true" : "false").c_str();
  qDebug() << "  GL Version Used: " << curContext->format().majorVersion() << "." << curContext->format().minorVersion();
  qDebug() << "  Vendor: " << reinterpret_cast<const char*>(glGetString(GL_VENDOR));
  qDebug() << "  Renderer: " << reinterpret_cast<const char*>(glGetString(GL_RENDERER));
  qDebug() << "  Version: " << reinterpret_cast<const char*>(glGetString(GL_VERSION));
  qDebug() << "  GLSL Version: " << reinterpret_cast<const char*>(glGetString(GL_SHADING_LANGUAGE_VERSION));

  createShader();
 
  Parser bunny_parser;
  Parser monkey_parser;
  
  bunny_parser.parse("../objects/bunny_centered.obj");
  monkey_parser.parse("../objects/monkey_centered.obj");

  bunny_vertices = bunny_parser.getVertices();
  bunny_indices = bunny_parser.getVertexIndices();

  monkey_vertices = monkey_parser.getVertices();
  monkey_indices = monkey_parser.getVertexIndices();

  shaderProgram_.bind();

  b_vbo_.setUsagePattern(QOpenGLBuffer::StaticDraw);
  b_vbo_.create();
  b_vbo_.bind();
  b_vbo_.allocate(bunny_vertices.data(), bunny_vertices.size() * sizeof(GL_FLOAT));

  b_ibo_.setUsagePattern(QOpenGLBuffer::StaticDraw);
  b_ibo_.create();
  b_ibo_.bind();
  b_ibo_.allocate(bunny_indices.data(), bunny_indices.size() * sizeof(GL_INT));

  m_vbo_.setUsagePattern(QOpenGLBuffer::StaticDraw);
  m_vbo_.create();
  m_vbo_.bind();
  m_vbo_.allocate(monkey_vertices.data(), monkey_vertices.size() * sizeof(GL_FLOAT));

  m_ibo_.setUsagePattern(QOpenGLBuffer::StaticDraw);
  m_ibo_.create();
  m_ibo_.bind();
  m_ibo_.allocate(monkey_indices.data(), monkey_indices.size() * sizeof(GL_INT));

  vao_.create();
  vao_.bind();
  b_vbo_.bind();
  shaderProgram_.enableAttributeArray(0);
  shaderProgram_.setAttributeBuffer(0, GL_FLOAT, 0, 3);

  b_ibo_.bind();
  // Releae the vao THEN the vbo
  vao_.release();
  shaderProgram_.release();
  glViewport(0, 0, width(), height());
}

void BasicWidget::resizeGL(int w, int h)
{
  glViewport(0, 0, w, h);
}

void BasicWidget::paintGL()
{
  glDisable(GL_DEPTH_TEST);
  glDisable(GL_CULL_FACE);

  glClearColor(0.f, 0.f, 0.f, 1.f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  shaderProgram_.bind();
  vao_.bind();
  
  glPolygonMode(GL_FRONT_AND_BACK, show_wireframe ? GL_LINE : GL_FILL);
  
  if (is_bunny) {
    b_vbo_.bind();
    shaderProgram_.enableAttributeArray(0);
    shaderProgram_.setAttributeBuffer(0, GL_FLOAT, 0, 3);
    b_ibo_.bind();
    glDrawElements(GL_TRIANGLES, bunny_indices.size(), GL_UNSIGNED_INT, 0);
    
  } else {
    m_vbo_.bind();
    shaderProgram_.enableAttributeArray(0);
    shaderProgram_.setAttributeBuffer(0, GL_FLOAT, 0, 3);
    m_ibo_.bind();
    glDrawElements(GL_TRIANGLES, monkey_indices.size(), GL_UNSIGNED_INT, 0);
  }
  
  vao_.release();
  shaderProgram_.release();

}