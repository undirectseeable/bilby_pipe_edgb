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

#ifndef FrameCPP_VERSION_4_FrStatData_HH
#define FrameCPP_VERSION_4_FrStatData_HH

#include <vector>

#include <boost/shared_ptr.hpp>

#include "framecpp/Common/SearchContainer.hh"
#include "framecpp/Common/TOCInfo.hh"
#include "framecpp/Common/FrStatData.hh"

#include "framecpp/Version3/FrStatData.hh"

#include "framecpp/Version4/FrameSpec.hh"
#include "framecpp/Version4/STRING.hh"
#include "framecpp/Version4/PTR_STRUCT.hh"

#include "framecpp/Version4/FrDetector.hh"
#include "framecpp/Version4/FrSE.hh"
#include "framecpp/Version4/FrTable.hh"
#include "framecpp/Version4/FrTOC.hh"
#include "framecpp/Version4/FrVect.hh"

namespace FrameCPP
{
    namespace Version_4
    {
        //===================================================================
        /// \brief Storage of data members for the FrStatData structure
        ///
        /// This class contains the data members of the FrStatData structure
        /// that are not referenced by a pointer.
        /// This allows for easier migration into future frame
        /// specifications.
        //===================================================================
        class FrStatDataNPS
        {
        public:
            typedef INT_4U timeStart_type;
            typedef INT_4U timeEnd_type;
            typedef INT_4U version_type;

            //-----------------------------------------------------------------
            /// \brief Constructor
            ///
            /// Default constructor
            ///
            /// \return
            ///     A new FrStatDataNPS object
            //-----------------------------------------------------------------
            FrStatDataNPS( );

            //-----------------------------------------------------------------
            /// \brief Constructor
            ///
            /// \param[in] Name
            ///     Static data name
            /// \param[in] Comment
            ///     Comment
            /// \param[in] Representation
            ///     Type of static data being represented
            /// \param[in] TimeStart
            ///     Start time of  static data validity
            /// \param[in] TimeEnd
            ///     End time of static data validity
            /// \param[in] Version
            ///     Version number for this static structure.
            ///
            /// \return
            ///     A new FrStatDataNPS object
            //-----------------------------------------------------------------
            FrStatDataNPS( const std::string&   Name,
                           const std::string&   Comment,
                           const std::string&   Representation,
                           const timeStart_type TimeStart,
                           const timeEnd_type   TimeEnd,
                           const version_type   Version );

            //-----------------------------------------------------------------
            /// \brief Retrieve static data name
            ///
            /// \return
            ///     The static data name
            //-----------------------------------------------------------------
            const std::string& GetName( ) const;

            //-----------------------------------------------------------------
            /// \brief Retrieve the comment
            ///
            /// \return
            ///     The comment
            //-----------------------------------------------------------------
            const std::string& GetComment( ) const;

            //-----------------------------------------------------------------
            /// \brief Retrieve the type of static data
            ///
            /// \return
            ///     The type of static data being represente
            //-----------------------------------------------------------------
            const std::string& GetRepresentation( ) const;

            //-----------------------------------------------------------------
            /// \brief Retrieve the start time
            ///
            /// \return
            ///     The start time of the static data validity.
            //-----------------------------------------------------------------
            timeStart_type GetTimeStart( ) const;

            //-----------------------------------------------------------------
            /// \brief Retrieve the end time
            ///
            /// \return
            ///     The end time of the static data validity.
            //-----------------------------------------------------------------
            timeEnd_type GetTimeEnd( ) const;

            //-----------------------------------------------------------------
            /// \brief Retrieve the version number
            ///
            /// \return
            ///    The version number for this static structure.
            //-----------------------------------------------------------------
            version_type GetVersion( ) const;

            //-----------------------------------------------------------------
            /// \brief Comparison operator
            ///
            /// \param[in] RHS
            ///     Object to compare for equality.
            //-----------------------------------------------------------------
            bool operator==( const FrStatDataNPS& RHS ) const;

        protected:
            //-----------------------------------------------------------------
            /// \todo Needs documentation
            //-----------------------------------------------------------------
            struct storage_type
            {
            public:
                //---------------------------------------------------------------
                /// \brief Stream size of object
                ///
                /// \return
                ///     The number of bytes needed to write or read this
                ///     class of object to or from a stream.
                //---------------------------------------------------------------
                cmn_streamsize_type Bytes( ) const;

                //---------------------------------------------------------------
                /// \brief Supply description
                ///
                /// \param[out] Desc
                ///     Storage for the description of the structure.
                //---------------------------------------------------------------
                template < typename SE >
                static void Describe( Common::Description& Desc );

                //---------------------------------------------------------------
                /// \brief Comparison operator
                ///
                /// \param[in] RHS
                ///     Object to compare for equality.
                //---------------------------------------------------------------
                bool operator==( const storage_type& RHS ) const;

