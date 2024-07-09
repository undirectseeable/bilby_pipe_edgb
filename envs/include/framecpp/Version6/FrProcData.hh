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

#ifndef FrameCPP_VERSION_6_FrProcData_HH
#define FrameCPP_VERSION_6_FrProcData_HH

#if __cplusplus
#if !defined( SWIGIMPORTED )
#include <vector>
#endif /* ! defined(SWIGIMPORTED) */

#if !defined( SWIGIMPORTED )

#include "framecpp/Common/Array.hh"
#include "framecpp/Common/Container.hh"
#include "framecpp/Common/TOCInfo.hh"

#include "framecpp/Version4/FrProcData.hh"
#endif /* ! defined(SWIGIMPORTED) */

#include "framecpp/Version6/FrameSpec.hh"
#endif /* __cplusplus */
#if !defined( SWIGIMPORTED )
#include "framecpp/Version6/FrProcDataNPS.hh"
#include "framecpp/Version6/FrProcDataPST.hh"

#if defined( __cplusplus )
#include "framecpp/Version6/FrHistory.hh"
#include "framecpp/Version6/FrTable.hh"
#include "framecpp/Version6/FrVect.hh"
#endif /* defined(__cplusplus) */
#endif /* ! defined(SWIGIMPORTED) */
#if defined( __cplusplus )

namespace FrameCPP
{
    namespace Version_6
    {
        //===================================================================
        //===================================================================

        typedef FrProcDataPST< FrVect, FrVect, FrTable, FrHistory >
            FrProcDataPS;

