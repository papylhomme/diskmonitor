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
#include "ui_mainwindow.h"

#include <QIcon>
#include <KHelpMenu>
#include <KLocalizedString>

#include "storageunitmodel.h"
#include "drivepanel.h"
#include "mdraidpanel.h"

#include "diskmonitor_settings.h"
#include "configdialog.h"


#include <QDebug>


/*
 * Constructor
 */
MainWindow::MainWindow(QWidget* parent) :
    KMainWindow(parent),
    ui(new Ui::MainWindow)
{
  ui -> setupUi(this);

  /*
   * setup KDE default help menu
   */
  KHelpMenu* helpMenu = new KHelpMenu(this, "some text", false);
  menuBar() -> addMenu(helpMenu -> menu());


  /*
   * setup the main list view
   */
  //http://stackoverflow.com/questions/3639468/what-qt-widgets-to-use-for-read-only-scrollable-collapsible-icon-list
  ui -> listView -> setMovement(QListView::Static);
  ui -> listView -> setResizeMode(QListView::Adjust);
  ui -> listView -> setViewMode(QListView::IconMode);
  ui -> listView -> setGridSize( QSize(150, 100));
  ui -> listView -> setWrapping(true);
  ui -> listView -> setWordWrap(true);
  ui -> listView -> setMinimumHeight(100);

  storageUnitModel = new StorageUnitModel();
  ui -> listView -> setModel(storageUnitModel);
  connect(ui -> actionRefresh, SIGNAL(triggered()), storageUnitModel, SLOT(refresh()));

  //connect(ui -> listView, SIGNAL(activated(QModelIndex)), this, SLOT(unitSelected(QModelIndex)));
  connect(ui -> listView -> selectionModel(), SIGNAL(currentChanged(QModelIndex,QModelIndex)), this, SLOT(unitSelected(QModelIndex)));


  /*
   * setup details panels
   */
  ui -> stackedWidget -> addWidget(new DrivePanel(this));
  ui -> stackedWidget -> addWidget(new MDRaidPanel(this));

  ui -> splitter -> setStretchFactor(0, 1);
  ui -> splitter -> setStretchFactor(1, 2);

  //GroupBox title style
  QFont f;
  ui -> groupBox -> setStyleSheet("QGroupBox { font-weight: bold; font-size: " %  QString::number(f.pointSize() + 4) % "pt;};");

  connect(ui -> refreshDetailsButton, SIGNAL(clicked()), this, SLOT(refreshDetails()));


  /*
   * Setup settings
   */
  connect(ui -> actionSettings, SIGNAL(triggered()), this, SLOT(showSettings()));
  connect(DiskMonitorSettings::self(), SIGNAL(configChanged()), this, SLOT(configChanged()));
}



/*
 * Destructor
 */
MainWindow::~MainWindow()
{
  delete storageUnitModel;
  delete ui;
}



/*
 * Set the select unit
 *
 * @param path The unit path
 */
void MainWindow::setSelectedUnit(const QString& path)
{
  QList<StorageUnit*> units = UDisks2Wrapper::instance() -> listStorageUnits();

  int i = 0;
  foreach(StorageUnit* u, units) {
    if(u -> getPath() == path)
      ui -> listView -> setCurrentIndex(storageUnitModel -> index(i, 0));

    i++;
  }
}



/*
 * Handle selection on the main list view and update
 * the details panel accordingly
 */
void MainWindow::unitSelected(const QModelIndex& index)
{
  int widgetIndex = 0;
  QString boxTitle = i18n("Details");

  //disconnect the old selected unit if needed
  if(currentUnit != NULL)
    disconnect(currentUnit, SIGNAL(updated(StorageUnit*)), this, SLOT(updateHealthStatus(StorageUnit*)));

  /*
   * No StorageUnit available, reset the view
   */
  if(!index.isValid() || index.data(Qt::UserRole).value<StorageUnit*>() == NULL) {
    ui -> groupBox -> setTitle(boxTitle);
    ui -> stackedWidget -> setCurrentIndex(widgetIndex);

    return;
  }


  /*
   * StorageUnit selected, set the details panel accordingly
   */
  StorageUnit* u = index.data(Qt::UserRole).value<StorageUnit*>();
  currentUnit = u;
  connect(currentUnit, SIGNAL(updated(StorageUnit*)), this, SLOT(updateHealthStatus(StorageUnit*)));
  currentUnit -> update();


  //select the panel to display
  StorageUnitPanel* panel = NULL;
  if(currentUnit -> isDrive()) {
    widgetIndex = 1;
    panel = (DrivePanel*) ui -> stackedWidget -> widget(1);
    boxTitle = i18n("Drive %1 (%2)", u -> getName(), u -> getDevice());

  } else if(u -> isMDRaid()) {
    widgetIndex = 2;
    panel = (MDRaidPanel*) ui -> stackedWidget -> widget(2);
    boxTitle = i18n("MDRaid %1 (%2)", u -> getName(), u -> getDevice());
  }

  panel -> setStorageUnit(currentUnit);
  ui -> groupBox -> setTitle(boxTitle);
  ui -> stackedWidget -> setCurrentIndex(widgetIndex);
}



/*
 * Call the refresh action on the active panel
 */
void MainWindow::refreshDetails()
{
  switch(ui -> stackedWidget -> currentIndex()) {
    case 1:
    case 2: ((StorageUnitPanel*) ui -> stackedWidget -> currentWidget()) -> refresh(); break;
    default: break;
  }
}



/*
 * Update the health status labels for the given unit
 */
void MainWindow::updateHealthStatus(StorageUnit* unit)
{
  QString style;
  QString text;
  QPixmap icon;

  if(!unit -> isFailingStatusKnown()) {
    style = "QLabel { color: " + DiskMonitorSettings::warningColor().name() + "; }";
    text = i18nc("Unknown health status", "Unknown");
    icon = QIcon::fromTheme(iconProvider.unknown()).pixmap(QSize(16,16));

  } else if(unit -> isFailing()) {
    style = "QLabel { color: " + DiskMonitorSettings::errorColor().name() + "; }";
    text = i18nc("Failing health status", "Failing");
    icon = QIcon::fromTheme(iconProvider.failing()).pixmap(QSize(16,16));

  } else {
    text = i18nc("Healthy health status", "Healthy");
    icon = QIcon::fromTheme(iconProvider.healthy()).pixmap(QSize(16,16));
  }

  ui -> iconLabel -> setPixmap(icon);
  ui -> statusLabel -> setText(text);
  ui -> statusLabel -> setStyleSheet(style);
}



/*
 * Display the application settings
 */
void MainWindow::showSettings()
{
  Settings::ConfigDialog::showDialog(this);
}



/*
 * Handle configuration change, reload main list and details panel
 */
void MainWindow::configChanged()
{
  qDebug() << "DiskMonitor::MainWindow - Configuration changed, updating UI...";

  storageUnitModel -> refresh();
}

