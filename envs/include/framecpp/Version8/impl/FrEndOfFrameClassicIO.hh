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

#ifndef FrameCPP_VERSION_8__IMPL__FrEndOfFrameClassicIO_HH
#define FrameCPP_VERSION_8__IMPL__FrEndOfFrameClassicIO_HH

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

#include "framecpp/Version7/FrEndOfFrame.hh"
#endif /* !defined( SWIGIMPORTED ) */

#include "framecpp/Version8/impl/FrEndOfFrameData.hh"

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
        class FrEndOfFrame;

        namespace FrEndOfFrameImpl
        {
            template < typename T >
            class ClassicIO
                : public virtual Data,
                  public ObjectWithChecksum< Common::FrameSpec::Object >
            {
            public:
                using ObjectWithChecksum< Common::FrameSpec::Object >::Bytes;

                //-------------------------------------------------------
                //
                //-------------------------------------------------------
                ClassicIO( )
                    : ObjectWithChecksum< Common::FrameSpec::Object >(
                          FrameSpecId( ), StructDescription( ) )
                {
                }

                //-------------------------------------------------------
                /// \brief The name structure name of this object.
                ///
                /// \return
                ///     The name of the structure as specified by the frame
                ///     specification.
                //-------------------------------------------------------
                virtual const char*
                ObjectStructName( ) const
                {
                  return( FrameSpecName( ) );
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
                        ret( FrSE( "run",
                                   "INT_4S",
                                   "Run number; same as in FrameHeader run "
                                   "number datum." ) );
                        ret( FrSE(
                            "frame",
                            "INT_4U",
                            "Frame number, monotonically increasing until end "
                            "of run;"
                            " same as in Frame Header run number datum" ) );
                        ret( FrSE( "GTimeS",
                                   "INT_4U",
                                   "Frame start time in GPS Seconds." ) );
                        ret( FrSE( "GTimeN",
                                   "INT_4U",
                                   "Frame start time residual, integer "
                                   "nanoseconds." ) );

                        ret( FrSE( "chkSum",
                                   CheckSumDataClass( ),
                                   CheckSumDataComment( ) ) );
                    }
                    return ( &ret );
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
                demote( INT_2U          Target,
                        demote_arg_type Obj,
                        istream_type*   Stream ) const
                {
                    throw Unimplemented(
                        "Object* FrEndOfFrame::demote( Object* Obj ) const",
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
                    throw Unimplemented(
                        "Object* FrEndOfFrame::promote( Object* Obj ) const",
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
                virtual cmn_streamsize_type
                pBytes( const Common::StreamBase& Stream ) const
                {
                    return sizeof( run ) + sizeof( frame ) +
                        sizeof( GTimeS_type ) + sizeof( GTimeN_type );
                }

                //-----------------------------------------------------------------
                /// \brief Virtual constructor.
                ///
                /// \param[in] Stream
                ///     The input stream from which to read the object.
                ///
                /// \return
                ///    A new instance of this object.
                //-----------------------------------------------------------------
                virtual self_type*
                pCreate( istream_type& Stream ) const
                {
                    GTimeS_type sec;
                    GTimeN_type nsec;

                    T* obj( new T( ) );

                    Stream >> obj->run >> obj->frame >> sec >> nsec;
                    obj->GTime = GPSTime( sec, nsec );

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
                    //---------------------------------------------------------------------
                    // Write out to the stream
                    //---------------------------------------------------------------------
                    Stream << run << frame << GTimeS_type( GTime.GetSeconds( ) )
                           << GTimeN_type( GTime.GetNanoseconds( ) );
                }

            private:
                //-----------------------------------------------------------------
                //-----------------------------------------------------------------
                typedef ObjectWithChecksum< Common::FrameSpec::Object >
                    object_type;

                using Common::FrameSpec::Object::Create;

            }; // Class - FrEndOfFrame

        } // namespace FrEndOfFrameImpl
    } // namespace Version_8
} // namespace FrameCPP
#endif /* ! defined(SWIGIMPORTED) */

#endif /* FrameCPP_VERSION_8__IMPL__FrEndOfFrameClassicIO_HH */
