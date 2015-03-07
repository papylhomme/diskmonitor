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


#ifndef METATYPES_H
#define METATYPES_H

#include <QtCore>
#include <QtDBus>


#include "types.h"

/*
 * A map of interface (key) with there properties (value)
 */
typedef QMap<QString,QVariantMap> InterfaceList;
Q_DECLARE_METATYPE(InterfaceList)



/*
 * A map of node (key) with there interfaces
 */
typedef QMap<QDBusObjectPath, InterfaceList> ManagedObjectList;
Q_DECLARE_METATYPE(ManagedObjectList)



/*
 * Structure mapping a SMART attribute on UDisks2
 */
struct SmartAttribute {
  quint8 id;
  QString name;
  quint16 flags;
  qint32 value;
  qint32 worst;
  qint32 threshold;
  qint64 pretty;
  qint32 pretty_unit;
  QVariantMap expansion;

  //internal type, do not belong to UDisks2
  HealthStatus::Status healthStatus = HealthStatus::Unknown;
};
Q_DECLARE_METATYPE(SmartAttribute)



/*
 * List of SMART attribute
 */
typedef QList<SmartAttribute> SmartAttributesList;
Q_DECLARE_METATYPE(SmartAttributesList)


extern QDBusArgument &operator<<(QDBusArgument &argument, const SmartAttribute& smartAttribue);
extern const QDBusArgument &operator>>(const QDBusArgument &argument, SmartAttribute& smartAttribue);



/*
 * Structure mapping a MDRaid member in UDisks2
 */
struct MDRaidMember {
  QDBusObjectPath block;
  qint32 slot;
  QStringList state;
  qint64 numReadErrors;
  QVariantMap expansion;

  //internal type, do not belong to UDisks2
  HealthStatus::Status healthStatus = HealthStatus::Unknown;
};
Q_DECLARE_METATYPE(MDRaidMember)



/*
 * List of MDRaid member
 */
typedef QList<MDRaidMember> MDRaidMemberList;
Q_DECLARE_METATYPE(MDRaidMemberList)


extern QDBusArgument &operator<<(QDBusArgument &argument, const MDRaidMember& smartAttribue);
extern const QDBusArgument &operator>>(const QDBusArgument &argument, MDRaidMember& smartAttribue);


#endif // METATYPES_H
