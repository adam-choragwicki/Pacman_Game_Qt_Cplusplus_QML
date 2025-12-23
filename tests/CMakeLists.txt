set(GOOGLETEST_VERSION 1.17.0)

if (MSVC)
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
endif ()

add_subdirectory(googletest)

find_package(Qt6 6.9.2 COMPONENTS Test REQUIRED)

set(TEST_SOURCES
        src/pacman_test.cpp
        src/ghost_test.cpp
        src/ghost_slowdown_test.cpp
        src/ghost_starting_box_test.cpp)

add_executable(${PROJECT_NAME}Test_run ${TEST_SOURCES})
target_include_directories(${PROJECT_NAME}Test_run PRIVATE ${PROJECT_SOURCE_DIR}/src)
target_link_libraries(${PROJECT_NAME}Test_run PRIVATE gtest_main ${PROJECT_NAME}Backend Qt6::Test)
