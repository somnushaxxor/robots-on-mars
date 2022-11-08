cmake_minimum_required(VERSION 3.0.0)
project(robots-on-mars)
cmake_policy(SET CMP0074 NEW)
set(CMAKE_CXX_STANDARD 14)

set(MAIN_SOURCES
        ${PROJECT_SOURCE_DIR}/Command/CommandParser/ManualModeCommandParser.cpp
        ${PROJECT_SOURCE_DIR}/Command/CommandParser/RobotCommandParser.cpp
        ${PROJECT_SOURCE_DIR}/Command/CommandParser/SimulationCommandParser.cpp
        ${PROJECT_SOURCE_DIR}/Command/RobotCommand/GrabCommand.cpp
        ${PROJECT_SOURCE_DIR}/Command/RobotCommand/MoveCommand.cpp
        ${PROJECT_SOURCE_DIR}/Command/RobotCommand/ScanCommand.cpp
        ${PROJECT_SOURCE_DIR}/Command/RobotCommand/StopCommand.cpp
        ${PROJECT_SOURCE_DIR}/Command/RobotCommand/RobotCommand.cpp
        ${PROJECT_SOURCE_DIR}/Command/SimulationCommand/AddCommand.cpp
        ${PROJECT_SOURCE_DIR}/Command/SimulationCommand/ContinueCommand.cpp
        ${PROJECT_SOURCE_DIR}/Command/SimulationCommand/EndCommand.cpp
        ${PROJECT_SOURCE_DIR}/Command/SimulationCommand/SetFocusCommand.cpp
        ${PROJECT_SOURCE_DIR}/Command/SimulationCommand/SetModeCommand.cpp
        ${PROJECT_SOURCE_DIR}/Command/SimulationCommand/SimulationCommand.cpp
        ${PROJECT_SOURCE_DIR}/Command/Command.cpp
        ${PROJECT_SOURCE_DIR}/Dispatcher/Dispatcher.cpp
        ${PROJECT_SOURCE_DIR}/Exception/CommandParserException.cpp
        ${PROJECT_SOURCE_DIR}/Exception/CommandException.cpp
        ${PROJECT_SOURCE_DIR}/Exception/DispatcherException.cpp
        ${PROJECT_SOURCE_DIR}/Exception/TerrainLoaderException.cpp
        ${PROJECT_SOURCE_DIR}/Exception/RadioMessageHandlerException.cpp
        ${PROJECT_SOURCE_DIR}/InputHandler/GraphicInputHandler.cpp
        ${PROJECT_SOURCE_DIR}/Mode/AutoMode.cpp
        ${PROJECT_SOURCE_DIR}/Mode/AutoDefuseMode.cpp
        ${PROJECT_SOURCE_DIR}/Mode/AutoGrabMode.cpp
        ${PROJECT_SOURCE_DIR}/Mode/AutoScanMode.cpp
        ${PROJECT_SOURCE_DIR}/Mode/ManualMode.cpp
        ${PROJECT_SOURCE_DIR}/Mode/Mode.cpp
        ${PROJECT_SOURCE_DIR}/Radio/RadioMessage/ApplesGrabbedMessage.cpp
        ${PROJECT_SOURCE_DIR}/Radio/RadioMessage/CommandResponseMessage.cpp
        ${PROJECT_SOURCE_DIR}/Radio/RadioMessage/MapUpdateMessage.cpp
        ${PROJECT_SOURCE_DIR}/Radio/RadioMessage/ModeUpdateMessage.cpp
        ${PROJECT_SOURCE_DIR}/Radio/RadioMessageHandler/DispatcherMessageHandler.cpp
        ${PROJECT_SOURCE_DIR}/Radio/RadioMessageHandler/RobotMessageHandler.cpp
        ${PROJECT_SOURCE_DIR}/Radio/RadioChannel.cpp
        ${PROJECT_SOURCE_DIR}/Radio/RadioModule.cpp
        ${PROJECT_SOURCE_DIR}/Robot/Robot.cpp
        ${PROJECT_SOURCE_DIR}/Robot/BasicMovementRobot/BasicMovementRobot.cpp
        ${PROJECT_SOURCE_DIR}/Robot/BasicMovementRobot/Collector.cpp
        ${PROJECT_SOURCE_DIR}/Robot/BasicMovementRobot/Sapper.cpp
        ${PROJECT_SOURCE_DIR}/Simulation/Simulation.cpp
        ${PROJECT_SOURCE_DIR}/Terrain/Terrain.cpp
        ${PROJECT_SOURCE_DIR}/Terrain/TerrainLoader/TerrainLoader.cpp
        ${PROJECT_SOURCE_DIR}/TerrainMap/TerrainMap.cpp
        ${PROJECT_SOURCE_DIR}/View/View.cpp
        ${PROJECT_SOURCE_DIR}/View/GraphicView.cpp
        ${PROJECT_SOURCE_DIR}/main.cpp
        )

set(TERRAIN_GENERATOR_SOURCES
        ${PROJECT_SOURCE_DIR}/Terrain/TerrainGenerator/TerrainGenerator.cpp
        ${PROJECT_SOURCE_DIR}/Terrain/TerrainGenerator/terrain_generator.cpp
        )

add_executable(MAIN ${MAIN_SOURCES})
add_executable(TERRAIN_GENERATOR ${TERRAIN_GENERATOR_SOURCES})

set(SFML_ROOT ${PROJECT_SOURCE_DIR}/SFML)
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake_modules)
find_package(SFML REQUIRED system window graphics)
include_directories(${SFML_INCLUDE_DIR})
target_link_libraries(MAIN ${SFML_LIBRARIES})

set(MAIN_DLLS
        ${SFML_ROOT}/bin/openal32.dll
        ${SFML_ROOT}/bin/sfml-system-2.dll
        ${SFML_ROOT}/bin/sfml-system-d-2.dll
        ${SFML_ROOT}/bin/sfml-graphics-2.dll
        ${SFML_ROOT}/bin/sfml-graphics-d-2.dll
        ${SFML_ROOT}/bin/sfml-window-2.dll
        ${SFML_ROOT}/bin/sfml-window-d-2.dll
        )

add_custom_command(TARGET MAIN POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different ${MAIN_DLLS} $<TARGET_FILE_DIR:MAIN>) 
