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

#ifndef FRAME_CPP_INTERFACE__IFrameStreamPlan_HH
#define FRAME_CPP_INTERFACE__IFrameStreamPlan_HH

#if !defined( SWIG )

#include <memory>

#include <boost/shared_ptr.hpp>

#include "framecpp/Common/FrameBuffer.hh"

#include "framecpp/FrameCPP.hh"
#include "framecpp/IFrameStream.hh"

#if FRAME_SPEC_CURRENT == 3
#include "framecpp/Version3/FrameStreamPlan.hh"
#elif FRAME_SPEC_CURRENT == 4
#include "framecpp/Version4/FrameStreamPlan.hh"
#elif FRAME_SPEC_CURRENT == 6
#include "framecpp/Version6/FrameStreamPlan.hh"
#elif FRAME_SPEC_CURRENT == 7
#include "framecpp/Version7/FrameStreamPlan.hh"
#elif FRAME_SPEC_CURRENT == 8
#include "framecpp/Version8/FrameStreamPlan.hh"
#else
#error "Unsupported frame spec: FRAME_SPEC_CURRENT"
#endif

#endif /* !defined(SWIG) */

namespace FrameCPP
{
    typedef Version::IFrameStreamPlan IFrameStreamPlan;

    class IFrameFStreamPlan
    {
    public:
        typedef boost::shared_ptr< IFrameFStreamPlan > seed_plan_type;
        typedef IFrameStreamPlan::frame_offset_type    frame_offset_type;
        typedef FrTOC                                  fr_toc_type;
        typedef IFrameStreamPlan::fr_adc_data_type     fr_adc_data_type;
        typedef IFrameStreamPlan::fr_event_type        fr_event_type;
        typedef IFrameStreamPlan::fr_proc_data_type    fr_proc_data_type;
        typedef IFrameStreamPlan::fr_ser_data_type     fr_ser_data_type;
        typedef IFrameStreamPlan::fr_sim_data_type     fr_sim_data_type;
        typedef IFrameStreamPlan::fr_sim_event_type    fr_sim_event_type;

        static const size_t BUFFER_SIZE = IFrameFStream::BUFFER_SIZE;

        IFrameFStreamPlan( seed_plan_type Seed, const char* Filename );

        IFrameFStreamPlan( seed_plan_type Previous,
                           const char*    Filename,
                           bool           UseMemoryMappedIO,
                           size_t         BufferSize );

        const fr_toc_type& GetTOC( ) const;

        fr_adc_data_type ReadFrAdcData( frame_offset_type  Frame,
                                        const std::string& Channel );

        fr_event_type ReadFrEvent( INT_4U Frame, const std::string& Channel );

        fr_proc_data_type ReadFrProcData( frame_offset_type  Frame,
                                          const std::string& Channel );

        fr_ser_data_type ReadFrSerData( INT_4U             Frame,
                                        const std::string& Channel );

        fr_sim_data_type ReadFrSimData( INT_4U             Frame,
                                        const std::string& Channel );

        fr_sim_event_type ReadFrSimEvent( INT_4U             Frame,
                                          const std::string& Channel );

    private:
        typedef LDASTools::AL::filebuf                filebuf_type;
        typedef Common::FrameBuffer< filebuf_type >   frame_buffer_type;
        typedef boost::shared_ptr< IFrameStreamPlan > plan_type;

        plan_type plan;
    };

    inline IFrameFStreamPlan::IFrameFStreamPlan( seed_plan_type Seed,
                                                 const char*    Filename )
    {
        frame_buffer_type* frame_buffer(
            new frame_buffer_type( std::ios::in ) );
        frame_buffer->open( Filename, std::ios::in | std::ios::binary );
        plan.reset( new plan_type::element_type(
            frame_buffer, ( Seed ? Seed->plan.get( ) : NULL ) ) );
    }

    inline IFrameFStreamPlan::IFrameFStreamPlan( seed_plan_type Seed,
                                                 const char*    Filename,
                                                 bool   UseMemoryMappedIO,
                                                 size_t BufferSize )
    {
        std::unique_ptr< CHAR[] > ibuffer( new CHAR[ BufferSize ] );
        frame_buffer_type*        frame_buffer(
            new frame_buffer_type( std::ios::in ) );
        frame_buffer->open( Filename, std::ios::in | std::ios::binary );
        frame_buffer->pubsetbuf( ibuffer.release( ), BufferSize );
        frame_buffer->UseMemoryMappedIO( UseMemoryMappedIO );
        plan.reset( new plan_type::element_type(
            frame_buffer, ( Seed ? Seed->plan.get( ) : NULL ) ) );
    }

    inline const IFrameFStreamPlan::fr_toc_type&
    IFrameFStreamPlan::GetTOC( ) const
    {
        return *( dynamic_cast< const fr_toc_type* >( plan->GetTOC( ) ) );
    }

    inline IFrameFStreamPlan::fr_adc_data_type
    IFrameFStreamPlan::ReadFrAdcData( frame_offset_type  Frame,
                                      const std::string& Channel )
    {
        return plan->ReadFrAdcData( Frame, Channel );
    }

    inline IFrameFStreamPlan::fr_event_type
    IFrameFStreamPlan::ReadFrEvent( INT_4U Frame, const std::string& Channel )
    {
        return plan->ReadFrEvent( Frame, Channel );
    }

    inline IFrameFStreamPlan::fr_proc_data_type
    IFrameFStreamPlan::ReadFrProcData( frame_offset_type  Frame,
                                       const std::string& Channel )
    {
        return plan->ReadFrProcData( Frame, Channel );
    }

    inline IFrameFStreamPlan::fr_ser_data_type
    IFrameFStreamPlan::ReadFrSerData( INT_4U Frame, const std::string& Channel )
    {
        return plan->ReadFrSerData( Frame, Channel );
    }

    inline IFrameFStreamPlan::fr_sim_data_type
    IFrameFStreamPlan::ReadFrSimData( INT_4U Frame, const std::string& Channel )
    {
        return plan->ReadFrSimData( Frame, Channel );
    }

    inline IFrameFStreamPlan::fr_sim_event_type
    IFrameFStreamPlan::ReadFrSimEvent( INT_4U             Frame,
                                       const std::string& Channel )
    {
        return plan->ReadFrSimEvent( Frame, Channel );
    }

} // namespace FrameCPP

#endif /* FRAME_CPP_INTERFACE__IFrameStreamPlan_HH */
