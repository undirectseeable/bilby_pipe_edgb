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

#ifndef FRAMECPP__COMMON__FrameStreamWrapper_HH
#define FRAMECPP__COMMON__FrameStreamWrapper_HH

#include <boost/pointer_cast.hpp>
#include <boost/shared_ptr.hpp>

#include "framecpp/Common/FrameStream.hh"

namespace FrameCPP
{
    namespace Common
    {
#define DECL                                                                   \
    INT_2U SPEC, typename AdcData, typename FrameH, typename ProcData,         \
        typename SerData, typename SimData, typename RawData, typename Event,  \
        typename SimEvent
#define DECL_PARAMS                                                            \
    SPEC, AdcData, FrameH, ProcData, SerData, SimData, RawData, Event, SimEvent

        //-------------------------------------------------------------------
        /// \brief Wrapper to properly cast return values into the namespace
        ///        associated with the frame specification namespace.
        //-------------------------------------------------------------------
        template < DECL >
        class IFrameStreamWrapper : public IFrameStream
        {
        public:
            typedef INT_4U frame_offset_type;

            typedef typename boost::shared_ptr< FrameH >   frame_h_type;
            typedef typename boost::shared_ptr< AdcData >  fr_adc_data_type;
            typedef typename boost::shared_ptr< Event >    fr_event_type;
            typedef INT_4U                                 fr_event_offset_type;
            typedef typename boost::shared_ptr< ProcData > fr_proc_data_type;
            typedef typename boost::shared_ptr< RawData >  fr_raw_data_type;
            typedef typename boost::shared_ptr< SerData >  fr_ser_data_type;
            typedef typename boost::shared_ptr< SimData >  fr_sim_data_type;
            typedef typename boost::shared_ptr< SimEvent > fr_sim_event_type;
            typedef INT_4U fr_sim_event_offset_type;

            //-----------------------------------------------------------------
            /// \brief Definition of buffer_type.
            //-----------------------------------------------------------------
            typedef IFrameStream::buffer_type buffer_type;

            //-----------------------------------------------------------------
            /// \brief Constructor
            //-----------------------------------------------------------------
            IFrameStreamWrapper( buffer_type* Buffer );

            //-----------------------------------------------------------------
            /// \brief Constructor
            //-----------------------------------------------------------------
            IFrameStreamWrapper( bool AutoDelete, buffer_type* Buffer );

            //-----------------------------------------------------------------
            //-----------------------------------------------------------------
            std::string FrameLibraryName( ) const;

            //-----------------------------------------------------------------
            /// \brief Extract the requested FrameH structure from the stream
            ///
            /// \param[in] Frame
            ///     Zero based index of the frame.
            /// \param[in] ContainerSet
            ///     Bit map of components to included.
            ///
            /// \return
            ///     Upon successful completion, the address of the FrameH
            ///     structure linked with all requested subcomponents
            ///     by ContainerSet.
            //-----------------------------------------------------------------
            frame_h_type ReadFrameH( frame_offset_type Frame,
                                     INT_4U            ContainerSet );

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
            fr_adc_data_type ReadFrAdcStruct( frame_offset_type  Frame,
                                              const std::string& Channel );
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
            fr_adc_data_type ReadFrAdcStruct( frame_offset_type Frame,
                                              INT_4U            Channel );

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
            ///     Name of the event being requested.
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
            fr_event_type ReadFrEventStruct( frame_offset_type  Frame,
                                             const std::string& Channel );

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
            /// \brief Extract the requested FrProcData structure from the
            /// stream
            ///
            /// \param[in] Frame
            ///     Zero based index of the frame.
            /// \param[in] Channel
            ///     Zero based index of channel being requested.
            ///
            /// \return
            ///     Upon success, a non-NULL pointer to the FrProcData is
            ///     returned. Upon failure, either an exception is thrown
            //      or a NULL pointer is returned.
            //-----------------------------------------------------------------
            fr_proc_data_type ReadFrProcData( frame_offset_type Frame,
                                              INT_4U            Channel );
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
            fr_proc_data_type ReadFrProcStruct( frame_offset_type  Frame,
                                                const std::string& Channel );

