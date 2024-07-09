//
// LDASTools frameCPP - A library implementing the LIGO/Virgo frame
// specification
//
// Copyright (C) 2018-2020 California Institute of Technology
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

#ifndef FrameCPP_VERSION_8__IMPL__FrStatDataClassicIO_HH
#define FrameCPP_VERSION_8__IMPL__FrStatDataClassicIO_HH

#if defined( __cplusplus ) && !defined( SWIG )
#include <vector>

#include "framecpp/Common/FrameSpec.hh"
#include "framecpp/Version8/FrameSpec.hh"

#include "framecpp/Common/Description.hh"
#include "framecpp/Common/FrDetector.hh"
#include "framecpp/Common/FrStatData.hh"
#include "framecpp/Common/TOCInfo.hh"

#include "framecpp/Version7/FrStatData.hh"

#include "framecpp/Version8/impl/FrStatDataData.hh"

#include "framecpp/Version8/FrSH.hh"
#include "framecpp/Version8/FrSE.hh"

namespace FrameCPP
{
    namespace Version_8
    {

        class FrStatData;

        namespace FrStatDataImpl
        {
            typedef Common::FrStatData base_object_type;

            template < typename T >
            class ClassicIO : public virtual Data,
                              public Common::TOCInfo,
                              public ObjectWithChecksum< base_object_type >
            {
            public:
                typedef Common::FrStatData::fr_detector_type fr_detector_type;
                //-------------------------------------------------------
                //
                //-------------------------------------------------------
                ClassicIO( )
                    : ObjectWithChecksum< base_object_type >(
                          StructDescription( ) )
                {
                }

                ClassicIO( const Previous::FrStatData& Source,
                           istream_type*               Stream )
                    : ObjectWithChecksum< base_object_type >(
                          StructDescription( ) )
                {
                    Data::name = Source.GetName( );
                    Data::comment = Source.GetComment( );
                    Data::representation = Source.GetRepresentation( );
                    Data::timeStart = Source.GetTimeStart( );
                    Data::timeEnd = Source.GetTimeEnd( );
                    Data::version = Source.GetVersion( );

                    if ( Stream )
                    {
                        //-------------------------------------------------------------------
                        // Modify references
                        //-------------------------------------------------------------------
                        const INT_2U max_ref = Previous::FrStatData::MAX_REF;
                        Stream->ReplacePtr( AddressOfDetector( ),
                                            Source.AddressOfDetector( ),
                                            max_ref );
                        Stream->ReplaceRef(
                            RefData( ), Source.RefData( ), max_ref );
                        Stream->ReplaceRef(
                            RefTable( ), Source.RefTable( ), max_ref );
                    }
                }

                Common::FrameSpec::Object*
                Clone( ) const
                {
                    return (
                        new T( *( reinterpret_cast< const T* >( this ) ) ) );
                }

                //-----------------------------------------------------------------
                /// \brief Retrieve the detector associated with the object.
                ///
                /// \return
                ///     The detector associated with the object.
                //-----------------------------------------------------------------
                virtual Common::FrStatData::fr_detector_type
                GetDetector( ) const
                {
                    return Data::GetDetector( );
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
                    return StructName( );
                }

                /**
                 * \brief Promote previous version of object to this version
                 *
                 * \param[in] Source
                 *     The frame specification version of the object.
                 * \param[in] Obj
                 *     The previous version of the object.
                 * \param[in] Stream
                 *     Stream from which the origional object was created.
                 *
                 * \return
                 *     A new instance of FrameH based on Obj
                 */
                inline static promote_ret_type
                Promote( INT_2U           Source,
                         promote_arg_type Obj,
                         istream_type*    Stream )
                {
                    return Object::PromoteObject< Previous::FrStatData, T >(
                        DATA_FORMAT_VERSION, Source, Obj, Stream );
                }

                //-----------------------------------------------------------------
                /// \brief The description of structure
                ///
                /// \return
                ///     A Description object which describes this structure as
                ///     specified by the frame specification.
                //-----------------------------------------------------------------
                static const Common::Description*
                StructDescription( )
                {
                    using Common::Description;

                    static Description ret;

                    if ( ret.size( ) == 0 )
                    {
                        //-----------------------------------------------
                        ret( FrSH( Data::StructName( ),
                                   Data::FrameSpecId( ),
                                   Data::FrameSpecDescription( ) ) );

                        ret( FrSE( "name",
                                   Description::Ascii< io_name_type >( ),
                                   "" ) );
                        ret( FrSE( "comment",
                                   Description::Ascii< io_comment_type >( ),
                                   "" ) );
                        ret( FrSE(
                            "representation",
                            Description::Ascii< io_representation_type >( ),
                            "" ) );
                        ret( FrSE( "timeStart",
                                   Description::Ascii< timeStart_type >( ),
                                   "" ) );
                        ret( FrSE( "timeEnd",
                                   Description::Ascii< timeEnd_type >( ),
                                   "" ) );
                        ret( FrSE( "version",
                                   Description::Ascii< version_type >( ),
                                   "" ) );

                        ret( FrSE(
                            "detector",
                            PTR_STRUCT::Desc( FrDetector::StructName( ) ) ) );
                        ret(
                            FrSE( "data",
                                  PTR_STRUCT::Desc( FrVect::StructName( ) ) ) );
                        ret( FrSE(
                            "table",
                            PTR_STRUCT::Desc( FrTable::StructName( ) ) ) );

                        ret( FrSE( "chkSum",
                                   CheckSumDataClass( ),
                                   CheckSumDataComment( ) ) );
                    }

                    return &ret;
                }

#if WORKING_VIRTUAL_TOCQUERY
            public:
                //-----------------------------------------------------------------
                /// \brief Answer requests for information as needed by TOC
                ///
                /// \param[in] InfoClass
                ///     Class of information being requested.
                //-----------------------------------------------------------------
                virtual void
                TOCQuery( int InfoClass, ... ) const
#else
            protected:
                //-----------------------------------------------------------------
                /// \brief Answer requests for information as needed by TOC
                ///
                /// \param[in] InfoClass
                ///     Class of information being requested.
                /// \param[in] vl
                ///     Variable argument list of requested data.
                //-----------------------------------------------------------------
                virtual void
                vTOCQuery( int InfoClass, va_list vl ) const
#endif /*  WORKING_VIRTUAL_TOCQUERY */
                {
                    using Common::TOCInfo;

#if WORKING_VIRTUAL_TOCQUERY
                    va_list vl;
                    va_start( vl, InfoClass );
#endif /*  WORKING_VIRTUAL_TOCQUERY */

                    while ( InfoClass != TOCInfo::IC_EOQ )
                    {
                        int data_type = va_arg( vl, int );
                        switch ( data_type )
                        {
                        case TOCInfo::DT_STRING_2:
                        {
                            STRING* data = va_arg( vl, STRING* );
                            switch ( InfoClass )
                            {
                            case TOCInfo::IC_NAME:
                                *data = GetName( );
                                break;
                            case TOCInfo::IC_DETECTOR:
                                if ( Data::GetDetector( ) )
                                {
                                    boost::shared_ptr< FrDetector > detector(
                                        boost::dynamic_pointer_cast<
                                            FrDetector >(
                                            Data::GetDetector( ) ) );

                                    *data = detector->GetName( );
                                }
                                else
                                {
                                    *data = "";
                                }
                                break;
                            default:
                                goto cleanup;
                                break;
                            }
                        }
                        break;
                        case TOCInfo::DT_INT_4U:
                        {
                            INT_4U* data = va_arg( vl, INT_4U* );
                            switch ( InfoClass )
                            {
                            case TOCInfo::IC_START:
                                *data = GetTimeStart( );
                                break;
                            case TOCInfo::IC_END:
                                *data = GetTimeEnd( );
                                break;
                            case TOCInfo::IC_VERSION:
                                *data = GetVersion( );
                                break;
                            default:
                                goto cleanup;
                                break;
                            }
                        }
                        break;
                        default:
                            // Stop processing
                            goto cleanup;
                        }
                        InfoClass = va_arg( vl, int );
                    }
                cleanup:
#if WORKING_VIRTUAL_TOCQUERY
                    va_end( vl )
#endif /*  WORKING_VIRTUAL_TOCQUERY */
                        ;
                }

            protected:
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
                demote( INT_2U          Target,
                        demote_arg_type Obj,
                        istream_type*   Stream ) const
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
                        // Do actual down conversion
                        boost::shared_ptr< Previous::FrStatData > retval(
                            new Previous::FrStatData( GetName( ),
                                                      GetComment( ),
                                                      GetRepresentation( ),
                                                      GetTimeStart( ),
                                                      GetTimeEnd( ),
                                                      GetVersion( ) ) );
                        if ( Stream )
                        {
                            //-----------------------------------------------------------------
                            // Modify references
                            //-----------------------------------------------------------------
                            Stream->ReplacePtr( retval->AddressOfDetector( ),
                                                AddressOfDetector( ),
                                                MAX_REF );
                            Stream->ReplaceRef(
                                retval->RefData( ), RefData( ), MAX_REF );
                            Stream->ReplaceRef(
                                retval->RefTable( ), RefTable( ), MAX_REF );
                        }
                        //-------------------------------------------------------------------
                        // Return demoted object
                        //-------------------------------------------------------------------
                        return retval;
                    }
                    catch ( ... )
                    {
                    }
                    throw Unimplemented(
                        "Object* FrStatData::demote( Object* Obj ) const",
                        DATA_FORMAT_VERSION,
                        __FILE__,
                        __LINE__ );
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
                         istream_type*    Stream ) const
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
                virtual cmn_streamsize_type
                pBytes( const Common::StreamBase& Stream ) const
                {
                    return ( io_name_type::Bytes( name ) +
                             io_comment_type::Bytes( comment ) +
                             io_representation_type::Bytes( representation ) +
                             sizeof( timeStart ) + sizeof( timeEnd ) +
                             sizeof( version ) //
                             + Stream.PtrStructBytes( ) // detector
                             + Stream.PtrStructBytes( ) // data
                             + Stream.PtrStructBytes( ) // table
                    );
                }

