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

#ifndef FrameCPP_VERSION_3_FrVect_HH
#define FrameCPP_VERSION_3_FrVect_HH

#if !defined( SWIGIMPORTED )
#include <memory>
#include <vector>
#include <string>

#include <boost/shared_array.hpp>

#include "ldastoolsal/types.hh"

#include "framecpp/Common/Compression.hh"
#include "framecpp/Common/FrVect.hh"

#include "framecpp/Version3/FrameSpec.hh"
#include "framecpp/Version3/Dimension.hh"
#include "framecpp/Version3/STRING.hh"
#endif /* ! defined(SWIGIMPORTED) */

#if !defined( SWIGIMPORTED )

namespace FrameCPP
{
    namespace Version_3
    {
        class FrVectDataTypes
        {
        public:
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
        };

        class FrVectCompressionScheme
        {
        public:
            static const INT_2U BYTE_SWAP = 0x100;

            enum compression_scheme_type
            {
                RAW = 0,
                GZIP = 1,
                DIFF = 2,
                DIFF_GZIP = 3
            };
        };

        class FrVect : public Common::FrameSpec::Object,
                       public Common::FrVect,
                       public FrVectDataTypes,
                       public FrVectCompressionScheme
        {
        public:
            // using FrameCPP::Compression;

            using Common::FrameSpec::ObjectInterface::Create;

            typedef Common::FrVect::cmn_compression_scheme_type
                cmn_compression_scheme_type;
            typedef Common::FrVect::cmn_compression_level_type
                cmn_compression_level_type;

            typedef INT_2U compress_type;
            typedef INT_2U type_type;
            typedef INT_4U nData_type;
            typedef INT_4U nBytes_type;
            typedef INT_4U nDim_type;

            typedef boost::shared_array< CHAR_U > data_type;

            typedef std::unique_ptr< FrVect > subfrvect_type;

            static const int DEFAULT_GZIP_LEVEL;

            static promote_ret_type Promote( INT_2U           Source,
                                             promote_arg_type Obj,
                                             istream_type*    Stream );

            static const char* StructName( );

            static const Common::Description* StructDescription( );

            //-----------------------------------------------------------------
            /// \brief Default constructor
            ///
            /// \return
            ///     A new instance of an FrVect.
            //-----------------------------------------------------------------
            FrVect( );

            //-----------------------------------------------------------------
            /// \brief Copy Constructor.
            ///
            /// \param[in] vect
            ///     Copied vector.
            ///
            /// \exception std::bad_alloc
            ///     Memory allocation failed.
            ///
            /// \return
            ///     A new instance of an FrVect
            //-----------------------------------------------------------------
            FrVect( const FrVect& vect );

            //-----------------------------------------------------------------
            /// \brief Constructor.
            ///
            /// \param[in] name
            ///     The name of the data.
            /// \param[in] type
            ///     The data type.
            /// \param[in] nDim
            ///     The number of dimensions.
            /// \param[in] dims
            ///     A pointer to 'nDim' Dimension objects
            ///     containing information about the dimensions for this data.
            /// \param[in] byte_order
            ///     Byte order of the data.
            ///     <b>Default</b> is BIGENDIAN.
            /// \param[in] data
            ///     A pointer to the data.
            ///     <b>Default</b>: 0
            /// \param[in] unitY
            ///     Units for the data.
            ///     <b>Default</b>: ""
            ///
            /// \return
            ///     A new instance of an FrVect
            ///
            /// \exception std::bad_alloc
            ///     Memory allocation failed.
            ///
            //-----------------------------------------------------------------
            FrVect( const std::string&    name,
                    type_type             type,
                    nDim_type             nDim,
                    const Dimension*      dims,
                    const byte_order_type byte_order = BYTE_ORDER_HOST,
                    const void*           data = 0,
                    const std::string&    unitY = "" );

            //-----------------------------------------------------------------
            /// \brief Constructor.
            ///
            /// \param[in] name
            ///     The name of the data.
            /// \param[in] type
            ///     The data type.
            /// \param[in] nDim
            ///     The number of dimensions.
            /// \param[in] dims
            ///     A pointer to 'nDim' Dimension objects
            ///     containing information about the dimensions for this data.
            /// \param[in] byte_order
            ///     Byte order of the data.
            ///     <b>Default</b> is BIGENDIAN.
            /// \param[in] data
            ///     A pointer to the data.
            ///     <b>Default</b>: 0
            /// \param[in] unitY
            ///     Units for the data.
            ///     <b>Default</b>: ""
            /// \param[in] allocate
            ///     Whether to allocate data.
            ///     <b>Default</b>: true.
            /// \param[in] owns
            ///     Whether to destruct data in the destructor.
            ///     <b>Default</b>: true.
            ///
            /// \return
            ///     A new instance of an FrVect
            ///
            /// \exception std::bad_alloc
            ///     Memory allocation failed.
            //-----------------------------------------------------------------
            FrVect( const std::string&    name,
                    type_type             type,
                    nDim_type             nDim,
                    const Dimension*      dims,
                    const byte_order_type byte_order = BYTE_ORDER_HOST,
                    void*                 data = 0,
                    const std::string&    unitY = "",
                    bool                  allocate = true,
                    bool                  owns = true );

            //-----------------------------------------------------------------
            /// \brief Constructor.
            ///
            /// \param[in] name
            ///     The name of the data.
            /// \param[in] Compress
            /// \param[in] type
            ///     The data type.
            /// \param[in] nDim
            ///     The number of dimensions.
            /// \param[in] dims
            ///     A pointer to 'nDim' Dimension objects
            ///     containing information about the dimensions for this data.
            /// \param[in] NData
            /// \param[in] NBytes
            /// \param[in] data
            ///     A pointer to the data.
            ///     <b>Default</b>: 0
            /// \param[in] unitY
            ///     Units for the data.
            ///     <b>Default</b>: ""
            /// \param[in] allocate
            ///     Whether to allocate data.
            ///     <b>Default</b>: true.
            /// \param[in] owns
            ///     Whether to destruct data in the destructor.
            ///     <b>Default</b>: true.
            ///
            /// \return
            ///     A new instance of an FrVect
            //-----------------------------------------------------------------
            FrVect( const std::string& name,
                    compress_type      Compress,
                    type_type          type,
                    nDim_type          nDim,
                    const Dimension*   dims,
                    nData_type         NData,
                    nBytes_type        NBytes,
                    void*              data,
                    const std::string& unitY = "",
                    bool               allocate = true,
                    bool               owns = true );

            //-----------------------------------------------------------------
            /// \brief Constructor.
            ///
            /// \param[in] name
            ///     The name of the data.
            /// \param[in] Compress
            /// \param[in] type
            ///     The data type.
            /// \param[in] nDim
            ///     The number of dimensions.
            /// \param[in] dims
            ///     A pointer to 'nDim' Dimension objects
            ///     containing information about the dimensions for this data.
            /// \param[in] NData
            /// \param[in] NBytes
            /// \param[in] data
            ///     A pointer to the data.
            ///     <b>Default</b>: 0
            /// \param[in] unitY
            ///     Units for the data.
            ///     <b>Default</b>: ""
            ///
            /// \return
            ///     A new instance of an FrVect
            //-----------------------------------------------------------------
            FrVect( const std::string& name,
                    compress_type      Compress,
                    type_type          type,
                    nDim_type          nDim,
                    const Dimension*   dims,
                    nData_type         NData,
                    nBytes_type        NBytes,
                    data_type          data,
                    const std::string& unitY = "" );

            //! exc: std::bad_alloc - Memory allocation failed.
            template < class T >
            FrVect( const std::string& name,
                    nDim_type          nDim = 1,
                    const Dimension*   dims = 0,
                    const T*           data = 0,
                    const std::string& unitY = "" );

            //! exc: std::bad_alloc - Memory allocation failed.
            template < class T >
            FrVect( const std::string& name,
                    nDim_type          nDim = 1,
                    const Dimension*   dims = 0,
                    T*                 data = 0,
                    const std::string& unitY = "",
                    bool               allocate = true,
                    bool               owns = true );

            virtual ~FrVect( );

            virtual const char* ObjectStructName( ) const;

            // Comparison operator
            bool operator==( const FrVect& RHS ) const;
            bool operator!=( const FrVect& RHS ) const;
            /// \brief Concatination operator
            FrVect& operator+=( const FrVect& RHS );

            /// \brief comparison operator
            virtual bool
            operator==( const Common::FrameSpec::Object& Obj ) const;

            /// \brief Number of bytes needed to write this structure
            FrameCPP::cmn_streamsize_type
            Bytes( const Common::StreamBase& Stream ) const;

            // Accessors
            const std::string& GetName( ) const;
            compress_type      GetCompress( ) const;
            type_type          GetType( ) const;
            nData_type         GetNData( ) const;
            nBytes_type        GetNBytes( ) const;
            data_type          GetData( bool Decompress = true ) const;
            data_type          GetData( bool Decompress = true );

            data_type GetDataRaw( ) const;

            data_type GetDataRaw( );

            template < class T >
            static INT_2U     GetDataType( );
            nDim_type         GetNDim( ) const;
            const Dimension&  GetDim( nDim_type Offset ) const;
            Dimension&        GetDim( nDim_type Offset );
            const std::string GetUnitY( ) const;

            // Mutators
            void Compress( compression_scheme_type Scheme, int GZipLevel );

            //-----------------------------------------------------------------
            /// \brief Expand compressed data.
            //-----------------------------------------------------------------
            void Uncompress( );

            virtual void CompressData( cmn_compression_scheme_type Scheme,
                                       cmn_compression_level_type  GZipLevel );

            virtual Compression::compression_base_type Compression( ) const;

            virtual Common::FrameSpec::Object*
            CloneCompressed( cmn_compression_scheme_type Scheme,
                             cmn_compression_level_type  Level ) const;

            //-----------------------------------------------------------------
            /// \brief Establish the channel name.
            ///
            /// \param[in] Name
            ///     The channel name
            //-----------------------------------------------------------------
            void SetName( const std::string& Name );

            void SetNData( INT_4U NData );

            //-----------------------------------------------------------------
            /// \brief Get size of single data point of particular size.
            ///
            /// \return
            ///     Data size.
            //-----------------------------------------------------------------
            size_t        GetTypeSize( ) const;
            static size_t GetTypeSize( type_type type );

            //-----------------------------------------------------------------
            /// \brief Merge with another FrVect
            ///
            /// \param[in] RHS
            ///     The other FrVect with which to merge.
            ///
            /// \return
            ///     Reference to this object.
            //-----------------------------------------------------------------
            FrVect& Merge( const FrVect& RHS );

            subfrvect_type SubFrVect( INT_4U Start, INT_4U Stop ) const;

            virtual FrVect* Create( istream_type& Stream ) const;

            //-----------------------------------------------------------------
            /// \brief Verify the integrity of the object
            ///
            /// \param Verifier
            ///     The handle to the Verify object used to store data that
            ///     needs to be accumulated before being processed.
            /// \param Stream
            ///     The input stream from which the object was created.
            ///
            /// \remarks
            ///     Upon failure, this method thows an exception.
            //-----------------------------------------------------------------
            virtual void VerifyObject( Common::Verify&       Verifier,
                                       Common::IFrameStream& Stream ) const;

            //-----------------------------------------------------------------
            /// \brief Write the structure to the stream
            //-----------------------------------------------------------------
            virtual void Write( ostream_type& Stream ) const;

            void expandToBuffer( boost::shared_array< CHAR_U >& Dest,
                                 INT_8U& DestNBytes ) const;

        protected:
            /// \brief Down grade an object
            virtual demote_ret_type demote( INT_2U          Target,
                                            demote_arg_type Obj,
                                            istream_type*   Stream ) const;

            /// \brief Upgrade an object
            virtual promote_ret_type promote( INT_2U           Target,
                                              promote_arg_type Obj,
                                              istream_type*    Stream ) const;

        private:
            struct data_container_type
            {
            public:
                STRING                   name;
                compress_type            compress;
                type_type                type;
                nData_type               nData;
                nBytes_type              nBytes;
                data_type                data;
                std::vector< Dimension > dimension;
                STRING                   unitY;

                //---------------------------------------------------------------
                /// \brief Default Constructor
                //---------------------------------------------------------------
                data_container_type( );

                //---------------------------------------------------------------
                /// \brief Constructor
                ///
                /// \param[in] n
                ///     The name of the data.
                /// \param[in] t
                ///     The data type.
                /// \param[in] byte_order
                /// \param[in] ndim,
                /// \param[in] dims
                /// \param[in] unit
                ///
                //---------------------------------------------------------------
                data_container_type( const std::string&    n,
                                     type_type             t,
                                     const byte_order_type byte_order,
                                     INT_4U                ndim,
                                     const Dimension*      dims,
                                     const std::string&    unit );

                //---------------------------------------------------------------
                /// \brief Constructor
                ///
                /// \param[in] Name
                ///     The name of the data.
                /// \param[in] Compress
                /// \param[in] Type
                ///     The data type.
                /// \param[in] NData
                ///     Number of data elements.
                /// \param[in] NBytes
                ///     Number of bytes allocated to Data.
                /// \param[in] Data
                ///     A pointer to the data.  Default: 0
                /// \param[in] NDim
                ///     The number of dimensions.
                /// \param[in] Dims
                ///     A pointer to 'nDim' Dimension objects containing
                ///     information about the dimensions for this data.
                /// \param[in] UnitY
                ///     Units for the data.
                /// \param[in] Allocate
                ///     True if space for the data space should be allocated
                ///     by this call, false otherwise.
                //---------------------------------------------------------------
                data_container_type( const std::string& Name,
                                     compress_type      Compress,
                                     type_type          Type,
                                     nData_type         NData,
                                     nBytes_type        NBytes,
                                     void*              Data,
                                     nDim_type          NDim,
                                     const Dimension*   Dims,
                                     const std::string& UnitY,
                                     bool               Allocate );

                //---------------------------------------------------------------
                /// \brief Constructor
                ///
                /// \param[in] Name
                ///     The name of the data.
                /// \param[in] Compress
                /// \param[in] Type
                ///     The data type.
                /// \param[in] NData
                ///     Number of data elements.
                /// \param[in] NBytes
                ///     Number of bytes allocated to Data.
                /// \param[in] Data
                ///     A pointer to the data.  Default: 0
                /// \param[in] NDim
                ///     The number of dimensions.
                /// \param[in] Dims
                ///     A pointer to 'nDim' Dimension objects containing
                ///     information about the dimensions for this data.
                /// \param[in] UnitY
                ///     Units for the data.
                data_container_type( const std::string& Name,
                                     compress_type      Compress,
                                     type_type          Type,
                                     nData_type         NData,
                                     nBytes_type        NBytes,
                                     data_type          Data,
                                     nDim_type          NDim,
                                     const Dimension*   Dims,
                                     const std::string& UnitY );

                void copy_core( const data_container_type& Source );

                bool operator==( const data_container_type& RHS ) const;
            };

            static const Common::FrameSpec::Info::frame_object_types
                s_object_id = Common::FrameSpec::Info::FSI_FR_VECT;

            data_container_type m_data;

            FrVect( istream_type& Stream );

            void copy_data( CHAR_U* Data, INT_8U size );
        };

