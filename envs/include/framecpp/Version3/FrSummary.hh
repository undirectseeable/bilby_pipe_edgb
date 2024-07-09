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

#ifndef FrameCPP_VERSION_3_FrSummary_HH
#define FrameCPP_VERSION_3_FrSummary_HH

#include "framecpp/Common/SearchContainer.hh"

#include "framecpp/Version3/FrameSpec.hh"
#include "framecpp/Version3/STRING.hh"

#include "framecpp/Version3/FrVect.hh"

namespace FrameCPP
{
    namespace Version_3
    {
        class FrSummary : public Common::FrameSpec::Object
        {
        public:
            typedef Common::SearchContainer< FrVect, &FrVect::GetName >
                                                 moments_type;
            typedef moments_type::iterator       iterator;
            typedef moments_type::const_iterator const_iterator;

            /// \brief Default constructor
            FrSummary( );
            FrSummary( const FrSummary& Summary );
            FrSummary( const std::string& name,
                       const std::string& comment,
                       const std::string& test );

            static promote_ret_type Promote( INT_2U           Source,
                                             promote_arg_type Obj,
                                             istream_type*    Stream );

            static const char* StructName( );

            static const Common::Description* StructDescription( );

            /// \brief Number of bytes needed to write this structure
            cmn_streamsize_type Bytes( const Common::StreamBase& Stream ) const;

            virtual FrSummary* Create( istream_type& Stream ) const;

            virtual const char* ObjectStructName( ) const;

            virtual void Write( ostream_type& Stream ) const;

            const std::string& GetName( ) const;

            const std::string& GetComment( ) const;

            const std::string& GetTest( ) const;

            const moments_type& RefMoments( ) const;

            moments_type& RefMoments( );

            /// \brief Merge with another FrAdcData
            FrSummary& Merge( const FrSummary& RHS );

            /// \brief comparison operator
            bool operator==( const FrSummary& RHS ) const;

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

            struct fr_summary_data_type
            {
                bool operator==( const fr_summary_data_type& RHS ) const;

                STRING       name;
                STRING       comment;
                STRING       test;
                moments_type moments;
            };

            fr_summary_data_type m_data;

            FrSummary( istream_type& Stream );
        };

        inline FrSummary::promote_ret_type
        FrSummary::Promote( INT_2U           Source,
                            promote_arg_type Obj,
                            istream_type*    Stream )
        {
            return Common::PromoteObject( DATA_FORMAT_VERSION, Source, Obj );
        }

        inline const char*
        FrSummary::StructName( )
        {
            static const char* name = "FrSummary";
            return name;
        }

        inline const std::string&
        FrSummary::GetComment( ) const
        {
            return m_data.comment;
        }

        inline const std::string&
        FrSummary::GetTest( ) const
        {
            return m_data.test;
        }

        inline const FrSummary::moments_type&
        FrSummary::RefMoments( ) const
        {
            return m_data.moments;
        }

        inline FrSummary::moments_type&
        FrSummary::RefMoments( )
        {
            return m_data.moments;
        }

        inline bool
        FrSummary::operator==( const FrSummary& RHS ) const
        {
            return ( m_data == RHS.m_data );
        }
    } // namespace Version_3
} // namespace FrameCPP
#endif /* FrameCPP_VERSION_3_FrSummary_HH */
