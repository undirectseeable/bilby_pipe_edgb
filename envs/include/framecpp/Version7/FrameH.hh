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

#ifndef FrameCPP_VERSION_7_FrameH_HH
#define FrameCPP_VERSION_7_FrameH_HH

#if !defined( SWIGIMPORTED )
#include "ldastoolsal/types.hh"

#include "framecpp/Version6/FrameH.hh"

#include "framecpp/Version7/FrameSpec.hh"

#include "framecpp/Common/Description.hh"
#include "framecpp/Common/SearchContainer.hh"
#include "framecpp/Common/FrameH.hh"
#include "framecpp/Common/TOCInfo.hh"
#endif /* !defined(SWIGIMPORTED) */

#include "framecpp/Version6/FrameH.hh"

#if !defined( SWIGIMPORTED )
#include "framecpp/Version7/GPSTime.hh"
#include "framecpp/Version7/STRING.hh"
#include "framecpp/Version7/PTR_STRUCT.hh"
#include "framecpp/Version7/FrSE.hh"

#include "framecpp/Version7/FrDetector.hh"
#include "framecpp/Version7/FrEvent.hh"
#include "framecpp/Version7/FrHistory.hh"
#include "framecpp/Version7/FrProcData.hh"
#include "framecpp/Version7/FrRawData.hh"
#include "framecpp/Version7/FrSimData.hh"
#include "framecpp/Version7/FrSimEvent.hh"
#include "framecpp/Version7/FrSummary.hh"
#include "framecpp/Version7/FrTable.hh"
#include "framecpp/Version7/FrVect.hh"
#endif /* !defined(SWIGIMPORTED) */

#if !defined( SWIGIMPORTED )
namespace FrameCPP
{
    namespace Common
    {
        class Description;
    }

    namespace Version_7
    {
        //===================================================================
        /// \brief Non-PTR_STRUCT elements of the FrameH structure
        ///
        /// This class contains the data members of the FrameH structure
        /// that are not refernced by a pointer.
        /// This allows for easier migration into future
        /// frame specifications.
        //===================================================================

        typedef Previous::FrameHNPS FrameHNPS;

        //===================================================================
        /// \brief PTR_STRUCT elements of the FrmaeH structure.
        ///
        /// This class contains the PTR_STRUCT references of the FrameH
        /// structure.
        /// This allows for easier migration into future
        /// frame specifications.
        //===================================================================
        typedef Previous::FrameHPST< FrDetector,
                                     FrEvent,
                                     FrHistory,
                                     FrProcData,
                                     FrRawData,
                                     FrSimData,
                                     FrSimEvent,
                                     FrSummary,
                                     FrTable,
                                     FrVect >
            FrameHPS;

        //===================================================================
        //===================================================================
        class FrameH : public Common::FrameH, public FrameHNPS, public FrameHPS
        {
        public:
            typedef Common::FrameH::assign_stream_type assign_stream_type;

            /// \brief Default constructor
            FrameH( );
            FrameH( const FrameH& frame );
            FrameH( const std::string& name,
                    INT_4S             run,
                    INT_4U             frame,
                    const GPSTime&     time,
                    INT_2U             uLeapS,
                    const REAL_8       dt,
                    INT_4U             dqual = 0 );
            FrameH( const FrameHNPS& Source );
            FrameH( const Previous::FrameH& Source, istream_type* Stream );
            ~FrameH( );

            static promote_ret_type Promote( INT_2U           Source,
                                             promote_arg_type Obj,
                                             istream_type*    Stream );

            static const char* StructName( );

            static const Common::Description* StructDescription( );

            /// \brief Number of bytes needed to write this structure
            cmn_streamsize_type Bytes( const Common::StreamBase& Stream ) const;

            //-----------------------------------------------------------------
            /// \brief Virtual constructor
            //-----------------------------------------------------------------
            virtual FrameH* Clone( ) const;

            virtual FrameH* Create( istream_type& Stream ) const;

            virtual const char* ObjectStructName( ) const;

            /// \brief Write the structure to the stream
            virtual void Write( ostream_type& Stream ) const;

            /// \brief comparison operator
            bool operator==( const FrameH& RHS ) const;

            /// \brief comparison operator
            virtual bool
            operator==( const Common::FrameSpec::Object& Obj ) const;

