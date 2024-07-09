//
// LDASTools frameCPP - A library implementing the LIGO/Virgo frame
// specification
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

#ifndef FRAME_CPP__Common__CompressionDifferential_hh
#define FRAME_CPP__Common__CompressionDifferential_hh

#include <boost/shared_array.hpp>
#include <boost/shared_ptr.hpp>

#include "framecpp/Common/Compression.hh"

namespace FrameCPP
{
    namespace Compression
    {

        namespace Differential
        {
            typedef Compression::output_type output_type;

            //-----------------------------------------------------------------
            //-----------------------------------------------------------------
            void Decode( CHAR_U* Data, INT_4U NData, data_types_type Type );

            //-----------------------------------------------------------------
            //-----------------------------------------------------------------
            void Decode( const CHAR_U*   Data,
                         INT_4U          NData,
                         data_types_type Type,
                         output_type&    Out );

            //-----------------------------------------------------------------
            //-----------------------------------------------------------------
            template < class T >
            void Decode( CHAR_U* Data, INT_4U NData );

            //-----------------------------------------------------------------
            //-----------------------------------------------------------------
            template < class T >
            void Decode( const CHAR_U* Data, INT_4U NData, output_type& Out );

            //-----------------------------------------------------------------
            //-----------------------------------------------------------------
            void Encode( CHAR_U* Data, INT_4U NData, INT_2U Type );

            //-----------------------------------------------------------------
            //-----------------------------------------------------------------
            void Encode( const CHAR_U* Data,
                         INT_4U        NData,
                         INT_2U        Type,
                         output_type&  Out );

            //-----------------------------------------------------------------
            //-----------------------------------------------------------------
            template < class T >
            void Encode( CHAR_U* Data, INT_4U NData );

            //-----------------------------------------------------------------
            //-----------------------------------------------------------------
            template < class T >
            void Encode( const CHAR_U* Data, INT_4U NData, output_type& Dest );

            //-----------------------------------------------------------------
            //-----------------------------------------------------------------
            inline void
            Decode( CHAR_U* Data, INT_4U NData, data_types_type Type )
            {
                if ( NData > 1 )
                {
                    switch ( Type )
                    {
                    case FR_VECT_C:
                        Decode< CHAR >( Data, NData );
                        break;
                    case FR_VECT_1U:
                        Decode< CHAR_U >( Data, NData );
                        break;
                    case FR_VECT_2S:
                        Decode< INT_2S >( Data, NData );
                        break;
                    case FR_VECT_2U:
                        Decode< INT_2U >( Data, NData );
                        break;
                    case FR_VECT_4S:
                        Decode< INT_4S >( Data, NData );
                        break;
                    case FR_VECT_4U:
                        Decode< INT_4U >( Data, NData );
                        break;
                    case FR_VECT_8S:
                        Decode< INT_8S >( Data, NData );
                        break;
                    case FR_VECT_8U:
                        Decode< INT_8U >( Data, NData );
                        break;
                    case FR_VECT_4R:
                        Decode< INT_4S >( Data, NData );
                        break;
                    case FR_VECT_8R:
                        Decode< INT_8S >( Data, NData );
                        break;
                    case FR_VECT_8C:
                        Decode< INT_4S >( Data, INT_4U( NData * 2 ) );
                        break;
                    case FR_VECT_16C:
                        Decode< INT_8S >( Data, INT_4U( NData * 2 ) );
                        break;
                    default:
                    {
                        std::ostringstream msg;

                        msg << "unable to perform differntial decoding on data "
                               "type: "
                            << Type;
                        throw std::range_error( msg.str( ) );
                    }
                    break;
                    }
                }
            } // function - Decode

