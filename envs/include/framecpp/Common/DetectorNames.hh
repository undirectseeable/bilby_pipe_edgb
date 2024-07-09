/*
 * LDASTools frameCPP - A library implementing the LIGO/Virgo frame
 * specification
 *
 * Copyright (C) 2018 California Institute of Technology
 *
 * LDASTools frameCPP is free software; you may redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 (GPLv2) of the
 * License or at your discretion, any later version.
 *
 * LDASTools frameCPP is distributed in the hope that it will be useful, but
 * without any warranty or even the implied warranty of merchantability
 * or fitness for a particular purpose. See the GNU General Public
 * License (GPLv2) for more details.
 *
 * Neither the names of the California Institute of Technology (Caltech),
 * The Massachusetts Institute of Technology (M.I.T), The Laser
 * Interferometer Gravitational-Wave Observatory (LIGO), nor the names
 * of its contributors may be used to endorse or promote products derived
 * from this software without specific prior written permission.
 *
 * You should have received a copy of the licensing terms for this
 * software included in the file LICENSE located in the top-level
 * directory of this package. If you did not, you can view a copy at
 * http://dcc.ligo.org/M1500244/LICENSE
 */

#ifndef FRAMECPP__COMMON__DETECTOR_NAMES_HH
#define FRAMECPP__COMMON__DETECTOR_NAMES_HH

#if defined( __cplusplus )

#if !defined( SWIGIMPORTED )
#include <string>
#endif /* ! defined(SWIGIMPORTED) */

#include "ldastoolsal/unordered_map.hh"

namespace FrameCPP
{
    namespace Common
    {
        /**
         * \brief Maintains information about known detectors.
         */
        class DetectorNames
        {
        public:
            /**
             * \brief Information describing a detector.
             *
             * This information is described in section two of appendix "D".
             */
            struct info_type
            {
                std::string           s_detector;
                std::string           s_prefix;
                std::pair< int, int > s_data_quality_bits;
            };
            /**
             * \brief Constructor
             */
            DetectorNames( );

            /**
             * \brief Get information about a detector.
             *
             * \param[in] Name
             *     The name of the detector as listed in the FrDetector
             *     structure.
             *
             * \return
             *     Information associated with the detector.
             */
            const info_type& Detector( const std::string& Name ) const;

            /**
             * \brief Prevent any further modifications to the structure.
             */
            void Freeze( );

            /**
             * \brief Add new element to the table
             *
             * \param[in] DetectorName
             *     The name of the detector as it appears in the FrDetector
             *     structure.
             * \param[in] Detector
             *     Description of the detector.
             * \param[in] Prefix
             *     The channel prefix used in channel names to identify
             *     the detector used.
             * \param[in] DataQualityBits
             *     Bits used in the data quality flag by this detector.
             */
            void operator( )( const std::string&          DetectorName,
                              const std::string&          Detector,
                              const std::string&          Prefix,
                              const std::pair< int, int > DataQualityBits );

        private:
            /**
             * \brief Container of detector information.
             */
            typedef LDASTools::AL::unordered_map< std::string, info_type >
                detector_info_container_type;

            /**
             * \brief State variable for frozen state.
             *
             * If this variable is true, then no further detectors can be
             * appended to the list.
             */
            bool m_frozen;
            /**
             * \brief Storage for detector information.
             *
             * This contains all information about detectors known at the
             * time of the appropriate frame specification.
             */
            detector_info_container_type m_info;
        };

        /**
         * Prevent further additions to the set of detectors.
         */
        inline void
        DetectorNames::Freeze( )
        {
            m_frozen = true;
        }
    } /* namespace Common */
} /* namespace FrameCPP */

#endif /* defined(__cplusplus) */

#endif /* FRAMECPP__COMMON__DETECTOR_NAMES_HH */
