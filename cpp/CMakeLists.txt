# Sets the minimum version of CMake required to build your native library.
# This ensures that a certain set of CMake features is available to
# your build.

cmake_minimum_required(VERSION 3.4.1)

# Specifies a library name, specifies whether the library is STATIC or
# SHARED, and provides relative paths to the source code. You can
# define multiple libraries by adding multiple add_library() commands,
# and CMake builds them for you. When you build your app, Gradle
# automatically packages shared libraries with your APK.

add_library( # Specifies the name of the library.
             native-main

             # Sets the library as a shared library.
             SHARED

             # Provides a relative path to your source file(s).
             CG.cpp
             CG_ref.cpp
             CheckAspectRatio.cpp
             CheckProblem.cpp
             ComputeDotProduct.cpp
             ComputeDotProduct_ref.cpp
             ComputeMG.cpp
             ComputeMG_ref.cpp
             ComputeOptimalShapeXYZ.cpp
             ComputeProlongation_ref.cpp
             ComputeResidual.cpp
             ComputeRestriction_ref.cpp
             ComputeSPMV.cpp
             ComputeSPMV_ref.cpp
             ComputeSYMGS_ref.cpp
             ComputeSYMGS.cpp
             ComputeWAXPBY.cpp
             ComputeWAXPBY_ref.cpp
             finalize.cpp
             GenerateCoarseProblem.cpp
             GenerateGeometry.cpp
             GenerateProblem.cpp
             GenerateProblem_ref.cpp
             init.cpp
             MixedBaseCounter.cpp
             mytimer.cpp
             OptimizeProblem.cpp
             OutputFile.cpp
             ReadHpcgDat.cpp
             ReportResults.cpp
             SetupHalo.cpp
             SetupHalo_ref.cpp
             TestCG.cpp
             TestNorms.cpp
             TestSymmetry.cpp
             WriteProblem.cpp
             Vector.hpp
             YAML_Doc.cpp
             YAML_Element.cpp
             native-main.cpp )

