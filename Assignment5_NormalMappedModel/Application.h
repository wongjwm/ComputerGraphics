/**
 * The primary application code.
 */

#include <QtGui>
#include <QtCore>
#include <QtWidgets>
using namespace std;

class Application : public QMainWindow
{
  Q_OBJECT

public:
  Application(string objFile, QWidget* parent=0);
  void setFile(string objectFile);
  virtual ~Application();
  
signals:

public slots:

private:
  string objectFile;
  void buildGui();
};