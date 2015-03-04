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


#include "appearance.h"

#include "iconmode.h"

using namespace Settings;



/*
 * Constructor
 */
Appearance::Appearance(QWidget *parent) : QWidget(parent) {
  setupUi(this);

  iconModeButtonGroup = new InvisibleButtonGroup(this);
  iconModeButtonGroup -> setObjectName("kcfg_IconMode");
  iconModeButtonGroup -> addButton(emotesIconModeRadioButton, int(DiskMonitor::IconMode::Emotes));
  iconModeButtonGroup -> addButton(dialogsIconModeRadioButton, int(DiskMonitor::IconMode::Dialogs));
  iconModeButtonGroup -> addButton(customIconModeRadioButton, int(DiskMonitor::IconMode::Custom));
}


