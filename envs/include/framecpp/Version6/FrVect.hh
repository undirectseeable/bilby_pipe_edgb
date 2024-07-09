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

#ifndef FrameCPP_VERSION_6_FrVect_HH
#define FrameCPP_VERSION_6_FrVect_HH

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

#include "framecpp/Version4/FrVect.hh"

#include "framecpp/Version6/FrameSpec.hh"
#include "framecpp/Version6/Dimension.hh"
#include "framecpp/Version6/GPSTime.hh"
#include "framecpp/Version6/STRING.hh"

namespace FrameCPP
{
    namespace Version_6
    {
        using Previous::FrVectDataTypes;

        class FrVect : public Common::FrameSpec::Object,
                       public Common::FrVect,
                       public FrVectDataTypes
        {
        public:
            // using FrameCPP::Compression;

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
                CST_DECL( ZERO_SUPPRESS_SHORT, 5 ),
                CST_DECL( ZERO_SUPPRESS_INT_FLOAT, 8 ),

#undef CST_DECL
#undef NATIVE_DECL

                //---------------------------------------------------------
                // Declaration of meta modes
                //---------------------------------------------------------
                ZERO_SUPPRESS_SHORT_GZIP_OTHER = 6,
                ZERO_SUPPRESS_OTHERWISE_GZIP = 10,

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

            typedef INT_2U                        compress_type;
            typedef INT_2U                        type_type;
            typedef INT_8U                        nData_type;
            typedef INT_8U                        nBytes_type;
            typedef INT_4U                        nDim_type;
            typedef boost::shared_array< CHAR_U > data_type;
            typedef data_type::element_type       data_element_type;
            typedef data_element_type*            data_pointer_type;
            typedef const data_element_type*      data_const_pointer_type;
            typedef std::unique_ptr< FrVect >     subfrvect_type;

            static const int DEFAULT_GZIP_LEVEL;

            static promote_ret_type Promote( INT_2U           Source,
                                             promote_arg_type Obj,
                                             istream_type*    Stream );

            static const char* StructName( );

            static const Common::Description* StructDescription( );

            //: Default constructor
            FrVect( );

            //-----------------------------------------------------------------
            ///
            /// \brief Copy Constructor.
            ///
            /// \param[in] Source
            ///     Source vector.
            ///
            //-----------------------------------------------------------------
            FrVect( const FrVect& Source );

            FrVect( const std::string& name,
                    compress_type      Compress,
                    type_type          type,
                    nDim_type          nDim,
                    const Dimension*   dims,
                    nData_type         NData,
                    nBytes_type        NBytes,
                    data_type          data,
                    const std::string& unitY = "" );

            //-----------------------------------------------------------------
            //
            //: Constructor.
            //
            //! param: const std::string& name - The name of the data.
            //! param: INT_2U type - The data type.
            //! param: INT_4U nDim - The number of dimensions.
            //! param: const Dimension* dims - A pointer to 'nDim' Dimension
            //! objects
            //+       containing information about the dimensions for this data.
            //! param: const byte_order_type byte_order - Byte order of the
            //! data. Default
            //+       is BIGENDIAN.
            //! param: const void* data - A pointer to the data.  Default: 0
            //! param: const std::string& unitY - Units for the data.  Default:
            //! ""
            //
            //! exc: std::bad_alloc - Memory allocation failed.
            //
            explicit FrVect( const std::string&    name,
                             INT_2U                type,
                             INT_4U                nDim,
                             const Dimension*      dims,
                             const byte_order_type byte_order = BYTE_ORDER_HOST,
                             const void*           data = 0,
                             const std::string&    unitY = "" );

            //-----------------------------------------------------------------
            //
            //: Constructor.
            //
            //! param: const std::string& name - The name of the data.
            //! param: INT_2U type - The data type.
            //! param: INT_4U nDim - The number of dimensions.
            //! param: const Dimension* dims - A pointer to 'nDim' Dimension
            //! objects
            //+     containing information about the dimensions for this data.
            //! param: const byte_order_type byte_order - Byte order of the
            //! data.
            //+	Default is BIGENDIAN.
            //! param: const void* data - A pointer to the data.  Default: 0
            //! param: const std::string& unitY - Units for the data.  Default:
            //! "" param: bool allocate - Whether to allocate data. Default:
            //! true. param: bool owns - Whether to destruct data in the
            //! destructor.
            //+	Default: true.
            //
            //! exc: std::bad_alloc - Memory allocation failed.
            //
            FrVect( const std::string&    name,
                    INT_2U                type,
                    INT_4U                nDim,
                    const Dimension*      dims,
                    const byte_order_type byte_order = BYTE_ORDER_HOST,
                    void*                 data = 0,
                    const std::string&    unitY = "" );

            explicit FrVect( const std::string& name,
                             compress_type      Compress,
                             type_type          type,
                             nDim_type          nDim,
                             const Dimension*   dims,
                             nData_type         NData,
                             nBytes_type        NBytes,
                             void*              data,
                             const std::string& unitY = "" );

            //! exc: std::bad_alloc - Memory allocation failed.
            template < class T >
            FrVect( const std::string& name,
                    INT_4U             nDim = 1,
                    const Dimension*   dims = 0,
                    const T*           data = 0,
                    const std::string& unitY = "" );

            //! exc: std::bad_alloc - Memory allocation failed.
            template < class T >
            FrVect( const std::string& name,
                    INT_4U             nDim = 1,
                    const Dimension*   dims = 0,
                    T*                 data = 0,
                    const std::string& unitY = "" );

            FrVect( const Previous::FrVect& Source, istream_type* Stream );

            virtual ~FrVect( );

            virtual const char* ObjectStructName( ) const;

            //: Comparison operator
            bool operator==( const FrVect& RHS ) const;
            bool operator!=( const FrVect& RHS ) const;
            //: Concatination operator
            FrVect& operator+=( const FrVect& RHS );

            /// \brief comparison operator
            virtual bool
            operator==( const Common::FrameSpec::Object& Obj ) const;

            //: Number of bytes needed to write this structure
            FrameCPP::cmn_streamsize_type
            Bytes( const Common::StreamBase& Stream ) const;

            // Accessors
            const std::string& GetName( ) const;
            INT_2U             GetCompress( ) const;
            INT_2U             GetType( ) const;
            INT_8U             GetNData( ) const;
            INT_8U             GetNBytes( ) const;
            data_type          GetData( ) const;
            data_type          GetDataRaw( ) const;
            data_type          GetDataRaw( );
            data_type          GetDataUncompressed( );
            data_pointer_type  GetDataUncompressed(
                 boost::shared_array< CHAR_U >& Expanded ) const;
            template < class T >
            static INT_2U     GetDataType( );
            INT_4U            GetNDim( ) const;
            const Dimension&  GetDim( nDim_type Offset ) const;
            Dimension&        GetDim( nDim_type Offset );
            const std::string GetUnitY( ) const;

            // Mutators
            void Compress( compression_scheme_type Scheme, int GZipLevel );
            void Uncompress( );

            virtual void CompressData( INT_4U Scheme, INT_2U GZipLevel );

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

            size_t        GetTypeSize( ) const;
            static size_t GetTypeSize( INT_2U type );

            //: Merge with another FrAdcData
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

            //: Write the structure to the stream
            virtual void Write( ostream_type& Stream ) const;

        protected:
            /// \brief Down grade an object
            virtual demote_ret_type demote( INT_2U          Target,
                                            demote_arg_type Obj,
                                            istream_type*   Stream ) const;

            /// \brief Upgrade an object
            virtual promote_ret_type promote( INT_2U           Target,
                                              promote_arg_type Obj,
                                              istream_type*    Stream ) const;

            void expandToBuffer( boost::shared_array< CHAR_U >& Dest,
                                 INT_8U& DestNBytes ) const;

        private:
            using Common::FrameSpec::Object::Create;

            struct data_definition_type
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

                data_definition_type( );
                data_definition_type( const std::string&    n,
                                      INT_2U                t,
                                      const byte_order_type byte_order,
                                      INT_4U                ndim,
                                      const Dimension*      dims,
                                      const std::string&    unit );

                void copy_core( const data_definition_type& Source );

                bool operator==( const data_definition_type& RHS ) const;
            };