                //---------------------------------------------------------------
                /// \brief Input elements from the stream
                ///
                /// \param[in] Stream
                ///     The stream from which the elements are read.
                //---------------------------------------------------------------
                void operator( )( Common::IStream& Stream );

                //---------------------------------------------------------------
                /// \brief Output elements to the stream
                ///
                /// \param[in] Stream
                ///     The stream to which the elements are written.
                //---------------------------------------------------------------
                void operator( )( Common::OStream& Stream ) const;

                //---------------------------------------------------------------
                /// \brief Copy contents
                ///
                /// \param[in] Source
                ///     Source to be copied
                //---------------------------------------------------------------
                void operator( )( const FrStatDataNPS& Source );

                //---------------------------------------------------------------
                /// \brief Copy contents
                ///
                /// \param[in] Source
                ///     Source to be copied
                ///
                /// \todo Need to modify Version 3 FrStatData to follow NPS
                //---------------------------------------------------------------
                void operator( )( const Previous::FrStatDataStorage& Source );

            private:
                friend class FrStatDataNPS;

                //---------------------------------------------------------------
                /// Static data name
                //---------------------------------------------------------------
                STRING name;
                //---------------------------------------------------------------
                /// Comment for static data
                //---------------------------------------------------------------
                STRING comment;
                //---------------------------------------------------------------
                /// Type of static data being represented. e,g., calibration,
                /// swept sine, pole-zero, FIR or IIR coefficients...
                //---------------------------------------------------------------
                STRING representation;
                //---------------------------------------------------------------
                /// Start time of static data validity.
                /// GPS time in integer seconds since GPS standard epoch.
                //---------------------------------------------------------------
                timeStart_type timeStart;
                //---------------------------------------------------------------
                /// End time of static data validity.
                /// A value of zero represents the end time being unknown.
                /// GPS time in integer seconds since GPS standard epoch.
                //---------------------------------------------------------------
                timeEnd_type timeEnd;
                //---------------------------------------------------------------
                /// Version number for this static structure.
                /// i.e., the counter begins at 0 and is incremented by 1
                /// thereafter.
                /// Updated statics for the same time window
                /// (e.g., modified calibration data) will be identified by
                /// identified by unique version numbers.
                //---------------------------------------------------------------
                version_type version;
            };

            storage_type m_data;
        };

        //-------------------------------------------------------------------
        /// Calculate the number of bytes that will be written to the stream
        /// for this strucutre.
        //-------------------------------------------------------------------
        inline cmn_streamsize_type
        FrStatDataNPS::storage_type::Bytes( ) const
        {
            return name.Bytes( ) + comment.Bytes( ) + representation.Bytes( ) +
                sizeof( timeStart ) + sizeof( timeEnd ) + sizeof( version );
        }

        //-------------------------------------------------------------------
        /// Supplies the FrSE description for each element of this object
        /// that will be written to the stream.
        //-------------------------------------------------------------------
        template < typename SE >
        inline void
        FrStatDataNPS::storage_type::Describe( Common::Description& Desc )
        {
            Desc( SE( "name", "STRING" ) );
            Desc( SE( "comment", "STRING" ) );
            Desc( SE( "representation", "STRING" ) );
            Desc( SE( "timeStart", "INT_4U" ) );
            Desc( SE( "timeEnd", "INT_4U" ) );
            Desc( SE( "version", "INT_4U" ) );
        }

        //-------------------------------------------------------------------
        /// Tests the equality of the two FrTableNPS objects.
        //-------------------------------------------------------------------
        inline bool
        FrStatDataNPS::storage_type::operator==( const storage_type& RHS ) const
        {
            return ( ( this == &RHS ) ||
                     ( ( name == RHS.name ) && ( comment == RHS.comment ) &&
                       ( representation == RHS.representation ) &&
                       ( timeStart == RHS.timeStart ) &&
                       ( timeEnd == RHS.timeEnd ) &&
                       ( version == RHS.version ) ) );
        }

        inline void
        FrStatDataNPS::storage_type::operator( )( Common::IStream& Stream )
        {
            Stream >> name >> comment >> representation >> timeStart >>
                timeEnd >> version;
        }

        inline void
        FrStatDataNPS::storage_type::
        operator( )( Common::OStream& Stream ) const
        {
            Stream << name << comment << representation << timeStart << timeEnd
                   << version;
        }

        inline void
        FrStatDataNPS::storage_type::operator( )( const FrStatDataNPS& Source )
        {
            name = Source.GetName( );
            comment = Source.GetComment( );
            representation = Source.GetRepresentation( );
            timeStart = Source.GetTimeStart( );
            timeEnd = Source.GetTimeEnd( );
            version = Source.GetVersion( );
        }

