//
// LDASTools frameCPP - A library implementing the LIGO/Virgo frame
// specification
//
// Copyright (C) 2019 California Institute of Technology
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

#ifndef FrameCPP_VERSION_8__IMPL__FrVectData_HH
#define FrameCPP_VERSION_8__IMPL__FrVectData_HH

#if !defined( SWIGIMPORTED )
#include <memory>
#include <vector>
#include <string>

#include <boost/shared_array.hpp>
#endif /* ! defined(SWIGIMPORTED) */

#if !defined( SWIGIMPORTED )
#include "ldastoolsal/types.hh"

#include "framecpp/Common/Compression.hh"
#include "framecpp/Common/FrVect.hh"

#include "framecpp/Version7/FrVect.hh"

#include "framecpp/Version8/impl/FrObjectMetaData.hh"

#include "framecpp/Version8/FrameSpec.hh"
#include "framecpp/Version8/Dimension.hh"
#include "framecpp/Version8/GPSTime.hh"
#endif /* ! defined(SWIGIMPORTED)*/

#undef FR_VECT_COMPRESS_TYPE
#undef FR_VECT_TYPE_TYPE
#undef FR_VECT_NDATA_TYPE
#undef FR_VECT_NBYTES_TYPE
#undef FR_VECT_NDIM_TYPE
#undef FR_VECT_COMPRESSION_LEVEL_TYPE

#define FR_VECT_COMPRESS_TYPE INT_2U
#define FR_VECT_TYPE_TYPE INT_2U
#define FR_VECT_NDATA_TYPE INT_8U
#define FR_VECT_NBYTES_TYPE INT_8U
#define FR_VECT_NDIM_TYPE INT_4U
#define FR_VECT_COMPRESSION_LEVEL_TYPE int

#if !defined( SWIGIMPORTED )
namespace FrameCPP
{
    namespace Version_8
    {
        using Previous::FrVectDataTypes;

