cmake_minimum_required(VERSION 3.16)

project(IncubatorLib)

file(GLOB_RECURSE INCUBATOR_LIB_SRCS src/*.cpp)

add_library(${PROJECT_NAME}
    ${INCUBATOR_LIB_SRCS}
)

target_link_libraries(${PROJECT_NAME} PUBLIC
    MFByteStreamLib
    TC2004Lib
    DHT11Lib
    NTCLib
    Eeprom24CLib
    SHT3XLib
    JoystickLib
)
target_include_directories(${PROJECT_NAME} PUBLIC include)
