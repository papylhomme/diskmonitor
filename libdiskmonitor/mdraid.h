#ifndef MDRAID_H
#define MDRAID_H

#include "storageunit.h"


class MDRaid : public StorageUnit
{
  Q_OBJECT

public:
  explicit MDRaid(QDBusObjectPath objectPath, QString device);
  ~MDRaid();

  int getNumDevices();
  int getSize();
  int getSyncRemainingTime();

  double getSyncCompleted();

  QString getUUID();
  QString getLevel();
  QString getSyncAction();

  virtual void update();


  virtual bool isMDRaid() { return true; }

protected:
  int numDevices;
  int size;
  int syncRemainingTime;

  double syncCompleted;

  QString uuid;
  QString level;
  QString syncAction;
};

#endif // MDRAID_H
