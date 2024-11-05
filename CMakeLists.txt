cmake_minimum_required(VERSION 3.10)
project(RaspberryPiCamProject)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
set(libcamera_LIBS /usr/lib/aarch64-linux-gnu/libcamera-base.so /usr/lib/aarch64-linux-gnu/libcamera.so /usr/lib/aarch64-linux-gnu/libcamera_app.so)
set(libcamera_INCLUDE_DIRS /usr/include/libcamera)
set(tof_INCLUDE_DIRS libs/tof)
set(HEADERS include/gpio_controller.h)
set(SOURCES src/main.cpp src/gpio_controller.cpp)

add_subdirectory(libs)
# Find required packages
find_package(OpenCV REQUIRED)
# find_package(libcamera REQUIRED)
add_library(libcamera SHARED IMPORTED ${libcamera_LIBS})

# Add your source files
add_executable(main ${SOURCES} ${HEADERS})
add_executable(i2c src/i2c.cpp)

# Include directories
message(libcamera_dirs="${PROJECT_SOURCE_DIR}/include")

# Link libraries
target_link_libraries(main PUBLIC /usr/local/lib/liblgpio.so)
target_link_libraries(main PUBLIC ${libcamera_LIBS})
target_link_libraries(i2c PUBLIC /usr/local/lib/liblgpio.so)
target_link_libraries(i2c PUBLIC ${libcamera_LIBS})
target_link_libraries(i2c PUBLIC tof)

target_include_directories(main PUBLIC ${libcamera_INCLUDE_DIRS})
target_include_directories(main PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_include_directories(i2c PUBLIC ${libcamera_INCLUDE_DIRS})
target_include_directories(i2c PUBLIC ${tof_INCLUDE_DIRS})
target_include_directories(i2c PUBLIC ${PROJECT_BINARY_DIR})
# Print some debug information
message(STATUS "OpenCV libraries: ${OpenCV_LIBS}")
