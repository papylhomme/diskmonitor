#ifndef MDRAIDPROPERTIESMODEL_H
#define MDRAIDPROPERTIESMODEL_H

#include "storageunitpropertiesmodel.h"

#include "mdraid.h"

class MDRaidPropertiesModel : public StorageUnitPropertiesModel
{
  Q_OBJECT

public:
    MDRaidPropertiesModel();
    ~MDRaidPropertiesModel();

    MDRaid* getMDRaid() const;


    virtual int rowCount(const QModelIndex& index) const;
    virtual int columnCount(const QModelIndex& index) const;
    virtual QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;

private:
    QStringList names;
};

#endif // MDRAIDPROPERTIESMODEL_H