                //-----------------------------------------------------------------
                /// \brief Virtual constructor
                ///
                /// \param[in] Stream
                ///     The input stream from where the object is being read.
                //-----------------------------------------------------------------
                virtual self_type*
                pCreate( istream_type& Stream ) const
                {
                    T* obj( new T( ) );

                    io_name_type           io_name;
                    io_comment_type        io_comment;
                    io_representation_type io_representation;

                    Stream >> io_name >> io_comment >> io_representation >>
                        obj->timeStart >> obj->timeEnd >> obj->version;

                    Stream >> &( obj->detector ) >> obj->data >> obj->table;

                    obj->name = io_name;
                    obj->comment = io_comment;
                    obj->representation = io_representation;

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
                    Stream << io_name_type( name ) << io_comment_type( comment )
                           << io_representation_type( representation )
                           << timeStart << timeEnd << version;

                    Stream << ostream_type::Pointer( detector ) << data
                           << table;
                }

            private:
                typedef STRING io_name_type;
                typedef STRING io_comment_type;
                typedef STRING io_representation_type;

            }; // class ClassicIO
        } // namespace FrStatDataImpl
    } // namespace Version_8
} // namespace FrameCPP

#endif /* defined( __cplusplus ) && !defined( SWIG ) */

#if 0
#include <vector>

