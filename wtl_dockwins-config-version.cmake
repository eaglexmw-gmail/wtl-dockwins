set (PACKAGE_VERSION 0.9.3)

# Compatible only if the requested and the actual major version are equal
if (PACKAGE_FIND_VERSION_MAJOR EQUAL _VERSION_MAJOR)
  set (PACKAGE_VERSION_COMPATIBLE TRUE)
else (PACKAGE_FIND_VERSION_MAJOR EQUAL _VERSION_MAJOR)
  set (PACKAGE_VERSION_COMPATIBLE FALSE)
endif (PACKAGE_FIND_VERSION_MAJOR EQUAL _VERSION_MAJOR)

if (PACKAGE_FIND_VERSION_MAJOR EQUAL _VERSION_MAJOR AND
    PACKAGE_FIND_VERSION_MINOR EQUAL _VERSION_MINOR)
  set (PACKAGE_VERSION_EXACT TRUE)
else ()
  set (PACKAGE_VERSION_EXACT FALSE)
endif ()
