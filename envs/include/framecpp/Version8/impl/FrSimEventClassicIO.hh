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

#ifndef FrameCPP_VERSION_8__IMPL__FrSimEventClassicIO_HH
#define FrameCPP_VERSION_8__IMPL__FrSimEventClassicIO_HH

#include "framecpp/Version8/impl/FrSimEventData.hh"

#if defined( __cplusplus )

namespace FrameCPP
{
    namespace Version_8
    {
        class FrSimEvent;

        namespace FrSimEventImpl
        {
            inline FrameCPP::Common::OStream&
            operator<<( FrameCPP::Common::OStream&  Stream,
                        const Data::ParamList_type& Data )
            {
                Stream << Data::nParam_type( Data.size( ) );
                for ( auto p : Data )
                {
                    Stream << p.second; // parameters
                }
                for ( auto p : Data )
                {
                    Stream << STRING( p.first );
                }
                return ( Stream );
            }

            inline FrameCPP::Common::IStream&
            operator>>( FrameCPP::Common::IStream& Stream,
                        Data::ParamList_type&      Data )
            {
                Data::nParam_type nParam;

                Stream >> nParam;

                Data.resize( nParam );
                for ( auto& p : Data )
                {
                    Stream >> p.second; // parameters
                }
                for ( auto& p : Data )
                {
                    STRING shadow;

                    Stream >> shadow;
                    p.first.swap( shadow );
                }
                return ( Stream );
            }

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

