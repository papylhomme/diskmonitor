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


#include "invisiblebuttongroup.h"

#include <kconfigdialogmanager.h>


using namespace Settings;




InvisibleButtonGroup::InvisibleButtonGroup(QWidget* parent) :
  QWidget(parent),
  d(new InvisibleButtonGroupPrivate)
{
  hide();
  d -> mGroup = new QButtonGroup(this);
  d -> mGroup -> setExclusive(true);
  connect(d -> mGroup, SIGNAL(buttonClicked(int)), SIGNAL(selectionChanged(int)) );

  const QString name = metaObject() -> className();
  if (!KConfigDialogManager::propertyMap() -> contains(name)) {
    KConfigDialogManager::propertyMap() -> insert(name, "current");
  }
}


InvisibleButtonGroup::~InvisibleButtonGroup() {
  delete d;
}


int InvisibleButtonGroup::selected() const {
  return d->mGroup->checkedId();
}


void InvisibleButtonGroup::addButton(QAbstractButton* button, int id) {
  d->mGroup->addButton(button, id);
}


void InvisibleButtonGroup::setSelected(int id) {
  QAbstractButton* button = d->mGroup->button(id);
  if (button) {
    button->setChecked(true);
  }
}
