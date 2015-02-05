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

  bool isRemovable() const;

  bool isSmartSupported() const;
  bool isSmartEnabled() const;

  int getSelfTestPercentRemaining() const;

  const QString& getSelfTestStatus() const;

  const SmartAttributesList& getSMARTAttributes() const;

  virtual void update();
  virtual bool isDrive() const { return true; }

protected:
  bool removable;
  bool hasATAIface;

  bool smartSupported;
  bool smartEnabled;

  int selfTestPercentRemaining;

  QString selfTestStatus;

  SmartAttributesList attributes;

signals:

public slots:
};

#endif // DRIVE_H
