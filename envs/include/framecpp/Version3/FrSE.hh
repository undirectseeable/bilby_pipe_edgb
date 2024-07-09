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

#ifndef FrameCPP__VERSION_3__FrSE_HH
#define FrameCPP__VERSION_3__FrSE_HH

#include "framecpp/Common/FrameSpec.hh"

#include "framecpp/Version3/STRING.hh"

namespace FrameCPP
{
    namespace Version_3
    {
        class FrSE : public Common::FrameSpec::Object
        {
        public:
            using Common::FrameSpec::Object::Create;

            static const char* StructName( );

            /// \brief Default constructor
            FrSE( );

            /// \brief constructor
            FrSE( const std::string& Name,
                  const std::string& ClassId,
                  const std::string& Comment = "" );

            /// \brief Desctructor
            virtual ~FrSE( );

            /// \brief Return the number of bytes needed to write this object
            INT_8U Bytes( const Common::StreamBase& Stream ) const;

            virtual const char* ObjectStructName( ) const;

            /// \brief Return class of object
            std::string GetClass( ) const;

            /// \brief Return comment of object
            std::string GetComment( ) const;

            /// \brief Return name of object
            std::string GetName( ) const;

            /// \brief Create a new instance of the object based on the input
            /// stream
            virtual FrSE* Create( istream_type& Stream ) const;

            /// \brief Create a new instance of the object based on an instance
            virtual FrSE* Clone( ) const;

            /// \brief Write the structure to the stream
            virtual void Write( ostream_type& Stream ) const;

            /// \brief comparison operator
            bool operator==( const FrSE& RHS ) const;

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
            static const Common::FrameSpec::Info::frame_object_types
                s_object_id = Common::FrameSpec::Info::FSI_FR_SE;

            struct image_t
            {
                STRING name;
                STRING classId;
                STRING comment;
            } m_data;

            FrSE( istream_type& Stream );

        }; // class - FrSE

        inline const char*
        FrSE::StructName( )
        {
            static const char* const class_name( "FrSE" );
            return class_name;
        }

        inline std::string
        FrSE::GetClass( ) const
        {
            return m_data.classId;
        }

        inline std::string
        FrSE::GetComment( ) const
        {
            return m_data.comment;
        }

    } // namespace Version_3
} // namespace FrameCPP
#endif /* FrameCPP__VERSION_3__FrSE_HH */
