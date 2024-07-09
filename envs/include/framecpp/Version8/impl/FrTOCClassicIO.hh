//
// LDASTools frameCPP - A library implementing the LIGO/Virgo frame
// specification
//
// Copyright (C) 2018 California Institute of Technology
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

#ifndef FrameCPP_VERSION_8__IMPL__FrTOCClassicIO_HH
#define FrameCPP_VERSION_8__IMPL__FrTOCClassicIO_HH

#include "framecpp/Version8/impl/FrTOCData.hh"

#if defined( __cplusplus ) && !defined( SWIG )
#include <map>
#include <vector>

#include "framecpp/Common/Description.hh"
#include "framecpp/Common/FrameSpec.hh"
#include "framecpp/Common/FrTOC.hh"

#include "framecpp/Version7/FrTOC.hh"

#include "framecpp/Version8/FrameSpec.hh"
#include "framecpp/Version8/FrSH.hh"
#include "framecpp/Version8/FrSE.hh"
#endif /* defined( __cplusplus ) && !defined( SWIG ) */

#if defined( __cplusplus )
#include "framecpp/Version8/impl/FrTOCAdcDataClassicIO.hh"
#include "framecpp/Version8/impl/FrTOCDataClassicIO.hh"
#include "framecpp/Version8/impl/FrTOCEventClassicIO.hh"
#include "framecpp/Version8/impl/FrTOCProcDataClassicIO.hh"
#include "framecpp/Version8/impl/FrTOCSerDataClassicIO.hh"
#include "framecpp/Version8/impl/FrTOCSimDataClassicIO.hh"
#include "framecpp/Version8/impl/FrTOCSimEventClassicIO.hh"
#include "framecpp/Version8/impl/FrTOCStatDataClassicIO.hh"
#include "framecpp/Version8/impl/FrTOCSummaryClassicIO.hh"

#endif /* defined( __cplusplus ) */

#if defined( __cplusplus ) && !defined( SWIG )

namespace FrameCPP
{
    namespace Version_8
    {

        class FrTOC;

        namespace FrTOCImpl
        {
            template < typename T >
            class ClassicIO : public virtual Data,
                              public ObjectWithChecksum< Common::FrTOC >,
                              public FrTOCDataClassicIO,
                              public FrTOCStatDataClassicIO,
                              public FrTOCAdcDataClassicIO,
                              public FrTOCProcDataClassicIO,
                              public FrTOCSimDataClassicIO,
                              public FrTOCSerDataClassicIO,
                              public FrTOCSummaryClassicIO,
                              public FrTOCEventClassicIO,
                              public FrTOCSimEventClassicIO
            {
            public:
                //-----------------------------------------------------------------
                ///
                //-----------------------------------------------------------------
                ClassicIO( )
                    : ObjectWithChecksum< Common::FrTOC >(
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
                        //-----------------------------------------------
                        ret( FrSH( Data::StructName( ),
                                   Data::FrameSpecId( ),
                                   Data::FrameSpecDescription( ) ) );

                        FrTOCDataClassicIO::Description< FrSE >( ret );
                        FrTOCStatDataClassicIO::Description< FrSE >( ret );
                        FrTOCAdcDataClassicIO::Description< FrSE >( ret );
                        FrTOCProcDataClassicIO::Description< FrSE >( ret );
                        FrTOCSimDataClassicIO::Description< FrSE >( ret );
                        FrTOCSerDataClassicIO::Description< FrSE >( ret );
                        FrTOCSummaryClassicIO::Description< FrSE >( ret );
                        FrTOCEventClassicIO::Description< FrSE >( ret );
                        FrTOCSimEventClassicIO::Description< FrSE >( ret );

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
                    throw Unimplemented(
                        "Object* FrTOC::demote( Object* Obj ) const",
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
                         Common::IStream* Stream ) const
                {
                    throw Unimplemented(
                        "Object* FrTOC::promote( Object* Obj ) const",
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
                virtual Common::FrameSpec::size_type
                pBytes( const Common::StreamBase& Stream ) const
                {
                    return FrTOCDataClassicIO::Bytes( Stream ) +
                        FrTOCStatDataClassicIO::Bytes( Stream ) +
                        FrTOCAdcDataClassicIO::Bytes( Stream ) +
                        FrTOCProcDataClassicIO::Bytes( Stream ) +
                        FrTOCSimDataClassicIO::Bytes( Stream ) +
                        FrTOCSerDataClassicIO::Bytes( Stream ) +
                        FrTOCSummaryClassicIO::Bytes( Stream ) +
                        FrTOCEventClassicIO::Bytes( Stream ) +
                        FrTOCSimEventClassicIO::Bytes( Stream );
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

                    obj->FrTOCDataClassicIO::Load( Stream );
                    obj->FrTOCStatDataClassicIO::Load( Stream );
                    obj->FrTOCAdcDataClassicIO::Load( Stream,
                                                      obj->GetNFrame( ) );
                    obj->FrTOCProcDataClassicIO::Load( Stream,
                                                       obj->GetNFrame( ) );
                    obj->FrTOCSimDataClassicIO::Load( Stream,
                                                      obj->GetNFrame( ) );
                    obj->FrTOCSerDataClassicIO::Load( Stream,
                                                      obj->GetNFrame( ) );
                    obj->FrTOCSummaryClassicIO::Load( Stream,
                                                      obj->GetNFrame( ) );
                    obj->FrTOCEventClassicIO::Load( Stream );
                    obj->FrTOCSimEventClassicIO::Load( Stream );

                    return ( obj );
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
                    FrTOCDataClassicIO::write( Stream );
                    FrTOCStatDataClassicIO::write( Stream );
                    FrTOCAdcDataClassicIO::write( Stream );
                    FrTOCProcDataClassicIO::write( Stream );
                    FrTOCSimDataClassicIO::write( Stream );
                    FrTOCSerDataClassicIO::write( Stream );
                    FrTOCSummaryClassicIO::write( Stream );
                    FrTOCEventClassicIO::write( Stream );
                    FrTOCSimEventClassicIO::write( Stream );
                }

            }; // class ClassicIO
        } // namespace FrTOCImpl
    } // namespace Version_8
} // namespace FrameCPP

#endif /* defined( __cplusplus ) && !defined( SWIG ) */

#endif /* FrameCPP_VERSION_8__IMPL__FrTOCClassicIO_HH */
