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


#ifndef STORAGEUNIT_H
#define STORAGEUNIT_H

#include <QDBusObjectPath>
#include <QDBusInterface>


#include "types.h"

/*
 * Base class for representing an unit of storage in UDisks2
 */
class StorageUnit : public QObject
{
  Q_OBJECT

public:
  StorageUnit();
  StorageUnit(QDBusObjectPath objectPath, QString device);
  StorageUnit(const StorageUnit&);
  ~StorageUnit();

  QDBusObjectPath getObjectPath() const;
  QString getPath() const;
  QString getDevice() const;
  QString getName() const;
  QString getShortName() const;

  HealthStatus::Status getHealthStatus() const;


  //QMETA_TYPE require a public empty constructor, we can't
  //use pure virtual here
  virtual void update()
  {
    emit updated(this);
  }

  virtual bool isDrive() const { return false; }
  virtual bool isMDRaid() const { return false; }

protected:
  QDBusObjectPath objectPath;
  QString device;
  QString name;
  QString shortName;


  HealthStatus healthStatus;
  bool failing = false;
  bool failingStatusKnown = false;
  bool warnings = false;

  static QVariant getProperty(QDBusInterface*, const char*);
  static bool getBoolProperty(QDBusInterface*, const char*);
  static int getIntProperty(QDBusInterface*, const char*);
  static qulonglong getULongLongProperty(QDBusInterface*, const char*);
  static double getDoubleProperty(QDBusInterface*, const char*);
  static QString getStringProperty(QDBusInterface*, const char*);

signals:
  void updated(StorageUnit* unit);
};

Q_DECLARE_METATYPE(StorageUnit)

#endif // STORAGEUNIT_H
