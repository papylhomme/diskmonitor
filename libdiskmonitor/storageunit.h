#ifndef STORAGEUNIT_H
#define STORAGEUNIT_H

#include <QDBusObjectPath>
#include <QDBusInterface>


/*
 *
 */
class StorageUnit : public QObject
{
  Q_OBJECT

public:
  StorageUnit();
  StorageUnit(QDBusObjectPath objectPath, QString device);
  StorageUnit(const StorageUnit&);
  ~StorageUnit();

  QDBusObjectPath getObjectPath();
  QString getPath();
  QString getDevice();
  QString getName();

  bool isFailing();
  bool isFailingStatusKnown();


  virtual void update()
  {
    //QMETA_TYPE require a public empty constructor, we can't
    //use pure virtual here
  }
  //virtual void update() = 0;

  virtual bool isDrive() { return false; }
  virtual bool isMDRaid() { return false; }

protected:
  QDBusObjectPath objectPath;
  QString device;
  QString name;

  bool failing = false;
  bool failingStatusKnown = false;

  QVariant getProperty(QDBusInterface*, const char*);
  bool getBoolProperty(QDBusInterface*, const char*);
  int getIntProperty(QDBusInterface*, const char*);
  double getDoubleProperty(QDBusInterface*, const char*);
  QString getStringProperty(QDBusInterface*, const char*);

private:


signals:

public slots:
};

Q_DECLARE_METATYPE(StorageUnit)

#endif // STORAGEUNIT_H
