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

#ifndef FrameCPP_VERSION_8_FrVect_HH
#define FrameCPP_VERSION_8_FrVect_HH

#if !defined( SWIGIMPORTED )
#include "framecpp/Common/FrVect.hh"
#endif /* !defined( SWIGIMPORTED ) */

#include "framecpp/Version8/impl/FrVectClassicIO.hh"
#include "framecpp/Version8/impl/FrVectSerialIO.hh"

namespace FrameCPP
{
    namespace Version_8
    {
        //===================================================================
        /// \brief Vector Data Structure Definition
        //===================================================================
        class FrVect
#if !defined( SWIG )
            : public FrVectImpl::ClassicIO< FrVect >,
              public FrVectImpl::SerialIO< FrVect >
#endif /* ! defined(SWIG) */
        {
        public:
            typedef std::unique_ptr< FrVect > subfrvect_type;

            //-----------------------------------------------------------------
            /// \brief Retrieve the name of message, error flag, or alarm
            /// state.
            ///
            /// \return
            ///     The name of message, error flag, or alarm state.
            //-----------------------------------------------------------------
            const name_type& GetName( ) const;

            //-----------------------------------------------------------------
            /// \brief Default constructor
            ///
            /// \return
            ///    A new instance of this object.
            //-----------------------------------------------------------------
            FrVect( );

            //-----------------------------------------------------------------
            /// \brief Copy Constructor
            ///
            /// \param[in] vect
            ///     The object from which to copy the information.
            ///
            /// \return
            ///    A new instance of this object.
            //-----------------------------------------------------------------
            FrVect( const FrVect& vect );

            //-----------------------------------------------------------------
            /// \brief Constructor.
            ///
            /// \param[in] name
            ///     The name of the data.
            /// \param[in] type
            ///     The data type.
            /// \param[in] nDim
            ///     The number of dimensions.
            /// \param[in] dims
            ///     A pointer to 'nDim' Dimension objects containing
            ///     information about the dimensions for this data.
            /// \param[in] byte_order
            ///     Byte order of the data. Default is BYTE_ORDER_HOST
            /// \param[in] data
            ///     A pointer to the data.  Default: 0
            /// \param[in] unitY
            ///     Units for the data.  Default: ""
            ///
            /// \return
            ///    A new instance of this object.
            //-----------------------------------------------------------------
            FrVect( const std::string&    name,
                    type_type             type,
                    nDim_type             nDim,
                    const Dimension*      dims,
                    const byte_order_type byte_order = BYTE_ORDER_HOST,
                    const void*           data = 0,
                    const std::string&    unitY = "" );

            FrVect( const std::string& name,
                    compress_type      Compress,
                    type_type          type,
                    nDim_type          nDim,
                    const Dimension*   dims,
                    nData_type         NData,
                    nBytes_type        NBytes,
                    data_type          Data,
                    const std::string& unitY = "" );

            //-----------------------------------------------------------------
            /// \brief Constructor
            ///
            /// \param[in] Name
            ///     The name of the data.
            /// \param[in] Type
            ///     The data type.
            /// \param[in] NDim
            ///     The number of dimensions.
            /// \param[in] Dims
            ///     A pointer to 'nDim' Dimension objects containing
            ///     information about the dimensions for this data.
            /// \param[in] UnitY
            ///     Units for the data.
            ///
            /// \return
            ///    A new instance of this object.
            //-----------------------------------------------------------------
            FrVect( const std::string& Name,
                    type_type          Type,
                    nDim_type          NDim,
                    const Dimension*   Dims,
                    const std::string& UnitY );

#if !defined( SWIG )
            template < class T >
            FrVect( const std::string& name,
                    nDim_type          nDim = 1,
                    const Dimension*   dims = 0,
                    const T*           data = 0,
                    const std::string& unitY = "" );

            template < class T >
            FrVect( const std::string& name,
                    nDim_type          nDim = 1,
                    const Dimension*   dims = 0,
                    T*                 data = 0,
                    const std::string& unitY = "" );
#endif /* ! defined(SWIG) */

            //-----------------------------------------------------------------
            /// \brief Promotion Constructor
            ///
            /// \param[in] Source
            ///     An FrAdcData structure from a previous frame specification.
            /// \param[in] Stream
            ///     The stream from which the earliest version of the
            ///     FrAdcData structure was read.
            ///
            /// \return
            ///     A new instance of the object.
            //-----------------------------------------------------------------
            FrVect( const Previous::FrVect& Source, Common::IStream* Stream );

            //-----------------------------------------------------------------
            /// \brief Destructor
            //-----------------------------------------------------------------
            virtual ~FrVect( );

            //-----------------------------------------------------------------
            /// \brief Request a subset of the data.
            ///
            /// \param[in] Start
            ///     The offset in the data set where to start.
            /// \param[in] Stop
            ///     The offset in the data set where to stop.
            ///
            /// \return
            ///     The subset of data bounded by data[Start, Stop).
            //-----------------------------------------------------------------
            subfrvect_type SubFrVect( INT_4U Start, INT_4U Stop ) const;

            //-----------------------------------------------------------------
            /// \brief equality operator
            ///
            /// \param[in] RHS
            ///     The FrAdcData object to be compared.
            ///
            /// \return
            ///     The value true is returned if this object is equivelent
            ///     to the RHS instance; false otherwise.
            //-----------------------------------------------------------------
            bool operator==( const FrVect& RHS ) const;

            //-----------------------------------------------------------------
            /// \brief inequality operator
            ///
            /// \param[in] RHS
            ///     The FrAdcData object to be compared.
            ///
            /// \return
            ///     The value true is returned if this object is not equivelent
            ///     to the RHS instance; false otherwise.
            //-----------------------------------------------------------------
            bool operator!=( const FrVect& RHS ) const;

            //-----------------------------------------------------------------
            /// \brief Concatinate with another FrAdcData
            ///
            /// \param[in] RHS
            ///     The source of the information to append to this FrAdcData
            ///     structure.
            ///
            /// \return
            ///     A reference to this object
            //-----------------------------------------------------------------
            FrVect& operator+=( const FrVect& RHS );

            //-----------------------------------------------------------------
            /// \brief Merge with another FrAdcData
            ///
            /// \param[in] RHS
            ///     The source of the information to append to this FrAdcData
            ///     structure.
            ///
            /// \return
            ///     A reference to this object
            //-----------------------------------------------------------------
            FrVect& Merge( const FrVect& RHS );
        };
    } // namespace Version_8
} // namespace FrameCPP

#if defined( __SUNPRO_CC )
#if ( __SUNPRO_CC <= 0x550 )
#include "framecpp/Version8/FrVect.icc"
#endif /* */
#endif /* */

#endif /* FrameCPP_VERSION_8_FrVect_HH */
