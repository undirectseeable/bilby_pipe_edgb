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

#ifndef FrameCPP_VERSION_6_FrProcData_NPS_HH
#define FrameCPP_VERSION_6_FrProcData_NPS_HH

#if !defined( SWIGIMPORTED )
#include "framecpp/Version4/FrProcData.hh"
#endif /* ! defined(SWIGIMPORTED) */

#include "framecpp/Version6/FrameSpec.hh"

#include "framecpp/Version6/STRING.hh"

#undef FR_PROC_DATA_NAME_TYPE
#define FR_PROC_DATA_NAME_TYPE STRING

#undef FR_PROC_DATA_COMMENT_TYPE
#define FR_PROC_DATA_COMMENT_TYPE STRING

#undef FR_PROC_DATA_TYPE_TYPE
#define FR_PROC_DATA_TYPE_TYPE INT_2U

#undef FR_PROC_DATA_SUB_TYPE_TYPE
#define FR_PROC_DATA_SUB_TYPE_TYPE INT_2U

#undef FR_PROC_DATA_TIME_OFFSET_TYPE
#define FR_PROC_DATA_TIME_OFFSET_TYPE REAL_8

#undef FR_PROC_DATA_T_RANGE_TYPE
#define FR_PROC_DATA_T_RANGE_TYPE REAL_8

#undef FR_PROC_DATA_F_SHIFT_TYPE
#define FR_PROC_DATA_F_SHIFT_TYPE REAL_8

#undef FR_PROC_DATA_PHASE_TYPE
#define FR_PROC_DATA_PHASE_TYPE REAL_4

#undef FR_PROC_DATA_F_RANGE_TYPE
#define FR_PROC_DATA_F_RANGE_TYPE REAL_8

#undef FR_PROC_DATA_BW_TYPE
#define FR_PROC_DATA_BW_TYPE REAL_8

#undef FR_PROC_DATA_DEFAULT_TYPE
#define FR_PROC_DATA_DEFAULT_TYPE 0

#undef FR_PROC_DATA_DEFAULT_SUB_TYPE
#define FR_PROC_DATA_DEFAULT_SUB_TYPE 0

#undef FR_PROC_DATA_DEFAULT_TRANGE
#define FR_PROC_DATA_DEFAULT_TRANGE 0.0

#undef FR_PROC_DATA_DEFAULT_FSHIFT
#define FR_PROC_DATA_DEFAULT_FSHIFT 0.0

#undef FR_PROC_DATA_DEFAULT_PHASE
#define FR_PROC_DATA_DEFAULT_PHASE 0.0

#undef FR_PROC_DATA_DEFAULT_FRANGE
#define FR_PROC_DATA_DEFAULT_FRANGE 0.0

#undef FR_PROC_DATA_DEFAULT_BW
#define FR_PROC_DATA_DEFAULT_BW 0.0

#if defined( __cplusplus )

namespace FrameCPP
{
    namespace Version_6
    {

        /*===================================================================
           Data elements for an FrProcData
          ===================================================================*/
        class FrProcDataNPS
        {
        public:
            typedef FR_PROC_DATA_NAME_TYPE        name_type;
            typedef FR_PROC_DATA_COMMENT_TYPE     comment_type;
            typedef FR_PROC_DATA_TYPE_TYPE        type_type;
            typedef FR_PROC_DATA_SUB_TYPE_TYPE    subType_type;
            typedef FR_PROC_DATA_TIME_OFFSET_TYPE timeOffset_type;
            typedef FR_PROC_DATA_T_RANGE_TYPE     tRange_type;
            typedef FR_PROC_DATA_F_SHIFT_TYPE     fShift_type;
            typedef FR_PROC_DATA_PHASE_TYPE       phase_type;
            typedef FR_PROC_DATA_F_RANGE_TYPE     fRange_type;
            typedef FR_PROC_DATA_BW_TYPE          BW_type;

            enum e_type_type
            {
                UNKNOWN_TYPE = 0,
                TIME_SERIES = 1,
                FREQUENCY_SERIES = 2,
                OTHER_1D_SERIES_DATA = 3,
                TIME_FREQUENCY = 4,
                WAVELETS = 5,
                MULTI_DIMENSIONAL = 6
            };

            enum e_subType_type
            {
                UNKNOWN_SUB_TYPE = 0,
                /*---------------------------------------------------------------
                 Subtype for fSeries
                 ---------------------------------------------------------------*/
                DFT = 1,
                AMPLITUDE_SPECTRAL_DENSITY = 2,
                POWER_SPECTRAL_DENSITY = 3,
                CROSS_SPECTRAL_DENSITY = 4,
                COHERENCE = 5,
                TRANSFER_FUNCTION = 6
            };

#if !defined( SWIGIMPORTED )
            struct AuxParam_type
            {
                typedef REAL_8 auxParam_type;
                typedef STRING auxParamName_type;

