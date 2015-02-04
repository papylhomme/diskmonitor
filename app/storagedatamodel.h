#ifndef STORAGEDATAMODEL_H
#define STORAGEDATAMODEL_H

#include <QAbstractListModel>
#include <QMap>

#include "drive.h"

class StorageDataModel : public QAbstractListModel
{
  Q_OBJECT

public:
    StorageDataModel();
    ~StorageDataModel();

    virtual int rowCount(const QModelIndex& index) const;
    virtual QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;

public slots:
    void refresh();

private:
    QMap<QString, StorageUnit*> storageUnits;

private slots:
    void storageUnitAdded(StorageUnit* drive);
    void storageUnitRemoved(QString path);
};

#endif // STORAGEDATAMODEL_H
