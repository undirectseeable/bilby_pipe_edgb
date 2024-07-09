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

#ifndef FrameCPP_VERSION_3_FrProcData_HH
#define FrameCPP_VERSION_3_FrProcData_HH

#if !defined( SWIGIMPORTED )
#include <memory>
#include <vector>
#endif /* ! defined(SWIGIMPORTED) */

#include "framecpp/Common/Container.hh"

#include "framecpp/Version3/FrameSpec.hh"
#include "framecpp/Version3/Dimension.hh"
#include "framecpp/Version3/FrVect.hh"
#include "framecpp/Version3/GPSTime.hh"
#include "framecpp/Version3/STRING.hh"

namespace FrameCPP
{
    namespace Version_3
    {

        //===================================================================
        // Data elements for an FrProcData
        //===================================================================
        class FrProcDataData
        {
        public:
            FrProcDataData( );
            FrProcDataData( const std::string& Name,
                            const std::string& Comment,
                            const REAL_8       SampleRate,
                            const GPSTime&     TimeOffset,
                            const REAL_8       FShift );
            FrProcDataData( Common::IStream& Stream );

            const std::string& GetName( ) const;
            const std::string& GetComment( ) const;
            REAL_8             GetSampleRate( ) const;
            const GPSTime&     GetTimeOffset( ) const;
            REAL_8             GetFShift( ) const;

            void SetFShift( REAL_8 FShift );
            void SetTimeOffset( const GPSTime& time );

            // Mutators
            void AppendComment( const std::string& comment );

        protected:
            struct fr_proc_data_data_type
            {
                STRING  name;
                STRING  comment;
                REAL_8  sampleRate;
                GPSTime timeOffset;
                REAL_8  fShift;

                fr_proc_data_data_type( );
                fr_proc_data_data_type( const fr_proc_data_data_type& Source );

                //---------------------------------------------------------------
                /// \brief Return the number of bytes for this object
                ///
                /// \param[in] Stream
                ///     The stream on which the object will be written or read.
                ///
                /// \return
                ///     The number of bytes required by this object for
                ///     the specified stream.
                //---------------------------------------------------------------
                FrameCPP::cmn_streamsize_type
                Bytes( const Common::StreamBase& Stream ) const;

                void Write( Common::OStream& Stream ) const;

                //---------------------------------------------------------------
                /// \brief assigment operator
                //---------------------------------------------------------------
                const fr_proc_data_data_type&
                operator=( const fr_proc_data_data_type& Source );

                //---------------------------------------------------------------
                /// \brief Equality operator
                ///
                /// \param[in] RHS
                ///     Argument to the right-hand side of the operator
                ///
                //---------------------------------------------------------------
                bool operator==( const fr_proc_data_data_type& RHS ) const;

                //---------------------------------------------------------------
                /// \brief Non equality operator
                /// \param[in] RHS
                ///     Argument to the right-hand side of the operator
                ///
                //---------------------------------------------------------------
                bool operator!=( const fr_proc_data_data_type& RHS ) const;
            };

            mutable fr_proc_data_data_type m_data;
        };

        inline void
        FrProcDataData::AppendComment( const std::string& comment )
        {
            FrameCPP::Common::AppendComment( m_data.comment, comment );
        }

        inline const std::string&
        FrProcDataData::GetName( ) const
        {
            return m_data.name;
        }

        inline const std::string&
        FrProcDataData::GetComment( ) const
        {
            return m_data.comment;
        }

        inline REAL_8
        FrProcDataData::GetSampleRate( ) const
        {
            return m_data.sampleRate;
        }

        inline const GPSTime&
        FrProcDataData::GetTimeOffset( ) const
        {
            return m_data.timeOffset;
        }

        inline REAL_8
        FrProcDataData::GetFShift( ) const
        {
            return m_data.fShift;
        }

        inline void
        FrProcDataData::SetFShift( REAL_8 FShift )
        {
            m_data.fShift = FShift;
        }

        inline void
        FrProcDataData::SetTimeOffset( const GPSTime& time )
        {
            m_data.timeOffset = time;
        }

        inline bool
        FrProcDataData::fr_proc_data_data_type::
        operator!=( const fr_proc_data_data_type& RHS ) const
        {
            return !( this->operator==( RHS ) );
        }

