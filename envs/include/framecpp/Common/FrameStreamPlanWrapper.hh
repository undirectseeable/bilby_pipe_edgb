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

#ifndef FRAMECPP__COMMON__FrameStreamPlanWrapper_HH
#define FRAMECPP__COMMON__FrameStreamPlanWrapper_HH

#include <algorithm>
#include <stdexcept>

#include "framecpp/Common/FrameStreamWrapper.hh"
#include "framecpp/Common/FrEndOfFile.hh"
#include "framecpp/Common/FrTOC.hh"

#undef DECL
#define DECL                                                                   \
    INT_2U SPEC, typename AdcData, typename FrameH, typename ProcData,         \
        typename SerData, typename SimData, typename RawData, typename Event,  \
        typename SimEvent
#undef DECL_PARAMS
#define DECL_PARAMS                                                            \
    SPEC, AdcData, FrameH, ProcData, SerData, SimData, RawData, Event, SimEvent

namespace FrameCPP
{
    namespace Common
    {
        /// Frame Reading FrameStreamPlanWrapper
        template < DECL >
        class IFrameStreamPlanWrapper
            : public IFrameStreamWrapper< DECL_PARAMS >
        {
        public:
            typedef IFrameStreamWrapper< DECL_PARAMS >    base_type;
            typedef typename base_type::buffer_type       buffer_type;
            typedef typename base_type::frame_offset_type frame_offset_type;
            typedef typename base_type::fr_adc_data_type  fr_adc_data_type;
            typedef typename base_type::fr_event_type     fr_event_type;
            typedef INT_4U                                fr_event_offset_type;
            typedef typename base_type::fr_proc_data_type fr_proc_data_type;
            typedef typename base_type::fr_ser_data_type  fr_ser_data_type;
            typedef typename base_type::fr_sim_data_type  fr_sim_data_type;
            typedef typename base_type::fr_sim_event_type fr_sim_event_type;
            typedef INT_4U fr_sim_event_offset_type;
            typedef IFrameStreamPlanWrapper< DECL_PARAMS > plan_type;

            IFrameStreamPlanWrapper( buffer_type* Stream,
                                     plan_type*   master = 0 );

            ~IFrameStreamPlanWrapper( );

            //-----------------------------------------------------------------
            /// \brief Extract the requested FrAdcData structure from the stream
            ///
            /// \param[in] Frame
            ///     Zero based index of the frame.
            /// \param[in] Channel
            ///     Zero based index of channel being requested.
            ///
            /// \return
            ///     Upon success, a non-NULL pointer to the FrAdcData is
            ///     returned. Upon failure, either an exception is thrown
            //      or a NULL pointer is returned.
            //-----------------------------------------------------------------
            fr_adc_data_type ReadFrAdcData( frame_offset_type Frame,
                                            INT_4U            Channel );

            //-----------------------------------------------------------------
            /// \brief Extract the requested FrAdcData structure from the stream
            ///
            /// \param[in] Frame
            ///     Zero based index of the frame.
            /// \param[in] Channel
            ///     Name of the channel being requested.
            ///
            /// \return
            ///     Upon success, a non-NULL pointer to the FrAdcData is
            ///     returned. Upon failure, either an exception is thrown
            //      or a NULL pointer is returned.
            //-----------------------------------------------------------------
            fr_adc_data_type ReadFrAdcData( frame_offset_type  Frame,
                                            const std::string& Channel );

            //-----------------------------------------------------------------
            /// \brief Extract the requested FrEvent structure from the stream
            ///
            /// \param[in] Frame
            ///     Zero based index of the frame.
            /// \param[in] Channel
            ///     Name of the channel being requested.
            ///
            /// \return
            ///     Upon success, a non-NULL pointer to the FrEvent is
            ///     returned. Upon failure, either an exception is thrown
            //      or a NULL pointer is returned.
            //-----------------------------------------------------------------
            fr_event_type ReadFrEvent( frame_offset_type  Frame,
                                       const std::string& Channel );

            //-----------------------------------------------------------------
            /// \brief Extract the requested FrEvent structure from the stream
            ///
            /// \param[in] EventType
            ///     Name of the event type being requested.
            /// \param[in] Offset
            ///     Index into the Event array for the Event type
            ///
            /// \return
            ///     Upon success, a non-NULL pointer to the FrEvent is
            ///     returned. Upon failure, either an exception is thrown
            //      or a NULL pointer is returned.
            //-----------------------------------------------------------------
            fr_event_type ReadFrEvent( const std::string&   EventType,
                                       fr_event_offset_type Offset );

            //-----------------------------------------------------------------
            /// \brief Extract the requested FrProcData structure from the
            /// stream
            ///
            /// \param[in] Frame
            ///     Zero based index of the frame.
            /// \param[in] Channel
            ///     Name of the channel being requested.
            ///
            /// \return
            ///     Upon success, a non-NULL pointer to the FrProcData is
            ///     returned. Upon failure, either an exception is thrown
            //      or a NULL pointer is returned.
            //-----------------------------------------------------------------
            fr_proc_data_type ReadFrProcData( frame_offset_type  Frame,
                                              const std::string& Channel );

            //-----------------------------------------------------------------
            /// \brief Extract the requested FrSerData structure from the stream
            ///
            /// \param[in] Frame
            ///     Zero based index of the frame.
            /// \param[in] Channel
            ///     Name of the channel being requested.
            ///
            /// \return
            ///     Upon success, a non-NULL pointer to the FrSerData is
            ///     returned. Upon failure, either an exception is thrown
            //      or a NULL pointer is returned.
            //-----------------------------------------------------------------
            fr_ser_data_type ReadFrSerData( frame_offset_type  Frame,
                                            const std::string& Channel );

            //-----------------------------------------------------------------
            /// \brief Extract the requested FrSimData structure from the stream
            ///
            /// \param[in] Frame
            ///     Zero based index of the frame.
            /// \param[in] Channel
            ///     Name of the channel being requested.
            ///
            /// \return
            ///     Upon success, a non-NULL pointer to the FrSimData is
            ///     returned. Upon failure, either an exception is thrown
            //      or a NULL pointer is returned.
            //-----------------------------------------------------------------
            fr_sim_data_type ReadFrSimData( frame_offset_type  Frame,
                                            const std::string& Channel );

            //-----------------------------------------------------------------
            /// \brief Extract the requested FrSimEvent structure from the
            /// stream
            ///
            /// \param[in] Frame
            ///     Zero based index of the frame.
            /// \param[in] Channel
            ///     Name of the channel being requested.
            ///
            /// \return
            ///     Upon success, a non-NULL pointer to the FrSimEvent is
            ///     returned. Upon failure, either an exception is thrown
            //      or a NULL pointer is returned.
            //-----------------------------------------------------------------
            fr_sim_event_type ReadFrSimEvent( frame_offset_type  Frame,
                                              const std::string& Channel );

            //-----------------------------------------------------------------
            /// \brief Extract the requested FrSimEvent structure from the
            /// stream
            ///
            /// \param[in] SimEventType
            ///     Name of the simulated event type being requested.
            /// \param[in] Offset
            ///     Index into the SimEvent array for the SimEvent type
            ///
            /// \return
            ///     Upon success, a non-NULL pointer to the FrSimEvent is
            ///     returned. Upon failure, either an exception is thrown
            //      or a NULL pointer is returned.
            //-----------------------------------------------------------------
            fr_sim_event_type ReadFrSimEvent( const std::string&   SimEventType,
                                              fr_event_offset_type Offset );

        private:
            IFrameStreamPlanWrapper* master_plan;
            typedef enum
            {
                CACHE_FR_ADC_DATA,
                CACHE_FR_EVENT,
                CACHE_FR_PROC_DATA,
                CACHE_FR_SER_DATA,
                CACHE_FR_SIM_DATA,
                CACHE_FR_SIM_EVENT,
                CACHE_SIZE // Must always be the last element
            } cache_type;
            bool needs_reset[ CACHE_SIZE ];

            //-----------------------------------------------------------
            /// \brief Verify that the TOC stream compatibility
            ///
            /// To be able to reuse a table of contents structure,
            /// several checks need to be performed for validation
            //-----------------------------------------------------------
            inline bool
            is_compatible( const plan_type* old_plan )
            {
                /* auto restore_pos( this->restorePosition( ) ); */
                auto eof( this->readFrEndOfFile( ) );

                if ( ( !old_plan ) || ( !old_plan->getTOC( ) ) || ( !eof ) ||
                     ( eof->NFrames( ) != old_plan->getTOC( )->nFrame( ) ) )
                {
                    return ( false );
                }

                auto       toc( this->readFrTOCHeader( eof->SeekTOC( ) ) );
                auto const old_toc( old_plan->getTOC( ) );
                auto       frame_count( old_toc->nFrame( ) );

                if ( ( !toc ) || ( toc->nFrame( ) != frame_count ) ||
                     ( toc->runs( ).size( ) != old_toc->runs( ).size( ) ) ||
                     ( !std::equal( old_toc->runs( ).begin( ),
                                    old_toc->runs( ).end( ),
                                    toc->runs( ).begin( ) ) ) )
                {
                    return ( false );
                }
                return ( true );
            }

            template < int OFFSET >
            inline void
            reset_positions( )
            {
                if ( master_plan )
                {
                    if ( needs_reset[ OFFSET ] )
                    {
                        switch ( OFFSET )
                        {
                        case CACHE_FR_ADC_DATA:
                            IFrameStream::getTOC( )->cacheAdcDataPositions(
                                *this );
                            break;
                        case CACHE_FR_PROC_DATA:
                            IFrameStream::getTOC( )->procDataCachePositions(
                                *this );
                            break;
                        default:
                            throw( std::runtime_error(
                                "Unable to reset TOC channel positions" ) );
                        }
                        needs_reset[ OFFSET ] = false;
                    }
                }
            }
        }; // class IFrameStreamPlanWrapper

