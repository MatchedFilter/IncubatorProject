cmake_minimum_required(VERSION 3.16)

project(IncubatorTestSimulator)


file(GLOB_RECURSE INCUBATOR_SRCS src/*.cpp)

add_executable(${PROJECT_NAME}
    ${INCUBATOR_SRCS}
)

target_include_directories(${PROJECT_NAME} PRIVATE src)

target_link_libraries(${PROJECT_NAME} PUBLIC IncubatorLib)

find_package(SDL2 REQUIRED)
target_include_directories(${PROJECT_NAME} PUBLIC ${SDL2_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PUBLIC ${SDL2_LIBRARIES})

find_package(SDL2_Image REQUIRED)
target_link_libraries(${PROJECT_NAME} PUBLIC SDL2_image)

find_package(SDL2_TTF REQUIRED)
target_link_libraries(${PROJECT_NAME} PUBLIC SDL2_ttf)


install(TARGETS ${PROJECT_NAME} DESTINATION ${CMAKE_SOURCE_DIR}/bin/)
install(DIRECTORY resources DESTINATION ${CMAKE_SOURCE_DIR}/bin/)