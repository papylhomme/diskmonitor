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


#include "mdraidpanel.h"
#include "ui_mdraidpanel.h"


#include "udisks2wrapper.h"

#include <QMessageBox>
#include <QScrollBar>


/*
 * Constructor
 */
MDRaidPanel::MDRaidPanel(QWidget *parent) :
  StorageUnitPanel(new MDRaidPropertiesModel(), parent),
  ui(new Ui::MDRaidPanel)
{
  ui -> setupUi(this);

  ui -> attributesView -> verticalHeader() -> hide();
  ui -> attributesView -> horizontalHeader() -> setSectionResizeMode(QHeaderView::ResizeMode::ResizeToContents);
  ui -> attributesView -> horizontalHeader() -> setStretchLastSection(true);
  ui -> attributesView -> setModel(this -> model);

  modelMembers = new MDRaidMembersModel();
  ui -> membersView -> verticalHeader() -> hide();
  ui -> membersView -> horizontalHeader() -> setSectionResizeMode(QHeaderView::ResizeMode::ResizeToContents);
  ui -> membersView -> horizontalHeader() -> setStretchLastSection(true);
  ui -> membersView -> setModel(modelMembers);

  connect(ui -> startScrubButton, SIGNAL(clicked()), this, SLOT(startScrubbing()));
  connect(ui -> cancelScrubButton, SIGNAL(clicked()), this, SLOT(cancelScrubbing()));
}



/*
 * Destructor
 */
MDRaidPanel::~MDRaidPanel()
{
  delete ui;
}



/*
 * Set the raid to display in the panel. Can be NULL
 */
void MDRaidPanel::setMDRaid(MDRaid* raid)
{
  this -> setStorageUnit(raid);
  this -> modelMembers -> setStorageUnit(raid);
}



/*
 * Retrieve the raid associated with the panel. Can be NULL
 */
MDRaid* MDRaidPanel::getMDRaid()
{
  return static_cast<MDRaid*>(this -> model -> getStorageUnit());
}



/*
 * Update the UI according to the state of the currently selected raid
 */
void MDRaidPanel::updateUI()
{
  bool running = isOperationRunning();
  MDRaid* raid = getMDRaid();

  ui -> progressBar -> setEnabled(running);
  ui -> startScrubButton -> setEnabled(!running);

  if(raid != nullptr) {
    double completed = raid -> getSyncCompleted();
    ui -> progressBar -> setValue(completed * 100);
    ui -> cancelScrubButton -> setVisible(raid -> getSyncAction() == "check");

    //force height of attributesView to be minimal
    enforceAttributesViewSize();
  } else {
    ui -> progressBar -> setValue(0);
    ui -> cancelScrubButton -> setVisible(false);
  }

  this -> modelMembers -> setStorageUnit(raid);
}



/*
 * Test if an operation is currently running on the raid
 */
bool MDRaidPanel::isOperationRunning()
{
  MDRaid* raid = getMDRaid();

  return !(raid == nullptr || raid -> getSyncAction() == "idle");
}



/*
 * Enforce a minimal size for the attributes listview
 */
void MDRaidPanel::enforceAttributesViewSize()
{
  int scrollHeight = ui -> attributesView -> horizontalScrollBar() -> height();

  ui -> attributesView -> setMinimumHeight(ui -> attributesView -> minimumSizeHint().height() + scrollHeight);
  ui -> attributesView -> setMaximumHeight(ui -> attributesView -> minimumSizeHint().height() + scrollHeight);
}



/*
 * Slot to start scrubbing on the raid
 */
void MDRaidPanel::startScrubbing()
{
  MDRaid* currentMDRaid = getMDRaid();

  if(currentMDRaid != nullptr) {

    if(QMessageBox::question(this,
                             i18nc("Dialog confirmation", "Confirm"),
                             i18n("Running a scrub operation may take several hours, are you sure you want to run it now ?")
                             ) == QMessageBox::Yes) {

      UDisks2Wrapper::instance() -> startMDRaidScrubbing(currentMDRaid);
      //delay the refresh as UDisks2 may take some time to update the status
      QTimer::singleShot(2000, this, SLOT(refresh()));
    }
  }
}



/*
 * Slot to cancel scrubbing on the raid
 */
void MDRaidPanel::cancelScrubbing()
{
  MDRaid* currentMDRaid = getMDRaid();

  if(currentMDRaid != nullptr) {

    if(QMessageBox::question(this,
                             i18nc("Dialog confirmation", "Confirm"),
                             i18n("Are you sure you want to cancel the current scrubbing operation ?")
                             ) == QMessageBox::Yes) {

      UDisks2Wrapper::instance() -> cancelMDRaidScrubbing(currentMDRaid);
      //delay the refresh as UDisks2 may take some time to update the status
      QTimer::singleShot(2000, this, SLOT(refresh()));
    }
  }

}
