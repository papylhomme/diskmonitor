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



/*
 * Main component for DiskMonitor notifier
 */
class StorageUnitMonitor : public QObject
{
  Q_OBJECT

  Q_PROPERTY(bool failing READ failing)
  Q_PROPERTY(bool notifyEnabled READ notifyEnabled WRITE setNotifyEnabled)
  Q_PROPERTY(int refreshTimeout READ refreshTimeout WRITE setRefreshTimeout)
  Q_PROPERTY(QString status READ status NOTIFY statusChanged)
  Q_PROPERTY(QString iconHealthy READ iconHealthy WRITE setIconHealthy)
  Q_PROPERTY(QString iconFailing READ iconFailing WRITE setIconFailing)
  Q_PROPERTY(QString iconWarning READ iconWarning WRITE setIconWarning)
  Q_PROPERTY(StorageUnitQmlModel* model READ model NOTIFY modelChanged)

public:
  StorageUnitMonitor();
  ~StorageUnitMonitor();

  int refreshTimeout() const;
  void setRefreshTimeout(int timeout);

  bool notifyEnabled() const;
  void setNotifyEnabled(bool notify);

  bool failing() const;
  QString status() const;

  QString iconHealthy() const;
  QString iconFailing() const;
  QString iconWarning() const;
  void setIconHealthy(QString healthyIcon);
  void setIconFailing(QString failingIcon);
  void setIconWarning(QString warningIcon);

  StorageUnitQmlModel* model();

private:
  bool notify = false;
  bool hasFailing = false;

  QString healthyIcon;
  QString failingIcon;
  QString warningIcon;

  QList<StorageUnit*> failingUnits;
  StorageUnitQmlModel storageUnitQmlModel;

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
  void statusChanged();
  void modelChanged();
};

#endif // STORAGEUNITMONITOR_H
