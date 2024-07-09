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

#ifndef FrameCPP_VERSION_8__IMPL__FrTableClassicIO_HH
#define FrameCPP_VERSION_8__IMPL__FrTableClassicIO_HH

#include "framecpp/Version7/FrTable.hh"

#include "framecpp/Version8/impl/FrTableData.hh"

namespace FrameCPP
{
    namespace Version_8
    {
        class FrTable;

        namespace FrTableImpl
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
                                                 Common::IStream* Stream );

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

                        ret( FrSE( "name",
                                   Description::Ascii< io_name_type >( ),
                                   "Name of this table" ) );
                        ret( FrSE( "comment",
                                   Description::Ascii< io_comment_type >( ),
                                   "Comment" ) );
                        ret( FrSE( "nColumn",
                                   Description::Ascii< nColumn_type >( ),
                                   "Number of columns in table" ) );
                        ret( FrSE( "nRow",
                                   Description::Ascii< nRow_type >( ),
                                   "Number of rows in table." ) );
                        ret( FrSE( "columnName"
                                   "STRING[nColumn]",
                                   "Names of the columns." ) );

                        ret( FrSE( "column",
                                   PTR_STRUCT::Desc( "FrVect" ),
                                   "Next table in linked list" ) );
                        ret( FrSE( "next",
                                   PTR_STRUCT::Desc( Data::FrameSpecName( ) ),
                                   "Next table in linked list" ) );

                        ret( FrSE( "chkSum",
                                   CheckSumDataClass( ),
                                   CheckSumDataComment( ) ) );
                    }

                    return &ret;
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
                        // Create a newly demoted instance.
                        //-------------------------------------------------------------------
                        boost::shared_ptr< Previous::FrTable > retval(
                            new Previous::FrTable( *this ) );

                        //-------------------------------------------------------------------
                        // Modify references
                        //-------------------------------------------------------------------
                        if ( Stream )
                        {
#define SRR__( R ) Stream->ReplaceRef( retval->R( ), R( ), m_refs.MAX_REF )

                            SRR__( RefColumn );
#undef SRR__
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
                        "Object* FrTable::Demote( Object* Obj ) const",
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
                /// \brief Number of bytes needed to write this structure
                ///
                /// \param[in] Stream
                ///     The stream from which to the object is being read or
                ///     written.
                ///
                /// \return
                ///     The number of bytes need to read or write this object.
                //-----------------------------------------------------------------
                virtual cmn_streamsize_type
                pBytes( const Common::StreamBase& Stream ) const
                {
                    cmn_streamsize_type retval = m_data.Bytes( Stream ) +
                        m_refs.Bytes( Stream ) +
                        Stream.PtrStructBytes( ) // next
                        ;
                    return retval;
                }

                //-----------------------------------------------------------------
                /// \brief Virtual constructor
                ///
                /// \param[in] Stream
                ///     The input stream from where the object is being read.
                //-----------------------------------------------------------------
                virtual self_type*
                pCreate( Common::IStream& Stream ) const
                {
                    T* obj( new T );

#if 0
                    io_name_type    io_name;
                    io_comment_type io_comment;

                    Stream >> io_name >> io_comment;
                    Stream.Next( obj );

                    obj->name = io_name;
                    obj->comment = io_comment;
#else
                    obj->m_data( Stream );
                    obj->m_refs( Stream );
                    Stream.Next( obj );
#endif /* 0 */

                    return ( obj );
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
                         Common::IStream* Stream ) const
                {
                    return Promote( Target, Obj, Stream );
                }

                //-----------------------------------------------------------------
                /// \brief Write the structure to the stream
                ///
                /// \param[in] Stream
                ///     The output stream where the object is to be written.
                //-----------------------------------------------------------------
                virtual void
                pWrite( Common::OStream& Stream ) const
                {
                    m_data( Stream );
                    m_refs( Stream );

                    WriteNext( Stream );
                }

            private:
                typedef STRING io_name_type;
                typedef STRING io_comment_type;

                //-----------------------------------------------------------------
                /// \brief Object with checksum data.
                //-----------------------------------------------------------------
                typedef ObjectWithChecksum< Common::FrameSpec::Object >
                    object_type;

                using Common::FrameSpec::Object::Create;
            };

            template < typename T >
            typename ClassicIO< T >::promote_ret_type
            ClassicIO< T >::Promote( INT_2U           Source,
                                     promote_arg_type Obj,
                                     istream_type*    Stream )
            {
                return Object::PromoteObject< Previous::FrTable, FrTable >(
                    DATA_FORMAT_VERSION, Source, Obj, Stream );
            }
        } // namespace FrTableImpl
    } // namespace Version_8
} // namespace FrameCPP

#endif /* FrameCPP_VERSION_8__IMPL__FrTableClassicIO_HH */
