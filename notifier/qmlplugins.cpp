#include "qmlplugins.h"

#include <QtQml>

#include "storageunitqmlmodel.h"

void QmlPlugins::registerTypes(const char* uri)
{
    // @uri org.papylhomme.diskmonitor.StorageUnitQmlModel
    qmlRegisterType<StorageUnitQmlModel>(uri, 0, 1, "StorageUnitQmlModel");
}
