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

#ifndef FrameCPP__VERSION_8__Specs_HH
#define FrameCPP__VERSION_8__Specs_HH

#include "ldastoolsal/types.hh"

#ifndef SWIGIMPORTED
#include "framecpp/Common/DetectorNames.hh"
#endif /* SWIGIMPORTED */
#include "framecpp/Common/FrameSpec.hh"

#if defined( __cplusplus ) && !defined( SWIG )
namespace FrameCPP
{
    namespace Common
    {
        class OFrameStreamGen;
    }

    namespace Version_7
    {
    }

    /**
     * \brief Implementation of the version 8 specification
     *
     * This namespace implements the Version 8 of the frame specification
     * as described in the docuemnt LIGO-T970130-v1 dated March 4, 2009.
     */
    namespace Version_8
    {
        namespace Previous = Version_7;

        typedef REAL_4 dt_type;
        typedef INT_8U position_type;

        typedef INT_4U                        checksum_type;
        typedef Common::FrameSpec::class_type class_type;

        template < typename ObjectType >
        class ObjectWithChecksum
            : public Common::FrameSpec::ObjectWithChecksum< ObjectType,
                                                            checksum_type >
        {
        private:
            typedef Common::FrameSpec::ObjectWithChecksum< ObjectType,
                                                           checksum_type >
                object_base_type;

        public:
            ObjectWithChecksum( )
            {
            }

            /**
             * \brief Constructor
             */
            ObjectWithChecksum( const Common::Description* Description )
                : object_base_type( Description )
            {
            }

            /**
             * \brief Constructor
             */
            ObjectWithChecksum( class_type                 Class,
                                const Common::Description* Description )
                : object_base_type( Class, Description )
            {
            }

            /**
             * \brief copy constructor
             */
            ObjectWithChecksum( const ObjectWithChecksum& Source )
                : object_base_type( Source )
            {
            }

            /**
             * \brief Constructor - Stream
             */
            ObjectWithChecksum( Common::IStream& Source )
                : object_base_type( Source )
            {
            }

            /**
             * \brief Destructor
             */
            ~ObjectWithChecksum( )
            {
            }
        };

        const CHAR_U DATA_FORMAT_VERSION = 8;
        const CHAR_U LIBRARY_MINOR_VERSION = 1;

        bool init_frame_spec( );

#ifndef SWIGIMPORTED
        extern const Common::DetectorNames& DetectorNameTable;
#endif /* SWIGIMPORTED */

    } /* namespace Version_8 */
} /* namespace FrameCPP */
#endif /* defined(__cplusplus) && !defined(SWIG) */
#endif /* FrameCPP__VERSION_8__Specs_HH */
