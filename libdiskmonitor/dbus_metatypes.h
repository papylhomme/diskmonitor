#ifndef METATYPES_H
#define METATYPES_H

#include <QtCore>
#include <QtDBus>


/*
 * A map of interface (key) with there properties (value)
 */
typedef QMap<QString,QVariantMap> InterfaceList;
Q_DECLARE_METATYPE(InterfaceList)



/*
 * A map of node (key) with there interfaces
 */
typedef QMap<QDBusObjectPath, InterfaceList> ManagedObjectList;
Q_DECLARE_METATYPE(ManagedObjectList)



/*
 * Structure mapping a SMART attribute on UDisks2
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



/*
 * List of SMART attribute
 */
typedef QList<SmartAttribute> SmartAttributesList;
Q_DECLARE_METATYPE(SmartAttributesList)


extern QDBusArgument &operator<<(QDBusArgument &argument, const SmartAttribute& smartAttribue);
extern const QDBusArgument &operator>>(const QDBusArgument &argument, SmartAttribute& smartAttribue);



/*
 * Structure mapping a MDRaid member in UDisks2
 */
struct MDRaidMember {
   QDBusObjectPath block;
   qint32 slot;
   QStringList state;
   qint64 numReadErrors;
   QVariantMap expansion;
};
Q_DECLARE_METATYPE(MDRaidMember)



/*
 * List of MDRaid member
 */
typedef QList<MDRaidMember> MDRaidMemberList;
Q_DECLARE_METATYPE(MDRaidMemberList)


extern QDBusArgument &operator<<(QDBusArgument &argument, const MDRaidMember& smartAttribue);
extern const QDBusArgument &operator>>(const QDBusArgument &argument, MDRaidMember& smartAttribue);


#endif // METATYPES_H
