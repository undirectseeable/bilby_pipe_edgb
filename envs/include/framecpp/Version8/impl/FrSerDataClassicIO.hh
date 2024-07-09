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

#ifndef FrameCPP_VERSION_8__IMPL__FrSerDataClassicIO_HH
#define FrameCPP_VERSION_8__IMPL__FrSerDataClassicIO_HH

#include "framecpp/Version8/impl/FrSerDataData.hh"

#include "framecpp/Version7/FrSerData.hh"

#if defined( __cplusplus )
#if !defined( SWIG )

namespace FrameCPP
{
    namespace Version_8
    {

        class FrSerData;

        namespace FrSerDataImpl
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

                ClassicIO( Previous::FrSerData& Source, istream_type* Stream )
                    : ObjectWithChecksum< Common::FrameSpec::Object >(
                          FrameSpecId( ), StructDescription( ) )
                {
                    name = Source.GetName( );
                    time = Source.GetTime( );
                    sampleRate = Source.GetSampleRate( );
                    data = Source.GetData( );

                    if ( Stream )
                    {
                        //-------------------------------------------------------------------
                        // Modify references
                        //-------------------------------------------------------------------
                        Stream->ReplaceRef(
                            RefSerial( ), Source.RefSerial( ), MAX_REF );
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
                    return Object::PromoteObject< Previous::FrSerData, T >(
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

                        ret( FrSE(
                            "name",
                            Description::Ascii< io_name_type >( ),
                            "Name of station producing serial data stream" ) );
                        ret( FrSE( "timeSec",
                                   Description::Ascii< io_timeSec_type >( ),
                                   "Time of data acquisition" ) );
                        ret( FrSE( "timeNsec",
                                   Description::Ascii< io_timeNsec_type >( ),
                                   "Frame start time residual" ) );
                        ret( FrSE( "sampleRate",
                                   Description::Ascii< sampleRate_type >( ),
                                   "Sample rate, samples/s" ) );
                        ret( FrSE( "data",
                                   Description::Ascii< io_data_type >( ),
                                   "Pointer to string for ASCII-based data" ) );

                        ret( FrSE( "serial",
                                   PTR_STRUCT::Desc( FrVect::StructName( ) ),
                                   "Identifier for serial data vector" ) );
                        ret( FrSE(
                            "table",
                            PTR_STRUCT::Desc( FrTable::StructName( ) ),
                            "Identifier for user-defined table structure" ) );

                        ret( FrSE( "next",
                                   PTR_STRUCT::Desc( Data::StructName( ) ) ) );

                        ret( FrSE( "chkSum",
                                   CheckSumDataClass( ),
                                   CheckSumDataComment( ) ) );
                    }

                    return &ret;
                }

#if WORKING_VIRTUAL_TOCQUERY
            public:
                /**
                 * \brief Answer requests for information as needed by TOC
                 *
                 * \param[in] InfoClass
                 *     Class of information being requested.
                 */
                virtual void
                TOCQuery( int InfoClass, ... ) const
#else
            protected:
                /**
                 * \brief Answer requests for information as needed by TOC
                 *
                 * \param[in] InfoClass
                 *     Class of information being requested.
                 * \param[in] vl
                 *     Variable argument list of requested data.
                 */
                virtual void
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
                        boost::shared_ptr< Previous::FrSerData > retval(
                            new Previous::FrSerData(
                                GetName( ), GetTime( ), GetSampleRate( ) ) );
                        retval->SetData( GetData( ) );
                        if ( Stream )
                        {
                            //-----------------------------------------------------------------
                            // Modify references
                            //-----------------------------------------------------------------
                            Stream->ReplaceRef(
                                retval->RefSerial( ), RefSerial( ), MAX_REF );
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
                        "Object* FrSerData::Demote( Object* Obj ) const",
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
                             sizeof( io_timeSec_type ) // timeSec
                             + sizeof( io_timeNsec_type ) // timeNsec
                             + sizeof( sampleRate ) +
                             io_data_type::Bytes( data ) +
                             Stream.PtrStructBytes( ) // serial
                             + Stream.PtrStructBytes( ) // table
                             + Stream.PtrStructBytes( ) // next
                    );
                }
                /**
                 * \brief Virtual constructor
                 *
                 * \param[in] Stream
                 *     The stream from which the earliest version of the
                 *     FrSerData structure was read.
                 *
                 * \return
                 *    A new instance of this object.
                 */
                virtual self_type*
                pCreate( istream_type& Stream ) const
                {
                    T* obj( new T( ) );

                    io_name_type     io_name;
                    io_data_type     io_data;
                    io_timeSec_type  io_timeSec;
                    io_timeNsec_type io_timeNsec;

                    Stream >> io_name >> io_timeSec >> io_timeNsec >>
                        obj->sampleRate >> io_data;

                    Stream >> obj->serial >> obj->table;

                    Stream.Next( obj );

                    obj->name = io_name;
                    obj->data = io_data;
                    obj->time = time_type( io_timeSec, io_timeNsec );

                    return ( obj );
                }

                virtual void
                pWrite( ostream_type& Stream ) const
                {
                    Stream << io_name_type( name )
                           << io_timeSec_type( time.GetSeconds( ) )
                           << io_timeNsec_type( time.GetNanoseconds( ) )
                           << sampleRate << io_data_type( data );
                    Stream << serial << table;
                    WriteNext( Stream );
                }

            private:
                typedef STRING io_name_type;
                typedef STRING io_data_type;
                typedef INT_4U io_timeSec_type;
                typedef INT_4U io_timeNsec_type;
            }; // class - ClassicIO

        } // namespace FrSerDataImpl
    } // namespace Version_8
} // namespace FrameCPP

#endif /* !defined( SWIG ) */
#endif /* defined( __cplusplus ) */

#endif /* FrameCPP_VERSION_8__IMPL__FrSerDataClassicIO_HH */
