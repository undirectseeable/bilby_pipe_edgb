//
// LDASTools frameCPP - A library implementing the LIGO/Virgo frame
// specification
//
// Copyright (C) 2020 California Institute of Technology
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

#ifndef FrameCPP_VERSION_8__IMPL__FrTOCDataData_HH
#define FrameCPP_VERSION_8__IMPL__FrTOCDataData_HH

#undef FR_TOC_NFRAME_TYPE
#define FR_TOC_NFRAME_TYPE INT_4U

#undef FR_TOC_ULEAPS_TYPE
#define FR_TOC_ULEAPS_TYPE INT_2S

namespace FrameCPP
{
    namespace Version_8
    {
        namespace FrTOCImpl
        {
            class FrTOCDataData
            {
            public:
                typedef INT_4U             data_quality_type;
                typedef REAL_8             dt_type;
                typedef INT_4U             frame_type;
                typedef INT_4U             gtimen_type;
                typedef INT_4U             gtimes_type;
                typedef std::string        namedetector_type;
                typedef INT_4U             ndetector_type;
                typedef INT_8U             nfirstadc_type;
                typedef INT_8U             nfirstmsg_type;
                typedef INT_8U             nfirstser_type;
                typedef INT_8U             nfirsttable_type;
                typedef FR_TOC_NFRAME_TYPE nFrame_type;
                typedef INT_4U             nsh_type;
                typedef INT_8U             positiondetector_type;
                typedef INT_8U             positionh_type;
                typedef INT_4S             runs_type;
                typedef INT_2U             shid_type;
                typedef std::string        shname_type;
                typedef FR_TOC_ULEAPS_TYPE uleaps_type;

                //-----------------------------------------------------------------
                /// \brief Array of integer QA words from each FrameH
                //-----------------------------------------------------------------
                typedef std::vector< data_quality_type >
                    data_quality_container_type;
                //-----------------------------------------------------------------
                /// \brief Array of frame durations in seconds.
                //-----------------------------------------------------------------
                typedef std::vector< dt_type > dt_container_type;
                //-----------------------------------------------------------------
                /// \brief Array of frame numbers.
                //-----------------------------------------------------------------
                typedef std::vector< frame_type > frame_container_type;
                //-----------------------------------------------------------------
                /// \brief Array of integer GPS residual nanoseconds for the
                /// frame.
                //-----------------------------------------------------------------
                typedef std::vector< gtimen_type > gtimen_container_type;
                //-----------------------------------------------------------------
                /// \brief Array of integer GPS frame times.
                //-----------------------------------------------------------------
                typedef std::vector< gtimes_type > gtimes_container_type;
                //-----------------------------------------------------------------
                /// \brief Array of FrDetector names.
                //-----------------------------------------------------------------
                typedef std::vector< namedetector_type >
                    namedetector_container_type;
                //-----------------------------------------------------------------
                /// \brief  Array of first FrADCData positions.
                //-----------------------------------------------------------------
                typedef std::vector< nfirstadc_type > nfirstadc_container_type;
                //-----------------------------------------------------------------
                /// \brief Array of first FrMsg positions.
                //-----------------------------------------------------------------
                typedef std::vector< nfirstmsg_type > nfirstmsg_container_type;
                //-----------------------------------------------------------------
                /// \brief Array of first FrSerData positions.
                //-----------------------------------------------------------------
                typedef std::vector< nfirstser_type > nfirstser_container_type;
                //-----------------------------------------------------------------
                /// \brief Array of first FrTable positions.
                //-----------------------------------------------------------------
                typedef std::vector< nfirsttable_type >
                    nfirsttable_container_type;
                //-----------------------------------------------------------------
                /// \brief Array of FrDetector positions.
                //-----------------------------------------------------------------
                typedef std::vector< positiondetector_type >
                    positiondetector_container_type;
                //-----------------------------------------------------------------
                /// \brief Array of FrSH IDs.
                //-----------------------------------------------------------------
                typedef std::vector< positionh_type > positionh_container_type;
                //-----------------------------------------------------------------
                /// \brief Array of FrameH positions.
                //-----------------------------------------------------------------
                typedef std::vector< runs_type > runs_container_type;
                //-----------------------------------------------------------------
                /// \brief Array of FrSH IDs.
                //-----------------------------------------------------------------
                typedef std::vector< shid_type > shid_container_type;
                //-----------------------------------------------------------------
                /// \brief Array of FrSH names.
                //-----------------------------------------------------------------
                typedef std::vector< shname_type > shname_container_type;

                //-----------------------------------------------------------------
                /// \brief Retreive array of integer QA words from each FrameH.
                //-----------------------------------------------------------------
                inline const data_quality_container_type&
                GetDataQuality( ) const
                {
                    return m_dataQuality;
                }

