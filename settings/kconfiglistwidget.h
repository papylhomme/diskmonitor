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


#ifndef KCONFIGLISTWIDGET_H
#define KCONFIGLISTWIDGET_H

#include <QListWidget>

namespace Settings {

  /*
   * Wrapper around QListWidget providing support for KConfigDialogManager
   */
  class KConfigListWidget : public QListWidget
  {
    Q_OBJECT
    Q_PROPERTY( QList<int> items READ items WRITE setItems USER true )
  public:
    KConfigListWidget(QWidget* parent = nullptr);
    ~KConfigListWidget();

    QList<int> items();
    void setItems(const QList<int>& items);

    void addItem(QListWidgetItem* item);
    void addItem(const QString &label);
    void addItems(const QStringList &labels);

    void insertItem(int row, QListWidgetItem* item);
    void insertItem(int row, const QString &label);
    void insertItems(int row, const QStringList &labels);

    void removeItemWidget(QListWidgetItem *item);
    QListWidgetItem* takeItem(int row);
    void clear();

  signals:
    void changed( const QList<int>& newItems );
  };

}

#endif // KCONFIGLISTWIDGET_H
