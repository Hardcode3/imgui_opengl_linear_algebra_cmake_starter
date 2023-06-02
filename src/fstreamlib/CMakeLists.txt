message(STATUS "> Found sources/fstreamlib directory")

set(target_name fstreamlib)

add_library(${target_name} STATIC "")

target_sources(${target_name}
    PRIVATE
        "${PROJECT_SOURCE_DIR}/src/fstreamlib/csv.cpp"
        "${PROJECT_SOURCE_DIR}/src/fstreamlib/text.cpp"
        "${PROJECT_SOURCE_DIR}/src/fstreamlib/segy.cpp"

    PRIVATE
        "${PROJECT_SOURCE_DIR}/include/fstreamlib/csv.h"
        "${PROJECT_SOURCE_DIR}/include/fstreamlib/text.h"
        "${PROJECT_SOURCE_DIR}/include/fstreamlib/segy.h"
)

target_include_directories (${target_name}
    PUBLIC
        "${PROJECT_SOURCE_DIR}/include/fstreamlib"
        "${PROJECT_BINARY_DIR}"
)


set_property(TARGET ${target_name} PROPERTY FOLDER "Sources/fstreamlib")
