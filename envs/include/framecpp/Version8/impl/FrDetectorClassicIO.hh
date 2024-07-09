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

#ifndef FrameCPP_VERSION_8__IMPL__FrDetectorClassicIO_HH
#define FrameCPP_VERSION_8__IMPL__FrDetectorClassicIO_HH

#ifndef SWIGIMPORTED
#include <string>
#include <vector>
#endif /* SWIGIMPORTED */

#if !defined( SWIGIMPORTED )
#include "ldastoolsal/types.hh"

#include "framecpp/Version8/FrameSpec.hh"

#endif /* ! defined(SWIGIMPORTED) */

#if !defined( SWIGIMPORTED )
#include "framecpp/Common/Description.hh"
#include "framecpp/Common/TOCInfo.hh"

#include "framecpp/Common/FrDetector.hh"

#include "framecpp/Version7/FrDetector.hh"
#endif /* !defined( SWIGIMPORTED ) */

#include "framecpp/Version8/impl/FrDetectorData.hh"

#if !defined( SWIGIMPORTED )
#include "framecpp/Version8/STRING.hh"

#include "framecpp/Version8/FrSH.hh"
#include "framecpp/Version8/FrSE.hh"
#endif /* ! defined(SWIGIMPORTED) */

#if !defined( SWIGIMPORTED )
namespace FrameCPP
{
    namespace Version_8
    {
        class FrDetector;

        namespace FrDetectorImpl
        {
            template < typename T >
            class ClassicIO : public virtual Data,
                              public Common::TOCInfo,
                              public ObjectWithChecksum< Common::FrDetector >
            {
            public:
                //-------------------------------------------------------
                //
                //-------------------------------------------------------
                ClassicIO( )
                    : ObjectWithChecksum< Common::FrDetector >(
                          StructDescription( ) )
                {
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
                        ret( FrSH( Data::FrameSpecName( ),
                                   Data::FrameSpecId( ),
                                   Data::FrameSpecDescription( ) ) );

                        ret( FrSE( "name", "STRING" ) );
                        ret( FrSE( "prefix",
                                   "CHAR[2]"
                                   "" ) );
                        ret( FrSE( "longitude", "REAL_8" ) );
                        ret( FrSE( "latitude", "REAL_8" ) );
                        ret( FrSE( "elevation", "REAL_4" ) );
                        ret( FrSE( "armXazimuth", "REAL_4" ) );
                        ret( FrSE( "armYazimuth", "REAL_4" ) );
                        ret( FrSE( "armXaltitude", "REAL_4" ) );
                        ret( FrSE( "armYaltitude", "REAL_4" ) );
                        ret( FrSE( "armXmidpoint", "REAL_4" ) );
                        ret( FrSE( "armYmidpoint", "REAL_4" ) );
                        ret( FrSE( "localTime", "INT_4S" ) );

                        ret(
                            FrSE( "aux",
                                  PTR_STRUCT::Desc( FrVect::StructName( ) ) ) );
                        ret( FrSE(
                            "table",
                            PTR_STRUCT::Desc( FrTable::StructName( ) ) ) );

                        ret( FrSE(
                            "next",
                            PTR_STRUCT::Desc( Data::FrameSpecName( ) ) ) );

                        ret( FrSE( "chkSum",
                                   CheckSumDataClass( ),
                                   CheckSumDataComment( ) ) );
                    }
                    return &ret;
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
                static promote_ret_type Promote( INT_2U           Source,
                                                 promote_arg_type Obj,
                                                 istream_type*    Stream );

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
                        boost::shared_ptr< Previous::FrDetector > retval(
                            new Previous::FrDetector( GetName( ),
                                                      GetPrefix( ),
                                                      GetLongitude( ),
                                                      GetLatitude( ),
                                                      GetElevation( ),
                                                      GetArmXazimuth( ),
                                                      GetArmYazimuth( ),
                                                      GetArmXaltitude( ),
                                                      GetArmYaltitude( ),
                                                      GetArmXmidpoint( ),
                                                      GetArmYmidpoint( ),
                                                      GetLocalTime( ) ) );
                        if ( Stream )
                        {
                            //-----------------------------------------------------------------
                            // Modify references
                            //-----------------------------------------------------------------
                            Stream->ReplaceRef(
                                retval->RefAux( ), RefAux( ), Data::MAX_REF );
                            Stream->ReplaceRef( retval->RefTable( ),
                                                RefTable( ),
                                                Data::MAX_REF );
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
                        "Object* FrDetector::demote( Object* Obj ) const",
                        DATA_FORMAT_VERSION,
                        __FILE__,
                        __LINE__ );
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
                    return ( FrameSpecName( ) );
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
                    return io_name_type::Bytes( name ) + sizeof( prefix ) +
                        sizeof( longitude ) + sizeof( latitude ) +
                        sizeof( elevation ) + sizeof( armXazimuth ) +
                        sizeof( armYazimuth ) + sizeof( armXaltitude ) +
                        sizeof( armYaltitude ) + sizeof( armXmidpoint ) +
                        sizeof( armYmidpoint ) + sizeof( localTime ) +
                        Stream.PtrStructBytes( ) // aux
                        + Stream.PtrStructBytes( ) // table
                        + Stream.PtrStructBytes( ) // next
                        ;
                }

