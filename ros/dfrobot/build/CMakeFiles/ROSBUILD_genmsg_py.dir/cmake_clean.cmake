FILE(REMOVE_RECURSE
  "../msg_gen"
  "../src/dfrobot/msg"
  "../msg_gen"
  "CMakeFiles/ROSBUILD_genmsg_py"
  "../src/dfrobot/msg/__init__.py"
  "../src/dfrobot/msg/_State.py"
)

# Per-language clean rules from dependency scanning.
FOREACH(lang)
  INCLUDE(CMakeFiles/ROSBUILD_genmsg_py.dir/cmake_clean_${lang}.cmake OPTIONAL)
ENDFOREACH(lang)
