#ifndef METATYPES_H
#define METATYPES_H

#include <QtCore>
#include <QtDBus>


typedef QMap<QString,QVariantMap> InterfaceList;
Q_DECLARE_METATYPE(InterfaceList)

typedef QMap<QDBusObjectPath, InterfaceList> ManagedObjectList;
Q_DECLARE_METATYPE(ManagedObjectList)



/*
 *
 */
struct SmartAttribute {
  quint8 id;
  QString name;
  quint16 flags;
  qint32 value;
  qint32 worst;
  qint32 threshold;
  qint64 pretty;
  qint32 pretty_unit;
  QVariantMap expansion;
};
Q_DECLARE_METATYPE(SmartAttribute)

typedef QList<SmartAttribute> SmartAttributesList;
Q_DECLARE_METATYPE(SmartAttributesList)



#endif // METATYPES_H
