#ifndef MDRAIDPROPERTIESMODEL_H
#define MDRAIDPROPERTIESMODEL_H

#include <QAbstractTableModel>

#include "mdraid.h"

class MDRaidPropertiesModel : public QAbstractTableModel
{
  Q_OBJECT

public:
    MDRaidPropertiesModel();
    ~MDRaidPropertiesModel();


    void updateMDRaid(MDRaid* raid);
    MDRaid* getMDRaid();

    void refreshAll();

    virtual int rowCount(const QModelIndex& index) const;
    virtual int columnCount(const QModelIndex& index) const;
    virtual QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;

private:
    QStringList names;
    MDRaid* mdraid;
};

#endif // MDRAIDPROPERTIESMODEL_H
