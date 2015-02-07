#include "storageunitpanel.h"


/*
 * Constructor
 */
StorageUnitPanel::StorageUnitPanel(StorageUnitPropertiesModel* model, QWidget* parent) : QWidget(parent)
{
  this -> model = model;

  this -> autorefreshTimer = new QTimer();
  connect(autorefreshTimer, SIGNAL(timeout()), this, SLOT(refresh()));
}



/*
 * Destructor
 */
StorageUnitPanel::~StorageUnitPanel()
{
  delete model;
}



/*
 * Set the StorageUnit. Call updateUI and handle auto-refresh if needed
 */
void StorageUnitPanel::setStorageUnit(StorageUnit* unit)
{
  this -> model -> setStorageUnit(unit);
  updateUI();
  updateAutoRefreshTimer();
}



/*
 * Refresh the content of the panel (by refreshing the model's StorageUnit)
 */
void StorageUnitPanel::refresh()
{
  this -> model -> refreshAll();
  updateUI();
  updateAutoRefreshTimer();
}



/*
 * Auto-refresh enabling/disabling routine
 */
void StorageUnitPanel::updateAutoRefreshTimer()
{
  bool running = isOperationRunning();

  if(running && !autorefreshTimer -> isActive())
    autorefreshTimer -> start(1000);
  else if(!running && autorefreshTimer -> isActive())
    autorefreshTimer -> stop();
}


