message(STATUS "> Found sources/utils directory")

set(target_name utils)

add_library(${target_name} STATIC "")

target_sources(${target_name}
    PRIVATE
        "${PROJECT_SOURCE_DIR}/src/utils/path.cpp"
        "${PROJECT_SOURCE_DIR}/src/utils/printer.cpp"
        "${PROJECT_SOURCE_DIR}/src/utils/strings.cpp"

    PRIVATE
        "${PROJECT_SOURCE_DIR}/include/utils/path.h"
        "${PROJECT_SOURCE_DIR}/include/utils/printer.h"
        "${PROJECT_SOURCE_DIR}/include/utils/strings.h"

)

target_include_directories (${target_name}
    PUBLIC
        "${PROJECT_SOURCE_DIR}/include/utils"
        "${PROJECT_BINARY_DIR}"
)


set_property(TARGET ${target_name} PROPERTY FOLDER "Sources/Utils")
