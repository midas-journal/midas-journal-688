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
	//input required parameters:
	// ./itkConnectedRegionEdgeThresholdImageFilter_Test1D original.png Seed Lower Upper output.png
	std::string strInputFilename = argv[1];
	std::string strSeed = argv[2];
	std::string strLower = argv[3];
	std::string strUpper = argv[4];
	std::string strOutputFilename = argv[5];
	
	//read the input image
	
	typedef float PixelType;
	const unsigned int Dimension = 1;
	typedef itk::Image< PixelType, Dimension >  ImageType;
	typedef itk::ImageFileReader<ImageType> ReaderType;
	ReaderType::Pointer reader = ReaderType::New();
	
	reader->SetFileName(strInputFilename.c_str());
	reader->Update();
	
	ImageType::Pointer image = reader->GetOutput();
	
	//convert the seed inputs to integers
	std::stringstream ssSeed(strSeed);
	unsigned int Seed;
	ssSeed >> Seed;

	//convert lower and upper to floats
	std::stringstream ssLower(strLower);
	float Lower;
	ssLower >> Lower;
	
	std::stringstream ssUpper(strUpper);
	float Upper;
	ssUpper >> Upper;
	
	//setup the output and casting filter
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
  	seed[0] = Seed;

	connectedThreshold->SetSeed(seed);
		
	//setup pipeline
	connectedThreshold->SetInput(image);
	caster->SetInput(connectedThreshold->GetOutput() );
	writer->SetInput(caster->GetOutput());
	writer->Update();
	
	return 0;
}