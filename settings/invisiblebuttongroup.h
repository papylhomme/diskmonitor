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


#ifndef INVISIBLEBUTTONGROUP_H
#define INVISIBLEBUTTONGROUP_H

#include <QWidget>
#include <QButtonGroup>
#include <QAbstractButton>


class QAbstractButton;

namespace Settings {

  class InvisibleButtonGroupPrivate;
  class InvisibleButtonGroup : public QWidget {
    Q_OBJECT
    Q_PROPERTY(int current READ selected WRITE setSelected)
  public:
    explicit InvisibleButtonGroup(QWidget* parent = nullptr);
    ~InvisibleButtonGroup();

    int selected() const;

    void addButton(QAbstractButton* button, int id);

  public Q_SLOTS:
    void setSelected(int id);

  Q_SIGNALS:
    void selectionChanged(int id);

  private:
    InvisibleButtonGroupPrivate* const d;
  };


  class InvisibleButtonGroupPrivate {
  public:
    QButtonGroup* mGroup;
  };

}

#endif /* INVISIBLEBUTTONGROUP_H */
