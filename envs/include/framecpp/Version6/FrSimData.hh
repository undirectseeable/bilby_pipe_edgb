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

#ifndef FrameCPP_VERSION_6_FrSimData_HH
#define FrameCPP_VERSION_6_FrSimData_HH

#if !defined( SWIGIMPORTED )
#include <vector>
#endif /* ! defined(SWIGIMPORTED) */

#include "framecpp/Common/SearchContainer.hh"
#include "framecpp/Common/TOCInfo.hh"

#include "framecpp/Version4/FrSimData.hh"

#include "framecpp/Version6/FrameSpec.hh"
#include "framecpp/Version6/STRING.hh"

#include "framecpp/Version6/FrHistory.hh"
#include "framecpp/Version6/FrTable.hh"
#include "framecpp/Version6/FrVect.hh"

namespace FrameCPP
{
    namespace Version_6
    {
        //===================================================================
        //===================================================================
        class FrSimDataStorage
        {
        public:
            typedef REAL_8 timeoffset_type;
            typedef REAL_8 fshift_type;
            typedef REAL_4 phase_type;

            static const timeoffset_type DEFAULT_TIME_OFFSET;
            static const fshift_type     DEFAULT_FSHIFT;
            static const phase_type      DEFAULT_PHASE;

            FrSimDataStorage( );
            FrSimDataStorage( const FrSimDataStorage& Source );
            FrSimDataStorage(
                const std::string&    Name,
                const std::string&    Comment,
                const REAL_4          SampleRate,
                const fshift_type     FShift,
                const phase_type      Phase,
                const timeoffset_type TimeOffset = DEFAULT_TIME_OFFSET );

            const std::string& GetName( ) const;
            const std::string& GetComment( ) const;
            REAL_4             GetSampleRate( ) const;
            REAL_8             GetTimeOffset( ) const;
            REAL_8             GetFShift( ) const;
            REAL_4             GetPhase( ) const;

        protected:
            struct data_type
            {
                STRING          name;
                STRING          comment;
                REAL_4          sampleRate;
                timeoffset_type timeOffset;
                fshift_type     fShift;
                phase_type      phase;

                inline FrameCPP::cmn_streamsize_type
                Bytes( const Common::StreamBase& Stream ) const
                {
                    return name.Bytes( ) + comment.Bytes( ) +
                        sizeof( sampleRate ) + sizeof( timeOffset ) +
                        sizeof( fShift ) + sizeof( phase );
                }

                inline bool
                operator==( const data_type& RHS ) const
                {
                    return ( ( this == &RHS ) ||
                             ( ( name == RHS.name ) &&
                               ( comment == RHS.comment ) &&
                               ( sampleRate == RHS.sampleRate ) &&
                               ( timeOffset == RHS.timeOffset ) &&
                               ( fShift == RHS.fShift ) &&
                               ( phase == RHS.phase ) ) );
                }

                void operator( )( Common::IStream& Stream );
                void operator( )( Common::OStream& Stream ) const;
            };

            data_type m_data;
        };

        inline const std::string&
        FrSimDataStorage::GetName( ) const
        {
            return m_data.name;
        }

        inline const std::string&
        FrSimDataStorage::GetComment( ) const
        {
            return m_data.comment;
        }

        inline REAL_4
        FrSimDataStorage::GetSampleRate( ) const
        {
            return m_data.sampleRate;
        }

        inline FrSimDataStorage::timeoffset_type
        FrSimDataStorage::GetTimeOffset( ) const
        {
            return m_data.timeOffset;
        }

        inline FrSimDataStorage::fshift_type
        FrSimDataStorage::GetFShift( ) const
        {
            return m_data.fShift;
        }

        inline FrSimDataStorage::phase_type
        FrSimDataStorage::GetPhase( ) const
        {
            return m_data.phase;
        }

        //===================================================================
        // FrSimDataRefs
        //===================================================================

        using Previous::FrSimDataRefsT;

        typedef FrSimDataRefsT< FrVect, FrTable > FrSimDataRefs;

        //===================================================================
        //===================================================================
        class FrSimData : public Common::FrameSpec::Object,
                          public FrSimDataStorage,
                          public FrSimDataRefs,
                          public Common::TOCInfo
        {
        public:
            //: Default constructor
            FrSimData( );
            FrSimData( const FrSimData& SimData );
            FrSimData( const std::string&    Name,
                       const std::string&    Comment,
                       const REAL_4          SampleRate,
                       const fshift_type     FShift,
                       const phase_type      Phase,
                       const timeoffset_type TimeOffset = DEFAULT_TIME_OFFSET );

            FrSimData( Previous::FrSimData& Source, istream_type* Stream );

            static promote_ret_type Promote( INT_2U           Source,
                                             promote_arg_type Obj,
                                             istream_type*    Stream );

            static const char* StructName( );

            static const Common::Description* StructDescription( );

            //: Number of bytes needed to write this structure
            cmn_streamsize_type Bytes( const Common::StreamBase& Stream ) const;

            virtual FrSimData* Create( istream_type& Stream ) const;

            virtual const char* ObjectStructName( ) const;

            virtual void Write( ostream_type& Stream ) const;

            /// \brief Retrive the name
            const std::string& GetNameSlow( ) const;

            //: Merge with another FrAdcData
            FrSimData& Merge( const FrSimData& RHS );

            /// \brief comparison operator
            bool operator==( const FrSimData& RHS ) const;

            /// \brief comparison operator
            virtual bool
            operator==( const Common::FrameSpec::Object& Obj ) const;

#if WORKING_VIRTUAL_TOCQUERY
            virtual void TOCQuery( int InfoClass, ... ) const;
#endif /*  WORKING_VIRTUAL_TOCQUERY */

        protected:
            /// \brief Down grade an object
            virtual demote_ret_type demote( INT_2U          Target,
                                            demote_arg_type Obj,
                                            istream_type*   Stream ) const;

            /// \brief Upgrade an object
            virtual promote_ret_type promote( INT_2U           Target,
                                              promote_arg_type Obj,
                                              istream_type*    Stream ) const;

#if !WORKING_VIRTUAL_TOCQUERY
            virtual void vTOCQuery( int InfoClass, va_list vl ) const;
#endif /* ! WORKING_VIRTUAL_TOCQUERY */

        private:
            using Common::FrameSpec::Object::Create;

            FrSimData( IStream& Stream );
        };

        inline FrSimData::promote_ret_type
        FrSimData::Promote( INT_2U           Source,
                            promote_arg_type Obj,
                            istream_type*    Stream )
        {
            return Object::PromoteObject< Previous::FrSimData, FrSimData >(
                DATA_FORMAT_VERSION, Source, Obj, Stream );
        }

        inline const char*
        FrSimData::StructName( )
        {
            static const char* name = "FrSimData";
            return name;
        }

        inline bool
        FrSimData::operator==( const FrSimData& RHS ) const
        {
            return ( ( this == &RHS ) ||
                     ( ( m_data == RHS.m_data ) && ( m_refs == RHS.m_refs ) ) );
        }
    } // namespace Version_6
} // namespace FrameCPP
#endif /* FrameCPP_VERSION_6_FrSimData_HH */
