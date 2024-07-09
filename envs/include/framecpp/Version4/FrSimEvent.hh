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

#ifndef FrameCPP_VERSION_4_FrSimEvent_HH
#define FrameCPP_VERSION_4_FrSimEvent_HH

#if !defined( SWIGIMPORTED )
#include <string>
#include <vector>

#include "framecpp/Common/SearchContainer.hh"
#include "framecpp/Common/TOCInfo.hh"
#endif /* ! defined(SWIGIMPORTED) */

#if !defined( SWIGIMPORTED )
#include "framecpp/Version4/FrameSpec.hh"
#include "framecpp/Version4/GPSTime.hh"
#include "framecpp/Version4/FrVect.hh"
#include "framecpp/Version4/FrTable.hh"
#include "framecpp/Version4/STRING.hh"

namespace FrameCPP
{
    namespace Version_4
    {
        //===================================================================
        // FrSimEventNPS
        //===================================================================
        class FrSimEventNPS
        {
        public:
            FrSimEventNPS( );
            FrSimEventNPS( const std::string& Name,
                           const std::string& Comment,
                           const std::string& Inputs,
                           const GPSTime&     Time,
                           const REAL_4       TimeBefore,
                           const REAL_4       TimeAfter,
                           const REAL_4       Amplitude );
            FrSimEventNPS( const FrSimEventNPS& Source );

            const std::string&
            GetName( ) const
            {
                return m_data.name;
            }
            const std::string&
            GetComment( ) const
            {
                return m_data.comment;
            }
            const std::string&
            GetInputs( ) const
            {
                return m_data.inputs;
            }
            const GPSTime&
            GetGTime( ) const
            {
                return m_data.GTime;
            }
            REAL_4
            GetTimeBefore( ) const
            {
                return m_data.timeBefore;
            }
            REAL_4
            GetTimeAfter( ) const
            {
                return m_data.timeAfter;
            }
            REAL_4
            GetAmplitude( ) const
            {
                return m_data.amplitude;
            }

        protected:
            struct storage_type
            {
            public:
                storage_type( );
                storage_type( const storage_type& Source );

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

            private:
                friend class FrSimEventNPS;

                STRING  name;
                STRING  comment;
                STRING  inputs;
                GPSTime GTime;
                REAL_4  timeBefore;
                REAL_4  timeAfter;
                REAL_4  amplitude;
            };

            storage_type m_data;
        };

        inline FrSimEventNPS::storage_type::storage_type( )
        {
        }

        inline FrSimEventNPS::storage_type::storage_type(
            const storage_type& Source )
            : name( Source.name ), comment( Source.comment ),
              inputs( Source.inputs ), GTime( Source.GTime ),
              timeBefore( Source.timeBefore ), timeAfter( Source.timeAfter ),
              amplitude( Source.amplitude )
        {
        }

        //-------------------------------------------------------------------
        //-------------------------------------------------------------------
        template < typename SE >
        void
        FrSimEventNPS::storage_type::Describe( Common::Description& Desc )
        {
            Desc( SE( "name", "STRING", "Name of event." ) );
            Desc( SE( "comment", "STRING", "Descriptor of event" ) );
            Desc( SE(
                "inputs",
                "STRING",
                "Input channels and filter parameters to event process." ) );
            Desc( SE(
                "GTimeS",
                "INT_4U",
                "GPS time in seconds corresponding to reference vale of event,"
                " as defined by the search algorigthm." ) );
            Desc( SE( "GTimeN",
                      "INT_4U",
                      "GPS time in residual nanoseconds relative to GTimeS" ) );
            Desc( SE( "timeBefore",
                      "REAL_4",
                      "Signal duration before (GTimeS.GTimeN)(seconds)" ) );
            Desc( SE( "timeAfter",
                      "REAL_4",
                      "Signal duration after (GTimeS.GTimeN)(seconds)" ) );
            Desc( SE( "amplitude",
                      "REAL_4",
                      "Continuouis output amplitude returned by event" ) );
        }

        inline bool
        FrSimEventNPS::storage_type::operator==( const storage_type& RHS ) const
        {
            return ( ( &RHS == this ) ||
                     ( ( name == RHS.name ) && ( comment == RHS.comment ) &&
                       ( inputs == RHS.inputs ) && ( GTime == RHS.GTime ) &&
                       ( timeBefore == RHS.timeBefore ) &&
                       ( timeAfter == RHS.timeAfter ) &&
                       ( amplitude == RHS.amplitude ) ) );
        }

        inline FrSimEventNPS::FrSimEventNPS( )
        {
        }

        inline FrSimEventNPS::FrSimEventNPS( const std::string& Name,
                                             const std::string& Comment,
                                             const std::string& Inputs,
                                             const GPSTime&     Time,
                                             const REAL_4       TimeBefore,
                                             const REAL_4       TimeAfter,
                                             const REAL_4       Amplitude )
        {
            m_data.name = Name;
            m_data.comment = Comment;
            m_data.inputs = Inputs;
            m_data.GTime = Time;
            m_data.timeBefore = TimeBefore;
            m_data.timeAfter = TimeAfter;
            m_data.amplitude = Amplitude;
        }

        inline FrSimEventNPS::FrSimEventNPS( const FrSimEventNPS& Source )
            : m_data( Source.m_data )
        {
        }

        //===================================================================
        // FrSimEventPST
        //===================================================================

