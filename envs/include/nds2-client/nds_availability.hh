/* -*- mode: C++ ; c-basic-offset: 2; indent-tabs-mode: nil -*- */

#ifndef SWIG__COMMON__NDS_AVAILABLILITY_HH
#define SWIG__COMMON__NDS_AVAILABLILITY_HH

#include <algorithm>
#include <iterator>
#include <memory>
#include <string>
#include <ostream>
#include <vector>

#include "nds_export.hh"
#include "nds_channel.hh"
#include "nds_buffer.hh"

namespace NDS
{
    inline namespace abi_0
    {
        /**
         * \brief An availability segment defines when data is available.
         * \details LIGO data is not always avaialble.  Channels are added,
         * removed,
         * the data collection services or the instrument have downtime.  This
         * structure holds information about a time span when data is available.
         *
         * An individual segment holds data on when a channel (not specified in
         * the
         * structure) was available in a  specific frame type in a given
         * [start,stop) time frame.
         *
         * \remark This information is only available for NDSv2
         *
         * \headerfile nds.hh nds.hh
         */
        struct segment
        {
            DLL_EXPORT segment( );

            DLL_EXPORT segment( NDS::buffer::gps_second_type gps_start,
                                NDS::buffer::gps_second_type gps_stop );

            DLL_EXPORT segment( std::string                  frame_type,
                                NDS::buffer::gps_second_type gps_start,
                                NDS::buffer::gps_second_type gps_stop );

            std::string frame_type; ///< The ldas supplied frame type
            NDS::buffer::gps_second_type
                gps_start; ///< The start time for this segment
            NDS::buffer::gps_second_type
                gps_stop; ///< The second after the end time
        };

        /**
         * \brief A simple [start,stop) range for denoting segments
         */
        struct simple_segment
        {
            typedef NDS::buffer::gps_second_type gps_second_type;

            DLL_EXPORT simple_segment( );

            DLL_EXPORT simple_segment( const simple_segment& other );

            DLL_EXPORT simple_segment( gps_second_type start,
                                       gps_second_type stop );

            DLL_EXPORT simple_segment& operator=( const simple_segment& other );

            gps_second_type gps_start;
            gps_second_type gps_stop;
        };

        /**
     * \brief A list of simple segments.  This does not contain the channel
     * name.
     */
        class simple_segment_list_type : public std::vector< simple_segment >
        {
        public:
        };

        /**
    * \brief A list of simple availability lists
    */
        class simple_availability_list_type
            : public std::vector< simple_segment_list_type >
        {
        public:
        };

        /**
    * \brief A list of detailed segments.  This does not contain the channel
    * name.
    */
        class segment_list_type : public std::vector< segment >
        {
        public:
        };

        /**
    * \brief Availability information for a channel.
    * \details This contains a channel name, and a list of segments in which
    * the data is available.
    */
        struct availability
        {
            std::string name; ///< The channel name

            /// \brief The full availability list, with full frame type
            /// information.
            ///
            segment_list_type data;

            /**
             * \brief Get a simple time span list of availability.
             * \return A simple_segment_list_type list.
             */
            DLL_EXPORT simple_segment_list_type simple_list( ) const;
        };

        /**
    * \brief A list of availabilitys (channels, availability segments)
    */
        class availability_list_type : public std::vector< availability >
        {
        public:
            DLL_EXPORT simple_availability_list_type simple_list( ) const;
        };

        DLL_EXPORT extern std::ostream& operator<<( std::ostream&  os,
                                                    const segment& obj );

        DLL_EXPORT std::ostream& operator<<( std::ostream&         os,
                                             const simple_segment& obj );

        DLL_EXPORT extern std::ostream&
        operator<<( std::ostream& os, const simple_segment_list_type& obj );

        DLL_EXPORT extern std::ostream&
        operator<<( std::ostream&                        os,
                    const simple_availability_list_type& obj );

        DLL_EXPORT extern std::ostream&
        operator<<( std::ostream& os, const segment_list_type& obj );

        DLL_EXPORT extern std::ostream& operator<<( std::ostream&       os,
                                                    const availability& obj );

        DLL_EXPORT extern std::ostream&
        operator<<( std::ostream& os, const availability_list_type& obj );
    }
}

#endif
