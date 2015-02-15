#include "mdraidpanel.h"
#include "ui_mdraidpanel.h"


#include "udisks2wrapper.h"



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
  return (MDRaid*) this -> model -> getStorageUnit();
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

  double completed = raid -> getSyncCompleted();
  ui -> progressBar -> setValue(completed * 100);

  this -> modelMembers -> setStorageUnit(raid);
}



/*
 * Test if an operation is currently running on the raid
 */
bool MDRaidPanel::isOperationRunning()
{
  MDRaid* raid = getMDRaid();

  return !(raid == NULL || raid -> getSyncAction() == "idle");
}



/*
 * Slot to start scrubbing on the raid
 */
void MDRaidPanel::startScrubbing()
{
  MDRaid* currentMDRaid = getMDRaid();

  if(currentMDRaid != NULL) {
    UDisks2Wrapper::instance() -> startMDRaidScrubbing(currentMDRaid);
    //delay the refresh as UDisks2 may take some time to update the status
    QTimer::singleShot(2000, this, SLOT(refresh()));
  }
}
