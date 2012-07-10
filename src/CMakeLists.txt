rock_library(alt_imagenex
    SOURCES Driver.cpp AltHandler.cpp
    HEADERS Driver.hpp AltHandler.hpp AltTypes.hpp AltRaw.hpp
    DEPS_PKGCONFIG base-types iodrivers_base base-lib)

rock_executable(alt_imagenex_bin Main.cpp
    DEPS alt_imagenex)

