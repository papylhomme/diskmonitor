#include "qmlplugins.h"

#include <QtQml>

#include "storageunitqmlmodel.h"


/*
 * Register types to QML engine
 */
void QmlPlugins::registerTypes(const char* uri)
{
    // @uri org.papylhomme.diskmonitor.StorageUnitQmlModel
    qmlRegisterType<StorageUnitQmlModel>(uri, 0, 1, "StorageUnitQmlModel");
}
