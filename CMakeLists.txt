cmake_minimum_required(VERSION 2.6)

INCLUDE(${CMAKE_SOURCE_DIR}/IJMacros.txt)

#Change PROJECT_NAME to the name of your project
PROJECT(itkConnectedRegionEdgeThresholdImageFilter)

#The following lines are required to use Dart
ENABLE_TESTING()
INCLUDE(Dart)


#Declare any external dependencies that your project may have here.
#examples include: ITK, VTK, JPEG, PNG, OpenGL, ZLIB, Perl, Java
#If you're not sure what name to use, look in the Modules directory of your
#cmake install and check that a file named Find(Package).cmake exists
#
# The packages can be specified with a version number, for example:
#
# ITK 2.8.1
# ITK 3.2.0
#
# If no version is specified, the most recent release of the package
# will be used.
SET(Required_Packages
ITK
)

#this foreach loads all of the packages that you specified as required.
#It shouldn't need to be modified.
FOREACH(Package ${Required_Packages})
  LOADPACKAGE(${Package})
ENDFOREACH(Package)

#Set any libraries that your project depends on.
#examples: ITKCommon, VTKRendering, etc
SET(Libraries
ITKCommon
ITKIO
)

SET(CurrentExe "ImageCompare")
ADD_EXECUTABLE(${CurrentExe} ImageCompare.cxx) 
TARGET_LINK_LIBRARIES(${CurrentExe} ${Libraries})

#1D Executable
SET(itkConnectedRegionEdgeThresholdImageFilter_Test1D)
ADD_EXECUTABLE(itkConnectedRegionEdgeThresholdImageFilter_Test1D itkConnectedRegionEdgeThresholdImageFilter_Test1D.cxx) 
TARGET_LINK_LIBRARIES(itkConnectedRegionEdgeThresholdImageFilter_Test1D ${Libraries})

#1D Test
ADD_TEST(itkConnectedRegionEdgeThresholdImageFilter_Test1D itkConnectedRegionEdgeThresholdImageFilter_Test1D ${CMAKE_SOURCE_DIR}/original_1D.png 120 5 5 ${CMAKE_SOURCE_DIR}/output_1D.png)
ADD_TEST(CompareImage1D ImageCompare ${CMAKE_SOURCE_DIR}/correct_1D.png ${CMAKE_SOURCE_DIR}/output_1D.png)


#2D Executable
SET(itkConnectedRegionEdgeThresholdImageFilter_Test2D)
ADD_EXECUTABLE(itkConnectedRegionEdgeThresholdImageFilter_Test2D itkConnectedRegionEdgeThresholdImageFilter_Test2D.cxx) 
TARGET_LINK_LIBRARIES(itkConnectedRegionEdgeThresholdImageFilter_Test2D ${Libraries})

#2D Test
ADD_TEST(itkConnectedRegionEdgeThresholdImageFilter_Test2D itkConnectedRegionEdgeThresholdImageFilter_Test2D ${CMAKE_SOURCE_DIR}/original_2D.png 135 95 5 5 ${CMAKE_SOURCE_DIR}/output_2D.png)
ADD_TEST(CompareImage2D ImageCompare ${CMAKE_SOURCE_DIR}/correct_2D.png ${CMAKE_SOURCE_DIR}/output_2D.png)
