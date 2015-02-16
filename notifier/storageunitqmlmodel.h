#ifndef STORAGEUNITQMLMODEL_H
#define STORAGEUNITQMLMODEL_H

#include <QAbstractListModel>
#include <QTimer>

#include "storageunit.h"
#include "iconprovider.h"



/*
 * Main model class for the plasma applet
 *
 * Provide a Qt Model to display the Storage units, and
 * global health status
 */
class StorageUnitQmlModel : public QAbstractListModel
{
  Q_OBJECT
  Q_PROPERTY(bool failing READ failing)
  Q_PROPERTY(QString status READ status NOTIFY statusChanged)

public:
  enum AnimalRoles {
    NameRole = Qt::UserRole + 1,
    DeviceRole,
    FailingRole,
    FailingKnownRole,
    PathRole,
    IconRole
  };

  StorageUnitQmlModel();
  ~StorageUnitQmlModel();

  bool failing() const;
  QString status() const;

  virtual QHash<int, QByteArray> roleNames() const;
  int rowCount(const QModelIndex & parent = QModelIndex()) const;
  QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

private:
  Settings::IconProvider iconProvider;
  QTimer* timer;
  QList<StorageUnit*> storageUnits;

  bool hasFailing = false;
  QList<StorageUnit*> failingUnits;

  void processUnit(StorageUnit* unit);
  void processUnits(const QList<StorageUnit*> & units);
  QString getIconForUnit(StorageUnit* unit) const;

private slots:
  void storageUnitAdded(StorageUnit* drive);
  void storageUnitRemoved(StorageUnit* path);
  void monitor();

signals:
  void statusChanged();

public slots:
  void configChanged();
  void refresh();
  void showSettings();
  void openApp(const QString& unitPath);
};

#endif // STORAGEUNITQMLMODEL_H
