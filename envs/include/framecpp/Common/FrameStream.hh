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

#ifndef FRAMECPP__COMMON__FrameStream_HH
#define FRAMECPP__COMMON__FrameStream_HH

#if !defined( SWIGIMPORTED )
#include <list>
#include <set>
#include <stdexcept>

#include <boost/shared_ptr.hpp>
#endif /* ! defined(SWIGIMPORTED) */

#include "ldastoolsal/types.hh"

#if !defined( SWIGIMPORTED )
// #include "framecpp/FrameCPP.hh"

#include "framecpp/Common/FrameSpec.hh"
#include "framecpp/Common/FrHeader.hh"
#include "framecpp/Common/FrEndOfFile.hh"
#include "framecpp/Common/FrStatData.hh"
#include "framecpp/Common/FrTOC.hh"

#include "framecpp/Common/IOStream.hh"
#endif /* ! defined(SWIGIMPORTED) */

namespace FrameCPP
{
    namespace Common
    {
        class IStream;
        class OStream;
        class StreamRefInterface;
        class FrStatData;
        class FrDetector;
        class Verify;

        //===================================================================
        //===================================================================
        class FrameStream : virtual protected StreamBase
        {
        public:
            using StreamBase::object_type;

            typedef FrHeader::frame_library_type    frame_library_type;
            typedef FrHeader::library_revision_type library_revision_type;
            typedef FrameSpec::version_type         version_type;
            typedef const StreamRefInterface*       streamref_interface_type;
            typedef INT_4U                          fr_event_offset_type;
            typedef INT_4U                          fr_sim_event_offset_type;

            frame_library_type FrameLibrary( ) const;

            library_revision_type LibraryRevision( ) const;

            version_type Version( ) const;

            const std::string& GetLastError( ) const;

            const MD5Sum& GetMD5Sum( ) const;

        protected:
            bool m_closed_state;

            FrameStream( version_type Version, bool AllowZeroVersion );

            using StreamBase::frameSpecInfo;

            virtual void frameSpecInfo( const FrameSpec::Info* Spec );

            void setLastError( const std::string& Message );

            void setTOC( );

            const StreamRefInterface& streamRef( ) const;

            void version_stream( version_type Version );

        protected:
            void frameLibrary( frame_library_type FrameLibrary );

            void libraryRevision( library_revision_type LibraryRevision );

            version_type memoryVersion( ) const;
            version_type streamVersion( ) const;

            virtual void reset( );

            std::unique_ptr< MD5SumFilter > m_md5sumFilter;

        private:
            frame_library_type m_frame_library;

            library_revision_type m_library_revision;

            /// \brief Version number to use for frames in memory
            version_type m_memory_version;

            /// \brief Version number to use for frames in stream
            version_type m_stream_version;

            streamref_interface_type m_stream_ref;

            std::string m_last_error_message;
        };

        inline const std::string&
        FrameStream::GetLastError( ) const
        {
            return m_last_error_message;
        }

        inline const MD5Sum&
        FrameStream::GetMD5Sum( ) const
        {
            MD5Sum* result( static_cast< MD5Sum* >( m_md5sumFilter.get( ) ) );
            if ( result == (MD5Sum*)NULL )
            {
                throw std::runtime_error(
                    "No md5sum being calculated for frame" );
            }

            return *result;
        }

        inline void
        FrameStream::frameLibrary( frame_library_type FrameLibrary )
        {
            m_frame_library = FrameLibrary;
        }

        inline void
        FrameStream::libraryRevision( library_revision_type LibraryRevision )
        {
            m_library_revision = LibraryRevision;
        }

        inline void
        FrameStream::setLastError( const std::string& Message )
        {
            m_last_error_message = Message;
        }

        inline const StreamRefInterface&
        FrameStream::streamRef( ) const
        {
            if ( m_stream_ref )
            {
                return *m_stream_ref;
            }
            throw std::invalid_argument( "m_stream_ref is NULL" );
        }

        inline FrameStream::frame_library_type
        FrameStream::FrameLibrary( ) const
        {
            return m_frame_library;
        }

        inline FrameStream::library_revision_type
        FrameStream::LibraryRevision( ) const
        {
            return m_library_revision;
        }

        inline FrameStream::version_type
        FrameStream::Version( ) const
        {
            return streamVersion( );
        }

