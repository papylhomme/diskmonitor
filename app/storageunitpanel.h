#ifndef STORAGEUNITPANEL_H
#define STORAGEUNITPANEL_H

#include <QWidget>
#include <QTimer>

#include "storageunitpropertiesmodel.h"



/*
 *
 */
class StorageUnitPanel : public QWidget
{
    Q_OBJECT
public:
  explicit StorageUnitPanel(StorageUnitPropertiesModel* model, QWidget *parent = 0);
  ~StorageUnitPanel();

protected:
  StorageUnitPropertiesModel* model;

  void setStorageUnit(StorageUnit* unit);
  virtual bool isOperationRunning() { return false; }
  virtual void updateUI() { }

private:
  QTimer* autorefreshTimer;

  void updateAutoRefreshTimer();

public slots:
  void refresh();

};

#endif // STORAGEUNITPANEL_H
