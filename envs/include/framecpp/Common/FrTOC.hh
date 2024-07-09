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

#ifndef FrameCPP__COMMON__FR_TOC_HH
#define FrameCPP__COMMON__FR_TOC_HH

#include "framecpp/Common/FrameSpec.hh"
#include "framecpp/Common/STRING.hh"
#include "framecpp/Common/FrStatData.hh"

namespace FrameCPP
{
    namespace Common
    {
        class Description;

        class FrTOC : public FrameSpec::Object
        {
        public:
            typedef INT_8U cmn_position_type;
            typedef INT_4U channel_id_type;

            enum query_info_type
            {
                TOC_CHANNEL_NAMES,
                TOC_DETECTOR,
                TOC_FR_STRUCTS
            };

            class FunctionBase
            {
            public:
                virtual ~FunctionBase( );
            };

            //-----------------------------------------------------------------
            /// \brief Function class used by ForEach method
            ///
            /// This function class is used to describe a function that
            /// takes as its parameters a single character argument.
            //-----------------------------------------------------------------
            class FunctionC : public FunctionBase
            {
            public:
                //---------------------------------------------------------------
                /// \brief Destructor
                //---------------------------------------------------------------
                virtual ~FunctionC( );

                //---------------------------------------------------------------
                /// \brief Prototype for function.
                //---------------------------------------------------------------
                virtual void operator( )( char C ) = 0;
            };

            class FunctionString : public FunctionBase
            {
            public:
                virtual ~FunctionString( );

                virtual void operator( )( const std::string& StrObj ) = 0;
            };

            //-----------------------------------------------------------------
            //-----------------------------------------------------------------
            class FunctionSI : public FunctionBase
            {
            public:
                //---------------------------------------------------------------
                /// \brief Destructor
                //---------------------------------------------------------------
                virtual ~FunctionSI( );

                //---------------------------------------------------------------
                /// \brief Prototype for function.
                //---------------------------------------------------------------
                virtual void operator( )( const std::string& S, INT_4U I ) = 0;
            };

            //===================================================================
            /// \brief Used for TOC optimization of channel offsets
            //===================================================================
            template < typename TString, typename TPosition >
            class PositionWithCache
            {
            public:
                typedef INT_4U    frame_count_type;
                typedef INT_4U    n_type;
                typedef TString   name_type;
                typedef TPosition position_type;

                typedef std::vector< position_type >              info_type;
                typedef typename std::map< name_type, info_type > Map_type;
                typedef typename std::vector< name_type > key_container_type;

                inline Common::FrameSpec::size_type
                Bytes( const Common::StreamBase& Stream ) const
                {
                    Common::FrameSpec::size_type retval = sizeof( n_type );
                    if ( m_info.size( ) )
                    {
                        retval += ( m_info.size( ) *
                                    ( sizeof( position_type ) *
                                      m_info.begin( )->second.size( ) ) );
                    }
                    for ( typename Map_type::const_iterator
                              cur = m_info.begin( ),
                              last = m_info.end( );
                          cur != last;
                          ++cur )
                    {
                        retval += cur->first.Bytes( );
                    }
                    return retval;
                }

                inline const key_container_type&
                GetPositionKeys( ) const
                {
                    return m_keys;
                }