        inline FrameStream::version_type
        FrameStream::memoryVersion( ) const
        {
            return m_memory_version;
        }

        inline FrameStream::version_type
        FrameStream::streamVersion( ) const
        {
            return m_stream_version;
        }

        inline void
        FrameStream::version_stream( version_type Version )
        {
            m_stream_version = Version;
            if ( m_memory_version == 0 )
            {
                m_memory_version = m_stream_version;
            }
        }

        //===================================================================
        //===================================================================
        class IFrameStream : public FrameStream, protected IStream
        {
        public:
            typedef IStream::buffer_type buffer_type;
            typedef INT_4U               size_type;

            using IStream::GetCheckSumFile;
            using IStream::GetCheckSumFrame;
            using IStream::GetCheckSumObject;
            using IStream::SetCheckSumFrame;
            using IStream::SetCheckSumObject;

            IFrameStream( buffer_type* Stream,
                          INT_2U       Version = FRAME_SPEC_CURRENT );

            IFrameStream( bool         AutoDelete,
                          buffer_type* Stream,
                          INT_2U       Version = FRAME_SPEC_CURRENT );

            virtual void Cleanup( );

            //-----------------------------------------------------------------
            /// \brief Retrieve the current frame
            ///
            /// \return
            ///   If no frames have been read, then the value of ~0 is
            ///   returned, otherwise the value of the current frame is
            ///   returned.
            //-----------------------------------------------------------------
            size_type GetCurrentFrameOffset( ) const;

            virtual const FrHeader& GetFrHeader( ) const;

            const FrTOC* GetTOC( ) const;

            size_type GetNumberOfFrames( ) const;

            FrameSpec::Info::verification_func_type VerificationFunc( ) const;

            object_type Read( );

            object_type ReadNextFrameAsObject( );

            //-----------------------------------------------------------------
            /// \brief Read the detector via the table of contents
            ///
            /// \param[in] Name
            ///     The name of the detector to be read
            ///
            /// \return
            ///     Upon successfully reading the detector, a reference to
            ///     the detector is returned, otherwise an exception is
            ///     is thrown.
            ///
            /// \note
            ///     The caller is responsible to recycle the resources
            ///     incurred from this call.
            //-----------------------------------------------------------------
            object_type ReadDetector( const std::string& Name );

            object_type ReadFrame( bool Decompress = false );

            object_type ReadFrameN( INT_4U FrameIndex,
                                    bool   Decompress = false );

            object_type ReadFrameNSubset( INT_4U FrameIndex,
                                          INT_4U ElementMask );

            //-----------------------------------------------------------------
            /// \brief Read FrStatData at a given postion in the stream
            ///
            /// \param Position
            ///     Offset of the FrStatData in the stream
            //-----------------------------------------------------------------
            IFrameStream::object_type ReadFrStatData( INT_8U Position );

            INT_4U
            ReadFrStatData( const std::string&            NamePattern,
                            const std::string&            DetectorPattern,
                            const LDASTools::AL::GPSTime& StartTime,
                            const LDASTools::AL::GPSTime& EndTime,
                            const INT_4U                  Version,
                            FrStatData::Query&            QueryResults );

            void SetAutoDeleteBuffer( const bool AutoDelete );

            void SetCheckSumFile( const CheckSum::kind_type Type );

            void SetMD5Sum( bool Value );

            void VerifyHeader( Verify& Verifier );

            using IStream::eof;
            using IStream::good;

        protected:
            typedef boost::shared_ptr< FrTOC > toc_type;

            //-----------------------------------------------------------------
            //
            //-----------------------------------------------------------------
            using IStream::Next;

            //-----------------------------------------------------------------
            ///
            //-----------------------------------------------------------------
            virtual ptr_struct_base_type Next( object_type::element_type* Obj );

            //-----------------------------------------------------------------
            // Routines dealing with specific data types
            //-----------------------------------------------------------------
            object_type advanceToFrame( INT_4U Frame );

            object_type readFrameHSubset( INT_4U Frame, INT_4U ElementMask );

            object_type readFrAdcData( INT_4U             Frame,
                                       const std::string& Channel );

            object_type readFrAdcData( INT_4U Frame, INT_4U Channel );

            object_type readFrAdcStruct( INT_4U             Frame,
                                         const std::string& Channel );

