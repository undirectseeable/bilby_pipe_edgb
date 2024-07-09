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

#ifndef FrameCPP_VERSION_8__IMPL__FrProcDataClassicIO_HH
#define FrameCPP_VERSION_8__IMPL__FrProcDataClassicIO_HH

#include "framecpp/Version8/impl/FrProcDataData.hh"

#if defined( __cplusplus )
#if !defined( SWIG )

#include "framecpp/Common/Description.hh"
#include "framecpp/Common/FrameSpec.hh"
#include "framecpp/Common/FrameSpec.tcc"
#include "framecpp/Common/TOCInfo.hh"

#include "framecpp/Version8/FrameSpec.hh"
#include "framecpp/Version8/FrSH.hh"
#include "framecpp/Version8/FrSE.hh"
#include "framecpp/Version8/PTR_STRUCT.hh"
#include "framecpp/Version8/STRING.hh"

#endif /* defined( SWIG ) */
#endif /* defined( __cplusplus ) */

#if defined( __cplusplus )
#if !defined( SWIG )

namespace FrameCPP
{
    namespace Version_8
    {
        class FrProcData;

        namespace FrProcDataImpl
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

                ClassicIO( Previous::FrProcData& Source, istream_type* Stream )
                    : ObjectWithChecksum< Common::FrameSpec::Object >(
                          FrameSpecId( ), StructDescription( ) )
                {
                    name = Source.GetName( );
                    comment = Source.GetComment( );
                    type = Source.GetType( );
                    subType = Source.GetSubType( );
                    timeOffset = Source.GetTimeOffset( );
                    tRange = Source.GetTRange( );
                    fShift = Source.GetFShift( );
                    phase = Source.GetPhase( );
                    fRange = Source.GetFRange( );
                    BW = Source.GetBW( );
                    auxParam.resize( Source.GetAuxParam( ).size( ) );
                    auto nextParam = auxParam.begin( );
                    for ( auto param : Source.GetAuxParam( ) )
                    {
                        // auxParam = Source.GetAuxParam( );
                        nextParam->auxParamName = param.auxParamName;
                        nextParam->auxParam = param.auxParam;
                        ++nextParam;
                    }

                    if ( Stream )
                    {
                        Stream->ReplaceRef(
                            RefData( ), Source.RefData( ), Data::MAX_REF );
                        Stream->ReplaceRef(
                            RefAux( ), Source.RefAux( ), Data::MAX_REF );
                        Stream->ReplaceRef(
                            RefTable( ), Source.RefTable( ), Data::MAX_REF );
                        Stream->ReplaceRef( RefHistory( ),
                                            Source.RefHistory( ),
                                            Data::MAX_REF );
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
                    return Object::PromoteObject< Previous::FrProcData, T >(
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
                        using Common::Description;

                        //-----------------------------------------------
                        ret( FrSH( Data::FrameSpecName( ),
                                   Data::FrameSpecId( ),
                                   Data::FrameSpecDescription( ) ) );

                        ret( FrSE( "name",
                                   Description::Ascii< io_name_type >( ),
                                   "Data or channel name" ) );
                        ret( FrSE( "comment",
                                   Description::Ascii< io_comment_type >( ),
                                   "Comment" ) );
                        ret( FrSE( "type",
                                   Description::Ascii< type_type >( ),
                                   "Type of data object" ) );
                        ret( FrSE(
                            "subType",
                            Description::Ascii< subType_type >( ),
                            "Subtype for f-Series(TDBD for other types)" ) );
                        ret( FrSE( "timeOffset",
                                   Description::Ascii< timeOffset_type >( ),
                                   "Offset of 1st sample relative to the frame "
                                   "start time" ) );
                        ret(
                            FrSE( "tRange",
                                  Description::Ascii< tRange_type >( ),
                                  "Duration of sampled data (tStop-tStart)" ) );
                        ret( FrSE(
                            "fShift",
                            Description::Ascii< fShift_type >( ),
                            "fShift is the requency iin the original data that "
                            "corresponds to 0Hz in the heerodyned series." ) );
                        ret( FrSE( "phase",
                                   Description::Ascii< phase_type >( ),
                                   "Phase of heterodyning signal at start of "
                                   "dataset (radians, 0 if unknown)" ) );
                        ret( FrSE(
                            "fRange",
                            Description::Ascii< fRange_type >( ),
                            "Frequency range (=fMax-fMin, 0 if unknown)" ) );
                        ret( FrSE( "BW",
                                   Description::Ascii< BW_type >( ),
                                   "Resolution bandwidth" ) );
                        ret( FrSE( "nAuxParam",
                                   "INT_2U",
                                   "Number of auxiliary parameters" ) );
                        ret( FrSE( "auxParam",
                                   "REAL_8[nAuxParam]",
                                   "Array of auxiliary parameters (size of "
                                   "nAuxParam)." ) );
                        ret( FrSE( "auxParamNames",
                                   "STRING[nAuxParam]",
                                   "Array of auxiliary parameter names (size "
                                   "of nAuxParam)." ) );

                        ret( FrSE( "data",
                                   PTR_STRUCT::Desc( FrVect::StructName( ) ),
                                   "Data vector. The data vector for single "
                                   "dimensional types (t-Series fand f-Series) "
                                   "must have a single dimension" ) );
                        ret( FrSE( "aux",
                                   PTR_STRUCT::Desc( FrVect::StructName( ) ),
                                   "Auxiliary data; use is generic." ) );
                        ret( FrSE( "table",
                                   PTR_STRUCT::Desc( FrTable::StructName( ) ),
                                   "Parameter table" ) );
                        ret( FrSE( "history",
                                   PTR_STRUCT::Desc( FrHistory::StructName( ) ),
                                   "Channel history" ) );

                        ret(
                            FrSE( "next",
                                  PTR_STRUCT::Desc( Data::StructName( ) ),
                                  "Identifier for next FrProcData structure in "
                                  "the linked list" ) );

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
                        /// \todo See if the actual sample rate can be computed
                        Previous::GPSTime t;
                        t += GetTimeOffset( );
                        boost::shared_ptr< Previous::FrProcData > retval(
                            new Previous::FrProcData( GetName( ),
                                                      GetComment( ),
                                                      GetType( ),
                                                      GetSubType( ),
                                                      GetTimeOffset( ),
                                                      GetTRange( ),
                                                      GetFShift( ),
                                                      GetPhase( ),
                                                      GetFRange( ),
                                                      GetBW( ) ) );
                        if ( Stream )
                        {
                            //-----------------------------------------------------------------
                            // Modify references
                            //-----------------------------------------------------------------
                            Stream->ReplaceRef(
                                retval->RefAux( ), RefAux( ), MAX_REF );
                            Stream->ReplaceRef(
                                retval->RefData( ), RefData( ), MAX_REF );
                            Stream->ReplaceRef(
                                retval->RefTable( ), RefTable( ), MAX_REF );
                            Stream->ReplaceRef(
                                retval->RefHistory( ), RefHistory( ), MAX_REF );
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
                        "Object* FrProcData::demote( Object* Obj ) const",
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
                    cmn_streamsize_type auxParamBytes{ sizeof( INT_2U ) };
                    for ( auto element : Data::auxParam )
                    {
                        auxParamBytes +=
                            ( STRING::Bytes( element.auxParamName ) +
                              sizeof( element.auxParam ) );
                    }

                    return ( io_name_type::Bytes( name ) +
                             io_comment_type::Bytes( comment ) +
                             sizeof( type ) + sizeof( subType ) +
                             sizeof( timeOffset ) + sizeof( tRange ) +
                             sizeof( fShift ) + sizeof( phase ) +
                             sizeof( fRange ) + sizeof( BW ) + auxParamBytes +
                             Stream.PtrStructBytes( ) // data
                             + Stream.PtrStructBytes( ) // aux
                             + Stream.PtrStructBytes( ) // table
                             + Stream.PtrStructBytes( ) // history
                             + Stream.PtrStructBytes( ) // next
                    );
                }

                /**
                 * \brief Virtual constructor
                 *
                 * \param[in] Stream
                 *     The stream from which the earliest version of the
                 *     FrProcData structure was read.
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

                    Stream >> io_name >> io_comment >> obj->type >>
                        obj->subType >> obj->timeOffset >> obj->tRange >>
                        obj->fShift >> obj->phase >> obj->fRange >> obj->BW;
                    {
                        INT_2U size;
                        Stream >> size;
                        obj->auxParam.resize( size );
                        for ( auto& element : obj->auxParam )
                        {
                            Stream >> element.auxParam;
                        }
                        for ( auto& element : obj->auxParam )
                        {
                            STRING value;

                            Stream >> value;
                            element.auxParamName = value;
                        }
                    }
                    Stream >> obj->data >> obj->aux >> obj->table >>
                        obj->history;

                    Stream.Next( obj );

                    obj->name = io_name;
                    obj->comment = io_comment;

                    return ( obj );
                }

                /**
                 * \brief Virtual constructor
                 *
                 * \param[in] Stream
                 *     The input stream from where the object is being read.
                 */
                virtual void
                pWrite( ostream_type& Stream ) const
                {
                    try
                    {
                        Stream << io_name_type( name )
                               << io_comment_type( comment ) << type << subType
                               << timeOffset << tRange << fShift << phase
                               << fRange << BW;
                        // auxParam
                        Stream << INT_2U( auxParam.size( ) );
                        for ( auto element : auxParam )
                        {
                            Stream << element.auxParam;
                        }
                        for ( auto element : auxParam )
                        {
                            Stream << STRING( element.auxParamName );
                        }
                        Stream << data << aux << table << history;
                        WriteNext( Stream );
                    }
                    catch ( const std::exception& Exception )
                    {
                        std::cerr << "DEBUG: Error Writing " << StructName( )
                                  << ": " << GetName( )
                                  << " exception: " << Exception.what( )
                                  << std::endl;
                        throw; // rethrow
                    }
                }

            private:
                typedef STRING io_name_type;
                typedef STRING io_comment_type;
            }; // class ClassicIO
        } // namespace FrProcDataImpl
    } // namespace Version_8
} // namespace FrameCPP

#endif /* defined( SWIG ) */
#endif /* defined( __cplusplus ) */

#endif /* FrameCPP_VERSION_8__IMPL__FrProcDataClassicIO_HH */
