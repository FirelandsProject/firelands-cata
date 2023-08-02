#
# Use it like:
# CopyModuleConfig("myModule.conf.dist")
#

function(CopyModuleConfig configDir)
  set(postPath "configs/mods")

  if(WIN32)
    if("${CMAKE_MAKE_PROGRAM}" MATCHES "MSBuild")
      add_custom_command(TARGET mods
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_BINARY_DIR}/bin/$(ConfigurationName)/${postPath}")
      add_custom_command(TARGET mods
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy "${configDir}" "${CMAKE_BINARY_DIR}/bin/$(ConfigurationName)/${postPath}")
    elseif(MINGW)
      add_custom_command(TARGET mods
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_BINARY_DIR}/bin/${postPath}")
      add_custom_command(TARGET mods
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy "${configDir} ${CMAKE_BINARY_DIR}/bin/${postPath}")
    endif()
  endif()

  if(UNIX)
    install(FILES "${configDir}" DESTINATION "${CONF_DIR}/mods")
  elseif(WIN32)
    install(FILES "${configDir}" DESTINATION "${CMAKE_INSTALL_PREFIX}/${postPath}")
  endif()
  unset(postPath)
endfunction()