        //===================================================================
        //===================================================================
        class FrProcData
#if !defined( SWIGIMPORTED )
            : public Common::FrameSpec::Object,
              public Common::TOCInfo,
              public FrProcDataNPS,
              public FrProcDataPS
#endif /* !defined( SWIGIMPORTED ) */
        {
        public:
            typedef std::unique_ptr< FrProcData > subset_ret_type;

            //-----------------------------------------------------------------
            /// \brief Default constructor
            ///
            /// \return
            ///    A new instance of this object.
            //-----------------------------------------------------------------
            FrProcData( );

            //-----------------------------------------------------------------
            /// \brief Copy Constructor
            ///
            /// \param[in] Source
            ///     The object from which to copy the information.
            ///
            /// \return
            ///    A new instance of this object.
            //-----------------------------------------------------------------
            FrProcData( const FrProcData& Source );

            //-----------------------------------------------------------------
            /// \brief Constructor
            ///
            /// \param[in] Name
            ///     Data or channel name
            /// \param[in] Comment
            ///     Comment
            /// \param[in] Type
            ///     Type of data object.
            /// \param[in] SubType
            ///     Subtype of f-Series.
            /// \param[in] TimeOffset
            ///     Ofset of 1st sample relative to the frame start time.
            /// \param[in] TRange
            ///     Duration of sampled data.
            /// \param[in] FShift
            ///     The frequency in the original data that corresponds to
            ///     zero Hz in the heterodyned series.
            /// \param[in] Phase
            ///     Phase of heterodyning signal at start of dataset.
            /// \param[in] FRange
            ///     Frequency range.
            /// \param[in] BW
            ///     Resolution bandwidth.
            ///
            /// \return
            ///    A new instance of this object.
            //-----------------------------------------------------------------
            FrProcData( const name_type&    Name,
                        const comment_type& Comment,
                        type_type           Type,
                        subType_type        SubType,
                        timeOffset_type     TimeOffset,
                        tRange_type         TRange,
                        fShift_type         FShift,
                        phase_type          Phase,
                        fRange_type         FRange,
                        BW_type             BW );

#if 0
      FrProcData( const std::string& Name,
		  REAL_8 SampleRate,
		  const GPSTime& TimeOffset,
		  fShift_type FShift,
		  phase_type Phase );
#endif /* 0 */

            //-----------------------------------------------------------------
            /// \brief Promotion Constructor
            ///
            /// \param[in] Source
            ///     An FrProcData structure from a previous frame specification.
            /// \param[in] Stream
            ///     The stream from which the earliest version of the
            ///     FrProcData structure was read.
            ///
            /// \return
            ///     A new instance of an FrProcData object
            //-----------------------------------------------------------------
            FrProcData( Previous::FrProcData& Source, istream_type* Stream );

            //-----------------------------------------------------------------
            /// \brief Destructor
            //-----------------------------------------------------------------
            ~FrProcData( );

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
            /// \brief equality operator
            ///
            /// \param[in] RHS
            ///     The FrProcData object to be compared.
            ///
            /// \return
            ///     The value true is returned if this object is equivelent
            ///     to the RHS instance; false otherwise.
            //-----------------------------------------------------------------
            bool operator==( const FrProcData& RHS ) const;

            //-----------------------------------------------------------------
            /// \brief inequality operator
            ///
            /// \param[in] RHS
            ///     The FrProcData object to be compared.
            ///
            /// \return
            ///     The value true is returned if this object is not equivelent
            ///     to the RHS instance; false otherwise.
            //-----------------------------------------------------------------
            bool operator!=( const FrProcData& RHS ) const;

            //-----------------------------------------------------------------
            /// \brief equality operator for abstract data type
            ///
            /// \param[in] Obj
            ///     The object to be compared.
            ///
            /// \return
            ///     The value true is returned if this object is equivelent
            ///     to the RHS instance; false otherwise.
            //-----------------------------------------------------------------
            virtual bool
            operator==( const Common::FrameSpec::Object& Obj ) const;

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
            cmn_streamsize_type Bytes( const Common::StreamBase& Stream ) const;

            //-----------------------------------------------------------------
            /// \brief Retrieve the frequency range.
            ///
            /// \return
            ///     The frequency range.
            //-----------------------------------------------------------------
            fRange_type GetFRange( ) const;

            //-----------------------------------------------------------------
            /// \brief Retrieve the time range.
            ///
            /// \return
            ///     The time range.
            //-----------------------------------------------------------------
            tRange_type GetTRange( ) const;

            //-----------------------------------------------------------------
            /// \brief Return the name associate with the FrProcData structure.
            ///
            /// \return
            ///     The name associated with the FrAdcData structure
            //-----------------------------------------------------------------
            const std::string& GetNameSlow( ) const;

            //-----------------------------------------------------------------
            /// \brief Merge with another FrProcData
            ///
            /// \param[in] RHS
            ///     The source of the information to append to this FrProcData
            ///     structure.
            ///
            /// \return
            ///     A reference to this object
            //-----------------------------------------------------------------
            FrProcData& Merge( const FrProcData& RHS );

            //-----------------------------------------------------------------
            /// \brief Request a subset of the data.
            ///
            /// \param[in] Offset
            ///     The number of seconds from the start of the FrProcData
            ///     object from which to start extracting data.
            /// \param[in] Dt
            ///     The number of seconds of data in the resulting FrProcData
            ///     strucutre.
            ///
            /// \return
            ///     A FrProcData structure which contains Dt seconds of data
            ///     starting at Offset of this FrProcData structure.
            //-----------------------------------------------------------------
            subset_ret_type SubFrProcData( REAL_8 Offset, REAL_8 Dt ) const;

            //-----------------------------------------------------------------
            /// \brief Virtual constructor
            ///
            /// \param[in] Stream
            ///     The stream from which the earliest version of the
            ///     FrProcData structure was read.
            ///
            /// \return
            ///    A new instance of this object.
            //-----------------------------------------------------------------
            virtual FrProcData* Create( istream_type& Stream ) const;

            //-----------------------------------------------------------------
            /// \brief The name structure name of this object.
            ///
            /// \return
            ///     The name of the structure as specified by the frame
            ///     specification.
            //-----------------------------------------------------------------
            virtual const char* ObjectStructName( ) const;

            //-----------------------------------------------------------------
            /// \brief Virtual constructor
            ///
            /// \param[in] Stream
            ///     The input stream from where the object is being read.
            //-----------------------------------------------------------------
            virtual void Write( ostream_type& Stream ) const;

#if WORKING_VIRTUAL_TOCQUERY
            //-----------------------------------------------------------------
            /// \brief Answer requests for information as needed by TOC
            ///
            /// \param[in] InfoClass
            ///     Class of information being requested.
            /// \param[in] vl
            ///     Variable argument list of requested data.
            //-----------------------------------------------------------------
            virtual void TOCQuery( int InfoClass, ... ) const;
#endif /*  WORKING_VIRTUAL_TOCQUERY */

            //-----------------------------------------------------------------
            /// \brief Convert numeric types to string representation
            ///
            /// \param[in] Type
            ///     Numeric type.
            ///
            /// \return
            ///     The string representation of Type.
            //-----------------------------------------------------------------
            static const std::string& IDTypeToString( type_type Type );

            //-----------------------------------------------------------------
            /// \brief Convert numeric sub-types to string representation
            ///
            /// \param[in] Type
            ///     Numeric type.
            /// \param[in] SubType
            ///     Numeric sub-type.
            ///
            /// \return
            ///     The string representation of SubType of Type.
            //-----------------------------------------------------------------
            static const std::string& IDSubTypeToString( type_type    Type,
                                                         subType_type SubType );

        protected:
            //-----------------------------------------------------------------
            /// \brief Down grade an object
            ///
            /// \param[in] Target
            ///     The version of the frame specification to demote too.
            /// \param[in] Obj
            ///     The version of the object to demote.
            /// \param[in] Stream
            ///     The input stream from which the original object was read.
            ///
            /// \return
            ///     An object of the previous generation.
            //-----------------------------------------------------------------
            virtual demote_ret_type demote( INT_2U          Target,
                                            demote_arg_type Obj,
                                            istream_type*   Stream ) const;

            //-----------------------------------------------------------------
            /// \brief Upgrade an object
            ///
            /// \param[in] Target
            ///     The version of the frame specification to promote too.
            /// \param[in] Obj
            ///     The object to be promoted.
            /// \param[in] Stream
            ///     The input stream from which the original object was read.
            ///
            /// \return
            ///     An object of this class.
            //-----------------------------------------------------------------
            virtual promote_ret_type promote( INT_2U           Target,
                                              promote_arg_type Obj,
                                              istream_type*    Stream ) const;

#if !WORKING_VIRTUAL_TOCQUERY
            //-----------------------------------------------------------------
            /// \brief Answer requests for information as needed by TOC
            ///
            /// \param[in] InfoClass
            ///     Class of information being requested.
            /// \param[in] vl
            ///     Variable argument list of requested data.
            //-----------------------------------------------------------------
            virtual void vTOCQuery( int InfoClass, va_list vl ) const;
#endif /* ! WORKING_VIRTUAL_TOCQUERY */

        private:
            using Common::FrameSpec::Object::Create;

            //-----------------------------------------------------------------
            /// True if FrProcData has been syncronized with its associated
            /// FrVect data structure.
            //-----------------------------------------------------------------
            bool m_synced_with_vector;

            //-----------------------------------------------------------------
            /// \brief Stream Constructor
            ///
            /// \param[in] Stream
            ///     The stream from which the object is being read.
            ///
            /// \return
            ///    A new instance of this object.
            //-----------------------------------------------------------------
            FrProcData( istream_type& Stream );

            //-----------------------------------------------------------------
            /// \brief Copy core data.
            ///
            /// \param[in] Source
            ///     The source from which to copy the data
            //-----------------------------------------------------------------
            void copy_core( const FrProcData& Source );

            //-----------------------------------------------------------------
            /// \brief Retrieve a time series subset.
            ///
            /// \param[in] Offset
            ///     The number of seconds from the start of the FrAdcData
            ///     object from which to start extracting data.
            /// \param[in] Dt
            ///     The number of seconds of data in the resulting FrAdcData
            ///     strucutre.
            ///
            /// \return
            ///     A FrProcData structure which contains Dt seconds of data
            ///     starting at Offset of this FrProcData structure.
            //-----------------------------------------------------------------
            subset_ret_type sub_time_series( REAL_8 Offset, REAL_8 Dt ) const;

            void sync_with_vector( );
        };