        inline void
        FrStatDataNPS::storage_type::
        operator( )( const Previous::FrStatDataStorage& Source )
        {
            name = Source.GetName( );
            comment = Source.GetComment( );
            timeStart = Source.GetTimeStart( );
            timeEnd = Source.GetTimeEnd( );
            version = Source.GetVersion( );
        }

        //-------------------------------------------------------------------
        ///
        //-------------------------------------------------------------------
        inline FrStatDataNPS::FrStatDataNPS( )
        {
        }

        //-------------------------------------------------------------------
        ///
        //-------------------------------------------------------------------
        inline FrStatDataNPS::FrStatDataNPS( const std::string& Name,
                                             const std::string& Comment,
                                             const std::string& Representation,
                                             const timeStart_type TimeStart,
                                             const timeEnd_type   TimeEnd,
                                             const version_type   Version )
        {
            m_data.name = Name;
            m_data.comment = Comment;
            m_data.representation = Representation;
            m_data.timeStart = TimeStart;
            m_data.timeEnd = TimeEnd;
            m_data.version = Version;
        }

        //-------------------------------------------------------------------
        ///
        //-------------------------------------------------------------------
        inline const std::string&
        FrStatDataNPS::GetName( ) const
        {
            return m_data.name;
        }

        //-------------------------------------------------------------------
        ///
        //-------------------------------------------------------------------
        inline const std::string&
        FrStatDataNPS::GetComment( ) const
        {
            return m_data.comment;
        }

        //-------------------------------------------------------------------
        ///
        //-------------------------------------------------------------------
        inline const std::string&
        FrStatDataNPS::GetRepresentation( ) const
        {
            return m_data.representation;
        }

        //-------------------------------------------------------------------
        ///
        //-------------------------------------------------------------------
        inline FrStatDataNPS::timeStart_type
        FrStatDataNPS::GetTimeStart( ) const
        {
            return m_data.timeStart;
        }

        //-------------------------------------------------------------------
        ///
        //-------------------------------------------------------------------
        inline FrStatDataNPS::timeEnd_type
        FrStatDataNPS::GetTimeEnd( ) const
        {
            return m_data.timeEnd;
        }

        //-------------------------------------------------------------------
        ///
        //-------------------------------------------------------------------
        inline FrStatDataNPS::version_type
        FrStatDataNPS::GetVersion( ) const
        {
            return m_data.version;
        }

        inline bool
        FrStatDataNPS::operator==( const FrStatDataNPS& RHS ) const
        {
            return ( m_data == RHS.m_data );
        }
        //===================================================================
        //===================================================================
        template < typename TPTR_STRUCT,
                   typename TDetector,
                   typename TVect,
                   typename TTable >
        class FrStatDataPST
        {
        public:
            static const INT_2U MAX_REF = 3;

            typedef boost::shared_ptr< TDetector > detector_type;

            typedef boost::shared_ptr< TDetector > const const_detector_type;

            typedef typename Common::SearchContainer< TVect, &TVect::GetName >
                                                       data_type;
            typedef typename data_type::iterator       iterator;
            typedef typename data_type::const_iterator const_iterator;

            typedef
                typename Common::SearchContainer< TTable, &TTable::GetNameSlow >
                                                        table_type;
            typedef typename table_type::iterator       table_iterator;
            typedef typename table_type::const_iterator const_table_iterator;

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
            const table_type&
            RefTable( ) const
            {
                return m_refs.table;
            }
            table_type&
            RefTable( )
            {
                return m_refs.table;
            }

            inline detector_type*
            AddressOfDetector( ) const
            {
                return &( const_cast< ref_type& >( m_refs ).detector );
            }

#if 0
      inline void
      SetDetector( TDetector* Detector )
      {
	m_refs.detector = Detector;
      }
#endif /* 0 */

            inline void
            SetDetector( detector_type Detector )
            {
                m_refs.detector = Detector;
            }

            bool operator==( const FrStatDataPST& RHS ) const;

        protected:
            struct ref_type
            {
                detector_type detector;
                data_type     data;
                table_type    table;

                inline cmn_streamsize_type
                Bytes( const Common::StreamBase& Stream ) const
                {
                    return Stream.PtrStructBytes( ) // detector
                        + Stream.PtrStructBytes( ) // data
                        + Stream.PtrStructBytes( ) // table
                        ;
                }

                template < typename SE >
                static inline void
                Describe( Common::Description& Desc )
                {
                    Desc( SE( "detector",
                              TPTR_STRUCT::Desc( TDetector::StructName( ) ) ) );
                    Desc( SE( "data",
                              TPTR_STRUCT::Desc( TVect::StructName( ) ) ) );
                    Desc( SE( "table",
                              TPTR_STRUCT::Desc( TTable::StructName( ) ) ) );
                }

