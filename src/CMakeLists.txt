set(SOURCE_FILES
        game.cpp game.h
        controller.cpp controller.h
        log_manager.cpp log_manager.h

        model.h model.cpp

        game_config.cpp game_config.h

        game_loop.cpp game_loop.h

        entities/movable_character.h entities/movable_character.cpp
        entities/pacman.h
        entities/ghosts/abstract_ghost.h entities/ghosts/abstract_ghost.cpp
        entities/ghosts/blue_ghost.h
        entities/ghosts/orange_ghost.h
        entities/ghosts/purple_ghost.h
        entities/ghosts/red_ghost.h

        ghost_timing_manager.cpp ghost_timing_manager.h

        direction.h

        path_points.h path_points.cpp
        coordinates.h coordinates.cpp
        score_manager.h

        abstract_movement_manager.cpp abstract_movement_manager.h
        pacman_movement_manager.h
        ghost_movement_manager.cpp ghost_movement_manager.h

        pellets/abstract_pellet.h
        pellets/standard_pellet.h
        pellets/power_pellet.h

        pellets/abstract_pellets_manager.h
        pellets/standard_pellets_manager.h
        pellets/power_pellets_manager.h

        pellets/abstract_pellets_model.h pellets/abstract_pellets_model_impl.h
        pellets/standard_pellets_model.h
        pellets/power_pellets_model.h

        window_manager.cpp window_manager.h
        resolution.h
        input_handler.cpp input_handler.h
        qml_helper.h
        game_coordinator.cpp game_coordinator.h
        overlay_manager.cpp overlay_manager.h
        game_result.h

        state_machine/abstract_state.h
        state_machine/game_state_manager.h
        state_machine/game_state_type.h
        state_machine/i_state_actions.h
        state_machine/states/ended_defeat_state.h
        state_machine/states/ended_victory_state.h
        state_machine/states/escape_menu_state.h
        state_machine/states/initialization_state.h
        state_machine/states/paused_for_debug_state.h
        state_machine/states/ready_to_start_state.h
        state_machine/states/running_state.h

        collision_detection/pellet_collision_detector.h
        collision_detection/ghost_collision_detector.h
        collision_detection/utils.h
)

add_library(${PROJECT_NAME}Backend ${SOURCE_FILES})
target_include_directories(${PROJECT_NAME}Backend PUBLIC ${PROJECT_SOURCE_DIR}/src)
target_link_libraries(${PROJECT_NAME}Backend PUBLIC Qt6::Core Qt6::Quick)

target_compile_definitions(${PROJECT_NAME}Backend PRIVATE
        APP_VERSION="${PROJECT_VERSION}"
        BUILD_TYPE="$<CONFIG>"
)

qt_add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE ${PROJECT_NAME}Backend Qt6::Quick PacmanQmlLibplugin)

qt_add_resources(${PROJECT_NAME}
        PREFIX /
        FILES "../assets/resources.qrc"
)

if (WIN32)
    set_target_properties(${PROJECT_NAME} PROPERTIES WIN32_EXECUTABLE $<CONFIG:Release>) # this avoids opening console window on Windows in Release mode
endif ()

set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin) # Set the output directory for the executable
