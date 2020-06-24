file(REMOVE_RECURSE
  "httpserver.pdb"
  "httpserver"
)

# Per-language clean rules from dependency scanning.
foreach(lang )
  include(CMakeFiles/httpserver.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
