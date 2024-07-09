/* -*- mode: C++ ; c-basic-offset: 2; indent-tabs-mode: nil -*- */

/*
 * High-level NDS client C++ library
 *
 * Copyright (C) 2015  Edward Maros <ed.maros@ligo.org>
 *
 * This work is derived from the C NDS clientlibrary created by Leo Singer
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#ifndef SWIG__COMMON__NDS_CONNECTION_HH
#define SWIG__COMMON__NDS_CONNECTION_HH

/**
 * \if DEVELOPER_SECTION
 * \page NDSClientBindings  NDS Client Bindings
 * \else
 * \mainpage NDS Client Bindings
 * \endif
 * \section Introduction
 * The %NDS Client bindings are a set of C/C++ libraries that provide access to
 * the LIGO project %NDS servers.
 * The libraries provide a uniform interface to both NDS1 and NDS2 servers.  In
 * addition to the C/C++ libraries a series
 * of modules are provided to allow Java, MATLAB, Octave, and Python programs to
 * interface with the %NDS systems.
 *
 * \section Main Components
 * The main components of the library are the \link NDS::connection connection
 * \endlink, \link NDS::buffer buffer \endlink objects, and \link NDS::channel
 * channel \endlink objects.
 *
 * \subsection Connections Connections
 * The libraries are connection oriented.  Each \link NDS::connection connection
 * \endlink object connects to a single %NDS server and allows the user
 * to query for available channels and retreive data.  This is the basic class
 * you use to interact with the %NDS server.  All requests for data are done
 * through
 * a connection object.
 *
 * \subsection Channels Channels
 * The \link NDS::channel channel \endlink class represents a stored channel.
 * It provides access to the metadata, such as name, rate, frame type, and data
 * type.
 * The channel does not give access to the data.  For that a buffer class is
 * used.
 *
 * \subsection Buffers Buffers
 * The \link NDS::buffer buffer \endlink class is the combination of channels
 * and data.  When you make requests for data to a connection you recieve a
 * series of buffers.
 *
 * \subsection Using Using the NDS client
 * Each of the C++ classes are broken out into their own header files.  However
 * there is a combined header file that should be included by the application.
 \code
 #include "nds.hh"
 \endcode
 *
 * \section NDS1vs2 Differences between NDS1 and NDS2
 * NDS1 has no concept of channel history.  It maintains one channel list, the
 * current channel list.  It cannot read historical data if channels have
 * changed name or rate.
 * NDS1 is only available in the LIGO control rooms.  It is not exported to the
 * outside world and is part of the LIGO control systems.
 *
 * NDS2 Contains the full history of LIGO data.  It tracks each name and rate
 * change.  Channels may have several co-existing versions, and may have long
 * stretches where
 * they do not exist.  When accessing data, users should keep in mind that
 * recent data is often cached on disk and as such can be read with relatively
 * low latency.  However
 * data that is not cached on disk must be pulled from tape archives and will
 * have a high latency for the request.
 *
 * \subsection ChannelNames Channel names in NDS2
 * With the full history of channels in NDS2 a name may map to multiple
 * channels.  The NDS2 server will attempt to extrapolate the channel you ask
 * for based
 * on the name and timespans given.  However a user may specify more information
 * in a channel name in order to force the NDS2 server to select the desired
 * channel.
 * The user must specify a base name, and may also specify channel types, and
 * rates.
 *
 * For example the H1 strain data is in H1:GDS-CALIB_STRAIN.  However there are
 * multiple sources of the data.  The real time online data and the archived
 * reduced type.
 * You can fully qualify the name by including frame type and rate information.
 * So you could qualify the name as H1:GDS-CALIB_STRAIN,reduced,16384 or
 * H1:GDS-CALIB_STRAIN,reduce to
 * denote archived strain data.  To specify the online, real time stream of
 * strain you could use H1:GDS-CALIB_STRAIN,online,16384 or
 * H1:GDS-CALIB_STRAIN,online.
 */

#include <memory>
#include <stdexcept>
#include <string>
#include <ostream>

