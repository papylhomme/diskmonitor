#ifndef MDRAIDMEMBERSMODEL_H
#define MDRAIDMEMBERSMODEL_H

#include "storageunitpropertiesmodel.h"

#include "mdraid.h"


/*
 * A Qt model to display raid members in a table
 */
class MDRaidMembersModel : public StorageUnitPropertiesModel
{
  Q_OBJECT

public:
  MDRaidMembersModel();
  ~MDRaidMembersModel();

  MDRaid* getMDRaid() const;


  virtual int rowCount(const QModelIndex& index) const;
  virtual int columnCount(const QModelIndex& index) const;
  virtual QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;
  virtual QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

protected:
  virtual void updateInternalState();

private:
  QStringList headerLabels;
  MDRaidMemberList members;

};

#endif // MDRAIDMEMBERSMODEL_H
