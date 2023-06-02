function(display_system_informations)
    set(os_name)
    set(os_release)
    set(os_version)
    set(os_platform)
    set(available_ram)
    set(total_ram)
    set(cpu_name)
    set(cpu_description)
    set(physical_cores_nb)
    set(logical_cores_nb)
    set(is_64_bits)

    cmake_host_system_information(RESULT os_name QUERY OS_NAME)
    cmake_host_system_information(RESULT os_release QUERY OS_RELEASE)
    cmake_host_system_information(RESULT os_version QUERY OS_VERSION)
    cmake_host_system_information(RESULT os_platform QUERY OS_PLATFORM)
    cmake_host_system_information(RESULT available_ram QUERY AVAILABLE_PHYSICAL_MEMORY)
    cmake_host_system_information(RESULT total_ram QUERY TOTAL_PHYSICAL_MEMORY)
    cmake_host_system_information(RESULT cpu_name QUERY PROCESSOR_NAME)
    cmake_host_system_information(RESULT cpu_description QUERY PROCESSOR_DESCRIPTION)
    cmake_host_system_information(RESULT physical_cores_nb QUERY NUMBER_OF_PHYSICAL_CORES)
    cmake_host_system_information(RESULT logical_cores_nb QUERY NUMBER_OF_LOGICAL_CORES)
    cmake_host_system_information(RESULT is_64_bits QUERY IS_64BIT)

    message(STATUS "")
    message(NOTICE "---------- SYSTEM CONFIGURATION ----------")
    message(STATUS "> Running on ------- ${os_name}")
    message(STATUS "> OS release ------- ${os_release}")
    message(STATUS "> OS version ------- ${os_version}")
    message(STATUS "> OS platform ------ ${os_platform}")
    message(STATUS "> Available RAM ---- ${available_ram} Mb")
    message(STATUS "> Total RAM -------- ${total_ram} Mb")
    if(is_64_bits)
        message(STATUS "> Using 64 bits architecture")
    else()
        message(STATUS "> Using 32 bits architecture")
    endif()
    message(STATUS "> CPU infos -------- ${cpu_description}")
    message(STATUS "> Physical cores --- ${physical_cores_nb}")
    message(STATUS "> Logical cores ---- ${logical_cores_nb}")
    message(NOTICE "------------------------------------------")
    message(STATUS "")
endfunction()