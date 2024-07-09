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

#ifndef FrameCPP__COMMON__PTR_STRUCT_BASE_HH
#define FrameCPP__COMMON__PTR_STRUCT_BASE_HH

namespace FrameCPP
{
    namespace Common
    {
        //-------------------------------------------------------------------
        /// \brief Holder of Stream reference to an object within the stream.
        ///
        /// This is an interface class allowing access to the information
        /// in a version independent mannor.
        //-------------------------------------------------------------------
        struct PTR_STRUCT_BASE : public FrameSpec::Object
        {
            //-----------------------------------------------------------------
            /// \brief Data type for the class identifier.
            ///
            /// \note
            ///     The data type used needs to be the maximum sized data type
            ///     used in any of the frame specifications to ensure
            ///     no rounding errors.
            //-----------------------------------------------------------------
            typedef INT_2U class_type;

            //-----------------------------------------------------------------
            /// \brief Data type for the instance counter.
            ///
            /// \note
            ///     The data type used needs to be the maximum sized data type
            ///     used in any of the frame specifications to ensure
            ///     no rounding errors.
            //-----------------------------------------------------------------
            typedef INT_4U instance_type;

            //-----------------------------------------------------------------
            /// \brief Default constructor
            ///
            /// \return
            ///     New instance of this object.
            //-----------------------------------------------------------------
            PTR_STRUCT_BASE( );

            //-----------------------------------------------------------------
            /// \brief Destructor
            ///
            /// Release the resource back to system.
            /// Because there are other vitual methods,
            /// the destuctor is also virtual to ensure all the resources
            /// are properly released.
            //-----------------------------------------------------------------
            virtual ~PTR_STRUCT_BASE( );

            //-----------------------------------------------------------------
            /// \brief Describe the reference object.
            ///
            /// \param[in] Type
            ///     The type of object being referenced.
            ///
            /// \return
            ///     The text that describes the pointer reference.
            //-----------------------------------------------------------------
            static std::string Desc( const std::string& Type );

            //-----------------------------------------------------------------
            /// \brief Retrieve the class identifier.
            ///
            /// \return
            ///     The class identifier.
            //-----------------------------------------------------------------
            virtual class_type Class( ) const = 0;

            //-----------------------------------------------------------------
            /// \brief Establish the class identifier.
            ///
            /// \param[in] Class
            ///     The class identifier.
            //-----------------------------------------------------------------
            virtual void Class( class_type Class ) = 0;

            //-----------------------------------------------------------------
            /// \brief Retrieve the instance of the class.
            ///
            /// \return
            ///     The instance of the class.
            //-----------------------------------------------------------------
            virtual instance_type Instance( ) const = 0;

            //-----------------------------------------------------------------
            /// \brief Establish the instance of the class.
            ///
            /// \param[in] Value
            ///     The instance of the class.
            //-----------------------------------------------------------------
            virtual void Instance( instance_type Value ) = 0;

            virtual PTR_STRUCT_BASE* Clone( ) const = 0;

            //-----------------------------------------------------------------
            /// \brief Determine if the reference represents a NULL reference
            ///
            /// \return
            ///     True if the reference represents a NULL reference,
            ///     false otherwise.
            //-----------------------------------------------------------------
            bool IsNULL( ) const;
        };

        //-------------------------------------------------------------------
        /// A NULL reference is used to terminate a list of objects.
        //-------------------------------------------------------------------
        inline bool
        PTR_STRUCT_BASE::IsNULL( ) const
        {
            return ( ( Class( ) == 0 ) && ( Instance( ) == 0 ) );
        }

        //-------------------------------------------------------------------
        /// Output the descriptive text that needs to be part of the FrSE
        /// object used to describe the entirety of an object.
        //-------------------------------------------------------------------
        inline std::string
        PTR_STRUCT_BASE::Desc( const std::string& Type )
        {
            std::string ret( "PTR_STRUCT(" );

            ret += Type;
            ret += " *)";
            return ret;
        }
    } // namespace Common
} // namespace FrameCPP

#endif /* FrameCPP__COMMON__PTR_STRUCT_BASE_HH */
