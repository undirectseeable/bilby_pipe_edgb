//
// LDASTools AL - A library collection to provide an abstraction layer
//
// Copyright (C) 2018 California Institute of Technology
//
// LDASTools AL is free software; you may redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 (GPLv2) of the
// License or at your discretion, any later version.
//
// LDASTools AL is distributed in the hope that it will be useful, but
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

#ifndef GENERAL__LOG_HH
#define GENERAL__LOG_HH

#include <queue>
#include <fstream>
#include <sstream>

#include <boost/shared_ptr.hpp>

#include "ldastoolsal/fstream.hh"
#include "ldastoolsal/gpstime.hh"
#include "ldastoolsal/mutexlock.hh"
#include "ldastoolsal/Thread.hh"
#include "ldastoolsal/unordered_map.hh"

namespace LDASTools
{
    namespace AL
    {
        class LogCB;

        //-------------------------------------------------------------------
        /// \brief Logging class
        ///
        /// This is a very simple logging class that is thread safe.
        /// It does support seperate debugging levels for each group.
        //-------------------------------------------------------------------
        class Log : public LDASTools::AL::Thread
        {
        public:
            //-----------------------------------------------------------------
            /// \brief Class to handle stream callbacks
            ///
            /// This abstaction class defines the interface for any class
            /// that is to be used as a callback on a stream.
            //-----------------------------------------------------------------
            class StreamCBInterface
            {
            public:
                //---------------------------------------------------------------
                // \brief Destructor
                //---------------------------------------------------------------
                virtual ~StreamCBInterface( );
                //---------------------------------------------------------------
                /// \brief Action to be performed when the stream is closed
                //---------------------------------------------------------------
                virtual void OnClose( ) = 0;

                //---------------------------------------------------------------
                /// \brief Action to be performed when the stream is opened
                //---------------------------------------------------------------
                virtual void OnOpen( ) = 0;
            };

            //-----------------------------------------------------------------
            /// \brief Class to handle streaming of messages
            ///
            /// This is an pure abstract class which describes the interface
            /// that needs to be created by derived classes.
            //-----------------------------------------------------------------
            class StreamInterface
            {
            public:
                typedef boost::shared_ptr< StreamCBInterface > callback_type;
                //---------------------------------------------------------------
                /// \brief Constructor
                //---------------------------------------------------------------
                StreamInterface( );

                //---------------------------------------------------------------
                /// \brief Destructor
                //---------------------------------------------------------------
                virtual ~StreamInterface( );

                //---------------------------------------------------------------
                /// \brief Establish callback
                //---------------------------------------------------------------
                void Callback( callback_type Callback );

                //---------------------------------------------------------------
                /// \brief How to close the stream
                //---------------------------------------------------------------
                virtual void Close( ) = 0;

                //---------------------------------------------------------------
                /// \brief Resturn the open state of the stream
                ///
                /// \return
                ///     If the stream is open and writable, then return true.
                ///     Otherwise, false.
                //---------------------------------------------------------------
                virtual bool IsOpen( ) const = 0;

                //---------------------------------------------------------------
                /// \brief How to open the stream
                //---------------------------------------------------------------
                virtual void Open( ) = 0;

                //---------------------------------------------------------------
                /// \brief How to open the stream
                ///
                /// \param[in] Message
                ///     The message to send to the output stream.
                //---------------------------------------------------------------
                virtual void WriteMessage( const std::string& Message ) = 0;

                //---------------------------------------------------------------
                /// \brief Output to the stream
                //---------------------------------------------------------------
                template < typename T >
                std::ostream&
                operator<<( T a )
                {
                    std::ostream& s( stream( ) );
                    std::         operator<<( s, a );
                    return s;
                }

            protected:
                void onClose( );

                void onOpen( );

                //---------------------------------------------------------------
                /// \brief Gain access to the stream
                //---------------------------------------------------------------
                virtual std::ostream& stream( ) = 0;

            private:
                //---------------------------------------------------------------
                /// \brief Callback storage
                ///
                /// If this is set, then this instance is called to handle
                /// additional actions that should happen when the stream is
                /// opened or closed.
                //---------------------------------------------------------------
                callback_type callback;
            };

