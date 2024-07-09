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

#ifndef FrameCPP_VERSION_3_FrAdcData_HH
#define FrameCPP_VERSION_3_FrAdcData_HH

#if defined( __cplusplus )
#if !defined( SWIGIMPORTED )
#include <memory>
#include <vector>
#endif /* ! defined(SWIGIMPORTED) */

#if !defined( SWIGIMPORTED )
#include "framecpp/Common/Container.hh"

#include "framecpp/Version3/FrameSpec.hh"
#include "framecpp/Version3/Dimension.hh"
#include "framecpp/Version3/FrVect.hh"
#include "framecpp/Version3/STRING.hh"

#endif /* ! defined(SWIGIMPORTED) */
#endif /* defined(__cplusplus) */

#include "framecpp/Version3/FrAdcDataNPS.hh"
#include "framecpp/Version3/FrAdcDataPST.hh"

#if defined( __cplusplus )
#if !defined( SWIGIMPORTED )
namespace FrameCPP
{
    namespace Version_3
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
                          public Common::FrameSpec::Object
        {
        public:
            typedef FrAdcDataNPS nps_type;
            typedef FrAdcDataPS  ps_type;

            /**
             * \brief Default constructor
             */
            FrAdcData( );

            FrAdcData( const FrAdcData& Source );

            FrAdcData(
                const std::string& name,
                crate_type         crate,
                channel_type       channel,
                nBits_type         nBits,
                sampleRate_type    sampleRate,
                bias_type          bias = FR_ADC_DATA_DEFAULT_BIAS,
                slope_type         slope = FR_ADC_DATA_DEFAULT_SLOPE,
                const std::string& units = FR_ADC_DATA_DEFAULT_UNITS( ),
                fShift_type        fShift = FR_ADC_DATA_DEFAULT_FSHIFT,
                timeOffsetS_type   timeOffsetS =
                    FR_ADC_DATA_DEFAULT_TIME_OFFSET_S,
                timeOffsetN_type timeOffsetN =
                    FR_ADC_DATA_DEFAULT_TIME_OFFSET_N,
                overRange_type overRange = FR_ADC_DATA_DEFAULT_OVER_RANGE );

            ~FrAdcData( );

            static const char* StructName( );

            static const Common::Description* StructDescription( );

            /**
             * \brief Retrieve the name of the FrAdcData struture.
             */
            const std::string& GetNameSlow( ) const;

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

            /* Merge with another FrAdcData */
            FrAdcData& Merge( const FrAdcData& RHS );

            static promote_ret_type Promote( INT_2U           Source,
                                             promote_arg_type Obj,
                                             istream_type*    Stream );

            void SetTimeOffset( INT_4U Seconds, INT_4U Nanoseconds );

            virtual FrAdcData* Create( istream_type& Stream ) const;

            /* Write the structure to the stream */
            virtual void Write( ostream_type& Stream ) const;

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
            return Common::PromoteObject( DATA_FORMAT_VERSION, Source, Obj );
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
    } /* namespace Version_3 */
} /* namespace FrameCPP */
#endif /* ! defined(SWIGIMPORTED) */

#endif /* defined(__cplusplus) */

#endif /* FrameCPP_VERSION_3_FrAdcData_HH */