        //===================================================================
        // FrProcData
        //===================================================================
        class FrProcData : public Common::FrameSpec::Object,
                           public FrProcDataData
        {
        public:
            typedef Common::Container< FrVect > data_type;
            typedef data_type::const_iterator   const_iterator;
            typedef data_type::iterator         iterator;

            typedef Common::Container< FrVect > aux_type;
            typedef aux_type::const_iterator    const_aux_iterator;
            typedef aux_type::iterator          aux_iterator;

            /// \brief Default constructor
            FrProcData( );

            FrProcData( const FrProcData& Source );

            FrProcData( const std::string& Name,
                        const std::string& Comment,
                        const REAL_8       SampleRate,
                        const GPSTime&     TimeOffset,
                        const REAL_8       FShift );

            ~FrProcData( );

            static promote_ret_type Promote( INT_2U           Source,
                                             promote_arg_type Obj,
                                             istream_type*    Stream );

            static const char* StructName( );

            static const Common::Description* StructDescription( );

            // Comparison operator
            bool operator==( const FrProcData& RHS ) const;
            bool operator!=( const FrProcData& RHS ) const;

            /// \brief comparison operator
            virtual bool
            operator==( const Common::FrameSpec::Object& Obj ) const;

            /// \brief Number of bytes needed to write this structure
            cmn_streamsize_type Bytes( const Common::StreamBase& Stream ) const;

            // Accessors
            const std::string& GetNameSlow( ) const;

            const aux_type&  RefAux( ) const;
            aux_type&        RefAux( );
            const data_type& RefData( ) const;
            data_type&       RefData( );

            /// \brief Merge with another FrProcData
            FrProcData& Merge( const FrProcData& RHS );

#if WORKING
            std::unique_ptr< FrProcData > SubFrProcData( REAL_8 Offset,
                                                         REAL_8 Dt ) const;
#endif /* WORKING */

            virtual FrProcData* Create( istream_type& Stream ) const;

            virtual const char* ObjectStructName( ) const;

            /// \brief Write the structure to the stream
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

        private:
            using Common::FrameSpec::Object::Create;

            struct fr_proc_data_ref_type
            {
                data_type data;
                aux_type  aux;

                void copy_core( const fr_proc_data_ref_type& Source );

                FrameCPP::cmn_streamsize_type
                Bytes( const Common::StreamBase& Stream ) const;

                void Write( ostream_type& Stream ) const;

                bool operator==( const fr_proc_data_ref_type& RHS ) const;
                Common::IStream& operator( )( Common::IStream& Stream );
            };
            fr_proc_data_ref_type m_refs;
            mutable bool          m_synced_with_vector;

            FrProcData( istream_type& Stream );

            void                          copy_core( const FrProcData& Source );
            std::unique_ptr< FrProcData > sub_time_series( REAL_8 Offset,
                                                           REAL_8 Dt ) const;
        };

        const REAL_8 FR_PROC_DATA_DEFAULT_FSHIFT = 0.0;

        inline void
        FrProcData::fr_proc_data_ref_type::copy_core(
            const fr_proc_data_ref_type& Source )
        {
            aux = Source.aux;
        }

        inline bool
        FrProcData::fr_proc_data_ref_type::
        operator==( const fr_proc_data_ref_type& RHS ) const
        {
            return ( ( this == &RHS ) ||
                     ( ( data == RHS.data ) && ( aux == RHS.aux ) ) );
        }

        inline FrProcData::promote_ret_type
        FrProcData::Promote( INT_2U           Source,
                             promote_arg_type Obj,
                             istream_type*    Stream )
        {
            return Common::PromoteObject( DATA_FORMAT_VERSION, Source, Obj );
        }

        inline const char*
        FrProcData::StructName( )
        {
            static const char* name = "FrProcData";
            return name;
        }

        inline const FrProcData::aux_type&
        FrProcData::RefAux( ) const
        {
            return m_refs.aux;
        }

        inline FrProcData::aux_type&
        FrProcData::RefAux( )
        {
            return m_refs.aux;
        }

        inline const FrProcData::data_type&
        FrProcData::RefData( ) const
        {
            return m_refs.data;
        }

        inline FrProcData::data_type&
        FrProcData::RefData( )
        {
            return m_refs.data;
        }

        inline bool
        FrProcData::operator==( const FrProcData& RHS ) const
        {
            return ( ( this == &RHS ) ||
                     ( ( m_data == RHS.m_data ) && ( m_refs == RHS.m_refs ) ) );
        }

        inline bool
        FrProcData::operator!=( const FrProcData& RHS ) const
        {
            return !( *this == RHS );
        }
    } // namespace Version_3
} // namespace FrameCPP
#endif /* FrameCPP_VERSION_3_FrProcData_HH */
