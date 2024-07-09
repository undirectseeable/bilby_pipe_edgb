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

#ifndef FrameCPP_VERSION_7_FrSimData_HH
#define FrameCPP_VERSION_7_FrSimData_HH

#ifndef SWIGIMPORTED
#include <vector>
#endif /* SWIGIMPORTED */

#include "framecpp/Common/SearchContainer.hh"
#include "framecpp/Common/TOCInfo.hh"

#include "framecpp/Version6/FrSimData.hh"

#include "framecpp/Version7/FrameSpec.hh"
#include "framecpp/Version7/STRING.hh"

#include "framecpp/Version7/FrHistory.hh"
#include "framecpp/Version7/FrTable.hh"
#include "framecpp/Version7/FrVect.hh"

namespace FrameCPP
{
    namespace Version_7
    {
        //===================================================================
        //===================================================================
        class FrSimDataStorage
        {
        public:
            typedef REAL_8 sampleRate_type;

            static const REAL_8 DEFAULT_TIME_OFFSET;

            FrSimDataStorage( );
            FrSimDataStorage( const FrSimDataStorage& Source );
            FrSimDataStorage( const std::string&    Name,
                              const std::string&    Comment,
                              const sampleRate_type SampleRate,
                              const REAL_8          FShift,
                              const REAL_4          Phase,
                              const REAL_8          TimeOffset );
            FrSimDataStorage( const Previous::FrSimDataStorage& Source );

            const std::string& GetName( ) const;
            const std::string& GetComment( ) const;
            sampleRate_type    GetSampleRate( ) const;
            REAL_8             GetTimeOffset( ) const;
            REAL_8             GetFShift( ) const;
            REAL_4             GetPhase( ) const;

            void SetSampleRate( sampleRate_type SampleRate );

        protected:
            struct fr_sim_data_data_type
            {
                STRING          name;
                STRING          comment;
                sampleRate_type sampleRate;
                REAL_8          timeOffset;
                REAL_8          fShift;
                REAL_4          phase;

                inline FrameCPP::cmn_streamsize_type
                Bytes( const Common::StreamBase& Stream ) const
                {
                    return name.Bytes( ) + comment.Bytes( ) +
                        sizeof( sampleRate ) + sizeof( timeOffset ) +
                        sizeof( fShift ) + sizeof( phase );
                }

                inline bool
                operator==( const fr_sim_data_data_type& RHS ) const
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

            fr_sim_data_data_type m_data;
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

        inline FrSimDataStorage::sampleRate_type
        FrSimDataStorage::GetSampleRate( ) const
        {
            return m_data.sampleRate;
        }

        inline REAL_8
        FrSimDataStorage::GetTimeOffset( ) const
        {
            return m_data.timeOffset;
        }

        inline REAL_8
        FrSimDataStorage::GetFShift( ) const
        {
            return m_data.fShift;
        }

        inline REAL_4
        FrSimDataStorage::GetPhase( ) const
        {
            return m_data.phase;
        }

        inline void
        FrSimDataStorage::SetSampleRate( sampleRate_type SampleRate )
        {
            m_data.sampleRate = SampleRate;
#if WORKING
            //-----------------------------------------------------------------
            /// \todo
            /// Modifications to the sample rate need also be reflected in the
            /// corrisponding FrVect structures.
            //-----------------------------------------------------------------
            for ( fr_sim_data_data_type::iterator cur = RefData( ).begin( ),
                                                  last = RefData( ).end( );
                  cur != last;
                  ++cur )
            {
                cur->
            }
#endif /* WORKING */
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
            /// \brief Default constructor
            FrSimData( );

            FrSimData( const FrSimData& SimData );

            FrSimData( const std::string&    Name,
                       const std::string&    Comment,
                       const sampleRate_type SampleRate,
                       const REAL_8          FShift,
                       const REAL_4          Phase,
                       const REAL_8          TimeOffset = DEFAULT_TIME_OFFSET );

            FrSimData( Previous::FrSimData& Source, istream_type* Stream );

            static promote_ret_type Promote( INT_2U           Source,
                                             promote_arg_type Obj,
                                             istream_type*    Stream );

            static const char* StructName( );

            static const Common::Description* StructDescription( );

            /// \brief Number of bytes needed to write this structure
            cmn_streamsize_type Bytes( const Common::StreamBase& Stream ) const;

            virtual FrSimData* Create( istream_type& Stream ) const;

            virtual const char* ObjectStructName( ) const;

            virtual void Write( ostream_type& Stream ) const;

            /// \brief Retrive the name
            const std::string& GetNameSlow( ) const;

            /// \brief Merge with another FrAdcData
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

            FrSimData( istream_type& Stream );
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
    } // namespace Version_7
} // namespace FrameCPP
#endif /* FrameCPP_VERSION_7_FrSimData_HH */
