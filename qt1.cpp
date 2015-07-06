#include <qapplication.h>
#include <qmainwindow.h>

int main(int argc, char **argv) {
  QApplication app(argc, argv);
  QMainWindow *window = new QMainWindos();
  app.setMainWidget(window);
  window->show();
  return app.exec();
}