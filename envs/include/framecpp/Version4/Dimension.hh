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

#ifndef FrameCPP_VERSION_4_Dimension_HH
#define FrameCPP_VERSION_4_Dimension_HH

// System Includes
#if !defined( SWIGIMPORTED )
#include <memory>
#include <string>
#endif /* ! defined(SWIGIMPORTED) */

#include "ldastoolsal/types.hh"

#include "framecpp/Version3/Dimension.hh"

#include "framecpp/Version4/FrameSpec.hh"
#include "framecpp/Version4/STRING.hh"

namespace FrameCPP
{

    namespace Version_4
    {

        //-------------------------------------------------------------------
        /// \brief Dimension information for a Vect.
        ///
        /// This is a simple class storing dimension information
        /// for a Vect object.
        /// It stores the following:
        ///
        /// <ol>
        ///   <li> The dimension length. </li>
        ///   <li> Scale factor </li>
        ///   <li> The units (unit per step size along the coordintate). </li>
        /// </ol>
        //-------------------------------------------------------------------
        class Dimension
        {
        public:
            typedef INT_4U nx_type;
            typedef REAL_8 dx_type;
            typedef REAL_8 startX_type;

            /* Constructors/Destructor */
            //! exc: None.
            Dimension( );

            //-----------------------------------------------------------------
            /// \brief Copy constructor
            ///
            /// \param[in] dim
            ///     The source from which to construct the new object.
            ///
            /// \exception std::bad_alloc
            ///     Memory allocation failed.
            //-----------------------------------------------------------------
            Dimension( const Dimension& dim );

            //! exc: std::bad_alloc - Memory allocation failed.
            Dimension( const Previous::Dimension& dim );

            //-----------------------------------------------------------------
            /// \brief Constructor.
            ///
            /// \param[in] nx
            ///     The dimension length.
            /// \param[in] dx
            ///     The Scale Factor.
            /// \param[in] unitX
            ///     The units (unit per step size).
            /// \param[in] startX
            ///     The origin of the data set.
            ///
            /// \exception std::bad_alloc
            ///     Memory allocation failed.
            //-----------------------------------------------------------------
            explicit Dimension( nx_type            nx,
                                dx_type            dx = 1.0,
                                const std::string& unitX = "",
                                startX_type        startX = 0.0 );

            /* Operator Overloads */
#if !defined( SWIG )
            //-----------------------------------------------------------------
            ///
            /// \brief Assignment operator.
            ///
            /// \param[in] dim
            ///     The object to assign from.
            ///
            /// \return
            ///     This object.
            ///
            /// \exception std::bad_alloc
            ///     Memory allocation failed.
            //-----------------------------------------------------------------
            const Dimension& operator=( const Dimension& dim );
#endif /* ! defined(SWIG) */

            //----------------------------------------------------------------
            ///
            /// \brief Equal comparison.
            ///
            /// \param[in] dim
            ///     The object to compare with.
            ///
            /// \return
            ///     true if the objects are equal, false otherwise.
            bool operator==( const Dimension& dim ) const;

            //----------------------------------------------------------------
            ///
            /// \brief Not equal comparison.
            ///
            /// \param[in] dim
            ///     The object to compare with.
            ///
            /// \return
            ///     false if the objects are equal, true otherwise.
            //
            bool operator!=( const Dimension& dim ) const;

            /* Accessors */
            //! exc: None.
            nx_type GetNx( ) const;

            //! exc: None.
            dx_type GetDx( ) const;

            //! exc: None.
            startX_type GetStartX( ) const;

            //! exc: None.
            const STRING& GetUnitX( ) const;

            void SetNx( nx_type Nx );

            cmn_streamsize_type Bytes( ) const;

        private:
            /// \brief Dimension length.
            nx_type mNx;
            /// \brief Scale factor.
            dx_type mDx;
            /// \brief Scale factor in ASCII.
            STRING mUnitX;
            /// \brief Origin.
            startX_type mStartX;
        };

        /******************/
        /* Inline Methods */
        /******************/

        inline Dimension::Dimension( const Previous::Dimension& Source )
            : mNx( Source.GetNx( ) ), mDx( Source.GetDx( ) ),
              mUnitX( Source.GetUnitX( ) ), mStartX( 0.0 )
        {
        }

        //------------------------------------------------------------------
        // Accessors
        //------------------------------------------------------------------

        //------------------------------------------------------------------
        ///
        /// \brief Get the dimension length.
        ///
        /// \return
        ///     The dimension length.
        ///
        inline Dimension::nx_type
        Dimension::GetNx( ) const
        {
            return mNx;
        }

        //------------------------------------------------------------------
        ///
        /// \brief Get the scale factor.
        ///
        /// \return
        ///     The scale factor.
        ///
        inline Dimension::dx_type
        Dimension::GetDx( ) const
        {
            return mDx;
        }

        //------------------------------------------------------------------
        ///
        /// \brief Get data set origin.
        ///
        /// \return
        ///     Data set origin.
        //
        inline Dimension::startX_type
        Dimension::GetStartX( ) const
        {
            return mStartX;
        }

        //------------------------------------------------------------------
        ///
        /// \brief Get the units.
        ///
        /// \return
        ///     The units.
        ///
        inline const STRING&
        Dimension::GetUnitX( ) const
        {
            return mUnitX;
        }

        inline void
        Dimension::SetNx( nx_type Nx )
        {
            mNx = Nx;
        }

        //------------------------------------------------------------------
        // Operator Overloads
        //------------------------------------------------------------------

        //------------------------------------------------------------------
        ///
        /// \brief Assignment operator.
        ///
        /// \param[in] dim
        ///     The object to assign from.
        ///
        /// \return
        ///     This object.
        ///
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
        ///
        /// \brief Equal comparison.
        ///
        /// \param[in] dim
        ///     The object to compare with.
        ///
        /// \return
        ///     true if the objects are equal, false otherwise.
        ///
        //------------------------------------------------------------------
        inline bool
        Dimension::operator==( const Dimension& dim ) const
        {
            return ( ( mNx == dim.mNx ) && ( mDx == dim.mDx ) &&
                     ( mStartX == dim.mStartX ) && ( mUnitX == dim.mUnitX ) );
        }

        //------------------------------------------------------------------
        ///
        /// \brief Not equal comparison.
        ///
        /// \param[in] dim
        ///     The object to compare with.
        ///
        /// \return
        ///     false if the objects are equal, true otherwise.
        ///
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
    } // namespace Version_4

} // namespace FrameCPP

#endif /* FrameCPP_VERSION_4_Dimension_HH */
