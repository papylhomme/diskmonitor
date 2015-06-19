set( SETTINGS_SRCS 
  configdialog.cpp
  configskeleton.cpp
  kconfiglistwidget.cpp
  invisiblebuttongroup.cpp
  iconprovider.cpp
  appearance.cpp
  smart.cpp
)

ki18n_wrap_ui( SETTINGS_SRCS 
  appearance.ui
  smart.ui
)

kconfig_add_kcfg_files( SETTINGS_SRCS diskmonitor_settings.kcfgc )

add_library( libsettings STATIC ${SETTINGS_SRCS} )

target_link_libraries( libsettings
  Qt5::Core
  KF5::ConfigWidgets
  KF5::IconThemes
  KF5::I18n
)

install( FILES diskmonitor.kcfg  DESTINATION ${KCFG_INSTALL_DIR})

