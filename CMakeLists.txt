CMAKE_MINIMUM_REQUIRED(VERSION 3.12 FATAL_ERROR)
SET(CMAKE_CXX_STANDARD 17)

IF (MSVC)
ADD_COMPILE_OPTIONS("/W4")
ELSE()
ADD_COMPILE_OPTIONS("-Wall" "-Wextra" "-Werror" "-Wno-unused-function" "-Wno-unused-label" "-Wno-unused-parameter")
ENDIF(MSVC)

PROJECT(FreedomSearch)
SET(CMAKE_INCLUDE_CURRENT_DIR ON)

# Internal subdirectories which we use for our own stuff.
ADD_SUBDIRECTORY(FreedomHTTP)

# Add mariadbpp, since it'll be needed for connecting to a database server.
ADD_SUBDIRECTORY(Externals/mariadbpp)
INCLUDE_DIRECTORIES(Externals/mariadbpp/include)

LIST(APPEND SOURCES Main.cpp)

ADD_EXECUTABLE(${CMAKE_PROJECT_NAME}
	${SOURCES} 
	${HEADERS}
)

TARGET_LINK_LIBRARIES(${CMAKE_PROJECT_NAME} FreedomHTTP)

IF (UNIX)
TARGET_LINK_LIBRARIES(${CMAKE_PROJECT_NAME} pthread)
ENDIF(UNIX)

IF (CMAKE_BUILD_TYPE STREQUAL Release)
    ADD_CUSTOM_COMMAND(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_STRIP} ${CMAKE_PROJECT_NAME})
ENDIF()
