#include "configskeleton.h"


using namespace Settings;



/*
 * Constructor
 */
ConfigSkeleton::ConfigSkeleton(const QString& configName) : KConfigSkeleton(configName)
{

}



/*
 * Destructor
 */
ConfigSkeleton::~ConfigSkeleton()
{

}



/*
 * Reload the configuration and emit configChanged
 */
void Settings::ConfigSkeleton::load()
{
  KConfigSkeleton::load();
  emit configChanged();
}
