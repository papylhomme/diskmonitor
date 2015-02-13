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
  resources.qrc
)

ki18n_wrap_ui(APP_SRCS
  mainwindow.ui
  drivepanel.ui
  mdraidpanel.ui
)

add_executable( diskmonitor ${APP_SRCS} )

target_link_libraries( diskmonitor
  libdiskmonitor
  libsettings
  Qt5::Core
  Qt5::DBus
  KF5::CoreAddons
  KF5::I18n
  KF5::IconThemes
  KF5::XmlGui
)

install(TARGETS diskmonitor ${INSTALL_TARGETS_DEFAULT_ARGS} )
install(FILES icon.svg RENAME diskmonitor.svg DESTINATION "${CMAKE_INSTALL_PREFIX}/share/icons/" )
install(FILES diskmonitor.desktop DESTINATION "${CMAKE_INSTALL_PREFIX}/share/applications/" )

