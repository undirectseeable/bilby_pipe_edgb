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

#ifndef FrameCPP_VERSION_8_FrSimEvent_HH
#define FrameCPP_VERSION_8_FrSimEvent_HH

#include "framecpp/Version8/impl/FrSimEventClassicIO.hh"

#ifndef SWIGIMPORTED
namespace FrameCPP
{
    namespace Version_8
    {
      //===================================================================
      /// \brief Event data
      //===================================================================
      class FrSimEvent : public FrSimEventImpl::ClassicIO< FrSimEvent >
      {
      public:
        typedef GTime_type time_type;

            //-----------------------------------------------------------------
            /// \brief Default constructor
            ///
            /// \return
            ///    A new instance of this object.
            //-----------------------------------------------------------------
            FrSimEvent( );

            //-----------------------------------------------------------------
            /// \brief Copy Constructor
            ///
            /// \param[in] Source
            ///     The object from which to copy the information.
            ///
            /// \return
            ///    A new instance of this object.
            //-----------------------------------------------------------------
            FrSimEvent( const FrSimEvent& Source );

            //-----------------------------------------------------------------
            /// \brief Constructor
            ///
            /// \param[in] name
            ///     Name of event.
            /// \param[in] comment
            ///     Descriptor of event.
            /// \param[in] inputs
            ///     Input channels and filter parameters to event process.
            /// \param[in] time
            ///     GPS time corresponding to reference value of event.
            /// \param[in] timeBefore
            ///     Signal duration before time.
            /// \param[in] timeAfter
            ///     Signal duration after time.
            /// \param[in] amplitude
            ///     Continuous output amplitude returned by event.
            /// \param[in] parameters
            ///     Array of additional event parameters.
            ///
            /// \return
            ///    A new instance of this object.
            //-----------------------------------------------------------------
            FrSimEvent( const name_type&      name,
                        const comment_type&   comment,
                        const inputs_type&    inputs,
                        const GPSTime&        time,
                        const timeBefore_type timeBefore,
                        const timeAfter_type  timeAfter,
                        const amplitude_type  amplitude,
                        const ParamList_type& parameters );

            //-----------------------------------------------------------------
            /// \brief Promotion Constructor
            ///
            /// \param[in] Source
            ///     An FrSimEvent structure from a previous frame specification.
            /// \param[in] Stream
            ///     The stream from which the earliest version of the
            ///     FrSimEvent structure was read.
            ///
            /// \return
            ///     A new instance of the object.
            //-----------------------------------------------------------------
            FrSimEvent( const Previous::FrSimEvent& Source,
                        istream_type*            Stream );

            //-----------------------------------------------------------------
            /// \brief Retrieve the name of event.
            ///
            /// \return
            ///     The name of event.
            //-----------------------------------------------------------------
            const std::string& GetNameSlow( ) const;

            //-----------------------------------------------------------------
            /// \brief Merge with another FrSimEvent
            ///
            /// \param[in] RHS
            ///     The source of the information to append to this FrSimEvent
            ///     structure.
            ///
            /// \return
            ///     A reference to this object
            //-----------------------------------------------------------------
            FrSimEvent& Merge( const FrSimEvent& RHS );

            //-----------------------------------------------------------------
            /// \brief inequality operator
            ///
            /// \param[in] RHS
            ///     The FrSimEvent object to be compared.
            ///
            /// \return
            ///     The value true is returned if this object is not equivelent
            ///     to the RHS instance; false otherwise.
            //-----------------------------------------------------------------
            bool operator==( const FrSimEvent& RHS ) const;

            //-----------------------------------------------------------------
            /// \brief equality operator for abstract data type
            ///
            /// \param[in] RHS
            ///     The object to be compared.
            ///
            /// \return
            ///     The value true is returned if this object is equivelent
            ///     to the RHS instance; false otherwise.
            //-----------------------------------------------------------------
            virtual bool
            operator==( const Common::FrameSpec::Object& RHS ) const;
        };

        inline bool
        FrSimEvent::operator==( const FrSimEvent& RHS ) const
        {
            return ( ( this == &RHS ) ||
                     ( static_cast< const Data& >( *this ) == static_cast< const Data& >( RHS ) ) );
        }
    } // namespace Version_8
} // namespace FrameCPP

#endif /* SWIGIMPORTED */

#endif /* FrameCPP_VERSION_8_FrSimEvent_HH */