            object_type readFrAdcStruct( INT_4U Frame, INT_4U Channel );

            object_type readFrEvent( INT_4U Frame, const std::string& Channel );

            object_type readFrEvent( const std::string&   EventType,
                                     fr_event_offset_type Offset );

            std::unique_ptr< FrEndOfFile > readFrEndOfFile( );

            object_type readFrEventStruct( INT_4U             Frame,
                                           const std::string& Channel );

            object_type readFrProcData( INT_4U             Frame,
                                        const std::string& Channel );

            object_type readFrProcData( INT_4U Frame, INT_4U Channel );

            object_type readFrProcStruct( INT_4U             Frame,
                                          const std::string& Channel );

            object_type readFrProcStruct( INT_4U Frame, INT_4U Channel );

            object_type readFrRawData( INT_4U Frame );

            object_type readFrSerData( INT_4U             Frame,
                                       const std::string& Channel );

            object_type readFrSerStruct( INT_4U             Frame,
                                         const std::string& Channel );

            object_type readFrSimData( INT_4U             Frame,
                                       const std::string& Channel );

            object_type readFrSimStruct( INT_4U             Frame,
                                         const std::string& Channel );

            object_type readFrSimEvent( INT_4U             Frame,
                                        const std::string& Channel );

            object_type readFrSimEvent( const std::string&       SimEventType,
                                        fr_sim_event_offset_type Offset );

            object_type readFrSimEventStruct( INT_4U             Frame,
                                              const std::string& Channel );

            std::unique_ptr< FrTOC >
            readFrTOCHeader( FrEndOfFile::seekTOC_cmn_type Offset );

            object_type readNextFrame( );

            boost::shared_ptr< StreamRefInterface > readStreamRef( );

            void readTOC( );

            virtual void reset( );

            //-----------------------------------------------------------------
            // General reading routines
            //-----------------------------------------------------------------
            //-----------------------------------------------------------------
            /// \brief Read an Object referenced in the stream
            ///
            /// \param StreamRef
            ///     Stream reference information for the requested object.
            //-----------------------------------------------------------------
            object_type readObject( const StreamRefInterface* StreamRef );

            void readRecursive( INT_4U StopOnClassId, bool Decompress = false );

            bool
            removeRecursiveDependant( const StreamRefInterface* StreamRef );

            //-----------------------------------------------------------------
            // Other functions
            //-----------------------------------------------------------------
            virtual void addRecursiveDependant( ptr_struct_base_type Ref );

            void addRecursiveDependant( const StreamRefInterface* StreamRef );

            toc_type getTOC( ) const;

            virtual void pushResolver( resolver_type Resolver );

            void seedTOCInfo( const IFrameStream& Source );

        private:
            friend class Verify;
            struct detector_info_type
            {
                INT_2U m_class;
                INT_4U m_instance;
            };

            typedef std::map< INT_8U, detector_info_type > detector_pos_type;

            boost::shared_ptr< FrHeader > m_file_header;
            toc_type                      m_toc;
            bool                          m_toc_loaded;
            /// state variable for reading frame subset.
            bool m_reading_frame_subset;
            //-----------------------------------------------------------------
            /// Set of references which need to resolved.
            /// Used by recursive reading function.
            //-----------------------------------------------------------------
            std::set< INT_8U > m_to_be_resolved;
            bool               m_log_recursive_dependants;
            //-----------------------------------------------------------------
            /// \brief Current frame index
            //-----------------------------------------------------------------
            INT_4U m_next_frame_index;

            detector_pos_type m_detector_pos;

            //-----------------------------------------------------------------
            //-----------------------------------------------------------------
            void init( );

            //-----------------------------------------------------------------
            /// \brief Load table of contents from stream
            //-----------------------------------------------------------------
            void load_toc( );

            //-----------------------------------------------------------------
            /// \brief Modify an object so it is appropriate for the stream.
            ///
            /// \param[in] Obj
            ///     The object that should be transformed.
            ///
            /// \return
            ///     A pointer to the object appropriately converted.
            ///     If no conversion was necessary, the same pointer is
            ///     returned.
            //-----------------------------------------------------------------
            object_type morph( object_type Obj );

            template < INT_4U ClassType, typename ChannelType >
            object_type read_fr_struct( INT_4U      Frame,
                                        ChannelType Channel,
                                        bool        Recursively );

