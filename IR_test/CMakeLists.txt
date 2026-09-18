#= Общие параметры =============================#
cmake_minimum_required(VERSION 3.10)            # Требование к минимальной версии CMake 

project(Camera_Test VERSION 1.0.0)                  # Имя проекта и его версия

set(CMAKE_CXX_STANDARD 17)			            #
set(CMAKE_CXX_STANDARD_REQUIRED ON)             # Стандарт С++17
set(CMAKE_CXX_EXTENSIONS OFF)			        #

if(NOT CMAKE_BUILD_TYPE)            		# Сборка релизной версии, если не указано другого
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()
#===============================================#





#= Поиск требуемых библиотек ===================#
find_package(OpenCV REQUIRED)		            # поиск OpenCV

find_package(PkgConfig REQUIRED)		    # поиск libusb-1.0
pkg_check_modules(LibUSB REQUIRED libusb-1.0)	# 
#===============================================#



#= Подключение исходных файлов =================#
set(SOURCES
    src/main.cpp
    src/IR_manager.cpp
    src/FileReader.cpp
)
add_executable(${PROJECT_NAME} ${SOURCES})
#===============================================#



#= Указание директорий с заголовочными файлами проекта =#
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}		                # собственные заголовочные файлы
    ${LibUSB_INCLUDE_DIRS}				# Подключение libusb
)
#=======================================================#

#= Линковка библиотек к проекту =======#
target_link_libraries(${PROJECT_NAME}   
    ${OpenCV_LIBS}
    ${LibUSB_LIBRARIES}
)
#======================================#
