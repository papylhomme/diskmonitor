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

#include "atadrivepanel.h"
#include "ui_atadrivepanel.h"

#include "udisks2wrapper.h"

#include <QMenu>
#include <QMessageBox>

/*
 * Constructor
 */
AtaDrivePanel::AtaDrivePanel(QWidget* parent) :
    StorageUnitPanel(new AtaDrivePropertiesModel(), parent),
    ui(new Ui::AtaDrivePanel)
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

  connect(ui -> cancelSelfTestButton, SIGNAL(clicked()), this, SLOT(cancelSelfTest()));
}



/*
 * Destructor
 */
AtaDrivePanel::~AtaDrivePanel()
{
  delete ui;
}



/*
 * Set the drive to display in the panel. Can be NULL
 */
void AtaDrivePanel::setAtaDrive(AtaDrive* ataDrive)
{
  this -> setStorageUnit(ataDrive);
}



/*
 * Retrieve the drive associated with the panel. Can be NULL
 */
AtaDrive* AtaDrivePanel::getAtaDrive()
{
  return static_cast<AtaDrive*>(this -> model -> getStorageUnit());
}



/*
 * Update the UI according to the state of the currently selected drive
 */
void AtaDrivePanel::updateUI()
{
  AtaDrive* ataDrive = getAtaDrive();

  //sanity check
  if(ataDrive == nullptr) {
    ui -> panelSmartNotSupported -> setVisible(false);
    ui -> panelSmartNotEnabled -> setVisible(false);
    ui -> panelSmartWidgets -> setEnabled(false);
    ui -> selfTestStatusLabel -> setText(i18n("unknown"));
    ui -> progressBar -> setValue(0);
    ui -> cancelSelfTestButton -> setVisible(false);
    return;
  }

  ui -> panelSmartNotSupported -> setVisible(!ataDrive -> isSmartSupported());
  ui -> panelSmartNotEnabled -> setVisible(ataDrive -> isSmartSupported() && !ataDrive -> isSmartEnabled());

  bool smartOK = ataDrive -> isSmartSupported() && ataDrive -> isSmartEnabled();
  ui -> panelSmartWidgets -> setEnabled(smartOK);


  if(smartOK) {
    int percent = ataDrive -> getSelfTestPercentRemaining();
    QString status = ataDrive -> getSelfTestStatus();

    ui -> selfTestStatusLabel -> setText(localizeSelfTestStatus(status));

    if(status == "inprogress") {
      ui -> startSelfTestButton -> setEnabled(false);
      ui -> progressBar -> setEnabled(true);
      ui -> cancelSelfTestButton -> setVisible(true);
      if(percent >= 0) ui -> progressBar -> setValue(100 - percent);

    } else {
      ui -> startSelfTestButton -> setEnabled(true);
      ui -> progressBar -> setEnabled(false);
      ui -> progressBar -> setValue(0);
      ui -> cancelSelfTestButton -> setVisible(false);
    }

  } else {
    ui -> selfTestStatusLabel -> setText(i18n("unknown"));
    ui -> progressBar -> setValue(0);
    ui -> cancelSelfTestButton -> setVisible(false);
  }
}



/*
 * Test if an operation is currently running on the drive
 */
bool AtaDrivePanel::isOperationRunning()
{
  AtaDrive* ataDrive = getAtaDrive();
  return !(ataDrive == nullptr || ataDrive -> getSelfTestStatus() != "inprogress");
}



/*
 * Enable SMART for the given drive
 */
void AtaDrivePanel::enableSmart() {
  UDisks2Wrapper::instance() -> enableSMART(getAtaDrive());
  //delay the refresh as UDisks2 may take some time to update the status
  QTimer::singleShot(2000, this, SLOT(refresh()));
}



/*
 * Slot to start a short selftest on the drive
 */
void AtaDrivePanel::startShortSelfTest()
{
  startSelfTest(UDisks2Wrapper::ShortSelfTest);
}



/*
 * Slot to start an extended selftest on the drive
 */
void AtaDrivePanel::startExtendedSelfTest()
{
  startSelfTest(UDisks2Wrapper::ExtendedSelfTest);
}




/*
 * Start SMART selftest of the given type on the drive
 */
void AtaDrivePanel::startSelfTest(UDisks2Wrapper::SMARTSelfTestType type)
{
  AtaDrive* currentDrive = getAtaDrive();

  if(currentDrive != nullptr) {

    if(type == UDisks2Wrapper::ShortSelfTest ||
       QMessageBox::question(this,
                             i18nc("Dialog confirmation", "Confirm"),
                             i18n("Running an extended selftest may take several hours, are you sure you want to run it now ?")
                             ) == QMessageBox::Yes) {

      UDisks2Wrapper::instance() -> startSMARTSelfTest(currentDrive, type);
      //delay the refresh as UDisks2 may take some time to update the status
      QTimer::singleShot(2000, this, SLOT(refresh()));
    }
  }
}



/*
 * Cancel a SMART selftest on the drive
 */
void AtaDrivePanel::cancelSelfTest()
{
  AtaDrive* currentDrive = getAtaDrive();

  if(currentDrive != nullptr) {

    if(QMessageBox::question(this,
                             i18nc("Dialog confirmation", "Confirm"),
                             i18n("Are you sure you want to cancel the current selftest ?")
                             ) == QMessageBox::Yes) {

      UDisks2Wrapper::instance() -> cancelSMARTSelfTest(currentDrive);
      //delay the refresh as UDisks2 may take some time to update the status
      QTimer::singleShot(2000, this, SLOT(refresh()));
    }
  }
}



/*
 * Get a localized version of the self test status
 *
 * @see Drive::getSelfTestStatus()
 */
QString AtaDrivePanel::localizeSelfTestStatus(QString status) const
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
