rock_library(alt_imagenex
    SOURCES Dummy.cpp
    HEADERS Dummy.hpp)

rock_executable(alt_imagenex_bin Main.cpp
    DEPS alt_imagenex)

