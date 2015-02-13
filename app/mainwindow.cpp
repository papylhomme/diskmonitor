#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QIcon>
#include <KHelpMenu>
#include <KConfigDialog>
#include <KLocalizedString>

#include "storageunitmodel.h"
#include "drivepanel.h"
#include "mdraidpanel.h"

#include "settings/diskmonitor_settings.h"
#include "appearance.h"
#include "smart.h"


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
  menuBar() -> addMenu(helpMenu->menu());


  /*
   * setup the main list view
   */
  //http://stackoverflow.com/questions/3639468/what-qt-widgets-to-use-for-read-only-scrollable-collapsible-icon-list
  ui -> listView -> setMovement(QListView::Static);
  ui -> listView -> setResizeMode(QListView::Adjust);
  ui -> listView -> setViewMode(QListView::IconMode);
  ui -> listView -> setGridSize( QSize(150, 100));
  ui -> listView -> setMinimumHeight(100);

  StorageUnitModel* model = new StorageUnitModel();
  ui -> listView -> setModel(model);
  connect(ui -> actionRefresh, SIGNAL(triggered()), model, SLOT(refresh()));

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
}



/*
 * Destructor
 */
MainWindow::~MainWindow()
{
  delete ui;
}



/*
 * Handle selection on the main list view and update
 * the details panel accordingly
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
 * Call the refresh action on the active panel
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
 * Update the health status labels for the given unit
 */
void MainWindow::updateHealthStatus(StorageUnit* unit)
{
  QString style;
  QString text;
  QPixmap icon;

  if(!unit -> isFailingStatusKnown()) {
    style = "QLabel { color: orange; }";
    text = tr("Unknown");
    icon = QIcon::fromTheme("face-confused").pixmap(QSize(16,16));

  } else if(unit -> isFailing()) {
    style = "QLabel { color: red; }";
    text = tr("Failing");
    icon = QIcon::fromTheme("face-sick").pixmap(QSize(16,16));

  } else {
    text = tr("Healthy");
    icon = QIcon::fromTheme("face-cool").pixmap(QSize(16,16));
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
  if(KConfigDialog::showDialog("settings"))
    return;


  KConfigDialog *dialog = new KConfigDialog(this, "settings", DiskMonitorSettings::self());
  dialog -> setFaceType(KPageDialog::List);
  dialog -> addPage(new Appearance(dialog), i18n("Appearance"), "preferences-desktop-icons", i18n("Appearance options"));
  dialog -> addPage(new SMART(dialog), i18n("S.M.A.R.T"), "drive-harddisk", i18n("S.M.A.R.T options") );

  dialog->show();
}

