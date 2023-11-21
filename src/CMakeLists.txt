# -*- explicit-buffer-name: "CMakeLists.txt<M1-MOBJ/7>" -*-
#
# To display executed commands, use:
#     > cmake -DCMAKE_VERBOSE_MAKEFILE:STRING=YES ../src

cmake_minimum_required(VERSION 2.8.0)
project(SCHEMATIC)

set (CMAKE_CXX_FLAGS            "-Wall -g" CACHE STRING "C++ Compiler Release options." FORCE)
set (CMAKE_INSTALL_PREFIX       "../install" )

# Detection de LibXml2.
find_package(LibXml2)
# Trouver les includes de LibXml2.
include_directories( ${SCHEMATIC_SOURCE_DIR} ${LIBXML2_INCLUDE_DIR} )

                   set( includes     Indentation.h
                                     Term.h
                                     Net.h
                                     Instance.h
                                     Point.h
                                     Node.h
                                     Cell.h
                                     XmlUtil.h
                                     Symbol.h
                                     Box.h
                                     Line.h 
                                     Shape.h
                      )

                   set( cpps         Indentation.cpp
                                     Term.cpp
                                     Net.cpp
                                     Instance.cpp
                                     Point.cpp
                                     Node.cpp
                                     Cell.cpp
                                     Main.cpp
                                     XmlUtil.cpp
                                     Symbol.cpp 
                                     Box.cpp 
                                     Line.cpp 
                                     Shape.cpp
                      )

      add_executable ( tme7 ${cpps} )
              install ( TARGETS      tme7        DESTINATION bin )
              install ( FILES        ${includes}  DESTINATION include )
              target_link_libraries ( tme7 ${LIBXML2_LIBRARIES} )
