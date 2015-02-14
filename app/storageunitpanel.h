#ifndef STORAGEUNITPANEL_H
#define STORAGEUNITPANEL_H

#include <QWidget>
#include <QTimer>

#include "storageunitpropertiesmodel.h"



/*
 * Base class to implement a panel displaying information for a StorageUnit
 *
 * Handle refreshing the internal data, and auto refresh during a running operation
 */
class StorageUnitPanel : public QWidget
{
    Q_OBJECT
public:
  explicit StorageUnitPanel(StorageUnitPropertiesModel* model, QWidget *parent = 0);
  ~StorageUnitPanel();

  void setStorageUnit(StorageUnit* unit);

protected:
  StorageUnitPropertiesModel* model = NULL;

  virtual bool isOperationRunning() { return false; }
  virtual void updateUI() { }

private:
  QTimer* autorefreshTimer;

  void updateAutoRefreshTimer();

public slots:
  void refresh();

};

#endif // STORAGEUNITPANEL_H
