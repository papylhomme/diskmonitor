#ifndef DRIVE_H
#define DRIVE_H

#include "storageunit.h"
#include "dbus_metatypes.h"

class Drive : public StorageUnit
{
  Q_OBJECT


public:
  explicit Drive(QDBusObjectPath objectPath, QString device, bool hasATAIface);
  ~Drive();

  bool isSmartSupported();
  bool isSmartEnabled();
  bool isRemovable();

  SmartAttributesList getAttributes();

  virtual void update();
  virtual bool isDrive() { return true; }

protected:
  bool smartSupported;
  bool smartEnabled;
  bool removable;

  bool hasATAIface;

  SmartAttributesList attributes;

signals:

public slots:
};

#endif // DRIVE_H
