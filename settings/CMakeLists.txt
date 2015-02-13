set( SETTINGS_SRCS 
  kconfiglistwidget.cpp
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
)


install( FILES diskmonitor.kcfg  DESTINATION ${KCFG_INSTALL_DIR})
install( FILES diskmonitor.rc  DESTINATION ${KXMLGUI_INSTALL_DIR}/diskmonitor)

