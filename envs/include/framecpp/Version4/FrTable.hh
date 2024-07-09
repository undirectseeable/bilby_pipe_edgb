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

#ifndef FrameCPP_VERSION_4_FrTable_HH
#define FrameCPP_VERSION_4_FrTable_HH

#if !defined( SWIGIMPORTED )
#include <vector>
#endif /* ! defined(SWIGIMPORTED) */

#include "framecpp/Version4/FrameSpec.hh"

#include "framecpp/Common/SearchContainer.hh"

#include "framecpp/Version4/Dimension.hh"
#include "framecpp/Version4/PTR_STRUCT.hh"
#include "framecpp/Version4/FrVect.hh"
#include "framecpp/Version4/GPSTime.hh"
#include "framecpp/Version4/STRING.hh"

namespace FrameCPP
{
    namespace Version_4
    {
        //===================================================================
        /// \brief Storage of data members for the FrTable structure
        ///
        /// This class contains the data members of the FrTable structure
        /// that are not referenced by a pointer.
        /// This allows for easier migration into future frame
        /// specifications.
        //===================================================================
        class FrTableNPS
        {
        public:
            //-----------------------------------------------------------------
            /// \brief Constructor
            ///
            /// Default constructor
            ///
            /// \return
            ///     A new FrTableNPS object
            //-----------------------------------------------------------------
            FrTableNPS( );

            //-----------------------------------------------------------------
            /// \brief Copy Constructor
            ///
            /// \param[in] Source
            ///     The source to be copied.
            ///
            /// \return
            ///     A new FrTableNPS object
            //-----------------------------------------------------------------
            FrTableNPS( const FrTableNPS& Source );

            //-----------------------------------------------------------------
            /// \brief Add additional information to the comment
            ///
            /// \param[in] comment
            ///     The text to append to the comment.
            //-----------------------------------------------------------------
            void AppendComment( const std::string& comment );

            //-----------------------------------------------------------------
            /// \brief Retrieve the comment
            ///
            /// \return
            ///     The text of the comment associated with the table.
            //-----------------------------------------------------------------
            const std::string& GetComment( ) const;

            //-----------------------------------------------------------------
            /// \brief Retrieve the name.
            ///
            /// \return
            ///     The name associated with the table
            //-----------------------------------------------------------------
            const std::string& GetName( ) const;

        protected:
            //-----------------------------------------------------------------
            /// \brief Retrieve the comment
            ///
            /// \return
            ///     The text of the comment associated with the table.
            //-----------------------------------------------------------------
            std::string& getComment( );

            //-----------------------------------------------------------------
            /// \brief Establish name
            ///
            /// \param[in] Name
            ///     The name to associate with the table
            //-----------------------------------------------------------------
            void setName( const std::string& Name );

            //-----------------------------------------------------------------
            //-----------------------------------------------------------------
            struct data_type
            {
                friend class FrTableNPS;

                //---------------------------------------------------------------
                /// \brief Default constructor
                ///
                /// \return
                ///     A new instance of data_type
                //---------------------------------------------------------------
                data_type( );

                //---------------------------------------------------------------
                /// \brief Copy constructor
                ///
                /// \param[in] Source
                ///     The source from which to constuct the data_type
                ///     instance.
                ///
                /// \return
                ///     A new instance of data_type
                //---------------------------------------------------------------
                data_type( const data_type& Source );

                //---------------------------------------------------------------
                /// \brief Stream size of object
                ///
                /// \return
                ///     The number of bytes needed to write or read this
                ///     class of object to or from a stream.
                //---------------------------------------------------------------
                cmn_streamsize_type
                Bytes( const Common::StreamBase& Stream ) const;

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
                bool operator==( const data_type& RHS ) const;

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
                //---------------------------------------------------------------
                /// \brief Table name
                //---------------------------------------------------------------
                STRING name;

                //---------------------------------------------------------------
                /// \brief Table comment
                //---------------------------------------------------------------
                STRING comment;
            };

            //-----------------------------------------------------------------
            //-----------------------------------------------------------------
            data_type m_data;
        };

