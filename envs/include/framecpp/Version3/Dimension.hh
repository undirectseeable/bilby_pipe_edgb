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

#ifndef FrameCPP_VERSION_3_Dimension_HH
#define FrameCPP_VERSION_3_Dimension_HH

// System Includes
#if !defined( SWIGIMPORTED )
#include <memory>
#include <string>
#endif /* ! defined(SWIGIMPORTED) */

#include "ldastoolsal/types.hh"

#include "framecpp/Version3/STRING.hh"

namespace FrameCPP
{

    namespace Version_3
    {

        //-------------------------------------------------------------------
        ///
        /// \brief Dimension information for a Vect.
        ///
        /// This is a simple class storing dimension information for a Vect
        /// object. It stores the following: <p><ol>
        ///     <li> The dimension length. </li>
        ///     <li> Scale factor </li>
        ///     <li> The units (unit per step size along the coordintate). </li>
        /// </ol>
        ///
        class Dimension
        {
        public:
            typedef INT_4U nx_type;
            typedef REAL_8 dx_type;

            /* Constructors/Destructor */
            Dimension( );

            /// \exception std::bad_alloc
            ///   Memory allocation failed.
            Dimension( const Dimension& dim );

            /// \excpetion std::bad_alloc
            ///   Memory allocation failed.
            explicit Dimension( nx_type            nx,
                                dx_type            dx = 1.0,
                                const std::string& unitX = "" );

            /* Operator Overloads */
#if !defined( SWIG )
            //-----------------------------------------------------------------
            /// \brief Assignment operator.
            ///
            /// \param[in] dim
            ///   The object to assign from.
            ///
            /// \return
            ///   This object.
            ///
            /// \exception std::bad_alloc
            ///   Memory allocation failed.
            const Dimension& operator=( const Dimension& dim );
#endif /* ! defined(SWIG) */

            //----------------------------------------------------------------
            ///
            /// \brief Equal comparison.
            ///
            /// \param[in] dim - The object to compare with.
            ///
            /// \return
            ///   true if the objects are equal, false otherwise.
            bool operator==( const Dimension& dim ) const;

            //----------------------------------------------------------------
            ///
            /// \brief Not equal comparison.
            ///
            /// \param[in] dim - The object to compare with.
            ///
            /// \return
            ///   false if the objects are equal, true otherwise.
            bool operator!=( const Dimension& dim ) const;

            /* Accessors */
            nx_type GetNx( ) const;

            dx_type GetDx( ) const;

            const STRING& GetUnitX( ) const;

            //-----------------------------------------------------------------
            /// \brief Set sample spacing
            ///
            /// \param[in] Dx
            ///     The new sample rate for the coordinate.
            //-----------------------------------------------------------------
            void SetDx( dx_type Dx );

            void SetNx( nx_type Nx );

            //-----------------------------------------------------------------
            /// \brief Set scale factor in ASCII
            ///
            /// \param[in] UnitX
            ///     The new scale factor description.
            //-----------------------------------------------------------------
            void SetUnitX( const STRING& UnitX );

            cmn_streamsize_type Bytes( ) const;

        private:
            /// \brief Dimension length.
            nx_type mNx;
            /// \brief Scale factor.
            dx_type mDx;
            /// \brief Scale factor in ASCII.
            STRING mUnitX;
        };

        /******************/
        /* Inline Methods */
        /******************/

        //------------------------------------------------------------------
        // Accessors
        //------------------------------------------------------------------

        //------------------------------------------------------------------
        /// \brief Get the dimension length.
        ///
        /// \return
        ///   The dimension length.
        inline Dimension::nx_type
        Dimension::GetNx( ) const
        {
            return mNx;
        }

        //------------------------------------------------------------------
        /// \brief Get the scale factor.
        ///
        /// \return
        ///   The scale factor.
        inline Dimension::dx_type
        Dimension::GetDx( ) const
        {
            return mDx;
        }

        //------------------------------------------------------------------
        /// \brief Get the units.
        ///
        /// \return
        ///   The units.
        inline const STRING&
        Dimension::GetUnitX( ) const
        {
            return mUnitX;
        }

        //------------------------------------------------------------------
        /// Establish a new value for sample spacing along the coordinate.
        //------------------------------------------------------------------
        inline void
        Dimension::SetDx( dx_type Dx )
        {
            mDx = Dx;
        }

        inline void
        Dimension::SetNx( nx_type Nx )
        {
            mNx = Nx;
        }

        //------------------------------------------------------------------
        /// Establish a new value for sample spacing along the coordinate.
        //------------------------------------------------------------------
        inline void
        Dimension::SetUnitX( const STRING& UnitX )
        {
            mUnitX = UnitX;
        }

        //------------------------------------------------------------------
        // Operator Overloads
        //------------------------------------------------------------------

        //------------------------------------------------------------------
        /// \brief Assignment operator.
        ///
        /// \param[in] dim
        ///   The object to assign from.
        ///
        /// \return
        ///   This object.
        ///
        /// \exception std::bad_alloc
        ///   Memory allocation failed.
        //------------------------------------------------------------------
        inline const Dimension&
        Dimension::operator=( const Dimension& dim )
        {
            if ( this != &dim )
            {
                mNx = dim.mNx;
                mDx = dim.mDx;
                mUnitX = dim.mUnitX;
            }

            return *this;
        }

        //------------------------------------------------------------------
        /// \brief Equal comparison.
        ///
        /// \param[in] dim
        ///   The object to compare with.
        ///
        /// \return
        ///   true if the objects are equal, false otherwise.
        //------------------------------------------------------------------
        inline bool
        Dimension::operator==( const Dimension& dim ) const
        {
            return ( ( mNx == dim.mNx ) && ( mDx == dim.mDx ) &&
                     ( mUnitX == dim.mUnitX ) );
        }

        //------------------------------------------------------------------
        /// \brief Not equal comparison.
        ///
        /// \param[in] dim
        ///   The object to compare with.
        ///
        /// \return
        ///   false if the objects are equal, true otherwise.
        //------------------------------------------------------------------
        inline bool
        Dimension::operator!=( const Dimension& dim ) const
        {
            return !( dim == *this );
        }

        inline cmn_streamsize_type
        Dimension::Bytes( ) const
        {
            return sizeof( mNx ) + sizeof( mDx ) + mUnitX.Bytes( );
        }
    } // namespace Version_3

} // namespace FrameCPP

#endif /* FrameCPP_VERSION_3_Dimension_HH */
