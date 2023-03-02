cmake_minimum_required(VERSION 3.23)
project(simple_sar)

set(CMAKE_CXX_STANDARD 20)

enable_testing()

# Add library's directories
add_subdirectory("3rdparty/googletest")
add_subdirectory("3rdparty/spdlog")

# Create definition of our library
SET(PROJECT_SRC "${CMAKE_CURRENT_LIST_DIR}/src")
SET (IMGUI_SOURCE_DIR "3rdparty/imgui")

FILE(GLOB_RECURSE
        PROJECT_FILES
        RELATIVE "${CMAKE_CURRENT_LIST_DIR}"
        "${PROJECT_SRC}/*.hpp"
        "${PROJECT_SRC}/*.cpp"
)

add_library(${PROJECT_NAME} STATIC ${PROJECT_FILES})
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SRC} ${IMGUI_SOURCE_DIR})

add_library(${PROJECT_NAME}_ready4injection MODULE ${PROJECT_FILES})
target_include_directories(${PROJECT_NAME}_ready4injection PRIVATE ${IMGUI_SOURCE_DIR})
target_link_libraries(${PROJECT_NAME}_ready4injection PRIVATE spdlog)

SET(LIBRARIES_TO_LINK_PRIVATE
        ""
)

SET(LIBRARIES_TO_LINK_PUBLIC
        ""
)

target_link_libraries(${PROJECT_NAME} PUBLIC ${LIBRARIES_TO_LINK_PUBLIC})
target_link_libraries(${PROJECT_NAME} PRIVATE ${LIBRARIES_TO_LINK_PRIVATE} spdlog)

# Add tests
add_subdirectory(tests)