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

#ifndef FrameCPP_VERSION_6_Dimension_HH
#define FrameCPP_VERSION_6_Dimension_HH

// System Includes
#if !defined( SWIGIMPORTED )
#include <memory>
#include <string>
#endif /* ! defined(SWIGIMPORTED) */

#include "ldastoolsal/types.hh"

#include "framecpp/Version4/Dimension.hh"

#include "framecpp/Version6/FrameSpec.hh"
#include "framecpp/Version6/STRING.hh"

namespace FrameCPP
{

    namespace Version_6
    {

        //-------------------------------------------------------------------
        //
        //: Dimension information for a Vect.
        //
        // This is a simple class storing dimension information for a Vect
        // object. It stores the following: <p><ol>
        //     <li> The dimension length. </li>
        //     <li> Scale factor </li>
        //     <li> The units (unit per step size along the coordintate). </li>
        // </ol>
        //
        class Dimension
        {
        public:
            typedef INT_8U nx_type;
            typedef REAL_8 dx_type;
            typedef REAL_8 startX_type;

            /* Constructors/Destructor */
            //! exc: None.
            Dimension( );

            //! exc: std::bad_alloc - Memory allocation failed.
            Dimension( const Dimension& dim );

            //! exc: std::bad_alloc - Memory allocation failed.
            explicit Dimension( INT_8U             nx,
                                REAL_8             dx = 1.0,
                                const std::string& unitX = "",
                                REAL_8             startX = 0.0 );

            Dimension( const Previous::Dimension& Source );

            /* Operator Overloads */
#if !defined( SWIG )
            //-----------------------------------------------------------------
            //
            //: Assignment operator.
            //
            //! param: const Dimension& dim - The object to assign from.
            //
            //! return: const Dimension& -- This object.
            //
            //! exc: std::bad_alloc - Memory allocation failed.
            //
            const Dimension& operator=( const Dimension& dim );
#endif /* ! defined(SWIG) */

            //----------------------------------------------------------------
            //
            //: Equal comparison.
            //
            //! param: const Dimension& dim - The object to compare with.
            //
            //! return: bool -- true if the objects are equal, false otherwise.
            //
            //! exc: None.
            //
            bool operator==( const Dimension& dim ) const;

            //----------------------------------------------------------------
            //
            //: Not equal comparison.
            //
            //! param: const Dimension& dim - The object to compare with.
            //
            //! return: bool -- false if the objects are equal, true otherwise.
            //
            //! exc: None.
            //
            bool operator!=( const Dimension& dim ) const;

            /* Accessors */
            //! exc: None.
            INT_8U GetNx( ) const;

            //! exc: None.
            REAL_8 GetDx( ) const;

            //! exc: None.
            REAL_8 GetStartX( ) const;

            //! exc: None.
            const STRING& GetUnitX( ) const;

            void SetNx( INT_8U Nx );

            cmn_streamsize_type Bytes( ) const;

        private:
            //: Dimension length.
            INT_8U mNx;
            //: Scale factor.
            REAL_8 mDx;
            //: Scale factor in ASCII.
            STRING mUnitX;
            //: Origin.
            REAL_8 mStartX;
        };

        /******************/
        /* Inline Methods */
        /******************/
        inline Dimension::Dimension( const Previous::Dimension& Source )
            : mNx( Source.GetNx( ) ), mDx( Source.GetDx( ) ),
              mUnitX( Source.GetUnitX( ) ), mStartX( Source.GetStartX( ) )
        {
        }

        //------------------------------------------------------------------
        // Accessors
        //------------------------------------------------------------------

        //------------------------------------------------------------------
        //
        //: Get the dimension length.
        //
        //! return: INT_8U -- The dimension length.
        //
        //! exc: None.
        //
        inline INT_8U
        Dimension::GetNx( ) const
        {
            return mNx;
        }

        //------------------------------------------------------------------
        //
        //: Get the scale factor.
        //
        //! return: REAL_8 -- The scale factor.
        //
        //! exc: None.
        //
        inline REAL_8
        Dimension::GetDx( ) const
        {
            return mDx;
        }

        //------------------------------------------------------------------
        //
        //: Get data set origin.
        //
        //! return: REAL_8 -- Data set origin.
        //
        //! exc: None.
        //
        inline REAL_8
        Dimension::GetStartX( ) const
        {
            return mStartX;
        }

        //------------------------------------------------------------------
        //
        //: Get the units.
        //
        //! return: const std::string& -- The units.
        //
        //! exc: None.
        //
        inline const STRING&
        Dimension::GetUnitX( ) const
        {
            return mUnitX;
        }

        inline void
        Dimension::SetNx( INT_8U Nx )
        {
            mNx = Nx;
        }

        //------------------------------------------------------------------
        // Operator Overloads
        //------------------------------------------------------------------

        //------------------------------------------------------------------
        //
        //: Assignment operator.
        //
        //! param: const Dimension& dim - The object to assign from.
        //
        //! return: const Dimension& - This object.
        //
        //! exc: std::bad_alloc - Memory allocation failed.
        //
        //------------------------------------------------------------------
        inline const Dimension&
        Dimension::operator=( const Dimension& dim )
        {
            if ( this != &dim )
            {
                mNx = dim.mNx;
                mDx = dim.mDx;
                mStartX = dim.mStartX;
                mUnitX = dim.mUnitX;
            }

            return *this;
        }

        //------------------------------------------------------------------
        //
        //: Equal comparison.
        //
        //! param: const Dimension& dim - The object to compare with.
        //
        //! return: bool - true if the objects are equal, false otherwise.
        //
        //! exc: None.
        //
        //------------------------------------------------------------------
        inline bool
        Dimension::operator==( const Dimension& dim ) const
        {
            return ( ( mNx == dim.mNx ) && ( mDx == dim.mDx ) &&
                     ( mStartX == dim.mStartX ) && ( mUnitX == dim.mUnitX ) );
        }

        //------------------------------------------------------------------
        //
        //: Not equal comparison.
        //
        //! param: const Dimension& dim - The object to compare with.
        //
        //! return: bool - false if the objects are equal, true otherwise.
        //
        //! exc: None.
        //
        //------------------------------------------------------------------
        inline bool
        Dimension::operator!=( const Dimension& dim ) const
        {
            return !( dim == *this );
        }

        inline cmn_streamsize_type
        Dimension::Bytes( ) const
        {
            return sizeof( mNx ) + sizeof( mDx ) + mUnitX.Bytes( ) +
                sizeof( mStartX );
        }
    } // namespace Version_6

} // namespace FrameCPP

#endif /* FrameCPP_VERSION_6_Dimension_HH */