                auxParam_type     auxParam;
                auxParamName_type auxParamName;

                inline AuxParam_type( ){};

                inline AuxParam_type( auxParam_type     Param,
                                      auxParamName_type ParamName )
                    : auxParam( Param ), auxParamName( ParamName ){};

                AuxParam_type( auxParamName_type ParamName,
                               auxParam_type     Param )
                    : auxParam( Param ), auxParamName( ParamName ){};

                cmn_streamsize_type bytes( ) const;

                bool operator==( const AuxParam_type& RHS ) const;
            };
#endif /* ! defined(SWIGIMPORTED) */

            typedef Common::Array< INT_2U, AuxParam_type > AuxParamList_type;

            static const phase_type  PHASE_UNKNOWN;
            static const fRange_type FRANGE_UNKNOWN;
            static const BW_type     BW_UNKNOWN;

            static const FrProcDataNPS::type_type    DEFAULT_VALUE_TYPE;
            static const FrProcDataNPS::subType_type DEFAULT_VALUE_SUB_TYPE;
            static const FrProcDataNPS::tRange_type  DEFAULT_VALUE_TRANGE;
            static const FrProcDataNPS::fShift_type  DEFAULT_VALUE_FSHIFT;
            static const FrProcDataNPS::phase_type   DEFAULT_VALUE_PHASE;
            static const FrProcDataNPS::fRange_type  DEFAULT_VALUE_FRANGE;
            static const FrProcDataNPS::BW_type      DEFAULT_VALUE_BW;

            /* Mutators */
            void AppendComment( const std::string& Comment );

            void AppendAuxParam( const AuxParam_type& Param );

            const name_type&         GetName( ) const;
            const comment_type&      GetComment( ) const;
            type_type                GetType( ) const;
            subType_type             GetSubType( ) const;
            timeOffset_type          GetTimeOffset( ) const;
            tRange_type              GetTRange( ) const;
            fShift_type              GetFShift( ) const;
            phase_type               GetPhase( ) const;
            fRange_type              GetFRange( ) const;
            BW_type                  GetBW( ) const;
            const AuxParamList_type& GetAuxParam( ) const;
            AuxParamList_type&       GetAuxParam( );

            void SetAuxParam( const AuxParamList_type& AuxParams );
            void SetComment( const comment_type& Comment );
            void SetFRange( fRange_type FRange );
            void SetFShift( fShift_type FShift );
            void SetTimeOffset( timeOffset_type time );
            void SetTRange( tRange_type TRange );

        protected:
            name_type         name;
            comment_type      comment;
            type_type         type;
            subType_type      subType;
            timeOffset_type   timeOffset;
            tRange_type       tRange;
            fShift_type       fShift;
            phase_type        phase;
            fRange_type       fRange;
            BW_type           BW;
            AuxParamList_type auxParams;

            FrProcDataNPS( );
            FrProcDataNPS( const name_type&    Name,
                           const comment_type& Comment,
                           type_type           Type,
                           subType_type        SubType,
                           timeOffset_type     TimeOffset,
                           tRange_type         TRange,
                           fShift_type         FShift,
                           phase_type          Phase,
                           fRange_type         FRange,
                           BW_type             BW );
            FrProcDataNPS( const FrProcDataNPS& Source );
            FrProcDataNPS( istream_type& Stream );
            FrProcDataNPS( const Previous::FrProcData& Source );

            cmn_streamsize_type bytes( ) const;

            void write( ostream_type& Stream ) const;

#if !defined( SWIGIMPORTED )
            FrProcDataNPS& operator=( const FrProcDataNPS& RHS );
#endif /* ! defined(SWIGIMPORTED) */

            /* Comparison operator */
            bool operator==( const FrProcDataNPS& RHS ) const;
        };
    } /* namespace Version_6 */

    namespace Common
    {
        /**
         * \cond ignore
         */
        template <>
        inline IStream&
        IStream::operator>>( Version_6::FrProcDataNPS::AuxParamList_type& Data )
        {
            typedef Version_6::FrProcDataNPS::AuxParamList_type
                AuxParamList_type;

            AuxParamList_type::n_size_type nAuxParam;

            *this >> nAuxParam;
            if ( nAuxParam > 0 )
            {
                Data.resize( nAuxParam );

                std::vector< AuxParamList_type::value_type::auxParam_type > ap(
                    nAuxParam );
                std::vector< AuxParamList_type::value_type::auxParamName_type >
                    apn( nAuxParam );

                *this >> ap >> apn;

                for ( AuxParamList_type::n_size_type cur = 0; cur != nAuxParam;
                      ++cur )
                {
                    Data[ cur ].auxParam = ap[ cur ];
                    Data[ cur ].auxParamName = apn[ cur ];
                }
            }
            return *this;
        }

