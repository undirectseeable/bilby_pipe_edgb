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

#ifndef FrameCPP_VERSION_8__IMPL__FrMsgClassicIO_HH
#define FrameCPP_VERSION_8__IMPL__FrMsgClassicIO_HH

#include "framecpp/Version8/impl/FrMsgData.hh"

#include "framecpp/Common/TOCInfo.hh"

#include "framecpp/Version7/FrMsg.hh"

#include "framecpp/Version8/FrameSpec.hh"
#include "framecpp/Version8/FrSH.hh"
#include "framecpp/Version8/FrSE.hh"
#include "framecpp/Version8/PTR_STRUCT.hh"

namespace FrameCPP
{
    namespace Version_8
    {
        class FrMsg;

        namespace FrMsgImpl
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

                        ret( FrSE(
                            "alarm",
                            Description::Ascii< io_alarm_type >( ),
                            "Name of message, error flag or alarm state" ) );
                        ret( FrSE( "message",
                                   Description::Ascii< io_message_type >( ),
                                   "Message body" ) );
                        ret( FrSE( "severity",
                                   Description::Ascii< severity_type >( ),
                                   "Message severify level (To Be Defined); "
                                   "default = 0" ) );
                        ret( FrSE( "GTimeS",
                                   Description::Ascii< io_gtimes_type >( ),
                                   "GPS time in secondes corresponding to this "
                                   "FrMsg" ) );
                        ret( FrSE( "GTimeN",
                                   Description::Ascii< io_gtimen_type >( ),
                                   "GPS time in residual nanoseconds relative "
                                   "to GTimeS" ) );

                        ret( FrSE( "next",
                                   PTR_STRUCT::Desc( Data::FrameSpecName( ) ),
                                   "Identifer for next message structure in "
                                   "the linked list." ) );

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
                typedef STRING io_alarm_type;
                typedef STRING io_message_type;
                typedef INT_4U io_gtimes_type;
                typedef INT_4U io_gtimen_type;

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
                        boost::shared_ptr< Previous::FrMsg > retval(
                            new Previous::FrMsg( GetAlarm( ),
                                                 GetMessage( ),
                                                 GetSeverity( ),
                                                 GetGTime( ) ) );
                        //-------------------------------------------------------------------
                        // Modify references
                        //-------------------------------------------------------------------
                        /// \todo Replace next references
                        //-------------------------------------------------------------------
                        // Return demoted object
                        //-------------------------------------------------------------------
                        return retval;
                    }
                    catch ( ... )
                    {
                    }
                    throw Unimplemented(
                        "Object* FrMsg::Demote( Object* Obj ) const",
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
                    return io_alarm_type::Bytes( alarm ) +
                        io_message_type::Bytes( message ) + sizeof( severity ) +
                        sizeof( INT_4U ) // GTime Seconds;
                        + sizeof( INT_4U ) // GTime Nanoeconds;
                        + Stream.PtrStructBytes( ) // next
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
                    T* obj( new T( ) );

                    io_alarm_type   io_alarm;
                    io_message_type io_message;

                    Stream >> io_alarm >> io_message >> obj->severity >>
                        obj->GTime;
                    Stream.Next( obj );

                    obj->alarm = io_alarm;
                    obj->message = io_message;

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
                    Stream << io_alarm_type( alarm )
                           << io_message_type( message ) << severity << GTime;
                    WriteNext( Stream );
                }

            private:
                //-----------------------------------------------------------------
                //-----------------------------------------------------------------
                typedef ObjectWithChecksum< Common::FrameSpec::Object >
                    object_type;

                using Common::FrameSpec::Object::Create;
#if WORKING_VIRTUAL_TOCQUERY
            public:
                //-----------------------------------------------------------------
                /// \brief Answer requests for information as needed by TOC
                ///
                /// \param[in] InfoClass
                ///     Class of information being requested.
                //-----------------------------------------------------------------
                void TOCQuery( int InfoClass, ... ) const;
#else /* WORKING_VIRTUAL_TOCQUERY */
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
                return Object::PromoteObject< Previous::FrMsg, FrMsg >(
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

#if WORKING_VIRTUAL_TOCQUERY
                va_end( vl )
#endif /*  WORKING_VIRTUAL_TOCQUERY */
                    ;
            } // TOCQuery
        } // namespace FrMsgImpl
    } // namespace Version_8
} // namespace FrameCPP

#endif /* FrameCPP_VERSION_8__IMPL__FrMsgClassicIO_HH */
