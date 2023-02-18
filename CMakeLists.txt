cmake_minimum_required(VERSION 3.23)
project(NitreetLibTemplate)

set(CMAKE_CXX_STANDARD 17)

enable_testing()

# Add library's directories
add_subdirectory("3rdparty/googletest")

# Create definition of our library
SET(PROJECT_SRC "${CMAKE_CURRENT_LIST_DIR}/src")

FILE(GLOB_RECURSE
        PROJECT_FILES
        RELATIVE "${CMAKE_CURRENT_LIST_DIR}"
        "${PROJECT_SRC}/*.hpp"
        "${PROJECT_SRC}/*.cpp"
)

add_library(${PROJECT_NAME} SHARED ${PROJECT_FILES})
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SRC})

SET(LIBRARIES_TO_LINK_PRIVATE
        ""
)

SET(LIBRARIES_TO_LINK_PUBLIC
        ""
)

target_link_libraries(${PROJECT_NAME} PUBLIC ${LIBRARIES_TO_LINK_PUBLIC})
target_link_libraries(${PROJECT_NAME} PRIVATE ${LIBRARIES_TO_LINK_PRIVATE})

# Add tests
add_subdirectory(tests)