        protected:
            //-----------------------------------------------------------------
            /// \brief Verify the object as being valid
            ///
            /// \param[in] Verifier
            ///     The instance of the Verify object where state information
            ///     is stored.
            /// \param[in] Stream
            ///     The input stream from which the object is being read.
            //-----------------------------------------------------------------
            virtual void VerifyObject( Common::Verify&       Verifier,
                                       Common::IFrameStream& Stream ) const;
            //-----------------------------------------------------------------
            // Interface routines
            //-----------------------------------------------------------------
            virtual void readSubset( istream_type& Stream, INT_4U ElementMask );

            //-----------------------------------------------------------------
            /// \brief Frame start time in seconds
            //-----------------------------------------------------------------
            virtual start_time_normalized_type normalizedStartTime( ) const;

            //-----------------------------------------------------------------
            /// \brief Duration of the frame
            //-----------------------------------------------------------------
            virtual delta_t_normalized_type normalizedDeltaT( ) const;

            //-----------------------------------------------------------------
            /// \brief Assign the contents of the instance
            ///
            /// \param[in] Stream
            ///     An input stream from which to read information for
            ///     the instance.
            ///
            /// \note
            ///     This has been hidden so programmers are not tempted to
            ///     bypass usage of IFrameStream as the input stream.
            //-----------------------------------------------------------------
            virtual void assign( assign_stream_type& Stream );

        private:
            using Common::FrameSpec::Object::Create;

            FrameH( istream_type& Stream );

            /// \brief Down grade an object
            virtual demote_ret_type demote( INT_2U          Target,
                                            demote_arg_type Obj,
                                            istream_type*   Stream ) const;

            /// \brief Upgrade an object
            virtual promote_ret_type promote( INT_2U           Target,
                                              promote_arg_type Obj,
                                              istream_type*    Stream ) const;
        };

        inline FrameH::FrameH( const Previous::FrameH& Source,
                               istream_type*           Stream )
            : Common::FrameH( StructDescription( ) ), FrameHNPS( Source )
        {
            if ( Stream )
            {
                const INT_2U max_ref = Previous::FrameHPS::MAX_REF;

                Stream->ReplaceRef( RefType( ), Source.RefType( ), max_ref );
                Stream->ReplaceRef( RefUser( ), Source.RefUser( ), max_ref );
                Stream->ReplaceRef(
                    RefDetectSim( ), Source.RefDetectSim( ), max_ref );
                Stream->ReplaceRef(
                    RefDetectProc( ), Source.RefDetectProc( ), max_ref );
                Stream->ReplaceRef(
                    RefHistory( ), Source.RefHistory( ), max_ref );
                Stream->ReplacePtr(
                    AddressOfRawData( ), Source.AddressOfRawData( ), max_ref );
                Stream->ReplaceRef(
                    RefProcData( ), Source.RefProcData( ), max_ref );
                Stream->ReplaceRef(
                    RefSimData( ), Source.RefSimData( ), max_ref );
                Stream->ReplaceRef( RefEvent( ), Source.RefEvent( ), max_ref );
                Stream->ReplaceRef(
                    RefSimEvent( ), Source.RefSimEvent( ), max_ref );
                Stream->ReplaceRef(
                    RefSummaryData( ), Source.RefSummaryData( ), max_ref );
                Stream->ReplaceRef(
                    RefAuxData( ), Source.RefAuxData( ), max_ref );
                Stream->ReplaceRef(
                    RefAuxTable( ), Source.RefAuxTable( ), max_ref );
            }
        }

        inline FrameH::promote_ret_type
        FrameH::Promote( INT_2U           Source,
                         promote_arg_type Obj,
                         istream_type*    Stream )
        {
            return Object::PromoteObject< Previous::FrameH, FrameH >(
                DATA_FORMAT_VERSION, Source, Obj, Stream );
        }

        inline const char*
        FrameH::StructName( )
        {
            static const char* name = "FrameH";
            return name;
        }

        inline bool
        FrameH::operator==( const FrameH& RHS ) const
        {
            return ( ( m_data == RHS.m_data ) && ( m_refs == RHS.m_refs ) );
        }

        //-------------------------------------------------------------------
        //-------------------------------------------------------------------
        inline start_time_normalized_type
        FrameH::normalizedStartTime( ) const
        {
            return GetGTime( );
        }

        //-------------------------------------------------------------------
        //-------------------------------------------------------------------
        inline delta_t_normalized_type
        FrameH::normalizedDeltaT( ) const
        {
            return GetDt( );
        }
    } // namespace Version_7
} // namespace FrameCPP
#endif /* !defined(SWIGIMPORTED) */
#endif /* FrameCPP_VERSION_7_FrameH_HH */