        template <>
        inline OStream&
        OStream::
        operator<<( const Version_6::FrProcDataNPS::AuxParamList_type& Data )
        {
            typedef Version_6::FrProcDataNPS::AuxParamList_type
                AuxParamList_type;

            AuxParamList_type::n_size_type nAuxParam( Data.size( ) );

            *this << nAuxParam;
            if ( nAuxParam )
            {
                std::vector< REAL_8 > auxParam( nAuxParam );

                INT_4U x = 0;
                for ( AuxParamList_type::const_iterator cur = Data.begin( ),
                                                        last = Data.end( );
                      cur != last;
                      ++cur, ++x )
                {
                    auxParam[ x ] = cur->auxParam;
                }
                write( (const char_type*)( &( auxParam[ 0 ] ) ),
                       sizeof( REAL_8 ) * nAuxParam );
                for ( AuxParamList_type::const_iterator cur = Data.begin( ),
                                                        last = Data.end( );
                      cur != last;
                      ++cur )
                {
                    *this << cur->auxParamName;
                }
            }

            return *this;
        }
        /**
         * \endcond ignore
         */
    } /* namespace Common */

    namespace Version_6
    {

        inline cmn_streamsize_type
        FrProcDataNPS::AuxParam_type::bytes( ) const
        {
            return sizeof( auxParam ) + auxParamName.Bytes( );
        }

        inline void
        FrProcDataNPS::SetAuxParam( const AuxParamList_type& AuxParams )
        {
            auxParams = AuxParams;
#if 0
      AuxParamList_type::n_size_type	index = 0;
      auxParams.erase( auxParams.begin( ),
		       auxParams.end( ) );
      auxParams.resize( AuxParams.size( ) );
      for ( AuxParamMap_type::const_iterator
	      cur = AuxParams.begin( ),
	      last = AuxParams.end( );
	    cur != last;
	    ++cur )
      {
	auxParams[ index++ ] = AuxParam_type( cur->first, cur->second );
      }
#endif /* 0 */
        }

        inline cmn_streamsize_type
        FrProcDataNPS::bytes( ) const
        {
            cmn_streamsize_type retval;
            retval = name.Bytes( ) + comment.Bytes( ) + sizeof( type ) +
                sizeof( subType ) + sizeof( timeOffset ) + sizeof( tRange ) +
                sizeof( fShift ) + sizeof( phase ) + sizeof( fRange ) +
                sizeof( BW ) + auxParams.bytes( );
            return retval;
        }

        inline void
        FrProcDataNPS::write( ostream_type& Stream ) const
        {
            Stream << name << comment << type << subType << timeOffset << tRange
                   << fShift << phase << fRange << BW << auxParams;
        }

        inline bool
        FrProcDataNPS::AuxParam_type::
        operator==( const AuxParam_type& RHS ) const
        {

            return ( ( this == &RHS ) ||
                     ( ( auxParam == RHS.auxParam ) &&
                       ( auxParamName == RHS.auxParamName ) ) );
        }

        inline void
        FrProcDataNPS::AppendComment( const std::string& Comment )
        {
            FrameCPP::Common::AppendComment( comment, Comment );
        }

        inline void
        FrProcDataNPS::AppendAuxParam( const AuxParam_type& Param )
        {
            auxParams.push_back( Param );
        }

        inline const FrProcDataNPS::AuxParamList_type&
        FrProcDataNPS::GetAuxParam( ) const
        {
            return auxParams;
        }

        inline FrProcDataNPS::AuxParamList_type&
        FrProcDataNPS::GetAuxParam( )
        {
            return auxParams;
        }

        inline const FrProcDataNPS::name_type&
        FrProcDataNPS::GetName( ) const
        {
            return name;
        }

        inline const FrProcDataNPS::comment_type&
        FrProcDataNPS::GetComment( ) const
        {
            return comment;
        }

        inline FrProcDataNPS::type_type
        FrProcDataNPS::GetType( ) const
        {
            return type;
        }

        inline FrProcDataNPS::subType_type
        FrProcDataNPS::GetSubType( ) const
        {
            return subType;
        }

        inline FrProcDataNPS::timeOffset_type
        FrProcDataNPS::GetTimeOffset( ) const
        {
            return timeOffset;
        }

        inline FrProcDataNPS::tRange_type
        FrProcDataNPS::GetTRange( ) const
        {
            return tRange;
        }

        inline FrProcDataNPS::fShift_type
        FrProcDataNPS::GetFShift( ) const
        {
            return fShift;
        }

        inline FrProcDataNPS::phase_type
        FrProcDataNPS::GetPhase( ) const
        {
            return phase;
        }

