#ifndef LIBNDSCXX_MODULE_STANDALONE_HH
#define LIBNDSCXX_MODULE_STANDALONE_HH

#include "nds_connection.hh"

namespace NDS
{
    inline namespace abi_0
    {

        /**
         * \brief Retreive data from the server without having to manage a
         * connection.
         * \details Given a start/stop time and a channel list retrieve the
         * associated data.
         *
         * \param[in] params Parameters object specifying connection settings
         * \param[in] gps_start Start time of request
         * \param[in] gps_stop Stop time of request
         * \param[in] channel_names The channel list
         *
         * \returns A list of buffers containing the request data.
         *
         * \remarks The params argument should be used to specify how fetch
         * selects gap handlers, deals with data on tape, and provide
         * a specific server to connect to.
         */
        DLL_EXPORT NDS::buffers_type
        fetch( const NDS::parameters&                     params,
               buffer::gps_second_type                    gps_start,
               buffer::gps_second_type                    gps_stop,
               const NDS::connection::channel_names_type& channel_names );

        /**
         * \brief Retreive data from the server without having to manage a
         * connection.
         * \details Given a start/stop time and a channel list retrieve the
         * associated data, pulling connection information from the environment.
         *
         * \param[in] gps_start Start time of request
         * \param[in] gps_stop Stop time of request
         * \param[in] channel_names The channel list
         *
         * \returns A list of buffers containing the request data.
         *
         * \remarks The server to connect to, gap handlers, ... are all
         * configured
         * via the environment.
         */
        DLL_EXPORT NDS::buffers_type
        fetch( buffer::gps_second_type                    gps_start,
               buffer::gps_second_type                    gps_stop,
               const NDS::connection::channel_names_type& channel_names );

        /**
         * \brief Retreive data in segments without having to manage a
         connection.
         * \details Setup an iterative data retrieval process.  This function
         * initiates the request for data in range specified by period, but does
         * not actually retreive the data.  Instead it returns a data_stream
         * object which manages the data iteration request.
         *
         * \param[in] params Parameters object specifying connection settings
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
         * \note All iterate calls must be terminated.  If you break out of
         * an iterate loop without retrieving all of the available data you
         * must call the abort() method of the data_iterable object to ensure
         * that a network connection is not left open to the server.
         * This will eventually happen when all references to the data_iterable
         * object and the iterators it refers to are destructed.
         *
         \code
         // to stream live data from a connection object 'conn'.
         auto params = parameters(hostname, port);
         auto stream = iterate(params, NDS::request_period(),
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
         auto params = parameters();
         params.set("ITERATE_USE_GAP_HANDLERS", "false");
         auto stream = iterate(params, NDS::request_period(start, stop),
         {"H1:GDS-CALIB_STRAIN,online",});
         for (auto it:stream) {
              // *it will be a std::shared_ptr<NDS::buffers_type>
              std::cout << (*it)->Start();
         }
         \endcode
         */
        DLL_EXPORT NDS::data_iterable
        iterate( const NDS::parameters&                     params,
                 NDS::request_period                        period,
                 const NDS::connection::channel_names_type& channel_names );

        /**
         * \brief Retreive data in segments without having to manage a
         connection.
         * \details Setup an iterative data retrieval process.  This function
         * initiates the request for data in range specified by period, but does
         * not actually retreive the data.  Instead it returns a data_stream
         * object which manages the data iteration request.
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
         * \note All iterate calls must be terminated.  If you break out of
         * an iterate loop without retrieving all of the available data you
         * must call the abort() method of the data_iterable object to ensure
         * that a network connection is not left open to the server.
         * This will eventually happen when all references to the data_iterable
         * object and the iterators it refers to are destructed.
         *
         \code
         // to stream live data from a connection object 'conn'.
         auto stream = iterate(NDS::request_period(),
         {"H1:GDS-CALIB_STRAIN,online",});
         for (auto it:stream) {
              // *it will be a std::shared_ptr<NDS::buffers_type>
              std::cout << (*it)->Start();
         }
         \endcode
         *
         \code
         // To stream historical data.
         // it is assumed that start, stop are defined elsewhere
         // but are in scope.
         // Note if to explicitly set gap handlers/... use the
         // overload which accepts a parameters object.
         auto stream = iterate(NDS::request_period(start, stop),
         {"H1:GDS-CALIB_STRAIN,online",});
         for (auto it:stream) {
              // *it will be a std::shared_ptr<NDS::buffers_type>
              std::cout << (*it)->Start();
         }
         \endcode
         */
        DLL_EXPORT NDS::data_iterable
        iterate( NDS::request_period                        period,
                 const NDS::connection::channel_names_type& channel_names );

        /**
         * \brief Retrieve a list of channels without having to manage a
         connection.
         * \details Return a list of channels that are available form this
         * connection within the given contstraints.
         * \param[in] params A parameters object used to specify a specific
         server
         * \param[in] pred A channel_predicate object holding the constraints
         * to impose on the search.
         * \return A count of channels matching the input parameters.
         *
         * \remarks This may result in multiple requests being sent
         * to the server.
         *
         \code
         // Return all channels
         auto params = parameters(hostname, port);
         auto chans = find_channels(params, channel_predicate());
         \endcode
         *
         \code
         // Return all DMT channels
         auto params = parameters(hostname, port);
         auto chans = conn.find_channels(params, channel_predicate("*DMT*"));
         \endcode
         *
         \code
         // Return all 16Hz-2KHz channels that are 32 bit integers
         auto params = parameters(hostname, port);
         auto chans =
         find_channels(params, channel_predicate(FrequencyRange(16.0, 2000.),
         channel::data_type::DATA_TYPE_INT32);
         \endcode
         *
         \code
         // Return all 16Hz-2KHz channels that are 32 bit integers
         // from the O1 run.
         auto params = parameters(hostname, port);
         auto chans =
         find_channels(params, channel_predicate(FrequencyRange(16.0, 2000.),
         channel::data_type::DATA_TYPE_INT32, epoch("O1"));
         \endcode
         */
        DLL_EXPORT channels_type
        find_channels( const NDS::parameters&          params,
                       const channel_predicate_object& pred );

        /**
         * \brief Retrieve a list of channels without having to manage a
         connection.
         * \details Return a list of channels that are available form this
         * connection within the given contstraints.
         * \param[in] pred A channel_predicate object holding the constraints
         * to impose on the search.
         * \return A count of channels matching the input parameters.
         *
         * \remarks This may result in multiple requests being sent
         * to the server.
         *
         * \note The server(s) that are queried for channel lists is pulled
         * from the environment.  To specify a specific server use the
         * overload that takes a parameters object.
         *
         \code
         // Return all channels
         auto chans = find_channels(channel_predicate());
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
         find_channels(channel_predicate(FrequencyRange(16.0, 2000.),
         channel::data_type::DATA_TYPE_INT32);
         \endcode
         *
         \code
         // Return all 16Hz-2KHz channels that are 32 bit integers
         // from the O1 run.
         auto chans =
         find_channels(channel_predicate(FrequencyRange(16.0, 2000.),
         channel::data_type::DATA_TYPE_INT32, epoch("O1"));
         \endcode
         */
        DLL_EXPORT channels_type
        find_channels( const channel_predicate_object& pred );
    }
}

#endif