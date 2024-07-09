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

#ifndef FrameCPP__VERSION_3__FrSH_HH
#define FrameCPP__VERSION_3__FrSH_HH

#include "framecpp/Common/FrameSpec.hh"
#include "framecpp/Common/FrSH.hh"
#include "framecpp/Common/TOCInfo.hh"

#include "framecpp/Version3/STRING.hh"

namespace FrameCPP
{
    namespace Version_3
    {
        class FrSH : public Common::FrSH, public Common::TOCInfo
        {
        public:
            static const char* StructName( );

            /// \brief Default constructor
            FrSH( );

            /// \brief Constructor
            FrSH( const std::string& Name,
                  INT_2U             ClassId,
                  const std::string& Comment );

            /// \brief Destructor
            virtual ~FrSH( );

            /// \brief Return the number of bytes needed to write this object
            virtual INT_8U Bytes( const Common::StreamBase& Stream ) const;

            virtual const char* ObjectStructName( ) const;

            /// \brief Return class of object
            INT_2U GetClass( ) const;

            /// \brief Return comment of object
            const std::string& GetComment( ) const;

            /// \brief Return name of object
            const STRING& GetName( ) const;

            /// \brief Create a new instance of the object based on the input
            /// stream
            virtual FrSH* Clone( ) const;

            /// \brief Create a new instance of the object based on the input
            /// stream
            virtual FrSH* Create( istream_type& Stream ) const;

            /// \brief Write the structure to the stream
            virtual void Write( ostream_type& Stream ) const;

            /// \brief comparison operator
            bool operator==( const FrSH& RHS ) const;

            /// \brief comparison operator
            virtual bool
            operator==( const Common::FrameSpec::Object& Obj ) const;

#if WORKING_VIRTUAL_TOCQUERY
            virtual void TOCQuery( int InfoClass, ... ) const;
#endif /* WORKING_VIRTUAL_TOCQUERY */

        protected:
            //-----------------------------------------------------------------
            // Interface routines
            //-----------------------------------------------------------------
            virtual const std::string& name( ) const;

            virtual INT_2U classId( ) const;

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

            static const Common::FrameSpec::Info::frame_object_types
                s_object_id = Common::FrameSpec::Info::FSI_FR_SH;

            struct image_t
            {
                STRING name;
                INT_2U classId;
                STRING comment;
            } m_data;

            FrSH( istream_type& Stream );
        }; // class - FrSH

        inline const STRING&
        FrSH::GetName( ) const
        {
            return m_data.name;
        }

        inline INT_2U
        FrSH::GetClass( ) const
        {
            return m_data.classId;
        }

        inline const std::string&
        FrSH::GetComment( ) const
        {
            return m_data.comment;
        }

        inline const char*
        FrSH::StructName( )
        {
            static const CHAR* class_name( "FrSH" );
            return class_name;
        }

    } // namespace Version_3
} // namespace FrameCPP
#endif /* FrameCPP__VERSION_3__FrSH_HH */
