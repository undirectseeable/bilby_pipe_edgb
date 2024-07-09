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

#ifndef FrameCPP_VERSION_8__IMPL__FrSimDataClassicIO_HH
#define FrameCPP_VERSION_8__IMPL__FrSimDataClassicIO_HH

#include "framecpp/Version8/impl/FrSimDataData.hh"

#if defined( __cplusplus ) && !defined( SWIG )

#include "framecpp/Version7/FrSimData.hh"

namespace FrameCPP
{
    namespace Version_8
    {

        class FrSimData;

        namespace FrSimDataImpl
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

                ClassicIO( Previous::FrSimData& Source, istream_type* Stream )
                    : ObjectWithChecksum< Common::FrameSpec::Object >(
                          FrameSpecId( ), StructDescription( ) )
                {
                  name = Source.GetName( );
                  comment = Source.GetComment( );
                  sampleRate = Source.GetSampleRate( );
                  timeOffset = Source.GetTimeOffset( );
                  fShift = Source.GetFShift( );
                  phase = Source.GetPhase( );

                  if ( Stream )
                    {
                      //-------------------------------------------------------------------
                      // Modify references
                      //-------------------------------------------------------------------
                      Stream->ReplaceRef(
                                         RefData( ), Source.RefData( ), MAX_REF );
                      Stream->ReplaceRef(
                                         RefInput( ), Source.RefInput( ), MAX_REF );
                      Stream->ReplaceRef(
                                         RefTable( ), Source.RefTable( ), MAX_REF );
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
                 *     A new instance of FrameH based on Obj
                 */
                inline static promote_ret_type
                Promote( INT_2U           Source,
                         promote_arg_type Obj,
                         istream_type*    Stream )
                {
                    return Object::PromoteObject< Previous::FrSimData, T >(
                        DATA_FORMAT_VERSION, Source, Obj, Stream );
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
                        ret( FrSH( Data::StructName( ),
                                   Data::FrameSpecId( ),
                                   Data::FrameSpecDescription( ) ) );

                        ret( FrSE( "name", "STRING" ) );
                        ret( FrSE( "comment", "STRING" ) );
                        ret( FrSE( "sampleRate",
                                   Description::Ascii< sampleRate_type >( ),
                                   "Simulated data sample rate, samples/s" ) );
                        ret( FrSE( "timeOffset",
                                   Description::Ascii< timeOffset_type >( ),
                                   "Offset of 1sst sample relative to the "
                                   "frame start time (seconds)."
                                   "Must be positive and smaller than the "
                                   "frame length." ) );
                        ret( FrSE(
                            "fShift",
                            Description::Ascii< fShift_type >( ),
                            "fShift is the frequency in the original data "
                            "that corresponds to 0 Hz in teh heterodyned "
                            "series." ) );
                        ret( FrSE( "phase",
                                   Description::Ascii< phase_type >( ),
                                   "Phase of heterodyning signal at start of "
                                   "dataset." ) );

                        ret( FrSE( "data",
                                   PTR_STRUCT::Desc( FrVect::StructName( ) ),
                                   "Identifier of array of simulated data." ) );
                        ret( FrSE( "input",
                                   PTR_STRUCT::Desc( FrVect::StructName( ) ),
                                   "Identifier for input parameters for "
                                   "simulation." ) );
                        ret( FrSE( "table",
                                   PTR_STRUCT::Desc( FrTable::StructName( ) ),
                                   "Identifier for table data structure." ) );

                        ret( FrSE( "next",
                                   PTR_STRUCT::Desc( Data::StructName( ) ),
                                   "Identifier for next simulated data "
                                   "structure in the linked list" ) );

                        ret( FrSE( "chkSum",
                                   CheckSumDataClass( ),
                                   CheckSumDataComment( ) ) );
                    }

                    return &ret;
                }

#if WORKING_VIRTUAL_TOCQUERY
            public:
                //-----------------------------------------------------------------
                /// \brief Answer requests for information as needed by TOC
                ///
                /// \param[in] InfoClass
                ///     Class of information being requested.
                //-----------------------------------------------------------------
                virtual void
                TOCQuery( int InfoClass, ... ) const

#else
            protected:
                //-----------------------------------------------------------------
                /// \brief Answer requests for information as needed by TOC
                ///
                /// \param[in] InfoClass
                ///     Class of information being requested.
                /// \param[in] vl
                ///     Variable argument list of requested data.
                //-----------------------------------------------------------------
                virtual void
                vTOCQuery( int InfoClass, va_list vl ) const
#endif /* ! WORKING_VIRTUAL_TOCQUERY */
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

            protected:
                //-----------------------------------------------------------------
                /// \brief Demotes object to previous version of the frame spec
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
                demote( INT_2U           Target,
                        demote_arg_type  Obj,
                        Common::IStream* Stream ) const
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
                        boost::shared_ptr< Previous::FrSimData > retval(
                            new Previous::FrSimData( GetName( ),
                                                     GetComment( ),
                                                     GetSampleRate( ),
                                                     GetFShift( ),
                                                     GetPhase( ),
                                                     GetTimeOffset( ) ) );
                        if ( Stream )
                        {
                            //-----------------------------------------------------------------
                            // Modify references
                            //-----------------------------------------------------------------
                            Stream->ReplaceRef(
                                retval->RefData( ), RefData( ), MAX_REF );
                            Stream->ReplaceRef(
                                retval->RefInput( ), RefInput( ), MAX_REF );
                            Stream->ReplaceRef(
                                retval->RefTable( ), RefTable( ), MAX_REF );
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
                        "Object* FrSimData::demote( Object* Obj ) const",
                        DATA_FORMAT_VERSION,
                        __FILE__,
                        __LINE__ );
                }

                //-----------------------------------------------------------------
                /// \brief Promotes object to another version of the frame spec
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
                ///     An object promoted to the next generation.
                //-----------------------------------------------------------------
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
                             sizeof( sampleRate_type ) +
                             sizeof( timeOffset_type ) + sizeof( fShift_type ) +
                             sizeof( phase_type ) +
                             Stream.PtrStructBytes( ) // data
                             + Stream.PtrStructBytes( ) // input
                             + Stream.PtrStructBytes( ) // table
                             + Stream.PtrStructBytes( ) // next
                    );
                }
                //-----------------------------------------------------------------
                /// \brief Virtual constructor
                ///
                /// \param[in] Stream
                ///     The input stream from where the object is being read.
                //-----------------------------------------------------------------
                virtual self_type*
                pCreate( istream_type& Stream ) const
                {
                    T* obj( new T( ) );

                    io_name_type    io_name;
                    io_comment_type io_comment;

                    Stream >> io_name >> io_comment >> obj->sampleRate >>
                        obj->timeOffset >> obj->fShift >> obj->phase;

                    Stream >> obj->data >> obj->input >> obj->table;

                    Stream.Next( obj );

                    obj->name = io_name;
                    obj->comment = io_comment;

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
                    Stream << io_name_type( name ) << io_comment_type( comment )
                           << sampleRate << timeOffset << fShift << phase;
                    Stream << data << input << table;
                    WriteNext( Stream );
                }

            private:
                typedef STRING io_name_type;
                typedef STRING io_comment_type;
            }; // class ClassicIO
        } // namespace FrSimDataImpl
    } // namespace Version_8
} // namespace FrameCPP

#endif /* defined( __cplusplus ) && !defined( SWIG ) */

#endif /* FrameCPP_VERSION_8__IMPL__FrSimDataClassicIO_HH */
