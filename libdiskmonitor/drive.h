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

  virtual void update() override;
  virtual bool isDrive() const override { return true; }

protected:
  bool removable = false;
  bool hasATAIface = false;

  bool smartSupported = false;
  bool smartEnabled = false;

  int selfTestPercentRemaining = 0;

  QString selfTestStatus;

  SmartAttributesList attributes;

signals:

public slots:
};

#endif // DRIVE_H