            data_definition_type m_data;

            FrVect( istream_type& Stream );

            void data_alloc( nBytes_type NBytes );

            void data_copy( data_const_pointer_type Data, nBytes_type NBytes );
        };

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

        inline FrVect::data_type
        FrVect::GetDataUncompressed( )
        {
            Uncompress( );

            return m_data.data;
        }

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
            return Object::PromoteObject< Previous::FrVect, FrVect >(
                DATA_FORMAT_VERSION, Source, Obj, Stream );
        }

        inline const char*
        FrVect::StructName( )
        {
            static const CHAR* class_name( "FrVect" );
            return class_name;
        }

        //-------------------------------------------------------------------
        /// Return a pointer to the data being managed by the FrVect
        /// structure.
        ///
        /// \see GetDataRaw, GetDataUncompressed
        //-------------------------------------------------------------------
        inline FrVect::data_type
        FrVect::GetData( ) const
        {
            return GetDataRaw( );
        }

        inline INT_2U
        FrVect::GetCompress( ) const
        {
            return m_data.compress;
        }

        inline INT_2U
        FrVect::GetType( ) const
        {
            return m_data.type;
        }

        inline size_t
        FrVect::GetTypeSize( ) const
        {
            return GetTypeSize( m_data.type );
        }

        inline INT_8U
        FrVect::GetNBytes( ) const
        {
            return m_data.nBytes;
        }

        inline INT_4U
        FrVect::GetNDim( ) const
        {
            return m_data.dimension.size( );
        }

        inline const Dimension&
        FrVect::GetDim( INT_4U Offset ) const
        {
            //:TODO: Throw exception if value out of range
            return m_data.dimension[ Offset ];
        }

        inline Dimension&
        FrVect::GetDim( INT_4U Offset )
        {
            //:TODO: Throw exception if value out of range
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
        FrVect::SetNData( INT_4U NData )
        {
            m_data.nData = NData;
        }

    } // namespace Version_6
} // namespace FrameCPP

#if defined( __SUNPRO_CC ) && ( __SUNPRO_CC <= 0x550 )
#include "framecpp/Version6/FrVect.icc"
#endif /* */

#endif /* ! defined(SWIGIMPORTED) */
#endif /* FrameCPP_VERSION_6_FrVect_HH */
