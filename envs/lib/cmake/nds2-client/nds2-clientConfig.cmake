# A FindPackage Configure package for nds2-client
# This defines typical variables for the c library in
# DAQC_CLIENT_*
# and for the C++ NDS client in
# NDS_CLIENT_*
#
# The following targets are exported
# nds::daqc
# nds::cxx
#
# To aid java/matlab module development the following variables are provided
# which reference a series of object files that have been built with a static
# C++ std library and are suitable for inclusion in a shared library.
#
# CONLIBNDSCXX_INCLUDE_DIRS
# CONLIBNDSCXX_LIBRARY_DIRS

set( NDS_CLIENT_VERSION 0.16.8 )


####### Expanded from @PACKAGE_INIT@ by configure_package_config_file() #######
####### Any changes to this file will be overwritten by the next CMake run ####
####### The input file was nds2-clientConfig.cmake.in                            ########

get_filename_component(PACKAGE_PREFIX_DIR "${CMAKE_CURRENT_LIST_DIR}/../" ABSOLUTE)

macro(set_and_check _var _file)
  set(${_var} "${_file}")
  if(NOT EXISTS "${_file}")
    message(FATAL_ERROR "File or directory ${_file} referenced by variable ${_var} does not exist !")
  endif()
endmacro()

macro(check_required_components _NAME)
  foreach(comp ${${_NAME}_FIND_COMPONENTS})
    if(NOT ${_NAME}_${comp}_FOUND)
      if(${_NAME}_FIND_REQUIRED_${comp})
        set(${_NAME}_FOUND FALSE)
      endif()
    endif()
  endforeach()
endmacro()

####################################################################################

