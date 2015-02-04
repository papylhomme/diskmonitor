#ifndef MDRAID_H
#define MDRAID_H

#include "storageunit.h"


/*
 * Represent a MDRaid device node in UDisks2
 */
class MDRaid : public StorageUnit
{
  Q_OBJECT

public:
  explicit MDRaid(QDBusObjectPath objectPath, QString device);
  ~MDRaid();

  int getNumDevices() const;
  int getSize() const;
  int getSyncRemainingTime() const;

  double getSyncCompleted() const;

  const QString& getUUID() const;
  const QString& getLevel() const;
  const QString& getSyncAction() const;

  virtual void update();


  virtual bool isMDRaid() const { return true; }

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
