cmake_minimum_required(VERSION 2.8.11)
project(test_pipeline)

find_package(Qt5Core    REQUIRED)
find_package(Qt5Gui     REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Quick   REQUIRED)
find_package(Qt5Charts	REQUIRED)

#MINGW or MSVC COMPILE FLAGS
IF (CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX )
   MESSAGE( STATUS "Setting flags for GNU GCC")
   SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11")
   SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")
   SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wall")
ENDIF(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)

IF (MSVC)
   MESSAGE( STATUS "Setting flags for Visual Studio")
   SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")
ENDIF(MSVC)

enable_testing(true)

SET(srcs
    ${CMAKE_CURRENT_SOURCE_DIR}/TestAll.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/TestPipeline.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/TestMultiply.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../applicationOpenimu/app/CustomQmlScene.cpp
    )

SET(headers
    ${CMAKE_CURRENT_SOURCE_DIR}/TestAll.h
    ${CMAKE_CURRENT_SOURCE_DIR}/TestPipeline.h
    ${CMAKE_CURRENT_SOURCE_DIR}/TestMultiply.h
    ${CMAKE_CURRENT_SOURCE_DIR}/../applicationOpenimu/app/CustomQmlScene.h
    )
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../applicationOpenimu/app/core ${CMAKE_CURRENT_BINARY_DIR}/core)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../applicationOpenimu/app/algorithm ${CMAKE_CURRENT_BINARY_DIR}/algorithm)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../applicationOpenimu/app/acquisition ${CMAKE_CURRENT_BINARY_DIR}/acquisition)


include_directories(
    ../applicationOpenimu/app/core/json
    )

# Tell CMake to run moc when necessary:
set(CMAKE_AUTOMOC ON)

# As moc files are generated in the binary dir, tell CMake
# to always look for includes there:
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt5Test REQUIRED)

add_executable(unitTests main.cpp ${srcs} ${headers})
add_test(unitTests unitTests)
qt5_use_modules(unitTests Sql Core Network Xml XmlPatterns Gui Widgets Quick Charts)

target_link_libraries(unitTests Qt5::Test)
