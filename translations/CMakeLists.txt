find_program(MSGFMT_EXECUTABLE msgfmt)

add_custom_target (i18n ALL COMMENT "Building i18n messages.")

file (GLOB PO_FILES ${CMAKE_SOURCE_DIR}/translations/app/*.po)
file (MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/app) 
foreach (PO_INPUT ${PO_FILES})
    get_filename_component (PO_INPUT_BASE ${PO_INPUT} NAME_WE)
    set (MO_OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/app/${PO_INPUT_BASE}.mo)
    add_custom_command (TARGET i18n COMMAND ${MSGFMT_EXECUTABLE} -o ${MO_OUTPUT} ${PO_INPUT})
    install (FILES ${MO_OUTPUT} DESTINATION share/locale/${PO_INPUT_BASE}/LC_MESSAGES RENAME diskmonitor.mo)
endforeach (PO_INPUT ${PO_FILES})

file (GLOB PO_FILES ${CMAKE_SOURCE_DIR}/translations/applet/*.po)
file (MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/applet) 
foreach (PO_INPUT ${PO_FILES})
    get_filename_component (PO_INPUT_BASE ${PO_INPUT} NAME_WE)
    set (MO_OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/applet/${PO_INPUT_BASE}.mo)
    add_custom_command (TARGET i18n COMMAND ${MSGFMT_EXECUTABLE} -o ${MO_OUTPUT} ${PO_INPUT})
    install (FILES ${MO_OUTPUT} DESTINATION share/locale/${PO_INPUT_BASE}/LC_MESSAGES RENAME plasma_applet_org.papylhomme.diskmonitor.mo)
endforeach (PO_INPUT ${PO_FILES})

