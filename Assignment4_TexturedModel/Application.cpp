#include "Application.h"
#include "BasicWidget.h"
using namespace std;

Application::Application(string objFile, QWidget* parent) : QMainWindow(parent)
{
  objectFile = objFile;
  buildGui();
}

Application::~Application()
{}

void Application::buildGui()
{
  // A simple menubar.
  QMenuBar* menu = menuBar();
  QMenu* file = menu->addMenu("File");
  QAction* exit = file->addAction("Quit", [this]() {close();});

  // Our basic widget.
  BasicWidget* widget = new BasicWidget(objectFile, this);
  setCentralWidget(widget);
}