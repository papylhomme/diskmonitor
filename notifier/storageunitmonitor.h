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


#ifndef STORAGEUNITMONITOR_H
#define STORAGEUNITMONITOR_H

#include <QList>
#include <QTimer>

#include "storageunitqmlmodel.h"

#include "storageunit.h"
#include "drive.h"
#include "mdraid.h"

#include "iconsprovider.h"


/*
 * Main component for DiskMonitor notifier
 */
class StorageUnitMonitor : public QObject
{
  Q_OBJECT

  Q_PROPERTY(bool notifyEnabled READ notifyEnabled WRITE setNotifyEnabled)
  Q_PROPERTY(int refreshTimeout READ refreshTimeout WRITE setRefreshTimeout)

  Q_PROPERTY(HealthStatus::Status globalHealthStatus READ globalHealthStatus NOTIFY globalHealthStatusChanged)
  Q_PROPERTY(QString statusText READ statusText NOTIFY statusTextChanged)

  Q_PROPERTY(StorageUnitQmlModel* model READ model NOTIFY modelChanged)
  Q_PROPERTY(IconsProvider* iconsProvider READ iconsProvider WRITE setIconsProvider NOTIFY iconsProviderChanged)

public:
  StorageUnitMonitor();
  ~StorageUnitMonitor();

  int refreshTimeout() const;
  void setRefreshTimeout(int timeout);

  bool notifyEnabled() const;
  void setNotifyEnabled(bool notify);

  HealthStatus::Status globalHealthStatus() const;
  const QString& statusText() const;


  IconsProvider* iconsProvider();
  void setIconsProvider(IconsProvider* provider);

  StorageUnitQmlModel* model();

private:
  bool notify = false;

  HealthStatus::Status status = HealthStatus::Unknown;
  QString statusMessage;

  StorageUnitQmlModel storageUnitQmlModel;
  IconsProvider* provider;
  IconsProvider* defaultProvider;

  int timeout = 5;
  QTimer* timer;

  void processUnits();

public slots:
  void monitor();
  void openApp(const QString& unitPath = QString());

private slots:
  void storageUnitAdded(StorageUnit* unit);
  void storageUnitRemoved(StorageUnit* unit);

signals:
  void globalHealthStatusChanged(HealthStatus::Status status);
  void statusTextChanged(const QString& statusText);

  void modelChanged();
  void iconsProviderChanged();
};

#endif // STORAGEUNITMONITOR_H
