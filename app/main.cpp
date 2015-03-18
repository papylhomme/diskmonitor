/****************************************************************************
 * DisKMonitor, KDE tools to monitor SMART and MDRaid health status         *
 * Copyright (C) 2014-2015 Michaël Lhomme <papylhomme@gmail.com>            *
 *                                                                          *
 * This program is free software; you can redistribute it and/or modify     *
 * it under the terms of the GNU General Public License as published by     *
 * the Free Software Foundation; either version 2 of the License, or        *
 * (at your option) any later version.                                      *
 *                                                                          *
 * This program is distributed in the hope that it will be useful,          *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of           *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the            *
 * GNU General Public License for more details.                             *
 *                                                                          *
 * You should have received a copy of the GNU General Public License along  *
 * with this program; if not, write to the Free Software Foundation, Inc.,  *
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.              *
 ****************************************************************************/


#include "mainwindow.h"

#include <QApplication>
#include <KLocalizedString>
#include <KAboutData>

#include "udisks2wrapper.h"
#include "diskmonitor_settings.h"
#include "config.h"


int main(int argc, char *argv[]) {
  KLocalizedString::setApplicationDomain("diskmonitor");
  QApplication app(argc, argv);

  KAboutData about("diskmonitor", i18n("DisKMonitor"), DISKMONITOR_VERSION,
    i18n("KDE tools to monitor SMART devices and MDRaid health status"),
    KAboutLicense::GPL_V2,
    i18n("Copyright (C) 2015 Michaël Lhomme"),
    QString(),
    "https://github.com/papylhomme/diskmonitor",
    QString()
  );

  about.addAuthor(i18n("Michaël Lhomme"), i18n("Maintainer & Developer"), "papylhomme@gmail.com", QString(), QString());
  about.setCustomAuthorText(
    i18n("Please report bugs directly to %1", QString("https://github.com/papylhomme/diskmonitor/issues")),
    i18n("Please report bugs directly to %1", QString("<a href='https://github.com/papylhomme/diskmonitor/issues'>GitHub</a>"))
  );

  KAboutData::setApplicationData(about);

  UDisks2Wrapper::instance() -> addDriveMonitor(new DriveMonitor(DiskMonitorSettings::sensitiveAttributes()));

  MainWindow* w = new MainWindow();
  w -> show();

  if(argc == 2)
    w -> setSelectedUnit(QString(argv[1]));

  return app.exec();
}

