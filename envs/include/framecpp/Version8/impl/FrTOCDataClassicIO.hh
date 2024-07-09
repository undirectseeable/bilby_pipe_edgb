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

#ifndef FrameCPP_VERSION_8__IMPL__FrTOCDataClassicIO_HH
#define FrameCPP_VERSION_8__IMPL__FrTOCDataClassicIO_HH

#include "framecpp/Version8/impl/FrTOCDataData.hh"

#if defined( __cplusplus )
#if !defined( SWIG )

#include "framecpp/Common/Description.hh"
#include "framecpp/Common/FrameSpec.hh"
#include "framecpp/Common/FrameSpec.tcc"
#include "framecpp/Common/TOCInfo.hh"

#include "framecpp/Version7/FrTOCData.hh"

#include "framecpp/Version8/impl/FrTOCDataData.hh"

#include "framecpp/Version8/FrameSpec.hh"
#include "framecpp/Version8/FrSH.hh"
#include "framecpp/Version8/FrSE.hh"
#include "framecpp/Version8/PTR_STRUCT.hh"
#include "framecpp/Version8/STRING.hh"

namespace FrameCPP
{
    namespace Version_8
    {
        namespace FrTOCImpl
        {
            class FrTOCDataClassicIO : public virtual FrTOCDataData
            {
            public:
                FrTOCDataClassicIO( ) = default;

                Common::FrameSpec::size_type
                Bytes( const Common::StreamBase& Stream ) const
                {
                    Common::FrameSpec::size_type retval = 0;

                    //-----------------------------------------------------------------
                    // main header block
                    //-----------------------------------------------------------------
                    retval += sizeof( m_ULeapS ) + sizeof( nFrame_type ) +
                        ( m_dataQuality.size( ) *
                          ( sizeof( data_quality_type ) +
                            sizeof( gtimes_type ) + sizeof( gtimen_type ) +
                            sizeof( dt_type ) + sizeof( runs_type ) +
                            sizeof( frame_type ) + sizeof( positionh_type ) +
                            sizeof( nfirstadc_type ) +
                            sizeof( nfirstmsg_type ) +
                            sizeof( nfirstser_type ) +
                            sizeof( nfirsttable_type ) ) );
                    //-----------------------------------------------------------------
                    // SH elements
                    //-----------------------------------------------------------------
                    retval += sizeof( nsh_type ) +
                        ( sizeof( shid_type ) * m_SHid.size( ) );
                    for ( shname_container_type::const_iterator
                              cur = m_SHname.begin( ),
                              last = m_SHname.end( );
                          cur != last;
                          ++cur )
                    {
                        retval += io_shname_type::Bytes( *cur );
                    }
                    //-----------------------------------------------------------------
                    // Detector information
                    //-----------------------------------------------------------------
                    retval += sizeof( ndetector_type ) +
                        ( sizeof( positiondetector_type ) *
                          m_positionDetector.size( ) );
                    for ( namedetector_container_type::const_iterator
                              cur = m_nameDetector.begin( ),
                              last = m_nameDetector.end( );
                          cur != last;
                          ++cur )
                    {
                        retval += io_namedetector_type::Bytes( *cur );
                    }
                    //-----------------------------------------------------------------
                    // Return the results
                    //-----------------------------------------------------------------
                    return retval;
                }

#if !defined( SWIG )
                //-----------------------------------------------------------------
                /// \brief asignment operator
                ///
                /// \param[in] Source
                ///     The source to be copied.
                //-----------------------------------------------------------------
                const FrTOCDataClassicIO&
                operator=( const Previous::FrTOCData& Source )
                {
                    m_ULeapS = Source.GetULeapS( );
                    m_dataQuality = Source.GetDataQuality( );
                    m_GTimeS = Source.GetGTimeS( );
                    m_GTimeN = Source.GetGTimeN( );
                    m_dt = Source.GetDt( );
                    m_runs = Source.GetRuns( );
                    m_frame = GetFrame( );

                    m_positionH = Source.GetPositionH( );

                    m_nFirstADC = Source.GetNFirstADC( );
                    m_nFirstSer = Source.GetNFirstSer( );
                    m_nFirstTable = Source.GetNFirstTable( );
                    m_nFirstMsg = Source.GetNFirstMsg( );

                    m_SHid = Source.GetSHid( );
                    m_SHname.resize( Source.GetSHname( ).size( ) );
                    std::copy(Source.GetSHname( ).begin( ),
                              Source.GetSHname( ).end( ),
                              m_SHname.begin( ) );

                    m_nameDetector.resize( Source.GetNameDetector( ).size( ) );
                    std::copy( Source.GetNameDetector( ).begin( ),
                               Source.GetNameDetector( ).end( ),
                               m_nameDetector.begin( ) );
                    m_positionDetector = Source.GetPositionDetector( );

                    return *this;
                }
#endif /* ! defined(SWIG) */

