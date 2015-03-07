/****************************************************************************
 * DisKMonitor, KDE tools to monitor SMART and MDRaid health status         *
 * Copyright (C) 2014-2015 Michaël Lhomme <papylhomme@gmail.com>            *
 *                                                                          *
 * This program is free software; you can redistribute it and/or modify     *
 * it under the terms of the GNU General Public License as published by     *
 * the Free Software Foundation; either version 2 of the License, or        *
 * (at your option) any later version.                                      *
 *                                                                          *
 * This program is distributed in the hope that it will be useful,          *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of           *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the            *
 * GNU General Public License for more details.                             *
 *                                                                          *
 * You should have received a copy of the GNU General Public License along  *
 * with this program; if not, write to the Free Software Foundation, Inc.,  *
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.              *
 ****************************************************************************/


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

#include "smartattributesmonitor.h"



#define UDISKS2_SERVICE "org.freedesktop.UDisks2"

#define DBUS_PROPERTIES_IFACE "org.freedesktop.DBus.Properties"
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
    ExtendedSelfTest,
    ConveyanceSelfTest
  };


  UDisks2Wrapper();
  ~UDisks2Wrapper();

  static UDisks2Wrapper* instance();

  QList<StorageUnit*> listStorageUnits();
  void startMDRaidScrubbing(MDRaid* mdraid) const;
  void enableSMART(Drive* drive) const;
  void startSMARTSelfTest(Drive* drive, SMARTSelfTestType type) const;

  QDBusInterface* propertiesIface(QDBusObjectPath) const;
  QDBusInterface* driveIface(QDBusObjectPath) const;
  QDBusInterface* ataIface(QDBusObjectPath) const;
  QDBusInterface* mdraidIface(QDBusObjectPath) const;

  void addSMARTAttributesMonitor(SMARTAttributesMonitor* monitor, const QString& path = QString());
  SMARTAttributesMonitor* getSMARTAttributeMonitor(const QString& path);


private:
  void initialize();
  bool hasATAIface(QDBusObjectPath objectPath) const;
  StorageUnit* createNewUnitFromBlockDevice(const InterfaceList& interfaces) const;

  bool initialized = false;
  QMap<QDBusObjectPath, StorageUnit*> units;

  SMARTAttributesMonitor* smartAttributesMonitor = NULL;

private slots:
  void interfacesAdded(const QDBusObjectPath&, const InterfaceList&);
  void interfacesRemoved(const QDBusObjectPath&, const QStringList&);

signals:
  void storageUnitAdded(StorageUnit*);
  void storageUnitRemoved(StorageUnit*);


public slots:
};

#endif // UDISKS2WRAPPER_H
