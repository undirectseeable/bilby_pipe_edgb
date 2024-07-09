//
// Created by jonathan.hanks on 5/25/18.
//

#ifndef NDS2_CLIENT_NDS_DATA_ITERATOR_HH
#define NDS2_CLIENT_NDS_DATA_ITERATOR_HH

#include <iterator>
#include <memory>

#include "nds_buffer.hh"
#include "nds_channel.hh"

namespace NDS
{
    namespace detail
    {
        class iterate_handler;
    }

    inline namespace abi_0
    {
        /**
         * \brief This represents a [start, stop) time with an optional data
         * stride.
         * \details This is used to represent a time range associated with a
         * data
         * request.
         * Constructors are provided to allow requesting a [start, stop) time in
         * the
         * past,
         * a bounded request of live data [0, duration), and an endless request
         * of
         * live data
         * [0, infinite).
         */
        struct request_period
        {
            using gps_second_type = NDS::buffer::gps_second_type;
            typedef long    stride_type;
            gps_second_type start;
            gps_second_type stop;
            stride_type     stride;

            /**
             * \brief a data stride of FAST_STRIDE requests sub-second data if
             * possible.  On
             * systems that do not support sub-second data this is treated as
             * AUTO_STRIDE.
             */
            const static stride_type FAST_STRIDE = -1;

            /**
             * \brief a data stride of AUTO_STRIDE requests that the NDS systems
             * determine
             * the stride of data.  For online requests this will typically be
             * 1s, for
             * offline data this may vary but is likely to be around the size of
             * a data frame.
             */
            const static stride_type AUTO_STRIDE = 0;

            /**
             * \brief Default constructor, represent a request for an endless
             * amount
             * of live data
             */
            request_period( ) : start( 0 ), stop( 0 ), stride( 0 )
            {
            }

            /**
             * \brief Represent a request for an endless amount of live data
             * with a
             * given stride.
             * @param requested_stride The number of seconds to return in each
             * iteration.
             * \note the requested_stride should be considered a requested max,
             * the
             * server may return less.
             */
            explicit request_period( stride_type requested_stride )
                : start( 0 ), stop( 0 ), stride( requested_stride )
            {
            }

            /**
             * \brief Represent a request for bounded data [start, stop)
             * @param requested_start The start time, 0 represents live/online
             * data,
             * else a gps time
             * @param requested_stop For online data this is the duration,
             * otherwise
             * it is the stop time
             * \note the requested_stride should be considered a requested max,
             * the
             * server may return less.
             */
            explicit request_period( gps_second_type requested_start,
                                     gps_second_type requested_stop )
                : start( requested_start ), stop( requested_stop ), stride( 0 )
            {
            }

            /**
             * \brief Represent a request for bounded data [start, stop) with a
             * stride
             * @param requested_start The start time, 0 represents live/online
             * data,
             * else a gps time
             * @param requested_stop For online data this is the duration,
             * otherwise
             * it is the stop time
             * @param requested_stride The number of seconds to return data for
             * each
             * iteration.
             * \note the requested_stride should be considered a requested max,
             * the
             * server may return less.
             */
            explicit request_period( gps_second_type requested_start,
                                     gps_second_type requested_stop,
                                     stride_type     requested_stride )
                : start( requested_start ), stop( requested_stop ),
                  stride( requested_stride )
            {
            }
        };

        /**
         * \brief A input iterator
         * \details This is the iterator type used by NDS::data_iterable.
         * \note Due to the demands of iterators, and to keep the number of
         * times
         * buffers are copied, the iteration is done
         * in terms of std::shared_ptr<NDS::buffers_type>.  As such the current
         * value is tracked by the data_iterable object
         * and by the iterators.  It is important to complete the iteration, and
         * allow the iterators to go out of scope (or
         * be assigned to the sentinal/empty value) to allow the internal
         * buffers to
         * be released.
         */
        class data_stream_iterator
        {
        public:
            typedef std::shared_ptr< buffers_type > value_type;
            typedef value_type&                     reference;
            typedef value_type*                     pointer;
            typedef std::size_t                     difference_type;
            typedef std::input_iterator_tag         iterator_category;

            /**
             * \brief Default constructor
             * \details The iterator is defined in an empty/end state.
             */
            DLL_EXPORT data_stream_iterator( );
            /**
             * \brief Copy constructor
             * \details A data_stream_iterator can be safely copied.  When done
             * the
             * two
             * iterators will refer to the same iteration and reference the same
             * data.
             * @param other The iterator to copy from.
             */
            DLL_EXPORT
            data_stream_iterator( const data_stream_iterator& other );
            /**
             * \brief Move constructor
             * \details A data_stream_iterator can be safely moved.  When done
             * other
             * will be in an empty/end state.
             * @param other The iterator to move from.
             */
            DLL_EXPORT
            data_stream_iterator( data_stream_iterator&& other ) noexcept;

            DLL_EXPORT
            data_stream_iterator( std::shared_ptr< detail::iterate_handler > p,
                                  value_type c );

            DLL_EXPORT ~data_stream_iterator( );

            /**
             * \brief Copy operator
             * \details A data_stream_iterator can be safely copied.  When done
             * the
             * two
             * iterators will refer to the same iteration and reference the same
             * data.
             * @param other The iterator to copy from.
             */
            DLL_EXPORT data_stream_iterator&
            operator=( const data_stream_iterator& other );
            /**
             * \brief Move operator
             * \details A data_stream_iterator can be safely moved.  When done
             * other
             * will be in an empty/end state.
             * @param other The iterator to move from.
             */
            DLL_EXPORT data_stream_iterator&
            operator=( data_stream_iterator&& other ) noexcept;

            DLL_EXPORT bool
            operator==( const data_stream_iterator& other ) const;

            DLL_EXPORT bool
            operator!=( const data_stream_iterator& other ) const;

            /**
             * \brief Access the data at the current location of the iteration.
             * @return A reference to the current data.
             * \note While the iterator is not in an end/empty state and the
             * iteration is not complete this
             * will never return a null shared_ptr.
             */
            DLL_EXPORT reference operator*( );

            /**
             * \note This updates the state of the associated data_iterable
             * object.
             */
            DLL_EXPORT data_stream_iterator& operator++( );
            /**
             * \note This updates the state of the associated data_iterable
             * object.
             */
            DLL_EXPORT data_stream_iterator operator++( int );

        private:
            std::shared_ptr< detail::iterate_handler > p_;
            value_type                                 cache_;
        };

        /**
         * \brief The data_iterable manages streaming data from an
         * NDS::connection.
         * \details This class manages a single stream of data by providing a
         * set of
         * input iterators which
         * represent the data stream.
         *
         * \note All data from a iteration must be consumed before the
         * underlying
         * connection is available for additional
         * commands.
         *
         * \note Due to the demands of iterators, and to keep the number of
         * times
         * buffers are copied, the iteration is done
         * in terms of std::shared_ptr<NDS::buffers_type>.  As such the current
         * value is tracked by the data_iterable object
         * and by the iterators.  It is important to complete the iteration, and
         * allow the iterators to go out of scope (or
         * be assigned to the end() value) to allow the internal buffers to be
         * released.
         *
         * \note The iteration is done when begin() == end().
         */
        class data_iterable
        {
        public:
            /**
             * \brief NDS::data_stream_iterator is the iterator type for this
             * object.
             */
            typedef data_stream_iterator iterator_type;

            DLL_EXPORT explicit data_iterable(
                std::shared_ptr< NDS::detail::iterate_handler > handler );
            /**
             * \brief Copy constructor
             * \details A data_iterable may safely be copied.  Copied objects
             * refer
             * to the same
             * iteration and share state.
             * \param other A data_iterable to copy from.
             */
            DLL_EXPORT data_iterable( const data_iterable& other );
            /**
             * \brief Move constructor
             * \details A data_iterable may safely be moved.
             * \param other A data_iterable to move from.
             * \note after a move other is defined as refering to a completed
             * iteration.
             */
            DLL_EXPORT data_iterable( data_iterable&& other ) noexcept;

            DLL_EXPORT ~data_iterable( );

            /**
             * \brief Copy assignment operator
             * \details A data_iterable may safely be copied.  Copied objects
             * refer
             * to the same
             * iteration and share state.
             * @param other The data_iterable to copy from
             * @return A reference to *this
             */
            DLL_EXPORT data_iterable& operator=( const data_iterable& other );
            /**
             * \brief Move assigment operator
             * \details A data_iterable may safely be moved.
             * \param other A data_iterable to move from.
             * \note after a move other is defined as refering to a completed
             * iteration.
             */
            DLL_EXPORT data_iterable&
            operator=( data_iterable&& other ) noexcept;

            /**
             * \brief Return the current start tof the iteration.
             * @return An iterator_type object referencing the current state of
             * the
             * iteration.
             * \note When an iterator is advanced, it updates the shared state
             * of
             * the iteration, and has the side
             * effect of moving where begin references.
             * \note the returned iterator satisfies the requirements of an
             * InputIterator
             */
            DLL_EXPORT iterator_type begin( );

            /**
             * \brief Return a end/sentinal iterator
             * @return An iterator_type object referencing the end state of the
             * iteration.
             * \note the returned iterator satisfies the requirements of an
             * InputIterator
             */
            DLL_EXPORT iterator_type end( );

            /**
             * \brief Abort an on-going iteration and close the underlying
             * connection.
             * \note As this closes the underlying connection, a new connection
             * object must be used
             * to do any further work after aborting an iteration.
             */
            DLL_EXPORT void abort( );

        private:
            std::shared_ptr< NDS::detail::iterate_handler > p_;
        };
    }
}

#endif // NDS2_CLIENT_NDS_DATA_ITERATOR_HH