                inline FrTOCDataClassicIO&
                operator=( FrTOCDataClassicIO&& TOC )
                {
                    static_cast< FrTOCDataData& >( *this ) =
                        static_cast< FrTOCDataData&& >( TOC );
                    return *this;
                }

                //-----------------------------------------------------------------
                /// \brief The description of structure
                ///
                /// \param[out] Desc
                ///     Storage for the description of the structure.
                ///
                /// \return
                ///     A Description object which describes this structure as
                ///     specified by the frame specification.
                //-----------------------------------------------------------------
                template < typename SE >
                static void
                Description( Common::Description& Desc )
                {
                    Desc( SE( "ULeapS",
                              "INT_2S",
                              "From the first FrameH in the file" ) );
                    //-----------------------------------------------------------------
                    Desc( SE(
                        "nFrame", "INT_4U", "Number of frames in the file" ) );
                    Desc( SE( "dataQuality",
                              "INT_4U[nFrame]",
                              "Array of integer QA words from each FrameH"
                              " (size of nFrames)" ) );
                    Desc( SE(
                        "GTimeS",
                        "INT_4U[nFrame]",
                        "Array of integer GPS frae times (size of nFrames" ) );
                    Desc( SE( "GTimeN",
                              "INT_4U[nFrame]",
                              "Array of integer GPS residual nanoseconds for "
                              "the frame"
                              " (size of nFrame" ) );
                    Desc( SE( "dt",
                              "REAL_8[nFrame]",
                              "Array of frame durations in seconds( size of "
                              "nFrames)" ) );
                    Desc( SE( "runs",
                              "INT_4S[nFrame]",
                              "Array of run numbers (size of nFrame)" ) );
                    Desc( SE( "frame",
                              "INT_4U[nFrame]",
                              "Array of frame numbers (size of nFrame)" ) );
                    Desc( SE( "positionH",
                              "INT_8U[nFrame]",
                              "Array of FrameH positions, in bytes, from the"
                              " bginning of file (size of nFrame)" ) );
                    Desc( SE( "nFirstADC",
                              "INT_8U[nFrame]",
                              "Array of first FrADCData positions, in bytes,"
                              " from beginning of file (size of nFrame)" ) );
                    Desc( SE( "nFirstSer",
                              "INT_8U[nFrame]",
                              "Array of first FrSerData positions in bytes,"
                              " from beginning of file (size of nFrame)" ) );
                    Desc( SE( "nFirstTable",
                              "INT_8U[nFrame]",
                              "Array of first FrTable positions, in bytes,"
                              " from beginning of file (size of nFrame)" ) );
                    Desc( SE( "nFirstMsg",
                              "INT_8U[nFrame]",
                              "Array of first FrMsg positions, in bytes,"
                              " from beginning of file (size of nFrame)" ) );
                    //-----------------------------------------------------------------
                    Desc( SE( "nSH",
                              "INT_4U",
                              "Number of FrSH structures in the file" ) );
                    Desc( SE( "SHid",
                              "INT_2U[nSH]",
                              "Array of FrSH IDs (size of nSH)" ) );
                    Desc( SE( "SHname",
                              "STRING[nSH]",
                              "Array of FrSH names (size of nSH)" ) );
                    //-----------------------------------------------------------------
                    Desc( SE( "nDetector",
                              "INT_4U",
                              "Number of distinct types of FrDetector in the "
                              "file" ) );
                    Desc( SE( "nameDetector",
                              "STRING[nDetector]",
                              "Array of FrDetector names (size of nDetector)."
                              " They appear alphabetically" ) );
                    Desc( SE( "positionDetector",
                              "INT_8U[nDetector]",
                              "Array of FrDetector positions from the beginning"
                              " of file (size of nDetector)." ) );
                }

                //-----------------------------------------------------------------
                /// \brief Read contents from stream
                ///
                /// \param[in] Stream
                ///     The stream from which the object is being read.
                ///
                /// \return
                ///    A new instance of this object.
                //-----------------------------------------------------------------
                void
                Load( istream_type& Stream )
                {
                    nFrame_type nframe;

                    Stream >> m_ULeapS >> nframe;
                    if ( nframe )
                    {
                        std::vector< io_shname_type >       io_SHname;
                        std::vector< io_namedetector_type > io_nameDetector;
                        m_dataQuality.resize( nframe );
                        m_GTimeS.resize( nframe );
                        m_GTimeN.resize( nframe );
                        m_dt.resize( nframe );
                        m_runs.resize( nframe );
                        m_frame.resize( nframe );
                        m_positionH.resize( nframe );
                        m_nFirstADC.resize( nframe );
                        m_nFirstSer.resize( nframe );
                        m_nFirstTable.resize( nframe );
                        m_nFirstMsg.resize( nframe );
                        Stream >> m_dataQuality >> m_GTimeS >> m_GTimeN >>
                            m_dt >> m_runs >> m_frame >> m_positionH >>
                            m_nFirstADC >> m_nFirstSer >> m_nFirstTable >>
                            m_nFirstMsg;
                    }
                    nsh_type nsh;
                    Stream >> nsh;
                    if ( nsh > 0 )
                    {
                        m_SHid.resize( nsh );
                        std::vector< io_shname_type > io_SHname( nsh );
                        Stream >> m_SHid >> io_SHname;
                        m_SHname.resize( nsh );
                        std::copy( io_SHname.begin( ),
                                   io_SHname.end( ),
                                   m_SHname.begin( ) );
                    }
                    ndetector_type ndetector;
                    Stream >> ndetector;
                    if ( ndetector > 0 )
                    {
                        std::vector< io_namedetector_type > io_nameDetector{
                            ndetector
                        };
                        m_positionDetector.resize( ndetector );
                        Stream >> io_nameDetector >> m_positionDetector;
                        m_nameDetector.resize( ndetector );
                        std::copy( io_nameDetector.begin( ),
                                   io_nameDetector.end( ),
                                   m_nameDetector.begin( ) );
                    }
                }

