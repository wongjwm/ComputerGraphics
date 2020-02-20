#pragma once

#include <QtGui>
#include <QtWidgets>
#include <QtOpenGL>
#include <vector>
#include <string>

#define USE_COLOR true
 
using namespace std;

/**
 * This is just a basic OpenGL widget that will allow a change of background color.
 */
class BasicWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
  Q_OBJECT

private:
  QString vertexShaderString() const;
  QString fragmentShaderString() const;
  void createShader();
  QOpenGLVertexArrayObject vao_;
  vector<GLfloat> bunny_vertices;
  vector<GLuint> bunny_indices;
  vector<GLfloat> monkey_vertices;
  vector<GLuint> monkey_indices;
  bool is_bunny;
  bool show_wireframe;
protected:
  // Required interaction overrides
  void keyReleaseEvent(QKeyEvent* keyEvent) override;

  // Required overrides form QOpenGLWidget
  void initializeGL() override;
  void resizeGL(int w, int h) override;
  void paintGL() override;

  QOpenGLShaderProgram shaderProgram_;
  QOpenGLBuffer b_vbo_;
  QOpenGLBuffer b_ibo_;
  QOpenGLBuffer m_ibo_;
  QOpenGLBuffer m_vbo_;


public:
  BasicWidget(QWidget* parent=nullptr);
  virtual ~BasicWidget();
  
  // Make sure we have some size that makes sense.
  QSize sizeHint() const {return QSize(800,600);}
};