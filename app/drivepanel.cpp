#include "drivepanel.h"
#include "ui_drivepanel.h"

#include "udisks2wrapper.h"

#include <QMenu>

/*
 * Constructor
 */
DrivePanel::DrivePanel(QWidget *parent) :
    StorageUnitPanel(new DrivePropertiesModel(), parent),
    ui(new Ui::DrivePanel)
{
  ui -> setupUi(this);

  ui -> tableView -> verticalHeader() -> hide();
  ui -> tableView -> horizontalHeader() -> setSectionResizeMode(QHeaderView::ResizeMode::ResizeToContents);
  ui -> tableView -> horizontalHeader() -> setStretchLastSection(true);
  ui -> tableView -> setModel(this -> model);

  ui -> warningNotSupportedLabel -> setPixmap(QIcon::fromTheme("dialog-warning").pixmap(QSize(32, 32)));
  ui -> warningNotEnabledLabel -> setPixmap(QIcon::fromTheme("dialog-warning").pixmap(QSize(32, 32)));

  connect(ui -> enableSmartButton, SIGNAL(clicked()), this, SLOT(enableSmart()));

  QAction* action;
  QMenu * menu = new QMenu();
  action = menu -> addAction(i18n("Short test"));
  connect(action, SIGNAL(triggered()), this, SLOT(startShortSelfTest()));
  action = menu -> addAction(i18n("Extended test"));
  connect(action, SIGNAL(triggered()), this, SLOT(startExtendedSelfTest()));
  ui -> startSelfTestButton -> setMenu(menu);
}



/*
 * Destructor
 */
DrivePanel::~DrivePanel()
{
  delete ui;
}



/*
 * Set the drive to display in the panel. Can be NULL
 */
void DrivePanel::setDrive(Drive* drive)
{
  this -> setStorageUnit(drive);
}



/*
 * Retrieve the drive associated with the panel. Can be NULL
 */
Drive* DrivePanel::getDrive()
{
  return (Drive*) this -> model -> getStorageUnit();
}



/*
 * Update the UI according to the state of the currently selected drive
 */
void DrivePanel::updateUI()
{
  Drive* drive = getDrive();

  //sanity check
  if(drive == NULL) {
    ui -> panelSmartNotSupported -> setVisible(!drive -> isSmartSupported());
    ui -> panelSmartNotEnabled -> setVisible(drive -> isSmartSupported() && !drive -> isSmartEnabled());
    ui -> panelSmartWidgets -> setEnabled(false);
    return;
  }

  ui -> panelSmartNotSupported -> setVisible(!drive -> isSmartSupported());
  ui -> panelSmartNotEnabled -> setVisible(drive -> isSmartSupported() && !drive -> isSmartEnabled());

  bool smartOK = drive -> isSmartSupported() && drive -> isSmartEnabled();
  ui -> panelSmartWidgets -> setEnabled(smartOK);


  if(smartOK) {
    int percent = drive -> getSelfTestPercentRemaining();
    QString status = drive -> getSelfTestStatus();

    ui -> selfTestStatusLabel -> setText(localizeSelfTestStatus(status));

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
    ui -> selfTestStatusLabel -> setText(i18n("unknown"));
    ui -> progressBar -> setValue(0);
  }
}



/*
 * Test if an operation is currently running on the drive
 */
bool DrivePanel::isOperationRunning()
{
  Drive* drive = getDrive();

  return !(drive == NULL || drive -> getSelfTestStatus() != "inprogress");
}



/*
 * Enable SMART for the given drive
 */
void DrivePanel::enableSmart() {
  UDisks2Wrapper::instance() -> enableSMART(getDrive());
  //delay the refresh as UDisks2 may take some time to update the status
  QTimer::singleShot(2000, this, SLOT(refresh()));
}



/*
 * Slot to start a short selftest on the drive
 */
void DrivePanel::startShortSelfTest()
{
  startSelfTest(UDisks2Wrapper::ShortSelfTest);
}



/*
 * Slot to start an extended selftest on the drive
 */
void DrivePanel::startExtendedSelfTest()
{
  startSelfTest(UDisks2Wrapper::ExtendedSelfTest);
}




/*
 * Start SMART selftest of the given type on the drive
 */
void DrivePanel::startSelfTest(UDisks2Wrapper::SMARTSelfTestType type)
{
  Drive* currentDrive = getDrive();

  if(currentDrive != NULL) {
    UDisks2Wrapper::instance() -> startSMARTSelfTest(currentDrive, type);
    //delay the refresh as UDisks2 may take some time to update the status
    QTimer::singleShot(2000, this, SLOT(refresh()));
  }
}



/*
 * Get a localized version of the self test status
 *
 * @see Drive::getSelfTestStatus()
 */
QString DrivePanel::localizeSelfTestStatus(QString status) const
{
  if(status == "inprogress")
    return i18nc("SelfTest status", "In progress");
  else if(status == "success")
    return i18nc("SelfTest status", "Success");
  else if(status == "aborted")
    return i18nc("SelfTest status", "Aborted");
  else if(status == "interrupted")
    return i18nc("SelfTest status", "Interrupted");
  else if(status == "fatal")
    return i18nc("SelfTest status", "Fatal");
  else if(status.startsWith("error_"))
    return i18nc("SelfTest status", "Error (%1)", status);
  else
    return status;
}