        inline FrTableNPS::data_type::data_type( ) : name( "" ), comment( "" )
        {
        }

        //-------------------------------------------------------------------
        /// Calculate the number of bytes that will be written to the stream
        /// for this strucutre.
        //-------------------------------------------------------------------
        inline FrameCPP::cmn_streamsize_type
        FrTableNPS::data_type::Bytes( const Common::StreamBase& Stream ) const
        {
            cmn_streamsize_type retval = name.Bytes( ) + comment.Bytes( );

            return retval;
        }

        //-------------------------------------------------------------------
        /// Supplies the FrSE description for each element of this object
        /// that will be written to the stream.
        //-------------------------------------------------------------------
        template < typename SE >
        inline void
        FrTableNPS::data_type::Describe( Common::Description& Desc )
        {
            Desc( SE( "name", "STRING", "Name of this table" ) );
            Desc( SE( "comment", "STRING", "Comment" ) );
        }

        //-------------------------------------------------------------------
        /// Tests the equality of the two FrTableNPS objects.
        //-------------------------------------------------------------------
        inline bool
        FrTableNPS::data_type::operator==( const data_type& RHS ) const
        {
            return ( ( name == RHS.name ) && ( comment == RHS.comment ) );
        }

        inline void
        FrTableNPS::AppendComment( const std::string& comment )
        {
            return FrameCPP::Common::AppendComment( getComment( ), comment );
        }

        inline const std::string&
        FrTableNPS::GetComment( ) const
        {
            return m_data.comment;
        }

        inline const std::string&
        FrTableNPS::GetName( ) const
        {
            return m_data.name;
        }

        inline std::string&
        FrTableNPS::getComment( )
        {
            return m_data.comment;
        }

        inline void
        FrTableNPS::setName( const std::string& Name )
        {
            m_data.name = Name;
        }
        //===================================================================
        /// \brief Pointer structure members of the FrTable structure.
        //===================================================================
        template < typename TPTR_STRUCT, typename TColumn >
        class FrTablePST
        {
        public:
            static const INT_2U MAX_REF = 1;

            typedef TPTR_STRUCT ptr_struct_type;
            typedef TColumn     column_type;

            typedef typename column_type::iterator       iterator;
            typedef typename column_type::const_iterator const_iterator;

            //-----------------------------------------------------------------
            /// \brief Collection of column names
            ///
            /// This storage class is used to abstract the container type
            /// used to maintain the collection of column names used in the
            /// table.
            /// The container maintains the column order of the column names.
            //-----------------------------------------------------------------
            typedef std::vector< STRING > column_name_container_type;

            //-----------------------------------------------------------------
            /// \brief Storage class for the number of rows.
            ///
            /// This storage class is used to abstract the data type used to
            /// store the number of rows in the table.
            //-----------------------------------------------------------------
            typedef INT_4U nRow_type;

            //-----------------------------------------------------------------
            /// \brief Storage class for the number of columns.
            ///
            /// This storage class is used to abstract the data type used to
            /// store the number of columns in the table.
            //-----------------------------------------------------------------
            typedef INT_2U nColumn_type;

            //-----------------------------------------------------------------
            /// \brief Retrieve the list of column names.
            ///
            /// \return
            ///     The set of column names in column order.
            //-----------------------------------------------------------------
            column_name_container_type
            GetColumnName( ) const
            {
                column_name_container_type columnName;

                for ( const_iterator cur = m_refs.column.begin( ),
                                     last = m_refs.column.end( );
                      cur != last;
                      ++cur )
                {
                    columnName.push_back( ( *cur )->GetName( ) );
                }
                return columnName;
            }

            //-----------------------------------------------------------------
            /// \brief Retrieve the number of columns
            ///
            /// \return
            ///     The number of columns in the table.
            //-----------------------------------------------------------------
            nColumn_type
            GetNColumn( ) const try
            {
                return RefColumn( ).size( );
            }
            catch ( ... )
            {
                return 0;
            }

