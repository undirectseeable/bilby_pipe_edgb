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

#ifndef FrameCPP_VERSION_8__IMPL__FrHistoryClassicIO_HH
#define FrameCPP_VERSION_8__IMPL__FrHistoryClassicIO_HH

#include "framecpp/Common/Description.hh"

#include "framecpp/Version8/impl/FrHistoryData.hh"

#include "framecpp/Version8/FrameSpec.hh"
#include "framecpp/Version8/FrSH.hh"
#include "framecpp/Version8/FrSE.hh"
#include "framecpp/Version8/PTR_STRUCT.hh"

namespace FrameCPP
{
    namespace Version_8
    {
        class FrHistory;

        namespace FrHistoryImpl
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
                static promote_ret_type
                Promote( INT_2U           Source,
                         promote_arg_type Obj,
                         istream_type*    Stream )
                {
                    return Object::PromoteObject< Previous::FrHistory,
                                                  FrHistory >(
                        DATA_FORMAT_VERSION, Source, Obj, Stream );
                }

                //-------------------------------------------------------
                /// \brief The description of structure
                ///
                /// \return
                ///     A Description object which describes this structure as
                ///     specified by the frame specification.
                //-------------------------------------------------------
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
                                   "Name of history record" ) );
                        ret( FrSE( "time",
                                   Description::Ascii< time_type >( ),
                                   "Time of post-processing." ) );
                        ret(
                            FrSE( "comment",
                                  Description::Ascii< io_comment_type >( ),
                                  "Program name and relevant comments needed to"
                                  " define post-processing" ) );

                        ret( FrSE(
                            "next",
                            PTR_STRUCT::Desc( Data::FrameSpecName( ) ),
                            "Identifier for next history structure in the "
                            "linked list" ) );

                        ret( FrSE( "chkSum",
                                   CheckSumDataClass( ),
                                   CheckSumDataComment( ) ) );
                    }

                    return &ret;
                }

              //-----------------------------------------------------------------
              /// \brief equality operator for abstract data type
              ///
              /// \param[in] RHS
              ///     The object to be compared.
              ///
              /// \return
              ///     The value true is returned if this object is equivelent
              ///     to the RHS instance; false otherwise.
              //-----------------------------------------------------------------
              virtual bool
              operator==( const Common::FrameSpec::Object& RHS ) const;

            protected:
                //-----------------------------------------------------------------
                /// \brief Type for name of history record
                //-----------------------------------------------------------------
                typedef STRING io_name_type;
                //-----------------------------------------------------------------
                /// \brief Type for comment field.
                ///
                /// Program name and relevant comments needed to
                /// define post-processing.
                //-----------------------------------------------------------------
                typedef STRING io_comment_type;

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
                        boost::shared_ptr< Previous::FrHistory > retval(
                            new Previous::FrHistory(
                                GetName( ), GetTime( ), GetComment( ) ) );
                        //-------------------------------------------------------------------
                        // Return demoted object
                        //-------------------------------------------------------------------
                        return retval;
                    }
                    catch ( ... )
                    {
                    }
                    throw Unimplemented(
                        "Object* FrHistory::demote( Object* Obj ) const",
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
                    return io_name_type::Bytes( name ) + sizeof( time ) +
                        io_comment_type::Bytes( comment ) +
                        Stream.PtrStructBytes( ) // next
                        ;
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
                    io_name_type    io_name;
                    io_comment_type io_comment;

                    T* obj( new T( ) );

                    Stream >> io_name >> obj->time >> io_comment;
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
                    Stream << io_name_type( name ) << time
                           << io_comment_type( comment );
                    WriteNext( Stream );
                }

            private:
                //-----------------------------------------------------------------
                //-----------------------------------------------------------------
                typedef ObjectWithChecksum< Common::FrameSpec::Object >
                    object_type;

                using Common::FrameSpec::Object::Create;
            };
        } // namespace FrHistoryImpl
    } // namespace Version_8
} // namespace FrameCPP

#endif /* FrameCPP_VERSION_8__IMPL__FrHistoryClassicIO_HH */
