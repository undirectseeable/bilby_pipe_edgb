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

#ifndef FrameCPP_VERSION_8_FrHistory_HH
#define FrameCPP_VERSION_8_FrHistory_HH

#if !defined( SWIGIMPORTED )
#include "framecpp/Version7/FrHistory.hh"
#endif /* ! defined(SWIGIMPORTED) */

#if !defined( SWIGIMPORTED )
#include "framecpp/Version8/impl/FrHistoryClassicIO.hh"
#include "framecpp/Version8/impl/FrHistorySerialIO.hh"
#include "framecpp/Version8/FrameSpec.hh"
#include "framecpp/Version8/STRING.hh"
#endif /* ! defined(SWIGIMPORTED) */

namespace FrameCPP
{
    namespace Version_8
    {
        //===================================================================
        /// \brief History Structure Definition
        //===================================================================
        class FrHistory
#if !defined( SWIG )
            : public FrHistoryImpl::ClassicIO< FrHistory >,
              public FrHistoryImpl::SerialIO< FrHistory >
#endif /* ! defined(SWIG) */
        {
        public:
            //-----------------------------------------------------------------
            /// \brief Default constructor
            ///
            /// \return
            ///    A new instance of this object.
            //-----------------------------------------------------------------
            FrHistory( );

            //-----------------------------------------------------------------
            /// \brief Copy Constructor
            ///
            /// \param[in] Source
            ///     The object from which to copy the information.
            ///
            /// \return
            ///    A new instance of this object.
            //-----------------------------------------------------------------
            FrHistory( const FrHistory& Source );

            //-----------------------------------------------------------------
            /// \brief Constructor
            ///
            /// \param[in] Name
            ///     Name of the history record
            /// \param[in] Time
            ///     Time of post-processing
            ///     (GPS seconds since GPS standard epoch)
            /// \param[in] Comment
            ///     Program name and relevant comments needed to define
            ///     post-processing
            ///
            /// \return
            ///    A new instance of this object.
            //-----------------------------------------------------------------
            FrHistory( const std::string& Name,
                       time_type          Time,
                       const std::string& Comment );

            //-----------------------------------------------------------------
            /// \brief Promotion Constructor
            ///
            /// \param[in] Source
            ///     An FrHistory structure from a previous frame specification.
            /// \param[in] Stream
            ///     The stream from which the earliest version of the
            ///     FrAdcData structure was read.
            ///
            /// \return
            ///     A new instance of an FrHistory object
            //-----------------------------------------------------------------
            FrHistory( Previous::FrHistory& Source, istream_type* Stream );

            //-----------------------------------------------------------------
            /// \brief Return the name associate with the FrHistory
            /// structure.
            ///
            /// \return
            ///     The name associated with the FrHistory structure
            //-----------------------------------------------------------------
            const name_type& GetName( ) const;

            //-----------------------------------------------------------------
            /// \brief The name structure name of this object.
            ///
            /// \return
            ///     The name of the structure as specified by the frame
            ///     specification.
            //-----------------------------------------------------------------
            virtual const char* ObjectStructName( ) const;

            virtual std::string ErrorInfo( ) const;

            //-----------------------------------------------------------------
            /// \brief Merge with another FrHistory object
            ///
            /// \param[in] RHS
            ///     The source of the information to append to this FrHistory
            ///     structure.
            ///
            /// \return
            ///     A reference to this object
            //-----------------------------------------------------------------
            FrHistory& Merge( const FrHistory& RHS );

            //-----------------------------------------------------------------
            /// \brief equality operator
            ///
            /// \param[in] RHS
            ///     The FrHistory object to be compared.
            ///
            /// \return
            ///     The value true is returned if this object is equivelent
            ///     to the RHS instance; false otherwise.
            //-----------------------------------------------------------------
            bool operator==( const FrHistory& RHS ) const;

        protected:
        private:
            //-----------------------------------------------------------------
            /// \brief Stream Constructor
            ///
            /// \param[in] Stream
            ///     The stream from which the object is being read.
            ///
            /// \return
            ///    A new instance of this object.
            //-----------------------------------------------------------------
            FrHistory( istream_type& Stream );
        };

        inline bool
        FrHistory::operator==( const FrHistory& RHS ) const
        {
            return ( FrHistoryImpl::Data::operator==( RHS ) );
        }
    } // namespace Version_8
} // namespace FrameCPP
#endif /* FrameCPP_VERSION_8_FrHistory_HH */