            template < INT_4U ClassType, typename ChannelType >
            object_type read_indexed_fr_struct( ChannelType Channel,
                                                INT_4U      Index,
                                                bool        Recursively );

            template < INT_4U ClassType, typename ChannelType >
            object_type advance_to_fr_struct( INT_4U      FrameIndex,
                                              ChannelType Channel );

            template < INT_4U ClassType, typename ChannelType >
            object_type advance_to_indexed_fr_struct( ChannelType Channel,
                                                      INT_4U      Index );

            template < INT_4U ClassType, typename ChannelType >
            INT_8U position( const FrTOC*       TOC,
                             INT_4U             Frame,
                             const ChannelType& Channel ) const;

            template < INT_4U ClassType, typename ChannelType >
            INT_8U position_index( const FrTOC*       TOC,
                                   const ChannelType& Channel,
                                   INT_4U             Index ) const;
        };

        inline IFrameStream::object_type
        IFrameStream::ReadFrame( bool Decompress )
        {
            return ReadFrameN( m_next_frame_index, Decompress );
        }

        inline IFrameStream::object_type
        IFrameStream::ReadFrameNSubset( INT_4U FrameIndex, INT_4U ElementMask )
        {
            return readFrameHSubset( FrameIndex, ElementMask );
        }

        inline FrameSpec::Info::verification_func_type
        IFrameStream::VerificationFunc( ) const
        {
            return frameSpecInfo( ).VerificationFunc( );
        }

        inline IFrameStream::size_type
        IFrameStream::GetCurrentFrameOffset( ) const
        {
            if ( m_next_frame_index == 0 )
            {
                return size_type( ~0 );
            }
            return ( m_next_frame_index - 1 );
        }

        inline const FrHeader&
        IFrameStream::GetFrHeader( ) const
        {
            if ( m_file_header.get( ) )
            {
                return *( m_file_header.get( ) );
            }
            std::ostringstream msg;

            msg << "FrHeader has not been initialized yet in this stream";
            throw std::runtime_error( msg.str( ) );
        }

        inline INT_4U
        IFrameStream::GetNumberOfFrames( ) const
        {
            return GetTOC( )->nFrame( );
        }

        inline const FrTOC*
        IFrameStream::GetTOC( ) const
        {
            if ( m_toc_loaded == false )
            {
                const_cast< IFrameStream* >( this )->load_toc( );
            }
            if ( m_toc )
            {
                return m_toc.get( );
            }
            throw std::runtime_error(
                "No Table of Contents object for Stream" );
        }

        inline void
        IFrameStream::SetAutoDeleteBuffer( const bool AutoDelete )
        {
            setAutoDeleteBuffer( AutoDelete );
        }

        inline void
        IFrameStream::SetCheckSumFile( const CheckSum::kind_type Type )
        {
            CheckSumFilter* fcs = GetCheckSumFile( );
            if ( fcs && ( fcs->Type( ) == Type ) )
            {
                return;
            }
            IStream::SetCheckSumFile( Type );
            fcs = GetCheckSumFile( );
            if ( fcs )
            {
                if ( cmn_streamsize_type( tellg( ) ) !=
                     m_file_header->Bytes( ) )
                {
                    std::ostringstream msg;

                    msg << "Unable to set file checksum: position error"
                        << " ( file position: "
                        << cmn_streamsize_type( tellg( ) )
                        << " header size: " << m_file_header->Bytes( ) << " )";
                    throw std::logic_error( msg.str( ) );
                }
                m_file_header->Filter( *fcs );
            }
        }

        inline IFrameStream::object_type
        IFrameStream::ReadNextFrameAsObject( )
        {
            return readNextFrame( );
        }

        inline void
        IFrameStream::SetMD5Sum( bool Value )
        {
            if ( m_md5sumFilter.get( ) )
            {
                rdbuf( )->FilterRemove( m_md5sumFilter.get( ) );
            }
            if ( Value )
            {
                if ( m_md5sumFilter.get( ) )
                {
                    m_md5sumFilter->Reset( );
                }
                else
                {
                    m_md5sumFilter.reset( new MD5SumFilter( ) );
                }
                rdbuf( )->FilterAdd( m_md5sumFilter.get( ) );
            }
            else
            {
                m_md5sumFilter.reset( (MD5SumFilter*)NULL );
            }
        }

