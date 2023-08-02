
#
# FC_SUBDIRLIST
#
FUNCTION(FC_SUBDIRLIST result curdir recursive includeRoot)
  # glob recurse seem's doesn't work
  FILE(GLOB children RELATIVE ${curdir} "${curdir}/[^\\.]*")
  if (${includeRoot})
    SET(dirlist "${curdir}")
  else()
    SET(dirlist "")
  endif()

  FOREACH(child ${children})
    IF(IS_DIRECTORY "${curdir}/${child}")
        if (${recursive})
          FC_SUBDIRLIST(sub_Dirs "${curdir}/${child}" TRUE FALSE)
          SET(dirlist "${curdir}/${child}" ${sub_Dirs} ${dirlist})
        else()
          SET(dirlist "${curdir}/${child}" ${dirlist})
        endif()
    ENDIF()
  ENDFOREACH()
  SET(${result} ${dirlist} PARENT_SCOPE)
ENDFUNCTION(FC_SUBDIRLIST result curdir recursive)

#
# FC_SET_GLOBAL
#
MACRO(FC_SET_GLOBAL name val)
  set_property ( GLOBAL PROPERTY ${name} ${val})
  # after set , create the variable for current scope
  FC_GET_GLOBAL(${name})
ENDMACRO()

MACRO(FC_ADD_GLOBAL name val)
  FC_GET_GLOBAL(${name})

  set_property ( GLOBAL PROPERTY ${name}
      ${${name}}
      ${val}
  )
  # after set , create the variable for current scope
  FC_GET_GLOBAL(${name})
ENDMACRO()

#
# FC_GET_GLOBAL
#
MACRO(FC_GET_GLOBAL name)
  get_property(${name} GLOBAL PROPERTY ${name})
ENDMACRO()

#
# FC_SET_CACHE
#
MACRO(FC_SET_CACHE name val)
  set(${name} ${val} CACHE INTERNAL "FC Var")
ENDMACRO()

#
# FC_LIST_ADD_CACHE
#
MACRO(FC_LIST_ADD_CACHE name val)

    # avoid duplicates
    if (";${${name}};" MATCHES ";${val};")
      # nothing to do for now
    else()
        set(${name} ${val} ${${name}} CACHE INTERNAL "FC Var")
    endif()
ENDMACRO()


#
# FC_SET_PATH
#
MACRO(FC_SET_PATH name val)
  FC_SET_CACHE(${name} ${val})

  FC_ADD_INC_PATH(${val})
ENDMACRO()

#
# FC_ADD_INC_PATH
#
MACRO(FC_ADD_INC_PATH val)

    if (";${FC_INC_PATHS};" MATCHES ";${val};")
      # nothing to do for now
    else()
        set(FC_INC_PATHS
            ${FC_INC_PATHS}
            ${val}
        )

        #update cache
        FC_SET_CACHE("FC_INC_PATHS" "${FC_INC_PATHS}")
        include_directories(${val})
    endif()
ENDMACRO()


#
# FC_LOAD_INC_PATHS
#
MACRO(FC_LOAD_INC_PATHS)
  include_directories(${FC_INC_PATHS})
ENDMACRO()

#
# FC_SET_PARENT
#
MACRO(FC_SET_PARENT name val)
  set(${name} ${val} PARENT_SCOPE)
ENDMACRO()


MACRO(FC_ADD_HOOK hook_name value)
  FC_ADD_GLOBAL(${hook_name} "${value}")
ENDMACRO()

MACRO(FC_RUN_HOOK hook_name)
  FC_GET_GLOBAL(${hook_name})
  message(STATUS "Running cmake hook: ${hook_name}")
  if (${hook_name})
      set(HOOK_ARRAY ${${hook_name}})
      FOREACH (hook_file ${HOOK_ARRAY})
          message("Including ${hook_file}")
          include("${hook_file}")
      ENDFOREACH()
  else()
      message(STATUS "No hooks registered for ${hook_name}")
  endif()
ENDMACRO()