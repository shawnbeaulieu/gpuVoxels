cmake_minimum_required(VERSION 3.5)

set(CMAKE_BUILD_TYPE "Debug")

project(VoxCAD LANGUAGES CXX CUDA)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(VOXCAD_MAIN src/main)
set(VX1 src/VX1)
set(VX2 src/VX2)
set(QTUTILS src/QTUtils)

file(GLOB VOXCAD_MAIN_SRC ${VOXCAD_MAIN}/*.c* ${VOXCAD_MAIN}/*.h)
file(GLOB VX2_SRC ${VX2}/src/*.c* ${VX2}/src/*.h)
file(GLOB VX1_SRC ${VX1}/*.c* ${VX1}/*.h)
file(GLOB QTUTILS_SRC ${QTUTILS}/*.c* ${QTUTILS}/*.h)

add_executable(VoxCAD VoxCad.qrc ${VOXCAD_MAIN_SRC} ${VX2_SRC} ${VX1_SRC} ${QTUTILS_SRC})

add_compile_definitions(QT_XML_LIB QT_OPENGL_LIB USE_ZLIB_COMPRESSION USE_OPEN_GL QT_DLL PREC_MED USE_OMP)

target_include_directories(VoxCAD PUBLIC ${VOXCAD_MAIN} ${VX2}/include ${VX1} ${QTUTILS})
find_package(Qt5 COMPONENTS Core Gui Xml OpenGL Concurrent Widgets REQUIRED)
target_link_libraries(VoxCAD PRIVATE Qt5::Core Qt5::Gui Qt5::Xml Qt5::OpenGL Qt5::Concurrent Qt5::Widgets)


#for visualization
set(OpenGL_GL_PREFERENCE GLVND)
if (UNIX)
    find_package(OpenGL REQUIRED) # find and include OpenGL
    if (OpenGL_FOUND)
        message(STATUS "OPENGL FOUND")
        target_include_directories(VoxCAD PRIVATE ${OpenGL_INCLUDE_DIRS})
        target_link_libraries(VoxCAD PRIVATE ${OpenGL_LIBRARIES} GL)
        target_link_libraries(VoxCAD PRIVATE ${OPENGL_glu_LIBRARY})
    endif()
else()
    find_package(OPENGL REQUIRED) # find and include OpenGL
    if (OPENGL_FOUND)
        message(STATUS "OPENGL FOUND")
        target_include_directories(VoxCAD PRIVATE ${OPENGL_INCLUDE_DIRS})
        target_link_libraries(VoxCAD PRIVATE ${OPENGL_LIBRARIES})
    endif()
endif()

find_package(glfw3 CONFIG REQUIRED)
if (glfw3_FOUND)
    message(STATUS "GLFW FOUND")
    target_include_directories(VoxCAD PRIVATE ${glfw3_INCLUDE_DIRS})
    target_link_libraries(VoxCAD PRIVATE ${glfw3_LIBRARIES})
endif()

find_package(GLUT REQUIRED) # GLEW
if (GLUT_FOUND)
    message(STATUS "GLUT FOUND")
    target_include_directories(VoxCAD PRIVATE ${GLUT_INCLUDE_DIRS})
    target_link_libraries(VoxCAD PRIVATE ${GLUT_LIBRARIES} glut)
endif()

find_package(glm CONFIG REQUIRED) # glm
if (glm_FOUND)
    message(STATUS "GLM FOUND")
    target_include_directories(VoxCAD PRIVATE ${glm_INCLUDE_DIRS})
    target_link_libraries(VoxCAD PRIVATE ${glm_LIBRARIES} glm)
endif()


#for zlib
find_package(ZLIB)
target_link_libraries(VoxCAD PRIVATE ${ZLIB_LIBRARIES})