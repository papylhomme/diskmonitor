#ifndef UDISKS2WRAPPER_H
#define UDISKS2WRAPPER_H

#include <QObject>
#include <QList>

#include <QDBusConnection>
#include <QDBusInterface>

#include "dbus_metatypes.h"

#include "storageunit.h"
#include "mdraid.h"
#include "drive.h"




#define UDISKS2_SERVICE "org.freedesktop.UDisks2"

#define UDISKS2_OBJECT_IFACE "org.freedesktop.DBus.ObjectManager"
#define UDISKS2_DRIVE_IFACE "org.freedesktop.UDisks2.Drive"
#define UDISKS2_ATA_IFACE "org.freedesktop.UDisks2.Drive.Ata"
#define UDISKS2_MDRAID_IFACE "org.freedesktop.UDisks2.MDRaid"
#define UDISKS2_BLOCK_IFACE "org.freedesktop.UDisks2.Block"

#define UDISKS2_PATH "/org/freedesktop/UDisks2"
#define UDISKS2_DRIVES_PATH "/org/freedesktop/UDisks2/drives"
#define UDISKS2_MDRAIDS_PATH "/org/freedesktop/UDisks2/mdraid"
#define UDISKS2_BLOCK_DEVICES_PATH "/org/freedesktop/UDisks2/block_devices"



/*
 * Singleton wrapper to access UDisks2 over DBus
 */
class UDisks2Wrapper : public QObject
{
  Q_OBJECT

public:

  /*
   * Types of SMART SelfTest
   */
  enum SMARTSelfTestType {
    ShortSelfTest,
    LongSelfTest
  };


  ~UDisks2Wrapper();

  static UDisks2Wrapper* getInstance();

  QList<StorageUnit*> listStorageUnits();
  QDBusInterface* driveIface(QDBusObjectPath) const;
  QDBusInterface* ataIface(QDBusObjectPath) const;
  QDBusInterface* mdraidIface(QDBusObjectPath) const;


  void startMDRaidScrubbing(MDRaid* mdraid) const;
  void startDriveSelfTest(Drive* drive, SMARTSelfTestType type) const;

private:
  static UDisks2Wrapper* instance;
  UDisks2Wrapper();

  void initialize();
  bool hasATAIface(QDBusObjectPath objectPath) const;
  StorageUnit* createNewUnitFromBlockDevice(const InterfaceList& interfaces) const;

  bool initialized;
  QMap<QDBusObjectPath, StorageUnit*> units;

private slots:
  void interfacesAdded(const QDBusObjectPath&, const InterfaceList&);
  void interfacesRemoved(const QDBusObjectPath&, const QStringList&);

signals:
  void storageUnitAdded(StorageUnit*);
  void storageUnitRemoved(StorageUnit*);


public slots:
};

#endif // UDISKS2WRAPPER_H
