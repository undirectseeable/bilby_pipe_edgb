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

#ifndef FrameCPP_VERSION_3_FrRawData_HH
#define FrameCPP_VERSION_3_FrRawData_HH

#if !defined( SWIGIMPORTED )
#include <string>
#include <vector>
#endif /* ! defined(SWIGIMPORTED) */

#include "framecpp/Common/SearchContainer.hh"

#include "framecpp/Version3/FrameSpec.hh"
#include "framecpp/Version3/FrAdcData.hh"
#include "framecpp/Version3/FrMsg.hh"
#include "framecpp/Version3/FrSerData.hh"
#include "framecpp/Version3/FrVect.hh"
#include "framecpp/Version3/STRING.hh"

namespace FrameCPP
{
    namespace Version_3
    {
        class FrRawData : public Common::FrameSpec::Object
        {
        public:
            typedef Common::SearchContainer< FrSerData, &FrSerData::GetName >
                                                  firstSer_type;
            typedef firstSer_type::iterator       firstSer_iterator;
            typedef firstSer_type::const_iterator const_firstSer_iterator;
            typedef firstSer_type::hash_iterator  firstSer_hash_iterator;
            typedef firstSer_type::const_hash_iterator
                const_firstSer_hash_iterator;

            typedef Common::SearchContainer< FrAdcData,
                                             &FrAdcData::GetNameSlow >
                                                  firstAdc_type;
            typedef firstAdc_type::iterator       firstAdc_iterator;
            typedef firstAdc_type::const_iterator const_firstAdc_iterator;
            typedef firstAdc_type::hash_iterator  firstAdc_hash_iterator;
            typedef firstAdc_type::const_hash_iterator
                const_firstAdc_hash_iterator;

            typedef Common::SearchContainer< FrMsg, &FrMsg::GetAlarm >
                                                     logMsg_type;
            typedef logMsg_type::iterator            logMsg_iterator;
            typedef logMsg_type::const_iterator      const_logMsg_iterator;
            typedef logMsg_type::hash_iterator       logMsg_hash_iterator;
            typedef logMsg_type::const_hash_iterator const_logMsg_hash_iterator;

            typedef Common::SearchContainer< FrVect, &FrVect::GetName >
                                                   more_type;
            typedef more_type::iterator            more_iterator;
            typedef more_type::const_iterator      const_more_iterator;
            typedef more_type::hash_iterator       more_hash_iterator;
            typedef more_type::const_hash_iterator const_more_hash_iterator;

            /// \brief Default constructor
            FrRawData( );
            FrRawData( const FrRawData& rawData );
            FrRawData( const std::string& name );
            ~FrRawData( );

            virtual cmn_streamsize_type
            Bytes( const Common::StreamBase& Stream ) const;

            virtual FrRawData* Create( istream_type& Stream ) const;

            virtual const char* ObjectStructName( ) const;

            /// \brief Write the structure to the stream
            virtual void Write( ostream_type& Stream ) const;

            const std::string&   GetName( ) const;
            const firstSer_type& RefFirstSer( ) const;
            firstSer_type&       RefFirstSer( );
            const firstAdc_type& RefFirstAdc( ) const;
            firstAdc_type&       RefFirstAdc( );
            const logMsg_type&   RefLogMsg( ) const;
            logMsg_type&         RefLogMsg( );
            const more_type&     RefMore( ) const;
            more_type&           RefMore( );

            static const Common::FrameSpec::Info::frame_object_types CLASS_ID =
                Common::FrameSpec::Info::FSI_FR_RAW_DATA;

            static promote_ret_type Promote( INT_2U           Source,
                                             promote_arg_type Obj,
                                             istream_type*    Stream );

            static const char* StructName( );

            static const Common::Description* StructDescription( );

            /// \brief comparison operator
            bool operator==( const FrRawData& RHS ) const;

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

            struct fr_raw_data_type
            {
                fr_raw_data_type( );
                bool operator==( const fr_raw_data_type& RHS ) const;

                STRING        name;
                firstSer_type firstSer;
                firstAdc_type firstAdc;
                logMsg_type   logMsg;
                more_type     more;
            };

            FrRawData( istream_type& Stream );

            fr_raw_data_type m_data;
        };

        inline FrRawData::promote_ret_type
        FrRawData::Promote( INT_2U           Source,
                            promote_arg_type Obj,
                            istream_type*    Stream )
        {
            return Common::PromoteObject( DATA_FORMAT_VERSION, Source, Obj );
        }

        inline const char*
        FrRawData::StructName( )
        {
            static const char* name = "FrRawData";
            return name;
        }

        inline const FrRawData::firstSer_type&
        FrRawData::RefFirstSer( ) const
        {
            return m_data.firstSer;
        }

        inline FrRawData::firstSer_type&
        FrRawData::RefFirstSer( )
        {
            return m_data.firstSer;
        }

        inline const FrRawData::firstAdc_type&
        FrRawData::RefFirstAdc( ) const
        {
            return m_data.firstAdc;
        }

        inline FrRawData::firstAdc_type&
        FrRawData::RefFirstAdc( )
        {
            return m_data.firstAdc;
        }

        inline const FrRawData::logMsg_type&
        FrRawData::RefLogMsg( ) const
        {
            return m_data.logMsg;
        }

        inline FrRawData::logMsg_type&
        FrRawData::RefLogMsg( )
        {
            return m_data.logMsg;
        }

        inline const FrRawData::more_type&
        FrRawData::RefMore( ) const
        {
            return m_data.more;
        }

        inline FrRawData::more_type&
        FrRawData::RefMore( )
        {
            return m_data.more;
        }

        inline bool
        FrRawData::operator==( const FrRawData& RHS ) const
        {
            return ( m_data == RHS.m_data );
        }

        inline bool
        FrRawData::fr_raw_data_type::
        operator==( const fr_raw_data_type& RHS ) const
        {
            return ( ( this == &RHS ) ||
                     ( ( name == RHS.name ) && ( firstSer == RHS.firstSer ) &&
                       ( firstAdc == RHS.firstAdc ) &&
                       ( logMsg == RHS.logMsg ) && ( more == RHS.more ) ) );
        }
    } // namespace Version_3
} // namespace FrameCPP
#endif /* FrameCPP_VERSION_3_FrRawData_HH */
