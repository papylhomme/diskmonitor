set(APP_SRCS
  main.cpp
  humanize.cpp
  mainwindow.cpp
  storageunitpanel.cpp
  unknowndrivepanel.cpp
  atadrivepanel.cpp
  mdraidpanel.cpp
  storageunitmodel.cpp
  storageunitpropertiesmodel.cpp
  mdraidpropertiesmodel.cpp
  mdraidmembersmodel.cpp
  atadrivepropertiesmodel.cpp
  resources.qrc
)

ki18n_wrap_ui(APP_SRCS
  mainwindow.ui
  unknowndrivepanel.ui
  atadrivepanel.ui
  mdraidpanel.ui
)

qt5_add_resources(APP_SRCS resources.qrc)

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

