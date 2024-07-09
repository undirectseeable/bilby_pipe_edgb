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

#ifndef FrameCPP_VERSION_8__IMPL__FrTOCProcDataClassicIO_HH
#define FrameCPP_VERSION_8__IMPL__FrTOCProcDataClassicIO_HH

#include "framecpp/Version8/impl/FrTOCProcDataData.hh"

#if defined( __cplusplus )
#if !defined( SWIG )

#include "framecpp/Common/Description.hh"
#include "framecpp/Common/FrameSpec.hh"
#include "framecpp/Common/FrameSpec.tcc"
#include "framecpp/Common/TOCInfo.hh"

#include "framecpp/Version7/FrTOCProcData.hh"

#include "framecpp/Version8/impl/FrTOCConstants.hh"
#include "framecpp/Version8/impl/FrTOCProcDataData.hh"

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
            class FrTOCProcDataClassicIO : public virtual FrTOCProcDataData
            {
            public:
                //-----------------------------------------------------------------
                /// \brief Default constructor.
                //-----------------------------------------------------------------
                FrTOCProcDataClassicIO( ) = default;

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
                    Common::FrameSpec::size_type retval = sizeof( nproc_type );
                    if ( m_info.size( ) )
                    {
                        retval += ( m_info.size( ) *
                                    ( sizeof( position_type ) *
                                      m_info.begin( )->second.size( ) ) );
                    }
                    for ( MapProc_type::const_iterator cur = m_info.begin( ),
                                                       last = m_info.end( );
                          cur != last;
                          ++cur )
                    {
                        retval += cur->first.Bytes( );
                    }
                    return retval;
                }

                //-----------------------------------------------------------------
                /// \brief Gather TOC info for FrProcData being written.
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
                void
                QueryProc( const Common::TOCInfo& Info,
                           INT_4U                 FrameOffset,
                           INT_8U                 Position )
                {
                    using Common::TOCInfo;

                    STRING name;

                    Info.TOCQuery( TOCInfo::IC_NAME,
                                   TOCInfo::DT_STRING_2,
                                   &name,
                                   TOCInfo::IC_EOQ );

                    proc_info_type& i( m_info[ name ] );
                    i.resize( FrameOffset + 1 );
                    i[ FrameOffset ] = Position;
                }

#if !defined( SWIG )
                //-----------------------------------------------------------------
                /// \brief asignment operator
                ///
                /// \param[in] Source
                ///     The source to be copied.
                //-----------------------------------------------------------------
                inline const FrTOCProcDataClassicIO&
                operator=( const Previous::FrTOCProcData& Source )
                {
                    m_keys = Source.GetKeys( );
                    m_info = Source.GetProc( );

                    return *this;
                }
