#include "mdraidpanel.h"
#include "ui_mdraidpanel.h"


#include "udisks2wrapper.h"



/*
 *
 */
MDRaidPanel::MDRaidPanel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MDRaidPanel)
{
  ui -> setupUi(this);

  this -> autorefreshTimer = new QTimer();
  this -> model = new MDRaidPropertiesModel();

  ui -> tableView -> verticalHeader() -> hide();
  ui -> tableView -> horizontalHeader() -> hide();
  ui -> tableView -> horizontalHeader() -> setSectionResizeMode(QHeaderView::ResizeMode::ResizeToContents);
  ui -> tableView -> horizontalHeader() -> setStretchLastSection(true);
  ui -> tableView -> setModel(this -> model);

  connect(autorefreshTimer, SIGNAL(timeout()), this, SLOT(refresh()));
  connect(ui -> startScrubButton, SIGNAL(clicked()), this, SLOT(startScrubbing()));
}



/*
 *
 */
MDRaidPanel::~MDRaidPanel()
{
  delete model;
  delete ui;
}



/*
 *
 */
void MDRaidPanel::setMDRaid(MDRaid* raid)
{
  model -> updateStorageUnit(raid);
  updateAutoRefresh();
}



/*
 *
 */
void MDRaidPanel::updateAutoRefresh()
{
  MDRaid* currentMDRaid = model -> getMDRaid();

  if(currentMDRaid == NULL)
    autorefreshTimer -> stop();

  else {
    QString currentSyncAction = model -> getMDRaid() -> getSyncAction();
    if(autorefreshTimer -> isActive() && currentSyncAction == "idle")
      autorefreshTimer -> stop();

    else if(!autorefreshTimer -> isActive() && (currentSyncAction == "check" || currentSyncAction == "repair"))
      autorefreshTimer -> start(1000);
  }
}



/*
 *
 */
void MDRaidPanel::refresh()
{
  model -> refreshAll();
  updateAutoRefresh();
}



/*
 *
 */
void MDRaidPanel::startScrubbing()
{
  MDRaid* currentMDRaid = model -> getMDRaid();

  if(currentMDRaid != NULL) {
    UDisks2Wrapper::getInstance() -> startMDRaidScrubbing(currentMDRaid);
    refresh();
  }
}