        inline IFrameStream::toc_type
        IFrameStream::getTOC( ) const
        {
            return m_toc;
        }

        inline void
        IFrameStream::seedTOCInfo( const IFrameStream& Source )
        {
            m_toc = Source.m_toc;
            m_toc_loaded = Source.m_toc_loaded;
            m_stream_id_to_fsi_id = Source.m_stream_id_to_fsi_id;
        }

        //===================================================================
        //===================================================================
        class OFrameStream : public FrameStream, protected OStream
        {
        public:
            typedef OStream::buffer_type buffer_type;
            typedef INT_4U               chkSum_type;

            using OStream::good;
            using OStream::rdbuf;
            using OStream::SetCheckSumFile;

            OFrameStream( buffer_type* Buffer,
                          INT_2U       Version = FRAME_SPEC_CURRENT );

            OFrameStream( bool         AutoDelete,
                          buffer_type* Buffer,
                          INT_2U       Version = FRAME_SPEC_CURRENT );

            ~OFrameStream( );

            void Close( );

            void DisableTOC( );

            virtual INT_4U GetNumberOfFrames( ) const;

            virtual INT_8U GetTOCOffset( ) const;

            //-----------------------------------------------------------------
            /// \brief Establish if the buffer is to be released with the Stream
            ///
            /// \param[in] AutoDelete
            ///     If true, then the buffer will be released with the
            ///     destruction of this instance.
            ///     If false, then the buffer will exist even after the
            ///     destruction of this instance.
            //-----------------------------------------------------------------
            void SetAutoDeleteBuffer( const bool AutoDelete );

            void SetMD5Sum( bool Value );

            void Write( object_type Obj );

            /// \brief Write Frame data to the stream
            void WriteFrame(
                object_type FrameObject,
                chkSum_type FrameChecksumType = Common::CheckSum::NONE );

            /// \brief Write Frame data to the stream
            void WriteFrame( object_type FrameObject,
                             INT_2U      CompressionScheme,
                             INT_2U      CompressionLevel,
                             chkSum_type FrameChecksumType = CheckSum::NONE );

            void WriteFrStatData( object_type FrameObject );

        private:
            typedef boost::shared_ptr< FrDetector > fr_detector_type;
            typedef boost::shared_ptr< FrStatData > fr_stat_data_type;

            struct detector_cmp
            {
                bool operator( )( fr_detector_type S1,
                                  fr_detector_type S2 ) const;
            };

            typedef std::set< INT_2U >             defined_container_type;
            typedef std::list< fr_stat_data_type > fr_stat_list_type;
            typedef std::
                map< fr_detector_type, fr_stat_list_type, detector_cmp >
                    fr_stat_container_type;

            boost::shared_ptr< FrTOC > m_toc;
            INT_8U                     m_toc_location;
            INT_4U                     m_frame_count;
            defined_container_type     m_defined;
            fr_stat_container_type     m_fr_stats;
            bool                       m_has_header;

            void init( );

            void write_stream_objects( );
        };

        inline void
        OFrameStream::DisableTOC( )
        {
            m_toc.reset( );
        }

        inline INT_4U
        OFrameStream::GetNumberOfFrames( ) const
        {
            return m_frame_count;
        }

        inline INT_8U
        OFrameStream::GetTOCOffset( ) const
        {
            return m_toc_location;
        }

        inline void
        OFrameStream::SetAutoDeleteBuffer( const bool AutoDelete )
        {
            setAutoDeleteBuffer( AutoDelete );
        }

        inline void
        OFrameStream::SetMD5Sum( bool Value )
        {
            if ( m_md5sumFilter.get( ) )
            {
                rdbuf( )->FilterRemove( m_md5sumFilter.get( ) );
            }
            if ( Value )
            {
                if ( m_md5sumFilter.get( ) )
                {
                    m_md5sumFilter->Reset( );
                }
                else
                {
                    m_md5sumFilter.reset( new MD5SumFilter( ) );
                }
                rdbuf( )->FilterAdd( m_md5sumFilter.get( ) );
            }
            else
            {
                m_md5sumFilter.reset( (MD5SumFilter*)NULL );
            }
        }

    } // namespace Common
} // namespace FrameCPP

#endif /* FRAMECPP__COMMON__FrameStream_HH */
