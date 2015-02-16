#ifndef CONFIGSKELETON_H
#define CONFIGSKELETON_H

#include <KConfigSkeleton>

namespace Settings {

  /*
   * Override KConfigSkeleton in order to emit configChanged upon load
   */
  class ConfigSkeleton : public KConfigSkeleton
  {
  public:
      ConfigSkeleton(const QString& configName = QString());
      ~ConfigSkeleton();

      void load();
  };

}

#endif // CONFIGSKELETON_H
