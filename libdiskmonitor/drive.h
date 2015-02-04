#ifndef DRIVE_H
#define DRIVE_H

#include "storageunit.h"
#include "dbus_metatypes.h"


/*
 * Represent a Drive node in UDisks2
 */
class Drive : public StorageUnit
{
  Q_OBJECT


public:
  explicit Drive(QDBusObjectPath objectPath, QString device, bool hasATAIface);
  ~Drive();

  bool isSmartSupported() const;
  bool isSmartEnabled() const;
  bool isRemovable() const;

  const SmartAttributesList& getSMARTAttributes() const;

  virtual void update();
  virtual bool isDrive() const { return true; }

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
