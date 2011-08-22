#include "itkImage.h"
#include "itkImageFileWriter.h"
#include "itkImageFileReader.h"

#include "itkConnectedRegionEdgeThresholdImageFilter.h"

#include "itkCastImageFilter.h"

#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>

int main( int argc, char *argv[])
{
	//required parameters:
	// ./itkConnectedRegionEdgeThresholdImageFilter_Test1D original.png SeedRow SeedCol Lower Upper output.png
	std::string strInputFilename = argv[1];
	std::string strSeedRow = argv[2];
	std::string strSeedCol = argv[3];
	std::string strLower = argv[4];
	std::string strUpper = argv[5];
	std::string strOutputFilename = argv[6];
	
	//Convert the seed to integers
	std::stringstream ssSeedRow(strSeedRow);
	unsigned int SeedRow;
	ssSeedRow >> SeedRow;
	
	std::stringstream ssSeedCol(strSeedCol);
	unsigned int SeedCol;
	ssSeedCol >> SeedCol;
	
	//convert lower and upper to floats
	std::stringstream ssLower(strLower);
	float Lower;
	ssLower >> Lower;
	
	std::stringstream ssUpper(strUpper);
	float Upper;
	ssUpper >> Upper;
	
	
	//read the input image
	typedef float     PixelType;
	const     unsigned int    Dimension = 2;
	typedef itk::Image< PixelType, Dimension >  ImageType;
	
	typedef itk::ImageFileReader<ImageType> ReaderType;
	ReaderType::Pointer reader = ReaderType::New();
	
	reader->SetFileName(strInputFilename.c_str());
	reader->Update();
	
	ImageType::Pointer image = reader->GetOutput();

	typedef itk::Image< unsigned char, Dimension >  OutputImageType;
	
	typedef itk::CastImageFilter< ImageType, OutputImageType > CastingFilterType;
	CastingFilterType::Pointer caster = CastingFilterType::New();
	
	typedef  itk::ImageFileWriter< OutputImageType  > WriterType;
	WriterType::Pointer writer = WriterType::New();
	writer->SetFileName(strOutputFilename.c_str());
		
	typedef itk::ConnectedRegionEdgeThresholdImageFilter < ImageType, ImageType> ConnectedFilterType;
	ConnectedFilterType::Pointer connectedThreshold = ConnectedFilterType::New();
	
	connectedThreshold->SetLower(Lower);
	connectedThreshold->SetUpper(Upper);
	
	connectedThreshold->SetReplaceValue(255);
		
	//seed
	ImageType::IndexType seed;
  	seed[0] = SeedCol; //95
	seed[1] = SeedRow; //135

	connectedThreshold->SetSeed(seed);
		
	//setup pipeline
	connectedThreshold->SetInput(image);
	caster->SetInput(connectedThreshold->GetOutput() );
	writer->SetInput(caster->GetOutput());
	
	writer->Update();

	return 0;
}