#========================================================================
# The package init assumes that everything is one level below the install
# prefix.  This is not always the case.
#------------------------------------------------------------------------
get_filename_component(PACKAGE_PREFIX_DIR "${CMAKE_CURRENT_LIST_DIR}/../../../" ABSOLUTE)
#========================================================================
# Extract information from a .pc file without using pkg-config
#------------------------------------------------------------------------
function( pkg_config_lite VAR_PREFIX PACKAGE )
  set( ${VAR_PREFIX}_FOUND False )
  set_and_check( this_pkg_config_path "${PACKAGE_PREFIX_DIR}/lib/pkgconfig" )
  set( pkg_config_path $ENV{PKG_CONFIG_PATH} )
  list( INSERT pkg_config_path 0 ${this_pkg_config_path} )
  message( STATUS "DEBUG: pkg_config_path: ${pkg_config_path}" )
  foreach( dir ${pkg_config_path} )
    file( TO_CMAKE_PATH "${dir}/${PACKAGE}.pc" pkg )
    if ( EXISTS ${pkg} )
      message( STATUS "DEBUG: found ${pkg}" )
      set( ${VAR_PREFIX}_FOUND True )
      file( READ ${pkg} pkg_info )
      string( REGEX REPLACE ";" "\\\\;" pkg_info ${pkg_info} )
      string( REGEX REPLACE "\n" ";" pkg_info ${pkg_info} )
      foreach( line ${pkg_info} )
	if ( line MATCHES "^Libs:" )
	  #--------------------------------------------------------------
	  # Libraries
	  #--------------------------------------------------------------
	  string( REGEX REPLACE "^Libs:" "" line ${line} )
	  string( STRIP line ${line} )
	  string( REGEX REPLACE " " ";" line ${line} )
	  string( CONFIGURE "${line}" line ESCAPE_QUOTES )
	  foreach( e ${line} )
	    list( APPEND ${VAR_PREFIX}_LDFLAGS ${e} )
	    if ( e MATCHES "^-L" )
	      string( REGEX REPLACE "^-L" "" d ${e} )
	      list( APPEND ${VAR_PREFIX}_LIBRARY_DIRS ${d} )
	      message( STATUS "DEBUG: ${VAR_PREFIX}_LIBRARY_DIRS: ${${VAR_PREFIX}_LIBRARY_DIRS}" )
	    elseif ( e MATCHES "^-l" )
	      string( REGEX REPLACE "^-l" "" l ${e} )
	      list( APPEND ${VAR_PREFIX}_LIBRARIES ${l} )
	      message( STATUS "DEBUG: ${VAR_PREFIX}_LIBRARIES: ${${VAR_PREFIX}_LIBRARIES}" )
	    else( )
	      list( APPEND ${VAR_PREFIX}_LDFLAGS_OTHER ${e} )
	    endif( )
	  endforeach( )
	elseif ( line MATCHES "^Cflags:" )
	  #--------------------------------------------------------------
	  # C Flags
	  #--------------------------------------------------------------
	  string( REGEX REPLACE "^Cflags:" "" line ${line} )
	  string( STRIP line ${line} )
	  string( REGEX REPLACE " " ";" line ${line} )
	  string( CONFIGURE "${line}" line ESCAPE_QUOTES )
	  foreach( e ${line} )
	    list( APPEND ${VAR_PREFIX}_CFLAGS ${e} )
	    if ( e MATCHES "^-I" )
	      string( REGEX REPLACE "^-I" "" d ${e} )
	      list( APPEND ${VAR_PREFIX}_INCLUDE_DIRS ${d} )
	      message( STATUS "DEBUG: ${VAR_PREFIX}_INCLUDE_DIRS: ${${VAR_PREFIX}_INCLUDE_DIRS}" )
	    else( )
	      list( APPEND ${VAR_PREFIX}_CFLAGS_OTHER ${e} )
	    endif( )
	  endforeach( )
	elseif ( line MATCHES ".*=.*" )
    	  #--------------------------------------------------------------
    	  # Internal variables
    	  #--------------------------------------------------------------
    	  string( REGEX REPLACE "=" ";" line ${line} )
    	  list( GET line 0 var )
    	  list( GET line 1 value )
    	  string( REGEX REPLACE
    	    "^.*include"
    	    "${PACKAGE_PREFIX_DIR}/include"
    	    value ${value} )
    	  string( REGEX REPLACE
    	    "^.*lib"
    	    "${PACKAGE_PREFIX_DIR}/lib"
    	    value ${value} )
    	  set( ${var} ${value} )
	endif( )
      endforeach( )
      foreach(lib ${${VAR_PREFIX}_LIBRARIES})
	find_library(__JUNK__ NAMES ${lib}
	  HINTS ${${VAR_PREFIX}_LIBRARY_DIRS} )
	if ( __JUNK__)
	  list(APPEND ${VAR_PREFIX}_LIBRARIES_FULL_PATH ${__JUNK__})
	endif ( __JUNK__)
	unset(__JUNK__ CACHE)
      endforeach(lib)
      break()
    endif ( )
  endforeach( )
  set( ${VAR_PREFIX}_FOUND ${${VAR_PREFIX}_FOUND} CACHE INTERNAL "" )
  set( ${VAR_PREFIX}_LIBRARIES ${${VAR_PREFIX}_LIBRARIES} CACHE INTERNAL "" )
  set( ${VAR_PREFIX}_LIBRARIES_FULL_PATH ${${VAR_PREFIX}_LIBRARIES_FULL_PATH} CACHE INTERNAL "" )
  set( ${VAR_PREFIX}_LIBRARY_DIRS ${${VAR_PREFIX}_LIBRARY_DIRS} CACHE INTERNAL "" )
  set( ${VAR_PREFIX}_LDFLAGS ${${VAR_PREFIX}_LDFLAGS} CACHE INTERNAL "" )
  set( ${VAR_PREFIX}_LDFLAGS_OTHER ${${VAR_PREFIX}_LDFLAGS_OTHER} CACHE INTERNAL "" )
  set( ${VAR_PREFIX}_INCLUDE_DIRS ${${VAR_PREFIX}_INCLUDE_DIRS} CACHE INTERNAL "" )
  set( ${VAR_PREFIX}_CFLAGS ${${VAR_PREFIX}_CFLAGS} CACHE INTERNAL "" )
  set( ${VAR_PREFIX}_CFLAGS_OTHER ${${VAR_PREFIX}_CFLAGS_OTHER} CACHE INTERNAL "" )
endfunction()


