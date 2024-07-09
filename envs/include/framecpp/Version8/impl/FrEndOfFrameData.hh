//
// LDASTools frameCPP - A library implementing the LIGO/Virgo frame
// specification
//
// Copyright (C) 2019 California Institute of Technology
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

#ifndef FrameCPP_VERSION_8__IMPL__FrEndOfFrameData_HH
#define FrameCPP_VERSION_8__IMPL__FrEndOfFrameData_HH

#if !defined( SWIGIMPORTED )

#include "ldastoolsal/types.hh"

#include "framecpp/Version8/FrameSpec.hh"
#include "framecpp/Version8/GPSTime.hh"
#include "framecpp/Version8/impl/FrObjectMetaData.hh"

#include "framecpp/Version8/FrameSpec.hh"

namespace FrameCPP
{
    namespace Version_8
    {
        namespace FrEndOfFrameImpl
        {
            class Data : public Impl::FrObjectMetaData< Data >
            {
            public:
                typedef INT_4S run_type; ///< Run number
                typedef INT_4U frame_type; ///< Frame number
                typedef INT_4U GTimeS_type; ///< Frame start time in GPS seconds
                typedef INT_4U GTimeN_type; ///< Frame start time residual
                typedef GPSTime GTime_type; ///< Frmae start time in GPS units

                static run_type constexpr DEFAULT_RUN{
                    0
                }; ///< Default run number
                static frame_type constexpr DEFAULT_FRAME{
                    0
                }; ///< Default frame number
                static GTimeS_type constexpr DEFAULT_GTIME_S{
                    0
                }; ///< Default start time in GPS seconds
                static GTimeN_type constexpr DEFAULT_GTIME_N{
                    0
                }; ///< Default start time residual

                //-----------------------------------------------------------------
                /// @brief Default constructor
                //-----------------------------------------------------------------
                Data( )
                    : run( DEFAULT_RUN ), frame( DEFAULT_FRAME ),
                      GTime( DEFAULT_GTIME_S, DEFAULT_GTIME_N )
                {
                }

                //-----------------------------------------------------------------
                /// \brief Run number of the frame
                /// \return
                ///     The run number of frame.
                ///     It is the same as the value in the FrameH run datum.
                //-----------------------------------------------------------------
                inline run_type
                GetRun( ) const
                {
                    return ( run );
                }

                //-----------------------------------------------------------------
                /// \brief frame number
                ///
                /// \return
                ///     The frame number.
                ///     It is the same as the value in the FrameH frame datum.
                //-----------------------------------------------------------------
                inline frame_type
                GetFrame( ) const
                {
                    return ( frame );
                }

                //-----------------------------------------------------------------
                /// \brief Get the GPS start time of this frame
                ///
                /// \return
                ///     The start time of the frame.
                //-----------------------------------------------------------------
                inline const GTime_type&
                GetGTime( ) const
                {
                    return ( GTime );
                }

            protected:
                //-------------------------------------------------------
                /// Run number.
                /// This is the same as the FrameH::rum member
                //-------------------------------------------------------
                run_type run;
                //-------------------------------------------------------
                /// Frame number, monotonically increasing until end of run;
                /// This is the same as the FrameH::frame number datum.
                //-------------------------------------------------------
                frame_type frame;
                //-------------------------------------------------------
                /// Frame start time in GPS seconds.
                //-------------------------------------------------------
                GTime_type GTime;
            };

        } // namespace FrEndOfFrameImpl
    } // namespace Version_8
} // namespace FrameCPP

FR_OBJECT_META_DATA_DECLARE( FrEndOfFrameImpl )

#endif /* ! defined(SWIGIMPORTED) */

#endif /* FrameCPP_VERSION_8__IMPL__FrEndOfFrameData_HH */
