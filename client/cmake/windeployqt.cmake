# windeployqt.cmake

function(windeployqt target)
    if(WIN32 AND Qt6_FOUND)
        set(_qt_bin_dir "${Qt6_DIR}/../../../bin")

        add_custom_command(TARGET ${target} POST_BUILD
            COMMAND "${_qt_bin_dir}/windeployqt.exe"
                    --verbose 1          
                    --no-svg                    
                    --no-opengl         
                    --no-opengl-sw       
                    --no-compiler-runtime 
                    --no-system-d3d-compiler 
                    --no-translations    
                    \"$<TARGET_FILE:${target}>\"
            COMMENT "Deploying Qt libraries using windeployqt for compilation target '${target}' ..."
        )
    endif()
endfunction()
