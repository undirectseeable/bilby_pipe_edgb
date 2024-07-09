#ifndef SWIG__COMMON__NDS_EPOCH_HH
#define SWIG__COMMON__NDS_EPOCH_HH

#include <memory>
#include <string>
#include <ostream>
#include <utility>
#include <vector>

#include <iostream>

namespace NDS
{
    inline namespace abi_0
    {
        class epoch
        {
        public:
            std::string             name;
            buffer::gps_second_type gps_start;
            buffer::gps_second_type gps_stop;

            epoch( ) : name( "" ), gps_start( 0 ), gps_stop( 0 ){};
            epoch( const std::string& name )
                : name( name ), gps_start( 0 ), gps_stop( 0 ){};
            epoch( buffer::gps_second_type start, buffer::gps_second_type stop )
                : name( "" ), gps_start( start ), gps_stop( stop )
            {
            }
            epoch( const std::string&      name,
                   buffer::gps_second_type start,
                   buffer::gps_second_type stop )
                : name( name ), gps_start( start ), gps_stop( stop ){};
            epoch( const epoch& other ) = default;
            ;
            ~epoch( ) = default;
            ;
        };

        inline std::ostream&
        operator<<( std::ostream& os, const epoch& obj )
        {
            os << "< epoch ";
            if ( obj.name == "" )
            {
                os << obj.gps_start << "-" << obj.gps_stop;
            }
            else
            {
                os << obj.name;
            }
            os << " >";
            return os;
        }

        typedef std::vector< epoch > epochs_type;

        inline std::ostream&
        operator<<( std::ostream& os, const epochs_type& obj )
        {
            os << "(";
            epochs_type::const_iterator cur = obj.begin( );
            for ( ; cur != obj.end( ); ++cur )
            {
                os << " " << *cur << ",";
            }
            os << " )";
            return os;
        }
    }
}

#endif