            //-----------------------------------------------------------------
            /// \brief Retrieve the number of rows
            ///
            /// \return
            ///     The number of rows in the table.
            //-----------------------------------------------------------------
            nRow_type
            GetNRow( ) const
            {
                try
                {

                    if ( RefColumn( ).size( ) )
                    {
                        return RefColumn( )[ 0 ]->GetNData( );
                    }
                }
                catch ( ... )
                {
                }
                return 0;
            }

            //-----------------------------------------------------------------
            /// \brief Retrieve reference to columns
            ///
            /// \return
            ///     A constant reference to the container of columns.
            //-----------------------------------------------------------------
            const column_type& RefColumn( ) const;

            //-----------------------------------------------------------------
            /// \brief Retrieve reference to columns
            ///
            /// \return
            ///     A reference to the container of columns.
            //-----------------------------------------------------------------
            column_type& RefColumn( );

            bool operator==( const FrTablePST& RHS );

        protected:
            struct refs_type
            {

                //-----------------------------------------------------------------
                /// Calculate the number of bytes that will be written to the
                /// stream for this strucutre.
                //-----------------------------------------------------------------
                inline FrameCPP::cmn_streamsize_type
                Bytes( const Common::StreamBase& Stream ) const
                {
                    cmn_streamsize_type retval = sizeof( nColumn_type ) +
                        sizeof( nRow_type ) + Stream.PtrStructBytes( ) // column
                        ;

                    for ( const_iterator cur = column.begin( ),
                                         last = column.end( );
                          cur != last;
                          ++cur )
                    {
                        retval += STRING( ( *cur )->GetName( ) ).Bytes( );
                    }
                    return retval;
                }

                //---------------------------------------------------------------
                /// Supplies the FrSE description for each element of this
                /// object that will be written to the stream.
                //---------------------------------------------------------------
                template < typename SE >
                inline static void
                Describe( Common::Description& Desc )
                {
                    Desc( SE(
                        "nColumn", "INT_2U", "Number of columns in table" ) );
                    Desc( SE( "nRow", "INT_4U", "Number of rows in table" ) );
                    Desc( SE( "columnName",
                              "STRING[nColumn]",
                              "Names of the columns" ) );
                    Desc( SE( "column",
                              ptr_struct_type::Desc( FrVect::StructName( ) ),
                              " First column of table" ) );
                }

                inline bool
                operator==( const refs_type& RHS ) const
                {
                    return ( column == RHS.column );
                }

                inline void
                operator( )( Common::IStream& Stream )
                {
                    typedef Common::IStream::
                        Resizer< column_name_container_type, nColumn_type >
                                               resizer;
                    nColumn_type               nColumn;
                    nRow_type                  nRow;
                    column_name_container_type columnName;

                    Stream >> nColumn >> nRow >>
                        resizer( columnName, nColumn ) >> columnName >> column;
                }

                inline void
                operator( )( Common::OStream& Stream ) const
                {
                    nColumn_type nColumn = 0;
                    nRow_type    nRow = 0;

                    nColumn = column.size( );
                    if ( nColumn > 0 )
                    {
                        nRow = column[ 0 ]->GetNData( );
                    }

                    column_name_container_type columnName;
                    for ( const_iterator cur = column.begin( ),
                                         last = column.end( );
                          cur != last;
                          ++cur )
                    {
                        columnName.push_back( ( *cur )->GetName( ) );
                    }

                    Stream << nColumn << nRow << columnName << column;
                }

                static const INT_2U MAX_REF = 1;

                column_type column;
            };

            refs_type m_refs;
        };

        template < typename TPTR_STRUCT, typename TColumn >
        inline const typename FrTablePST< TPTR_STRUCT, TColumn >::column_type&
        FrTablePST< TPTR_STRUCT, TColumn >::RefColumn( ) const
        {
            return m_refs.column;
        }

        template < typename TPTR_STRUCT, typename TColumn >
        inline typename FrTablePST< TPTR_STRUCT, TColumn >::column_type&
        FrTablePST< TPTR_STRUCT, TColumn >::RefColumn( )
        {
            return m_refs.column;
        }

