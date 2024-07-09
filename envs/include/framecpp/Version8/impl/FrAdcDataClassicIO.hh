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

#ifndef FrameCPP_VERSION_8__IMPL__FrAdcDataClassicIO_HH
#define FrameCPP_VERSION_8__IMPL__FrAdcDataClassicIO_HH

#include "framecpp/Version8/impl/FrAdcDataData.hh"

#if defined( __cplusplus )
#if !defined( SWIG )

#include "framecpp/Common/Description.hh"
#include "framecpp/Common/FrameSpec.hh"
#include "framecpp/Common/FrameSpec.tcc"
#include "framecpp/Common/TOCInfo.hh"

#include "framecpp/Version7/FrAdcData.hh"

#include "framecpp/Version8/FrameSpec.hh"
#include "framecpp/Version8/FrSH.hh"
#include "framecpp/Version8/FrSE.hh"
#include "framecpp/Version8/PTR_STRUCT.hh"
#include "framecpp/Version8/STRING.hh"

namespace FrameCPP
{
    namespace Version_8
    {
        class FrAdcData;

        namespace FrAdcDataImpl
        {
            template < typename T >
            class ClassicIO
                : public virtual Data,
                  public Common::TOCInfo,
                  public ObjectWithChecksum< Common::FrameSpec::Object >
            {
            public:
                //-------------------------------------------------------
                //
                //-------------------------------------------------------
                ClassicIO( )
                    : ObjectWithChecksum< Common::FrameSpec::Object >(
                          FrameSpecId( ), StructDescription( ) )
                {
                }

                ClassicIO( Previous::FrAdcData& Source, istream_type* Stream )
                    : ObjectWithChecksum< Common::FrameSpec::Object >(
                          FrameSpecId( ), StructDescription( ) )
                {
                    name = Source.GetName( );
                    comment = Source.GetComment( );
                    channelGroup = Source.GetChannelGroup( );
                    channelNumber = Source.GetChannelNumber( );
                    nBits = Source.GetNBits( );
                    sampleRate = Source.GetSampleRate( );
                    bias = Source.GetBias( );
                    slope = Source.GetSlope( );
                    units = Source.GetUnits( );
                    fShift = Source.GetFShift( );
                    timeOffset = Source.GetTimeOffset( );
                    dataValid = Source.GetDataValid( );
                    phase = Source.GetPhase( );
                    if ( Stream )
                    {
                        Stream->ReplaceRef(
                            RefData( ), Source.RefData( ), Data::MAX_REF );
                        Stream->ReplaceRef(
                            RefAux( ), Source.RefAux( ), Data::MAX_REF );
                    }
                }

                /**
                 * \brief The name structure name of this object.
                 *
                 * \return
                 *     The name of the structure as specified by the frame
                 *     specification.
                 */
                virtual const char*
                ObjectStructName( ) const
                {
                    return StructName( );
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

                        ret( FrSE(
                            "name",
                            Common::Description::Ascii< name_type >( ),
                            "Channel name -- must be unique with the frame" ) );
                        ret(
                            FrSE( "comment",
                                  Common::Description::Ascii< comment_type >( ),
                                  "Comment" ) );
                        ret( FrSE(
                            "channelGroup",
                            Common::Description::Ascii< channelGroup_type >( ),
                            "Channel grouping number containing ADC" ) );
                        ret( FrSE(
                            "channelNumber",
                            Common::Description::Ascii< channelNumber_type >( ),
                            "Channel number" ) );
                        ret( FrSE( "nBits",
                                   Common::Description::Ascii< nBits_type >( ),
                                   "Number of bits in A/D output" ) );
                        ret( FrSE(
                            "bias",
                            Common::Description::Ascii< bias_type >( ),
                            "DC bias on channel (Units @ ADC counts = 0)" ) );
                        ret( FrSE( "slope",
                                   Common::Description::Ascii< slope_type >( ),
                                   "ADC calibration: input units/ct" ) );
                        ret( FrSE( "units",
                                   Common::Description::Ascii< units_type >( ),
                                   "ADC calibration: input units for slope. If "
                                   "dimensionless, then units == <NONE>, in "
                                   "CAPITALS (without<...>)." ) );
                        ret( FrSE(
                            "sampleRate",
                            Common::Description::Ascii< sampleRate_type >( ),
                            "Data Acquisition rate, samples/s" ) );
                        ret( FrSE(
                            "timeOffset",
                            Common::Description::Ascii< timeOffset_type >( ),
                            "Offset of 1st sample relative to the frame start "
                            "time (seconds). Must be positive and smaller than "
                            "the frame length" ) );
                        ret( FrSE( "fShift",
                                   Common::Description::Ascii< fShift_type >( ),
                                   "fShift is the frequency (in Hz) in the "
                                   "original data that corresponds to 0 Hz in "
                                   "the heterodyned series" ) );
                        ret( FrSE( "phase",
                                   Common::Description::Ascii< phase_type >( ),
                                   "Phase (in radiant) of heterodyning signal "
                                   "at start of dataset" ) );
                        ret( FrSE(
                            "dataValid",
                            Common::Description::Ascii< dataValid_type >( ),
                            "Data valid flag: dataValid = 0 -> ADC data valid; "
                            "dataValid != 0 -> ADC data suspect/not valid" ) );
                        //-----------------------------------------------
                        ret( FrSE( "data",
                                   PTR_STRUCT::Desc( "FrVect" ),
                                   "Identifier for vector of sampled data." ) );
                        ret( FrSE( "aux",
                                   PTR_STRUCT::Desc( "FrVect" ),
                                   "Identifier for vector for user-provided "
                                   "information; use is generic" ) );
                        //-----------------------------------------------
                        ret( FrSE( "next",
                                   PTR_STRUCT::Desc( Data::StructName( ) ),
                                   "Identifier for next ADC structure in the "
                                   "linked list." ) );
                        //-----------------------------------------------
                        ret( FrSE( "chkSum",
                                   CheckSumDataClass( ),
                                   CheckSumDataComment( ) ) );
                    }

                    return &ret;
                }