                inline void
                write( Common::OStream& Stream ) const
                {
                    //-----------------------------------------------------------------
                    // Flatten data so it is streamable
                    //-----------------------------------------------------------------
                    typename std::vector< name_type >::size_type s(
                        m_info.size( ) );
                    if ( s )
                    {
                        typename std::vector< name_type >::size_type fc(
                            m_info.begin( )->second.size( ) );

                        std::vector< name_type >     names( s );
                        std::vector< position_type > positions( s * fc );
                        //---------------------------------------------------------------
                        // Copy data for streaming
                        //---------------------------------------------------------------
                        typename std::vector< name_type >::iterator cur_name =
                            names.begin( );
                        typename std::vector< position_type >::iterator
                            cur_position = positions.begin( );

                        for ( typename Map_type::const_iterator
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
                        Stream << n_type( s ) << names << positions;
                    }
                    else
                    {
                        Stream << ~n_type( 0 );
                    }
                }

                inline const PositionWithCache&
                operator=( const PositionWithCache& Source )
                {
                    m_keys = Source.m_keys;
                    m_info = Source.m_info;

                    return *this;
                }

            protected:
                key_container_type m_keys;
                Map_type           m_info;

                inline PositionWithCache( ) : frame_count( 0 )
                {
                }

                inline PositionWithCache( Common::IStream& Stream,
                                          frame_count_type FrameCount )
                    : frame_count( FrameCount )
                {
                    n_type n;
                    Stream >> n;
                    if ( n && ( n != ~n_type( 0 ) ) )
                    {
                        //---------------------------------------------------------------
                        // Read in the information
                        //---------------------------------------------------------------
                        typename key_container_type::size_type s( n );
                        std::vector< position_type >           positions( s *
                                                                FrameCount );

                        m_keys.resize( s );

                        Stream >> m_keys;
                        setPositionsOffset( Stream );
                        Stream >> positions;
                        //---------------------------------------------------------------
                        // Move into structure.
                        //---------------------------------------------------------------
                        input_iterator f(
                            m_info, positions.begin( ), FrameCount );

                        std::for_each( m_keys.begin( ), m_keys.end( ), f );
                    }
                }

                inline const Map_type&
                getInfo( ) const
                {
                    return m_info;
                }

                inline typename Map_type::const_iterator
                getInfo( const std::string& Name ) const
                {
                    return getInfo( ).find( Name );
                }

                inline typename Map_type::const_iterator
                getInfo( INT_4U Index ) const
                {
                    const Map_type& i( getInfo( ) );

                    if ( Index >= i.size( ) )
                    {
                        return i.end( );
                    }
                    return i.find( m_keys[ Index ] );
                }

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

                inline void
                setPositionsOffset( istream_type& Stream )
                {
                    positions_cache_offset = Stream.Size( ) - Stream.tellg( );
                }

                inline bool operator==( const PositionWithCache& RHS ) const;

            private:
                typedef std::vector< position_type > positions_cache_type;

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

                frame_count_type frame_count;
                //---------------------------------------------------------------
                /// A cache of the positions of the FrAdcData structures within
                /// the stream.
                //---------------------------------------------------------------
                positions_cache_type positions_cache;
                //---------------------------------------------------------------
                /// The number of bytes from the end of the stream where the
                ///   array containing the FrAdcData offsets.
                //---------------------------------------------------------------
                position_type positions_cache_offset;
            }; // class PositionWithCache

            typedef boost::shared_ptr< FrameSpec::Object > object_type;

            static const Common::FrameSpec::Info::frame_object_types
                s_object_id = Common::FrameSpec::Info::FSI_FR_TOC;

            FrTOC( const Description* Desc );

            typedef std::vector< STRING< INT_2U > > cmn_name_container_type;
            typedef std::vector< REAL_8 >           cmn_dt_container_type;
            typedef std::vector< INT_4U >           cmn_GTimeS_container_type;
            typedef std::vector< INT_4U >           cmn_GTimeN_container_type;
            typedef std::vector< INT_4S >           cmn_runs_container_type;

            virtual ~FrTOC( );

            virtual void ForEach( query_info_type Info,
                                  FunctionBase&   Action ) const;

            virtual void IndexObject( object_type    Obj,
                                      std::streampos Position ) = 0;

            //-----------------------------------------------------------------
            //
            //-----------------------------------------------------------------

            virtual void
            FrStatDataQuery( const std::string&            NamePattern,
                             const LDASTools::AL::GPSTime& StartTime,
                             const LDASTools::AL::GPSTime& EndTime,
                             const INT_4U                  Version,
                             FrStatData::Query&            Result ) const = 0;

            //-----------------------------------------------------------------
            // Interface routines
            //-----------------------------------------------------------------
            virtual INT_4U nFrame( ) const = 0;

            virtual const cmn_dt_container_type&     dt( ) const = 0;
            virtual const cmn_GTimeS_container_type& GTimeS( ) const = 0;
            virtual const cmn_GTimeN_container_type& GTimeN( ) const = 0;