if (NOT nds_check_cpp11_included)
    set(nds_check_cpp11_included TRUE)

    # To make this easy, we want cmake 3.1+
    # it is simple if that is present, else we need to autodetect flags
    if (${CMAKE_VERSION} VERSION_GREATER "3.0.99")

        macro(target_requires_cpp11 target mode)
            target_compile_features(${target} ${mode} cxx_auto_type)
        endmacro()

    else (${CMAKE_VERSION} VERSION_GREATER "3.0.99")

        if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
            MESSAGE(FATAL "When building with MSVC please use a newer CMAKE (3.1+) to allow C++11 support to be specified")
        endif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")

        INCLUDE(CheckCXXCompilerFlag)

        CHECK_CXX_COMPILER_FLAG(-std=c++0x HAS_CXX_0X)
        CHECK_CXX_COMPILER_FLAG(-std=c++11 HAS_CXX_11)

        if (${HAS_CXX_11})
            set(CPPSTD_FLAG "-std=c++11")
        else (${HAS_CXX_11})
            if (${HAS_CXX_0X})
                set(CPPSTD_FLAG "-std=c++0x")
            else (${HAS_CXX_0X})
                set(CPPSTD_FLAG "")
            endif (${HAS_CXX_0X})
        endif (${HAS_CXX_11})

        macro(target_requires_cpp11 target mode)
            target_compile_options(${target} ${mode} ${CPPSTD_FLAG})
        endmacro()

    endif (${CMAKE_VERSION} VERSION_GREATER "3.0.99")
endif()

set (_daqc_lib_list "")
set (_nds_lib_list "")

# This function takes a external library name
# looks it up in the NDS_CLIENT library paths
# creates a IMPORTED library target and adds
# the target to the _${lib_list_prefix}_lib_list variable
function(_nds_add_library libname lib_list_prefix)
    # check for duplicates
    if (NOT TARGET "${libname}")
        # find library MUST have a unique variable name
        # as it gets cached, hence the recursive name
        find_library(${libname}_LIBRARY_PATH name ${libname}
            PATHS ${NDS_CLIENT_LIBRARY_DIRS}
                /lib /usr/lib
                /lib64 /usr/lib64
                /usr/lib/x86_64-linux-gnu
                /usr/local/lib /usr/local/lib64
            NO_DEFAULT_PATH)
        add_library(${libname} SHARED IMPORTED)
        set_target_properties(${libname} PROPERTIES
            IMPORTED_LOCATION ${${libname}_LIBRARY_PATH})
        set (_${lib_list_prefix}_lib_list ${_${lib_list_prefix}_lib_list} ${libname} PARENT_SCOPE)
        # message("target ${libname} found at ${${libname}_LIBRARY_PATH}")
        set(_local_dup_list "${_nds_add_lib_dup_list}")
        list(APPEND _local_dup_list "${libname}")
    endif()
endfunction()

pkg_config_lite( DAQC_CLIENT nds2-client )
pkg_config_lite( NDS_CLIENT libndscxx )

# convert the pkg-config library list to cmake library targets
foreach (_daqc_lib ${DAQC_CLIENT_LIBRARIES})
    _nds_add_library(${_daqc_lib} "daqc")
endforeach()
foreach (_nds_lib ${NDS_CLIENT_LIBRARIES})
    _nds_add_library(${_nds_lib} "nds")
endforeach()

add_library(_daqc_client_intl INTERFACE)
target_include_directories(_daqc_client_intl INTERFACE ${DAQC_CLIENT_INCLUDE_DIRS})
target_compile_options(_daqc_client_intl INTERFACE ${DAQC_CLIENT_CFLAGS_OTHER})
target_link_libraries(_daqc_client_intl INTERFACE ${_daqc_lib_list})
add_library(nds::daqc ALIAS _daqc_client_intl)

add_library(_ndscxx_intl INTERFACE)
target_include_directories(_ndscxx_intl INTERFACE ${NDS_CLIENT_INCLUDE_DIRS})
target_compile_options(_ndscxx_intl INTERFACE ${NDS_CLIENT_CFLAGS_OTHER})
target_link_libraries(_ndscxx_intl INTERFACE ${_nds_lib_list})
target_requires_cpp11(_ndscxx_intl INTERFACE)
add_library(nds::cxx ALIAS _ndscxx_intl)

set_and_check( CONLIBNDSCXX_LIBRARY_DIRS "${PACKAGE_PREFIX_DIR}/lib/nds2-client/ndswrapcxx" )
set_and_check( CONLIBNDSCXX_INCLUDE_DIRS "${PACKAGE_PREFIX_DIR}/include/nds2-client" )
