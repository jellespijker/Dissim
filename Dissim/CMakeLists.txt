cmake_minimum_required(VERSION 3.6)
project(Dissim_lib)

set(CMAKE_CXX_STANDARD 14)

set (PROJECT_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set (PROJECT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

set(EIGEN3_INCLUDE_DIR /usr/include/eigen3 )
include_directories ( ${EIGEN3_INCLUDE_DIR} )

set(DISSIM_LIB_SRC 	 ${PROJECT_INCLUDE_DIR}/dissim.h
        ${PROJECT_INCLUDE_DIR}/Core/Core.h
        ${PROJECT_INCLUDE_DIR}/Core/Simulation.h
        ${PROJECT_INCLUDE_DIR}/Core/Block.h
        ${PROJECT_INCLUDE_DIR}/Core/BasicOperationBlock.h
        ${PROJECT_INCLUDE_DIR}/Core/DissimType.h
        ${PROJECT_INCLUDE_DIR}/Core/Integrator.h
        ${PROJECT_INCLUDE_DIR}/Core/Saturation.h
        ${PROJECT_INCLUDE_DIR}/Core/Chronos.h
        ${PROJECT_INCLUDE_DIR}/Core/SystemBlock.h
        ${PROJECT_INCLUDE_DIR}/Core/AlgabraicLoop.h
        ${PROJECT_INCLUDE_DIR}/Core/Abs.h
        ${PROJECT_INCLUDE_DIR}/Core/Hyberbolic.h
        ${PROJECT_INCLUDE_DIR}/Core/Solver.h

        ${PROJECT_INCLUDE_DIR}/Math/Math.h
        ${PROJECT_INCLUDE_DIR}/Math/Common.h

        ${PROJECT_INCLUDE_DIR}/Components/Components.h
        ${PROJECT_INCLUDE_DIR}/Components/Motor/ElectroMotor.h
        ${PROJECT_INCLUDE_DIR}/Components/Motor/HydraulicMotor.h
        ${PROJECT_INCLUDE_DIR}/Components/Pump/HydraulicPump.h
        ${PROJECT_INCLUDE_DIR}/Components/Math/K_HP.h
        ${PROJECT_INCLUDE_DIR}/Components/Math/tau_friction.h

        ${PROJECT_INCLUDE_DIR}/FirstPrinciple/FirstPrinciple.h
        ${PROJECT_INCLUDE_DIR}/FirstPrinciple/DeltaTorque2omega.h

        ${PROJECT_SOURCE_DIR}/Core/Simulation.cpp
        ${PROJECT_SOURCE_DIR}/Core/Block.cpp
        ${PROJECT_SOURCE_DIR}/Core/BasicOperationBlock.cpp
        ${PROJECT_SOURCE_DIR}/Core/DissimType.cpp
        ${PROJECT_SOURCE_DIR}/Core/Integrator.cpp
        ${PROJECT_SOURCE_DIR}/Core/Saturation.cpp
        ${PROJECT_SOURCE_DIR}/Core/Chronos.cpp
        ${PROJECT_SOURCE_DIR}/Core/SystemBlock.cpp
        ${PROJECT_SOURCE_DIR}/Core/AlgabraicLoop.cpp
        ${PROJECT_SOURCE_DIR}/Core/Abs.cpp
        ${PROJECT_SOURCE_DIR}/Core/Hyberbolic.cpp
        ${PROJECT_SOURCE_DIR}/Core/Solver.cpp

        ${PROJECT_SOURCE_DIR}/Math/Common.cpp

        ${PROJECT_SOURCE_DIR}/Components/Motor/ElectroMotor.cpp
        ${PROJECT_SOURCE_DIR}/Components/Motor/HydraulicMotor.cpp
        ${PROJECT_SOURCE_DIR}/Components/Pump/HydraulicPump.cpp
        ${PROJECT_SOURCE_DIR}/Components/Math/K_HP.cpp
        ${PROJECT_SOURCE_DIR}/Components/Math/tau_friction.cpp

        ${PROJECT_SOURCE_DIR}/FirstPrinciple/DeltaTorque2omega.cpp
        )

include_directories("${PROJECT_BINARY_DIR}")
include_directories("${PROJECT_INCLUDE_DIR}")

add_library(dissim SHARED ${DISSIM_LIB_SRC})
