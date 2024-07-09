//
// LDASTools frameCPP - A library implementing the LIGO/Virgo frame
// specification
//
// Copyright (C) 2019 California Institute of Technology
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

#ifndef FrameCPP_VERSION_8__IMPL__FrameHClassicIO_HH
#define FrameCPP_VERSION_8__IMPL__FrameHClassicIO_HH


#if defined( __cplusplus )
#if !defined( SWIG )

#include <boost/make_shared.hpp>

#include "framecpp/Common/FrameH.hh"

#endif /* defined( SWIG ) */
#endif /* defined( __cplusplus ) */

#include "framecpp/Version8/impl/FrameHData.hh"

#if defined( __cplusplus )
#if !defined( SWIG )

#include "framecpp/Version8/FrEndOfFrame.hh"

namespace FrameCPP
{
    namespace Version_8
    {
        class FrameH;

        namespace FrameHImpl
        {
            template < typename T >
            class ClassicIO : public virtual Data,
                              public Common::TOCInfo,
                              public ObjectWithChecksum< Common::FrameH >
            {
            public:
                //-------------------------------------------------------
                //
                //-------------------------------------------------------
                ClassicIO( )
                    : ObjectWithChecksum< Common::FrameH >(
                          StructDescription( ) )
                {
                }

                ClassicIO( const Previous::FrameH& Source,
                           istream_type*           Stream )
                    : ObjectWithChecksum< Common::FrameH >(
                          StructDescription( ) )
                {
                    name = Source.GetName( );
                    run = Source.GetRun( );
                    frame = Source.GetFrame( );
                    GTime = Source.GetGTime( );
                    ULeapS = Source.GetULeapS( );
                    dt = Source.GetDt( );
                    dataQuality = Source.GetDataQuality( );
                    if ( Stream )
                    {
                        Stream->ReplaceRef(
                            RefType( ), Source.RefType( ), MAX_REF );
                        Stream->ReplaceRef(
                            RefUser( ), Source.RefUser( ), MAX_REF );
                        Stream->ReplaceRef(
                            RefDetectSim( ), Source.RefDetectSim( ), MAX_REF );
                        Stream->ReplaceRef( RefDetectProc( ),
                                            Source.RefDetectProc( ),
                                            MAX_REF );
                        Stream->ReplaceRef(
                            RefHistory( ), Source.RefHistory( ), MAX_REF );
                        Stream->ReplacePtr( AddressOfRawData( ),
                                            Source.AddressOfRawData( ),
                                            MAX_REF );
                        Stream->ReplaceRef(
                            RefProcData( ), Source.RefProcData( ), MAX_REF );
                        Stream->ReplaceRef(
                            RefSimData( ), Source.RefSimData( ), MAX_REF );
                        Stream->ReplaceRef(
                            RefEvent( ), Source.RefEvent( ), MAX_REF );
                        Stream->ReplaceRef(
                            RefSimEvent( ), Source.RefSimEvent( ), MAX_REF );
                        Stream->ReplaceRef( RefSummaryData( ),
                                            Source.RefSummaryData( ),
                                            MAX_REF );
                        Stream->ReplaceRef(
                            RefAuxData( ), Source.RefAuxData( ), MAX_REF );
                        Stream->ReplaceRef(
                            RefAuxTable( ), Source.RefAuxTable( ), MAX_REF );
                    }
                }

                //-----------------------------------------------------------------
                /// \brief The name structure name of this object.
                ///
                /// \return
                ///     The name of the structure as specified by the frame
                ///     specification.
                //-----------------------------------------------------------------
                virtual const char*
                ObjectStructName( ) const
                {
                    return StructName( );
                }

                //-----------------------------------------------------------------
                /// \brief Promote previous version of object to this version
                ///
                /// \param[in] Source
                ///     The frame specification version of the object.
                /// \param[in] Obj
                ///     The previous version of the object.
                /// \param[in] Stream
                ///     Stream from which the origional object was created.
                ///
                /// \return
                ///     A new instance of FrameH based on Obj
                //-----------------------------------------------------------------
                static promote_ret_type
                Promote( INT_2U           Source,
                         promote_arg_type Obj,
                         istream_type*    Stream )
                {
                    return ( Object::PromoteObject< Previous::FrameH, T >(
                        DATA_FORMAT_VERSION, Source, Obj, Stream ) );
                }

                //-----------------------------------------------------------------
                /// \brief The description of structure
                ///
                /// \return
                ///     A Description object which describes this structure as
                ///     specified by the frame specification.
                //-----------------------------------------------------------------
                static const Common::Description*
                StructDescription( )
                {
                    using Common::Description;

                    static Description ret;

                    if ( ret.size( ) == 0 )
                    {
                        //-----------------------------------------------
                        ret( FrSH( Data::FrameSpecName( ),
                                   Data::FrameSpecId( ),
                                   Data::FrameSpecDescription( ) ) );

                        //-----------------------------------------------
                        ret( FrSE( "name",
                                   "STRING",
                                   "Name of project or other experiment "
                                   "description" ) );
                        ret( FrSE(
                            "run",
                            "INT_4S",
                            "Run number(number<0 reserved for simulated data);"
                            " monotonic for experimental runs." ) );
                        ret( FrSE( "frame",
                                   "INT_4U",
                                   "Frame number, monotonically increasing "
                                   "until end of run,"
                                   " re-starting from 0 with each new run" ) );
                        ret( FrSE( "dataQuality",
                                   "INT_4U",
                                   "A logical 32-bit word to denote top level "
                                   "quality of data."
                                   " Lowest order bits are reserved in pairs "
                                   "for the various"
                                   " GW detectors" ) );
                        ret( FrSE( "GTimeS",
                                   "INT_4U",
                                   "Frame start time in GPS seconds" ) );
                        ret( FrSE( "GTimeN",
                                   "INT_4U",
                                   "Frame start time residual, integer "
                                   "nanoseconds" ) );
                        ret(
                            FrSE( "ULeapS",
                                  "INT_2U",
                                  "The integer number of leap seconds between "
                                  "GPS/TAI and UTC"
                                  " in the epoch when the frame is written" ) );
                        ret( FrSE(
                            "dt", "REAL_8", "Frame length in seconds." ) );

                        //-----------------------------------------------
                        ret( FrSE(
                            "type",
                            PTR_STRUCT::Desc( FrVect::StructName( ) ),
                            "Identifier for array used to store general info "
                            "like the event type." ) );
                        ret( FrSE( "user",
                                   PTR_STRUCT::Desc( FrVect::StructName( ) ),
                                   "Identifier for array for user-provided "
                                   "information." ) );
                        ret( FrSE(
                            "detectSim",
                            PTR_STRUCT::Desc( FrDetector::StructName( ) ),
                            "Identifier for array storing model or simulation "
                            "parameter data definition" ) );
                        ret(
                            FrSE( "detectProc",
                                  PTR_STRUCT::Desc( FrDetector::StructName( ) ),
                                  "Identifier for detector-derived data." ) );
                        ret( FrSE( "history",
                                   PTR_STRUCT::Desc( FrHistory::StructName( ) ),
                                   "Identifier for first history of "
                                   "post-processing with"
                                   " which frame may have been generated." ) );
                        ret( FrSE(
                            "rawData",
                            PTR_STRUCT::Desc(
                                rawData_type::element_type::StructName( ) ),
                            "Identifier for the raw data structure" ) );
                        ret( FrSE(
                            "procData",
                            PTR_STRUCT::Desc( FrProcData::StructName( ) ),
                            "Identifier for the first post-processed data" ) );
                        ret( FrSE( "simData",
                                   PTR_STRUCT::Desc( FrSimData::StructName( ) ),
                                   "Identifier for the first simulated data "
                                   "buffers" ) );
                        ret( FrSE(
                            "event",
                            PTR_STRUCT::Desc( FrEvent::StructName( ) ),
                            "Identifier for the first event structure" ) );
                        ret( FrSE(
                            "simEvent",
                            PTR_STRUCT::Desc( FrSimEvent::StructName( ) ),
                            "Identifier for the first simulated event data "
                            "structure." ) );
                        ret( FrSE( "summaryData",
                                   PTR_STRUCT::Desc( FrSummary::StructName( ) ),
                                   "Identifier for the first statistical "
                                   "summary data" ) );
                        ret(
                            FrSE( "auxData",
                                  PTR_STRUCT::Desc( FrVect::StructName( ) ),
                                  "Identifier for the first auxiliary data" ) );
                        ret( FrSE(
                            "auxTable",
                            PTR_STRUCT::Desc( FrTable::StructName( ) ),
                            "Identifier for the first auxiliary table data" ) );
                        //-----------------------------------------------
                        ret( FrSE( "chkSum",
                                   CheckSumDataClass( ),
                                   CheckSumDataComment( ) ) );
                    }

                    return &ret;
                }

            protected:
                typedef Common::FrameH::assign_stream_type assign_stream_type;

                //-----------------------------------------------------------------
                /// \brief Assign the contents of the instance
                ///
                /// \param[in] Stream
                ///     An input stream from which to read information for
                ///     the instance.
                ///
                /// \note
                ///     This has been hidden so programmers are not tempted to
                ///     bypass usage of IFrameStream as the input stream.
                //-----------------------------------------------------------------
                virtual void
                assign( assign_stream_type& Stream )
                {
                    io_name_type io_name;

                    Stream >> io_name >> run >> frame >> dataQuality >> GTime >>
                        ULeapS >> dt;

                    name = io_name;
                }

                //-------------------------------------------------------------------
                /// \brief Frame start time in seconds
                //-------------------------------------------------------------------
                virtual inline delta_t_normalized_type
                normalizedDeltaT( ) const
                {
                    return GetDt( );
                }
                //-------------------------------------------------------------------
                /// \brief Duration of the frame
                //-------------------------------------------------------------------
                virtual inline start_time_normalized_type
                normalizedStartTime( ) const
                {
                    return GetGTime( );
                }

                //-----------------------------------------------------------------
                /// \brief Number of bytes needed to write this structure
                ///
                /// \param[in] Stream
                ///     The stream from which to the object is being read or
                ///     written.
                ///
                /// \return
                ///     The number of bytes need to read or write this object.
                //-----------------------------------------------------------------
                cmn_streamsize_type
                pBytes( const Common::StreamBase& Stream ) const
                {
                    return (
                        io_name_type::Bytes( name ) // name
                        + sizeof( run ) // run;
                        + sizeof( frame ) // frame;
                        + sizeof( dataQuality ) // dataQuality;
                        + sizeof( GTimeS_type ) // GTime Seconds;
                        + sizeof( GTimeN_type ) // GTime Nanoeconds;
                        + sizeof( ULeapS ) // ULeapS;
                        + sizeof( dt ) // dt;
                        + ( Stream.PtrStructBytes( ) * MAX_REF ) // References
                    );
                }

                //-----------------------------------------------------------------
                /// \brief Virtual constructor.
                ///
                /// \param[in] Stream
                ///     The input stream from which to read the object.
                ///
                /// \return
                ///    A new instance of this object.
                //-----------------------------------------------------------------
                virtual self_type*
                pCreate( istream_type& Stream ) const
                {
                    T* obj( new T( ) );

                    io_name_type io_name;

                    Stream >> io_name >> obj->run >> obj->frame >>
                        obj->dataQuality >> obj->GTime >> obj->ULeapS >>
                        obj->dt >> obj->type >> obj->user >> obj->detectSim >>
                        obj->detectProc >> obj->history >> &( obj->rawData ) >>
                        obj->procData >> obj->simData >> obj->event >>
                        obj->simEvent >> obj->summaryData >> obj->auxData >>
                        obj->auxTable;

                    obj->name = io_name;

                    return ( obj );
                }

                //-----------------------------------------------------------------
                /// \brief Write the structure to the stream
                ///
                /// \param[in] Stream
                ///     The output stream where the object is to be written.
                //-----------------------------------------------------------------
                virtual void
                pWrite( ostream_type& Stream ) const
                {
                    Common::OStream::Pointer raw_data_ptr( rawData );

                    Stream << io_name_type( name ) << run << frame
                           << dataQuality << GTime << ULeapS << dt << type
                           << user << detectSim << detectProc << history
                           << raw_data_ptr << procData << simData << event
                           << simEvent << summaryData << auxData << auxTable;

                    boost::shared_ptr< FrEndOfFrame > eof =
                        boost::make_shared< FrEndOfFrame >( GetRun( ),
                                                            GetFrame( ) );
                    Stream.PushSingle( eof );
                }

                //-----------------------------------------------------------------
                /// \brief Limitted reading of the object
                ///
                /// \param[in] Stream
                ///     The input stream from which to read the object.
                /// \param[in] ElementMask
                ///     Mask of elements to read from the Stream
                //-----------------------------------------------------------------
                virtual void
                readSubset( istream_type& Stream, INT_4U ElementMask )
                {
                    if ( !( ElementMask & Common::FrameH::DETECT_SIM ) )
                    {
                        Stream.RemoveResolver( &( detectSim ), MAX_REF );
                    }
                    if ( !( ElementMask & Common::FrameH::DETECT_PROC ) )
                    {
                        Stream.RemoveResolver( &( detectProc ), MAX_REF );
                    }
                    if ( !( ElementMask & Common::FrameH::HISTORY ) )
                    {
                        Stream.RemoveResolver( &( history ), MAX_REF );
                    }
                    if ( !( ElementMask & Common::FrameH::TYPE ) )
                    {
                        Stream.RemoveResolver( &( type ), MAX_REF );
                    }
                    if ( !( ElementMask & Common::FrameH::USER ) )
                    {
                        Stream.RemoveResolver( &( user ), MAX_REF );
                    }
#if WORKING
                    if ( !( ElementMask & Common::FrameH::RAW_DATA ) )
                    {
                        Stream.RemoveResolver( &( rawData ), MAX_REF );
                    }
#endif /* WORKING */
                    Stream.RemoveResolver( &( procData ), MAX_REF );
                    Stream.RemoveResolver( &( simData ), MAX_REF );
                    Stream.RemoveResolver( &( event ), MAX_REF );
                    Stream.RemoveResolver( &( simEvent ), MAX_REF );
                    Stream.RemoveResolver( &( summaryData ), MAX_REF );
                    if ( !( ElementMask & Common::FrameH::AUX_DATA ) )
                    {
                        Stream.RemoveResolver( &( auxData ), MAX_REF );
                    }
                    if ( !( ElementMask & Common::FrameH::AUX_TABLE ) )
                    {
                        Stream.RemoveResolver( &( auxTable ), MAX_REF );
                    }
                }

            private:
                typedef STRING io_name_type;

                using Common::FrameSpec::Object::Create;

                //-----------------------------------------------------------------
                /// \brief Down grade an object
                ///
                /// \param[in] Target
                ///     The version of the frame specification to demote too.
                /// \param[in] Obj
                ///     The version of the object to demote.
                /// \param[in] Stream
                ///     The input stream from which the original object was
                ///     read.
                ///
                /// \return
                ///     An object of the previous generation.
                //-----------------------------------------------------------------
                virtual demote_ret_type
                demote( INT_2U          Target,
                        demote_arg_type Obj,
                        istream_type*   Stream ) const
                {
                    if ( Target >= DATA_FORMAT_VERSION )
                    {
                        return Obj;
                    }
                    try
                    {
                        //-------------------------------------------------------------------
                        // Copy non-reference information
                        //-------------------------------------------------------------------
                        // Do actual down conversion
                        boost::shared_ptr< Previous::FrameH > retval(
                            new Previous::FrameH( GetName( ),
                                                  GetRun( ),
                                                  GetFrame( ),
                                                  GetGTime( ),
                                                  GetULeapS( ),
                                                  GetDt( ),
                                                  GetDataQuality( ) ) );
                        if ( Stream )
                        {
                            //-----------------------------------------------------------------
                            // Modify references
                            //-----------------------------------------------------------------
                            Stream->ReplaceRef(
                                retval->RefType( ), RefType( ), MAX_REF );
                            Stream->ReplaceRef(
                                retval->RefUser( ), RefUser( ), MAX_REF );
                            Stream->ReplaceRef( retval->RefDetectSim( ),
                                                RefDetectSim( ),
                                                MAX_REF );
                            Stream->ReplaceRef( retval->RefDetectProc( ),
                                                RefDetectProc( ),
                                                MAX_REF );
                            Stream->ReplaceRef(
                                retval->RefHistory( ), RefHistory( ), MAX_REF );
                            Stream->ReplacePtr( retval->AddressOfRawData( ),
                                                AddressOfRawData( ),
                                                MAX_REF );
                            Stream->ReplaceRef( retval->RefProcData( ),
                                                RefProcData( ),
                                                MAX_REF );
                            Stream->ReplaceRef(
                                retval->RefSimData( ), RefSimData( ), MAX_REF );
                            Stream->ReplaceRef(
                                retval->RefEvent( ), RefEvent( ), MAX_REF );
                            Stream->ReplaceRef( retval->RefSimEvent( ),
                                                RefSimEvent( ),
                                                MAX_REF );
                            Stream->ReplaceRef( retval->RefSummaryData( ),
                                                RefSummaryData( ),
                                                MAX_REF );
                            Stream->ReplaceRef(
                                retval->RefAuxData( ), RefAuxData( ), MAX_REF );
                            Stream->ReplaceRef( retval->RefAuxTable( ),
                                                RefAuxTable( ),
                                                MAX_REF );
                        }
                        //-------------------------------------------------------------------
                        // Return demoted object
                        //-------------------------------------------------------------------
                        return retval;
                    }
                    catch ( ... )
                    {
                    }
                    throw Unimplemented(
                        "Object* FrameH::demote( Object* Obj ) const",
                        DATA_FORMAT_VERSION,
                        __FILE__,
                        __LINE__ );
                }

                //-----------------------------------------------------------------
                /// \brief Upgrade an object
                ///
                /// \param[in] Target
                ///     The version of the promoted frame specification.
                /// \param[in] Obj
                ///     The object to be promoted.
                /// \param[in] Stream
                ///     The input stream from which the original object was
                ///     read.
                ///
                /// \return
                ///     An object of this class.
                //-----------------------------------------------------------------
                virtual promote_ret_type
                promote( INT_2U           Target,
                         promote_arg_type Obj,
                         istream_type*    Stream ) const
                {
                    return ( Promote( Target, Obj, Stream ) );
                }

#if WORKING_VIRTUAL_TOCQUERY
            public:
                //-----------------------------------------------------------------
                /// \brief Answer requests for information as needed by TOC
                ///
                /// \param[in] InfoClass
                ///     Class of information being requested.
                //-----------------------------------------------------------------
                void TOCQuery( int InfoClass, ... ) const;
#else /* WORKING_VIRTUAL_TOCQUERY */
            protected:
                //-----------------------------------------------------------------
                /// \brief Answer requests for information as needed by TOC
                ///
                /// \param[in] InfoClass
                ///     Class of information being requested.
                /// \param[in] vl
                ///     Variable argument list of requested data.
                //-----------------------------------------------------------------
                virtual void vTOCQuery( int InfoClass, va_list vl ) const;
#endif /* WORKING_VIRTUAL_TOCQUERY */
            };