        //===================================================================
        //
        //===================================================================
        typedef FrTablePST<
            PTR_STRUCT,
            Common::SearchContainer< FrVect, &FrVect::GetName > >
            FrTablePS;

        //===================================================================
        /// \brief Implementation of FrTable according to the frame
        /// specification.
        //===================================================================
        class FrTable : public Common::FrameSpec::Object,
                        public FrTableNPS,
                        public FrTablePS
        {
        public:
            /// \brief Default constructor
            FrTable( );
            FrTable( const FrTable& table );
            FrTable( const std::string& name, INT_4U nrows );

            FrTable( const std::string&         Name,
                     const std::string&         Comment,
                     nRow_type                  NRows,
                     column_name_container_type ColumnNames );

            FrTable( const FrTableNPS& Source );

            virtual ~FrTable( );

            //-----------------------------------------------------------------
            /// \brief Stream size of object
            ///
            /// \param[in] Stream
            ///     The input or output stream used in conjunction with
            ///     this object.
            ///
            /// \return
            ///     The number of bytes needed to write or read this
            ///     class of object to or from a stream.
            //-----------------------------------------------------------------
            virtual cmn_streamsize_type
            Bytes( const Common::StreamBase& Stream ) const;

            virtual FrTable* Create( istream_type& Stream ) const;

            virtual const char* ObjectStructName( ) const;

            virtual void Write( ostream_type& Stream ) const;

            const std::string& GetNameSlow( ) const;

            /// \brief Merge with another FrAdcData
            FrTable& Merge( const FrTable& RHS );

            static promote_ret_type Promote( INT_2U           Source,
                                             promote_arg_type Obj,
                                             istream_type*    Stream );

            /// \brief Concatination operator
            FrTable& operator+=( const FrTable& RHS );

            static const Common::FrameSpec::Info::frame_object_types CLASS_ID =
                Common::FrameSpec::Info::FSI_FR_TABLE;

            //-----------------------------------------------------------------
            /// \brief Full description for the FrTable structure
            ///
            /// \return
            ///     A pointer to a static Description object containing
            ///     the full description of an FrTable structure for
            ///     the current frame specification.
            //-----------------------------------------------------------------
            static const Common::Description* StructDescription( );

            //-----------------------------------------------------------------
            /// \brief Name of the frame specification structure
            ///
            /// \return
            ///     A pointer to a static address containing the name
            ///     to be associated with this structure as specified
            ///     by the frame specification.
            //-----------------------------------------------------------------
            static const char* StructName( );

            //-----------------------------------------------------------------
            /// \brief comparison operator
            ///
            /// \param[in] RHS
            ///     The right hand side argument of the comparison operator
            ///
            /// \return
            ///     True if the two FrTable objects being compared are
            ///     equivelant, false otherwise.
            //-----------------------------------------------------------------
            bool operator==( const FrTable& RHS ) const;

            //-----------------------------------------------------------------
            /// \brief comparison operator
            //-----------------------------------------------------------------
            virtual bool
            operator==( const Common::FrameSpec::Object& Obj ) const;

        protected:
            //-----------------------------------------------------------------
            /// \brief Down grade an object
            //-----------------------------------------------------------------
            virtual demote_ret_type demote( INT_2U          Target,
                                            demote_arg_type Obj,
                                            istream_type*   Stream ) const;

            //-----------------------------------------------------------------
            /// \brief Up grade an object
            //-----------------------------------------------------------------
            virtual promote_ret_type promote( INT_2U           Source,
                                              promote_arg_type Obj,
                                              istream_type*    Stream ) const;

        private:
            using Common::FrameSpec::Object::Create;

            FrTable( istream_type& Stream );
        };

        inline const char*
        FrTable::StructName( )
        {
            static const char* name = "FrTable";
            return name;
        }

        inline bool
        FrTable::operator==( const FrTable& RHS ) const
        {
            return ( ( m_data == RHS.m_data ) && ( m_refs == RHS.m_refs ) );
        }
    } // namespace Version_4
} // namespace FrameCPP
#endif /* FrameCPP_VERSION_4_FrTable_HH */
