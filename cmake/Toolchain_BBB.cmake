# load with -DCMAKE_TOOLCHAIN_FILE=./cmake/Toolchain_BBB.cmake
set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR arm)
set(CMAKE_CROSSCOMPILING 1)
set(CMAKE_C_COMPILER                    arm-linux-gnueabihf-gcc)
set(CMAKE_CXX_COMPILER                  arm-linux-gnueabihf-g++)
set(CXX_COMPILER_ID                     arm-linux-gnueabihf)
set(ARCH_CROSS_COMPILE                  ON)

# where is the target environment
SET(CMAKE_FIND_ROOT_PATH                "${dissim_main_SOURCE_DIR}/build/arch_rootfs")
SET(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM   NEVER)
SET(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY   ONLY)
SET(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE   ONLY)
