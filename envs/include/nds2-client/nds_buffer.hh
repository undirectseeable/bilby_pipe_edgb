/* -*- mode: C++ ; c-basic-offset: 2; indent-tabs-mode: nil -*- */

#ifndef SWIG__COMMON__NDS_BUFFER_HH
#define SWIG__COMMON__NDS_BUFFER_HH

#include <cmath>
#include <iostream>

#include <vector>

#include "nds_export.hh"
#include "nds_channel.hh"

namespace NDS
{

    inline namespace abi_0
    {
        //---------------------------------------------------------------------
        /// \brief A buffer holds the data contents of a channel.
        ///
        /// This class facilitates the storage of data and accompanying
        /// meta data.
        ///
        /// \headerfile nds.hh nds.hh
        //---------------------------------------------------------------------
        class buffer : public channel
        {
        public:
            //-------------------------------------------------------------------
            /// \brief Type second portion of a gps time
            //-------------------------------------------------------------------
            typedef long gps_second_type;
            //-------------------------------------------------------------------
            /// \brief Type nano second portion of a gps time
            //-------------------------------------------------------------------
            typedef long gps_nanosecond_type;
            //-------------------------------------------------------------------
            /// \brief Type appropriate for length.
            //-------------------------------------------------------------------
            typedef size_t size_type;
            //-------------------------------------------------------------------
            /// \brief Storage type for the data.
            //-------------------------------------------------------------------
            typedef std::vector< unsigned char > data_type;

            static const gps_second_type GPS_INF = 1999999999;

            //-------------------------------------------------------------------
            /// \brief Default constructor.
            ///
            /// \return
            ///     New object instance
            //-------------------------------------------------------------------
            DLL_EXPORT
            buffer( );

            //-------------------------------------------------------------------
            /// \brief Constructor
            ///
            /// \param[in] ChannelInfo
            ///     Channel metadata.
            /// \param[in] Second
            ///     GPS second start time of channel data.
            /// \param[in] NanoSecond
            ///     GPS nanosecond start time of channel data.
            /// \param[in] Buffer
            ///     Channel data.
            /// \param[in] BufferSize
            ///     Number of bytes in Buffer.
            ///
            /// \return
            ///     New object instance
            //-------------------------------------------------------------------
            DLL_EXPORT
            buffer( const channel&      ChannelInfo,
                    gps_second_type     Second,
                    gps_nanosecond_type NanoSecond,
                    const void*         Buffer,
                    size_type           BufferSize );

            //-------------------------------------------------------------------
            /// \brief Constructor
            ///
            /// \param[in] ChannelInfo
            ///     Channel metadata.
            /// \param[in] Second
            ///     GPS second start time of channel data.
            /// \param[in] NanoSecond
            ///     GPS nanosecond start time of channel data.
            /// \param[in] Buffer
            ///     Channel data in a std::vector<char>.  The vector will be
            ///     moved from.
            ///
            /// \return
            ///     New object instance
            //-------------------------------------------------------------------
            DLL_EXPORT
            buffer( const channel&      ChannelInfo,
                    gps_second_type     Second,
                    gps_nanosecond_type NanoSecond,
                    data_type&&         Buffer );

            //-------------------------------------------------------------------
            /// \brief Retrieve the number of samples being stored
            ///
            /// \return
            ///     The number of samples being stored
            //-------------------------------------------------------------------
            DLL_EXPORT size_type Samples( ) const;

            //-------------------------------------------------------------------
            /// \brief Retrieve the GPS start second of the data
            ///
            /// \return
            ///     The GPS start second of the data
            //-------------------------------------------------------------------
            DLL_EXPORT gps_second_type Start( ) const;

            //-------------------------------------------------------------------
            /// \brief Retrieve the GPS start nano second of the data
            ///
            /// \return
            ///     The GPS start nano second of the data
            //-------------------------------------------------------------------
            DLL_EXPORT gps_nanosecond_type StartNano( ) const;

            //-------------------------------------------------------------------
            /// \brief Retrieve the GPS stop second of the data
            ///
            /// \return
            ///     The GPS stop second of the data
            //-------------------------------------------------------------------
            DLL_EXPORT gps_second_type Stop( ) const;

            //-------------------------------------------------------------------
            /// \brief Retrieve the GPS stop nanosecond of the data
            ///
            /// \return
            ///     The GPS stop nanosecond of the data
            //-------------------------------------------------------------------
            DLL_EXPORT gps_nanosecond_type StopNano( ) const;
            //-------------------------------------------------------------------
            /// \brief Exchange the contents of this container with another.
            //-------------------------------------------------------------------
            DLL_EXPORT void swap( buffer& Source );

            //-------------------------------------------------------------------
            /// \brief Resize the container to hold N elements
            ///
            /// \param[in] N
            ///     The new number of elements to be stored.
            //-------------------------------------------------------------------
            DLL_EXPORT void resize( size_type N );

            //-------------------------------------------------------------------
            /// \brief Return a constant data iterator for this buffer, that
            /// references the beginning of the data.
            /// \tparam T The type to return an iterator for
            /// \return The iterator
            /// \note If T is incompatible with the runtime type of the buffer
            /// an
            /// exception is thrown.
            /// If T is void a void pointer to the buffer is returned, and you
            /// are
            /// guaranted not
            /// to have an exception raised.
            template < typename T >
            const T*
            cbegin( ) const
            {
                const auto val_type =
                    NDS::channel_data_type_conversion< T >::value;

                if ( val_type == DataType( ) ||
                     ( std::is_same< T, void >::value &&
                       val_type == NDS::channel::DATA_TYPE_UNKNOWN ) )
                {
                    return reinterpret_cast< const T* >( data.data( ) );
                }
                throw std::runtime_error(
                    "Invalid cast, the buffer data type is "
                    "not compatible with your requested "
                    "type" );
            }

            //-------------------------------------------------------------------
            /// \brief Return a constant data iterator for this buffer, that
            /// references the just after the end of the data.
            /// \tparam T The type to return an iterator for
            /// \return The iterator
            /// \note If T is incompatible with the runtime type of the buffer
            /// an
            /// exception is thrown.
            template < typename T >
            const T*
            cend( ) const
            {
                const auto val_type =
                    NDS::channel_data_type_conversion< T >::value;

                if ( val_type == DataType( ) ||
                     ( std::is_same< T, void >::value &&
                       val_type == NDS::channel::DATA_TYPE_UNKNOWN ) )
                {
                    return reinterpret_cast< const T* >(
                        data.data( ) + ( Samples( ) * DataTypeSize( ) ) );
                }
                throw std::runtime_error(
                    "Invalid cast, the buffer data type is "
                    "not compatible with your requested "
                    "type" );
            }

            //-------------------------------------------------------------------
            /// \brief This is a type aware, bounds checked lookup in the
            /// buffer.
            /// \tparam T The type to return a const reference for.
            /// \tparam index The number/index of the sample to reference.
            /// \return A const reference to the sample.
            /// \note If T is incompatible with the runtime type of the buffer
            /// an exception is thrown.  If the index is out of bounds < 0 || >=
            /// Samples()
            /// an out of range exception is thrown.
            template < typename T >
            const T&
            at( size_type index ) const
            {
                const T* start = cbegin< T >( );
                if ( array_out_of_range( index, Samples( ) ) )
                {
                    throw std::out_of_range(
                        "The requested index is out of range" );
                }
                return start[ index ];
            }

            // Helper functions

            //-------------------------------------------------------------------
            /// \brief Convert relative sample offsets to relative second
            /// offsets.
            ///
            /// \param[in] offset_samples
            ///     An sample number [0,...)
            ///
            /// \return
            ///     The number of seconds since the beginning of this buffer
            ///     that
            ///     this sample refers located at.  This is the number of
            ///     seconds
            ///     since Start().
            //-------------------------------------------------------------------
            DLL_EXPORT gps_second_type
            samples_to_seconds( size_type offset_samples ) const;

            //-------------------------------------------------------------------
            /// \brief Given a sample count, determine how many seconds and
            ///  nanoseconds worth of data are avaialble, and return the
            ///  nanosecond
            /// count.
            ///
            /// \param[in] offset_samples
            ///     An sample number [0,...)
            ///
            /// \return
            ///     A nanosecond value [0,1000000000) corresponding to the
            ///     number
            ///     of nanoseconds passed the last second boundary for a given
            ///     sample count.
            //-------------------------------------------------------------------
            DLL_EXPORT gps_second_type
            samples_to_trailing_nanoseconds( size_type offset_samples ) const;

            //-------------------------------------------------------------------
            /// \brief Convert relative byte offsets to relative sample offsets.
            ///
            /// \param[in] offset_bytes
            ///     An byte number [0,...)
            ///
            /// \return
            ///     The number of samples since the beginning of this buffer
            ///     that
            //      this byte location refers to.
            //-------------------------------------------------------------------
            DLL_EXPORT size_type
            bytes_to_samples( size_type offset_bytes ) const;

            //-------------------------------------------------------------------
            /// \brief Convert relative second offsets to relative sample
            /// offsets.
            ///
            /// \param[in] offset_seconds
            ///     A second number [0,...).  This is the number of seconds
            ///     since
            ///     Start()
            /// \param[in] offset_nano
            ///     A nanosecond offset, defaults to 0
            ///
            /// \return
            ///     The number of samples since the beginning of this buffer
            ///     that
            //      this time location refers to.
            //-------------------------------------------------------------------
            DLL_EXPORT size_type
            seconds_to_samples( gps_second_type     offset_seconds,
                                gps_nanosecond_type offset_nano = 0 ) const;

            //-------------------------------------------------------------------
            /// \brief Convert relative sample offsets to relative byte offsets.
            ///
            /// \param[in] offset_samples
            ///     A sample number [0,...).  This is the number of samples
            ///     since
            ///     the start of this buffer
            ///
            /// \return
            ///     The byte offset that this sample would refer to relative to
            ///     the start of this buffer.
            //-------------------------------------------------------------------
            DLL_EXPORT size_type
            samples_to_bytes( size_type offset_samples ) const;

            //-------------------------------------------------------------------
            /// \brief Reset the channel type.  Set the sample count to 0.
            ///
            /// \param[in] ChannelInfo channel meta data to copy into this
            /// buffer
            /// \param[in] Second
            ///     A second number [0,...) that the buffer should start at
            /// \param[in] NanoSecond
            ///     The number of nanoseconds atfer Second that this buffer
            ///     starts.
            ///
            /// \return
            ///     The number of samples since the beginning of this buffer
            ///     that this time location refers to.
            //-------------------------------------------------------------------
            DLL_EXPORT void
            reset_channel_info( const channel&      ChannelInfo,
                                gps_second_type     Second,
                                gps_nanosecond_type NanoSecond );

        private:
            gps_second_type     gps_second;
            gps_nanosecond_type gps_nanosecond;
            data_type           data;

            template < typename IndexType >
            bool array_out_of_range( IndexType Index, IndexType Max ) const;

        protected:
            bool is_minute_trend( ) const;
        };

        typedef std::vector< buffer > buffers_type;

        inline bool
        buffer::is_minute_trend( ) const
        {
            return Type( ) == CHANNEL_TYPE_MTREND;
        }

        //---------------------------------------------------------------------
        //---------------------------------------------------------------------
        inline buffer::gps_second_type
        buffer::samples_to_seconds( buffer::size_type offset_samples ) const
        {
            if ( is_minute_trend( ) )
            {
                return static_cast< gps_second_type >( offset_samples * 60 );
            }
            return static_cast< gps_second_type >( offset_samples /
                                                   SampleRate( ) );
        }

        //---------------------------------------------------------------------
        //---------------------------------------------------------------------
        inline buffer::gps_nanosecond_type
        buffer::samples_to_trailing_nanoseconds(
            NDS::buffer::size_type offset_samples ) const
        {
            if ( is_minute_trend( ) )
            {
                return 0;
            }
            gps_nanosecond_type samples = offset_samples %
                static_cast< gps_nanosecond_type >( SampleRate( ) );
            return static_cast< gps_nanosecond_type >( 1e+9 * samples /
                                                       SampleRate( ) );
        }

        //---------------------------------------------------------------------
        //---------------------------------------------------------------------
        inline buffer::size_type
        buffer::bytes_to_samples( buffer::size_type offset_bytes ) const
        {
            return offset_bytes / DataTypeSize( );
        }

        //---------------------------------------------------------------------
        //---------------------------------------------------------------------
        inline buffer::size_type
        buffer::seconds_to_samples(
            buffer::gps_second_type     offset_seconds,
            buffer::gps_nanosecond_type offset_nano ) const
        {
            if ( is_minute_trend( ) )
            {
                return static_cast< size_type >( offset_seconds / 60 );
            }
            return static_cast< size_type >( offset_seconds * SampleRate( ) );
        }

        //---------------------------------------------------------------------
        //---------------------------------------------------------------------
        inline buffer::size_type
        buffer::samples_to_bytes( buffer::size_type offset_samples ) const
        {
            return offset_samples * DataTypeSize( );
        }

        //---------------------------------------------------------------------
        /// The number of samples in the data set.
        /// The number of bytes stored is the number of samples multiplied by
        /// size of the data type.
        //---------------------------------------------------------------------
        inline buffer::size_type
        buffer::Samples( ) const
        {
            return data.size( ) / DataTypeSize( );
        }

        //---------------------------------------------------------------------
        //---------------------------------------------------------------------
        inline buffer::gps_second_type
        buffer::Start( ) const
        {
            return gps_second;
        }

        //---------------------------------------------------------------------
        //---------------------------------------------------------------------
        inline buffer::gps_nanosecond_type
        buffer::StartNano( ) const
        {
            return gps_nanosecond;
        }

        //---------------------------------------------------------------------
        //---------------------------------------------------------------------
        inline buffer::gps_second_type
        buffer::Stop( ) const
        {
            auto samples = Samples( );
            auto total_ns =
                StartNano( ) + samples_to_trailing_nanoseconds( samples );
            gps_second_type additional_from_nano =
                ( total_ns >= static_cast< gps_nanosecond_type >( 1e+9 ) ? 1
                                                                         : 0 );
            return gps_second + samples_to_seconds( samples ) +
                additional_from_nano;
        }

        inline buffer::gps_nanosecond_type
        buffer::StopNano( ) const
        {
            auto samples = Samples( );
            auto total_ns =
                StartNano( ) + samples_to_trailing_nanoseconds( samples );
            return total_ns % 1000000000;
        }

        //---------------------------------------------------------------------
        //---------------------------------------------------------------------
        inline void
        buffer::resize( size_type N )
        {
            data.resize( N * DataTypeSize( ) );
        }

        //---------------------------------------------------------------------
        //---------------------------------------------------------------------

        DLL_EXPORT extern std::ostream& operator<<( std::ostream& os,
                                                    const buffer& obj );

        DLL_EXPORT extern std::ostream& operator<<( std::ostream&       os,
                                                    const buffers_type& obj );

        //---------------------------------------------------------------------
        //---------------------------------------------------------------------

        template <>
        inline bool
        buffer::array_out_of_range< size_t >( size_t Index, size_t Max ) const
        {
            return ( Index >= Samples( ) );
        }

        template < typename IndexType >
        inline bool
        buffer::array_out_of_range( IndexType Index, IndexType Max ) const
        {
            return ( Index <= 0 || Index >= Samples( ) );
        }

    } // namespace abi_0
} // namespace NDS

#endif /* SWIG__COMMON__NDS_BUFFERL_HH */