                //-----------------------------------------------------------------
                /// \brief Virtual constructor
                //-----------------------------------------------------------------
                virtual self_type*
                pCreate( istream_type& Stream ) const
                {
                    {
                        T* obj( new T( ) );

                        io_name_type io_name;

                        Stream >> io_name;
                        Stream.read( obj->prefix, sizeof( obj->prefix ) );
                        Stream >> obj->longitude >> obj->latitude >>
                            obj->elevation >> obj->armXazimuth >>
                            obj->armYazimuth >> obj->armXaltitude >>
                            obj->armYaltitude >> obj->armXmidpoint >>
                            obj->armYmidpoint >> obj->localTime >> obj->aux >>
                            obj->table;

                        Stream.Next( obj );

                        obj->name = io_name;

                        return ( obj );
                    }
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
                    Stream << io_name_type( name );
                    Stream.write( prefix, sizeof( prefix ) );
                    Stream << longitude << latitude << elevation << armXazimuth
                           << armYazimuth << armXaltitude << armYaltitude
                           << armXmidpoint << armYmidpoint << localTime << aux
                           << table;
                    WriteNext( Stream );
                }

            private:
                typedef STRING io_name_type;
#if WORKING_VIRTUAL_TOCQUERY
            public:
                //-----------------------------------------------------------------
                /// \brief Answer requests for information as needed by TOC
                ///
                /// \param[in] InfoClass
                ///     Class of information being requested.
                //-----------------------------------------------------------------
                virtual void TOCQuery( int InfoClass, ... ) const;
#else /*  WORKING_VIRTUAL_TOCQUERY */
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
#endif /* ! WORKING_VIRTUAL_TOCQUERY */
            };

            template < typename T >
            typename ClassicIO< T >::promote_ret_type
            ClassicIO< T >::Promote( INT_2U           Source,
                                     promote_arg_type Obj,
                                     istream_type*    Stream )
            {
                return Object::PromoteObject< Previous::FrDetector, T >(
                    DATA_FORMAT_VERSION, Source, Obj, Stream );
            }

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
                        case TOCInfo::IC_DETECTOR_PREFIX:
                        {
                            const char* p = GetPrefix( );
                            if ( p[ 0 ] )
                            {
                                if ( p[ 1 ] )
                                {
                                    data->assign( p, 2 );
                                }
                                else
                                {
                                    data->assign( p, 1 );
                                }
                            }
                        }
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
            } // TOCQuery
        } // namespace FrDetectorImpl
    } // namespace Version_8
} // namespace FrameCPP
#endif /* ! defined(SWIGIMPORTED) */

#endif /* FrameCPP_VERSION_8__IMPL__FrDetectorClassicIO_HH */
