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

#ifndef FrameCPP_VERSION_8_FrameH_HH
#define FrameCPP_VERSION_8_FrameH_HH

#include "framecpp/Version8/impl/FrameHClassicIO.hh"

#if defined( __cplusplus ) && !defined( SWIGIMPORTED )
namespace FrameCPP
{
    namespace Version_8
    {
        //===================================================================
        /// \brief Event data
        //===================================================================
        class FrameH : public FrameHImpl::ClassicIO< FrameH >
        {
        public:
            //-----------------------------------------------------------------
            /// \brief Default constructor
            //-----------------------------------------------------------------
            FrameH( );

            //-----------------------------------------------------------------
            /// \brief Explicate construction
            ///
            /// \param[in] name
            ///     Name of project or other experiment description
            /// \param[in] run
            ///     Run number (number < 0 reserved for simulated data);
            ///     monotonic for experimental runs.
            /// \param[in] frame
            ///     Frame number, monotonically increasing until end of run,
            ///     re-starting from 0 with each new run.
            /// \param[in] time
            ///     Frame start time in GPS units.
            /// \param[in] uLeapS
            ///     The integer number of leap seconds between GPS/TAI and
            ///     UTC in the epoch when the frame is written.
            /// \param[in] dt
            ///     Frame length in seconds
            /// \param[in] dqual
            ///     Data quality flag
            ///
            /// \return
            ///     A new instance of this object.
            //-----------------------------------------------------------------
            FrameH( const name_type&  name,
                    run_type          run,
                    frame_type        frame,
                    const GTime_type& time,
                    ULeapS_type       uLeapS,
                    const dt_type     dt,
                    dataQuality_type  dqual = 0 );

            //-----------------------------------------------------------------
            /// \brief Copy Constructor
            ///
            /// \param[in] frame
            ///     Frame to use as the base
            ///
            /// \return
            ///     A new instance of the object.
            //-----------------------------------------------------------------
            FrameH( const FrameH& frame );

            //-----------------------------------------------------------------
            /// \brief Upconvert constructor
            ///
            /// \param[in] Source
            ///     An instance of a similiar object from a previous version
            ///     of the frame specification.
            /// \param[in] Stream
            ///     The stream from which the origional object was read.
            /// \return
            ///     A new instance of the object.
            //-----------------------------------------------------------------
            FrameH( const Previous::FrameH& Source, istream_type* Stream );

            //-----------------------------------------------------------------
            /// \brief Virtual constructor
            //-----------------------------------------------------------------
            virtual inline FrameH*
            Clone( ) const
            {
                return new FrameH( *this );
            }

            //-----------------------------------------------------------------
            /// \brief equality operator
            ///
            /// \param[in] RHS
            ///     The FrameH object to be compared.
            ///
            /// \return
            ///     The value true is returned if this object is equivelent
            ///     to the RHS instance; false otherwise.
            //-----------------------------------------------------------------
            virtual bool
            operator==( const Common::FrameSpec::Object& Obj ) const;

            bool
            operator==( const FrameH& RHS ) const
            {
                return Data::operator==( RHS );
            }

        protected:
        };

    } // namespace Version_8
} // namespace FrameCPP

#endif /* defined( __cplusplus ) && !defined( SWIGIMPORTED ) */

#if 0
#if !defined( SWIGIMPORTED )
#include "ldastoolsal/types.hh"

#include "framecpp/Version8/FrameSpec.hh"

#include "framecpp/Common/Description.hh"
#include "framecpp/Common/SearchContainer.hh"
#include "framecpp/Common/FrameH.hh"
#include "framecpp/Common/TOCInfo.hh"
#endif /* !defined(SWIGIMPORTED) */

#include "framecpp/Version7/FrameH.hh"

#if !defined( SWIGIMPORTED )
namespace FrameCPP
{
    namespace Common
    {
        class Description;
    }

    namespace Version_8
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

#if 1
        typedef Version_6::FrameHPST< FrDetector,
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
#else /* 0 */
        typedef Previous::FrameHPS FrameHPS;
#endif /* 0 */

        //===================================================================
        /// \brief Frame Header
        //===================================================================
        class FrameH : public ObjectWithChecksum< Common::FrameH >,
                       public FrameHNPS,
                       public FrameHPS
        {
        public:
            //-----------------------------------------------------------------
            /// \param[in] frame
            ///     Frame to use as the base
            //-----------------------------------------------------------------
            FrameH( const FrameH& frame );

            //-----------------------------------------------------------------
            /// \brief Copy constructor
            ///
            /// \param[in] Source
            ///     The non-pointer portion of the frame header.
            //-----------------------------------------------------------------
            FrameH( const FrameHNPS& Source );

            //-----------------------------------------------------------------
            /// \brief Destructor
            //-----------------------------------------------------------------
            ~FrameH( );

            //-----------------------------------------------------------------
            /// \brief Virtual constructor
            //-----------------------------------------------------------------
            virtual FrameH* Clone( ) const;

            //-----------------------------------------------------------------
            /// \brief The name structure name of this object.
            ///
            /// \return
            ///     The name of the structure as specified by the frame
            ///     specification.
            //-----------------------------------------------------------------
            static const char* StructName( );

          //-----------------------------------------------------------------
          /// \brief equality operator
          ///
          /// \param[in] RHS
          ///     The FrameH object to be compared.
          ///
          /// \return
          ///     The value true is returned if this object is equivelent
          ///     to the RHS instance; false otherwise.
          //-----------------------------------------------------------------
          bool operator==( const FrameH& RHS ) const;

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

        private:
            //-----------------------------------------------------------------
            /// \brief Object with checksum data.
            //-----------------------------------------------------------------
            typedef ObjectWithChecksum< Common::FrameH > object_type;

            //-----------------------------------------------------------------
            /// \brief Constructor via stream
            //-----------------------------------------------------------------
            FrameH( istream_type& Stream );

        };

        //-------------------------------------------------------------------
        //-------------------------------------------------------------------
        inline FrameH::FrameH( const Previous::FrameH& Source,
                               istream_type*           Stream )
            : object_type( StructDescription( ) ), FrameHNPS( Source )
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

        //-------------------------------------------------------------------
        //-------------------------------------------------------------------
        inline FrameH::promote_ret_type
        FrameH::Promote( INT_2U           Source,
                         promote_arg_type Obj,
                         istream_type*    Stream )
        {
            return Object::PromoteObject< Previous::FrameH, FrameH >(
                DATA_FORMAT_VERSION, Source, Obj, Stream );
        }

        //-------------------------------------------------------------------
        //-------------------------------------------------------------------
        inline const char*
        FrameH::StructName( )
        {
            static const char* name = "FrameH";
            return name;
        }

        //-------------------------------------------------------------------
        //-------------------------------------------------------------------
        inline bool
        FrameH::operator==( const FrameH& RHS ) const
        {
            return ( ( m_data == RHS.m_data ) && ( m_refs == RHS.m_refs ) );
        }

    } // namespace Version_8
} // namespace FrameCPP

#endif /* !defined(SWIGIMPORTED) */
#endif /* 0 */

#endif /* FrameCPP_VERSION_8_FrameH_HH */
