#ifndef DRIVEPROPERTIESMODEL_H
#define DRIVEPROPERTIESMODEL_H

#include "storageunitpropertiesmodel.h"
#include "drive.h"


/*
 * A Qt model to display smart attributes in a table
 */
class DrivePropertiesModel : public StorageUnitPropertiesModel
{
  Q_OBJECT

public:
  DrivePropertiesModel();
  ~DrivePropertiesModel();

  Drive* getDrive() const;

  virtual int rowCount(const QModelIndex& index) const;
  virtual int columnCount(const QModelIndex& index) const;
  virtual QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;
  virtual QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

protected:
  virtual void updateInternalState();

  QVariant humanizeSmartAttribute(const SmartAttribute& attr) const;

private:
  QStringList headerLabels;
  QList<int> sensitiveAttributes;
  SmartAttributesList attributes;
};

#endif // DRIVEPROPERTIESMODEL_H
