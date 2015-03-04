#include "mainwindow.h"

#include <QApplication>
#include <KAboutData>
#include <KLocalizedString>

#include "udisks2wrapper.h"


int main(int argc, char *argv[]) {
  KLocalizedString::setApplicationDomain("diskmonitor");
  QApplication app(argc, argv);

  KAboutData about("diskmonitor", i18n("DisKMonitor"), "0.1",
    i18n("KDE tools to monitor SMART devices and MDRaid health status"),
    KAboutLicense::GPL_V2,
    i18n("Copyright (C) 2015 Michaël Lhomme"),
    QString(),
    "https://github.com/papylhomme/diskmonitor",
    QString()
  );

  about.addAuthor("Michaël Lhomme", i18n("Maintainer & Developer"), "papylhomme@gmail.com", QString(), QString());
  about.setCustomAuthorText(
    i18n("Please report bugs directly to ") + "https://github.com/papylhomme/diskmonitor/issues",
    i18n("Please report bugs directly to ") + "<a href='https://github.com/papylhomme/diskmonitor/issues'>GitHub</a>");

  KAboutData::setApplicationData(about);

  UDisks2Wrapper::instance();
  MainWindow* w = new MainWindow();
  w -> show();

  if(argc == 2)
    w -> setSelectedUnit(QString(argv[1]));

  return app.exec();
}

