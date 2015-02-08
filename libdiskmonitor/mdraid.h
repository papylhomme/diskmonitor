#ifndef MDRAID_H
#define MDRAID_H

#include "storageunit.h"

#include "dbus_metatypes.h"


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
  qulonglong getSize() const;
  qulonglong getSyncRemainingTime() const;

  double getSyncCompleted() const;

  const QString& getUUID() const;
  const QString& getLevel() const;
  const QString& getSyncAction() const;

  const MDRaidMemberList& getMembers() const;

  virtual void update();


  virtual bool isMDRaid() const { return true; }

protected:
  int numDevices = 0;
  qulonglong size = 0;
  qulonglong syncRemainingTime = 0;

  double syncCompleted = 0;

  QString uuid;
  QString level;
  QString syncAction;

  MDRaidMemberList members;
};

#endif // MDRAID_H