#endif /* ! defined(SWIG) */

                inline FrTOCProcDataClassicIO&
                operator=( FrTOCProcDataClassicIO&& TOC )
                {
                    static_cast< FrTOCProcDataData& >( *this ) =
                        static_cast< FrTOCProcDataData&& >( TOC );
                    return *this;
                }

                //-----------------------------------------------------------------
                /// \brief equality operator
                ///
                /// \param[in] RHS
                ///     The FrTOCProcData object to be compared.
                ///
                /// \return
                ///     The value true is returned if this object is equivelent
                ///     to the RHS instance; false otherwise.
                //-----------------------------------------------------------------
                bool operator==( const FrTOCProcDataClassicIO& RHS ) const;

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
                    Desc( SE( "nProc",
                              "INT_4U",
                              "Number of unique FrProcData names in file." ) );
                    Desc( SE( "nameProc",
                              "STRING[nProc]",
                              "Array of FrProcData names" ) );
                    Desc( SE(
                        "positionProc",
                        "INT_8U[nProc][nFrame]",
                        "Array of lists of FrProcData offset positions, in "
                        "bytes,"
                        " from beginning of file (size of nFrame*nProc)" ) );
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
                void Load( istream_type& Stream, INT_4U FrameCount );

            protected:
                //---------------------------------------------------------------
                /// \brief TOC optimization
                ///
                /// This method optimizes the TOC reading by only reading
                /// the structure offsets.
                /// Once read, it is moved into the structure.
                //---------------------------------------------------------------
                inline void
                cachePositions( istream_type& Stream )
                {
                    std::streampos       here( Stream.tellg( ) );
                    positions_cache_type positions( frame_count *
                                                    m_keys.size( ) );

                    Stream.seekg( -positions_cache_offset, Stream.end );
                    Stream >> positions_cache;
                    Stream.seekg( here, Stream.beg );

                    //-------------------------------------------------------------
                    // Move into structure.
                    //-------------------------------------------------------------
                    input_iterator f( m_info, positions.begin( ), frame_count );

                    std::for_each( m_keys.begin( ), m_keys.end( ), f );
                }

                //-----------------------------------------------------------------
                /// \brief Iterate over contents.
                ///
                /// \param[in] Info
                ///     Specifies the type of information to be searched.
                ///
                /// \param[in] Action
                ///     Action to be taken for each piece of information found.
                //-----------------------------------------------------------------
                inline void
                forEach( Common::FrTOC::query_info_type Info,
                         Common::FrTOC::FunctionBase&   Action ) const
                {
                    switch ( Info )
                    {
                    case Common::FrTOC::TOC_CHANNEL_NAMES:
                    {
                        try
                        {
                            Common::FrTOC::FunctionString& action(
                                dynamic_cast< Common::FrTOC::FunctionString& >(
                                    Action ) );

                            for ( MapProc_type::const_iterator
                                      cur = m_info.begin( ),
                                      last = m_info.end( );
                                  cur != last;
                                  ++cur )
                            {
                                action( cur->first );
                            }
                        }
                        catch ( ... )
                        {
                            // Does not understand Action
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

                inline void
                setPositionsOffset( istream_type& Stream )
                {
                    positions_cache_offset = Stream.Size( ) - Stream.tellg( );
                }

                //-----------------------------------------------------------------
                /// \brief Write the structure to the stream
                ///
                /// \param[in] Stream
                ///     The output stream where the object is to be written.
                //-----------------------------------------------------------------
                inline void
                write( Common::OStream& Stream ) const
                {
                    //-----------------------------------------------------------------
                    // Flatten data so it is streamable
                    //-----------------------------------------------------------------
                    std::vector< name_type >::size_type s( m_info.size( ) );
                    if ( s )
                    {
                        std::vector< name_type >::size_type fc(
                            m_info.begin( )->second.size( ) );

                        std::vector< name_type >     names( s );
                        std::vector< position_type > positions( s * fc );
                        //---------------------------------------------------------------
                        // Copy data for streaming
                        //---------------------------------------------------------------
                        std::vector< name_type >::iterator cur_name =
                            names.begin( );
                        std::vector< position_type >::iterator cur_position =
                            positions.begin( );

                        for ( MapProc_type::const_iterator
                                  cur = m_info.begin( ),
                                  last = m_info.end( );
                              cur != last;
                              ++cur, ++cur_name, cur_position += fc )
                        {
                            *cur_name = cur->first;
                            std::copy( cur->second.begin( ),
                                       cur->second.end( ),
                                       cur_position );
                        }
                        //---------------------------------------------------------------
                        // Stream out
                        //---------------------------------------------------------------
                        Stream << nproc_type( s ) << names << positions;
                    }
                    else
                    {
                        Stream << nproc_type( NO_DATA_AVAILABLE );
                    }
                }

            private:
                typedef std::vector< position_type >              info_type;
                typedef typename std::map< name_type, info_type > Map_type;
                typedef typename std::vector< name_type > key_container_type;
                typedef std::vector< position_type >      positions_cache_type;
                typedef INT_4U                            frame_count_type;
                typedef INT_4U                            n_type;

                class input_iterator
                {
                public:
                    input_iterator( Map_type& Destination,
                                    typename info_type::const_iterator Position,
                                    frame_count_type FrameCount )
                        : destination( Destination ), cur_position( Position ),
                          frame_count( FrameCount ), it( Destination.begin( ) )
                    {
                    }

                    void
                    operator( )( const typename Map_type::key_type& Name )
                    {
                        typedef typename Map_type::value_type  value_type;
                        typedef typename Map_type::mapped_type mapped_type;

                        it = destination.insert(
                            it,
                            value_type(
                                Name,
                                mapped_type( cur_position,
                                             cur_position + frame_count ) ) );
                        cur_position += frame_count;
                    }

                private:
                    Map_type&                          destination;
                    typename info_type::const_iterator cur_position;
                    frame_count_type                   frame_count;
                    typename Map_type::iterator        it;
                }; // class input_iterator

                frame_count_type frame_count{ 0 };
                //---------------------------------------------------------------
                /// A cache of the positions of the FrAdcData structures within
                /// the stream.
                //---------------------------------------------------------------
                positions_cache_type positions_cache;
                //---------------------------------------------------------------
                /// The number of bytes from the end of the stream where the
                ///   array containing the FrAdcData offsets.
                //---------------------------------------------------------------
                position_type positions_cache_offset{ 0 };
            }; // class ClassicIO

        } // namespace FrTOCImpl
    } // namespace Version_8
} // namespace FrameCPP

#endif /* ! defined(SWIG) */
#endif /* defined( __cplusplus ) */

#endif /* FrameCPP_VERSION_8__IMPL__FrTOCProcDataClassicIO_HH */
