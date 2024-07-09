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

#ifndef FrameCPP_VERSION_6_FrTable_HH
#define FrameCPP_VERSION_6_FrTable_HH

#if !defined( SWIGIMPORTED )
#include <vector>
#endif /* ! defined(SWIGIMPORTED) */

#include "framecpp/Version6/FrameSpec.hh"

#include "framecpp/Common/SearchContainer.hh"

#include "framecpp/Version4/FrTable.hh"

#include "framecpp/Version6/PTR_STRUCT.hh"
#include "framecpp/Version6/FrVect.hh"
#include "framecpp/Version6/GPSTime.hh"
#include "framecpp/Version6/STRING.hh"

namespace FrameCPP
{
    namespace Version_6
    {
        //===================================================================
        //
        //===================================================================
        using Previous::FrTableNPS;

        //===================================================================
        //
        //===================================================================
        typedef Version_4::FrTablePST<
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
            //: Default constructor
            FrTable( );
            FrTable( const FrTable& table );
            FrTable( const std::string& name, INT_4U nrows );

            FrTable( const std::string&         Name,
                     const std::string&         Comment,
                     nRow_type                  NRows,
                     column_name_container_type ColumnNames );

            FrTable( const FrTableNPS& Source );

            FrTable( Previous::FrTable& Source, istream_type* Stream );

            virtual ~FrTable( );

            //-----------------------------------------------------------------
            /// \brief Stream size of object
            ///
            /// \param[in] Stream
            ///     The stream from which to the object is being read or
            ///     written.
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

            //: Merge with another FrAdcData
            FrTable& Merge( const FrTable& RHS );

            static promote_ret_type Promote( INT_2U           Source,
                                             promote_arg_type Obj,
                                             istream_type*    Stream );

            //: Concatination operator
            FrTable& operator+=( const FrTable& RHS );

            //-----------------------------------------------------------------
            /// \brief Dictionary class id for this structure.
            //-----------------------------------------------------------------
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
            ///     Right hand side of equality expression.
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

        inline FrTable::promote_ret_type
        FrTable::Promote( INT_2U           Source,
                          promote_arg_type Obj,
                          istream_type*    Stream )
        {
            return Object::PromoteObject< Previous::FrTable, FrTable >(
                DATA_FORMAT_VERSION, Source, Obj, Stream );
        }

    } // namespace Version_6
} // namespace FrameCPP
#endif /* FrameCPP_VERSION_6_FrTable_HH */
