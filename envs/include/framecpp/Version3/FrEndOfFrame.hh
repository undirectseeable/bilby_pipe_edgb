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

#ifndef FrameCPP_VERSION_3_FrEndOfFrame_HH
#define FrameCPP_VERSION_3_FrEndOfFrame_HH

#include "ldastoolsal/types.hh"

#include "framecpp/Version3/FrameSpec.hh"

namespace FrameCPP
{
    namespace Version_3
    {
        class FrEndOfFrame : public Common::FrameSpec::Object
        {
        public:
            typedef INT_4U run_type;
            typedef INT_4U frame_type;

            /// \brief Default constructor
            FrEndOfFrame( );

            /// \brief Default constructor
            FrEndOfFrame( run_type Run, frame_type Frame );

            static const char* StructName( );

            static const Common::Description* StructDescription( );

            /// \brief Desctructor
            virtual ~FrEndOfFrame( );

            /// \brief Return the number of bytes needed to write this object
            INT_8U Bytes( ) const;

            /// \brief Return run number of frame
            run_type GetRun( ) const;

            /// \brief Return frame number
            frame_type GetFrame( ) const;

            virtual cmn_streamsize_type
            Bytes( const Common::StreamBase& Stream ) const;

            virtual FrEndOfFrame* Create( istream_type& Stream ) const;

            virtual const char* ObjectStructName( ) const;

            /// \brief Write the structure to the stream
            virtual void Write( ostream_type& Stream ) const;

            /// \brief comparison operator
            bool operator==( const FrEndOfFrame& RHS ) const;

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

            struct data_type
            {
                run_type   run;
                frame_type frame;
            };

            struct data_type m_data;

            FrEndOfFrame( istream_type& Stream );
        };

        inline const char*
        FrEndOfFrame::StructName( )
        {
            static const CHAR* class_name( "FrEndOfFrame" );
            return class_name;
        }

        /// \brief Return run number of frame
        inline FrEndOfFrame::run_type
        FrEndOfFrame::GetRun( ) const
        {
            return m_data.run;
        }

        /// \brief Return frame number
        inline FrEndOfFrame::frame_type
        FrEndOfFrame::GetFrame( ) const
        {
            return m_data.frame;
        }

    } // namespace Version_3
} // namespace FrameCPP

#endif /* FrameCPP_VERSION_3_FrEndOfFrame_HH */