        inline Compression::compression_base_type
        FrVect::Compression( ) const
        {
            return ( 0x0FF & m_data.compress );
        }

        inline FrVect::promote_ret_type
        FrVect::Promote( INT_2U           Source,
                         promote_arg_type Obj,
                         istream_type*    Stream )
        {
            return Common::PromoteObject( DATA_FORMAT_VERSION, Source, Obj );
        }

        inline const char*
        FrVect::StructName( )
        {
            static const CHAR* class_name( "FrVect" );
            return class_name;
        }

        inline FrVect::data_type
        FrVect::GetDataRaw( ) const
        {
            return m_data.data;
        }

        inline FrVect::data_type
        FrVect::GetDataRaw( )
        {
            return m_data.data;
        }

        inline FrVect::compress_type
        FrVect::GetCompress( ) const
        {
            return m_data.compress;
        }

        inline FrVect::type_type
        FrVect::GetType( ) const
        {
            return m_data.type;
        }

        inline size_t
        FrVect::GetTypeSize( ) const
        {
            return GetTypeSize( m_data.type );
        }

        inline FrVect::nBytes_type
        FrVect::GetNBytes( ) const
        {
            return m_data.nBytes;
        }

        inline FrVect::nDim_type
        FrVect::GetNDim( ) const
        {
            return m_data.dimension.size( );
        }

        inline const Dimension&
        FrVect::GetDim( nDim_type Offset ) const
        {
            /// \todo
            ///   Throw exception if value out of range
            return m_data.dimension[ Offset ];
        }

        inline Dimension&
        FrVect::GetDim( nDim_type Offset )
        {
            /// \todo
            ///   Throw exception if value out of range
            return m_data.dimension[ Offset ];
        }

        inline const std::string
        FrVect::GetUnitY( ) const
        {
            return m_data.unitY;
        }

        //-------------------------------------------------------------------
        /// Assign a new value for the channel name.
        //-------------------------------------------------------------------
        inline void
        FrVect::SetName( const std::string& Name )
        {
            m_data.name = Name;
        }

        inline void
        FrVect::SetNData( nData_type NData )
        {
            m_data.nData = NData;
        }
    } // namespace Version_3
} // namespace FrameCPP

#if defined( __SUNPRO_CC ) && ( __SUNPRO_CC <= 0x550 )
#include "framecpp/Version3/FrVect.tcc"
#endif /* */

#endif /* ! defined(SWIGIMPORTED) */

#endif /* FrameCPP_VERSION_3_FrVect_HH */