                /**
                 * \brief Promote previous version of object to this version
                 *
                 * \param[in] Source
                 *     The frame specification version of the object.
                 * \param[in] Obj
                 *     The previous version of the object.
                 * \param[in] Stream
                 *     Stream from which the origional object was created.
                 *
                 * \return
                 *     A new instance of FrAdcData based on Obj
                 */
                static promote_ret_type
                Promote( INT_2U           Source,
                         promote_arg_type Obj,
                         istream_type*    Stream )
                {
                    return Object::PromoteObject< Previous::FrAdcData, T >(
                        DATA_FORMAT_VERSION, Source, Obj, Stream );
                }

            protected:
                /**
                 * \brief Down grade an object
                 *
                 * \param[in] Target
                 *     The version of the frame specification to demote too.
                 * \param[in] Obj
                 *     The version of the object to demote.
                 * \param[in] Stream
                 *     The input stream from which the original object was read.
                 *
                 * \return
                 *     An object of the previous generation.
                 */
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
                        boost::shared_ptr< Previous::FrAdcData > retval(
                            new Previous::FrAdcData( GetName( ),
                                                     GetChannelGroup( ),
                                                     GetChannelNumber( ),
                                                     GetNBits( ),
                                                     GetSampleRate( ),
                                                     GetBias( ),
                                                     GetSlope( ),
                                                     GetUnits( ),
                                                     GetFShift( ),
                                                     GetTimeOffset( ),
                                                     GetDataValid( ),
                                                     GetPhase( ) ) );
                        retval->AppendComment( GetComment( ) );

                        if ( Stream )
                        {
                            //-----------------------------------------------------------------
                            // Modify references
                            //-----------------------------------------------------------------
                            Stream->ReplaceRef(
                                retval->RefData( ), RefData( ), MAX_REF );
                            Stream->ReplaceRef(
                                retval->RefAux( ), RefAux( ), MAX_REF );
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
                        "Object* FrAdcData::demote( Object* Obj ) const",
                        DATA_FORMAT_VERSION,
                        __FILE__,
                        __LINE__ );
                }

                /**
                 * \brief Upgrade an object
                 *
                 * \param[in] Target
                 *     The version of the frame specification to promote too.
                 * \param[in] Obj
                 *     The object to be promoted.
                 * \param[in] Stream
                 *     The input stream from which the original object was read.
                 *
                 * \return
                 *     An object of this class.
                 */
                virtual promote_ret_type
                promote( INT_2U           Target,
                         promote_arg_type Obj,
                         istream_type*    Stream ) const
                {
                    return Promote( Target, Obj, Stream );
                }

                /**
                 * \brief Number of bytes needed to write this structure
                 *
                 * \param[in] Stream
                 *     The stream from which to the object is being read or
                 *     written.
                 *
                 * \return
                 *     The number of bytes need to read or write this object.
                 */
                cmn_streamsize_type
                pBytes( const Common::StreamBase& Stream ) const
                {
                    return ( io_name_type::Bytes( name ) +
                             io_comment_type::Bytes( comment ) +
                             sizeof( channelGroup_type ) +
                             sizeof( channelNumber_type ) +
                             sizeof( nBits_type ) + sizeof( bias_type ) +
                             sizeof( slope_type ) +
                             io_units_type::Bytes( units ) +
                             sizeof( sampleRate_type ) +
                             sizeof( timeOffset_type ) + sizeof( fShift_type ) +
                             sizeof( phase_type ) + sizeof( dataValid_type ) +
                             Stream.PtrStructBytes( ) // data
                             + Stream.PtrStructBytes( ) // aux
                             + Stream.PtrStructBytes( ) // next
                    );
                }

