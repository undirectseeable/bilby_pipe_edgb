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

#ifndef FrameCPP_VERSION_3_FrSerData_HH
#define FrameCPP_VERSION_3_FrSerData_HH

#if !defined( SWIGIMPORTED )
#include <vector>
#endif /* ! defined(SWIGIMPORTED) */

#include "framecpp/Common/SearchContainer.hh"

#include "framecpp/Version3/FrameSpec.hh"
#include "framecpp/Version3/STRING.hh"
#include "framecpp/Version3/GPSTime.hh"

#include "framecpp/Version3/FrVect.hh"

namespace FrameCPP
{
    namespace Version_3
    {
        class FrSerData : public Common::FrameSpec::Object
        {
        public:
            typedef Common::SearchContainer< FrVect, &FrVect::GetName >
                                                serial_type;
            typedef serial_type::iterator       iterator;
            typedef serial_type::const_iterator const_iterator;

            typedef Common::SearchContainer< FrVect, &FrVect::GetName >
                                              more_type;
            typedef more_type::iterator       more_iterator;
            typedef more_type::const_iterator const_more_iterator;

            /// \brief Default constructor
            FrSerData( );
            FrSerData( const FrSerData& serData );
            FrSerData( const std::string& name,
                       const GPSTime&     time,
                       REAL_4             sampleRate );

            static promote_ret_type Promote( INT_2U           Source,
                                             promote_arg_type Obj,
                                             istream_type*    Stream );

            static const char* StructName( );

            static const Common::Description* StructDescription( );

            /// \brief Number of bytes needed to write this structure
            cmn_streamsize_type Bytes( const Common::StreamBase& Stream ) const;

            virtual FrSerData* Create( istream_type& Stream ) const;

            virtual const char* ObjectStructName( ) const;

            virtual void Write( ostream_type& Stream ) const;

            const std::string& GetName( ) const;
            const GPSTime&     GetTime( ) const;
            REAL_4             GetSampleRate( ) const;
            const std::string& GetData( ) const;

            void SetData( const std::string& Data );

            const serial_type& RefSerial( ) const;
            serial_type&       RefSerial( );
            const more_type&   RefMore( ) const;
            more_type&         RefMore( );

            /// \brief Merge with another FrAdcData
            FrSerData& Merge( const FrSerData& RHS );

            /// \brief comparison operator
            bool operator==( const FrSerData& RHS ) const;

            /// \brief comparison operator
            virtual bool
            operator==( const Common::FrameSpec::Object& Obj ) const;

        protected:
            /// \brief Down grade an object
            virtual demote_ret_type demote( INT_2U          Target,
                                            demote_arg_type Obj,
                                            istream_type*   Stream ) const;

            /// \brief Upgrade an object
            virtual promote_ret_type promote( INT_2U           Target,
                                              promote_arg_type Obj,
                                              istream_type*    Stream ) const;

        private:
            using Common::FrameSpec::Object::Create;

            struct fr_ser_data_data_type
            {
                bool operator==( const fr_ser_data_data_type& RHS ) const;

                STRING      name;
                GPSTime     time;
                REAL_4      sampleRate;
                STRING      data;
                serial_type serial;
                more_type   more;
            };

            fr_ser_data_data_type m_data;

            FrSerData( istream_type& Stream );
        };

        inline FrSerData::promote_ret_type
        FrSerData::Promote( INT_2U           Source,
                            promote_arg_type Obj,
                            istream_type*    Stream )
        {
            return Common::PromoteObject( DATA_FORMAT_VERSION, Source, Obj );
        }

        inline const char*
        FrSerData::StructName( )
        {
            static const char* name = "FrSerData";
            return name;
        }

        inline const GPSTime&
        FrSerData::GetTime( ) const
        {
            return m_data.time;
        }

        inline REAL_4
        FrSerData::GetSampleRate( ) const
        {
            return m_data.sampleRate;
        }

        inline const std::string&
        FrSerData::GetData( ) const
        {
            return m_data.data;
        }

        inline void
        FrSerData::SetData( const std::string& Data )
        {
            m_data.data = Data;
            return;
        }

        inline const FrSerData::serial_type&
        FrSerData::RefSerial( ) const
        {
            return m_data.serial;
        }

        inline FrSerData::serial_type&
        FrSerData::RefSerial( )
        {
            return m_data.serial;
        }

        inline const FrSerData::more_type&
        FrSerData::RefMore( ) const
        {
            return m_data.more;
        }

        inline FrSerData::more_type&
        FrSerData::RefMore( )
        {
            return m_data.more;
        }

        inline bool
        FrSerData::operator==( const FrSerData& RHS ) const
        {
            return ( m_data == RHS.m_data );
        }
    } // namespace Version_3
} // namespace FrameCPP
#endif /* FrameCPP_VERSION_3_FrSerData_HH */