#include "framecpp/Common/TOCInfo.hh"
#include "framecpp/Common/SearchContainer.hh"
#include "framecpp/Common/FrameStream.hh"
#include "framecpp/Common/FrStatData.hh"

#include "framecpp/Version7/FrStatData.hh"

#include "framecpp/Version8/FrameSpec.hh"
#include "framecpp/Version8/STRING.hh"
#include "framecpp/Version8/PTR_STRUCT.hh"

#include "framecpp/Version8/FrDetector.hh"
#include "framecpp/Version8/FrSE.hh"
#include "framecpp/Version8/FrTable.hh"
#include "framecpp/Version8/FrTOC.hh"
#include "framecpp/Version8/FrVect.hh"

namespace FrameCPP
{
    namespace Version_8
    {
        //===================================================================
        //===================================================================

        typedef Previous::FrStatData::FrStatDataNPS FrStatDataNPS;

        //===================================================================
        //===================================================================

        typedef Version_4::
            FrStatDataPST< PTR_STRUCT, FrDetector, FrVect, FrTable >
                FrStatDataPS;

        //===================================================================
        /// \brief Static Data Structure Definition
        //===================================================================
        class FrStatData : public ObjectWithChecksum< Common::FrStatData >,
                           public FrStatDataNPS,
                           public FrStatDataPS,
                           public Common::TOCInfo
        {
        public:
            typedef FrStatDataNPS nps_type;
            typedef FrStatDataPS  ps_type;

            //-----------------------------------------------------------------
            /// \brief Default constructor
            ///
            /// \return
            ///    A new instance of this object.
            //-----------------------------------------------------------------
            FrStatData( );

            //-----------------------------------------------------------------
            /// \brief Copy Constructor
            ///
            /// \param[in] Source
            ///     The object from which to copy the information.
            ///
            /// \return
            ///    A new instance of this object.
            //-----------------------------------------------------------------
            FrStatData( const FrStatData& Source );

            //-----------------------------------------------------------------
            /// \brief Constructor
            ///
            /// \param[in] name
            ///     Static data name
            /// \param[in] comment
            ///     Comemnt
            /// \param[in] representation
            ///     Type of static data being represented
            /// \param[in] timeStart
            ///     Start time of static data validity.
            /// \param[in] timeEnd
            ///     End time of static data validity.
            /// \param[in] version
            ///     Version number of this static structure.
            ///
            /// \return
            ///     A new instance of the object.
            //-----------------------------------------------------------------
            FrStatData( const std::string& name,
                        const std::string& comment,
                        const std::string& representation,
                        INT_4U             timeStart,
                        INT_4U             timeEnd,
                        INT_4U             version );

            //-----------------------------------------------------------------
            /// \brief Promotion Constructor
            ///
            /// \param[in] Source
            ///     An FrAdcData structure from a previous frame specification.
            /// \param[in] Stream
            ///     The stream from which the earliest version of the
            ///     FrAdcData structure was read.
            ///
            /// \return
            ///     A new instance of the object.
            //-----------------------------------------------------------------
            FrStatData( const Previous::FrStatData& Source,
                        istream_type*               Stream );

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
            static promote_ret_type Promote( INT_2U           Source,
                                             promote_arg_type Obj,
                                             istream_type*    Stream );

            //-----------------------------------------------------------------
            /// \brief The name structure name of this object.
            ///
            /// \return
            ///     The name of the structure as specified by the frame
            ///     specification.
            //-----------------------------------------------------------------
            static const char* StructName( );

            //-----------------------------------------------------------------
            /// \brief The description of structure
            ///
            /// \return
            ///     A Description object which describes this structure as
            ///     specified by the frame specification.
            //-----------------------------------------------------------------
            static const Common::Description* StructDescription( );

            //-----------------------------------------------------------------
            /// \brief Virtual constructor
            ///
            /// \return
            ///     A new instance of FrameH based on Obj
            ///
            /// \deprecated
            ///     Do not make this call as it will be gone by version 1.14.0.
            //-----------------------------------------------------------------
            virtual FrStatData* Clone( ) const;

#if WORKING
            //-----------------------------------------------------------------
            /// \brief Retrieve the detector associated with the object.
            ///
            /// \return
            ///     The detector associated with the object.
            //-----------------------------------------------------------------
            virtual fr_detector_type
            GetDetector( ) const
            {
                return FrStatDataPS::GetDetector( );
            }
#endif /* 0 */

            //-----------------------------------------------------------------
            /// \brief The name structure name of this object.
            ///
            /// \return
            ///     The name of the structure as specified by the frame
            ///     specification.
            //-----------------------------------------------------------------
            virtual const char* ObjectStructName( ) const;

#if WORKING_VIRTUAL_TOCQUERY
            //-----------------------------------------------------------------
            /// \brief Answer requests for information as needed by TOC
            ///
            /// \param[in] InfoClass
            ///     Class of information being requested.
            //-----------------------------------------------------------------
            virtual void TOCQuery( int InfoClass, ... ) const;
#endif /*  WORKING_VIRTUAL_TOCQUERY */

            //-----------------------------------------------------------------
            /// \brief Merge with another FrAdcData
            ///
            /// \param[in] RHS
            ///     The source of the information to append to this FrAdcData
            ///     structure.
            ///
            /// \return
            ///     A reference to this object
            //-----------------------------------------------------------------
            FrStatData& Merge( const FrStatData& RHS );

            //-----------------------------------------------------------------
            /// \brief equality operator
            ///
            /// \param[in] RHS
            ///     The FrAdcData object to be compared.
            ///
            /// \return
            ///     The value true is returned if this object is equivelent
            ///     to the RHS instance; false otherwise.
            //-----------------------------------------------------------------
            bool operator==( const FrStatData& RHS ) const;

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
        private:
            //-----------------------------------------------------------------
            /// \brief Object with checksum data.
            //-----------------------------------------------------------------
            typedef ObjectWithChecksum< Common::FrStatData > object_type;

            using Common::FrameSpec::Object::Create;

            //-----------------------------------------------------------------
            /// \brief Stream Constructor
            ///
            /// \param[in] Stream
            ///     The stream from which the object is being read.
            ///
            /// \return
            ///    A new instance of this object.
            //-----------------------------------------------------------------
            FrStatData( istream_type& Stream );
        };

        //===================================================================
        //===================================================================
        inline FrStatData::promote_ret_type
        FrStatData::Promote( INT_2U           Source,
                             promote_arg_type Obj,
                             istream_type*    Stream )
        {
            return Object::PromoteObject< Previous::FrStatData, FrStatData >(
                DATA_FORMAT_VERSION, Source, Obj, Stream );
        }

        inline const char*
        FrStatData::StructName( )
        {
            static const char* name = "FrStatData";
            return name;
        }

        inline bool
        FrStatData::operator==( const FrStatData& RHS ) const
        {
            return (
                ( this == &RHS ) ||
                ( nps_type::operator==( RHS ) && ps_type::operator==( RHS ) ) );
        }
    } // namespace Version_8
} // namespace FrameCPP

#endif /* 0 */

#endif /* FrameCPP_VERSION_8__IMPL__FrStatDataClassicIO_HH */