        template < DECL >
        inline IFrameStreamPlanWrapper< DECL_PARAMS >::IFrameStreamPlanWrapper(
            buffer_type* Stream, plan_type* master )
            : IFrameStreamWrapper< DECL_PARAMS >( Stream ),
              master_plan( master )
        {
            std::fill(
                &( needs_reset[ 0 ] ), &( needs_reset[ CACHE_SIZE ] ), true );
            if ( is_compatible( master_plan ) )
            {
                // Will not load the TOC but rather use the master plan TOC
                // :TODO: need to see if the TOC size is still the same and
                // that the frame sequence is continuous
                // Assign the TOC pointer from the mater plan
                this->seedTOCInfo( *master_plan );
            }
            else
            {
                std::fill( &( needs_reset[ 0 ] ),
                           &( needs_reset[ CACHE_SIZE ] ),
                           false );
            }
        }

        template < DECL >
        inline IFrameStreamPlanWrapper<
            DECL_PARAMS >::~IFrameStreamPlanWrapper( )
        {
        }

        template < DECL >
        inline typename IFrameStreamPlanWrapper< DECL_PARAMS >::fr_adc_data_type
        IFrameStreamPlanWrapper< DECL_PARAMS >::ReadFrAdcData(
            frame_offset_type Frame, INT_4U Channel )
        {
            reset_positions< CACHE_FR_ADC_DATA >( );
            return IFrameStreamWrapper< DECL_PARAMS >::ReadFrAdcData( Frame,
                                                                      Channel );
        }

