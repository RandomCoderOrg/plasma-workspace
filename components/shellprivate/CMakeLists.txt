
if (KF5TextEditor_FOUND)
   set(interactiveconsole_SRCS
       interactiveconsole/interactiveconsole.cpp
       )
endif (KF5TextEditor_FOUND)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/config-shellprivate.h.cmake ${CMAKE_CURRENT_BINARY_DIR}/config-shellprivate.h)

set(plasmashellprivateplugin_SRCS
    widgetexplorer/kcategorizeditemsviewmodels.cpp
    widgetexplorer/plasmaappletitemmodel.cpp
    widgetexplorer/openwidgetassistant.cpp
    widgetexplorer/widgetexplorer.cpp
    shellprivateplugin.cpp
    ${interactiveconsole_SRCS}
)

add_library(plasmashellprivateplugin SHARED ${plasmashellprivateplugin_SRCS})
target_link_libraries(plasmashellprivateplugin
        Qt::Core
        Qt::Quick
        Qt::Qml
        Qt::Gui
        Qt::Widgets
        Qt::Quick
        Qt::Qml
        KF5::Plasma
        KF5::PlasmaQuick
        KF5::I18n
        KF5::Service
        KF5::NewStuff
        KF5::KIOFileWidgets
        KF5::WindowSystem
        KF5::Declarative
        KF5::Activities
        KF5::TextWidgets
)

if (KF5TextEditor_FOUND)
   target_link_libraries(plasmashellprivateplugin
                         KF5::TextEditor)
endif (KF5TextEditor_FOUND)

install(TARGETS plasmashellprivateplugin DESTINATION ${KDE_INSTALL_QMLDIR}/org/kde/plasma/private/shell)
install(FILES
    wallpaperplugin.knsrc
    widgetexplorer/plasmoids.knsrc
    DESTINATION ${KDE_INSTALL_KNSRCDIR}
)

install(FILES qmldir DESTINATION ${KDE_INSTALL_QMLDIR}/org/kde/plasma/private/shell)

