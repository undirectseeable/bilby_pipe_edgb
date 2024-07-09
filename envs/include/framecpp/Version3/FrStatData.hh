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

#ifndef FrameCPP_VERSION_3_FrStatData_HH
#define FrameCPP_VERSION_3_FrStatData_HH

#include <vector>

#include <boost/shared_ptr.hpp>

#include "framecpp/Common/Description.hh"
#include "framecpp/Common/SearchContainer.hh"
#include "framecpp/Common/FrStatData.hh"

#include "framecpp/Version3/FrameSpec.hh"
#include "framecpp/Version3/STRING.hh"
#include "framecpp/Version3/PTR_STRUCT.hh"

#include "framecpp/Version3/FrDetector.hh"
#include "framecpp/Version3/FrSE.hh"
#include "framecpp/Version3/FrVect.hh"

namespace FrameCPP
{
    namespace Version_3
    {
        //===================================================================
        //===================================================================
        class FrStatDataStorage
        {
        public:
            typedef INT_4U timeStart_type;
            typedef INT_4U timeEnd_type;
            typedef INT_4U version_type;

            FrStatDataStorage( );

            FrStatDataStorage( const std::string&   Name,
                               const std::string&   Comment,
                               const timeStart_type TimeStart,
                               const timeEnd_type   TimeEnd,
                               const version_type   Version );

            const std::string& GetName( ) const;
            const std::string& GetComment( ) const;
            timeStart_type     GetTimeStart( ) const;
            timeEnd_type       GetTimeEnd( ) const;
            version_type       GetVersion( ) const;

            bool operator==( const FrStatDataStorage& RHS ) const;

        protected:
            struct data_type
            {
                STRING         name;
                STRING         comment;
                timeStart_type timeStart;
                timeEnd_type   timeEnd;
                version_type   version;

                cmn_streamsize_type Bytes( ) const;
                static void         Describe( Common::Description& Desc );

                bool operator==( const data_type& RHS ) const;
                void operator( )( Common::IStream& Stream );
                void operator( )( Common::OStream& Stream ) const;
            };

            data_type m_data;
        };

        inline cmn_streamsize_type
        FrStatDataStorage::data_type::Bytes( ) const
        {
            return name.Bytes( ) + comment.Bytes( ) + sizeof( timeStart ) +
                sizeof( timeEnd ) + sizeof( version );
        }

        inline void
        FrStatDataStorage::data_type::Describe( Common::Description& Desc )
        {
            Desc( FrSE( "name", "STRING" ) );
            Desc( FrSE( "comment", "STRING" ) );
            Desc( FrSE( "timeStart", "INT_4U" ) );
            Desc( FrSE( "timeEnd", "INT_4U" ) );
            Desc( FrSE( "version", "INT_4U" ) );
        }

        inline bool
        FrStatDataStorage::data_type::operator==( const data_type& RHS ) const
        {
            return ( ( this == &RHS ) ||
                     ( ( name == RHS.name ) && ( comment == RHS.comment ) &&
                       ( timeStart == RHS.timeStart ) &&
                       ( timeEnd == RHS.timeEnd ) &&
                       ( version == RHS.version ) ) );
        }

        inline void
        FrStatDataStorage::data_type::operator( )( Common::IStream& Stream )
        {
            Stream >> name >> comment >> timeStart >> timeEnd >> version;
        }

        inline void
        FrStatDataStorage::data_type::
        operator( )( Common::OStream& Stream ) const
        {
            Stream << name << comment << timeStart << timeEnd << version;
        }

        inline FrStatDataStorage::FrStatDataStorage( )
        {
        }

        inline FrStatDataStorage::FrStatDataStorage(
            const std::string&   Name,
            const std::string&   Comment,
            const timeStart_type TimeStart,
            const timeEnd_type   TimeEnd,
            const version_type   Version )
        {
            m_data.name = Name;
            m_data.comment = Comment;
            m_data.timeStart = TimeStart;
            m_data.timeEnd = TimeEnd;
            m_data.version = Version;
        }

        inline const std::string&
        FrStatDataStorage::GetName( ) const
        {
            return m_data.name;
        }

        inline const std::string&
        FrStatDataStorage::GetComment( ) const
        {
            return m_data.comment;
        }

        inline FrStatDataStorage::timeStart_type
        FrStatDataStorage::GetTimeStart( ) const
        {
            return m_data.timeStart;
        }

        inline FrStatDataStorage::timeEnd_type
        FrStatDataStorage::GetTimeEnd( ) const
        {
            return m_data.timeEnd;
        }

        inline FrStatDataStorage::version_type
        FrStatDataStorage::GetVersion( ) const
        {
            return m_data.version;
        }

        inline bool
        FrStatDataStorage::operator==( const FrStatDataStorage& RHS ) const
        {
            return ( m_data == RHS.m_data );
        }
        //===================================================================
        //===================================================================
        template < typename TDetector, typename TVect >
        class FrStatDataRefsT
        {
        public:
            static const INT_2U MAX_REF = 2;

            typedef boost::shared_ptr< TDetector >       detector_type;
            typedef boost::shared_ptr< TDetector > const const_detector_type;