        template < DECL >
        inline typename IFrameStreamPlanWrapper< DECL_PARAMS >::fr_adc_data_type
        IFrameStreamPlanWrapper< DECL_PARAMS >::ReadFrAdcData(
            frame_offset_type Frame, const std::string& Channel )
        {
            reset_positions< CACHE_FR_ADC_DATA >( );
            return IFrameStreamWrapper< DECL_PARAMS >::ReadFrAdcData( Frame,
                                                                      Channel );
        }

        template < DECL >
        inline typename IFrameStreamPlanWrapper< DECL_PARAMS >::fr_event_type
        IFrameStreamPlanWrapper< DECL_PARAMS >::ReadFrEvent(
            frame_offset_type Frame, const std::string& Channel )
        {
            reset_positions< CACHE_FR_EVENT >( );
            return IFrameStreamWrapper< DECL_PARAMS >::ReadFrEvent( Frame,
                                                                    Channel );
        }

        template < DECL >
        inline typename IFrameStreamPlanWrapper< DECL_PARAMS >::fr_event_type
        IFrameStreamPlanWrapper< DECL_PARAMS >::ReadFrEvent(
            const std::string& EventType, fr_event_offset_type Offset )
        {
            reset_positions< CACHE_FR_EVENT >( );
            return IFrameStreamWrapper< DECL_PARAMS >::ReadFrEvent( EventType,
                                                                    Offset );
        }

