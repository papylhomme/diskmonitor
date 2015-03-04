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


#include "kconfiglistwidget.h"

#include <KConfigDialogManager>


using namespace Settings;


/*
 * Constructor
 */
KConfigListWidget::KConfigListWidget(QWidget* parent) : QListWidget(parent)
{
  //register change signal to KConfigDialogManager
  if(!KConfigDialogManager::changedMap() -> contains("KConfigListWidget"))
    KConfigDialogManager::changedMap() -> insert("KConfigListWidget", SIGNAL(changed(const QList<int>&)));
}



/*
 * Destructor
 */
KConfigListWidget::~KConfigListWidget()
{

}



/*
 * Property getter for KConfigDialogManager
 */
QList<int> KConfigListWidget::items()
{
  QList<int> res;

  for(int i = 0; i < count(); i++)
    res << item(i) -> text().toInt();

  return res;
}



/*
 * Property setter for KConfigDialogManager
 */
void KConfigListWidget::setItems(const QList<int>& items)
{
  QStringList newItems;


  foreach(int i, items)
    newItems << QString::number(i);

  clear();
  addItems(newItems);
}



/*
 * Wrap underlying method of QListWidget in order to emit changed signal
 */
void KConfigListWidget::addItem(QListWidgetItem* item)
{
  QListWidget::addItem(item);
  emit changed(items());
}



/*
 * Wrap underlying method of QListWidget in order to emit changed signal
 */
void KConfigListWidget::addItem(const QString& label)
{
  QListWidget::addItem(label);
  emit changed(items());
}



/*
 * Wrap underlying method of QListWidget in order to emit changed signal
 */
void KConfigListWidget::addItems(const QStringList& labels)
{
  QListWidget::addItems(labels);
  emit changed(items());
}



/*
 * Wrap underlying method of QListWidget in order to emit changed signal
 */
void KConfigListWidget::insertItem(int row, QListWidgetItem* item)
{
  QListWidget::insertItem(row, item);
  emit changed(items());
}



/*
 * Wrap underlying method of QListWidget in order to emit changed signal
 */
void KConfigListWidget::insertItem(int row, const QString& label)
{
  QListWidget::insertItem(row, label);
  emit changed(items());
}



/*
 * Wrap underlying method of QListWidget in order to emit changed signal
 */
void KConfigListWidget::insertItems(int row, const QStringList& labels)
{
  QListWidget::insertItems(row, labels);
  emit changed(items());
}



/*
 * Wrap underlying method of QListWidget in order to emit changed signal
 */
void KConfigListWidget::removeItemWidget(QListWidgetItem* item)
{
  QListWidget::removeItemWidget(item);
  emit changed(items());
}



/*
 * Wrap underlying method of QListWidget in order to emit changed signal
 */
QListWidgetItem*KConfigListWidget::takeItem(int row)
{
  QListWidgetItem* item = QListWidget::takeItem(row);
  emit changed(items());
  return item;
}



/*
 * Wrap underlying method of QListWidget in order to emit changed signal
 */
void KConfigListWidget::clear()
{
  QListWidget::clear();
  emit changed(items());
}


