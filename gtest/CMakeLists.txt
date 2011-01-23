INCLUDE_DIRECTORIES(${datetimelite_SOURCE_DIR}/gtest/include)
ADD_LIBRARY(gtest STATIC src/gtest-all.cc)
ADD_LIBRARY(gtest-main STATIC src/gtest_main.cc)