        namespace FrVectImpl
        {
            class Data : public Impl::FrObjectMetaData< Data >,
                         public Common::FrVect,
                         public FrVectDataTypes
            {
            public:
                enum compression_scheme_type
                {
                //---------------------------------------------------------
                //---------------------------------------------------------

#if WORDS_BIGENDIAN
#define NATIVE_DECL( x ) x = BIGENDIAN_##x
#else
#define NATIVE_DECL( x ) x = LITTLEENDIAN_##x
#endif
#define CST_DECL( x, y )                                                       \
    BIGENDIAN_##x = y, LITTLEENDIAN_##x = y + 256, NATIVE_DECL( x )

                    CST_DECL( RAW, 0 ),
                    CST_DECL( GZIP, 1 ),
                    CST_DECL( DIFF_GZIP, 3 ),
                    CST_DECL( ZERO_SUPPRESS_WORD_2, 5 ),
                    CST_DECL( ZERO_SUPPRESS_WORD_4, 8 ),
                    CST_DECL( ZERO_SUPPRESS_WORD_8, 10 ),

#undef CST_DECL
#undef NATIVE_DECL

                    //---------------------------------------------------------
                    // Declaration of meta modes
                    //---------------------------------------------------------
                    ZERO_SUPPRESS_OTHERWISE_GZIP = 6,
                    BEST_COMPRESSION = 9,

                    //---------------------------------------------------------
                    // Backwards compatability
                    //---------------------------------------------------------
                    ZERO_SUPPRESS_SHORT = ZERO_SUPPRESS_WORD_2,
                    ZERO_SUPPRESS_INT_FLOAT = ZERO_SUPPRESS_WORD_4,
#undef GENERIC
                    NONE = RAW
                };

                enum data_types_type
                {
                    FR_VECT_C = 0,
                    FR_VECT_2S = 1,
                    FR_VECT_8R = 2,
                    FR_VECT_4R = 3,
                    FR_VECT_4S = 4,
                    FR_VECT_8S = 5,
                    FR_VECT_8C = 6,
                    FR_VECT_16C = 7,
                    FR_VECT_STRING = 8,
                    FR_VECT_2U = 9,
                    FR_VECT_4U = 10,
                    FR_VECT_8U = 11,
                    FR_VECT_1U = 12
                };

                typedef std::string                    name_type;
                typedef std::string                    unit_y_type;
                typedef FR_VECT_COMPRESS_TYPE          compress_type;
                typedef FR_VECT_COMPRESSION_LEVEL_TYPE compression_level_type;
                typedef FR_VECT_TYPE_TYPE              type_type;
                typedef FR_VECT_NDATA_TYPE             nData_type;
                typedef FR_VECT_NBYTES_TYPE            nBytes_type;
                typedef FR_VECT_NDIM_TYPE              nDim_type;
                typedef boost::shared_array< CHAR_U >  data_type;
                typedef data_type::element_type        data_element_type;
                typedef data_element_type*             data_pointer_type;
                typedef const data_element_type*       data_const_pointer_type;
                typedef std::vector< Dimension >       dimension_container_type;
                static const constexpr int             DEFAULT_GZIP_LEVEL = 6;

                virtual ~Data( )
                {
                }

                virtual Compression::compression_base_type
                Compression( ) const
                {
                    return ( 0x0FF & m_data.compress );
                }

                virtual void
                CompressData( INT_4U Scheme, INT_2U Level )
                {
                    Compress( compression_scheme_type( Scheme ), Level );
                }

                //-----------------------------------------------------------------
                /// \brief Allocate a block of memory suitable for storing data.
                ///
                /// \param[in] Type
                ///     The type of data that is to be stored in the buffer.
                /// \param[in] Dims
                ///     Information concearning each dimension of the array
                ///     of data to be stored in the buffer.
                /// \param[in] NDim
                ///     The number of dimensions of data to be stored in the
                ///     buffer
                ///
                /// \return
                ///     Upon successful allocation, an appropriated sized buffer
                ///     is returned.
                ///     An expection is thrown for all error conditions.
                //-----------------------------------------------------------------
                static data_type
                DataAlloc( type_type        Type,
                           const Dimension* Dims,
                           const nDim_type  NDim = 1 )
                {
                    data_type retval;
                    nDim_type dsize = 1;

                    for ( nDim_type x = 0; x < NDim; ++x )
                    {
                        dsize *= Dims[ x ].GetNx( );
                    }
                    switch ( Type )
                    {
                    case FR_VECT_C:
                        retval.reset( reinterpret_cast< data_pointer_type >(
                            new CHAR[ dsize ] ) );
                        break;
                    case FR_VECT_1U:
                        retval.reset( reinterpret_cast< data_pointer_type >(
                            new CHAR_U[ dsize ] ) );
                        break;
                    case FR_VECT_2S:
                        retval.reset( reinterpret_cast< data_pointer_type >(
                            new INT_2S[ dsize ] ) );
                        break;
                    case FR_VECT_2U:
                        retval.reset( reinterpret_cast< data_pointer_type >(
                            new INT_2U[ dsize ] ) );
                        break;
                    case FR_VECT_4S:
                        retval.reset( reinterpret_cast< data_pointer_type >(
                            new INT_4S[ dsize ] ) );
                        break;
                    case FR_VECT_4U:
                        retval.reset( reinterpret_cast< data_pointer_type >(
                            new INT_4U[ dsize ] ) );
                        break;
                    case FR_VECT_8S:
                        retval.reset( reinterpret_cast< data_pointer_type >(
                            new INT_8S[ dsize ] ) );
                        break;
                    case FR_VECT_8U:
                        retval.reset( reinterpret_cast< data_pointer_type >(
                            new INT_8U[ dsize ] ) );
                        break;
                    case FR_VECT_4R:
                        retval.reset( reinterpret_cast< data_pointer_type >(
                            new REAL_4[ dsize ] ) );
                        break;
                    case FR_VECT_8R:
                        retval.reset( reinterpret_cast< data_pointer_type >(
                            new REAL_8[ dsize ] ) );
                        break;
                    case FR_VECT_8C:
                        retval.reset( reinterpret_cast< data_pointer_type >(
                            new REAL_4[ dsize * 2 ] ) );
                        break;
                    case FR_VECT_16C:
                        retval.reset( reinterpret_cast< data_pointer_type >(
                            new REAL_8[ dsize * 2 ] ) );
                        break;
                        /*
                          ????
                          case FR_VECT_STR:
                          return sizeof( std::std::string );
                          ????
                        */
                    }

                    return retval;
                }

                //-----------------------------------------------------------------
                /// \brief Retrieve the channel name.
                ///
                /// \return
                ///     The channel name
                //-----------------------------------------------------------------
                const name_type&
                GetName( ) const
                {
                    return m_data.name;
                }

                //-----------------------------------------------------------------
                /// \brief Retrieve the compression algorithm number.
                ///
                /// \return
                ///     The compression algorithm number.
                //-----------------------------------------------------------------
                compress_type
                GetCompress( ) const
                {
                    return m_data.compress;
                }

                //-----------------------------------------------------------------
                /// \brief Retrieve the vector class.
                ///
                /// \return
                ///     The vector class.
                //-----------------------------------------------------------------
                type_type
                GetType( ) const
                {
                    return m_data.type;
                }

                //-----------------------------------------------------------------
                //-----------------------------------------------------------------
                size_t
                GetTypeSize( ) const
                {
                    return GetTypeSize( m_data.type );
                }

                //-----------------------------------------------------------------
                /// \brief Get size of single data point of particular size.
                ///
                /// \param[in] Type
                ///     Data type ID.
                ///
                /// \return
                ///     Data size.
                //-----------------------------------------------------------------
                static size_t
                GetTypeSize( type_type Type )
                {
                    switch ( Type )
                    {
                    case FR_VECT_C:
                        return sizeof( CHAR );
                    case FR_VECT_2S:
                        return sizeof( INT_2S );
                    case FR_VECT_8R:
                        return sizeof( REAL_8 );
                    case FR_VECT_4R:
                        return sizeof( REAL_4 );
                    case FR_VECT_4S:
                        return sizeof( INT_4S );
                    case FR_VECT_8S:
                        return sizeof( INT_8S );
                    case FR_VECT_8C:
                        return ( sizeof( REAL_4 ) * 2 );
                    case FR_VECT_16C:
                        return ( sizeof( REAL_8 ) * 2 );
                        /*
                          ????
                          case FR_VECT_STR:
                          return sizeof( std::std::string );
                          ????
                        */
                    case FR_VECT_2U:
                        return sizeof( INT_2U );
                    case FR_VECT_4U:
                        return sizeof( INT_4U );
                    case FR_VECT_8U:
                        return sizeof( INT_8U );
                    case FR_VECT_1U:
                        return sizeof( CHAR_U );
                    }
                    // None of above: Perhaps add type for throw?
                    return 0;
                }

                //-----------------------------------------------------------------
                /// \brief Retrieve the number of sample elements in data
                /// series.
                ///
                /// \return
                ///     The number of sample elements in data series.
                //-----------------------------------------------------------------
                nData_type
                GetNData( ) const
                {
                    return m_data.nData;
                }

                //-----------------------------------------------------------------
                /// \brief Retrieve the number of bytes in the compressed
                /// vector.
                ///
                /// \return
                ///     The number of bytes in the compressed vector.
                //-----------------------------------------------------------------
                nBytes_type
                GetNBytes( ) const
                {
                    return m_data.nBytes;
                }

                //-----------------------------------------------------------------
                /// \brief Retrieve the pointer to the data.
                ///
                /// Return a pointer to the data being managed by the FrVect
                /// structure.
                ///
                /// \return
                ///     The pointer to the data.
                ///
                /// \note
                ///     This will expand the data if it is currently compressed.
                ///
                /// \see GetDataRaw, GetDataUncompressed
                //-----------------------------------------------------------------
                data_type
                GetData( ) const
                {
                    return GetDataRaw( );
                }

                //-----------------------------------------------------------------
                /// \brief Retrieve the pointer to the compressed data.
                ///
                /// \return
                ///     The pointer to the compressed data.
                //-----------------------------------------------------------------
                data_type
                GetDataRaw( ) const
                {
                    return m_data.data;
                }

                //-----------------------------------------------------------------
                /// \brief Retrieve the pointer to the compressed data.
                ///
                /// \return
                ///     The pointer to the compressed data.
                //-----------------------------------------------------------------
                data_type
                GetDataRaw( )
                {
                    return m_data.data;
                }

                //-----------------------------------------------------------------
                /// \brief Retrieve the pointer to the uncompressed data.
                ///
                /// \return
                ///     The pointer to the uncompressed data.
                //-----------------------------------------------------------------
                data_type
                GetDataUncompressed( )
                {
                    Uncompress( );

                    return m_data.data;
                }

                //-----------------------------------------------------------------
                /// \brief Retrieve the pointer to the uncompressed data.
                ///
                /// \param[in] Expanded
                ///     Buffer into which the data is expanded.
                ///
                /// \return
                ///     The pointer to the uncompressed data.
                //-----------------------------------------------------------------
                const CHAR_U*
                GetDataUncompressed( data_type& Expanded ) const
                {
                    nBytes_type nBytes( 0 );

                    expandToBuffer( Expanded, nBytes );
                    if ( nBytes == 0 )
                    {
                        return m_data.data.get( );
                    }

                    return Expanded.get( );
                }

                template < class T >
                static type_type GetDataType( );

                //-----------------------------------------------------------------
                /// \brief Retrieve the number of dimensions
                ///
                /// \return
                ///     The number of dimensions
                //-----------------------------------------------------------------
                nDim_type
                GetNDim( ) const
                {
                    return m_data.dimension.size( );
                }

                //-----------------------------------------------------------------
                /// \brief Retrieve the Nth dimension
                ///
                /// \param[in] Offset
                ///     Index for desired dimension
                ///
                /// \return
                ///     The Nth dimension
                //-----------------------------------------------------------------
                const Dimension&
                GetDim( nDim_type Offset ) const
                {
                    /// \todo
                    ///   Throw exception if value out of range
                    return m_data.dimension[ Offset ];
                }

                //-----------------------------------------------------------------
                /// \brief Retrieve the Nth dimension
                ///
                /// \param[in] Offset
                ///     Index for desired dimension
                ///
                /// \return
                ///     The Nth dimension
                //-----------------------------------------------------------------
                Dimension&
                GetDim( nDim_type Offset )
                {
                    /// \todo
                    ///   Throw exception if value out of range
                    return m_data.dimension[ Offset ];
                }

                //-----------------------------------------------------------------
                /// \brief Retrieve all the dimension information
                ///
                /// \return
                ///     The colletion of dimension data
                //-----------------------------------------------------------------
                dimension_container_type&
                GetDims( )
                {
                    return m_data.dimension;
                }

                //-----------------------------------------------------------------
                /// \brief Retrieve the description of how to interpret each
                /// element
                ///
                /// \return
                ///     The description of how to interpret each element
                //-----------------------------------------------------------------
                const unit_y_type&
                GetUnitY( ) const
                {
                    return m_data.unitY;
                }

                void
                Compress( compression_scheme_type Scheme, int Level )
                {
                    if ( Scheme == GetCompress( ) )
                    {
                        // Nothing to do. Just return
                        return;
                    }

                    //---------------------------------------------------------------------
                    // Uncompress the data first
                    //---------------------------------------------------------------------
                    Uncompress( );

                    //---------------------------------------------------------------------
                    // Compress the data
                    //---------------------------------------------------------------------

                    INT_4U                        compress = ( Scheme & 0xFF );
                    const INT_8U                  nData( m_data.nData );
                    const INT_8U                  nBytes( m_data.nBytes );
                    boost::shared_array< CHAR_U > data_out( (CHAR_U*)NULL );
                    INT_8U                        data_out_len( 0 );

                    FrameCPP::Compression::Compress(
                        compress,
                        Level,
                        compress_type_map( ),
                        compress_type_reverse_map( ),
                        GetType( ),
                        data_type_map( ),
                        m_data.data.get( ),
                        nData,
                        nBytes,
                        data_out,
                        data_out_len );

                    if ( data_out && data_out_len )
                    {
                        //-------------------------------------------------------------------
                        // Save the compressed data
                        //-------------------------------------------------------------------
                        m_data.nBytes = nBytes_type( data_out_len );
                        m_data.data = data_out;
                        //-------------------------------------------------------------------
                        // Save the compression mode
                        //-------------------------------------------------------------------
                        m_data.compress =
                            ( MODE_HOSTENDIAN | ( compress & 0xFF ) );
                    }
                }

                //-----------------------------------------------------------------------------
                /// \brief Expand compressed data.
                ///
                /// In general, uncompressing follows three steps:
                ///
                /// 1) Gunzip the data.
                /// 2) Fix byte-ordering.
                /// 3) Integrate.
                ///
                /// Depending upon the compression type and byte-ordering
                /// differences, not all of these steps are needed.
                void
                Uncompress( )
                {
                    //---------------------------------------------------------------------
                    // Check if there is anything that needs to be done
                    //---------------------------------------------------------------------
                    if ( GetCompress( ) == RAW )
                    {
                        // Nothing to do. The buffer is already uncompressed
                        return;
                    }

                    //---------------------------------------------------------------------
                    // There is something to be done
                    //---------------------------------------------------------------------
                    nBytes_type nBytes( m_data.nBytes );
                    data_type   expanded_buffer;

                    expandToBuffer( expanded_buffer, nBytes );

                    //---------------------------------------------------------------------
                    // Now record what has been done
                    //---------------------------------------------------------------------
                    if ( expanded_buffer.get( ) )
                    {
                        /* Transfer ownership */
                        m_data.data = expanded_buffer;
                        m_data.nBytes = nBytes_type( nBytes );
                        m_data.compress = RAW;
                    }
                }

                //-----------------------------------------------------------------
                /// \brief Set the current FrVect with the MIME data
                //-----------------------------------------------------------------
                void
                MimeData( const std::string& MimeType,
                          void*              Data,
                          nBytes_type        DataSize )
                {
                    //---------------------------------------------------------------------
                    // Setup dimension information
                    //---------------------------------------------------------------------
                    SetUnitY( MIME_TYPE_KEYWORD );
                    GetDims( ).erase( GetDims( ).begin( ), GetDims( ).end( ) );
                    GetDims( ).push_back( Dimension( MIME_TYPE_NX,
                                                     MIME_TYPE_DX,
                                                     MimeType,
                                                     MIME_TYPE_START_X ) );
                    //---------------------------------------------------------------------
                    // Fill data field with the blob
                    //---------------------------------------------------------------------
                    data_copy( (data_element_type*)Data, DataSize );
                }

                //-----------------------------------------------------------------
                /// \brief Establish the channel name.
                ///
                /// Assign a new value for the channel name.
                ///
                /// \param[in] Name
                ///     The channel name
                //-----------------------------------------------------------------
                void
                SetName( const name_type& Name )
                {
                    m_data.name = Name;
                }

                //-----------------------------------------------------------------
                /// \brief Set the description of how to interpret each element
                ///
                /// Assign a new value for the channel name.
                ///
                /// \param[in] UnitY
                ///     New description
                ///
                /// \return
                ///     The description of how to interpret each element
                //-----------------------------------------------------------------
                void
                SetUnitY( const unit_y_type& UnitY )
                {
                    m_data.unitY = UnitY;
                }

                //-----------------------------------------------------------------
                //-----------------------------------------------------------------
                void
                SetNData( nData_type NData )
                {
                    m_data.nData = NData;
                }

            protected:
                enum
                {
                    MODE_RAW = BIGENDIAN_RAW,
                    MODE_GZIP = BIGENDIAN_GZIP,
                    MODE_DIFF_GZIP = BIGENDIAN_DIFF_GZIP,
                    MODE_ZERO_SUPPRESS_WORD_2 = BIGENDIAN_ZERO_SUPPRESS_WORD_2,
                    MODE_ZERO_SUPPRESS_WORD_4 = BIGENDIAN_ZERO_SUPPRESS_WORD_4,
                    MODE_ZERO_SUPPRESS_WORD_8 = BIGENDIAN_ZERO_SUPPRESS_WORD_8
                };

                enum
                {
                    MODE_BIGENDIAN = BIGENDIAN_RAW,
                    MODE_LITTLEENDIAN = LITTLEENDIAN_RAW,
                    MODE_HOSTENDIAN = RAW
                };

                static FrameCPP::Compression::compress_type_mapping&
                compress_type_map( )
                {
                    static FrameCPP::Compression::compress_type_mapping m;

                    if ( m.size( ) == 0 )
                    {

#define INIT( x, y ) m[ Data::BIGENDIAN_##x ] = FrameCPP::Compression::y

                        INIT( RAW, MODE_RAW );
                        INIT( GZIP, MODE_GZIP );
                        INIT( DIFF_GZIP, MODE_DIFF_GZIP );
                        INIT( ZERO_SUPPRESS_WORD_2, MODE_ZERO_SUPPRESS_SHORT );
                        INIT( ZERO_SUPPRESS_WORD_4, MODE_ZERO_SUPPRESS_WORD_4 );
                        INIT( ZERO_SUPPRESS_WORD_8, MODE_ZERO_SUPPRESS_WORD_8 );

#undef INIT
#define INIT( x, y ) m[ Data::x ] = FrameCPP::Compression::y

                        INIT( ZERO_SUPPRESS_OTHERWISE_GZIP,
                              MODE_ZERO_SUPPRESS_2_4_8_OTHERWISE_GZIP );
                    }

#undef INIT
                    return m;
                }

                static FrameCPP::Compression::compress_type_reverse_mapping&
                compress_type_reverse_map( )
                {
                    static FrameCPP::Compression::compress_type_reverse_mapping
                        m;

                    if ( m.size( ) == 0 )
                    {

#define INIT( x, y ) m[ FrameCPP::Compression::x ] = Data::BIGENDIAN_##y;

                        INIT( MODE_RAW, RAW );
                        INIT( MODE_GZIP, GZIP );
                        INIT( MODE_DIFF_GZIP, DIFF_GZIP );
                        INIT( MODE_ZERO_SUPPRESS_SHORT, ZERO_SUPPRESS_WORD_2 );
                        INIT( MODE_ZERO_SUPPRESS_WORD_4, ZERO_SUPPRESS_WORD_4 );
                        INIT( MODE_ZERO_SUPPRESS_WORD_8, ZERO_SUPPRESS_WORD_8 );

                        INIT( MODE_ZERO_SUPPRESS_INT_FLOAT,
                              ZERO_SUPPRESS_WORD_4 );
#undef INIT
                    }
                    return m;
                }

                void
                data_alloc( nBytes_type NBytes )
                {
                    m_data.data.reset( new CHAR_U[ NBytes ] );
                    m_data.nBytes = NBytes;
                }

                void
                data_copy( data_const_pointer_type Data, nBytes_type NBytes )
                {
                    if ( ( NBytes == 0 ) ||
                         ( Data == (const data_pointer_type)NULL ) )
                    {
                        m_data.data.reset( );
                    }
                    else
                    {
                        if ( ( m_data.nBytes != NBytes ) || ( !m_data.data ) )
                        {
                            m_data.data.reset( new CHAR_U[ NBytes ] );
                            m_data.nBytes = NBytes;
                        }
                        std::copy( Data, Data + NBytes, m_data.data.get( ) );
                    }
                }

                static FrameCPP::Compression::data_type_mapping&
                data_type_map( )
                {
                    static FrameCPP::Compression::data_type_mapping m;

                    if ( m.size( ) == 0 )
                    {
#define INIT( x ) m[ Data::x ] = FrameCPP::Compression::x

                        INIT( FR_VECT_C );
                        INIT( FR_VECT_2S );
                        INIT( FR_VECT_8R );
                        INIT( FR_VECT_4R );
                        INIT( FR_VECT_4S );
                        INIT( FR_VECT_8S );
                        INIT( FR_VECT_8C );
                        INIT( FR_VECT_16C );
                        INIT( FR_VECT_STRING );
                        INIT( FR_VECT_2U );
                        INIT( FR_VECT_4U );
                        INIT( FR_VECT_8U );
                        INIT( FR_VECT_1U );

#undef INIT
                    }
                    return m;
                }

                void
                expandToBuffer( data_type& Dest, nBytes_type& DestNBytes ) const
                {
                    Common::FrVect::expandToBuffer(
                        compress_type_map( ),
                        data_type_map( ),
                        GetType( ),
                        GetNData( ),
                        GetDataRaw( ).get( ),
                        GetNBytes( ),
                        GetCompress( ),
                        ( ( GetCompress( ) & 0x100 ) ? BYTE_ORDER_LITTLE_ENDIAN
                                                     : BYTE_ORDER_BIG_ENDIAN ),
                        Dest,
                        DestNBytes );
                }

                struct data_definition_type
                {
                public:
                    //---------------------------------------------------------------
                    /// Channel name.
                    ///
                    /// \note
                    ///     Not required to be unique.
                    //---------------------------------------------------------------
                    name_type name;
                    //---------------------------------------------------------------
                    /// Compression algorithm number
                    //---------------------------------------------------------------
                    compress_type compress;
                    //---------------------------------------------------------------
                    /// Vector class
                    //---------------------------------------------------------------
                    type_type type;
                    //---------------------------------------------------------------
                    /// Number of sample elements in data series.
                    //---------------------------------------------------------------
                    nData_type nData;
                    //---------------------------------------------------------------
                    /// Number of bytes in the compressed vector.
                    //---------------------------------------------------------------
                    nBytes_type nBytes;
                    //---------------------------------------------------------------
                    /// Compressed data series.
                    //---------------------------------------------------------------
                    data_type data;
                    //---------------------------------------------------------------
                    /// Dimension data for data series.
                    //---------------------------------------------------------------
                    dimension_container_type dimension;
                    //---------------------------------------------------------------
                    /// String describing how to interpret the value of each
                    /// element.
                    //---------------------------------------------------------------
                    unit_y_type unitY;

                    data_definition_type( )
                        : name( "" ), compress( RAW ), type( FR_VECT_C ),
                          nData( 0 ), nBytes( 0 ), dimension( ), unitY( "" )
                    {
                    }

                    data_definition_type( const std::string&    n,
                                          INT_2U                t,
                                          const byte_order_type byte_order,
                                          nDim_type             ndim,
                                          const Dimension*      dims,
                                          const std::string&    unit )
                    {
                        set( n, t, byte_order, ndim, dims, unit );
                    }

                    void
                    copy_core( const data_definition_type& Source )
                    {
                        name = Source.name;
                        compress = Source.compress;
                        type = Source.type;
                        nData = Source.nData;
                        nBytes = Source.nBytes;

                        for ( std::vector< Dimension >::const_iterator
                                  d( Source.dimension.begin( ) ),
                              d_end( Source.dimension.end( ) );
                              d != d_end;
                              ++d )
                        {
                            dimension.push_back( *d );
                        }

                        unitY = Source.unitY;
                    }

                    static FrameCPP::cmn_streamsize_type
                    calc_nData( const std::vector< Dimension >& Dimensions )
                    {
                        FrameCPP::cmn_streamsize_type ret( 0 );

                        if ( Dimensions.size( ) > 0 )
                        {
                            ret = 1;
                            for ( std::vector< Dimension >::const_iterator i(
                                      Dimensions.begin( ) );
                                  i != Dimensions.end( );
                                  i++ )
                            {
                                ret *= ( *i ).GetNx( );
                            }
                        }
                        return ret;
                    }

                    void
                    set( const std::string&    n,
                         INT_2U                t,
                         const byte_order_type byte_order,
                         nDim_type             ndim,
                         const Dimension*      dims,
                         const std::string&    unit )
                    {
                        name = n;
                        type = t;
                        unitY = unit;
                        compress = RAW;

                        for ( nDim_type x = 0; x < ndim; ++x, ++dims )
                        {
                            dimension.push_back( *dims );
                        }

                        nData = calc_nData( dimension );
                        nBytes = GetTypeSize( type ) * nData;
                    }

                    bool
                    operator==( const data_definition_type& RHS ) const
                    {
#if LM_INFO
                        if ( name != RHS.name )
                        {
                            std::cerr << "DEBUG: " << __LINE__ << std::endl;
                        }
                        if ( compress != RHS.compress )
                        {
                            std::cerr << "DEBUG: " << __LINE__ << std::endl;
                        }
                        if ( type != RHS.type )
                        {
                            std::cerr << "DEBUG: " << __LINE__ << std::endl;
                        }
                        if ( nData != RHS.nData )
                        {
                            std::cerr << "DEBUG: " << __LINE__ << std::endl;
                        }
                        if ( nBytes != RHS.nBytes )
                        {
                            std::cerr << "DEBUG: " << __LINE__
                                      << " nBytes: " << nBytes
                                      << " RHS.nBytes: " << RHS.nBytes
                                      << std::endl;
                        }
                        if ( dimension != RHS.dimension )
                        {
                            std::cerr << "DEBUG: " << __LINE__ << std::endl;
                        }
                        if ( unitY != RHS.unitY )
                        {
                            std::cerr << "DEBUG: " << __LINE__ << std::endl;
                        }
                        if ( ( nBytes == RHS.nBytes ) &&
                             ( std::equal( data.get( ),
                                           data.get( ) + nBytes,
                                           RHS.data.get( ) ) == false ) )
                        {
                            std::cerr << "DEBUG: " << __LINE__ << std::endl;
                        }
                        std::cerr << "DEBUG: nData: " << nData << std::endl;
#endif
                        return ( ( this == &RHS ) ||
                                 ( ( name == RHS.name ) &&
                                   ( compress == RHS.compress ) &&
                                   ( type == RHS.type ) &&
                                   ( nData == RHS.nData ) &&
                                   ( nBytes == RHS.nBytes ) &&
                                   ( dimension == RHS.dimension ) &&
                                   ( unitY == RHS.unitY ) &&
                                   ( ( data == RHS.data ) ||
                                     ( std::equal( data.get( ),
                                                   data.get( ) + nBytes,
                                                   RHS.data.get( ) ) ) ) ) );
                    }
                };

                data_definition_type m_data;

            private:
                static const constexpr char* MIME_TYPE_KEYWORD = "MIMETYPE";
                static const constexpr FrameCPP::Version_8::Dimension::nx_type
                                       MIME_TYPE_NX = 0;
                static const constexpr FrameCPP::Version_8::Dimension::dx_type
                                       MIME_TYPE_DX = 0;
                static const constexpr
                        FrameCPP::Version_8::Dimension::startX_type
                        MIME_TYPE_START_X = 0;
            };
        } // namespace FrVectImpl
    } // namespace Version_8
} // namespace FrameCPP

FR_OBJECT_META_DATA_DECLARE( FrVectImpl )

#endif /* ! defined(SWIGIMPORTED) */

#endif /* FrameCPP_VERSION_8__IMPL__FrVectData_HH */
