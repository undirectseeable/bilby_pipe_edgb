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

#ifndef FrameCPP_VERSION_4_FrAdcData_HH
#define FrameCPP_VERSION_4_FrAdcData_HH

#if defined( __cplusplus )
#if !defined( SWIGIMPORTED )
#include <memory>
#include <vector>
#endif /* ! defined(SWIGIMPORTED) */

#if !defined( SWIGIMPORTED )
#include "framecpp/Common/Container.hh"
#include "framecpp/Common/TOCInfo.hh"

#include "framecpp/Version4/FrameSpec.hh"
#include "framecpp/Version4/Dimension.hh"
#include "framecpp/Version4/FrVect.hh"
#include "framecpp/Version4/STRING.hh"
#endif /* ! defined(SWIGIMPORTED) */
#endif /* defined(__cplusplus) */

#include "framecpp/Version3/FrAdcData.hh"

#include "framecpp/Version4/FrAdcDataNPS.hh"

#if defined( __cplusplus )
#if !defined( SWIGIMPORTED )
namespace FrameCPP
{
    namespace Version_4
    {
        /*-----------------------------------------------------------------
        -----------------------------------------------------------------*/

        typedef FR_ADC_DATA_PS_NAMESPACE ::FrAdcDataPST< FrVect, FrVect >
            FrAdcDataPS;

        /**
         * \brief ADC Data Structure Definition
         */
        class FrAdcData : public FrAdcDataNPS,
                          public FrAdcDataPS,
                          public Common::FrameSpec::Object,
                          public Common::TOCInfo
        {
        public:
            typedef FrAdcDataNPS nps_type;
            typedef FrAdcDataPS  ps_type;

            /**
             * \brief Default constructor
             */
            FrAdcData( );

            /**
             * \brief Copy constructor
             */
            FrAdcData( const FrAdcData& Source );

            FrAdcData(
                const std::string& Name,
                channelGroup_type  Group,
                channelNumber_type Channel,
                nBits_type         NBits,
                sampleRate_type    SampleRate,
                bias_type          Bias = FR_ADC_DATA_DEFAULT_BIAS,
                slope_type         Slope = FR_ADC_DATA_DEFAULT_SLOPE,
                const std::string& Units = FR_ADC_DATA_DEFAULT_UNITS( ),
                fShift_type        FShift = FR_ADC_DATA_DEFAULT_FSHIFT,
                timeOffsetS_type   TimeOffsetS =
                    FR_ADC_DATA_DEFAULT_TIME_OFFSET_S,
                timeOffsetN_type TimeOffsetN =
                    FR_ADC_DATA_DEFAULT_TIME_OFFSET_N,
                dataValid_type DataValid = FR_ADC_DATA_DEFAULT_DATA_VALID );

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

            virtual FrAdcData* Create( istream_type& Stream ) const;

            /* Write the structure to the stream */
            virtual void Write( ostream_type& Stream ) const;

#if WORKING_VIRTUAL_TOCQUERY
            virtual void TOCQuery( int InfoClass, ... ) const;
#endif /* WORKING_VIRTUAL_TOCQUERY */

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
    } /* namespace Version_4 */
} /* namespace FrameCPP */
#endif /* defined(__cplusplus) */
#endif /* ! defined(SWIGIMPORTED) */
#endif /* FrameCPP_VERSION_4_FrAdcData_HH */
