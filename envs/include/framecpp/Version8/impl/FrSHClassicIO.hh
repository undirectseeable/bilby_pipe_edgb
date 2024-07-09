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

#ifndef FrameCPP_VERSION_8__IMPL__FrSHClassicIO_HH
#define FrameCPP_VERSION_8__IMPL__FrSHClassicIO_HH

#if !defined( SWIGIMPORTED )
#include "framecpp/Common/FrameSpec.hh"
#include "framecpp/Common/FrSH.hh"
#endif /* !defined( SWIGIMPORTED ) */

#if !defined( SWIGIMPORTED )
#include "framecpp/Version8/STRING.hh"
#include "framecpp/Version8/GPSTime.hh"
#endif /* !defined( SWIGIMPORTED ) */
#include "framecpp/Version8/impl/FrSHData.hh"
#if !defined( SWIGIMPORTED )
#include "framecpp/Version8/FrameSpec.hh"
#endif /* !defined( SWIGIMPORTED ) */

#if !defined( SWIGIMPORTED )
namespace FrameCPP
{
    namespace Version_8
    {
        namespace FrSHImpl
        {
            template < typename FR_SH_T >
            class ClassicIO : public virtual Data,
                              public ObjectWithChecksum< Common::FrSH >
            {
            public:
                //-------------------------------------------------------
                //
                //-------------------------------------------------------
                ClassicIO( )
                {
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
                    throw Unimplemented(
                        "Object* FrSH::Demote( Object* Obj ) const",
                        DATA_FORMAT_VERSION,
                        __FILE__,
                        __LINE__ );
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

                Common::FrameSpec::Object*
                Clone( ) const
                {
                    return ( new FR_SH_T(
                        *( reinterpret_cast< const FR_SH_T* >( this ) ) ) );
                }

            protected:
                /* typedef Previous::FrSH previous_type; */
                /* typedef FR_SH_T        current_type; */

                typedef STRING io_name_type;
                typedef STRING io_comment_type;

                //-------------------------------------------------------
                /// \brief Assign the contents of the instance
                ///
                /// \param[in] Stream
                ///     An input stream from which to read information for
                ///     the instance.
                //-------------------------------------------------------
                virtual void
                assign( assign_stream_type& Stream )
                {
                  io_name_type    io_name;
                  io_comment_type io_comment;

                  Stream >> io_name >> klass >> io_comment;

                  Data::name = io_name;
                  comment = io_comment;
                }

                //-------------------------------------------------------
                /// \todo
                ///     See about storing name in this class and eliminate the
                ///     need for this virtual method.
                //-------------------------------------------------------
                virtual const std::string&
                name( ) const
                {
                    return ( Data::name );
                }

                virtual cmn_classId_type
                classId( ) const
                {
                    return ( klass );
                }

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
                demote( frame_spec_version_type Target,
                        demote_arg_type         Obj,
                        istream_type*           Stream ) const
                {
                    throw Unimplemented(
                        "Object* FrSH::Demote( Object* Obj ) const",
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
                promote( frame_spec_version_type Target,
                         promote_arg_type        Obj,
                         istream_type*           Stream ) const
                {
                    throw Unimplemented(
                        "Object* FrSH::promote( Object* Obj ) const",
                        DATA_FORMAT_VERSION,
                        __FILE__,
                        __LINE__ );
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
                    return io_name_type::Bytes( Data::name ) +
                        sizeof( klass ) + io_comment_type::Bytes( comment );
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
                    FR_SH_T* obj( new FR_SH_T( ) );

                    io_name_type    io_name;
                    io_comment_type io_comment;

                    Stream >> io_name >> obj->klass >> io_comment;

                    obj->Data::name = io_name;
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
                    Stream << io_name_type( Data::name ) << klass
                           << io_comment_type( comment );
                }

            private:
                //-----------------------------------------------------------------
                //-----------------------------------------------------------------
                typedef ObjectWithChecksum< Common::FrameSpec::Object >
                    object_type;

                using Common::FrameSpec::Object::Create;
            };

        } // namespace FrSHImpl
    } // namespace Version_8
} // namespace FrameCPP

#endif /* !defined( SWIGIMPORTED ) */

#endif /* FrameCPP_VERSION_8__IMPL__FrSHClassicIO_HH */
