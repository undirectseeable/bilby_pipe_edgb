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

#ifndef FrameCPP_VERSION_8__IMPL__FrSEClassicIO_HH
#define FrameCPP_VERSION_8__IMPL__FrSEClassicIO_HH

#include "framecpp/Version8/impl/FrSEData.hh"

#include "framecpp/Version8/FrameSpec.hh"
#include "framecpp/Version8/STRING.hh"

namespace FrameCPP
{
    namespace Version_8
    {
        class FrSE;

        namespace FrSEImpl
        {
            template < typename BASE_TYPE >
            class ClassicIO
                : public virtual Data,
                  public ObjectWithChecksum< Common::FrameSpec::Object >
            {
            public:
                typedef STRING io_name_type;
                typedef STRING io_id_type;
                typedef STRING io_comment_type;

                ClassicIO( )
                    : ObjectWithChecksum< Common::FrameSpec::Object >(
                          FrameSpecId( ), StructDescription( ) )
                {
                }

                Common::FrameSpec::Object*
                Clone( ) const
                {
                    return ( new BASE_TYPE(
                        *( reinterpret_cast< const BASE_TYPE* >( this ) ) ) );
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
                    return nullptr;
                }

                virtual const char*
                ObjectStructName( ) const
                {
                    return ( FrameSpecName( ) );
                }

                //-----------------------------------------------------------------
                /// \brief comparison operator
                //-----------------------------------------------------------------
                virtual bool
                operator==( const Common::FrameSpec::Object& Obj ) const;

            protected:
                //-----------------------------------------------------------------
                //-----------------------------------------------------------------
                typedef ObjectWithChecksum< Common::FrameSpec::Object >
                    object_type;

                //-----------------------------------------------------------------
                /// \brief Down grade an object
                //-----------------------------------------------------------------
                virtual demote_ret_type
                demote( INT_2U           Target,
                        demote_arg_type  Obj,
                        Common::IStream* Stream ) const
                {
                    throw Unimplemented(
                        "Object* FrSE::Demote( Object* Obj ) const",
                        DATA_FORMAT_VERSION,
                        __FILE__,
                        __LINE__ );
                }

                //-----------------------------------------------------------------
                /// \brief Upgrade an object
                //-----------------------------------------------------------------
                virtual promote_ret_type
                promote( INT_2U           Target,
                         promote_arg_type Obj,
                         Common::IStream* Stream ) const
                {
                    throw Unimplemented(
                        "Object* FrSE::Promote( Object* Obj ) const",
                        DATA_FORMAT_VERSION,
                        __FILE__,
                        __LINE__ );
                }

                //-----------------------------------------------------------------
                // \brief Return the number of bytes needed to write this object
                //-----------------------------------------------------------------
                virtual cmn_streamsize_type
                pBytes( const Common::StreamBase& Stream ) const
                {
                    return io_name_type::Bytes( name ) +
                        io_id_type::Bytes( classId ) +
                        io_comment_type::Bytes( comment );
                }

                //-----------------------------------------------------------------
                /// \brief Create a new instance of the object based on the
                /// input stream
                //-----------------------------------------------------------------
                virtual self_type*
                pCreate( istream_type& Stream ) const
                {
                    BASE_TYPE* obj( new BASE_TYPE( ) );

                    io_name_type    io_name;
                    io_id_type      io_id;
                    io_comment_type io_comment;

                    Stream >> io_name >> io_id >> io_comment;

                    obj->name = io_name;
                    obj->classId = io_id;
                    obj->comment = io_comment;

                    return ( obj );
                }

                void
                pWrite( Common::OStream& Stream ) const
                {
                    Stream << io_name_type( name ) << io_id_type( classId )
                           << io_comment_type( comment );
                }
            }; // class ClassicIO

        } // namespace FrSEImpl
    } // namespace Version_8
} // namespace FrameCPP

#endif /* FrameCPP_VERSION_8__IMPL__FrSEClassicIO_HH */