            //-----------------------------------------------------------------
            //
            //-----------------------------------------------------------------
            class StreamStdErr : public StreamInterface
            {
            public:
                //---------------------------------------------------------------
                /// \brief Constructor
                //---------------------------------------------------------------
                StreamStdErr( );

                //---------------------------------------------------------------
                /// \brief Destructor
                //---------------------------------------------------------------
                virtual ~StreamStdErr( );

                //---------------------------------------------------------------
                /// \brief How to close the stream
                //---------------------------------------------------------------
                virtual void Close( );

                //---------------------------------------------------------------
                /// \brief Return the open state of the stream
                ///
                /// \return
                ///     If the stream is open and writable, then return true.
                ///     Otherwise, false.
                //---------------------------------------------------------------
                virtual bool IsOpen( ) const;

                //---------------------------------------------------------------
                /// \brief How to open the stream
                //---------------------------------------------------------------
                virtual void Open( );

                //---------------------------------------------------------------
                /// \brief How to open the stream
                ///
                /// \param[in] Message
                ///     The message to send to the output stream.
                //---------------------------------------------------------------
                virtual void WriteMessage( const std::string& Message );

            protected:
                //---------------------------------------------------------------
                /// \brief Gain access to the stream
                //---------------------------------------------------------------
                virtual std::ostream& stream( );

                //---------------------------------------------------------------
                /// \brief Tracks if a call to onOpen has been made.
                //---------------------------------------------------------------
                bool on_open_called;
            };

            //-----------------------------------------------------------------
            //
            //-----------------------------------------------------------------
            class StreamFile : public StreamInterface, protected std::ofstream
            {
            public:
                //---------------------------------------------------------------
                /// \brief Constructor
                //---------------------------------------------------------------
                StreamFile( );

                //---------------------------------------------------------------
                /// \brief Destructor
                //---------------------------------------------------------------
                virtual ~StreamFile( );

                void        ArchiveDirectory( const std::string& Value );
                std::string ArchiveDirectory( ) const;
                void        FilenameExtension( const std::string& Value );
                std::string FilenameExtension( ) const;
                void        FilenamePattern( const std::string& Value );
                std::string FilenamePattern( ) const;

                //---------------------------------------------------------------
                /// \brief How to close the stream
                //---------------------------------------------------------------
                virtual void Close( );

                //---------------------------------------------------------------
                /// \brief Return the open state of the stream
                ///
                /// \return
                ///     If the stream is open and writable, then return true.
                ///     Otherwise, false.
                //---------------------------------------------------------------
                virtual bool IsOpen( ) const;

                //---------------------------------------------------------------
                /// \brief How to open the stream
                //---------------------------------------------------------------
                virtual void Open( );

                //---------------------------------------------------------------
                /// \brief How to open the stream
                ///
                /// \param[in] Message
                ///     The message to send to the output stream.
                //---------------------------------------------------------------
                virtual void WriteMessage( const std::string& Message );

            protected:
                //---------------------------------------------------------------
                // \brief Obtain the archive log filename
                //---------------------------------------------------------------
                virtual std::string archive_filename( ) const;

                //---------------------------------------------------------------
                // \brief Number of entries currently written to the log file
                //---------------------------------------------------------------
                INT_4U entries( ) const;

                //---------------------------------------------------------------
                // \brief Number of entries to trigger a log rotation
                //---------------------------------------------------------------
                virtual INT_4U entriesMax( ) const;

                //---------------------------------------------------------------
                // \brief Obtain the log filename
                //---------------------------------------------------------------
                virtual std::string filename( ) const;

                //---------------------------------------------------------------
                /// \brief Rotate log files
                //---------------------------------------------------------------
                virtual void rotate( );

                //---------------------------------------------------------------
                /// \brief Gain access to the stream
                //---------------------------------------------------------------
                virtual std::ostream& stream( );

            private:
                std::string archive_directory;
                std::string filename_extension;
                std::string filename_pattern;
                INT_4U      rotate_bytes;
                INT_4U      rotate_bytes_trigger;
                INT_4U      rotate_entries;
                INT_4U      rotate_entries_trigger;
            };

