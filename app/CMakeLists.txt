set(APP_SRCS
  main.cpp
  humanize.cpp
  mainwindow.cpp
  storageunitpanel.cpp
  drivepanel.cpp
  mdraidpanel.cpp
  storageunitmodel.cpp
  storageunitpropertiesmodel.cpp
  mdraidpropertiesmodel.cpp
  mdraidmembersmodel.cpp
  drivepropertiesmodel.cpp
)

ki18n_wrap_ui(APP_SRCS
  mainwindow.ui
  drivepanel.ui
  mdraidpanel.ui
)


add_executable( diskmonitor ${APP_SRCS} )

target_link_libraries( diskmonitor
    libdiskmonitor
    Qt5::Core
    Qt5::DBus
    KF5::I18n
    KF5::IconThemes

#TODO cleanup
#    KF5::ConfigWidgets
#    KF5::GuiAddons
#    KF5::Notifications
#    KF5::XmlGui
)

#kconfig_add_kcfg_files(kcalc_KDEINIT_SRCS kcalc_settings.kcfgc )
#kf5_add_kdeinit_executable( diskmonitor ${SRCS})

install(TARGETS diskmonitor ${INSTALL_TARGETS_DEFAULT_ARGS} )

