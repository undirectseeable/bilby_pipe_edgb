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

#ifndef FrameCPP_VERSION_8__IMPL__FrVectClassicIO_HH
#define FrameCPP_VERSION_8__IMPL__FrVectClassicIO_HH

#if !defined( SWIGIMPORTED )
#include "framecpp/Common/Description.hh"
#include "framecpp/Common/Verify.hh"
#endif /* !defined( SWIGIMPORTED ) */

#include "framecpp/Version8/impl/FrVectData.hh"

#if !defined( SWIGIMPORTED )
#include "framecpp/Version8/FrameSpec.hh"
#include "framecpp/Version8/FrSH.hh"
#include "framecpp/Version8/FrSE.hh"
#include "framecpp/Version8/PTR_STRUCT.hh"
#include "framecpp/Version8/STRING.hh"
#endif /* ! defined(SWIGIMPORTED) */

#if !defined( SWIGIMPORTED )
namespace FrameCPP
{
    namespace Version_8
    {
        class FrVect;

        namespace FrVectImpl
        {
            template < typename T >
            class ClassicIO
                : public virtual Data,
                  public ObjectWithChecksum< Common::FrameSpec::Object >
            {
            public:
                //-------------------------------------------------------
                //
                //-------------------------------------------------------
                ClassicIO( )
                    : ObjectWithChecksum< Common::FrameSpec::Object >(
                          FrameSpecId( ), StructDescription( ) )
                {
                }

                virtual Common::FrameSpec::Object*
                CloneCompressed( cmn_compression_scheme_type Scheme,
                                 cmn_compression_level_type  Level ) const
                {
                    Common::FrameSpec::ObjectInterface::unique_object_type
                                                  retval;
                    boost::shared_array< CHAR_U > compressed_data;
                    INT_8U                        nbytes( 0 );

                    if ( Scheme == GetCompress( ) )
                    {
                        // Nothing to do. Just return
                        return retval.release( );
                    }

                    compressToBuffer( compress_type_map( ),
                                      compress_type_reverse_map( ),
                                      data_type_map( ),
                                      GetType( ),
                                      GetNData( ),
                                      GetDataRaw( ).get( ),
                                      GetNBytes( ),
                                      GetCompress( ),
                                      compressed_data,
                                      nbytes,
                                      Scheme,
                                      Level );

                    if ( nbytes && compressed_data.get( ) )
                    {
                        //-------------------------------------------------------------------
                        // Save the compressed data
                        //-------------------------------------------------------------------
                        retval.reset(
                            new T( GetName( ),
                                   ( MODE_HOSTENDIAN | ( Scheme & 0xFF ) ),
                                   GetType( ),
                                   GetNDim( ),
                                   &( m_data.dimension[ 0 ] ),
                                   GetNData( ),
                                   nbytes,
                                   compressed_data,
                                   GetUnitY( ) ) );
                    }
                    //---------------------------------------------------------------------
                    // Return the results
                    //---------------------------------------------------------------------
                    return retval.release( );
                }

                //-----------------------------------------------------------------
                /// \brief Promote previous version of object to this version
                ///
                /// \param[in] Source
                ///     The frame specification version of the object.
                /// \param[in] Obj
                ///     The previous version of the object.
                /// \param[in] Stream
                ///     Stream from which the origional object was created.
                ///
                /// \return
                ///     A new instance of FrameH based on Obj
                //-----------------------------------------------------------------
                static promote_ret_type
                Promote( INT_2U           Source,
                         promote_arg_type Obj,
                         Common::IStream* Stream )
                {
                    return Object::PromoteObject< Previous::FrVect, T >(
                        DATA_FORMAT_VERSION, Source, Obj, Stream );
                }

                static const Common::Description*
                StructDescription( )
                {
                    using Common::Description;

                    static Description ret;

                    if ( ret.size( ) == 0 )
                    {
                        ret( FrSH( Data::FrameSpecName( ),
                                   Data::FrameSpecId( ),
                                   Data::FrameSpecDescription( ) ) );

                        ret( FrSE(
                            "name",
                            Description::Ascii< io_name_type >( ),
                            "Channel name -- not required to be unique" ) );
                        ret( FrSE( "compress",
                                   Description::Ascii< compress_type >( ),
                                   "Compression algorithm number" ) );
                        ret( FrSE( "type",
                                   Description::Ascii< type_type >( ),
                                   "Vector class" ) );
                        ret( FrSE(
                            "nData",
                            Description::Ascii< nData_type >( ),
                            "Number of sample elements in data series" ) );
                        ret( FrSE(
                            "nBytes",
                            Description::Ascii< nBytes_type >( ),
                            "Number of bytes in the compressed vector" ) );
                        ret( FrSE( "data",
                                   "CHAR[nBytes]",
                                   "nData elements of specified class" ) );
                        ret( FrSE( "nDim",
                                   Description::Ascii< nDim_type >( ),
                                   "Dimensionality of data vector" ) );
                        ret(
                            FrSE( "nx", "INT_8U[nDim]", "dimension lengths" ) );
                        ret( FrSE( "dx",
                                   "REAL_8[nDim]",
                                   "sample spacing along each coordinate" ) );
                        ret( FrSE( "startX",
                                   "REAL_8[nDim]",
                                   "Origin for each data set" ) );
                        ret( FrSE( "unitX",
                                   "STRING[nDim]",
                                   "scale factors in ASCII" ) );
                        ret( FrSE( "unitY",
                                   Description::Ascii< io_unit_y_type >( ),
                                   "String describing how to interpret the "
                                   "value of each element" ) );

                        ret( FrSE( "next",
                                   PTR_STRUCT::Desc( Data::FrameSpecName( ) ),
                                   "Identifier for additional data." ) );

                        ret( FrSE( "chkSum",
                                   CheckSumDataClass( ),
                                   CheckSumDataComment( ) ) );
                    }

                    return &ret;
                }

              //-----------------------------------------------------------------
              /// \brief equality operator for abstract data type
              ///
              /// \param[in] RHS
              ///     The object to be compared.
              ///
              /// \return
              ///     The value true is returned if this object is equivelent
              ///     to the RHS instance; false otherwise.
              //-----------------------------------------------------------------
              virtual bool
              operator==( const Common::FrameSpec::Object& RHS ) const;

            protected:
                typedef STRING io_name_type;
                typedef STRING io_unit_y_type;

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
                virtual void
                VerifyObject( Common::Verify&       Verifier,
                              Common::IFrameStream& Stream ) const
                {
                    if ( Verifier.Expandability( ) )
                    {
                        //-------------------------------------------------------------------
                        // Verify that the buffer can be decompressed
                        //-------------------------------------------------------------------
                        nBytes_type nBytes( 0 );
                        data_type   expanded_buffer;

                        expandToBuffer( expanded_buffer, nBytes );
                    }
                }

                //-----------------------------------------------------------------
                /// \brief Demotes object to previous version of the frame spec
                ///
                /// \param[in] Target
                ///     The version of the frame specification to demote too.
                /// \param[in] Obj
                ///     The version of the object to demote.
                /// \param[in] Stream
                ///     The input stream from which the original object was
                ///     read.
                ///
                /// \return
                ///     An object of the previous generation.
                //-----------------------------------------------------------------
                virtual demote_ret_type
                demote( INT_2U           Target,
                        demote_arg_type  Obj,
                        Common::IStream* Stream ) const
                {
                    if ( Target >= DATA_FORMAT_VERSION )
                    {
                        return Obj;
                    }
                    try
                    {
                        //-------------------------------------------------------------------
                        // Copy non-reference information
                        //-------------------------------------------------------------------
                        std::vector< Previous::Dimension > dims;
                        for ( std::vector< Dimension >::const_iterator
                                  cur = m_data.dimension.begin( ),
                                  last = m_data.dimension.end( );
                              cur != last;
                              ++cur )
                        {
                            dims.push_back(
                                Previous::Dimension( cur->GetNx( ),
                                                     cur->GetDx( ),
                                                     cur->GetUnitX( ),
                                                     cur->GetStartX( ) ) );
                        }
                        // Do actual down conversion
                        boost::shared_ptr< Previous::FrVect > retval(
                            new Previous::FrVect( GetName( ),
                                                  GetCompress( ),
                                                  GetType( ),
                                                  dims.size( ),
                                                  &( dims[ 0 ] ),
                                                  GetNData( ),
                                                  GetNBytes( ),
                                                  GetDataRaw( ),
                                                  GetUnitY( ) ) );
                        //-------------------------------------------------------------------
                        // Return demoted object
                        //-------------------------------------------------------------------
                        return retval;
                    }
                    catch ( ... )
                    {
                    }
                    throw Unimplemented(
                        "Object* FrVect::demote( Object* Obj ) const",
                        DATA_FORMAT_VERSION,
                        __FILE__,
                        __LINE__ );
                }

                //-----------------------------------------------------------------
                /// \brief The name structure name of this object.
                ///
                /// \return
                ///     The name of the structure as specified by the frame
                ///     specification.
                //-----------------------------------------------------------------
                virtual const char*
                ObjectStructName( ) const
                {
                    return ( FrameSpecName( ) );
                }

                //-----------------------------------------------------------------
                /// \brief Promotes object to another version of the frame spec
                ///
                /// \param[in] Target
                ///     The version of the promoted frame specification.
                /// \param[in] Obj
                ///     The object to be promoted.
                /// \param[in] Stream
                ///     The input stream from which the original object was
                ///     read.
                ///
                /// \return
                ///     An object promoted to the next generation.
                //-----------------------------------------------------------------
                virtual promote_ret_type
                promote( INT_2U           Target,
                         promote_arg_type Obj,
                         Common::IStream* Stream ) const
                {
                    return Promote( Target, Obj, Stream );
                }

                //-----------------------------------------------------------------
                /// \brief Number of bytes needed to write this structure
                ///
                /// \param[in] Stream
                ///     The stream from which to the object is being read or
                ///     written.
                ///
                /// \return
                ///     The number of bytes need to read or write this object.
                //-----------------------------------------------------------------
                virtual FrameCPP::cmn_streamsize_type
                pBytes( const Common::StreamBase& Stream ) const
                {
                    return io_name_type::Bytes( m_data.name ) +
                        sizeof( m_data.compress ) + sizeof( m_data.type ) +
                        sizeof( m_data.nData ) + sizeof( m_data.nBytes ) +
                        m_data.nBytes // data
                        + Bytes( m_data.dimension ) +
                        io_unit_y_type::Bytes( m_data.unitY ) +
                        Stream.PtrStructBytes( ) // next
                        ;
                }

                //-----------------------------------------------------------------
                /// \brief Stream constructor
                ///
                /// \param[in] Stream
                ///     The input stream from where the object is being read.
                //-----------------------------------------------------------------
                virtual self_type*
                pCreate( istream_type& Stream ) const
                {
                    //---------------------------------------------------------------------
                    // Read information from the stream
                    //---------------------------------------------------------------------
                    DimBuffer dims;

                    T* obj( new T );

                    io_name_type   io_name;
                    io_unit_y_type io_unit_y;

                    Stream >> io_name >> obj->m_data.compress >>
                        obj->m_data.type >> obj->m_data.nData >>
                        obj->m_data.nBytes;
                    obj->m_data.data.reset( new CHAR_U[ obj->m_data.nBytes ] );
                    Stream.read(
                        reinterpret_cast< Common::IStream::char_type* >(
                            obj->m_data.data.get( ) ),
                        obj->m_data.nBytes );
                    Stream >> dims >> io_unit_y;
                    Stream.Next( obj );
                    //---------------------------------------------------------------------
                    // Reorder dimension data
                    //---------------------------------------------------------------------
                    dims.copy( obj->m_data.dimension );
                    obj->m_data.name = io_name;
                    obj->m_data.unitY = io_unit_y;

                    return ( obj );
                }

                //-----------------------------------------------------------------
                /// \brief Write the structure to the stream
                ///
                /// \param[in] Stream
                ///     The output stream where the object is to be written.
                //-----------------------------------------------------------------
                virtual void
                pWrite( ostream_type& Stream ) const
                {
                    //---------------------------------------------------------------------
                    // Write data to the stream.
                    //---------------------------------------------------------------------
                    DimBuffer dims( m_data.dimension );

                    Stream << io_name_type( m_data.name ) << m_data.compress << m_data.type
                           << m_data.nData << m_data.nBytes;
                    Stream.write(
                        reinterpret_cast< const Common::OStream::char_type* >(
                            m_data.data.get( ) ),
                        m_data.nBytes );
                    Stream << dims << io_unit_y_type( m_data.unitY );
                    WriteNext( Stream );
                }

            private:
                //=====================================================================
                // Local classes
                //=====================================================================
                class DimBuffer
                {
                public:
                    DimBuffer( )
                    {
                    }

                    DimBuffer( const std::vector< Dimension >& Dims )
                    {
                        nDim_type nDim( Dims.size( ) );

                        m_nx.resize( nDim );
                        m_dx.resize( nDim );
                        m_startX.resize( nDim );
                        m_unitX.resize( nDim );

                        for ( nDim_type x = 0; x < nDim; x++ )
                        {
                            m_nx[ x ] = Dims[ x ].GetNx( );
                            m_dx[ x ] = Dims[ x ].GetDx( );
                            m_startX[ x ] = Dims[ x ].GetStartX( );
                            m_unitX[ x ] = Dims[ x ].GetUnitX( );
                        }
                    }

                    void
                    copy( std::vector< Dimension >& Dims )
                    {
                        nDim_type nDim( m_nx.size( ) );

                        Dims.resize( nDim );
                        for ( nDim_type x = 0; x < nDim; x++ )
                        {
                            Dims[ x ] = Dimension( m_nx[ x ],
                                                   m_dx[ x ],
                                                   m_unitX[ x ],
                                                   m_startX[ x ] );
                        }
                    }

                    static FrameCPP::cmn_streamsize_type
                    GetMinimumBytes( )
                    {
                        return sizeof( INT_8U ) + sizeof( REAL_8 ) +
                            sizeof( REAL_8 ) + STRING::Bytes( "" );
                    }

                    friend ostream_type&
                    operator<<( ostream_type& Stream, const DimBuffer& Dims )
                    {
                        nDim_type nDim( Dims.m_nx.size( ) );

                        Stream << nDim << Dims.m_nx << Dims.m_dx << Dims.m_startX << Dims.m_unitX;
                        return Stream;
                    }

                    friend istream_type&
                    operator>>( istream_type& Stream, DimBuffer& Dims )
                    {
                        nDim_type nDim( 0 );
                        Stream >> nDim;

                        Dims.m_nx.resize( nDim );
                        Dims.m_dx.resize( nDim );
                        Dims.m_startX.resize( nDim );
                        Dims.m_unitX.resize( nDim );

                        Stream >> Dims.m_nx >> Dims.m_dx >> Dims.m_startX >> Dims.m_unitX;

                        return Stream;
                    }

                private:
                    friend class FrameCPP::Common::IStream;
                    friend class FrameCPP::Common::OStream;

                    std::vector< INT_8U > m_nx;
                    std::vector< REAL_8 > m_dx;
                    std::vector< REAL_8 > m_startX;
                    std::vector< STRING > m_unitX;
                };

                //-----------------------------------------------------------------
                /// \brief Object with checksum data.
                //-----------------------------------------------------------------
                typedef ObjectWithChecksum< Common::FrameSpec::Object >
                    object_type;

                using Common::FrameSpec::Object::Create;

                template < typename OBJECT_TYPE >
                static FrameCPP::cmn_streamsize_type
                Bytes( const OBJECT_TYPE& Object );
            };

        } // namespace FrVectImpl
    } // namespace Version_8
} // namespace FrameCPP

#endif /* ! defined(SWIGIMPORTED) */

#endif /* FrameCPP_VERSION_8__IMPL__FrVectClassicIO_HH */
