# check what platform we're on 64-bit, and create a simpler test than CMAKE_SIZEOF_VOID_P
if(CMAKE_SIZEOF_VOID_P MATCHES 8)
    set(PLATFORM 64)
    message(STATUS "Detected 64-bit platform - ok")
else()
	set(PLATFORM 32)
	message(FATAL_ERROR "FirelandsCore doesn't support x86, please use x64 architecture.")
endif()

if(WIN32)
  include("${CMAKE_SOURCE_DIR}/cmake/platform/win/settings.cmake")
elseif(UNIX)
  include("${CMAKE_SOURCE_DIR}/cmake/platform/unix/settings.cmake")
endif()
