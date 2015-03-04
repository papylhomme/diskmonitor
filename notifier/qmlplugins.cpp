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


#include "qmlplugins.h"

#include <QtQml>

#include "storageunitqmlmodel.h"
#include "storageunitmonitor.h"


/*
 * Register types to QML engine
 */
void QmlPlugins::registerTypes(const char* uri)
{
    // @uri org.papylhomme.diskmonitor.StorageUnitQmlModel
    qmlRegisterType<StorageUnitQmlModel>(uri, 0, 1, "StorageUnitQmlModel");

    // @uri org.papylhomme.diskmonitor.StorageUnitMonitor
    qmlRegisterType<StorageUnitMonitor>(uri, 0, 1, "StorageUnitMonitor");
}