        template < DECL >
        inline
            typename IFrameStreamPlanWrapper< DECL_PARAMS >::fr_proc_data_type
            IFrameStreamPlanWrapper< DECL_PARAMS >::ReadFrProcData(
                frame_offset_type Frame, const std::string& Channel )
        {
            reset_positions< CACHE_FR_PROC_DATA >( );
            return IFrameStreamWrapper< DECL_PARAMS >::ReadFrProcData(
                Frame, Channel );
        }

        template < DECL >
        inline typename IFrameStreamPlanWrapper< DECL_PARAMS >::fr_ser_data_type
        IFrameStreamPlanWrapper< DECL_PARAMS >::ReadFrSerData(
            frame_offset_type Frame, const std::string& Channel )
        {
            reset_positions< CACHE_FR_SER_DATA >( );
            return IFrameStreamWrapper< DECL_PARAMS >::ReadFrSerData( Frame,
                                                                      Channel );
        }

        template < DECL >
        inline typename IFrameStreamPlanWrapper< DECL_PARAMS >::fr_sim_data_type
        IFrameStreamPlanWrapper< DECL_PARAMS >::ReadFrSimData(
            frame_offset_type Frame, const std::string& Channel )
        {
            reset_positions< CACHE_FR_SIM_DATA >( );
            return IFrameStreamWrapper< DECL_PARAMS >::ReadFrSimData( Frame,
                                                                      Channel );
        }

        template < DECL >
        inline
            typename IFrameStreamPlanWrapper< DECL_PARAMS >::fr_sim_event_type
            IFrameStreamPlanWrapper< DECL_PARAMS >::ReadFrSimEvent(
                frame_offset_type Frame, const std::string& Channel )
        {
            reset_positions< CACHE_FR_SIM_EVENT >( );
            return IFrameStreamWrapper< DECL_PARAMS >::ReadFrSimEvent(
                Frame, Channel );
        }

        template < DECL >
        inline
            typename IFrameStreamPlanWrapper< DECL_PARAMS >::fr_sim_event_type
            IFrameStreamPlanWrapper< DECL_PARAMS >::ReadFrSimEvent(
                const std::string&       SimEventType,
                fr_sim_event_offset_type Offset )
        {
            reset_positions< CACHE_FR_SIM_EVENT >( );
            return IFrameStreamWrapper< DECL_PARAMS >::ReadFrSimEvent(
                SimEventType, Offset );
        }

    } // namespace Common
} // namespace FrameCPP

#undef DECL
#undef DECL_PARAMS

#endif /* FRAMECPP__COMMON__FrameStreamPlanWrapper_HH */
