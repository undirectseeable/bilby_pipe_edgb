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

#ifndef FrameCPP_VERSION_4_FrSimData_HH
#define FrameCPP_VERSION_4_FrSimData_HH

#if !defined( SWIGIMPORTED )
#include <vector>
#endif /* ! defined(SWIGIMPORTED) */

#include "framecpp/Common/Container.hh"
#include "framecpp/Common/SearchContainer.hh"
#include "framecpp/Common/TOCInfo.hh"

#include "framecpp/Version3/FrSimData.hh"

#include "framecpp/Version4/FrameSpec.hh"
#include "framecpp/Version4/STRING.hh"

#include "framecpp/Version4/FrHistory.hh"
#include "framecpp/Version4/FrTable.hh"
#include "framecpp/Version4/FrVect.hh"

namespace FrameCPP
{
    namespace Version_4
    {
        //===================================================================
        // FrSimDataStorage
        //===================================================================

        typedef Previous::FrSimDataStorage FrSimDataStorage;

        //===================================================================
        // FrSimDataRefs
        //===================================================================
        template < typename FrVectType, typename FrTableType >
        class FrSimDataRefsT
        {
        public:
            static const INT_2U MAX_REF = 4;

            typedef typename Common::Container< FrVectType > data_type;
            typedef typename data_type::iterator             iterator;
            typedef typename data_type::const_iterator       const_iterator;

            typedef typename Common::SearchContainer< FrVectType,
                                                      &FrVectType::GetName >
                                                        input_type;
            typedef typename input_type::iterator       input_iterator;
            typedef typename input_type::const_iterator const_input_iterator;

            typedef
                typename Common::SearchContainer< FrTableType,
                                                  &FrTableType::GetNameSlow >
                                                        table_type;
            typedef typename table_type::iterator       table_iterator;
            typedef typename table_type::const_iterator const_table_iterator;

            FrSimDataRefsT( )
            {
            }

            FrSimDataRefsT( const FrSimDataRefsT& Source )
            {
                m_refs.data = Source.m_refs.data;
                m_refs.input = Source.m_refs.input;
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

            inline const input_type&
            RefInput( ) const
            {
                return m_refs.input;
            }

            inline input_type&
            RefInput( )
            {
                return m_refs.input;
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
            struct ref_type
            {
                data_type  data;
                input_type input;
                table_type table;

                inline ref_type( )
                {
                }

                inline FrameCPP::cmn_streamsize_type
                Bytes( const Common::StreamBase& Stream ) const
                {
                    return Stream.PtrStructBytes( ) // data
                        + Stream.PtrStructBytes( ) // input
                        + Stream.PtrStructBytes( ) // table
                        ;
                }

                inline bool
                operator==( const ref_type& RHS ) const
                {
                    return ( ( this == &RHS ) ||
                             ( ( data == RHS.data ) && ( input == RHS.input ) &&
                               ( table == RHS.table ) ) );
                }

                void
                operator( )( Common::IStream& Stream )
                {
                    Stream >> data >> input >> table;
                }

                void
                operator( )( Common::OStream& Stream ) const
                {
                    Stream << data << input << table;
                }
            };

            ref_type m_refs;
        };

        typedef FrSimDataRefsT< FrVect, FrTable > FrSimDataRefs;

        //===================================================================
        //===================================================================
        class FrSimData : public Common::FrameSpec::Object,
                          public FrSimDataStorage,
                          public FrSimDataRefs,
                          public Common::TOCInfo
        {
        public:
            /// \brief Default constructor
            FrSimData( );
            FrSimData( const FrSimData& SimData );
            FrSimData( const std::string& Name,
                       const std::string& Comment,
                       REAL_4             SampleRate );
            FrSimData( Previous::FrSimData& Source, istream_type* Stream );

            static promote_ret_type Promote( INT_2U           Source,
                                             promote_arg_type Obj,
                                             istream_type*    Stream );

            static const char* StructName( );

            static const Common::Description* StructDescription( );

            /// \brief Number of bytes needed to write this structure
            cmn_streamsize_type Bytes( const Common::StreamBase& Stream ) const;

            virtual FrSimData* Create( istream_type& Stream ) const;

            virtual const char* ObjectStructName( ) const;

            virtual void Write( ostream_type& Stream ) const;

            /// \brief Retrive the name
            const std::string& GetNameSlow( ) const;

            /// \brief Merge with another FrAdcData
            FrSimData& Merge( const FrSimData& RHS );

            /// \brief comparison operator
            bool operator==( const FrSimData& RHS ) const;

            /// \brief comparison operator
            virtual bool
            operator==( const Common::FrameSpec::Object& Obj ) const;

#if WORKING_VIRTUAL_TOCQUERY
            virtual void TOCQuery( int InfoClass, ... ) const;
#endif /* WORKING_VIRTUAL_TOCQUERY */

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

            FrSimData( istream_type& Stream );
        };

        inline FrSimData::promote_ret_type
        FrSimData::Promote( INT_2U           Source,
                            promote_arg_type Obj,
                            istream_type*    Stream )
        {
            return Object::PromoteObject< Previous::FrSimData, FrSimData >(
                DATA_FORMAT_VERSION, Source, Obj, Stream );
        }

        inline const char*
        FrSimData::StructName( )
        {
            static const char* name = "FrSimData";
            return name;
        }

        inline bool
        FrSimData::operator==( const FrSimData& RHS ) const
        {
            return ( ( this == &RHS ) ||
                     ( ( m_data == RHS.m_data ) && ( m_refs == RHS.m_refs ) ) );
        }
    } // namespace Version_4
} // namespace FrameCPP
#endif /* FrameCPP_VERSION_4_FrSimData_HH */