                ClassicIO( const Previous::FrSimEvent& Source,
                           istream_type*               Stream )
                    : ObjectWithChecksum< Common::FrameSpec::Object >(
                          FrameSpecId( ), StructDescription( ) )
                {
                    name = Source.GetName( );
                    comment = Source.GetComment( );
                    inputs = Source.GetInputs( );
                    GTime = Source.GetGTime( );
                    timeBefore = Source.GetTimeBefore( );
                    timeAfter = Source.GetTimeAfter( );
                    amplitude = Source.GetAmplitude( );

                    Params.resize( Source.GetParam( ).size( ) );

                    auto param_new = Params.begin( );
                    for ( auto param_old : Source.GetParam( ) )
                    {
                        param_new->first = param_old.first;
                        param_new->second = param_old.second;
                        ++param_new;
                    }

                    if ( Stream )
                    {
                        //-------------------------------------------------------------------
                        // Modify references
                        //-------------------------------------------------------------------
                        Stream->ReplaceRef( RefData( ),
                                            Source.RefData( ),
                                            Previous::FrSimEvent::MAX_REF );
                        Stream->ReplaceRef( RefTable( ),
                                            Source.RefTable( ),
                                            Previous::FrSimEvent::MAX_REF );
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

                /**
                 * \brief The description of structure
                 *
                 * \return
                 *     A Description object which describes this structure as
                 *     specified by the frame specification.
                 */
                static const Common::Description*
                StructDescription( )
                {
                    using Common::Description;

                    static Description ret;

                    if ( ret.size( ) == 0 )
                    {
                        ret( FrSH( Data::FrameSpecName( ),
                                   Data::FrameSpecId( ),
                                   Data::FrameSpecDescription( ) ) );

                        ret( FrSE( "name", "STRING", "Name of event." ) );
                        ret( FrSE(
                            "comment", "STRING", "Descriptor of event" ) );
                        ret( FrSE(
                            "inputs",
                            "STRING",
                            "Input channels and filter parameters to event "
                            "process." ) );
                        ret( FrSE(
                            "GTimeS",
                            "INT_4U",
                            "GPS time in seconds corresponding to reference "
                            "vale of event,"
                            " as defined by the search algorigthm." ) );
                        ret( FrSE( "GTimeN",
                                   "INT_4U",
                                   "GPS time in residual nanoseconds relative "
                                   "to GTimeS" ) );
                        ret( FrSE( "timeBefore",
                                   "REAL_4",
                                   "Signal duration before "
                                   "(GTimeS.GTimeN)(seconds)" ) );
                        ret( FrSE( "timeAfter",
                                   "REAL_4",
                                   "Signal duration after "
                                   "(GTimeS.GTimeN)(seconds)" ) );
                        ret( FrSE( "amplitude",
                                   "REAL_4",
                                   "Continuouis output amplitude returned by "
                                   "event" ) );
                        ret( FrSE( "nParam",
                                   "INT_2U",
                                   "Number of additional event parameters" ) );
                        ret( FrSE( "parameters",
                                   "REAL_8[nParam]",
                                   "Array of additional event paraameters(size "
                                   "of nParam)" ) );
                        ret( FrSE(
                            "parameterNames",
                            "STRING[nParam]",
                            "Array of parameter names (size of nParam)." ) );
                        ret( FrSE( "data",
                                   PTR_STRUCT::Desc( "FrVect" ),
                                   "" ) );
                        ret( FrSE( "table",
                                   PTR_STRUCT::Desc( "FrTable" ),
                                   "" ) );
                        ret( FrSE( "next",
                                   PTR_STRUCT::Desc( Data::StructName( ) ),
                                   "" ) );

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
                 *     A new instance of FrSimEvent based on Obj
                 */
                static promote_ret_type Promote( INT_2U           Source,
                                                 promote_arg_type Obj,
                                                 istream_type*    Stream );

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
                        Previous::FrSimEvent::ParamList_type params;
                        for ( ParamList_type::const_iterator
                                  cur = GetParam( ).begin( ),
                                  last = GetParam( ).end( );
                              cur != last;
                              ++cur )
                        {
                            params.push_back( Previous::FrSimEvent::Param_type(
                                cur->first, cur->second ) );
                        }
                        // Do actual down conversion
                        boost::shared_ptr< Previous::FrSimEvent > retval(
                            new Previous::FrSimEvent( GetName( ),
                                                      GetComment( ),
                                                      GetInputs( ),
                                                      GetGTime( ),
                                                      GetTimeBefore( ),
                                                      GetTimeAfter( ),
                                                      GetAmplitude( ),
                                                      params ) );
                        if ( Stream )
                        {
                            //-----------------------------------------------------------------
                            // Modify references
                            //-----------------------------------------------------------------
                            Stream->ReplaceRef(
                                retval->RefData( ), RefData( ), MAX_REF );
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
                        "Object* FrSimEvent::demote( Object* Obj ) const",
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
                    cmn_streamsize_type param_size{ 0 };
                    param_size += sizeof( INT_2U );
                    for ( auto i : Params )
                    {
                        param_size +=
                            io_name_type::Bytes( i.first ) + sizeof( i.second );
                    }
                    return io_name_type::Bytes( name ) +
                        io_comment_type::Bytes( comment ) +
                        io_inputs_type::Bytes( inputs ) +
                        sizeof( INT_4U ) // GTimeS
                        + sizeof( INT_4U ) // GTimeN
                        + sizeof( timeBefore ) + sizeof( timeAfter ) +
                        sizeof( amplitude ) + param_size +
                        Stream.PtrStructBytes( ) // data
                        + Stream.PtrStructBytes( ) // table
                        + Stream.PtrStructBytes( ) // next
                        ;
                }

                /**
                 * \brief Virtual constructor.
                 *
                 * \param[in] Stream
                 *     The input stream from which to read the object.
                 *
                 * \return
                 *    A new instance of this object.
                 */
                virtual self_type*
                pCreate( istream_type& Stream ) const
                {
                    T* obj( new T( ) );

                    io_name_type    io_name;
                    io_comment_type io_comment;
                    io_inputs_type  io_inputs;

                    Stream >> io_name >> io_comment >> io_inputs >>
                        obj->GTime >> obj->timeBefore >> obj->timeAfter >>
                        obj->amplitude >> obj->Params >> obj->data >>
                        obj->table;

                    Stream.Next( obj );

                    obj->name = io_name;
                    obj->comment = io_comment;
                    obj->inputs = io_inputs;

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
                    Stream << io_name_type( name ) << io_comment_type( comment )
                           << io_inputs_type( inputs ) << GTime << timeBefore
                           << timeAfter << amplitude << Params << data << table;
                    WriteNext( Stream );
                }

                /**
                 * \brief Answer requests for information as needed by TOC
                 *
                 * \param[in] InfoClass
                 *     Class of information being requested.
                 * \param[in] vl
                 *     Variable argument list of requested data.
                 */
                virtual void
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
                        case TOCInfo::DT_INT_4U:
                        {
                            INT_4U* data = va_arg( vl, INT_4U* );
                            switch ( InfoClass )
                            {
                            case TOCInfo::IC_GTIME_S:
                                *data = GetGTime( ).GetSeconds( );
                                break;
                            case TOCInfo::IC_GTIME_N:
                                *data = GetGTime( ).GetNanoseconds( );
                                break;
                            default:
                                goto cleanup;
                                break;
                            }
                        }
                        break;
                        case TOCInfo::DT_REAL_4:
                        {
                            REAL_4* data = va_arg( vl, REAL_4* );
                            switch ( InfoClass )
                            {
                            case TOCInfo::IC_AMPLITUDE:
                                *data = GetAmplitude( );
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
                            case TOCInfo::IC_AMPLITUDE:
                                *data = GetAmplitude( );
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

            private:
                typedef STRING io_name_type;
                typedef STRING io_comment_type;
                typedef STRING io_inputs_type;
            }; // class ClassicIO

            template < typename T >
            typename ClassicIO< T >::promote_ret_type
            ClassicIO< T >::Promote( INT_2U           Source,
                                     promote_arg_type Obj,
                                     istream_type*    Stream )
            {
                return Object::PromoteObject< Previous::FrSimEvent, T >(
                    DATA_FORMAT_VERSION, Source, Obj, Stream );
            }

        } // namespace FrSimEventImpl
    } // namespace Version_8
} // namespace FrameCPP

#endif /* defined( __cplusplus ) */

#endif /* FrameCPP_VERSION_8__IMPL__FrSimEventClassicIO_HH */