                /**
                 * \brief Virtual constructor
                 *
                 * \param[in] Stream
                 *     The input stream from where the object is being read.
                 *
                 * \return
                 *     The newly allocated object.
                 */
                virtual self_type*
                pCreate( istream_type& Stream ) const
                {
                    T* obj( new T( ) );

                    io_name_type    io_name;
                    io_comment_type io_comment;
                    io_units_type   io_units;

                    Stream >> io_name >> io_comment >> obj->channelGroup >>
                        obj->channelNumber >> obj->nBits >> obj->bias >>
                        obj->slope >> io_units >> obj->sampleRate >>
                        obj->timeOffset >> obj->fShift >> obj->phase >>
                        obj->dataValid >> obj->data >> obj->aux;

                    Stream.Next( obj );

                    obj->name = io_name;
                    obj->comment = io_comment;
                    obj->units = io_units;

                    return ( obj );
                }
                /**
                 * \brief Write the structure to the stream
                 *
                 * \param[in] Stream
                 *     The output stream where the object is to be written.
                 */
                virtual void
                pWrite( ostream_type& Stream ) const
                {
                    try
                    {
                        Stream << io_name_type( name )
                               << io_comment_type( comment ) << channelGroup
                               << channelNumber << nBits << bias << slope
                               << io_units_type( units ) << sampleRate
                               << timeOffset << fShift << phase << dataValid
                               << data << aux;
                        WriteNext( Stream );
                    }
                    catch ( const std::exception& Exception )
                    {
                        std::cerr
                            << "DEBUG: Error Writing FrAdcData: " << GetName( )
                            << " exception: " << Exception.what( ) << std::endl;
                        throw; // rethrow
                    }
                }

            private:
                typedef STRING io_name_type;
                typedef STRING io_comment_type;
                typedef STRING io_units_type;

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
#if 0
                // using Data::Data;

                /**
                 * \brief Constructor
                 */
                ClassicIO( const name_type&   Name,
                           channelGroup_type  Group,
                           channelNumber_type Channel,
                           nBits_type         NBits,
                           sampleRate_type    SampleRate,
                           bias_type          Bias = DEFAULT_BIAS,
                           slope_type         Slope = DEFAULT_SLOPE,
                           const units_type&  Units = DEFAULT_UNITS( ),
                           fShift_type        FShift = DEFAULT_FSHIFT,
                           timeOffset_type    TimeOffset = DEFAULT_TIME_OFFSET,
                           dataValid_type     DataValid = DEFAULT_DATA_VALID,
                           phase_type         Phase = DEFAULT_PHASE )
                    : Data( Name,
                            Group,
                            Channel,
                            NBits,
                            SampleRate,
                            Bias,
                            Slope,
                            Units,
                            FShift,
                            TimeOffset,
                            DataValid,
                            Phase ),
                      ObjectWithChecksum< Common::FrameSpec::Object >(
                          FrameSpecId( ), StructDescription( ) )
                {
                  std::cerr << "DEBUG: Creating ClassicIO::Adc with name: " << Name << "(" << GetName() << ")" << std::endl;
                }

                virtual ~ClassicIO( )
               { 
                }

            protected:
#endif /* 0 */

            }; // class ClassicIO

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
                    case TOCInfo::DT_STRING_2:
                    {
                        STRING* data = va_arg( vl, STRING* );
                        switch ( InfoClass )
                        {
                        case TOCInfo::IC_NAME:
                            *data = GetName( );
                            break;
                        default:
                            goto cleanup;
                            break;
                        }
                    }
                    break;
                    case TOCInfo::DT_INT_2U:
                    {
                        INT_2U* data = va_arg( vl, INT_2U* );
                        switch ( InfoClass )
                        {
                        case TOCInfo::IC_DATA_VALID:
                            *data = GetDataValid( );
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
                        case TOCInfo::IC_CHANNEL_ID:
                            *data = GetChannelNumber( );
                            break;
                        case TOCInfo::IC_GROUP_ID:
                            *data = GetChannelGroup( );
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
        } // namespace FrAdcDataImpl
    } // namespace Version_8
} // namespace FrameCPP

#endif /* ! defined(SWIG) */
#endif /* defined( __cplusplus ) */

#endif /* FrameCPP_VERSION_8__IMPL__FrAdcDataClassicIO_HH */
