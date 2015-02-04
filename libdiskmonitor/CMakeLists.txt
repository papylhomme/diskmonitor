set(LIBDISKMONITOR_SRCS
  storageunit.cpp
  drive.cpp
  mdraid.cpp
  udisks2wrapper.cpp
)

add_library( libdiskmonitor STATIC ${LIBDISKMONITOR_SRCS} )

target_link_libraries( libdiskmonitor
    Qt5::Core
    Qt5::DBus
)

