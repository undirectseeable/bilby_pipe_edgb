/* -*- mode: C++ ; c-basic-offset: 2; indent-tabs-mode: nil -*- */
/* set vi: ts=2:softtabstop=2,shiftwidth=2,expandtab */

#ifndef SWIG__COMMON__NDS_CHANNEL_HH
#define SWIG__COMMON__NDS_CHANNEL_HH

#include <ctime>

#include <complex>
#include <memory>
#include <string>
#include <ostream>
#include <vector>

#include "nds_export.hh"

namespace NDS
{
    namespace detail
    {
        struct conn_p_type;
    }

    inline namespace abi_0
    {
        /**
         * \brief Represents a LIGO data channel.
         * \details A channel encasulates the meta data of LIGO data.  It has a
         * name
         * and parameters.
         * \headerfile nds.hh nds.hh
         */
        class channel
        {
        public:
            /**
             * The available channel types
             */
            typedef enum {
                CHANNEL_TYPE_UNKNOWN = 0, ///< Unknown
                CHANNEL_TYPE_ONLINE = ( 1 << 0 ), ///< Online channel
                CHANNEL_TYPE_RAW = ( 1 << 1 ), ///< Raw channel
                CHANNEL_TYPE_RDS = ( 1 << 2 ), ///< Reduced data set
                CHANNEL_TYPE_STREND = ( 1 << 3 ), ///< Second trend
                CHANNEL_TYPE_MTREND = ( 1 << 4 ), ///< Minute trend
                CHANNEL_TYPE_TEST_POINT = ( 1 << 5 ), ///< Test point data
                CHANNEL_TYPE_STATIC = ( 1 << 6 ) ///< Static data
            } channel_type;

            /**
             * \brief Defines the internal data representation.
             */
            typedef enum {
                DATA_TYPE_UNKNOWN = 0, ///< Unkown
                DATA_TYPE_INT16 = ( 1 << 0 ), ///< 16 bit signed integer
                DATA_TYPE_INT32 = ( 1 << 1 ), ///< 32 bit signed integer
                DATA_TYPE_INT64 = ( 1 << 2 ), ///< 64 bit signed integer
                DATA_TYPE_FLOAT32 = ( 1 << 3 ), ///< 32 bit float value
                DATA_TYPE_FLOAT64 = ( 1 << 4 ), ///< 64 bit float value
                DATA_TYPE_COMPLEX32 =
                    ( 1 << 5 ), ///< Complex value, two 32 bit floats
                DATA_TYPE_UINT32 = ( 1 << 6 ) ///< 32 bit unsigned integer value
            } data_type;

            /**
             * \brief The hash_type represents a channel hash.
             * The channel hash is an hash of the NDS2 channel list.  It can be
             * used
             * by appliations to determine if a channel list has changed.
             */
            class hash_type : private std::vector< unsigned char >
            {
            public:
                typedef std::vector< unsigned char > element_type;

                using element_type::size;

                hash_type( );

                bool compare( const void* Buffer,
                              size_t      Length = ( size_t )( -1 ) ) const;

                const void* ref( ) const;

                void reset( );

            private:
                friend struct NDS::detail::conn_p_type;

                static const unsigned char zero_hash[ 1 ];
                static const size_t        MAX_SIZE;
            };

            typedef double sample_rate_type; ///< Defines the sample rate type
            typedef float  signal_gain_type; ///< Defines the gain type
            typedef float  signal_slope_type; ///< Defines the slope type
            typedef float  signal_offset_type; ///< Defines the offset type
            typedef size_t
                size_type; ///< Defines sizes when dealing with channels

            /**
             * \brief A vector of channel names
             */
            typedef std::vector< std::string > channel_names_type;

            /**
             * \brief The combination of all valid channel types.
             */
            DLL_EXPORT static const channel_type DEFAULT_CHANNEL_MASK =
                ( channel_type )(
                    CHANNEL_TYPE_ONLINE | CHANNEL_TYPE_RAW | CHANNEL_TYPE_RDS |
                    CHANNEL_TYPE_STREND | CHANNEL_TYPE_MTREND |
                    CHANNEL_TYPE_TEST_POINT | CHANNEL_TYPE_STATIC );

            /**
             * \brief The combinatino of all valid data types.
             */
            DLL_EXPORT static const data_type DEFAULT_DATA_MASK = ( data_type )(
                DATA_TYPE_INT16 | DATA_TYPE_INT32 | DATA_TYPE_INT64 |
                DATA_TYPE_FLOAT32 | DATA_TYPE_FLOAT64 | DATA_TYPE_COMPLEX32 |
                DATA_TYPE_UINT32 );

            DLL_EXPORT static const sample_rate_type
                MIN_SAMPLE_RATE; ///< Smallest sample rate possible
            DLL_EXPORT static const sample_rate_type
                MAX_SAMPLE_RATE; ///< Largest sample rate possible

            /**
             * \brief Convert from the legacy daqd channel types to a
             * channel_type
             * enum.
             * \param[in] ChanType The daqd channel type value
             * \return The corresponding channel_type enum
             */
            DLL_EXPORT static channel_type convert_daq_chantype( int ChanType );

            /**
             * \brief Convert from the legacy daqd data types to a data_type
             * enum.
             * \param[in] DataType The daqd data type value
             * \return The corresponding data_type enum
             */
            DLL_EXPORT static data_type convert_daq_datatype( int DataType );

            /**
             * \brief Return a string representatino of the given channel_type
             * \param[in] ChannelType Input channel type
             * \return A string representing ChannelType
             */
            DLL_EXPORT static const std::string&
            ToString( channel_type ChannelType );

            /**
             * \brief Return a string representatino of the given data_type
             * \param[in] DataType Input data type
             * \return A string representing DataType
             */
            DLL_EXPORT static const std::string& ToString( data_type DataType );

            /**
             * \brief Default constructor
             * \return New instance of a channel object
             */
            DLL_EXPORT
            channel( );

            /**
             * \brief Copy constructor
             * \param[in] Source The object to be copied
             * \return New instance of a channel object
             */
            DLL_EXPORT
            channel( const channel& Source );

            /**
             * \brief Create a channel object.
             * \details The channel object represents a stream a LIGO data.
             * \param[in] Name The name of the channel as a string.
             * \param[in] Type The channel type (RAW, ONLINE, ...).
             * \param[in] DataType The data_type that of the channel.
             * \param[in] SampleRate Rate that the channel was recorded at.
             * \param[in] Gain Gain of the channel.
             * \param[in] Slope Slope of the channel.
             * \param[in] Offset Offset of the channel.
             * \param[in] Units Units of the channel as a string.
             * \return New instance of a channel object
             */
            DLL_EXPORT
            channel( const std::string& Name,
                     channel_type       Type,
                     data_type          DataType,
                     sample_rate_type   SampleRate,
                     signal_gain_type   Gain,
                     signal_slope_type  Slope,
                     signal_offset_type Offset,
                     std::string        Units );

            /**
             * \brief Return the channel name.
             * \return The name as a string.
             */
            DLL_EXPORT const std::string& Name( ) const;

            /**
             * \brief Return the name with additional information.
             * \return The name, rate, type, and data type as a string.
             *
             * \remark Returns a string such as "<name (sample rate, type, data
             * type)>"
             */
            DLL_EXPORT std::string NameLong( ) const;

            /**
             * \brief Return the type of the channel.
             * \return Returns a channel_type representing the channel type.
             */
            DLL_EXPORT channel_type Type( ) const;

            /**
             * \brief Return the data type of the channel.
             * \return A data_type representing the data type of the channel.
             */
            DLL_EXPORT data_type DataType( ) const;

            /**
             * \brief Return the size in bytes of an individual sample from the
             * channel.
             * \return A size_type value giving the size of an individual sample
             * of
             * this channel.
             */
            DLL_EXPORT size_type DataTypeSize( ) const;

            /**
             * \brief Return the sample rate of the channel.
             * \return The sample rate as a sample_rate_type.
             */
            DLL_EXPORT sample_rate_type SampleRate( ) const;

            /**
             * \brief Return the gain of the channel.
             * \return The gain as a signal_gain_type.
             */
            DLL_EXPORT signal_gain_type Gain( ) const;

            /**
             * \brief Return the slope of the channel.
             * \return The slope as a signal_slope_type.
             */
            DLL_EXPORT signal_slope_type Slope( ) const;

            /**
             * \brief Return the offset of the channel.
             * \return The offset as a signal_offset_type.
             */
            DLL_EXPORT signal_offset_type Offset( ) const;

            /**
             * \brief Return the units of this channel.
             * \return The units as a string.
             */
            DLL_EXPORT const std::string& Units( ) const;

            /**
             * \brief Swap this channel with another.
             * \details Switches all values of this channel with the input
             * channel
             * Source.
             * \param[in,out] Source A channel to swap values with.
             */
            DLL_EXPORT void swap( channel& Source );

            /**
             * \brief Check the channel name to see if it is a second trend.
             * \param[in] Name A channel name, as a string.
             * \return true if Name ends in ",s-trend", else false.
             */
            DLL_EXPORT static bool IsSecondTrend( const std::string& Name );

            /**
             * \brief Check the channel name to see if it is a minute trend.
             * \param[in] Name A channel name, as a string.
             * \return true if Name ends in ",m-trend", else false.
             */
            DLL_EXPORT static bool IsMinuteTrend( const std::string& Name );

        private:
            std::string        name;
            channel_type       type;
            data_type          data;
            sample_rate_type   sample_rate;
            signal_gain_type   gain;
            signal_slope_type  slope;
            signal_offset_type offset;
            std::string        units;
        };

        typedef std::vector< channel > channels_type;

        inline const void*
        channel::hash_type::ref( ) const
        {
            return ( ( size( ) > 0 ) ? &( this->operator[]( 0 ) ) : zero_hash );
        }

        inline const std::string&
        channel::Name( ) const
        {
            return name;
        }

        inline channel::channel_type
        channel::Type( ) const
        {
            return type;
        }

        inline channel::data_type
        channel::DataType( ) const
        {
            return data;
        }

        inline channel::size_type
        channel::DataTypeSize( ) const
        {
            switch ( data )
            {
            case DATA_TYPE_INT16:
                return ( 2 );
                break;
            case DATA_TYPE_INT32:
            case DATA_TYPE_FLOAT32:
            case DATA_TYPE_UINT32:
                return ( 4 );
                break;
            case DATA_TYPE_INT64:
            case DATA_TYPE_FLOAT64:
            case DATA_TYPE_COMPLEX32:
                return ( 8 );
                break;
            default:
                return 0;
            }
        }

        inline channel::sample_rate_type
        channel::SampleRate( ) const
        {
            return sample_rate;
        }

        inline channel::signal_gain_type
        channel::Gain( ) const
        {
            return gain;
        }

        inline channel::signal_slope_type
        channel::Slope( ) const
        {
            return slope;
        }

        inline channel::signal_offset_type
        channel::Offset( ) const
        {
            return offset;
        }

        inline const std::string&
        channel::Units( ) const
        {
            return units;
        }

        inline bool
        channel::IsSecondTrend( const std::string& Name )
        {
            static const std::string STREND_EXT( ",s-trend" );

            if ( Name.size( ) <= STREND_EXT.size( ) )
            {
                return false;
            }
            return ( STREND_EXT.compare( Name.substr(
                         Name.size( ) - STREND_EXT.size( ) ) ) == 0 );
        }

        inline bool
        channel::IsMinuteTrend( const std::string& Name )
        {
            static const std::string MTREND_EXT( ",m-trend" );

            if ( Name.size( ) <= MTREND_EXT.size( ) )
            {
                return false;
            }
            return ( MTREND_EXT.compare( Name.substr(
                         Name.size( ) - MTREND_EXT.size( ) ) ) == 0 );
        }

        DLL_EXPORT extern std::ostream& operator<<( std::ostream&  os,
                                                    const channel& ch );

        /** \brief Given a C++ data type, determine which NDS channel data type
         * applies to it
         * @tparam T The type to check.
         * @details This is used by template code to map between the C++ type
         * system and the NDS channel types.  For example to find the type
         * associated with an std::int32_t you would do:
        \code
            NDS::channel::data_type value_type =
        NDS::channel_data_type_conversion<std::int_32>::value;
            // in this case value_type == NDS::channel::DATA_TYPE_INT32
        \endcode
         * When types do not match, they are mapped to DATA_TYPE_UNKOWN
        \code
            const auto val =
        NDS::channel_data_type_conversion<NDS::connection>::value;
            // This does not make sense, so it maps to DATA_TYPE_UNKOWN
        \endcode
         */
        template < typename T >
        struct channel_data_type_conversion
        {
            static const NDS::channel::data_type value =
                NDS::channel::DATA_TYPE_UNKNOWN;
        };

        template <>
        struct channel_data_type_conversion< std::int16_t >
        {
            static const NDS::channel::data_type value =
                NDS::channel::DATA_TYPE_INT16;
        };

        template <>
        struct channel_data_type_conversion< std::int32_t >
        {
            static const NDS::channel::data_type value =
                NDS::channel::DATA_TYPE_INT32;
        };

        template <>
        struct channel_data_type_conversion< std::int64_t >
        {
            static const NDS::channel::data_type value =
                NDS::channel::DATA_TYPE_INT64;
        };

        template <>
        struct channel_data_type_conversion< float >
        {
            static const NDS::channel::data_type value =
                ( NDS::channel::DATA_TYPE_FLOAT32 );
        };

        template <>
        struct channel_data_type_conversion< double >
        {
            static const NDS::channel::data_type value =
                NDS::channel::DATA_TYPE_FLOAT64;
        };

        template <>
        struct channel_data_type_conversion< std::complex< float > >
        {
            static const NDS::channel::data_type value =
                ( NDS::channel::DATA_TYPE_COMPLEX32 );
        };

        template <>
        struct channel_data_type_conversion< std::uint32_t >
        {
            static const NDS::channel::data_type value =
                NDS::channel::DATA_TYPE_UINT32;
        };

        DLL_EXPORT const std::string&
        channel_type_to_string( channel::channel_type ctype );

        DLL_EXPORT const std::string&
        data_type_to_string( channel::data_type dtype );
    }
} // namespace - NDS

#endif /* SWIG__COMMON__NDS_CHANNEL_HH */
