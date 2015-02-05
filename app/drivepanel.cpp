#include "drivepanel.h"
#include "ui_drivepanel.h"

#include "udisks2wrapper.h"

#include <QMenu>

/*
 *
 */
DrivePanel::DrivePanel(QWidget *parent) :
    StorageUnitPanel(new DrivePropertiesModel(), parent),
    ui(new Ui::DrivePanel)
{
  ui->setupUi(this);

  ui -> tableView -> verticalHeader() -> hide();
  ui -> tableView -> horizontalHeader() -> setSectionResizeMode(QHeaderView::ResizeMode::ResizeToContents);
  ui -> tableView -> horizontalHeader() -> setStretchLastSection(true);
  ui -> tableView -> setModel(this -> model);

  QAction* action;
  QMenu * menu = new QMenu();
  action = menu -> addAction(tr("Short test"));
  connect(action, SIGNAL(triggered()), this, SLOT(startShortSelfTest()));
  action = menu -> addAction(tr("Long test"));
  connect(action, SIGNAL(triggered()), this, SLOT(startLongSelfTest()));
  ui -> startSelfTestButton -> setMenu(menu);
}



/*
 *
 */
DrivePanel::~DrivePanel()
{
  delete ui;
}



/*
 *
 */
void DrivePanel::setDrive(Drive* drive)
{
  this -> setStorageUnit(drive);
}



/*
 *
 */
Drive* DrivePanel::getDrive()
{
  return (Drive*) this -> model -> getStorageUnit();
}



/*
 *
 */
void DrivePanel::updateUI()
{
  Drive* drive = getDrive();
  bool smartOK = drive != NULL && drive -> isSmartSupported() && drive -> isSmartEnabled();

  ui -> tableView -> setEnabled(smartOK );


  if(smartOK ) {
    int percent = drive -> getSelfTestPercentRemaining();
    QString status = drive -> getSelfTestStatus();

    ui -> selfTestStatusLabel -> setText(status);

    if(status == "inprogress") {
      ui -> startSelfTestButton -> setEnabled(false);
      ui -> progressBar -> setEnabled(true);
      if(percent >= 0) ui -> progressBar -> setValue(100 - percent);

    } else {
      ui -> startSelfTestButton -> setEnabled(true);
      ui -> progressBar -> setEnabled(false);
      ui -> progressBar -> setValue(0);
    }

  } else {
    ui -> selfTestStatusLabel -> setText(tr("unknown"));
    ui -> progressBar -> setValue(0);
  }
}



/*
 *
 */
bool DrivePanel::isOperationRunning()
{
  Drive* drive = getDrive();

  return !(drive == NULL || drive -> getSelfTestStatus() != "inprogress");
}



/*
 *
 */
void DrivePanel::startShortSelfTest()
{
  startSelfTest(UDisks2Wrapper::ShortSelfTest);
}



/*
 *
 */
void DrivePanel::startLongSelfTest()
{
  startSelfTest(UDisks2Wrapper::LongSelfTest);
}




/*
 *
 */
void DrivePanel::startSelfTest(UDisks2Wrapper::SMARTSelfTestType type)
{
  Drive* currentDrive = getDrive();

  if(currentDrive != NULL) {
    UDisks2Wrapper::getInstance() -> startDriveSelfTest(currentDrive, type);
    //delay the refresh as UDisks2 may take some time to update the status
    QTimer::singleShot(2000, this, SLOT(refresh()));
  }
}
