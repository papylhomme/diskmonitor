#ifndef DRIVEPROPERTIESMODEL_H
#define DRIVEPROPERTIESMODEL_H

#include <QAbstractTableModel>

#include "drive.h"

class DrivePropertiesModel : public QAbstractTableModel
{
  Q_OBJECT

public:
  DrivePropertiesModel();
  ~DrivePropertiesModel();


  void updateDrive(Drive* drive);
  Drive* getDrive();

  void refreshAll();

  virtual int rowCount(const QModelIndex& index) const;
  virtual int columnCount(const QModelIndex& index) const;
  virtual QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;
  virtual QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

private:
  QStringList headerLabels;
  SmartAttributesList attributes;
  Drive* drive;
};

#endif // DRIVEPROPERTIESMODEL_H
