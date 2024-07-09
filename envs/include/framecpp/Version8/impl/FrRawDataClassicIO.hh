//
// LDASTools frameCPP - A library implementing the LIGO/Virgo frame
// specification
//
// Copyright (C) 2018-2020 California Institute of Technology
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

#ifndef FrameCPP_VERSION_8__IMPL__FrRawData_ClassicIO_HH
#define FrameCPP_VERSION_8__IMPL__FrRawData_ClassicIO_HH

#include "framecpp/Version8/impl/FrRawDataData.hh"

#if defined( __cplusplus ) && !defined( SWIG )

#include "framecpp/Version7/FrRawData.hh"

namespace FrameCPP
{
    namespace Version_8
    {

        class FrRawData;

        namespace FrRawDataImpl
        {
            template < typename T >
            class ClassicIO
                : public virtual Data,
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

                ClassicIO( Previous::FrRawData& Source, istream_type* Stream )
                    : ObjectWithChecksum< Common::FrameSpec::Object >(
                          FrameSpecId( ), StructDescription( ) )
                {
                    name = Source.GetName( );
                    if ( Stream )
                    {
                        //-------------------------------------------------------------------
                        // Modify references
                        //-------------------------------------------------------------------
                        Stream->ReplaceRef(
                            RefFirstSer( ), Source.RefFirstSer( ), MAX_REF );
                        Stream->ReplaceRef(
                            RefFirstAdc( ), Source.RefFirstAdc( ), MAX_REF );
                        Stream->ReplaceRef( RefFirstTable( ),
                                            Source.RefFirstTable( ),
                                            MAX_REF );
                        Stream->ReplaceRef(
                            RefLogMsg( ), Source.RefLogMsg( ), MAX_REF );
                        Stream->ReplaceRef(
                            RefMore( ), Source.RefMore( ), MAX_REF );
                    }
                }

                //-----------------------------------------------------------------
                /// @brief The name structure name of this object.
                ///
                /// @return
                ///     The name of the structure as specified by the frame
                ///     specification.
                //-----------------------------------------------------------------
                virtual const char*
                ObjectStructName( ) const
                {
                    return StructName( );
                }

                /**
                 * @brief Promote previous version of object to this version
                 *
                 * @param[in] Source
                 *     The frame specification version of the object.
                 * @param[in] Obj
                 *     The previous version of the object.
                 * @param[in] Stream
                 *     Stream from which the origional object was created.
                 *
                 * @return
                 *     A new instance of FrameH based on Obj
                 */
                inline static promote_ret_type
                Promote( INT_2U           Source,
                         promote_arg_type Obj,
                         istream_type*    Stream )
                {
                    return Object::PromoteObject< Previous::FrRawData, T >(
                        DATA_FORMAT_VERSION, Source, Obj, Stream );
                }

                //-----------------------------------------------------------------
                /// @brief The description of structure
                ///
                /// @return
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

                        ret( FrSE( "name",
                                   Description::Ascii< io_name_type >( ),
                                   "" ) );
                        ret( FrSE( "firstSer",
                                   PTR_STRUCT::Desc( FrSerData::StructName( ) ),
                                   "" ) );
                        ret( FrSE( "firstAdc",
                                   PTR_STRUCT::Desc( FrAdcData::StructName( ) ),
                                   "" ) );
                        ret( FrSE( "firstTable",
                                   PTR_STRUCT::Desc( FrTable::StructName( ) ),
                                   "" ) );
                        ret( FrSE( "logMsg",
                                   PTR_STRUCT::Desc( FrMsg::StructName( ) ),
                                   "" ) );
                        ret( FrSE( "more",
                                   PTR_STRUCT::Desc( FrVect::StructName( ) ),
                                   "" ) );

                        ret( FrSE( "chkSum",
                                   CheckSumDataClass( ),
                                   CheckSumDataComment( ) ) );
                    }

                    return &ret;
                }

