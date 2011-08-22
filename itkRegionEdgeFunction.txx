/*=========================================================================

  Program:   Insight Segmentation & Registration Toolkit
  Module:    $RCSfile: itkBinaryThresholdImageFunction.txx,v $
  Language:  C++
  Date:      $Date: 2006-02-06 22:01:53 $
  Version:   $Revision: 1.4 $

  Copyright (c) Insight Software Consortium. All rights reserved.
  See ITKCopyright.txt or http://www.itk.org/HTML/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even 
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#ifndef __itkRegionEdgeFunction_txx
#define __itkRegionEdgeFunction_txx

#include "itkRegionEdgeFunction.h"

namespace itk
{

template <class TInputImage, class TOutputImageType, class TCoordRep>
		RegionEdgeFunction<TInputImage,TOutputImageType, TCoordRep>
	::RegionEdgeFunction()
{
  m_Lower = NumericTraits<PixelType>::NonpositiveMin();
  m_Upper = NumericTraits<PixelType>::max();
  RegionSize = 0;
}

/**
 * Values greater than or equal to the value are inside
 */
template <class TInputImage, class TOutputImageType, class TCoordRep>
void 
		RegionEdgeFunction<TInputImage,TOutputImageType, TCoordRep>
::ThresholdAbove(PixelType thresh)
{
  if (m_Lower != thresh
      || m_Upper != NumericTraits<PixelType>::max())
    {
    m_Lower = thresh;
    m_Upper = NumericTraits<PixelType>::max();
    this->Modified();
    }
}

/**
 * The values less than or equal to the value are inside
 */
template <class TInputImage, class TOutputImageType, class TCoordRep>
void 
		RegionEdgeFunction<TInputImage,TOutputImageType, TCoordRep>
::ThresholdBelow(PixelType thresh)
{
  if (m_Lower != NumericTraits<PixelType>::NonpositiveMin()
      || m_Upper != thresh)
    {
    m_Lower = NumericTraits<PixelType>::NonpositiveMin();
    m_Upper = thresh;
    this->Modified();
    }
}

/**
 * The values less than or equal to the value are inside
 */
template <class TInputImage, class TOutputImageType, class TCoordRep>
void 
		RegionEdgeFunction<TInputImage,TOutputImageType, TCoordRep>
::ThresholdBetween(PixelType lower, PixelType upper)
{
  if (m_Lower != lower
      || m_Upper != upper)
    {
    m_Lower = lower;
    m_Upper = upper;
    this->Modified();
    }
}

template <class TInputImage, class TOutputImageType, class TCoordRep>
void 
		RegionEdgeFunction<TInputImage,TOutputImageType, TCoordRep>
::PrintSelf(std::ostream& os, Indent indent) const
{
  Superclass::PrintSelf( os, indent );

  os << indent << "Lower: " << m_Lower << std::endl;
  os << indent << "Upper: " << m_Upper << std::endl;
}

} // end namespace itk

#endif
