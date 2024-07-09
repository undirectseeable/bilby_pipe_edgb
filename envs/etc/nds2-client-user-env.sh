#
#  nds2-client package setup script for lscsoft environment
#
prepend()
{
#  prepend - add new item to path if not already there
    newpath=$1
    oldpath=$2
    compath=$3
    if [ -z "$compath" ]; then
        export $oldpath=$newpath
    else
        echo $compath | egrep -i $newpath >&/dev/null
        if [ "$?" -ne 0 ]; then
            export $oldpath=$newpath:$compath
        fi
    fi
}

prepend "/scratch/nj2nu/non_GR/BBH_dataset/gw150914_xas/github_repo/bilby_pipe_edgb/envs/bin" "PATH" "$PATH"
prepend "/scratch/nj2nu/non_GR/BBH_dataset/gw150914_xas/github_repo/bilby_pipe_edgb/envs/lib/pkgconfig" "PKG_CONFIG_PATH" "$PKG_CONFIG_PATH"
prepend "/scratch/nj2nu/non_GR/BBH_dataset/gw150914_xas/github_repo/bilby_pipe_edgb/envs/lib/cmake/nds2-client" "CMAKE_MODULE_PATH" "$CMAKE_MODULE_PATH"
prepend "`nds-client-config --matlabdir`" "MATLABPATH" "$MATLABPATH"
case "`python --version 2>&1`" in
"Python 2."*)
  prepend "`nds-client-config --py27dir`" "PYTHONPATH" "$PYTHONPATH"
  prepend "`nds-client-config --py27execdir`" "PYTHONPATH" "$PYTHONPATH"
  ;;
"Python 3.4"*)
  prepend "`nds-client-config --py34dir`" "PYTHONPATH" "$PYTHONPATH"
  prepend "`nds-client-config --py34execdir`" "PYTHONPATH" "$PYTHONPATH"
  ;;
"Python 3.5"*)
  prepend "`nds-client-config --py35dir`" "PYTHONPATH" "$PYTHONPATH"
  prepend "`nds-client-config --py35execdir`" "PYTHONPATH" "$PYTHONPATH"
  ;;
"Python 3.6"*)
  prepend "`nds-client-config --py36dir`" "PYTHONPATH" "$PYTHONPATH"
  prepend "`nds-client-config --py36execdir`" "PYTHONPATH" "$PYTHONPATH"
  ;;
esac