                inline bool
                operator==( const ref_type& RHS ) const
                {
                    return ( ( this == &RHS ) ||
                             ( ( ( detector == RHS.detector ) ||
                                 ( detector && RHS.detector &&
                                   ( *detector == *( RHS.detector ) ) ) ) &&
                               ( data == RHS.data ) &&
                               ( table == RHS.table ) ) );
                }

                inline void
                operator( )( Common::IStream& Stream )
                {
                    Stream >> &detector >> data >> table;
                }

                inline void
                operator( )( Common::OStream& Stream ) const
                {
                    Common::OStream::Pointer detector_ptr( detector );

                    Stream << detector_ptr << data << table;
                }
            };

            ref_type m_refs;
        };

        template < typename TPTR_STRUCT,
                   typename TDetector,
                   typename TVect,
                   typename TTable >
        inline bool
        FrStatDataPST< TPTR_STRUCT, TDetector, TVect, TTable >::
        operator==( const FrStatDataPST& RHS ) const
        {
            return ( m_refs == RHS.m_refs );
        }

        typedef FrStatDataPST< PTR_STRUCT, FrDetector, FrVect, FrTable >
            FrStatDataPS;

        //===================================================================
        //===================================================================
        class FrStatData : public Common::FrStatData,
                           public FrStatDataNPS,
                           public FrStatDataPS,
                           public Common::TOCInfo
        {
        public:
            typedef FrStatDataNPS nps_type;
            typedef FrStatDataPS  ps_type;

            static const INT_4U ALL_VERSIONS;
            static const INT_4U LATEST_VERSION;

#if WORKING
            class Query
            {
            public:
                ~Query( );
                void Add( const std::string&            NamePattern,
                          const std::string&            DetectorPattern,
                          const LDASTools::AL::GPSTime& StartTime,
                          const LDASTools::AL::GPSTime& EndTime,
                          const INT_4U                  Version );

                void   Reset( istream_type& Stream );
                INT_4U size( ) const;

                FrStatData* operator[]( INT_4U Index );

            private:
                struct query_info_type
                {
                    FrStatData* s_fr_stat_data;
                    INT_8U      s_fr_stat_pos;
                    bool        s_own;
                    // Information needed when looking for the latest version
                    std::string s_nameStat;
                    std::string s_detector;
                    INT_4U      s_tStart;
                    INT_4U      s_tEnd;
                    INT_4U      s_version;
                };

                typedef std::vector< query_info_type > data_type;

                class CompareFilePosition
                {
                public:
                    int operator( )( const query_info_type& LHS,
                                     const query_info_type& RHS ) const;
                };

                std::list< fr_detector_type > m_detectors;
                bool                          m_dirty;
                data_type                     m_fr_stat_data;
                istream_type*                 m_stream;

                void add( const FrTOC::StatTypeKey&   Key,
                          const FrTOC::StatType_type& Data,
                          INT_4U                      Start,
                          INT_4U                      Stop,
                          INT_4U                      Version );

                void load( );
                std::unique_ptr< FrStatData >
                read_fr_stat_data( istream_type&      Stream,
                                   const std::string& Detector,
                                   INT_8U             PositionOfStatData );
            };
#endif /* WORKING */

            /// \brief Default constructor
            FrStatData( );
            FrStatData( const FrStatData& statData );
            FrStatData( const std::string& name,
                        const std::string& comment,
                        const std::string& representation,
                        INT_4U             timeStart,
                        INT_4U             timeEnd,
                        INT_4U             version );
            FrStatData( const Previous::FrStatData& Source,
                        istream_type*               Stream );

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
                return FrStatDataPS::GetDetector( );
            }

            virtual const char* ObjectStructName( ) const;

            virtual void Write( ostream_type& Stream ) const;

#if WORKING_VIRTUAL_TOCQUERY
            virtual void TOCQuery( int InfoClass, ... ) const;
#endif /*  WORKING_VIRTUAL_TOCQUERY */

            /// \brief Merge with another FrAdcData
            FrStatData& Merge( const FrStatData& RHS );

            //-----------------------------------------------------------------
            /// \brief Comparison operator
            ///
            /// \param[in] RHS
            ///     Object to compare for equality.
            //-----------------------------------------------------------------
            bool operator==( const FrStatData& RHS ) const;

            //-----------------------------------------------------------------
            /// \brief Comparison operator
            ///
            /// \param[in] RHS
            ///     Object to compare for equality.
            //-----------------------------------------------------------------
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

#if !WORKING_VIRTUAL_TOCQUERY
            virtual void vTOCQuery( int InfoClass, va_list vl ) const;
#endif /* ! WORKING_VIRTUAL_TOCQUERY */

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
    } // namespace Version_4
} // namespace FrameCPP
#endif /* FrameCPP_VERSION_4_FrStatData_HH */
