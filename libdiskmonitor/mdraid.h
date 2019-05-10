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
  ~MDRaid() override;

  int getNumDevices() const;
  qulonglong getSize() const;
  qulonglong getSyncRemainingTime() const;

  double getSyncCompleted() const;

  const QString& getUUID() const;
  const QString& getLevel() const;
  const QString& getSyncAction() const;

  const MDRaidMemberList& getMembers() const;

  virtual void update() override;


  virtual bool isMDRaid() const override { return true; }

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