            //-----------------------------------------------------------------
            /// \brief Type for group.
            ///
            /// This is the data type used when referencing parameters
            /// representing the group associated with the message.
            //-----------------------------------------------------------------
            typedef int group_type;

            //-------------------------------------------------------------------
            /// The stream_type is used to represent the output stream class
            /// used to log the messages.
            //-------------------------------------------------------------------
            typedef boost::shared_ptr< StreamInterface > stream_type;
            typedef boost::shared_ptr< StreamFile >      stream_file_type;

            //-----------------------------------------------------------------
            /// \brief Type for level.
            ///
            /// This is the data type used when referencing parameters
            /// representing the level of message.
            //-----------------------------------------------------------------
            typedef int level_type;

            //-----------------------------------------------------------------
            /// \brief Constructor
            ///
            /// \param[in] BaseName
            ///     The base name to be used for creation of the log file.
            ///
            /// \return
            ///     An instance of this object.
            //-----------------------------------------------------------------
            Log( const std::string& BaseName );

            //-----------------------------------------------------------------
            /// \brief Destructor
            //-----------------------------------------------------------------
            ~Log( );

            //-----------------------------------------------------------------
            /// \brief Send a message to the log.
            ///
            /// \param[in] Group
            ///     The group associated with the message.
            /// \param[in] Level
            ///     The level associated with the message.
            /// \param[in] Message
            ///     The text of the message.
            //-----------------------------------------------------------------
            void Message( const group_type   Group,
                          const level_type   Level,
                          const std::string& Message );

            //-----------------------------------------------------------------
            /// \brief Set the stream to use for output
            ///
            /// \param[in] Output
            ///     Stream to use for output
            //-----------------------------------------------------------------
            void Stream( stream_type Output );

            stream_type Stream( );

            void Sync( ) const;
            //-----------------------------------------------------------------
            /// \brief Establish logging level for a given group
            ///
            /// \param[in] Group
            ///     The group for which the logging level is to be modified.
            /// \param[in] Level
            ///     The level of debugging to output.
            //-----------------------------------------------------------------
            void Verbosity( const group_type Group, const level_type Level );

            //-----------------------------------------------------------------
            /// \brief Check if the message will be logged.
            ///
            /// \param[in] Group
            ///     The group for which to check.
            /// \param[in] Level
            ///     The level to check.
            //-----------------------------------------------------------------
            bool VerbosityCheck( const group_type Group,
                                 const level_type Level ) const;

            //-----------------------------------------------------------------
            /// \brief Specify the maximum number of entries per file
            ///
            /// \param[in] Value
            ///     The number of entries.
            ///
            //-----------------------------------------------------------------
            void EntriesMax( int Value );

        protected:
            //-----------------------------------------------------------------
            /// \brief Information about a log message
            //-----------------------------------------------------------------
            struct message_queue_entry_type
            {
                //---------------------------------------------------------------
                /// Body of the message.
                //---------------------------------------------------------------
                std::string s_message;
                //---------------------------------------------------------------
                /// Time when the message was generated.
                //---------------------------------------------------------------
                GPSTime s_timestamp;
            };

            //-----------------------------------------------------------------
            /// \brief Hook to do additional action when the stream is closed
            //-----------------------------------------------------------------
            virtual void onStreamClose( );

            //-----------------------------------------------------------------
            /// \brief Hook to do additional action when the stream is opened
            //-----------------------------------------------------------------
            virtual void onStreamOpen( );

            //-----------------------------------------------------------------
            /// \brief Flush the output queue.
            //-----------------------------------------------------------------
            void purge( );

            //-----------------------------------------------------------------
            /// \brief Active output stream.
            //-----------------------------------------------------------------
            stream_type m_stream;

            bool stream_delete_on_destruct;

        private:
            friend class LogCB;

            //-----------------------------------------------------------------
            /// The message_queue_type is used to represent the storage class
            /// used for the message queue.
            //-----------------------------------------------------------------
            typedef std::queue< message_queue_entry_type > message_queue_type;

