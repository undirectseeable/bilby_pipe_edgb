//
// LDASTools frameCPP - A library implementing the LIGO/Virgo frame specification
//
// Copyright (C) 2018 California Institute of Technology
//
// LDASTools frameCPP is free software; you may redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 (GPLv2) of the
// License or at your discretion, any later version.
//
// LDASTools frameCPP is distributed in the hope that it will be useful, but
// without any warranty or even the implied warranty of merchantability
// or fitness for a particular purpose. See the GNU General Public
// License (GPLv2) for more details.
//
// Neither the names of the California Institute of Technology (Caltech),
// The Massachusetts Institute of Technology (M.I.T), The Laser
// Interferometer Gravitational-Wave Observatory (LIGO), nor the names
// of its contributors may be used to endorse or promote products derived
// from this software without specific prior written permission.
//
// You should have received a copy of the licensing terms for this
// software included in the file LICENSE located in the top-level
// directory of this package. If you did not, you can view a copy at
// http://dcc.ligo.org/M1500244/LICENSE
//

#ifndef FRAMECPP__VERSION_3__FR_VECT_ICC
#define FRAMECPP__VERSION_3__FR_VECT_ICC

template< class T > INT_2U get_type( );

template< >
inline INT_2U get_type< CHAR >( )
{
  return FrameCPP::Version_3::FrVect::FR_VECT_C;
}

template< >
inline INT_2U get_type< INT_2S >( )
{
  return FrameCPP::Version_3::FrVect::FR_VECT_2S;
}

template< >
inline INT_2U get_type< REAL_8 >( )
{
  return FrameCPP::Version_3::FrVect::FR_VECT_8R;
}

template< >
inline INT_2U get_type< REAL_4 >( )
{
  return FrameCPP::Version_3::FrVect::FR_VECT_4R;
}

template< >
inline INT_2U get_type< INT_4S >( )
{
  return FrameCPP::Version_3::FrVect::FR_VECT_4S;
}

template< >
inline INT_2U get_type< INT_8S >( )
{
  return FrameCPP::Version_3::FrVect::FR_VECT_8S;
}

template< >
inline INT_2U get_type< COMPLEX_8 >( )
{
  return FrameCPP::Version_3::FrVect::FR_VECT_8C;
}

template< >
inline INT_2U get_type< COMPLEX_16 >( )
{
  return FrameCPP::Version_3::FrVect::FR_VECT_16C;
}

template< >
inline INT_2U get_type< FrameCPP::Version_3::STRING >( )
{
  return FrameCPP::Version_3::FrVect::FR_VECT_STRING;
}

template< >
inline INT_2U get_type< INT_2U >( )
{
  return FrameCPP::Version_3::FrVect::FR_VECT_2U;
}

template< >
inline INT_2U get_type< INT_4U >( )
{
  return FrameCPP::Version_3::FrVect::FR_VECT_4U;
}
template< >
inline INT_2U get_type< INT_8U >( )
{
  return FrameCPP::Version_3::FrVect::FR_VECT_8U;
}

template< >
inline INT_2U get_type< CHAR_U >( )
{
  return FrameCPP::Version_3::FrVect::FR_VECT_1U;
}

template< class T >
FrameCPP::Version_3::FrVect::
FrVect( const std::string& name, nDim_type nDim,
	const Dimension* dims,
	const T* data, const std::string& unitY )
  : Common::FrameSpec::Object( s_object_id, StructDescription( ) ),
    m_data( name, get_type< T >(), BYTE_ORDER_BIG_ENDIAN, nDim, dims, unitY )
{
#ifdef MEM_ALLOCATE
  MEM_ALLOCATE( );
#endif /* MEM_ALLOCATE */
  m_data.compress = RAW;
  copy_data( (CHAR_U*)data, m_data.nBytes );
}

template< class T >
FrameCPP::Version_3::FrVect::
FrVect( const std::string& name, nDim_type nDim,
	const Dimension* dims,
	T* data, const std::string& unitY,
	bool allocate, bool owns )
  : Common::FrameSpec::Object( s_object_id, StructDescription( ) ),
    m_data( name, get_type< T >(), BYTE_ORDER_BIG_ENDIAN, nDim, dims, unitY )
{
#ifdef MEM_ALLOCATE
  MEM_ALLOCATE( );
#endif /* MEM_ALLOCATE */
  m_data.compress = RAW;

  copy_data( reinterpret_cast< CHAR_U* >( data ), m_data.nBytes );
}

#endif /* FRAMECPP__VERSION_3__FR_VECT_ICC */
