set(MODULE_NAME PacmanQml)
set(LIB_NAME ${MODULE_NAME}Lib) # PacmanQmlLib

qt_add_library(${LIB_NAME} STATIC)

target_link_libraries(${LIB_NAME} PRIVATE Qt6::Quick)

qt_add_qml_module(${LIB_NAME}
        URI ${MODULE_NAME}
        VERSION 1.0
        OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/PacmanQml
        QML_FILES
        Main.qml
        GameArea.qml
        GameInput.qml
        UiScaler.qml

        Arena.qml

        entities/Pacman.qml
        entities/ghosts/AbstractGhost.qml
        entities/ghosts/BlueGhost.qml
        entities/ghosts/OrangeGhost.qml
        entities/ghosts/PurpleGhost.qml
        entities/ghosts/RedGhost.qml

        pellets/StandardPellet.qml
        pellets/PowerPellet.qml

        Score.qml

        overlays/TextOverlay.qml
        overlays/EndGameOverlay.qml
        overlays/EscapeMenuOverlay.qml
)