            protected:
                //-----------------------------------------------------------------
                /// \brief Iterate over contents.
                ///
                /// \param[in] Info
                ///     Specifies the type of information to be searched.
                ///
                /// \param[in] Action
                ///     Action to be taken for each piece of information found.
                //-----------------------------------------------------------------
                void
                forEach( Common::FrTOC::query_info_type Info,
                         Common::FrTOC::FunctionBase&   Action ) const
                {
                    switch ( Info )
                    {
                    case Common::FrTOC::TOC_DETECTOR:
                    {
                        try
                        {
                            Common::FrTOC::FunctionC& action(
                                dynamic_cast< Common::FrTOC::FunctionC& >(
                                    Action ) );

                            for ( namedetector_container_type::const_iterator
                                      cur = GetNameDetector( ).begin( ),
                                      last = GetNameDetector( ).end( );
                                  cur != last;
                                  ++cur )
                            {
                                try
                                {
                                    const Common::DetectorNames::info_type&
                                        info( DetectorNameTable.Detector(
                                            *cur ) );

                                    action( info.s_prefix[ 0 ] );
                                }
                                catch ( ... )
                                {
                                }
                            }
                        }
                        catch ( ... )
                        {
                            // Does not understand Action
                        }
                    }
                    break;
                    case Common::FrTOC::TOC_FR_STRUCTS:
                    {
                        try
                        {
                            Common::FrTOC::FunctionSI& action(
                                dynamic_cast< Common::FrTOC::FunctionSI& >(
                                    Action ) );
                            shid_container_type::const_iterator
                                cur_id = GetSHid( ).begin( ),
                                last_id = GetSHid( ).end( );
                            shname_container_type::const_iterator
                                cur_name = GetSHname( ).begin( ),
                                last_name = GetSHname( ).end( );
                            while ( ( cur_id != last_id ) &&
                                    ( cur_name != last_name ) )
                            {
                                action( *cur_name, *cur_id );
                                ++cur_name;
                                ++cur_id;
                            }
                        }
                        catch ( ... )
                        {
                        }
                    }
                    break;
                    default:
                        //---------------------------------------------------------------
                        // ignore all other requests
                        //---------------------------------------------------------------
                        break;
                    }
                }

                //-----------------------------------------------------------------
                /// \brief Write the structure to the stream
                ///
                /// \param[in] Stream
                ///     The output stream where the object is to be written.
                //-----------------------------------------------------------------
                void
                write( Common::OStream& Stream ) const
                {
                    std::vector< io_shname_type > io_shname( m_SHname.size( ) );
                    std::copy( m_SHname.begin( ),
                               m_SHname.end( ),
                               io_shname.begin( ) );
                    std::vector< io_namedetector_type > io_nameDetector(
                        m_nameDetector.size( ) );
                    std::copy( m_nameDetector.begin( ),
                               m_nameDetector.end( ),
                               io_nameDetector.begin( ) );

                    Stream << m_ULeapS << nFrame_type( m_dataQuality.size( ) )
                           << m_dataQuality << m_GTimeS << m_GTimeN << m_dt
                           << m_runs << m_frame << m_positionH << m_nFirstADC
                           << m_nFirstSer << m_nFirstTable << m_nFirstMsg
                           << nsh_type( m_SHid.size( ) ) << m_SHid << io_shname
                           << ndetector_type( io_nameDetector.size( ) )
                           << io_nameDetector << m_positionDetector;
                }

            private:
                typedef STRING io_namedetector_type;
                typedef STRING io_shname_type;
            };

        }; // namespace FrTOCImpl

    } // namespace Version_8
} // namespace FrameCPP

#endif /* ! defined(SWIG) */
#endif /* defined( __cplusplus ) */

#endif /* FrameCPP_VERSION_8__IMPL__FrTOCDataClassicIO_HH */
