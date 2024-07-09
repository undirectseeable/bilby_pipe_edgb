#
#  nds2-client package setup script for lscsoft environment.
#
echo ${PATH} | egrep -i "/scratch/nj2nu/non_GR/BBH_dataset/gw150914_xas/github_repo/bilby_pipe_edgb/envs/bin" >&/dev/null
if ($status != 0) then
    setenv PATH "/scratch/nj2nu/non_GR/BBH_dataset/gw150914_xas/github_repo/bilby_pipe_edgb/envs/bin:${PATH}"
endif
if ( $?PKG_CONFIG_PATH ) then
    echo ${PKG_CONFIG_PATH} | egrep -i "/scratch/nj2nu/non_GR/BBH_dataset/gw150914_xas/github_repo/bilby_pipe_edgb/envs/lib/pkgconfig" >&/dev/null
    if ($status != 0) then
        setenv PKG_CONFIG_PATH "/scratch/nj2nu/non_GR/BBH_dataset/gw150914_xas/github_repo/bilby_pipe_edgb/envs/lib/pkgconfig:${PKG_CONFIG_PATH}"
    endif
else
        setenv PKG_CONFIG_PATH "/scratch/nj2nu/non_GR/BBH_dataset/gw150914_xas/github_repo/bilby_pipe_edgb/envs/lib/pkgconfig"
endif
if ( $?CMAKE_MODULE_PATH ) then
    echo ${CMAKE_MODULE_PATH} | egrep -i "/scratch/nj2nu/non_GR/BBH_dataset/gw150914_xas/github_repo/bilby_pipe_edgb/envs/lib/cmake/nds2-client" >&/dev/null
    if ($status != 0) then
        setenv CMAKE_MODULE_PATH "/scratch/nj2nu/non_GR/BBH_dataset/gw150914_xas/github_repo/bilby_pipe_edgb/envs/lib/cmake/nds2-client:${CMAKE_MODULE_PATH}"
    endif
else
        setenv CMAKE_MODULE_PATH "/scratch/nj2nu/non_GR/BBH_dataset/gw150914_xas/github_repo/bilby_pipe_edgb/envs/lib/cmake/nds2-client"
endif

set matlabdir = `nds-client-config --matlabdir`
if ( $?MATLABPATH ) then
    echo ${MATLABPATH} | egrep -i "${matlabdir}" >&/dev/null
    if ($status != 0) then
        setenv MATLABPATH "${matlabdir}:${MATLABPATH}"
    endif
else
        setenv MATLABPATH "${matlabdir}"
endif

set pyversion = `python --version |& cat`
switch( "${pyversion}" )
case "Python 2."*:
    set pydir = `nds-client-config --py27dir`
    set pyexecdir = `nds-client-config --py27execdir`
    breaksw
case "Python 3.4"*:
    set pydir = `nds-client-config --py34dir`
    set pyexecdir = `nds-client-config --py34execdir`
    breaksw
case "Python 3.5"*:
    set pydir = `nds-client-config --py35dir`
    set pyexecdir = `nds-client-config --py35execdir`
    breaksw
case "Python 3.6"*:
    set pydir = `nds-client-config --py36dir`
    set pyexecdir = `nds-client-config --py36execdir`
    breaksw
endsw
if ( $?PYTHONPATH ) then
    echo ${PYTHONPATH} | egrep -i "${pydir}" >&/dev/null
    if ($status != 0) then
        setenv PYTHONPATH "${pydir}:${PYTHONPATH}"
    endif
    echo ${PYTHONPATH} | egrep -i "${pyexecdir}" >&/dev/null
    if ($status != 0) then
        setenv PYTHONPATH "${pyexecdir}:${PYTHONPATH}"
    endif
else
        setenv PYTHONPATH "${pyexecdir}:${pydir}"
endif