#include "nds_export.hh"
#include "nds_buffer.hh"
#include "nds_channel.hh"
#include "nds_data_iterator.hh"
#include "nds_availability.hh"
#include "nds_epoch.hh"

namespace NDS
{
    namespace detail
    {
        struct conn_p_type;
        class parameter_block;
        class parameter_accessor;
    } // namespace detail
    inline namespace abi_0
    {
        class parameters;

        /// \brief A simple range for sample rates.
        struct frequency_range
        {
            NDS::channel::sample_rate_type
                minimum; /// The minimum frequency in this range
            NDS::channel::sample_rate_type
                maximum; /// The maximum frequency in this range

            frequency_range( )
                : minimum( NDS::channel::MIN_SAMPLE_RATE ),
                  maximum( NDS::channel::MAX_SAMPLE_RATE )
            {
            }
            frequency_range( NDS::channel::sample_rate_type Min,
                             NDS::channel::sample_rate_type Max )
                : minimum( Min ), maximum( Max )
            {
            }
            frequency_range( const frequency_range& other ) = default;
            frequency_range&
            operator=( const frequency_range& other ) = default;
        };

        /**
         * \brief A predicate object to be used in limiting the number of
         * channels returned when searching for channels.
         * \details This object holds the various conditions that the
         * nds2_client library will use when searching channels.
         * The conditions (NDS epoch, name globbing, sample rates, channel type,
         * data type,
         * ...) are all specified in a uniform
         * manner.  Each condition should have a distinct type.
         */
        class channel_predicate_object
        {
        public:
            typedef std::vector< NDS::channel::channel_type > channel_type_list;
            typedef std::vector< NDS::channel::data_type >    data_type_list;

            channel_predicate_object( )
                : epoch_( "", 0, NDS::buffer::GPS_INF ), glob_( ),
                  channel_types_( ), data_types_( ), sample_rates_( )
            {
            }

            channel_predicate_object( const channel_predicate_object& other ) =
                default;

            channel_predicate_object( channel_predicate_object&& other ) =
                default;

            channel_predicate_object&
            operator=( const channel_predicate_object& other ) = default;

            channel_predicate_object&
            operator=( channel_predicate_object&& other ) = default;

            /// \brief Return the channel name glob (defaults to "*")
            std::string
            glob( ) const
            {
                return ( glob_.empty( ) ? "*" : glob_ );
            }

            /// \brief return a container of distinct channel types that are to
            /// be matched
            /// (defaults to an expansion of NDS::channel::DEFAULT_CHANNEL_MASK)
            const channel_type_list
            channel_types( ) const
            {

                if ( channel_types_.empty( ) )
                {
                    channel_type_list result{ all_channel_types };
                    return result;
                }
                return channel_types_;
            }

            /// \brief return a compact mask of the channel types selected.
            /// this is mainly provided for the SWIG language bindings.
            NDS::channel::channel_type
            channel_type_mask( ) const
            {
                if ( channel_types_.empty( ) )
                {
                    return NDS::channel::DEFAULT_CHANNEL_MASK;
                }
                NDS::channel::channel_type result;
                for ( const NDS::channel::channel_type val : channel_types_ )
                {
                    result = ( NDS::channel::channel_type )( result | val );
                }
                return result;
            }

            /// \brief return a container of distinct data types that are to be
            /// matched
            /// (defaults to an expansion of NDS::channel::DEFAULT_DATA_MASK)
            const data_type_list
            data_types( ) const
            {
                if ( data_types_.empty( ) )
                {
                    data_type_list result{ all_data_types };
                    return result;
                }
                return data_types_;
            }

            /// \brief return a compact mask of the data types selected.
            /// this is mainly provided for the SWIG language bindings.
            NDS::channel::data_type
            data_type_mask( ) const
            {
                if ( data_types_.empty( ) )
                {
                    return NDS::channel::DEFAULT_DATA_MASK;
                }
                NDS::channel::data_type result;
                for ( const NDS::channel::data_type val : data_types_ )
                {
                    result = ( NDS::channel::data_type )( result | val );
                }
                return result;
            }

            /// \brief return the range of sample rates that are to be allowed
            /// in the query.
            /// defaults to (NDS::channel::MIN_SAMPLE_RATE,
            /// NDS::channel::MAX_SAMPLE_RATE)
            const frequency_range&
            sample_rates( ) const
            {
                return sample_rates_;
            }

            /// \brief return the minimum sample rate to be selected.
            /// This is also available through the sample_rates method.
            NDS::channel::sample_rate_type
            min_sample_rate( ) const
            {
                return sample_rates_.minimum;
            }

            /// \brief return the maximum sample rate to be selected.
            /// This is also available through the sample_rates method.
            NDS::channel::sample_rate_type
            max_sample_rate( ) const
            {
                return sample_rates_.maximum;
            }

            /// \brief return the timespan/epoch that should constrain the query
            /// defaults to [0, NDS::buffer::GPS_INF)
            const epoch&
            time_span( ) const
            {
                return epoch_;
            }

            /// \brief Return the gps start time that constrains this query.
            /// Note this is available via the time_span method.
            NDS::buffer::gps_second_type
            gps_start( ) const
            {
                return epoch_.gps_start;
            }

            /// \brief Return the gps stop time that constrains this query.
            /// Note this is available via the time_span method.
            NDS::buffer::gps_second_type
            gps_stop( ) const
            {
                return epoch_.gps_stop;
            }

            /**
             * \brief Set the glob string used in channel matching
             * @param val The glob string to match with
             * @return This object
             */
            channel_predicate_object&
            set( std::string val )
            {
                glob_ = std::move( val );
                return *this;
            }

            /**
             * @brief Set the glob string to match on
             * @param val
             * @note this calls set(string)
             */
            void
            set_glob( std::string val )
            {
                set( val );
            }

            /**
             * \brief Set a channel type to search for.
             * @param val The channel type to search for.
             * @return This object
             * @note This may be called multiple times, each additional type
             * expands the search space
             */
            channel_predicate_object&
            set( NDS::channel::channel_type val )
            {
                {
                    for ( auto entry : all_channel_types )
                        if ( (int)entry | (int)val )
                        {
                            channel_types_.push_back( val );
                        }
                }
                return *this;
            }

            /**
             * @brief Set the channel type mask
             * @param val
             * @note this calls set(channel_type)
             */
            void
            set_channel_type_mask( NDS::channel::channel_type val )
            {
                set( val );
            }

            /**
             * \brief Set a data type to search for.
             * @param val The data type to search for.
             * @return This object
             * @note This may be called multiple times, each additional type
             * expands the search space
             */
            channel_predicate_object&
            set( NDS::channel::data_type val )
            {
                for ( auto entry : all_data_types )
                {
                    if ( (int)entry | (int)val )
                    {
                        data_types_.push_back( val );
                    }
                }
                return *this;
            }

            /**
             * @brief Set the data type mask
             * @param val
             * @note this calls set(data_type)
             */
            void
            set_data_type_mask( NDS::channel::data_type val )
            {
                set( val );
            }

            /**
             * Set the sample rate rate to search for
             * @param val The sample rate range
             * @return This object
             */
            channel_predicate_object&
            set( frequency_range val )
            {
                sample_rates_ = val;
                return *this;
            }
            /**
             * @brief Set the [min, max) frequency range that limits this query
             * @param min_sample_rate The minimal sample rate
             * @param max_sample_rate The maximum sample rate
             * @note this calls set(frequency_range)
             */
            void
            set_frequency_range(
                NDS::channel::sample_rate_type min_sample_rate,
                NDS::channel::sample_rate_type max_sample_rate )
            {
                frequency_range range( min_sample_rate, max_sample_rate );
                set( range );
            }
            /**
             * Set the epoch/time span for the predicate
             * @param val A NDS::epoch representing the timespan
             * @return This object
             */
            channel_predicate_object&
            set( epoch val )
            {
                epoch_ = val;
                return *this;
            }
            /**
             * @brief Set the [gps_start, gps_stop) time range that limits this
             * query
             * @param gps_start Start time in GPS Seconds
             * @param gps_stop End time in GPS Seconds exclusive.
             * @note this calls set(epoch)
             */
            void
            set_timespan( NDS::buffer::gps_second_type gps_start,
                          NDS::buffer::gps_second_type gps_stop )
            {
                NDS::epoch e( "", gps_start, gps_stop );
                set( e );
            }

        private:
            DLL_EXPORT const static data_type_list    all_data_types;
            DLL_EXPORT const static channel_type_list all_channel_types;

            epoch             epoch_;
            std::string       glob_;
            channel_type_list channel_types_;
            data_type_list    data_types_;
            frequency_range   sample_rates_;
        };

        inline void
        build_channel_predicate( channel_predicate_object& pred )
        {
        }

        template < typename T >
        void
        build_channel_predicate( channel_predicate_object& pred, T val )
        {
            pred.set( val );
        }

        template < typename T, typename... Args >
        void
        build_channel_predicate( channel_predicate_object& pred,
                                 T                         val,
                                 Args... args )
        {
            pred.set( val );
            build_channel_predicate( pred, args... );
        }

        /**
         * Create a ChannelPredicate object initialized with the parameters to
         * this call.
         * @tparam Args The types of args
         * @param args arguments predicate object.
         * @return A ChannelPredicate object which has been initialized with the
         * search parameters specified.
         * @note Each argument passed to this function is used to set a
         * constraint in a ChannelPredicate object.
         */
        template < typename... Args >
        channel_predicate_object
        channel_predicate( Args... args )
        {
            channel_predicate_object pred;
            build_channel_predicate( pred, args... );
            return pred;
        }

        /**
         * \brief A connection to the NDS/NDS2 server
         * \details The connection object is used to interact with the NDS (v1
         * or
         * v2) servers to retrieve
         *          data and channel lists.
         *          Connnection objects have a few main categories of methods:
         *          1. Data retreival (fetch and iterate)
         *          2. Channel listing and counting (find_channels and
         * count_channels)
         *          3. Channel availability checking (get_availability)
         *
         * \headerfile nds.hh nds.hh
         */
        class connection
        {
        public:
            /**
             * \brief Base class for NDS errors
             */
            class error : public std::runtime_error
            {
            public:
                DLL_EXPORT
                error( const std::string& What, int ErrNo = 0 );
            };

            /**
             * \brief Signal that the connection has already been closed.
             */
            class already_closed_error : public error
            {
            public:
                DLL_EXPORT
                already_closed_error( );
            };

            /**
             * \brief Signals that a minute trend has been requested but the
             * start/stop times are not divisible by 60.
             */
            class minute_trend_error : public error
            {
            public:
                DLL_EXPORT
                minute_trend_error( );
            };

            /**
             * \brief A transfer is already in progress
             */
            class transfer_busy_error : public error
            {
            public:
                DLL_EXPORT
                transfer_busy_error( );
            };

            /**
             * \brief An unexpected channel or data was received
             */
            class unexpected_channels_received_error : public error
            {
            public:
                DLL_EXPORT
                unexpected_channels_received_error( );
            };

            /**
             * \brief an error state was returned by the NDS server
             */
            class daq_error : public error
            {
            public:
                DLL_EXPORT
                explicit daq_error( int daq_code );

                DLL_EXPORT
                daq_error( int                daq_code,
                           const std::string& additional_information );

                DLL_EXPORT
                daq_error( int daq_code, const char* additional_information );

                DLL_EXPORT
                inline int
                DAQCode( ) const
                {
                    return error_code;
                }

            private:
                int index;
                int error_code;

                static int counter_;

                static std::string format( int         DAQCode,
                                           const char* extra = nullptr );
            };

            /**
             * \brief Connection constants
             */
            typedef enum
            {
                PROTOCOL_INVALID = -1, ///< Unknown or invalid connection
                PROTOCOL_ONE = 1, ///< Connect with NDS1 protocol
                PROTOCOL_TWO = 2, ///< Connect with NDS2 protocol
                PROTOCOL_TRY = 3 ///< Autodetect server protocol
            } protocol_type;

            typedef std::string host_type; ///< Host name type
            typedef int         port_type; ///< Host port number type
            typedef size_t      count_type; ///< Generic count time

            /**
             * \brief A list of channel names
             */
            typedef channel::channel_names_type channel_names_type;
            typedef std::vector< std::string >  parameters_type;

            static const port_type DEFAULT_PORT =
                31200; ///< Default NDS2 port number

            /**
             *  \brief Default constructor
             */
            DLL_EXPORT
            connection( ) = delete;

            /**
             *  \brief Create a connection
             *  \param[in]  host Server to connect to
             *  \param[in]  port Port number to connect to (defaults to
             * DEFAULT_PORT)
             *  \param[in]  protocol Protocol version to use (defaults to
             * PROTOCOL_TRY)
             */
            DLL_EXPORT
            explicit connection( const host_type& host,
                                 port_type        port = DEFAULT_PORT,
                                 protocol_type    protocol = PROTOCOL_TRY );

            /**
             * \brief Create a connection object, initialized with parameters
             * from a parameters object.
             * \param[in] params The parameter/configuration object used to
             * specify the connection parameters and options.
             *
             * \note params is deep copied.
             */
            DLL_EXPORT
            explicit connection( const NDS::parameters& params );

            /**
             * \brief Connection objects are not copyable
             */
            connection( const NDS::connection& other ) = delete;

            /**
             * \brief Connection objects are not copyable
             */
            connection& operator=( const NDS::connection& other ) = delete;

            /**
             * \brief Destroy the connection
             */
            DLL_EXPORT
            ~connection( );

            /**
             * \brief Close the connection
             */
            DLL_EXPORT
            void close( );

            /**
             * \brief Return the count of channels matching the given
             * predicate.
             * \details Return a count of channels that are available form this
             * connection within the given contstraints.
             * \param[in] pred A ChannelPredicate object holding the constraints
             * to impose on the search.
             * \return A count of channels matching the input parameters.
             *
             * \remarks For NDS1 a local cache of the channel list is searched.
             * For
             * NDS2 this call may result in one or more
             *          requests to the server, no local cache is used.
             *
             \code
             // Return all channels
             auto chan_count = conn.count_channels(channel_predicate());
             \endcode
             *
             \code
             // Return all DMT channels
             auto chan_count =
             conn.count_channels(channel_predicate("*DMT*"));
             \endcode
             *
             \code
             // Return all 16Hz-2KHz channels that are 32 bit integers
             auto chan_count =
             conn.count_channels(channel_predicate(FrequencyRange(16.0,
             2000.), channel::data_type::DATA_TYPE_INT32);
             \endcode
             *
             \code
             // Return all 16Hz-2KHz channels that are 32 bit integers
             // from O1
             auto chan_count =
             conn.count_channels(channel_predicate(FrequencyRange(16.0,
             2000.), channel::data_type::DATA_TYPE_INT32,
             epoch("O1"));
             \endcode
             */
            DLL_EXPORT
            count_type count_channels( const channel_predicate_object& pred );

            /**
             * \brief Retrieve a list of channels
             * \details Return a list of channels that are available form this
             * connection within the given contstraints.
             * \param[in] pred A ChannelPredicate object holding the constraints
             * to impose on the search.
             * \return A count of channels matching the input parameters.
             *
             * \remarks For NDS1 a local cache of the channel list is searched.
             * For
             * NDS2 this call may result in one or more
             *          requests to the server, no local cache is used.
             *
             \code
             // Return all channels
             auto chans = conn.find_channels(channel_predicate());
             \endcode
             *
             \code
             // Return all DMT channels
             auto chans = conn.find_channels(channel_predicate("*DMT*"));
             \endcode
             *
             \code
             // Return all 16Hz-2KHz channels that are 32 bit integers
             auto chans =
             conn.find_channels(channel_predicate(FrequencyRange(16.0, 2000.),
             channel::data_type::DATA_TYPE_INT32);
             \endcode
             *
             \code
             // Return all 16Hz-2KHz channels that are 32 bit integers
             // from the O1 run.
             auto chans =
             conn.find_channels(channel_predicate(FrequencyRange(16.0, 2000.),
             channel::data_type::DATA_TYPE_INT32, epoch("O1"));
             \endcode
             */
            DLL_EXPORT channels_type
                       find_channels( const channel_predicate_object& pred );

            /**
             * \brief Return a list of epochs
             * \details NDS2 has the concept of epochs.  A epoch may be set on a
             * connection to constrain all data and channel requests
             * to a given time frame.  This call returns the currently available
             * epochs.
             *
             * \return A list of epochs
             *
             * \remarks Only available on NDS2 connections.
             */
            DLL_EXPORT epochs_type get_epochs( );

            /**
             * \brief Given a list of channels return their availability over
             * the
             * current epoch.
             *
             * \param[in] time_span A epoch limiting start/stop time of the
             * availability check
             * \param[in] channel_names A list of channels to return
             * availability
             * for.
             *
             * \returns A list a channel availabilities.  There is one set of
             * aviailabilities returned per channel requested.
             */
            DLL_EXPORT availability_list_type
                       get_availability( const epoch&              time_span,
                                         const channel_names_type& channel_names );

            /**
             * \brief Check to see if data is avaiable
             * \details Given a start/stop time and a channel list check to see
             * if a
             * fetch request would suceed.  This will return failure if there is
             * a
             * gap in the data, or
             * if the data is on tape.
             *
             * \param[in] gps_start Start time of request
             * \param[in] gps_stop Stop time of request
             * \param[in] channel_names The channel list
             *
             * \returns True if the data is availble and not on tape
             */
            DLL_EXPORT bool check( buffer::gps_second_type   gps_start,
                                   buffer::gps_second_type   gps_stop,
                                   const channel_names_type& channel_names );

            /**
             * \brief Retreive data from the server
             * \details Given a start/stop time and a channel list retrieve the
             * associated data.
             *
             * \param[in] gps_start Start time of request
             * \param[in] gps_stop Stop time of request
             * \param[in] channel_names The channel list
             *
             * \returns A list of buffers containing the request data.
             *
             * \remarks This command can respond to missing data and high
             * latency
             * situations in various ways.  Use the (get/set)_parameter function
             * to
             * set how data gaps
             * or data on tape situations are handled.
             */
            DLL_EXPORT buffers_type
                       fetch( buffer::gps_second_type   gps_start,
                              buffer::gps_second_type   gps_stop,
                              const channel_names_type& channel_names );

            /**
             * \brief Return the parameter/configuration object.
             * @return A const reference to the parameter/configuration object
             * for the connection.
             */
            DLL_EXPORT NDS::parameters& parameters( ) const;

            /**
             * \brief Return the NDS2 channel hash.
             * \details NDSv2 server can return a hash of its internal channel
             * list.
             * This hash value can be used
             * by a client to determine if the channel list has updated.
             *
             * \returns A hash value.
             *
             * \remarks NDSv2 only.
             */
            DLL_EXPORT const channel::hash_type& hash( ) const;

            /**
             * \brief Retreive data in segments.
             * \details Setup an iterative data retrieval process.  This
             function
             * initiates the request for data in range specified by period, but
             * does
             * not actually retreive the data.  Instead it returns a data_stream
             * object
             * which manages the data iteration request.
             *
             * \param[in] period The range of data to return.  It may be any
             * range
             * that
             * a request_period may express, including unbounded live data,
             * bounded
             * live data,
             * or bounded historical data.
             *
             * \param[in] channel_names The list of channels to retrieve data
             * for.
             *
             * \returns A data_iterable object which manages the iteration.
             *
             * \note The iteration must be completed before any other operation
             * can take place on the connection object.
             *
             \code
             // to stream live data from a connection object 'conn'.
             auto stream = conn->iterate(NDS::request_period(),
             {"H1:GDS-CALIB_STRAIN,online",});
             for (auto it:stream) {
                  // *it will be a std::shared_ptr<NDS::buffers_type>
                  std::cout << (*it)->Start();
             }
             \endcode
             *
             \code
             // To stream historical data, skipping over gaps
             // it is assumed that start, stop are defined elsewhere
             // but are in scope.
             conn->parameters().set("ITERATE_USE_GAP_HANDLERS", "false");
             auto stream = conn->iterate(NDS::request_period(start, stop),
             {"H1:GDS-CALIB_STRAIN,online",});
             for (auto it:stream) {
                  // *it will be a std::shared_ptr<NDS::buffers_type>
                  std::cout << (*it)->Start();
             }
             \endcode
             */
            DLL_EXPORT NDS::data_iterable
                       iterate( NDS::request_period       period,
                                const channel_names_type& channel_names );

            /**
             * \brief Query the connection to see if a request is in progress.
             *
             * \returns True if a request is in progress, else false.
             *
             * \remarks A connection can only do on request at a time.
             */
            DLL_EXPORT bool request_in_progress( ) const;

        private:
            std::shared_ptr< detail::conn_p_type > p_;
        };

        DLL_EXPORT extern std::ostream& operator<<( std::ostream&     os,
                                                    const connection& conn );

        /**
         * \brief The parameters class holds the configuration for a connection.
         * This includes
         * gap handling strategy and server connection information.
         */
        class parameters
        {
        public:
            DLL_EXPORT parameters( );
            DLL_EXPORT explicit parameters(
                const connection::host_type& host,
                connection::port_type        port = connection::DEFAULT_PORT,
                connection::protocol_type protocol = connection::PROTOCOL_TRY );

            DLL_EXPORT parameters( const parameters& other );
            DLL_EXPORT parameters( parameters&& other ) noexcept;

            DLL_EXPORT parameters& operator=( const parameters& other );
            DLL_EXPORT parameters& operator=( parameters&& other ) noexcept;

            DLL_EXPORT ~parameters( );

            /**
             * \brief Return the host that is currently connected/configured.
             * \returns The hostname
             */
            DLL_EXPORT connection::host_type host( ) const;
            /**
             * \brief Return the port number that is currently
             * connected/configured.
             * \returns The connection port number.
             */
            DLL_EXPORT connection::port_type port( ) const;
            /**
             * \brief Return the protocol version configured/in use.
             * \returns The protocol version (PROTOCOL_ONE|PROTOCOL_TWO)
             */
            DLL_EXPORT connection::protocol_type protocol( ) const;

            /**
             * \brief Retreive the current parameter setting on a connection.
             * \details Retreive the current value set for parameter.  See
             * #set for documentation
             * on the available parameters.
             *
             * \param[in] key Parameter name, as a string.
             *
             * \returns The parameter value, or "" if an invalid parameter is
             * found.
             */
            DLL_EXPORT std::string get( const std::string& key ) const;

            /**
             * \brief Change the default behavior of the connection.
             * \details The connection object has a series of parameters that
             * can
             * be
             * set.  Currently the parameters
             * that can be set are "ALLOW_DATA_ON_TAPE", "GAP_HANDLER",
             * "ITERATE_USE_GAP_HANDLERS", "HOSTNAME", "PORT",
             * "PROTOCOL_VERSION"
             *
             * \section parameters Parameters
             * The parameters can be broken down into multiple types.  Those
             * dealing
             * with data access and those dealing with server selection.
             * \subsection parameter_access "Parameters for data access"
             * \subsubsection tape ALLOW_DATA_ON_TAPE
             * NDS2 only.  The NDS2 server may serve data that resides on a high
             * latency storage layer, such as a tape system.  This may lead
             * to data requests taking minutes or hours to complete, depending
             * on
             * the load on the storage system.  As of version 0.12 of the client
             * the default is to raise an error when accessing data that is on a
             * high latency storage layer.  This allows the
             * application to provide feedback (if needed) to a users regarding
             * amount of time that a request may take.  If this parameter is set
             * to
             * a
             * true value ("True", "1", "yes") then an error will not be raised
             * when
             * requesting data on a high latency storage.
             *
             * \subsubsection gaps GAP_HANDLER
             * For a given request there may not be be data available to fill
             * the
             * request completely.  This happens due to issues upstream of the
             * NDS server.  How this is handled is application specific. Setting
             * the "GAP_HANDLER" parameter allows the application to
             * specify what to do.  This includes options such as abort, zero
             * fill
             * the data, ...
             *
             * The gap handler will attempt to always return data if at all
             * possible.  You can detect the gaps by either
             * using the "ABORT_HANDLER" which will raise an error on the
             * presence of a gap, or by setting a gap handling
             * policy that makes the "gap filled" data obvious (ie
             * STATIC_HANDLER_NAN).  The times where data is not returned
             * should be limited to requesting a channel with a bad name (ie
             * H1:THIS-CHANNEL_NEVER_EXISTED_ANYWHERE) or an I/O
             * error.
             *
             * Available GAP_HANDLERS
             *  * "ABORT_HANDLER" This aborts the request when a gap is found in
             * the
             * data.
             *  * "STATIC_HANDLER_ZERO" This zero fills any missing data.
             *  * "STATIC_HANDLER_ONE" This fills any missing data with ones.
             *  * "STATIC_HANDLER_NAN" This fills any missing data with NaN
             * values
             * (or zero for integer channels).
             *  * "STATIC_HANDLER_POS_INF" This fills any missing data with
             * +infinity (or the maximum integer value for integer channels).
             *  * "STATIC_HANDLER_NEG_INF" This fills any missing data with
             * -infinity (or the minimum integer value for integer channels).
             *
             * \subsubsection iterate ITERATE_USE_GAP_HANDLERS
             * The iterate methods have a special case.  Unlike fetch operations
             * which work on a single block, the iterate methods retrieve chunks
             * of
             * data that
             * may not need to be contigous.  Setting ITERATE_USE_GAP_HANDLERS
             * to "false" configures the connection to simply skip any gaps in
             * the
             * data and only return
             * the data that is available.
             *
             * Please note that if you are asking for multiple channels that do
             * not have identical gaps the NDS servers will return a data not
             * found
             * error if ITERATE_USE_GAP_HANDLERS is set to false.
             *
             * \subsubsection Specifying the server
             *
             * \subsection server_selection "Server Selection"
             * The follow parameters are used to help select the server.  These
             * are only used by the connection when a connection is made.
             * Changes
             * to these parameters after a connection is made do not change
             * which
             * server it is connected to.  The connection object will update
             * these
             * fields if it makes a change (ie resolving PROTOCOL_TRY to a
             * specific
             * version).
             *
             * \subsubsection hostname Hostname
             * The host to connect to.  If not specified this defaults to
             * localhost.
             *
             * \subsubsection port Port
             * The port number to connect to.  If not specified this defaults to
             * NDS::connection::DEFAULT_PORT
             *
             * \subsubsection protocol_version PROTOCOL_VERSION
             * The protocol version to connect as.  If not specified this
             * defaults to NDS::connection::PROTOCOL_TRY
             *
             * \param[in] key A parameter name as a string.
             * \param[in] value The value to set parameter to, as a string.
             *
             * \returns True if the value could be set, else false.
             *
             */
            DLL_EXPORT bool set( const std::string& key,
                                 const std::string& value );

            /**
             * \brief Return a list of supported parameters.
             * \returns a list of parameter names that may be used with
             * #set or #get
             */
            DLL_EXPORT connection::parameters_type parameter_list( ) const;

        private:
            friend class NDS::detail::parameter_accessor;
            std::unique_ptr< detail::parameter_block > p_;
        };
    } // namespace abi_0
} // namespace NDS

#endif /* SWIG__COMMON__NDS_CONNECTION_HH */