            //-----------------------------------------------------------------
            /// \brief Container type for managing verbosity levels.
            //-----------------------------------------------------------------
            typedef LDASTools::AL::unordered_map< group_type, level_type >
                verbose_map_type;

            //-----------------------------------------------------------------
            /// The base name for the log file.
            /// It is used as the pattern for log rotation.
            //-----------------------------------------------------------------
            const std::string m_base_name;

            //-----------------------------------------------------------------
            /// Holder for the maximum number of entries that should be
            /// written to the stream before rotating.
            /// If the value is zero, then it is unlimited.
            //-----------------------------------------------------------------
            int m_entries_max;

            //-----------------------------------------------------------------
            /// \brief Storage for pending message.
            ///
            /// This storage holds the list of pending mesages.
            //-----------------------------------------------------------------
            message_queue_type m_message_queue;

            //-----------------------------------------------------------------
            /// \brief Storage for output message.
            ///
            /// This storage holds the list of pending output mesages.
            //-----------------------------------------------------------------
            message_queue_type m_output_queue;

            //-----------------------------------------------------------------
            /// \brief Protect integrity of the message queue
            ///
            /// The holder of this resouce has the authority to modify
            /// the message queue..
            //-----------------------------------------------------------------
            mutable MutexLock::baton_type m_message_baton;

            //-----------------------------------------------------------------
            /// \brief Keep track of the verbosity of each group
            //-----------------------------------------------------------------
            mutable verbose_map_type m_verbosity;

            //-----------------------------------------------------------------
            /// \brief Output contents of the message queue to the output
            /// stream.
            //-----------------------------------------------------------------
            virtual void action( );

            //-----------------------------------------------------------------
            /// \brief Flush all remaining messages to the log file
            //-----------------------------------------------------------------
            void flush( bool EveryThing = false );

            //-----------------------------------------------------------------
            /// \brief Write message to the output stream
            ///
            /// \param[in] MessageInfo
            ///     The content to be written to the log.
            //-----------------------------------------------------------------
            void write_message( const message_queue_entry_type& MessageInfo );
        };

        //-------------------------------------------------------------------
        //-------------------------------------------------------------------
        inline void
        Log::StreamInterface::Callback( callback_type CB )
        {
            callback = CB;
        }

        //-------------------------------------------------------------------
        /// The Value specified is the maximum number of lines that a file
        /// should have before triggering a log rotation request.
        //-------------------------------------------------------------------
        inline void
        Log::EntriesMax( int Value )
        {
            m_entries_max = Value;
        }

        inline void
        Log::Verbosity( const group_type Group, const level_type Level )
        {
            MutexLock lock( m_message_baton, __FILE__, __LINE__ );

            m_verbosity[ Group ] = Level;
        }

        inline bool
        Log::VerbosityCheck( const group_type Group,
                             const level_type Level ) const
        {
            MutexLock lock( m_message_baton, __FILE__, __LINE__ );

            verbose_map_type::mapped_type e( 0 );
            verbose_map_type::iterator    i( m_verbosity.find( Group ) );
            if ( i == m_verbosity.end( ) )
            {
                m_verbosity[ Group ] = 0;
            }
            else
            {
                e = i->second;
            }
            return ( Level <= e );
        }

        inline void
        Log::StreamFile::ArchiveDirectory( const std::string& Value )
        {
            archive_directory = Value;
        }

        inline std::string
        Log::StreamFile::ArchiveDirectory( ) const
        {
            return archive_directory;
        }

        inline void
        Log::StreamFile::FilenameExtension( const std::string& Value )
        {
            filename_extension = Value;
        }

        inline std::string
        Log::StreamFile::FilenameExtension( ) const
        {
            return filename_extension;
        }

        inline void
        Log::StreamFile::FilenamePattern( const std::string& Value )
        {
            filename_pattern = Value;
        }

        inline std::string
        Log::StreamFile::FilenamePattern( ) const
        {
            return filename_pattern;
        }

        inline INT_4U
        Log::StreamFile::entries( ) const
        {
            return rotate_entries;
        }
    } // namespace AL
} // namespace LDASTools

#endif /* GENERAL__LOG_HH */
