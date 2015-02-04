#ifndef STORAGEUNIT_H
#define STORAGEUNIT_H

#include <QDBusObjectPath>
#include <QDBusInterface>


/*
 * Base class for representing an unit of storage in UDisks2
 */
class StorageUnit : public QObject
{
  Q_OBJECT

public:
  StorageUnit();
  StorageUnit(QDBusObjectPath objectPath, QString device);
  StorageUnit(const StorageUnit&);
  ~StorageUnit();

  QDBusObjectPath getObjectPath() const;
  QString getPath() const;
  QString getDevice() const;
  QString getName() const;

  bool isFailing() const;
  bool isFailingStatusKnown() const;


  virtual void update()
  {
    //QMETA_TYPE require a public empty constructor, we can't
    //use pure virtual here
  }
  //virtual void update() = 0;

  virtual bool isDrive() const { return false; }
  virtual bool isMDRaid() const { return false; }

protected:
  QDBusObjectPath objectPath;
  QString device;
  QString name;

  bool failing = false;
  bool failingStatusKnown = false;

  QVariant getProperty(QDBusInterface*, const char*) const;
  bool getBoolProperty(QDBusInterface*, const char*) const;
  int getIntProperty(QDBusInterface*, const char*) const;
  double getDoubleProperty(QDBusInterface*, const char*) const;
  QString getStringProperty(QDBusInterface*, const char*) const;
};

Q_DECLARE_METATYPE(StorageUnit)

#endif // STORAGEUNIT_H
