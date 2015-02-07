#include "mdraidpanel.h"
#include "ui_mdraidpanel.h"


#include "udisks2wrapper.h"



/*
 *
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
}



/*
 *
 */
MDRaidPanel::~MDRaidPanel()
{
  delete ui;
}



/*
 *
 */
void MDRaidPanel::setMDRaid(MDRaid* raid)
{
  this -> setStorageUnit(raid);
  this -> modelMembers -> setStorageUnit(raid);
}



/*
 *
 */
MDRaid* MDRaidPanel::getMDRaid()
{
  return (MDRaid*) this -> model -> getStorageUnit();
}



/*
 *
 */
void MDRaidPanel::updateUI()
{
  bool running = isOperationRunning();
  MDRaid* raid = getMDRaid();

  ui -> progressBar -> setEnabled(running);
  ui -> startScrubButton -> setEnabled(!running);

  double completed = raid -> getSyncCompleted();
  ui -> progressBar -> setValue(completed * 100);

  this -> modelMembers -> setStorageUnit(raid);
}



/*
 *
 */
bool MDRaidPanel::isOperationRunning()
{
  MDRaid* raid = getMDRaid();

  return !(raid == NULL || raid -> getSyncAction() == "idle");
}



/*
 *
 */
void MDRaidPanel::startScrubbing()
{
  MDRaid* currentMDRaid = getMDRaid();

  if(currentMDRaid != NULL) {
    UDisks2Wrapper::getInstance() -> startMDRaidScrubbing(currentMDRaid);
    //delay the refresh as UDisks2 may take some time to update the status
    QTimer::singleShot(2000, this, SLOT(refresh()));
  }
}
