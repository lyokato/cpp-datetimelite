INCLUDE_DIRECTORIES(${datetimelite_SOURCE_DIR}/include)

#FILE(GLOB src_files ${datetimelite_SOURCE_DIR}/src/*)
#ADD_LIBRARY(datetimelite SHARED ${src_files})
#ADD_LIBRARY(datetimelite_static STATIC ${src_files})
# SET_TARGET_PROPERTIES(datetimelite_static PROPERTIES OUTPUT_NAME datetimelite)

FILE(GLOB header_files ${datetimelite_SOURCE_DIR}/include/*)
INSTALL(FILES ${header_files} DESTINATION include)
#INSTALL(TARGETS datetimelite DESTINATION lib)
