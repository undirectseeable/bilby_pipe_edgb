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

#ifndef FrameCPP_VERSION_8_Dimension_HH
#define FrameCPP_VERSION_8_Dimension_HH

// System Includes
#if !defined( SWIGIMPORTED )
#include <memory>
#include <string>
#endif /* ! defined(SWIGIMPORTED) */

#if !defined( SWIGIMPORTED )
#include "ldastoolsal/types.hh"

#include "framecpp/Version7/Dimension.hh"

#include "framecpp/Version8/FrameSpec.hh"
#include "framecpp/Version8/STRING.hh"
#endif /* ! defined(SWIGIMPORTED) */

#undef DIMENSION_NDIM_TYPE
#undef DIMENSION_NX_TYPE
#undef DIMENSION_DX_TYPE
#undef DIMENSION_STARTX_TYPE

#define DIMENSION_NDIM_TYPE INT_4U
#define DIMENSION_NX_TYPE INT_8U
#define DIMENSION_DX_TYPE REAL_8
#define DIMENSION_STARTX_TYPE REAL_8

namespace FrameCPP
{

    namespace Version_8
    {

        //------------------------------------------------------------------
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
            typedef DIMENSION_NDIM_TYPE   nDim_type;
            typedef DIMENSION_NX_TYPE     nx_type;
            typedef DIMENSION_DX_TYPE     dx_type;
            typedef DIMENSION_STARTX_TYPE startX_type;
            typedef STRING                unitX_type;

            /* Constructors/Destructor */
            Dimension( );

            Dimension( const Dimension& dim );

            explicit Dimension( nx_type            nx,
                                dx_type            dx = 1.0,
                                const std::string& unitX = "",
                                startX_type        startX = 0.0 );

            Dimension( const Previous::Dimension& Source );

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
            ///
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
            ///
            bool operator!=( const Dimension& dim ) const;

            /* Accessors */
            //----------------------------------------------------------------
            ///
            /// \brief Get the dimension length.
            ///
            /// \return
            ///     The dimension length.
            ///
            //----------------------------------------------------------------
            nx_type GetNx( ) const;

            //----------------------------------------------------------------
            ///
            /// \brief Get the scale factor.
            ///
            /// \return
            ///     The scale factor.
            ///
            //----------------------------------------------------------------
            dx_type GetDx( ) const;

            //----------------------------------------------------------------
            ///
            /// \brief Get data set origin.
            ///
            /// \return
            ///     Data set origin.
            ///
            //----------------------------------------------------------------
            startX_type GetStartX( ) const;

            //----------------------------------------------------------------
            ///
            /// \brief Get the units.
            ///
            /// \return
            ///     The units.
            ///
            //----------------------------------------------------------------
            const unitX_type& GetUnitX( ) const;

            //-----------------------------------------------------------------
            /// \brief Set sample spacing
            ///
            /// \param[in] Dx
            ///     The new sample rate for the coordinate.
            //-----------------------------------------------------------------
            void SetDx( dx_type Dx );

            //-----------------------------------------------------------------
            /// \brief Set dimension length
            ///
            /// \param[in] Nx
            ///     The new dimension length
            //-----------------------------------------------------------------
            void SetNx( nx_type Nx );

            //----------------------------------------------------------------
            /// \brief Set data set origin.
            ///
            /// \param[in] StartX
            ///     Data set origin.
            //----------------------------------------------------------------
            void SetStartX( startX_type StartX );

            //-----------------------------------------------------------------
            /// \brief Set scale factor in ASCII
            ///
            /// \param[in] UnitX
            ///     The new scale factor description.
            //-----------------------------------------------------------------
            void SetUnitX( const unitX_type& UnitX );

            cmn_streamsize_type Bytes( ) const;

            static nx_type CalcNData( nDim_type NDims, const Dimension* Dims );

        private:
            //-----------------------------------------------------------------
            /// \brief Dimension length.
            //-----------------------------------------------------------------
            nx_type mNx;
            //-----------------------------------------------------------------
            /// \brief Scale factor.
            //-----------------------------------------------------------------
            dx_type mDx;
            //-----------------------------------------------------------------
            /// \brief Scale factor in ASCII.
            //-----------------------------------------------------------------
            unitX_type mUnitX;
            //-----------------------------------------------------------------
            /// \brief Origin.
            //-----------------------------------------------------------------
            startX_type mStartX;
        };

        //===================================================================
        // Inlined methods
        //===================================================================

        inline Dimension::Dimension( const Previous::Dimension& Source )
            : mNx( Source.GetNx( ) ), mDx( Source.GetDx( ) ),
              mUnitX( Source.GetUnitX( ) ), mStartX( Source.GetStartX( ) )
        {
        }

        inline Dimension::nx_type
        Dimension::CalcNData( nDim_type NDims, const Dimension* Dims )
        {
            if ( NDims > 0 )
            {
                nx_type retval = 1;

                for ( nDim_type cur = 0, last = NDims; cur != last; ++cur )
                {
                    retval *= Dims[ cur ].GetNx( );
                }
                return retval;
            }
            return 0;
        }

        //------------------------------------------------------------------
        // Accessors
        //------------------------------------------------------------------

        inline Dimension::nx_type
        Dimension::GetNx( ) const
        {
            return mNx;
        }

        inline Dimension::dx_type
        Dimension::GetDx( ) const
        {
            return mDx;
        }

        inline Dimension::startX_type
        Dimension::GetStartX( ) const
        {
            return mStartX;
        }

        inline const Dimension::unitX_type&
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

        inline void
        Dimension::SetStartX( startX_type StartX )
        {
            mStartX = StartX;
        }

        //------------------------------------------------------------------
        /// Establish a new value for sample spacing along the coordinate.
        //------------------------------------------------------------------
        inline void
        Dimension::SetUnitX( const unitX_type& UnitX )
        {
            mUnitX = UnitX;
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
            return ( ( this == &dim ) ||
                     ( ( mNx == dim.mNx ) && ( mDx == dim.mDx ) &&
                       ( mStartX == dim.mStartX ) &&
                       ( mUnitX == dim.mUnitX ) ) );
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
    } // namespace Version_8

} // namespace FrameCPP

#endif /* FrameCPP_VERSION_8_Dimension_HH */