            //-----------------------------------------------------------------
            /// \brief Extract the requested FrProcData structure from the
            /// stream
            ///
            /// \param[in] Frame
            ///     Zero based index of the frame.
            /// \param[in] Channel
            ///     Zero based index of channel being requested.
            ///
            /// \return
            ///     Upon success, a non-NULL pointer to the FrProcData is
            ///     returned. Upon failure, either an exception is thrown
            //      or a NULL pointer is returned.
            //-----------------------------------------------------------------
            fr_proc_data_type ReadFrProcStruct( frame_offset_type Frame,
                                                INT_4U            Channel );

            //-----------------------------------------------------------------
            /// \brief Extract the requested FrRawData structure from the stream
            ///
            /// \param[in] Frame
            ///     Zero based index of the frame.
            ///
            /// \return
            ///     Upon success, a non-NULL pointer to the FrRawData is
            ///     returned. Upon failure, either an exception is thrown
            //      or a NULL pointer is returned.
            //-----------------------------------------------------------------
            fr_raw_data_type ReadFrRawData( frame_offset_type Frame );

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
            fr_ser_data_type ReadFrSerStruct( frame_offset_type  Frame,
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
            ///     Name of the simulated event being requested.
            /// \param[in] Offset
            ///     Index into the Event array for the Event type
            ///
            /// \return
            ///     Upon success, a non-NULL pointer to the FrSimEvent is
            ///     returned. Upon failure, either an exception is thrown
            //      or a NULL pointer is returned.
            //-----------------------------------------------------------------
            fr_sim_event_type ReadFrSimEvent( const std::string& SimEventType,
                                              fr_sim_event_offset_type Offset );

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
            fr_sim_event_type
            ReadFrSimEventStruct( frame_offset_type  Frame,
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
            ///     Upon success, a non-NULL pointer to the FrSimData is
            ///     returned. Upon failure, either an exception is thrown
            //      or a NULL pointer is returned.
            //-----------------------------------------------------------------
            fr_sim_data_type ReadFrSimStruct( frame_offset_type  Frame,
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
            ///     Upon success, a non-NULL pointer to the FrSimData is
            ///     returned. Upon failure, either an exception is thrown
            //      or a NULL pointer is returned.
            //-----------------------------------------------------------------
            fr_sim_data_type ReadFrSimData( frame_offset_type  Frame,
                                            const std::string& Channel );

            //-----------------------------------------------------------------
            /// \brief Extract the next FrameH structure from the stream
            ///
            /// \return
            ///     Upon success, a pointer to a FrameH structure.
            //-----------------------------------------------------------------
            frame_h_type ReadNextFrame( );
        };

        template < DECL >
        IFrameStreamWrapper< DECL_PARAMS >::IFrameStreamWrapper(
            buffer_type* Buffer )
            : IFrameStream( Buffer, SPEC )
        {
        }

        template < DECL >
        IFrameStreamWrapper< DECL_PARAMS >::IFrameStreamWrapper(
            bool AutoDelete, buffer_type* Buffer )
            : IFrameStream( AutoDelete, Buffer, SPEC )
        {
        }

        template < DECL >
        inline std::string
        IFrameStreamWrapper< DECL_PARAMS >::FrameLibraryName( ) const
        {
            return GetFrHeader( ).GetFrameLibraryName( );
        }

        template < DECL >
        typename IFrameStreamWrapper< DECL_PARAMS >::frame_h_type
        IFrameStreamWrapper< DECL_PARAMS >::ReadFrameH( frame_offset_type Frame,
                                                        INT_4U ContainerSet )
        {
            typedef frame_h_type ret_type;

            ret_type retval(
                boost::dynamic_pointer_cast< typename ret_type::element_type >(
                    readFrameHSubset( Frame, ContainerSet ) ) );

            return retval;
        }

        template < DECL >
        typename IFrameStreamWrapper< DECL_PARAMS >::fr_adc_data_type
        IFrameStreamWrapper< DECL_PARAMS >::ReadFrAdcData(
            frame_offset_type Frame, const std::string& Channel )
        {
            typedef fr_adc_data_type ret_type;

            ret_type retval(
                boost::dynamic_pointer_cast< typename ret_type::element_type >(
                    readFrAdcData( Frame, Channel ) ) );

            return retval;
        }

        template < DECL >
        typename IFrameStreamWrapper< DECL_PARAMS >::fr_adc_data_type
        IFrameStreamWrapper< DECL_PARAMS >::ReadFrAdcData(
            frame_offset_type Frame, INT_4U Channel )
        {
            typedef fr_adc_data_type ret_type;

            ret_type retval(
                boost::dynamic_pointer_cast< typename ret_type::element_type >(
                    readFrAdcData( Frame, Channel ) ) );

            return retval;
        }

        template < DECL >
        typename IFrameStreamWrapper< DECL_PARAMS >::fr_adc_data_type
        IFrameStreamWrapper< DECL_PARAMS >::ReadFrAdcStruct(
            frame_offset_type Frame, const std::string& Channel )
        {
            typedef fr_adc_data_type ret_type;

            ret_type retval(
                boost::dynamic_pointer_cast< typename ret_type::element_type >(
                    readFrAdcStruct( Frame, Channel ) ) );

            return retval;
        }

        template < DECL >
        typename IFrameStreamWrapper< DECL_PARAMS >::fr_adc_data_type
        IFrameStreamWrapper< DECL_PARAMS >::ReadFrAdcStruct(
            frame_offset_type Frame, INT_4U Channel )
        {
            typedef fr_adc_data_type ret_type;

            ret_type retval(
                boost::dynamic_pointer_cast< typename ret_type::element_type >(
                    readFrAdcStruct( Frame, Channel ) ) );

            return retval;
        }

        template < DECL >
        typename IFrameStreamWrapper< DECL_PARAMS >::fr_event_type
        IFrameStreamWrapper< DECL_PARAMS >::ReadFrEvent(
            frame_offset_type Frame, const std::string& Channel )
        {
            typedef fr_event_type ret_type;

            ret_type retval(
                boost::dynamic_pointer_cast< typename ret_type::element_type >(
                    readFrEvent( Frame, Channel ) ) );

            return retval;
        }

        template < DECL >
        typename IFrameStreamWrapper< DECL_PARAMS >::fr_event_type
        IFrameStreamWrapper< DECL_PARAMS >::ReadFrEvent(
            const std::string& EventType, fr_event_offset_type Offset )
        {
            typedef fr_event_type ret_type;

            ret_type retval(
                boost::dynamic_pointer_cast< typename ret_type::element_type >(
                    readFrEvent( EventType, Offset ) ) );

            return retval;
        }

        template < DECL >
        typename IFrameStreamWrapper< DECL_PARAMS >::fr_event_type
        IFrameStreamWrapper< DECL_PARAMS >::ReadFrEventStruct(
            frame_offset_type Frame, const std::string& Channel )
        {
            typedef fr_event_type ret_type;

            ret_type retval(
                boost::dynamic_pointer_cast< typename ret_type::element_type >(
                    readFrEventStruct( Frame, Channel ) ) );

            return retval;
        }

        template < DECL >
        typename IFrameStreamWrapper< DECL_PARAMS >::fr_proc_data_type
        IFrameStreamWrapper< DECL_PARAMS >::ReadFrProcData(
            frame_offset_type Frame, const std::string& Channel )
        {
            typedef fr_proc_data_type ret_type;

            ret_type retval(
                boost::dynamic_pointer_cast< typename ret_type::element_type >(
                    readFrProcData( Frame, Channel ) ) );

            return retval;
        }

        template < DECL >
        typename IFrameStreamWrapper< DECL_PARAMS >::fr_proc_data_type
        IFrameStreamWrapper< DECL_PARAMS >::ReadFrProcData(
            frame_offset_type Frame, INT_4U Channel )
        {
            typedef fr_proc_data_type ret_type;

            ret_type retval(
                boost::dynamic_pointer_cast< typename ret_type::element_type >(
                    readFrProcData( Frame, Channel ) ) );

            return retval;
        }

        template < DECL >
        typename IFrameStreamWrapper< DECL_PARAMS >::fr_proc_data_type
        IFrameStreamWrapper< DECL_PARAMS >::ReadFrProcStruct(
            frame_offset_type Frame, const std::string& Channel )
        {
            typedef fr_proc_data_type ret_type;

            ret_type retval(
                boost::dynamic_pointer_cast< typename ret_type::element_type >(
                    readFrProcStruct( Frame, Channel ) ) );

            return retval;
        }

        template < DECL >
        typename IFrameStreamWrapper< DECL_PARAMS >::fr_proc_data_type
        IFrameStreamWrapper< DECL_PARAMS >::ReadFrProcStruct(
            frame_offset_type Frame, INT_4U Channel )
        {
            typedef fr_proc_data_type ret_type;

            ret_type retval(
                boost::dynamic_pointer_cast< typename ret_type::element_type >(
                    readFrProcStruct( Frame, Channel ) ) );

            return retval;
        }

        template < DECL >
        typename IFrameStreamWrapper< DECL_PARAMS >::fr_raw_data_type
        IFrameStreamWrapper< DECL_PARAMS >::ReadFrRawData(
            frame_offset_type Frame )
        {
            typedef fr_raw_data_type ret_type;

            ret_type retval(
                boost::dynamic_pointer_cast< typename ret_type::element_type >(
                    readFrRawData( Frame ) ) );

            return retval;
        }

        template < DECL >
        typename IFrameStreamWrapper< DECL_PARAMS >::fr_ser_data_type
        IFrameStreamWrapper< DECL_PARAMS >::ReadFrSerData(
            frame_offset_type Frame, const std::string& Channel )
        {
            typedef fr_ser_data_type ret_type;

            ret_type retval(
                boost::dynamic_pointer_cast< typename ret_type::element_type >(
                    readFrSerData( Frame, Channel ) ) );

            return retval;
        }

        template < DECL >
        typename IFrameStreamWrapper< DECL_PARAMS >::fr_ser_data_type
        IFrameStreamWrapper< DECL_PARAMS >::ReadFrSerStruct(
            frame_offset_type Frame, const std::string& Channel )
        {
            typedef fr_ser_data_type ret_type;

            ret_type retval(
                boost::dynamic_pointer_cast< typename ret_type::element_type >(
                    readFrSerStruct( Frame, Channel ) ) );

            return retval;
        }

        template < DECL >
        typename IFrameStreamWrapper< DECL_PARAMS >::fr_sim_data_type
        IFrameStreamWrapper< DECL_PARAMS >::ReadFrSimData(
            frame_offset_type Frame, const std::string& Channel )
        {
            typedef fr_sim_data_type ret_type;

            ret_type retval(
                boost::dynamic_pointer_cast< typename ret_type::element_type >(
                    readFrSimData( Frame, Channel ) ) );

            return retval;
        }

        template < DECL >
        typename IFrameStreamWrapper< DECL_PARAMS >::fr_sim_data_type
        IFrameStreamWrapper< DECL_PARAMS >::ReadFrSimStruct(
            frame_offset_type Frame, const std::string& Channel )
        {
            typedef fr_sim_data_type ret_type;

            ret_type retval(
                boost::dynamic_pointer_cast< typename ret_type::element_type >(
                    readFrSimStruct( Frame, Channel ) ) );

            return retval;
        }

        template < DECL >
        typename IFrameStreamWrapper< DECL_PARAMS >::fr_sim_event_type
        IFrameStreamWrapper< DECL_PARAMS >::ReadFrSimEvent(
            frame_offset_type Frame, const std::string& Channel )
        {
            typedef fr_sim_event_type ret_type;

            ret_type retval(
                boost::dynamic_pointer_cast< typename ret_type::element_type >(
                    readFrSimEvent( Frame, Channel ) ) );

            return retval;
        }

        template < DECL >
        typename IFrameStreamWrapper< DECL_PARAMS >::fr_sim_event_type
        IFrameStreamWrapper< DECL_PARAMS >::ReadFrSimEvent(
            const std::string& SimEventType, fr_sim_event_offset_type Offset )
        {
            typedef fr_sim_event_type ret_type;

            ret_type retval(
                boost::dynamic_pointer_cast< typename ret_type::element_type >(
                    readFrSimEvent( SimEventType, Offset ) ) );

            return retval;
        }

        template < DECL >
        typename IFrameStreamWrapper< DECL_PARAMS >::fr_sim_event_type
        IFrameStreamWrapper< DECL_PARAMS >::ReadFrSimEventStruct(
            frame_offset_type Frame, const std::string& Channel )
        {
            typedef fr_sim_event_type ret_type;

            ret_type retval(
                boost::dynamic_pointer_cast< typename ret_type::element_type >(
                    readFrSimEventStruct( Frame, Channel ) ) );

            return retval;
        }

        template < DECL >
        typename IFrameStreamWrapper< DECL_PARAMS >::frame_h_type
        IFrameStreamWrapper< DECL_PARAMS >::ReadNextFrame( )
        {
            typedef frame_h_type ret_type;

            ret_type retval(
                boost::dynamic_pointer_cast< typename ret_type::element_type >(
                    readNextFrame( ) ) );

            return retval;
        }

#undef DECL_PARAMS
#undef DECL

    } // namespace Common
} // namespace FrameCPP

#endif /* FRAMECPP__COMMON__FrameStreamWrapper_HH */
