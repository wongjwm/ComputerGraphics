#include "BasicWidget.h"
#include "Parser.h"

#include <vector>
#include <iostream>

using namespace std;

//////////////////////////////////////////////////////////////////////
// Publics
BasicWidget::BasicWidget(string obFile, QWidget* parent) : QOpenGLWidget(parent), logger_(this)
{
  objectFile = obFile;
  cout << "In BasicWidget constructor, objectfile = " << objectFile << endl;

  setFocusPolicy(Qt::StrongFocus);
  isWireframe = false;
}

BasicWidget::~BasicWidget()
{
  for (auto renderable : renderables_) {
    delete renderable;
  }
  renderables_.clear();
}

///////////////////////////////////////////////////////////////////////
// Protected
void BasicWidget::keyReleaseEvent(QKeyEvent* keyEvent)
{
  if (keyEvent->key() == Qt::Key_1) {
    update();  
  } else if (keyEvent->key() == Qt::Key_2) {
    update();
  } else if (keyEvent->key() == Qt::Key_Q) {
    exit(0);
  } else if (keyEvent->key() == Qt::Key_W) {
    isWireframe = !isWireframe;
    update();
  } else {
    qDebug() << "You Pressed an unsupported Key!";
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


  Parser test;

  //test.parse("../objects/house/house_obj.obj");
  test.parse(objectFile);

  Renderable* ren = new Renderable();
  ren->init(test);
  ren->setRotationAxis(QVector3D(0., 1., 0.));
  renderables_.push_back(ren);

  glViewport(0, 0, width(), height());
  frameTimer_.start();
}

void BasicWidget::resizeGL(int w, int h)
{
  if (!logger_.isLogging()) {
    logger_.initialize();
    // Setup the logger for real-time messaging
    connect(&logger_, &QOpenGLDebugLogger::messageLogged, [=]() {
      const QList<QOpenGLDebugMessage> messages = logger_.loggedMessages();
      for (auto msg : messages) {
        qDebug() << msg;
      }
    });
    logger_.startLogging();
  }

  view_.setToIdentity();
  view_.lookAt(QVector3D(0.0f, 0.0f, 4.0f),
      QVector3D(0.0f, 0.0f, 0.0f),
      QVector3D(0.0f, 1.0f, 0.0f));

  projection_.setToIdentity();
  projection_.perspective(70.f, (float)w/(float)h, 0.001, 1000.0);

  glViewport(0, 0, w, h);
}

void BasicWidget::paintGL()
{
  qint64 msSinceRestart = frameTimer_.restart();
  glEnable(GL_DEPTH_TEST);
  glDisable(GL_CULL_FACE);

  glClearColor(0.f, 0.f, 0.f, 1.f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glPolygonMode(GL_FRONT_AND_BACK, isWireframe ? GL_LINE : GL_FILL);

  for (auto renderable : renderables_) {
      renderable->update(msSinceRestart);
      renderable->draw(view_, projection_);
  }
  update();
}