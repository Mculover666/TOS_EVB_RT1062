if(NOT COMPONENT_LOG_MIMXRT1062_INCLUDED)
    
    set(COMPONENT_LOG_MIMXRT1062_INCLUDED true CACHE BOOL "component_log component is included.")

    target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/fsl_component_log.c
    )


    target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/.
    )


    include(driver_common_MIMXRT1062)

    include(utility_debug_console_MIMXRT1062)

endif()
