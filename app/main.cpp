#include "mainwindow.h"

#include <QApplication>
#include <QDBusMetaType>


#include "udisks2wrapper.h"


int main(int argc, char *argv[]) {
  QApplication app(argc, argv);

  UDisks2Wrapper::getInstance();

  /*QTranslator appTranslator;
  appTranslator.load(":/resources/translations/octopi_cachecleaner_" +
                     QLocale::system().name());
  app.installTranslator(&appTranslator);*/

  MainWindow w;
  w.show();

  //QResource::registerResource("./resources.qrc");

  return app.exec();
}

