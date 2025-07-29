cmake_minimum_required(VERSION 3.21)

project(mdeditor VERSION 0.1 LANGUAGES CXX)

# Qt 元对象系统
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# C++ 标准
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Qt6
find_package(Qt6 REQUIRED COMPONENTS 
    Widgets 
    WebEngineWidgets
    WebChannel
)

# 源文件
file(GLOB_RECURSE PROJECT_SOURCES
    src/*.cpp
    src/*.h
)

# 可执行文件
qt_add_executable(${PROJECT_NAME} MACOSX_BUNDLE ${PROJECT_SOURCES})

# 链接
target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt6::Widgets
    Qt6::WebEngineWidgets
    Qt6::WebChannel
)

# 安装规则
include(GNUInstallDirs)
install(TARGETS ${PROJECT_NAME}
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)