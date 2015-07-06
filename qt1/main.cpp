#include <QApplication>
#include <QDialog>
#include <QLabel>

int main(int args, char **argv) {
  QApplication app(args, argv);
  QDialog dlg;
  QLabel *label = new QLabel("HELLO!");
  
  dlg.setVisible(true);
  label->show();
  return app.exec();
}