            //-----------------------------------------------------------------
            /// \brief Retrieve the stream position for the detector
            ///
            /// \param[in] Name
            ///     The name of the detector for which the position is
            ///     being requested.
            ///
            /// \return
            ///     Upon successfully locating the requested detector,
            ///     its position within the stream is returned,
            ///     otherwise a detailed exception is throw.
            //-----------------------------------------------------------------
            virtual cmn_position_type
            positionDetector( const std::string& Name ) const = 0;

            virtual cmn_position_type positionH( INT_4U FrameIndex ) const = 0;
            virtual const cmn_name_container_type& nameADC( ) const = 0;
            virtual cmn_position_type
            positionADC( INT_4U             FrameIndex,
                         const std::string& Channel ) const = 0;
            virtual cmn_position_type
            positionADC( INT_4U FrameIndex, channel_id_type Channel ) const = 0;
            virtual cmn_position_type
            positionEvent( INT_4U             FrameIndex,
                           const std::string& Channel ) const = 0;
            virtual cmn_position_type
                                                   positionEvent( const std::string& EventType,
                                                                  INT_4U             Index ) const = 0;
            virtual const cmn_name_container_type& nameProc( ) const = 0;
            virtual cmn_position_type
            positionProc( INT_4U             FrameIndex,
                          const std::string& Channel ) const = 0;
            virtual cmn_position_type
                                                   positionProc( INT_4U          FrameIndex,
                                                                 channel_id_type Channel ) const = 0;
            virtual const cmn_name_container_type& nameSim( ) const = 0;
            virtual cmn_position_type
                                                   positionSim( INT_4U             FrameIndex,
                                                                const std::string& Channel ) const = 0;
            virtual const cmn_name_container_type& nameSer( ) const = 0;
            virtual cmn_position_type
            positionSer( INT_4U             FrameIndex,
                         const std::string& Channel ) const = 0;
            virtual cmn_position_type
            positionSimEvent( INT_4U             FrameIndex,
                              const std::string& Channel ) const = 0;
            virtual cmn_position_type
            positionSimEvent( const std::string& EventType,
                              INT_4U             Index ) const = 0;

            virtual cmn_runs_container_type const& runs( ) const = 0;
            virtual INT_4U                         nSH( ) const = 0;
            virtual INT_2U             SHid( INT_4U Offset ) const = 0;
            virtual const std::string& SHname( INT_4U Offset ) const = 0;

            //-----------------------------------------------------------------
            /// \brief Cache where the positions of the Adc channels
            ///
            /// \param[in,out] Stream
            ///     The Stream being read
            //-----------------------------------------------------------------
            virtual void cacheAdcDataPositions( istream_type& Stream ) = 0;

            //-----------------------------------------------------------------
            /// \brief Advance to the specified Adc channel
            ///
            /// \param[in,out] Stream
            ///     The Stream being read
            /// \param[in] Channel
            ///     The requested channel
            //-----------------------------------------------------------------
            virtual void seekAdcDataPositions( istream_type&   Stream,
                                               channel_id_type Channel ) = 0;
            //-----------------------------------------------------------------
            /// \brief Advance to the specified Adc channel
            ///
            /// \param[in,out] Stream
            ///     The Stream being read
            /// \param[in] Channel
            ///     The requested channel
            //-----------------------------------------------------------------
            virtual void seekAdcDataPositions( istream_type&      Stream,
                                               const std::string& Channel ) = 0;

            //-----------------------------------------------------------------
            /// \brief Cache where the positions of the FrProcData channels
            ///
            /// \param[in,out] Stream
            ///     The Stream being read
            //-----------------------------------------------------------------
            virtual void procDataCachePositions( istream_type& Stream ) = 0;

        protected:
            friend class IFrameStream;
            void setAdcDataPoisitions( );

            //-----------------------------------------------------------------
            ///
            //-----------------------------------------------------------------
            virtual void loadHeader( Common::IStream& Stream ) = 0;

        }; // class FrTOC
    } // namespace Common
} // namespace FrameCPP

#endif /* FrameCPP__COMMON__FR_TOC_HH */
