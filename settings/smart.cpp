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


#include "smart.h"


using namespace Settings;



/*
 * Constructor
 */
SMART::SMART(QWidget *parent) : QWidget(parent) {
  setupUi(this);

  connect(this -> clearButton, SIGNAL(clicked()), this, SLOT(clear()));
  connect(this -> addButton, SIGNAL(clicked()), this, SLOT(add()));
  connect(this -> removeButton, SIGNAL(clicked()), this, SLOT(remove()));
}



/*
 * Add the value from the spinbox to the list
 */
void SMART::add()
{
  this -> kcfg_SensitiveAttributes -> addItem(new QListWidgetItem(QString::number(this -> spinBox -> value())));
}



/*
 * Remove the current item from the list
 */
void SMART::remove()
{
  int row = this -> kcfg_SensitiveAttributes -> currentRow();

  if(row >= 0) {
    QListWidgetItem* item = this -> kcfg_SensitiveAttributes -> takeItem(row);
    delete item;
  }
}



/*
 * Empty the list
 */
void SMART::clear()
{
  this -> kcfg_SensitiveAttributes -> clear();
}