                //-----------------------------------------------------------------
                /// \brief Retrieve array of frame durations in seconds.
                //-----------------------------------------------------------------
                inline const dt_container_type&
                GetDt( ) const
                {
                    return m_dt;
                }

                //-----------------------------------------------------------------
                /// \brief Retrieve array of frame numbers.
                //-----------------------------------------------------------------
                inline const frame_container_type&
                GetFrame( ) const
                {
                    return m_frame;
                }

                //-----------------------------------------------------------------
                /// \brief Retrieve array of integer GPS residual nanoseconds
                /// for the frame.
                //-----------------------------------------------------------------
                inline const gtimes_container_type&
                GetGTimeN( ) const
                {
                    return m_GTimeN;
                }

                //-----------------------------------------------------------------
                /// \brief Retrieve array of integer GPS frame times.
                //-----------------------------------------------------------------
                inline const gtimen_container_type&
                GetGTimeS( ) const
                {
                    return m_GTimeS;
                }

                //-----------------------------------------------------------------
                /// \brief Retrieve array of first FrADCData positions.
                //-----------------------------------------------------------------
                inline const nfirstadc_container_type&
                GetNFirstADC( ) const
                {
                    return m_nFirstADC;
                }

                //-----------------------------------------------------------------
                /// \brief Retrieve array of first FrMsg positions.
                //-----------------------------------------------------------------
                inline const nfirstmsg_container_type&
                GetNFirstMsg( ) const
                {
                    return m_nFirstMsg;
                }

                //-----------------------------------------------------------------
                /// \brief Retrieve array of first FrSerData positions.
                //-----------------------------------------------------------------
                inline const nfirstser_container_type&
                GetNFirstSer( ) const
                {
                    return m_nFirstSer;
                }

                //-----------------------------------------------------------------
                /// \brief Retrieve array of first FrTable positions.
                //-----------------------------------------------------------------
                inline const nfirsttable_container_type&
                GetNFirstTable( ) const
                {
                    return m_nFirstTable;
                }

                //-----------------------------------------------------------------
                /// \brief
                //-----------------------------------------------------------------
                inline nFrame_type
                GetNFrame( ) const
                {
                    return m_dataQuality.size( );
                }

                //-----------------------------------------------------------------
                /// \brief Retrieve array of FrameH positions.
                //-----------------------------------------------------------------
                inline const positionh_container_type&
                GetPositionH( ) const
                {
                    return m_positionH;
                }

                //-----------------------------------------------------------------
                /// \brief
                //-----------------------------------------------------------------
                inline const runs_container_type&
                GetRuns( ) const
                {
                    return m_runs;
                }

                //-----------------------------------------------------------------
                /// \brief Retrieve array of FrSH IDs.
                //-----------------------------------------------------------------
                inline const shid_container_type&
                GetSHid( ) const
                {
                    return m_SHid;
                }

                //-----------------------------------------------------------------
                /// \brief Retrieve array of FrSH names.
                //-----------------------------------------------------------------
                inline const shname_container_type&
                GetSHname( ) const
                {
                    return m_SHname;
                }

                //-----------------------------------------------------------------
                /// \brief Retrieve the number of leap seconds.
                //-----------------------------------------------------------------
                inline uleaps_type
                GetULeapS( ) const
                {
                    return m_ULeapS;
                }

                //-----------------------------------------------------------------
                /// \brief Retrieve array of FrDetector names.
                //-----------------------------------------------------------------
                inline const namedetector_container_type&
                GetNameDetector( ) const
                {
                    return m_nameDetector;
                }

                //-----------------------------------------------------------------
                /// \brief Retrieve array of FrDetector positions.
                //-----------------------------------------------------------------
                inline const positiondetector_container_type&
                GetPositionDetector( ) const
                {
                    return m_positionDetector;
                }

                //-----------------------------------------------------------------
                /// \brief equality operator
                ///
                /// \param[in] RHS
                ///     The FrTOCData object to be compared.
                ///
                /// \return
                ///     The value true is returned if this object is equivelent
                ///     to the RHS instance; false otherwise.
                //-----------------------------------------------------------------
                inline bool
                operator==( const FrTOCDataData& RHS ) const
                {
#define CMP__( X ) ( X == RHS.X )

                    return ( ( &RHS == this ) ||
                             ( CMP__( m_ULeapS ) && CMP__( m_dataQuality ) &&
                               CMP__( m_GTimeS ) && CMP__( m_GTimeN ) &&
                               CMP__( m_dt ) && CMP__( m_runs ) &&
                               CMP__( m_frame ) && CMP__( m_positionH ) &&
                               CMP__( m_nFirstADC ) && CMP__( m_nFirstSer ) &&
                               CMP__( m_nFirstTable ) && CMP__( m_nFirstMsg ) &&
                               CMP__( m_SHid ) && CMP__( m_SHname ) &&
                               CMP__( m_nameDetector ) &&
                               CMP__( m_positionDetector ) ) );
#undef CMP__
                }