        template < typename TPTR_STRUCT, typename TData, typename TTable >
        class FrSimEventPST
        {
        public:
            static const INT_2U MAX_REF = 2;

            typedef typename Common::SearchContainer< TData, &TData::GetName >
                                                       data_type;
            typedef typename data_type::iterator       iterator;
            typedef typename data_type::const_iterator const_iterator;

            typedef
                typename Common::SearchContainer< TTable, &TTable::GetNameSlow >
                                                        table_type;
            typedef typename table_type::iterator       table_iterator;
            typedef typename table_type::const_iterator const_table_iterator;

            FrSimEventPST( )
            {
            }

            FrSimEventPST( const FrSimEventPST& Source )
            {
                m_refs.data = Source.m_refs.data;
                m_refs.table = Source.m_refs.table;
            }

            inline const data_type&
            RefData( ) const
            {
                return m_refs.data;
            }

            inline data_type&
            RefData( )
            {
                return m_refs.data;
            }

            inline const table_type&
            RefTable( ) const
            {
                return m_refs.table;
            }

            inline table_type&
            RefTable( )
            {
                return m_refs.table;
            }

        protected:
            struct refs_type
            {
                data_type  data;
                table_type table;

                inline FrameCPP::cmn_streamsize_type
                Bytes( const Common::StreamBase& Stream ) const
                {
                    return Stream.PtrStructBytes( ) // data
                        + Stream.PtrStructBytes( ) // table
                        ;
                }

                template < typename SE >
                static inline void
                Describe( Common::Description& Desc )
                {
                    Desc( SE( "data",
                              TPTR_STRUCT::Desc( TData::StructName( ) ) ) );
                    Desc( SE( "table",
                              TPTR_STRUCT::Desc( TTable::StructName( ) ) ) );
                }

                inline bool
                operator==( const refs_type& RHS ) const
                {
                    return (
                        ( this == &RHS ) ||
                        ( ( data == RHS.data ) && ( table == RHS.table ) ) );
                }

                void
                operator( )( Common::IStream& Stream )
                {
                    Stream >> data >> table;
                }

                void
                operator( )( Common::OStream& Stream ) const
                {
                    Stream << data << table;
                }
            };

            refs_type m_refs;
        };

        typedef FrSimEventPST< PTR_STRUCT, FrVect, FrTable > FrSimEventPS;

        //===================================================================
        // FrSimEvent
        //===================================================================
        class FrSimEvent : public Common::FrameSpec::Object,
                           public FrSimEventNPS,
                           public FrSimEventPS,
                           public Common::TOCInfo
        {
        public:
            /// \brief Default constructor
            FrSimEvent( );
            FrSimEvent( const FrSimEvent& eventData );
            FrSimEvent( const std::string& name,
                        const std::string& comment,
                        const std::string& inputs,
                        const GPSTime&     time,
                        const REAL_4       timeBefore,
                        const REAL_4       timeAfter,
                        const REAL_4       amplitude );

            const std::string& GetNameSlow( ) const;

            static promote_ret_type Promote( INT_2U           Source,
                                             promote_arg_type Obj,
                                             istream_type*    Stream );

            static const char* StructName( );

            static const Common::Description* StructDescription( );

            /// \brief Number of bytes needed to write this structure
            cmn_streamsize_type Bytes( const Common::StreamBase& Stream ) const;

            virtual FrSimEvent* Create( istream_type& Stream ) const;

            virtual const char* ObjectStructName( ) const;

#if WORKING_VIRTUAL_TOCQUERY
            virtual void TOCQuery( int InfoClass, ... ) const;
#endif /* WORKING_VIRTUAL_TOCQUERY */

            virtual void Write( ostream_type& Stream ) const;

            /// \brief Merge with another FrSimEvent
            FrSimEvent& Merge( const FrSimEvent& RHS );

            /// \brief comparison operator
            bool operator==( const FrSimEvent& RHS ) const;

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

#if !WORKING_VIRTUAL_TOCQUERY
            virtual void vTOCQuery( int InfoClass, va_list vl ) const;
#endif /* ! WORKING_VIRTUAL_TOCQUERY */

        private:
            using Common::FrameSpec::Object::Create;

            FrSimEvent( istream_type& Stream );
        };

        inline FrameCPP::cmn_streamsize_type
        FrSimEvent::Bytes( const Common::StreamBase& Stream ) const
        {
            return m_data.Bytes( ) + m_refs.Bytes( Stream ) +
                Stream.PtrStructBytes( ) // next
                ;
        }

        inline FrSimEvent::promote_ret_type
        FrSimEvent::Promote( INT_2U           Source,
                             promote_arg_type Obj,
                             istream_type*    Stream )
        {
            return Common::PromoteObject( DATA_FORMAT_VERSION, Source, Obj );
        }

        inline const char*
        FrSimEvent::StructName( )
        {
            static const char* name = "FrSimEvent";
            return name;
        }

        inline bool
        FrSimEvent::operator==( const FrSimEvent& RHS ) const
        {
            return ( ( this == &RHS ) ||
                     ( ( m_data == RHS.m_data ) && ( m_refs == RHS.m_refs ) ) );
        }
    } // namespace Version_4
} // namespace FrameCPP

#endif /* ! defined(SWIGIMPORTED) */

#endif /* FrameCPP_VERSION_4_FrSimEvent_HH */