        inline FrProcDataNPS::fRange_type
        FrProcDataNPS::GetFRange( ) const
        {
            return fRange;
        }

        inline FrProcDataNPS::BW_type
        FrProcDataNPS::GetBW( ) const
        {
            return BW;
        }

        inline void
        FrProcDataNPS::SetComment( const comment_type& Comment )
        {
            comment = Comment;
        }

        inline void
        FrProcDataNPS::SetFRange( fRange_type FRange )
        {
            fRange = FRange;
        }

        inline void
        FrProcDataNPS::SetFShift( fShift_type FShift )
        {
            fShift = FShift;
        }

        inline void
        FrProcDataNPS::SetTimeOffset( timeOffset_type time )
        {
            timeOffset = time;
        }

        inline void
        FrProcDataNPS::SetTRange( tRange_type TRange )
        {
            tRange = TRange;
        }

        inline FrProcDataNPS::FrProcDataNPS( )
            : type( DEFAULT_VALUE_TYPE ), subType( DEFAULT_VALUE_SUB_TYPE ),
              tRange( DEFAULT_VALUE_TRANGE ), fShift( DEFAULT_VALUE_FSHIFT ),
              phase( DEFAULT_VALUE_PHASE ), fRange( DEFAULT_VALUE_FRANGE ),
              BW( DEFAULT_VALUE_BW )
        {
        }

        inline FrProcDataNPS::FrProcDataNPS( const name_type&    Name,
                                             const comment_type& Comment,
                                             type_type           Type,
                                             subType_type        SubType,
                                             timeOffset_type     TimeOffset,
                                             tRange_type         TRange,
                                             fShift_type         FShift,
                                             phase_type          Phase,
                                             fRange_type         FRange,
                                             BW_type             BW )
            : name( Name ), comment( Comment ), type( Type ),
              subType( SubType ), timeOffset( TimeOffset ), tRange( TRange ),
              fShift( FShift ), phase( Phase ), fRange( FRange ), BW( BW )
        {
        }

        inline FrProcDataNPS::FrProcDataNPS( const FrProcDataNPS& Source )
            : name( Source.name ), comment( Source.comment ),
              type( Source.type ), subType( Source.subType ),
              timeOffset( Source.timeOffset ), tRange( Source.tRange ),
              fShift( Source.fShift ), phase( Source.phase ),
              fRange( Source.fRange ), BW( Source.BW ),
              auxParams( Source.auxParams )
        {
        }

        inline FrProcDataNPS::FrProcDataNPS(
            const Previous::FrProcData& Source )
            : tRange( FR_PROC_DATA_DEFAULT_TRANGE ),
              phase( FR_PROC_DATA_DEFAULT_PHASE ),
              fRange( FR_PROC_DATA_DEFAULT_FRANGE ),
              BW( FR_PROC_DATA_DEFAULT_BW )

        {
            if ( Source.GetSampleRate( ) == -1 )
            {
                type = FREQUENCY_SERIES;
            }
            else
            {
                type = TIME_SERIES;
            }
            subType = UNKNOWN_SUB_TYPE;
            name = Source.GetName( );
            comment = Source.GetComment( );
            timeOffset = Source.GetTimeOffset( ).GetTime( );
            fShift = Source.GetFShift( );
        }

        inline FrProcDataNPS::FrProcDataNPS( istream_type& Stream )
        {
            Stream >> name >> comment >> type >> subType >> timeOffset >>
                tRange >> fShift >> phase >> fRange >> BW >> auxParams;
        }

        inline FrProcDataNPS&
        FrProcDataNPS::operator=( const FrProcDataNPS& RHS )
        {
            name = RHS.name;
            comment = RHS.comment;
            type = RHS.type;
            subType = RHS.subType;
            timeOffset = RHS.timeOffset;
            tRange = RHS.tRange;
            fShift = RHS.fShift;
            phase = RHS.phase;
            fRange = RHS.fRange;
            BW = RHS.BW;
            auxParams = RHS.auxParams;
            return *this;
        }

        inline bool
        FrProcDataNPS::operator==( const FrProcDataNPS& RHS ) const
        {
            return ( ( &RHS == this ) ||
                     ( ( name == RHS.name ) && ( comment == RHS.comment ) &&
                       ( type == RHS.type ) && ( subType == RHS.subType ) &&
                       ( timeOffset == RHS.timeOffset ) &&
                       ( tRange == RHS.tRange ) && ( fShift == RHS.fShift ) &&
                       ( phase == RHS.phase ) && ( fRange == RHS.fRange ) &&
                       ( BW == RHS.BW ) && ( auxParams == RHS.auxParams ) ) );
        }
    } /* namespace Version_6 */
} /* namespace FrameCPP */

#endif /* defined(__cplusplus) */

#endif /* FrameCPP_VERSION_6_FrProcData_NPS_HH */