        inline FrProcData::promote_ret_type
        FrProcData::Promote( INT_2U           Source,
                             promote_arg_type Obj,
                             istream_type*    Stream )
        {
            return Object::PromoteObject< Previous::FrProcData, FrProcData >(
                DATA_FORMAT_VERSION, Source, Obj, Stream );
        }

        inline const char*
        FrProcData::StructName( )
        {
            static const char* name = "FrProcData";
            return name;
        }

        inline REAL_8
        FrProcData::GetFRange( ) const
        {
            if ( !m_synced_with_vector )
            {
                const_cast< FrProcData* >( this )->sync_with_vector( );
            }
            return FrProcDataNPS::GetFRange( );
        }

        inline REAL_8
        FrProcData::GetTRange( ) const
        {
            if ( !m_synced_with_vector )
            {
                const_cast< FrProcData* >( this )->sync_with_vector( );
            }
            return FrProcDataNPS::GetTRange( );
        }

        inline bool
        FrProcData::operator==( const FrProcData& RHS ) const
        {
            return ( ( this == &RHS ) ||
                     ( ( FrProcDataNPS::operator==( RHS ) ) &&
                       ( FrProcDataPS::operator==( RHS ) ) ) );
        }

        inline bool
        FrProcData::operator!=( const FrProcData& RHS ) const
        {
            return !( *this == RHS );
        }
    } // namespace Version_6
} // namespace FrameCPP
#endif /* __cplusplus */
#endif /* FrameCPP_VERSION_6_FrProcData_HH */
