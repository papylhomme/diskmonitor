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


#include "storageunitmonitor.h"

#include <KLocalizedString>
#include <KNotification>

#include <QProcess>

#include "udisks2wrapper.h"



/*
 * Constructor
 */
StorageUnitMonitor::StorageUnitMonitor() : QObject()
{
  defaultProvider = new IconsProvider();
  provider = defaultProvider;

  UDisks2Wrapper* udisks2 = UDisks2Wrapper::instance();

  QList<int> sensitiveAttributes;
  sensitiveAttributes << 1 << 5 << 7 << 192 << 197 << 198 << 201 << 192;
  udisks2 -> addSMARTAttributesMonitor(new SMARTAttributesMonitor(sensitiveAttributes));

  connect(udisks2, SIGNAL(storageUnitAdded(StorageUnit*)), this, SLOT(storageUnitAdded(StorageUnit*)));
  connect(udisks2, SIGNAL(storageUnitRemoved(StorageUnit*)), this, SLOT(storageUnitRemoved(StorageUnit*)));

  timer = new QTimer();
  connect(timer, SIGNAL(timeout()), this, SLOT(monitor()));
  timer -> start(timeout * 60 * 1000);

  //delay the fist monitor in order to let the applet
  //configure its value (mainly notifyEnabled)
  QTimer::singleShot(2000, this, SLOT(monitor()));
}



/*
 * Destructor
 */
StorageUnitMonitor::~StorageUnitMonitor()
{
  timer -> stop();
  delete timer;

  delete defaultProvider;

  qDebug() << "StorageUnitMonitor destructed !";
}



/*
 * Main monitor callback, process each storage unit
 * to detect errors and warnings
 */
void StorageUnitMonitor::monitor()
{
  //first refresh the model as it update all storage units
  storageUnitQmlModel.refresh();

  //then process the unit to detect potential errors
  processUnits();
}



/*
 * Get the refresh timeout value
 */
int StorageUnitMonitor::refreshTimeout() const
{
  return timeout;
}



/*
 * Set the refresh timeout value
 */
void StorageUnitMonitor::setRefreshTimeout(int timeout)
{
  this -> timeout = timeout;
  this -> timer -> stop();
  this -> timer -> start(timeout * 60 * 1000);
}



/*
 * Get the notifyEnabled value
 */
bool StorageUnitMonitor::notifyEnabled() const
{
  return notify;
}



/*
 * Set the notifyEnabled value
 */
void StorageUnitMonitor::setNotifyEnabled(bool notify)
{
  this -> notify = notify;
}



/*
 *
 */
HealthStatus::Status StorageUnitMonitor::globalHealthStatus() const
{
  return status;
}



/*
 * Retrieve the current status as a formatted string
 */
const QString& StorageUnitMonitor::statusText() const
{
  return statusMessage;
}



/*
 *
 */
void StorageUnitMonitor::setIconsProvider(IconsProvider* provider)
{
  this -> provider = provider;
  emit iconsProviderChanged();
}



/*
 *
 */
IconsProvider* StorageUnitMonitor::iconsProvider()
{
  return provider;
}



/*
 * Handle StorageUnit added
 */
void StorageUnitMonitor::storageUnitAdded(StorageUnit* /*unit*/)
{
  //refresh the status with the new unit
  processUnits();
}



/*
 * Handle StorageUnit removed
 */
void StorageUnitMonitor::storageUnitRemoved(StorageUnit* /*unit*/)
{
  //refresh status for the remaining units
  processUnits();
}



/*
 * Get the StorageUnit model for the plasma applet
 */
StorageUnitQmlModel*StorageUnitMonitor::model()
{
  return &storageUnitQmlModel;
}



/*
 * Update the current general health status with the given storage units
 */
void StorageUnitMonitor::processUnits()
{
  HealthStatus::Status newStatus = HealthStatus::Unknown;
  QList<StorageUnit*> units = UDisks2Wrapper::instance() -> listStorageUnits();

  //test each unit
  QString details;
  foreach(StorageUnit* unit, units) {
    if(unit -> getHealthStatus() > HealthStatus::Healthy)
      details = "<br/><i>" + unit -> getName() + " (" + unit -> getDevice() + "): " + HealthStatus::toString(unit -> getHealthStatus()) + "</i>";

    if(unit -> getHealthStatus() >= HealthStatus::Warning) {
      newStatus = unit -> getHealthStatus();
    }
  }

  if(status == HealthStatus::Unknown)
    statusMessage = i18n("Global health status is unknown");
  if(status == HealthStatus::Healthy)
    statusMessage = i18n("Everything looks healthy.");
  else {
    statusMessage = i18n("The following storage units are not healthy:<br/>%1", details);
  }

  emit statusTextChanged(statusMessage);


  //General health status changed, notify the user
  if(status != newStatus) {
    qDebug() << "StorageMonitor: Changing failing status from " << status << " to " << newStatus;
    status = newStatus;
    emit globalHealthStatusChanged(status);

    if(notifyEnabled())
      KNotification::event(status == HealthStatus::Failing ? "failing" : "healthy",
                           status == HealthStatus::Failing ? i18n("Storage units failing") : i18n("Storage units are back to healthy status"),
                           statusText(),
                           iconsProvider() -> iconForStatus(status),
                           NULL,
                           KNotification::Persistent,
                           "diskmonitor"
                           );
  }
}



/*
 * Slot to open the main DisKMonitor application
 *
 * @param unitPath The DBus path to the unit to display
 */
void StorageUnitMonitor::openApp(const QString& unitPath)
{
  if(unitPath.isEmpty())
    QProcess::startDetached("diskmonitor");

  else {
    QStringList params;
    params << unitPath;
    QProcess::startDetached("diskmonitor", params);
  }
}