            protected:
                //-----------------------------------------------------------------
                /// @brief Demotes object to previous version of the frame spec
                ///
                /// @param[in] Target
                ///     The version of the frame specification to demote too.
                /// @param[in] Obj
                ///     The version of the object to demote.
                /// @param[in] Stream
                ///     The input stream from which the original object was
                ///     read.
                ///
                /// @return
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
                        boost::shared_ptr< Previous::FrRawData > retval(
                            new Previous::FrRawData( GetName( ) ) );
                        if ( Stream )
                        {
                            //-----------------------------------------------------------------
                            // Modify references
                            //-----------------------------------------------------------------
                            Stream->ReplaceRef( retval->RefFirstSer( ),
                                                RefFirstSer( ),
                                                MAX_REF );
                            Stream->ReplaceRef( retval->RefFirstAdc( ),
                                                RefFirstAdc( ),
                                                MAX_REF );
                            Stream->ReplaceRef( retval->RefFirstTable( ),
                                                RefFirstTable( ),
                                                MAX_REF );
                            Stream->ReplaceRef(
                                retval->RefLogMsg( ), RefLogMsg( ), MAX_REF );
                            Stream->ReplaceRef(
                                retval->RefMore( ), RefMore( ), MAX_REF );
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
                        "Object* FrRawData::Demote( Object* Obj ) const",
                        DATA_FORMAT_VERSION,
                        __FILE__,
                        __LINE__ );
                }

                //-----------------------------------------------------------------
                /// @brief Promotes object to another version of the frame spec
                ///
                /// @param[in] Target
                ///     The version of the promoted frame specification.
                /// @param[in] Obj
                ///     The object to be promoted.
                /// @param[in] Stream
                ///     The input stream from which the original object was
                ///     read.
                ///
                /// @return
                ///     An object promoted to the next generation.
                //-----------------------------------------------------------------
                virtual promote_ret_type
                promote( INT_2U           Target,
                         promote_arg_type Obj,
                         Common::IStream* Stream ) const
                {
                    return Promote( Target, Obj, Stream );
                }

                //-----------------------------------------------------------------
                /// @brief Number of bytes needed to write this structure
                ///
                /// @param[in] Stream
                ///     The stream from which to the object is being read or
                ///     written.
                ///
                /// @return
                ///     The number of bytes need to read or write this object.
                //-----------------------------------------------------------------
                virtual cmn_streamsize_type
                pBytes( const Common::StreamBase& Stream ) const
                {
                    cmn_streamsize_type retval = io_name_type::Bytes( name ) +
                        Stream.PtrStructBytes( ) // firstSer
                        + Stream.PtrStructBytes( ) // firstAdc
                        + Stream.PtrStructBytes( ) // firstTable
                        + Stream.PtrStructBytes( ) // logMsg
                        + Stream.PtrStructBytes( ) // more
                        ;
                    return retval;
                }

                //-----------------------------------------------------------------
                /// @brief Virtual constructor
                ///
                /// @param[in] Stream
                ///     The input stream from where the object is being read.
                //-----------------------------------------------------------------
                virtual self_type*
                pCreate( istream_type& Stream ) const
                {
                    T* obj( new T( ) );

                    io_name_type io_name;

                    Stream >> io_name;

                    Stream >> obj->firstSer >> obj->firstAdc >>
                        obj->firstTable >> obj->logMsg >> obj->more;

                    obj->name = io_name;

                    return ( obj );
                }

                //-----------------------------------------------------------------
                /// @brief Write the structure to the stream
                ///
                /// @param[in] Stream
                ///     The output stream where the object is to be written.
                //-----------------------------------------------------------------
                virtual void
                pWrite( Common::OStream& Stream ) const
                {
                    Stream << io_name_type( name ) << firstSer << firstAdc
                           << firstTable << logMsg << more;
                }

            private:
                typedef STRING io_name_type;
            }; // class ClassicIO
        } // namespace FrRawDataImpl
    } // namespace Version_8
} // namespace FrameCPP

#endif /* defined( __cplusplus ) && !defined( SWIG ) */

#endif /* FrameCPP_VERSION_8__IMPL__FrRawData_ClassicIO_HH */
