#include "mainwindow.h"
#include "ui_mainwindow.h"


#include <kiconloader.h>

#include "storagedatamodel.h"

#include "drivepanel.h"
#include "mdraidpanel.h"


/*
 *
 */
MainWindow::MainWindow(QWidget* parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
  ui -> setupUi(this);

  //http://stackoverflow.com/questions/3639468/what-qt-widgets-to-use-for-read-only-scrollable-collapsible-icon-list
  ui -> listView -> setMovement(QListView::Static);
  ui -> listView -> setResizeMode(QListView::Adjust);
  ui -> listView -> setViewMode(QListView::IconMode);
  ui -> listView -> setGridSize( QSize(150, 100));

  StorageDataModel* model = new StorageDataModel();
  ui -> listView -> setModel(model);
  connect(ui -> actionRefresh, SIGNAL(triggered()), model, SLOT(refresh()));

  ui -> stackedWidget -> addWidget(new DrivePanel(this));
  ui -> stackedWidget -> addWidget(new MDRaidPanel(this));

  ui -> splitter -> setStretchFactor(0, 1);
  ui -> splitter -> setStretchFactor(1, 2);


  //GroupBox title style
  QFont f;
  ui -> groupBox -> setStyleSheet("QGroupBox { font-weight: bold; font-size: " %  QString::number(f.pointSize() + 4) % "pt;};");

  connect(ui -> refreshDetailsButton, SIGNAL(clicked()), this, SLOT(refreshDetails()));

  //connect(ui -> listView, SIGNAL(activated(QModelIndex)), this, SLOT(unitSelected(QModelIndex)));
  connect(ui -> listView -> selectionModel(), SIGNAL(currentChanged(QModelIndex,QModelIndex)), this, SLOT(unitSelected(QModelIndex)));
}



/*
 *
 */
MainWindow::~MainWindow()
{
  delete ui;
}



/*
 *
 */
void MainWindow::unitSelected(const QModelIndex& index)
{
  int widgetIndex = 0;
  QString boxTitle = tr("Details");

  if(!index.isValid() || index.data(Qt::UserRole).value<StorageUnit*>() == NULL) {
    ui -> groupBox -> setTitle(boxTitle);
    ui -> stackedWidget -> setCurrentIndex(widgetIndex);

    return;
  }

  StorageUnit* u = index.data(Qt::UserRole).value<StorageUnit*>();
  u -> update();
  updateHealthStatus(u);

  if(u -> isDrive()) {
    DrivePanel* panel = (DrivePanel*) ui -> stackedWidget -> widget(1);
    panel -> setDrive((Drive*) u);

    widgetIndex = 1;
    boxTitle = tr("Drive") % " " % u -> getName() % " (" % u-> getDevice() % ")";

  } else if(u -> isMDRaid()) {
    MDRaidPanel* panel = (MDRaidPanel*) ui -> stackedWidget -> widget(2);
    panel -> setMDRaid((MDRaid*) u);

    widgetIndex = 2;
    boxTitle = tr("MDRaid") % " " % u -> getName() % " (" % u -> getDevice() % ")";

  }

  ui -> groupBox -> setTitle(boxTitle);
  ui -> stackedWidget -> setCurrentIndex(widgetIndex);
}



/*
 *
 */
void MainWindow::refreshDetails()
{
  switch(ui -> stackedWidget -> currentIndex()) {
    case 1:
    case 2: ((StorageUnitPanel*) ui -> stackedWidget -> currentWidget()) -> refresh(); break;
    default: break;
  }

  QModelIndex currentIndex = ui -> listView -> currentIndex();

  if(currentIndex.isValid() && currentIndex.data(Qt::UserRole).value<StorageUnit*>() != NULL)
    updateHealthStatus(ui -> listView -> currentIndex().data(Qt::UserRole).value<StorageUnit*>());
}



/*
 *
 */
void MainWindow::updateHealthStatus(StorageUnit* unit)
{
  QString style;
  QString text;
  QPixmap icon;

  if(!unit -> isFailingStatusKnown()) {
    style = "QLabel { color: orange; }";
    text = tr("Unknown");
    icon = KIconLoader::global() -> loadIcon("face-confused", KIconLoader::Desktop, 16);

  } else if(unit -> isFailing()) {
    style = "QLabel { color: red; }";
    text = tr("Failing");
    icon = KIconLoader::global() -> loadIcon("face-sick", KIconLoader::Desktop, 16);

  } else {
    text = tr("Healthy");
    icon = KIconLoader::global() -> loadIcon("face-cool", KIconLoader::Desktop, 16);
  }

  ui -> iconLabel -> setPixmap(icon);
  ui -> statusLabel -> setText(text);
  ui -> statusLabel -> setStyleSheet(style);
}

