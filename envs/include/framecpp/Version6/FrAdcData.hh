/*
 * LDASTools frameCPP - A library implementing the LIGO/Virgo frame
 * specification
 *
 * Copyright (C) 2018 California Institute of Technology
 *
 * LDASTools frameCPP is free software; you may redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 (GPLv2) of the
 * License or at your discretion, any later version.
 *
 * LDASTools frameCPP is distributed in the hope that it will be useful, but
 * without any warranty or even the implied warranty of merchantability
 * or fitness for a particular purpose. See the GNU General Public
 * License (GPLv2) for more details.
 *
 * Neither the names of the California Institute of Technology (Caltech),
 * The Massachusetts Institute of Technology (M.I.T), The Laser
 * Interferometer Gravitational-Wave Observatory (LIGO), nor the names
 * of its contributors may be used to endorse or promote products derived
 * from this software without specific prior written permission.
 *
 * You should have received a copy of the licensing terms for this
 * software included in the file LICENSE located in the top-level
 * directory of this package. If you did not, you can view a copy at
 * http://dcc.ligo.org/M1500244/LICENSE
 */

#ifndef FrameCPP_VERSION_6_FrAdcData_HH
#define FrameCPP_VERSION_6_FrAdcData_HH

#if defined( __cplusplus )
#if !defined( SWIGIMPORTED )
#include <memory>
#include <vector>

#include "ldastoolsal/types.hh"

#include "framecpp/Common/Container.hh"
#include "framecpp/Common/TOCInfo.hh"

#include "framecpp/Version6/FrameSpec.hh"
#include "framecpp/Version6/Dimension.hh"
#include "framecpp/Version6/FrVect.hh"
#include "framecpp/Version6/STRING.hh"
#endif /* ! defined(SWIGIMPORTED) */
#endif /* defined(__cplusplus) */

#include "framecpp/Version4/FrAdcData.hh"

#include "framecpp/Version6/FrAdcDataNPS.hh"

#if defined( __cplusplus ) && !defined( SWIGIMPORTED )
namespace FrameCPP
{
    namespace Version_6
    {
        typedef FR_ADC_DATA_PS_NAMESPACE ::FrAdcDataPST< FrVect, FrVect >
            FrAdcDataPS;

        class FrAdcData : public FrAdcDataNPS,
                          public FrAdcDataPS,
                          public Common::FrameSpec::Object,
                          public Common::TOCInfo
        {
        public:
            typedef FrAdcDataNPS                 nps_type;
            typedef FrAdcDataPS                  ps_type;
            typedef std::unique_ptr< FrAdcData > subfradcdata_type;

            /**
              // \brief Default constructor
              */
            FrAdcData( );

            /**
              // \brief Copy constructor
              */
            FrAdcData( const FrAdcData& Source );

            FrAdcData( const std::string& name,
                       channelGroup_type  group,
                       channelNumber_type channel,
                       nBits_type         nBits,
                       sampleRate_type    sampleRate,
                       bias_type          bias = DEFAULT_BIAS,
                       slope_type         slope = DEFAULT_SLOPE,
                       const std::string& units = FR_ADC_DATA_DEFAULT_UNITS( ),
                       fShift_type        fShift = DEFAULT_FSHIFT,
                       timeOffset_type    timeOffset = DEFAULT_TIME_OFFSET,
                       dataValid_type     dataValid = DEFAULT_DATA_VALID,
                       phase_type         phase = DEFAULT_PHASE );

            FrAdcData( Previous::FrAdcData& Source, istream_type* Stream );

            ~FrAdcData( );

            static const char* StructName( );

            static const Common::Description* StructDescription( );

            /* Comparison operator */
            bool operator==( const FrAdcData& RHS ) const;
            bool operator!=( const FrAdcData& RHS ) const;

            /**
             * \brief comparison operator
             */
            virtual bool
            operator==( const Common::FrameSpec::Object& Obj ) const;

            /* Number of bytes needed to write this structure */
            cmn_streamsize_type Bytes( const Common::StreamBase& Stream ) const;

            virtual const char* ObjectStructName( ) const;

            const std::string& GetName( ) const;

            /* Merge with another FrAdcData */
            FrAdcData& Merge( const FrAdcData& RHS );

            static promote_ret_type Promote( INT_2U           Source,
                                             promote_arg_type Obj,
                                             istream_type*    Stream );

            subfradcdata_type SubFrAdcData( REAL_8 Offset, REAL_8 Dt ) const;

            virtual FrAdcData* Create( istream_type& Stream ) const;

            /* Write the structure to the stream */
            virtual void Write( ostream_type& Stream ) const;

#if WORKING_VIRTUAL_TOCQUERY
            virtual void TOCQuery( int InfoClass, ... ) const;
#endif /*  WORKING_VIRTUAL_TOCQUERY */

        protected:
            /**
             * \brief Down grade an object
             */
            virtual demote_ret_type demote( INT_2U          Target,
                                            demote_arg_type Obj,
                                            istream_type*   Stream ) const;

            /**
             * \brief Upgrade an object
             */
            virtual promote_ret_type promote( INT_2U           Target,
                                              promote_arg_type Obj,
                                              istream_type*    Stream ) const;

#if !WORKING_VIRTUAL_TOCQUERY
            virtual void vTOCQuery( int InfoClass, va_list vl ) const;
#endif /* ! WORKING_VIRTUAL_TOCQUERY */

        private:
            using Common::FrameSpec::Object::Create;

            FrAdcData( istream_type& Stream );

            void copy_core( const FrAdcData& Source );
        };

        inline FrAdcData::promote_ret_type
        FrAdcData::Promote( INT_2U           Source,
                            promote_arg_type Obj,
                            istream_type*    Stream )
        {
            return Object::PromoteObject< Previous::FrAdcData, FrAdcData >(
                DATA_FORMAT_VERSION, Source, Obj, Stream );
        }

        inline const char*
        FrAdcData::StructName( )
        {
            static const char* name = "FrAdcData";
            return name;
        }

        inline bool
        FrAdcData::operator==( const FrAdcData& RHS ) const
        {
            return (
                ( this == &RHS ) ||
                ( nps_type::operator==( RHS ) && ps_type::operator==( RHS ) ) );
        }

        inline bool
        FrAdcData::operator!=( const FrAdcData& RHS ) const
        {
            return !( *this == RHS );
        }

        inline void
        FrAdcData::copy_core( const FrAdcData& Source )
        {
            nps_type::copyCore( Source );
            ps_type::copyCore( Source );
        }
    } /* namespace Version_6 */
} /* namespace FrameCPP */
#endif /* defined(__cplusplus) && !defined(SWIGIMPORTED) */
#endif /* FrameCPP_VERSION_6_FrAdcData_HH */
