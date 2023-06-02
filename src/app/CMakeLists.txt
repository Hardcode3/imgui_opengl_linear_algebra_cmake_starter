message(STATUS "> Found sources/app directory")

set(target_name app)

add_library(${target_name} STATIC "")

target_link_libraries(${target_name} PRIVATE glgraph externals fstreamlib utils)

target_sources(${target_name}
    PRIVATE
        "${PROJECT_SOURCE_DIR}/src/app/app_base.cpp"
        "${PROJECT_SOURCE_DIR}/src/app/app.cpp"
        "${PROJECT_SOURCE_DIR}/src/app/window_base.cpp"
        "${PROJECT_SOURCE_DIR}/src/app/imgui_utils/table_utils.cpp"
        "${PROJECT_SOURCE_DIR}/src/app/imgui_utils/ui_utils.cpp"
        "${PROJECT_SOURCE_DIR}/src/app/imgui_utils/notification.cpp"
        "${PROJECT_SOURCE_DIR}/src/app/node_system/node_editor.cpp"
        "${PROJECT_SOURCE_DIR}/src/app/node_system/nodes.cpp"
        "${PROJECT_SOURCE_DIR}/src/app/node_system/link.cpp"


    PRIVATE
        "${PROJECT_SOURCE_DIR}/include/app/app_base.h"
        "${PROJECT_SOURCE_DIR}/include/app/app.h"
        "${PROJECT_SOURCE_DIR}/include/app/window_base.h"
        "${PROJECT_SOURCE_DIR}/include/app/imgui_utils/table_utils.h"
        "${PROJECT_SOURCE_DIR}/include/app/imgui_utils/ui_utils.h"

        # notification system
        "${PROJECT_SOURCE_DIR}/include/app/imgui_utils/notification.h"

        # node editor
        "${PROJECT_SOURCE_DIR}/include/app/node_system/node_editor.h"
        "${PROJECT_SOURCE_DIR}/include/app/node_system/nodes.h"
        "${PROJECT_SOURCE_DIR}/include/app/node_system/link.h"

        # file browser
        "${PROJECT_SOURCE_DIR}/include/app/file_browser/imfilebrowser.h"
)

target_include_directories (${target_name}
    PUBLIC
        "${PROJECT_SOURCE_DIR}/include/app"
        "${PROJECT_SOURCE_DIR}/include/app/imgui_utils"
        "${PROJECT_SOURCE_DIR}/include/app/node_system"
        "${PROJECT_SOURCE_DIR}/include/app/file_browser"
        "${PROJECT_SOURCE_DIR}/include/glgraph"
        "${PROJECT_SOURCE_DIR}/include/fstreamlib"
        "${PROJECT_SOURCE_DIR}/include/utils"
        "${PROJECT_SOURCE_DIR}/assets"
        "${PROJECT_BINARY_DIR}"
)

set_property(TARGET ${target_name} PROPERTY FOLDER "Sources/ui")
