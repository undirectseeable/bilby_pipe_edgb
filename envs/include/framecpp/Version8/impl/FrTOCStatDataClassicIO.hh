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

#ifndef FrameCPP_VERSION_8__IMPL__FrTOCStatDataClassicIO_HH
#define FrameCPP_VERSION_8__IMPL__FrTOCStatDataClassicIO_HH

#include "framecpp/Version8/impl/FrTOCStatDataData.hh"

#if defined( __cplusplus )
#if !defined( SWIG )

#include "framecpp/Common/Description.hh"
#include "framecpp/Common/FrameSpec.hh"
#include "framecpp/Common/FrameSpec.tcc"
#include "framecpp/Common/TOCInfo.hh"

#include "framecpp/Version7/FrTOCStatData.hh"

#include "framecpp/Version8/impl/FrTOCConstants.hh"
#include "framecpp/Version8/impl/FrTOCStatDataData.hh"

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
            class FrTOCStatDataClassicIO : public virtual FrTOCStatDataData
            {
            public:
                //-----------------------------------------------------------------
                /// \brief Default constructor.
                //-----------------------------------------------------------------
                FrTOCStatDataClassicIO( ) = default;
                //-----------------------------------------------------------------
                /// \brief Number of bytes needed to write this structure
                ///
                /// \param[in] Stream
                ///     The stream from which to the object is being read or
                ///     written.
                ///
                /// \return
                ///     The number of bytes need to read or write this object.
                //-----------------------------------------------------------------
                inline Common::FrameSpec::size_type
                Bytes( const Common::StreamBase& Stream ) const
                {
                    Common::FrameSpec::size_type retval =
                        sizeof( nstat_type ) // nStatType
                        + sizeof( nstat_type ) // nTotalStat
                        ;

                    static const INT_4U si = sizeof( tstart_type ) +
                        sizeof( tend_type ) + sizeof( version_type ) +
                        sizeof( positionStat_type );

                    for ( stat_container_type::const_iterator
                              cur = m_info.begin( ),
                              last = m_info.end( );
                          cur != last;
                          ++cur )
                    {
                        retval += cur->first.Bytes( ) +
                            cur->second.detector.Bytes( ) +
                            sizeof( nstat_instance_type ) +
                            ( cur->second.stat_instances.size( ) * si );
                    }
                    return retval;
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
                    Desc( SE(
                        "nStatType",
                        "INT_4U",
                        "Number of static data block types in the file." ) );
                    Desc(
                        SE( "nameStat",
                            "STRING[nStatType]",
                            "Array of FrStatData name (size of nStatType)" ) );
                    Desc( SE( "detector",
                              "STRING[nStatType]",
                              "Array of Detector name(size of nStatType)" ) );
                    Desc( SE( "nStatInstance",
                              "INT_4U[nStatType]",
                              "Array of number of instance for each "
                              "FrStatData(size of "
                              "nStatType)" ) );
                    Desc( SE( "nTotalStat",
                              "INT_4U",
                              "Summation of nStatInstance array" ) );

                    Desc( SE( "tStart",
                              "INT_4U[nTotalStat]",
                              "Array of GPS integer start times,"
                              " in seconds (size of nTotalStat)" ) );
                    Desc( SE( "tEnd",
                              "INT_4U[nTotalStat]",
                              "Array of GPS integer end times,"
                              " in seconds (size of nTotalStat)" ) );
                    Desc( SE( "version",
                              "INT_4U[nTotalStat]",
                              "Array of version time"
                              " (size of nTotalStat)" ) );
                    Desc( SE(
                        "positionStat",
                        "INT_8U[nTotalStat]",
                        "Array of FrStatData positions from beginning of file"
                        " (size of nTotalStat)" ) );
                }

#if !defined( SWIG )
                //-----------------------------------------------------------------
                /// \brief asignment operator
                ///
                /// \param[in] Source
                ///     The source to be copied.
                //-----------------------------------------------------------------
                const FrTOCStatDataClassicIO&
                operator=( const Previous::FrTOCStatData& Source )
                {
#if WORKING
                    /// \todo Copy the contents from the Previous frame spec
                    /// object
                    m_info = Source.GetStat( );
#endif /* WORKING */

                    return *this;
                }
#endif /* ! defined(SWIG) */

                inline FrTOCStatDataClassicIO&
                operator=( FrTOCStatDataClassicIO&& TOC )
                {
                    static_cast< FrTOCStatDataData& >( *this ) =
                        static_cast< FrTOCStatDataData&& >( TOC );
                    return *this;
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
                inline void
                Load( istream_type& Stream )
                {
                    nstat_type nstat;

                    Stream >> nstat;
                    if ( nstat && ( nstat != NO_DATA_AVAILABLE ) )
                    {
                        std::vector< name_type >           names( nstat );
                        std::vector< detector_type >       detectors( nstat );
                        std::vector< nstat_instance_type > nstatinstances(
                            nstat );
                        nstat_type ntotalstat;

                        Stream >> names >> detectors >> nstatinstances >>
                            ntotalstat;

                        std::vector< tstart_type >       tstart( ntotalstat );
                        std::vector< tend_type >         tend( ntotalstat );
                        std::vector< version_type >      version( ntotalstat );
                        std::vector< positionStat_type > position( ntotalstat );

                        Stream >> tstart >> tend >> version >> position;

                        //---------------------------------------------------------------
                        // Fill in the structure
                        //---------------------------------------------------------------
                        m_info.erase( m_info.begin( ), m_info.end( ) );
                        INT_4U offset = 0;
                        INT_4U suboffset = 0;
                        for ( std::vector< name_type >::const_iterator
                                  cur_name = names.begin( ),
                                  last_name = names.end( );
                              cur_name != last_name;
                              ++cur_name )
                        {
                            stat_type& s( m_info[ *cur_name ] );

                            //-------------------------------------------------------------
                            // Fill in the static data core
                            //-------------------------------------------------------------
                            s.detector = detectors[ offset ];
                            //-------------------------------------------------------------
                            // Fill in the version specific information
                            //-------------------------------------------------------------
                            if ( nstatinstances[ offset ] )
                            {
                                s.stat_instances.resize(
                                    nstatinstances[ offset ] );
                                for ( nstat_type
                                          x = 0,
                                          x_end = nstatinstances[ offset ];
                                      x != x_end;
                                      ++x )
                                {
                                    s.stat_instances[ x ].tStart =
                                        tstart[ suboffset ];
                                    s.stat_instances[ x ].tEnd =
                                        tend[ suboffset ];
                                    s.stat_instances[ x ].version =
                                        version[ suboffset ];
                                    s.stat_instances[ x ].positionStat =
                                        position[ suboffset ];
                                    ++suboffset;
                                }
                            }
                            ++offset;
                        }
                    }
                    else
                    {
                        nstat_type tstat;

                        Stream >> tstat;
                    }
                }

                //-----------------------------------------------------------------
                /// \brief Gather TOC info for FrStatData being written.
                ///
                /// \param[in] Info
                ///     Information
                ///
                /// \param[in] FrameOffset
                ///     The frame offset of the frame being written.
                ///     The frame offsets start at 0 (zero).
                ///
                /// \param[in] Position
                ///     The byte offset from the start of the file
                ///     where the structure is written.
                //-----------------------------------------------------------------
                inline void
                QueryStatData( const Common::TOCInfo& Info,
                               INT_4U                 FrameOffset,
                               INT_8U                 Position )
                {
                    using Common::TOCInfo;

                    STRING name;
                    STRING detector;
                    INT_4U start;
                    INT_4U end;
                    INT_4U version;

                    Info.TOCQuery( TOCInfo::IC_NAME,
                                   TOCInfo::DataType( name ),
                                   &name,
                                   TOCInfo::IC_DETECTOR,
                                   TOCInfo::DataType( detector ),
                                   &detector,
                                   TOCInfo::IC_START,
                                   TOCInfo::DataType( start ),
                                   &start,
                                   TOCInfo::IC_END,
                                   TOCInfo::DataType( end ),
                                   &end,
                                   TOCInfo::IC_VERSION,
                                   TOCInfo::DataType( version ),
                                   &version,
                                   TOCInfo::IC_EOQ );

                    stat_instance_type si;

                    si.tStart = start;
                    si.tEnd = end;
                    si.version = version;
                    si.positionStat = Position;

                    stat_type& i( m_info[ name ] );
                    if ( ( i.detector.length( ) ) &&
                         ( i.detector != detector ) )
                    {
                        std::ostringstream msg;

                        msg << "FrStatData with the name '" << name
                            << "' is associated with detector '" << i.detector
                            << "' and detector '" << detector << "'";
                        throw std::runtime_error( msg.str( ) );
                    }
                    i.detector = detector;
                    i.stat_instances.push_back( si );
                }

            protected:
                //-----------------------------------------------------------------
                /// \brief Write the structure to the stream
                ///
                /// \param[in] Stream
                ///     The output stream where the object is to be written.
                //-----------------------------------------------------------------
                inline void
                write( ostream_type& Stream ) const
                {
                    if ( m_info.size( ) > 0 )
                    {
                        //---------------------------------------------------------------
                        // Flatten the strucutres.
                        //---------------------------------------------------------------

                        nstat_type offset( 0 );

                        std::vector< name_type >     names( m_info.size( ) );
                        std::vector< detector_type > detectors(
                            m_info.size( ) );
                        std::vector< nstat_type > nstatinstances(
                            m_info.size( ) );
                        nstat_type ntotalstat = 0;

                        std::vector< tstart_type >       tstart;
                        std::vector< tend_type >         tend;
                        std::vector< version_type >      version;
                        std::vector< positionStat_type > position;

                        for ( stat_container_type::const_iterator
                                  cur = m_info.begin( ),
                                  last = m_info.end( );
                              cur != last;
                              ++cur, ++offset )
                        {
                            names[ offset ] = cur->first;
                            detectors[ offset ] = cur->second.detector;
                            nstatinstances[ offset ] =
                                cur->second.stat_instances.size( );
                            ntotalstat += cur->second.stat_instances.size( );
                            for ( stat_instance_container_type::const_iterator
                                      cur_instance =
                                          cur->second.stat_instances.begin( ),
                                      last_instance =
                                          cur->second.stat_instances.end( );
                                  cur_instance != last_instance;
                                  ++cur_instance )
                            {
                                tstart.push_back( cur_instance->tStart );
                                tend.push_back( cur_instance->tEnd );
                                version.push_back( cur_instance->version );
                                position.push_back(
                                    cur_instance->positionStat );
                            }
                        }

                        Stream << nstat_type( m_info.size( ) ) << names
                               << detectors << nstatinstances << ntotalstat
                               << tstart << tend << version << position;
                    }
                    else
                    {
#if WORKING
                        Stream << nstat_type( NO_DATA_AVAILABLE );
#else /* WORKING */
                        Stream << nstat_type( 0 ); // nStatType
                        Stream << nstat_type( 0 ); // nTotalStat
#endif /* WORKING */
                    }
                }
            };

        }; // namespace FrTOCImpl

    } // namespace Version_8
} // namespace FrameCPP

#endif /* ! defined(SWIG) */
#endif /* defined( __cplusplus ) */

#endif /* FrameCPP_VERSION_8__IMPL__FrTOCStatDataClassicIO_HH */
