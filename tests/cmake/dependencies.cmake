cmake_minimum_required(VERSION 3.10)

find_package(Boost 1.74.0 COMPONENTS filesystem)

include(ExternalProject)

set(source_dir "${CMAKE_CURRENT_BINARY_DIR}/googletest-src")
set(build_dir "${CMAKE_CURRENT_BINARY_DIR}/googletest-build")
set(install_dir "${CMAKE_CURRENT_BINARY_DIR}")

EXTERNALPROJECT_ADD(
  googletest
  GIT_REPOSITORY    https://github.com/google/googletest.git
  GIT_TAG           v1.14.0
  PREFIX            ${install_dir}
  SOURCE_DIR        ${source_dir}
  BINARY_DIR        ${build_dir}
  CMAKE_ARGS        -D BUILD_SHARED_LIBS=ON
  INSTALL_COMMAND   ""
  UPDATE_COMMAND    ""
)

include_directories(${source_dir}/googletest/include)
include_directories(${source_dir}/googlemock/include)
link_directories(${build_dir}/lib)

IF(NOT Boost_FOUND)

include(ExternalProject)
set(source_dir "${CMAKE_BINARY_DIR}/libboost-src")
set(build_dir "${CMAKE_BINARY_DIR}/libboost-build")

EXTERNALPROJECT_ADD(
  libboost
  URL               "https://archives.boost.io/release/1.74.0/source/boost_1_74_0.tar.gz"
  PATCH_COMMAND     ""
  PREFIX            libboost-workspace
  SOURCE_DIR        ${source_dir}
  BINARY_DIR        ${build_dir}
  CONFIGURE_COMMAND cd ${source_dir} && ./bootstrap.sh --prefix=${build_dir} 
    --with-libraries=filesystem --without-icu
  BUILD_COMMAND     cd ${source_dir} && ./b2 install -j8 --disable-icu 
    --ignore-site-config "cxxflags=-fPIC" threading=multi link=shared
  UPDATE_COMMAND    ""
  INSTALL_COMMAND   "" 
  TEST_COMMAND      ""
)

include_directories(${build_dir}/include)
link_directories(${build_dir}/lib)

ENDIF()