            template < typename T >
            void
            ClassicIO< T >::
#if WORKING_VIRTUAL_TOCQUERY
                TOCQuery( int InfoClass, ... ) const
#else /*  WORKING_VIRTUAL_TOCQUERY */
                vTOCQuery( int InfoClass, va_list vl ) const
#endif /*  WORKING_VIRTUAL_TOCQUERY */
            {
                using Common::TOCInfo;

#if WORKING_VIRTUAL_TOCQUERY
                va_list vl;
                va_start( vl, InfoClass );
#endif /*  WORKING_VIRTUAL_TOCQUERY */

                while ( InfoClass != TOCInfo::IC_EOQ )
                {
                    int data_type = va_arg( vl, int );
                    switch ( data_type )
                    {
                    case TOCInfo::DT_INT_2S:
                    {
                        INT_2S* data = va_arg( vl, INT_2S* );
                        switch ( InfoClass )
                        {
                        case TOCInfo::IC_ULEAP_S:
                            *data = GetULeapS( );
                            break;
                        default:
                            goto cleanup;
                            break;
                        }
                    }
                    break;
                    case TOCInfo::DT_INT_4S:
                    {
                        INT_4S* data = va_arg( vl, INT_4S* );
                        switch ( InfoClass )
                        {
                        case TOCInfo::IC_RUN:
                            *data = GetRun( );
                            break;
                        default:
                            goto cleanup;
                            break;
                        }
                    }
                    break;
                    case TOCInfo::DT_INT_4U:
                    {
                        INT_4U* data = va_arg( vl, INT_4U* );
                        switch ( InfoClass )
                        {
                        case TOCInfo::IC_DATA_QUALITY:
                            *data = GetDataQuality( );
                            break;
                        case TOCInfo::IC_GTIME_S:
                            *data = GetGTime( ).GetSeconds( );
                            break;
                        case TOCInfo::IC_GTIME_N:
                            *data = GetGTime( ).GetNanoseconds( );
                            break;
                        case TOCInfo::IC_FRAME:
                            *data = GetFrame( );
                            break;
                        default:
                            goto cleanup;
                            break;
                        }
                    }
                    break;
                    case TOCInfo::DT_REAL_8:
                    {
                        REAL_8* data = va_arg( vl, REAL_8* );
                        switch ( InfoClass )
                        {
                        case TOCInfo::IC_DT:
                            *data = GetDt( );
                            break;
                        default:
                            goto cleanup;
                            break;
                        }
                    }
                    break;
                    default:
                        // Stop processing
                        goto cleanup;
                    }
                    InfoClass = va_arg( vl, int );
                }
            cleanup:
#if WORKING_VIRTUAL_TOCQUERY
                va_end( vl )
#endif /*  WORKING_VIRTUAL_TOCQUERY */
                    ;
            }

        } // namespace FrameHImpl
    } // namespace Version_8
} // namespace FrameCPP

#endif /* defined( SWIG ) */
#endif /* defined( __cplusplus ) */

#endif /* FrameCPP_VERSION_8__IMPL__FrameHClassicIO_HH */
