/*
 * LDASTools frameCPP - A library implementing the LIGO/Virgo frame
 * specification
 *
 * Copyright (C) 2018 California Institute of Technology
 *
 * LDASTools frameCPP is free software; you may redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 (GPLv2) of the
 * License or at your discretion, any later version.
 *
 * LDASTools frameCPP is distributed in the hope that it will be useful, but
 * without any warranty or even the implied warranty of merchantability
 * or fitness for a particular purpose. See the GNU General Public
 * License (GPLv2) for more details.
 *
 * Neither the names of the California Institute of Technology (Caltech),
 * The Massachusetts Institute of Technology (M.I.T), The Laser
 * Interferometer Gravitational-Wave Observatory (LIGO), nor the names
 * of its contributors may be used to endorse or promote products derived
 * from this software without specific prior written permission.
 *
 * You should have received a copy of the licensing terms for this
 * software included in the file LICENSE located in the top-level
 * directory of this package. If you did not, you can view a copy at
 * http://dcc.ligo.org/M1500244/LICENSE
 */

#ifndef FrameCPP_VERSION_8_FrEvent_HH
#define FrameCPP_VERSION_8_FrEvent_HH

#include "framecpp/Version8/impl/FrEventClassicIO.hh"
#include "framecpp/Version8/impl/FrEventSerialIO.hh"

#if defined( __cplusplus )
#if !defined( SWIGIMPORTED )
namespace FrameCPP
{
    namespace Version_8
    {
        //===================================================================
        /// \brief Event data
        //===================================================================
        class FrEvent : public FrEventImpl::ClassicIO< FrEvent >,
                        public FrEventImpl::SerialIO< FrEvent >
        {
        public:
            typedef GTime_type time_type;

            /**
             * \brief Default constructor
             */
            FrEvent( );
            /**
             * \brief Copy constructor
             *
             * \param[in] eventData
             *      Source of the event data.
             *
             * \return
             *    A new instance of this object.
             */
            FrEvent( const FrEvent& eventData );

            /**
             * \brief Constructor
             *
             * \param[in] name
             *     Name of event.
             * \param[in] comment
             *     Descriptor of event.
             * \param[in] inputs
             *     Input channels and filter parameters to event process.
             * \param[in] time
             *     GPS time corresponding to reference value of event.
             * \param[in] timeBefore
             *     Signal duration before time.
             * \param[in] timeAfter
             *     Signal duration after time.
             * \param[in] eventStatus
             *     Defined by event search algorithm.
             * \param[in] amplitude
             *     Continuous output amplitude returned by event.
             * \param[in] probability
             *     Likelihood estimate of event.
             * \param[in] statistics
             *     Statistical description of event.
             * \param[in] parameters
             *     Array of additional event parameters.
             *
             * \return
             *    A new instance of this object.
             */
            FrEvent( const name_type&       name,
                     const comment_type&    comment,
                     const inputs_type&     inputs,
                     const time_type&       time,
                     const timeBefore_type  timeBefore,
                     const timeAfter_type   timeAfter,
                     const eventStatus_type eventStatus,
                     const amplitude_type   amplitude,
                     const probability_type probability,
                     const statistics_type& statistics,
                     const ParamList_type&  parameters );

            /**
             * \brief Upconvert constructor
             *
             * \param[in] Source
             *     An instance of a similiar object from a previous version
             *     of the frame specification.
             * \param[in] Stream
             *     The stream from which the origional object was read.
             *
             * \return
             *    A new instance of this object.
             */
            FrEvent( const Previous::FrEvent& Source, istream_type* Stream );

            /**
             * \brief Retrieve the name of the event
             *
             * \return
             *     A name of the event via non-inlined function
             */
            const std::string& GetNameSlow( ) const;

            /**
             * \brief Merge with another FrEvent
             *
             * \param[in] RHS
             *     FrEvent information to incorperate into this object.
             */
            FrEvent& Merge( const FrEvent& RHS );

            /**
             * \brief equality operator
             *
             * \param[in] RHS
             *     The FrEndOfFrame object to be compared.
             *
             * \return
             *     The value true is returned if this object is equivelent
             *     to the RHS instance; false otherwise.
             */
            bool operator==( FrEvent const& RHS ) const;

            /**
             * \brief equality operator for abstract data type
             *
             * \param[in] Obj
             *     The object to be compared.
             *
             * \return
             *     The value true is returned if this object is equivelent
             *     to the RHS instance; false otherwise.
             */
            virtual bool
            operator==( Common::FrameSpec::Object const& Obj ) const;
        };

        inline bool
        FrEvent::operator==( FrEvent const& RHS ) const
        {
            return ( ( this == &RHS ) ||
                     ( (const Data&)( *this ) == (const Data&)( RHS ) ) );
        }
    } // namespace Version_8
} // namespace FrameCPP

#endif /* ! defined(SWIGIMPORTED) */
#endif /* defined( __cplusplus ) */

#endif /* FrameCPP_VERSION_8_FrEvent_HH */