            protected:
                //-----------------------------------------------------------------
                /// \brief From the first FrameH in the file.
                //-----------------------------------------------------------------
                uleaps_type m_ULeapS = { 0 };
                //-----------------------------------------------------------------
                /// \brief Array of integer QA words from each FrameH (size of
                /// nFrame)
                //-----------------------------------------------------------------
                data_quality_container_type m_dataQuality;
                //-----------------------------------------------------------------
                /// \brief Array of integer GPS frame times (size of nFrame).
                //-----------------------------------------------------------------
                gtimes_container_type m_GTimeS;
                //-----------------------------------------------------------------
                /// \brief Array of integer GPS residual nanoseconds for the
                /// frame (size of nFrame).
                //-----------------------------------------------------------------
                gtimen_container_type m_GTimeN;
                //-----------------------------------------------------------------
                /// \brief Array of frame durations in seconds (size of nFrame).
                //-----------------------------------------------------------------
                dt_container_type m_dt;
                //-----------------------------------------------------------------
                /// \brief Array of run numbers.
                ///
                /// Array of run numbers.
                /// The size of this array is specified by nFrame.
                //-----------------------------------------------------------------
                runs_container_type m_runs;
                //-----------------------------------------------------------------
                /// \brief Array of frame numbers (size of nFrame).
                //-----------------------------------------------------------------
                frame_container_type m_frame;
                //-----------------------------------------------------------------
                /// \brief Array of FrDetector positions.
                ///
                /// Array of FrDetector positions from the beginning of
                /// file.
                /// The size of array is specified by nDetector.
                ///
                /// \note
                /// Only the first occurrence for each type of FrDetector
                /// is captured.
                //-----------------------------------------------------------------
                positiondetector_container_type m_positionDetector;
                //-----------------------------------------------------------------
                /// \brief
                ///
                /// Array of FrameH positions, in bytes,
                /// from beginning of file.
                /// The size of this array is specified by nFrame.
                //-----------------------------------------------------------------
                positionh_container_type m_positionH;
                //-----------------------------------------------------------------
                /// \brief Array of FrDetector names.
                ///
                /// The size of this array is specified by nDetector.
                /// They appear alphabetically.
                //-----------------------------------------------------------------
                namedetector_container_type m_nameDetector;
                //-----------------------------------------------------------------
                /// \brief Array of first FrADCData positions.
                ///
                /// Array of first FrADCData positions, in bytes,
                /// from beginning of file.
                /// The size of this array is specified by nFrame.
                //-----------------------------------------------------------------
                nfirstadc_container_type m_nFirstADC;
                //-----------------------------------------------------------------
                /// \brief Array of first FrSerData positions.
                ///
                /// Array of first FrSerData positions, in bytes,
                /// from beginning of file.
                /// The size of this array is specified by nFrame.
                //-----------------------------------------------------------------
                nfirstser_container_type m_nFirstSer;
                //-----------------------------------------------------------------
                /// \brief Array of first FrTable positions.
                ///
                /// Array of first FrTable positions, in bytes,
                /// from beginning of file
                /// The size of this array is specified by nFrame.
                ///
                /// \note
                /// The pointer is to the first table associated
                /// with FrRawData for each frame.
                //-----------------------------------------------------------------
                nfirsttable_container_type m_nFirstTable;
                //-----------------------------------------------------------------
                /// \brief Array of first FrMsg positions.
                ///
                /// Array of first FrMsg positions, in bytes,
                /// from beginning of file.
                /// The size of this array is specified by nFrame.
                //-----------------------------------------------------------------
                nfirstmsg_container_type m_nFirstMsg;
                //-----------------------------------------------------------------
                /// \brief Array of FrSH IDs.
                ///
                /// Array of FrSH IDs.
                /// The size of this array is specified by nSH.
                //-----------------------------------------------------------------
                shid_container_type m_SHid;
                //-----------------------------------------------------------------
                /// \brief
                ///
                /// Array of FrSH names.
                /// The size of array is specified by nSH.
                //-----------------------------------------------------------------
                shname_container_type m_SHname;
            };
        } // namespace FrTOCImpl
    } // namespace Version_8
} // namespace FrameCPP

#endif /* FrameCPP_VERSION_8__IMPL__FrTOCDataData_HH */