            //-----------------------------------------------------------------
            //-----------------------------------------------------------------
            inline void
            Decode( const CHAR_U*   Data,
                    INT_4U          NData,
                    data_types_type Type,
                    output_type&    Out )
            {
                if ( NData > 1 )
                {
                    switch ( Type )
                    {
                    case FR_VECT_C:
                        Decode< CHAR >( Data, NData, Out );
                        break;
                    case FR_VECT_1U:
                        Decode< CHAR_U >( Data, NData, Out );
                        break;
                    case FR_VECT_2S:
                        Decode< INT_2S >( Data, NData, Out );
                        break;
                    case FR_VECT_2U:
                        Decode< INT_2U >( Data, NData, Out );
                        break;
                    case FR_VECT_4S:
                        Decode< INT_4S >( Data, NData, Out );
                        break;
                    case FR_VECT_4U:
                        Decode< INT_4U >( Data, NData, Out );
                        break;
                    case FR_VECT_8S:
                        Decode< INT_8S >( Data, NData, Out );
                        break;
                    case FR_VECT_8U:
                        Decode< INT_8U >( Data, NData, Out );
                        break;
                    case FR_VECT_4R:
                        Decode< INT_4S >( Data, NData, Out );
                        break;
                    case FR_VECT_8R:
                        Decode< INT_8S >( Data, NData, Out );
                        break;
                    case FR_VECT_8C:
                        Decode< INT_4S >( Data, INT_4U( NData * 2 ), Out );
                        break;
                    case FR_VECT_16C:
                        Decode< INT_8S >( Data, INT_4U( NData * 2 ), Out );
                        break;
                    default:
                    {
                        std::ostringstream msg;

                        msg << "unable to perform differntial decoding on data "
                               "type: "
                            << Type;
                        throw std::range_error( msg.str( ) );
                    }
                    break;
                    }
                }
            } // function - Decode

            //-----------------------------------------------------------------
            //-----------------------------------------------------------------
            inline void
            Encode( CHAR_U* Data, INT_4U NData, INT_2U Type )
            {
                switch ( Type )
                {
                case FR_VECT_1U:
                    Encode< CHAR_U >( Data, NData );
                    break;
                case FR_VECT_C:
                    Encode< CHAR >( Data, NData );
                    break;

                case FR_VECT_2S:
                    Encode< INT_2S >( Data, NData );
                    break;

                case FR_VECT_2U:
                    Encode< INT_2U >( Data, NData );
                    break;

                case FR_VECT_4S:
                    Encode< INT_4S >( Data, NData );
                    break;

                case FR_VECT_4U:
                    Encode< INT_4U >( Data, NData );
                    break;

                case FR_VECT_8S:
                    Encode< INT_8S >( Data, NData );
                    break;

                case FR_VECT_8U:
                    Encode< INT_8U >( Data, NData );
                    break;

                case FR_VECT_4R:
                    Encode< INT_4S >( Data, NData );
                    break;

                case FR_VECT_8R:
                    Encode< INT_8S >( Data, NData );
                    break;

                case FR_VECT_8C:
                    Encode< INT_4S >( Data, INT_4U( NData * 2 ) );
                    break;

                case FR_VECT_16C:
                    Encode< INT_8S >( Data, INT_4U( NData * 2 ) );
                    break;
                }
            } // function - Encode

            //-----------------------------------------------------------------
            //-----------------------------------------------------------------
            inline void
            Encode( const CHAR_U* Data,
                    INT_4U        NData,
                    INT_2U        Type,
                    output_type&  Out )
            {
                switch ( Type )
                {
                case FR_VECT_1U:
                    Encode< CHAR_U >( Data, NData, Out );
                    break;
                case FR_VECT_C:
                    Encode< CHAR >( Data, NData, Out );
                    break;

                case FR_VECT_2S:
                    Encode< INT_2S >( Data, NData, Out );
                    break;

                case FR_VECT_2U:
                    Encode< INT_2U >( Data, NData, Out );
                    break;

                case FR_VECT_4S:
                    Encode< INT_4S >( Data, NData, Out );
                    break;

                case FR_VECT_4U:
                    Encode< INT_4U >( Data, NData, Out );
                    break;

                case FR_VECT_8S:
                    Encode< INT_8S >( Data, NData, Out );
                    break;

                case FR_VECT_8U:
                    Encode< INT_8U >( Data, NData, Out );
                    break;

                case FR_VECT_4R:
                    Encode< INT_4S >( Data, NData, Out );
                    break;

                case FR_VECT_8R:
                    Encode< INT_8S >( Data, NData, Out );
                    break;

                case FR_VECT_8C:
                    Encode< INT_4S >( Data, INT_4U( NData * 2 ), Out );
                    break;

                case FR_VECT_16C:
                    Encode< INT_8S >( Data, INT_4U( NData * 2 ), Out );
                    break;
                }
            } // function - Encode
        } // namespace Differential
    } // namespace Compression

} // namespace FrameCPP

#endif /* FRAME_CPP__Common__CompressionDifferential_hh */
