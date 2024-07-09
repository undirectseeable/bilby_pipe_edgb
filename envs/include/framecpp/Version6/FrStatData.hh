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

#ifndef FrameCPP_VERSION_6_FrStatData_HH
#define FrameCPP_VERSION_6_FrStatData_HH

#include <vector>

#include "framecpp/Common/TOCInfo.hh"
#include "framecpp/Common/SearchContainer.hh"
#include "framecpp/Common/FrameStream.hh"
#include "framecpp/Common/FrStatData.hh"

#include "framecpp/Version4/FrStatData.hh"

#include "framecpp/Version6/FrameSpec.hh"
#include "framecpp/Version6/STRING.hh"
#include "framecpp/Version6/PTR_STRUCT.hh"

#include "framecpp/Version6/FrDetector.hh"
#include "framecpp/Version6/FrSE.hh"
#include "framecpp/Version6/FrTable.hh"
#include "framecpp/Version6/FrTOC.hh"
#include "framecpp/Version6/FrVect.hh"

namespace FrameCPP
{
    namespace Version_6
    {
        //===================================================================
        /// \todo Needs documentation
        //===================================================================

        typedef Previous::FrStatDataNPS FrStatDataNPS;

        //===================================================================
        /// \todo Needs documentation
        //===================================================================

        typedef Version_4::
            FrStatDataPST< PTR_STRUCT, FrDetector, FrVect, FrTable >
                FrStatDataPS;

        //===================================================================
        //===================================================================
        class FrStatData : public Common::FrStatData,
                           public FrStatDataNPS,
                           public FrStatDataPS,
                           public Common::TOCInfo
        {
        public:
            typedef FrStatDataNPS nps_type;
            typedef FrStatDataPS  ps_type;

            //: Default constructor
            FrStatData( );
            FrStatData( const FrStatData& statData );
            FrStatData( const std::string& name,
                        const std::string& comment,
                        const std::string& representation,
                        INT_4U             timeStart,
                        INT_4U             timeEnd,
                        INT_4U             version );
            FrStatData( const Previous::FrStatData& Source,
                        istream_type*               Stream );

            static promote_ret_type Promote( INT_2U           Source,
                                             promote_arg_type Obj,
                                             istream_type*    Stream );

            static const char* StructName( );

            static const Common::Description* StructDescription( );

            //: Number of bytes needed to write this structure
            cmn_streamsize_type Bytes( const Common::StreamBase& Stream ) const;

            virtual FrStatData* Clone( ) const;

            virtual FrStatData* Create( istream_type& Stream ) const;

            virtual fr_detector_type
            GetDetector( ) const
            {
                return FrStatDataPS::GetDetector( );
            }

            virtual const char* ObjectStructName( ) const;

            virtual void Write( ostream_type& Stream ) const;

#if WORKING_VIRTUAL_TOCQUERY
            virtual void TOCQuery( int InfoClass, ... ) const;
#endif /*  WORKING_VIRTUAL_TOCQUERY */

            //: Merge with another FrAdcData
            FrStatData& Merge( const FrStatData& RHS );

            //-----------------------------------------------------------------
            /// \brief Comparison operator
            ///
            /// \param[in] RHS
            ///     Object to compare for equality.
            //-----------------------------------------------------------------
            bool operator==( const FrStatData& RHS ) const;

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

#if !WORKING_VIRTUAL_TOCQUERY
            virtual void vTOCQuery( int InfoClass, va_list vl ) const;
#endif /* ! WORKING_VIRTUAL_TOCQUERY */

        private:
            using Common::FrameSpec::Object::Create;

            FrStatData( istream_type& Stream );
        };

        //===================================================================
        //===================================================================
        inline FrStatData::promote_ret_type
        FrStatData::Promote( INT_2U           Source,
                             promote_arg_type Obj,
                             istream_type*    Stream )
        {
            return Object::PromoteObject< Previous::FrStatData, FrStatData >(
                DATA_FORMAT_VERSION, Source, Obj, Stream );
        }

        inline const char*
        FrStatData::StructName( )
        {
            static const char* name = "FrStatData";
            return name;
        }

        inline bool
        FrStatData::operator==( const FrStatData& RHS ) const
        {
            return (
                ( this == &RHS ) ||
                ( nps_type::operator==( RHS ) && ps_type::operator==( RHS ) ) );
        }
    } // namespace Version_6
} // namespace FrameCPP
#endif /* FrameCPP_VERSION_6_FrStatData_HH */