            typedef typename Common::SearchContainer< TVect, &TVect::GetName >
                                                       data_type;
            typedef typename data_type::iterator       iterator;
            typedef typename data_type::const_iterator const_iterator;

            detector_type
            GetDetector( )
            {
                return m_refs.detector;
            }

            const_detector_type
            GetDetector( ) const
            {
                return m_refs.detector;
            }

            const data_type&
            RefData( ) const
            {
                return m_refs.data;
            }

            data_type&
            RefData( )
            {
                return m_refs.data;
            }

            inline detector_type*
            AddressOfDetector( ) const
            {
                return &m_refs.detector;
            }

            inline void
            SetDetector( detector_type Detector )
            {
                m_refs.detector = Detector;
            }

            bool operator==( const FrStatDataRefsT& RHS ) const;

        protected:
            struct ref_type
            {
                detector_type detector;
                data_type     data;

                inline cmn_streamsize_type
                Bytes( const Common::StreamBase& Stream ) const
                {
                    return Stream.PtrStructBytes( ) // detector
                        + Stream.PtrStructBytes( ) // data
                        ;
                }

                static inline void
                Describe( Common::Description& Desc )
                {
                    Desc( FrSE(
                        "detector",
                        PTR_STRUCT::Desc(
                            detector_type::element_type::StructName( ) ) ) );
                    Desc( FrSE( "data",
                                PTR_STRUCT::Desc( TVect::StructName( ) ) ) );
                }

                inline bool
                operator==( const ref_type& RHS ) const
                {
                    return ( ( this == &RHS ) ||
                             ( ( ( detector == RHS.detector ) ||
                                 ( detector && RHS.detector &&
                                   ( *detector == *( RHS.detector ) ) ) ) &&
                               ( data == RHS.data ) ) );
                }

                inline void
                operator( )( Common::IStream& Stream )
                {
                    Stream >> &detector >> data;
                }

                inline void
                operator( )( Common::OStream& Stream ) const
                {
                    Common::OStream::Pointer detector_ptr( detector );

                    Stream << detector_ptr << data;
                }
            };

            ref_type m_refs;
        };

        template < typename TDetector, typename TVect >
        inline bool
        FrStatDataRefsT< TDetector, TVect >::
        operator==( const FrStatDataRefsT& RHS ) const
        {
            return ( m_refs == RHS.m_refs );
        }

        typedef FrStatDataRefsT< FrDetector, FrVect > FrStatDataRefs;

        //===================================================================
        //===================================================================
        class FrStatData : public Common::FrStatData,
                           public FrStatDataStorage,
                           public FrStatDataRefs
        {
        public:
            typedef FrStatDataStorage nps_type;
            typedef FrStatDataRefs    ps_type;

            static const INT_4U ALL_VERSIONS;
            static const INT_4U LATEST_VERSION;

            /// \brief Default constructor
            FrStatData( );
            FrStatData( const FrStatData& statData );
            FrStatData( const std::string& name,
                        const std::string& comment,
                        INT_4U             timeStart,
                        INT_4U             timeEnd,
                        INT_4U             version );

            static promote_ret_type Promote( INT_2U           Source,
                                             promote_arg_type Obj,
                                             istream_type*    Stream );

            static const char* StructName( );

            static const Common::Description* StructDescription( );

            /// \brief Number of bytes needed to write this structure
            cmn_streamsize_type Bytes( const Common::StreamBase& Stream ) const;

            virtual FrStatData* Clone( ) const;

            virtual FrStatData* Create( istream_type& Stream ) const;

            virtual fr_detector_type
            GetDetector( ) const
            {
                return FrStatDataRefs::GetDetector( );
            }

            virtual const char* ObjectStructName( ) const;

            virtual void Write( ostream_type& Stream ) const;

            /// \brief Merge with another FrAdcData
            FrStatData& Merge( const FrStatData& RHS );

            /// \brief comparison operator
            bool operator==( const FrStatData& RHS ) const;

            /// \brief comparison operator
            virtual bool
            operator==( const Common::FrameSpec::Object& Obj ) const;

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
            using Common::FrameSpec::Object::Create;

            FrStatData( istream_type& Stream );
        };

        //===================================================================
        //===================================================================
#if WORKING
        inline int
        FrStatData::Query::CompareFilePosition::
        operator( )( const query_info_type& LHS,
                     const query_info_type& RHS ) const
        {
            return LHS.s_fr_stat_pos < RHS.s_fr_stat_pos;
        }

        inline INT_4U
        FrStatData::Query::size( ) const
        {
            return m_fr_stat_data.size( );
        }
#endif /* WORKING */

        //===================================================================
        //===================================================================
        inline FrStatData::promote_ret_type
        FrStatData::Promote( INT_2U           Source,
                             promote_arg_type Obj,
                             istream_type*    Stream )
        {
            return Common::PromoteObject( DATA_FORMAT_VERSION, Source, Obj );
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
    } // namespace Version_3
} // namespace FrameCPP
#endif /* FrameCPP_VERSION_3_FrStatData_HH */
