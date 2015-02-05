#include "storageunitpanel.h"


/*
 *
 */
StorageUnitPanel::StorageUnitPanel(StorageUnitPropertiesModel* model, QWidget* parent) : QWidget(parent)
{
  this -> model = model;

  this -> autorefreshTimer = new QTimer();
  connect(autorefreshTimer, SIGNAL(timeout()), this, SLOT(refresh()));
}



/*
 *
 */
StorageUnitPanel::~StorageUnitPanel()
{
  delete model;
}



/*
 *
 */
void StorageUnitPanel::setStorageUnit(StorageUnit* unit)
{
  this -> model -> setStorageUnit(unit);
  updateUI();
  updateAutoRefreshTimer();
}



/*
 *
 */
void StorageUnitPanel::refresh()
{
  this -> model -> refreshAll();
  updateUI();
  updateAutoRefreshTimer();
}



/*
 *
 */
void StorageUnitPanel::updateAutoRefreshTimer()
{
  bool running = isOperationRunning();

  if(running && !autorefreshTimer -> isActive())
    autorefreshTimer -> start(1000);
  else if(!running && autorefreshTimer -> isActive())
    autorefreshTimer -> stop();
}


