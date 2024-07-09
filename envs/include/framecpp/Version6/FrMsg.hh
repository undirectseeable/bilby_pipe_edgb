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

#ifndef FrameCPP_VERSION_6_FrMsg_HH
#define FrameCPP_VERSION_6_FrMsg_HH

#if !defined( SWIGIMPORTED )
#include <vector>
#endif /* ! defined(SWIGIMPORTED) */

#include "ldastoolsal/types.hh"

#include "framecpp/Common/TOCInfo.hh"

#include "framecpp/Version4/FrMsg.hh"

#include "framecpp/Version6/FrameSpec.hh"
#include "framecpp/Version6/GPSTime.hh"
#include "framecpp/Version6/STRING.hh"

namespace FrameCPP
{
    namespace Version_6
    {
        class FrMsg : public Common::FrameSpec::Object, public Common::TOCInfo
        {
        public:
            typedef INT_4U severity_type;

            static constexpr severity_type const DEFAULT_SEVERITY{ 0 };

            //: Default constructor
            FrMsg( );

            FrMsg( const FrMsg& Source );

            FrMsg( const std::string& Alarm,
                   const std::string& Message,
                   INT_4U             Severity,
                   const GPSTime&     GTime );

            FrMsg( Previous::FrMsg& Source, istream_type* Stream );

            static const char* StructName( );

            static const Common::Description* StructDescription( );

            //: Number of bytes needed to write this structure
            cmn_streamsize_type Bytes( const Common::StreamBase& Stream ) const;

            virtual FrMsg* Create( istream_type& Stream ) const;

            virtual const char* ObjectStructName( ) const;

#if WORKING_VIRTUAL_TOCQUERY
            void TOCQuery( int InfoClass, ... ) const;
#endif /*  WORKING_VIRTUAL_TOCQUERY */

            virtual void Write( ostream_type& Stream ) const;

            //: Accessors
            const std::string& GetAlarm( ) const;
            const std::string&
            GetMessage( ) const
            {
                return m_data.message;
            }
            INT_4U
            GetSeverity( ) const
            {
                return m_data.severity;
            }
            const GPSTime&
            GetGTime( ) const
            {
                return m_data.GTime;
            }

            //: Merge with another FrAdcData
            FrMsg& Merge( const FrMsg& RHS );

            static promote_ret_type Promote( INT_2U           Source,
                                             promote_arg_type Obj,
                                             istream_type*    Stream );

            /// \brief comparison operator
            bool operator==( const FrMsg& RHS ) const;

            /// \brief comparison operator
            virtual bool
            operator==( const Common::FrameSpec::Object& Obj ) const;

        protected:
            /// \brief Down grade an object
            virtual demote_ret_type demote( INT_2U          Target,
                                            demote_arg_type Obj,
                                            istream_type*   Stream ) const;

            virtual promote_ret_type promote( INT_2U           Target,
                                              promote_arg_type Obj,
                                              istream_type*    Stream ) const;

#if !WORKING_VIRTUAL_TOCQUERY
            virtual void vTOCQuery( int InfoClass, va_list vl ) const;
#endif /* ! WORKING_VIRTUAL_TOCQUERY */

        private:
            using Common::FrameSpec::Object::Create;

            struct fr_msg_data_type
            {
                bool operator==( const fr_msg_data_type& RHS ) const;

                STRING  alarm;
                STRING  message;
                INT_4U  severity;
                GPSTime GTime;
            };

            fr_msg_data_type m_data;

            FrMsg( istream_type& Stream );
        };

        inline const char*
        FrMsg::StructName( )
        {
            static const char* name = "FrMsg";
            return name;
        }

        inline bool
        FrMsg::operator==( const FrMsg& RHS ) const
        {
            return ( m_data == RHS.m_data );
        }

    } // namespace Version_6
} // namespace FrameCPP
#endif /* FrameCPP_VERSION_6_FrMsg_HH */
