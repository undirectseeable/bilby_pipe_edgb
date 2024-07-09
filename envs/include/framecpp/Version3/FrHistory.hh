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

#ifndef FrameCPP_VERSION_3_FrHistory_HH
#define FrameCPP_VERSION_3_FrHistory_HH

#include "framecpp/Version3/FrameSpec.hh"
#include "framecpp/Version3/STRING.hh"

namespace FrameCPP
{
    namespace Version_3
    {
        class FrHistory : public Common::FrameSpec::Object
        {
        public:
            /// \brief Default constructor
            FrHistory( );

            FrHistory( const FrHistory& Source );

            FrHistory( const std::string& Name,
                       INT_4U             Time,
                       const std::string& Comment );

            static const char* StructName( );

            static const Common::Description* StructDescription( );

            /// \brief Number of bytes needed to write this structure
            cmn_streamsize_type Bytes( const Common::StreamBase& Stream ) const;

            virtual FrHistory* Create( istream_type& Stream ) const;

            virtual const char* ObjectStructName( ) const;

            virtual void Write( ostream_type& Stream ) const;

            virtual std::string ErrorInfo( ) const;

            // Accessors
            const std::string& GetName( ) const;

            INT_4U
            GetTime( ) const
            {
                return m_data.time;
            }
            const std::string&
            GetComment( ) const
            {
                return m_data.comment;
            }

            /// \brief Merge with another FrAdcData
            FrHistory& Merge( const FrHistory& RHS );

            //-----------------------------------------------------------------
            /// \brief Promote object
            ///
            /// \param[in] Source
            /// \param[in] Obj
            /// \param[in] Stream
            ///
            /// \return
            ///     Promoted version of Obj.
            //-----------------------------------------------------------------
            static promote_ret_type Promote( INT_2U           Source,
                                             promote_arg_type Obj,
                                             istream_type*    Stream );

            /// \brief comparison operator
            bool operator==( const FrHistory& RHS ) const;

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

            struct fr_history_data_type
            {
                STRING name;
                INT_4U time;
                STRING comment;

                bool operator==( const fr_history_data_type& RHS ) const;
            };

            fr_history_data_type m_data;

            FrHistory( istream_type& Stream );
        };

        inline const char*
        FrHistory::StructName( )
        {
            static const char* name = "FrHistory";
            return name;
        }

        inline bool
        FrHistory::operator==( const FrHistory& RHS ) const
        {
            return ( m_data == RHS.m_data );
        }
    } // namespace Version_3
} // namespace FrameCPP
#endif /* FrameCPP_VERSION_3_FrHistory_HH */
