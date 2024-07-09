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

#ifndef FrameCPP__COMMON__PTR_STRUCT_HH
#define FrameCPP__COMMON__PTR_STRUCT_HH

#if !defined( SWIGIMPORTED )
#include <iostream>
#include <string>
#endif /* ! defined(SWIGIMPORTED) */

#include "ldastoolsal/types.hh"

#include "framecpp/Common/FrameSpec.hh"
#include "framecpp/Common/PTR_STRUCT_BASE.hh"
#include "framecpp/Common/IOStream.hh"

namespace FrameCPP
{
    namespace Common
    {
        //-------------------------------------------------------------------
        /// \brief Holder of Stream reference to an object within the stream.
        ///
        /// This is a version specific interface to the information.
        //-------------------------------------------------------------------
        template < class DC, class DI >
        struct PTR_STRUCT : public PTR_STRUCT_BASE
        {
            typedef DC data_class_type;
            typedef DI data_instance_type;

            typedef PTR_STRUCT_BASE::class_type    class_type;
            typedef PTR_STRUCT_BASE::instance_type instance_type;

            //-----------------------------------------------------------------
            /// \brief Default constructor
            ///
            /// \return
            ///    New instance of this object
            //-----------------------------------------------------------------
            PTR_STRUCT( );

            //-----------------------------------------------------------------
            /// \brief Constructor
            ///
            /// \param[in] ClassId
            ///
            /// \param[in] Instance
            ///
            /// \return
            ///    New instance of this object
            //-----------------------------------------------------------------
            PTR_STRUCT( data_class_type ClassId, data_instance_type Instance );

            //-----------------------------------------------------------------
            /// \brief Retrieve the class identifier.
            ///
            /// \return
            ///     The class identifier.
            //-----------------------------------------------------------------
            virtual class_type Class( ) const;

            //-----------------------------------------------------------------
            /// \brief Establish the class identifier.
            ///
            /// \param[in] Value
            ///     The class identifier.
            //-----------------------------------------------------------------
            virtual void Class( class_type Value );

            //-----------------------------------------------------------------
            /// \brief Retrieve the class identifier.
            //-----------------------------------------------------------------
            inline data_class_type
            ClassRaw( ) const
            {
                return data_class;
            }

            //-----------------------------------------------------------------
            /// \brief Retrieve the instance of the class.
            ///
            /// \return
            ///     The instance of the class.
            //-----------------------------------------------------------------
            virtual instance_type Instance( ) const;

            //-----------------------------------------------------------------
            /// \brief Establish the instance of the class.
            ///
            /// \param[in] Value
            ///     The instance of the class.
            //-----------------------------------------------------------------
            virtual void Instance( instance_type Value );

            //-----------------------------------------------------------------
            /// \brief Establish the instance of the class.
            ///
            /// \return
            ///     The instance of the class.
            //-----------------------------------------------------------------
            inline data_instance_type
            InstanceRaw( ) const
            {
                return data_instance;
            }

            //-----------------------------------------------------------------
            /// \brief Assignment operator
            ///
            /// \param[in] RHS
            ///     The source to copy.
            ///
            /// \return
            ///     Reference to this object.
            //-----------------------------------------------------------------
            const PTR_STRUCT& operator=( const PTR_STRUCT& RHS );

            //-----------------------------------------------------------------
            /// \brief Number of bytes needed to write this structure
            ///
            /// \return
            ///     The number of bytes need to read or write this object.
            //-----------------------------------------------------------------
            static cmn_streamsize_type Bytes( );

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
            cmn_streamsize_type Bytes( const StreamBase& Stream ) const;

            //-----------------------------------------------------------------
            /// \brief Virtual constructor.
            ///
            /// \param[in] Stream
            ///     The input stream from which to read the object.
            ///
            /// \return
            ///    A new instance of this object.
            //-----------------------------------------------------------------
            virtual PTR_STRUCT* Create( IStream& Stream ) const;

            //-----------------------------------------------------------------
            /// \brief Virtual constructor.
            ///
            /// \return
            ///    A new instance of this object.
            //-----------------------------------------------------------------
            virtual PTR_STRUCT* Clone( ) const;

            //-----------------------------------------------------------------
            /// \brief The name structure name of this object.
            ///
            /// \return
            ///     The name of the structure as specified by the frame
            ///     specification.
            //-----------------------------------------------------------------
            virtual const char* ObjectStructName( ) const;

            //-----------------------------------------------------------------
            /// \brief Write the structure to the stream
            ///
            /// \param[in] Stream
            ///     The output stream where the object is to be written.
            //-----------------------------------------------------------------
            virtual void Write( OStream& Stream ) const;

            //-----------------------------------------------------------------
            /// \brief comparison operator
            ///
            /// \param[in] RHS
            ///     The PTR_STRUCT to compare.
            ///
            /// \return
            ///     True if the two PTR_STRUCT elements reference the same
            ///     stream object.
            //-----------------------------------------------------------------
            bool operator==( const PTR_STRUCT& RHS ) const;

            //-----------------------------------------------------------------
            /// \brief comparison operator
            ///
            /// \param[in] Obj
            ///     The stream object to compare.
            ///
            /// \return
            ///     True if this PTR_STRUCT references Obj.
            //-----------------------------------------------------------------
            virtual bool
            operator==( const Common::FrameSpec::Object& Obj ) const;

            //-----------------------------------------------------------------
            /// \brief comparison operator
            ///
            /// \param[in] RHS
            ///     The PTR_STRUCT to compare.
            //-----------------------------------------------------------------
            bool operator!=( const PTR_STRUCT& RHS ) const;

            //-----------------------------------------------------------------
            /// \brief Version specific NULL reference
            //-----------------------------------------------------------------
            static const PTR_STRUCT& NULL_PTR;

        protected:
            //-----------------------------------------------------------------
            /// \brief Demotes object to previous version of the frame spec
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
            virtual FrameSpec::ObjectInterface::demote_ret_type
            demote( INT_2U Target, demote_arg_type Obj, IStream* Stream ) const;

            //-----------------------------------------------------------------
            /// \brief Promotes object to another version of the frame spec
            ///
            /// \param[in] Target
            ///     The version of the promoted frame specification.
            /// \param[in] Obj
            ///     The object to be promoted.
            /// \param[in] Stream
            ///     The input stream from which the original object was read.
            ///
            /// \return
            ///     An object promoted to the next generation.
            //-----------------------------------------------------------------
            virtual FrameSpec::ObjectInterface::promote_ret_type
            promote( INT_2U                                       Target,
                     FrameSpec::ObjectInterface::promote_arg_type Obj,
                     IStream* Stream ) const;

        private:
            using FrameSpec::Object::Create;

            //-----------------------------------------------------------------
            /// \brief The class identifier
            ///
            /// The class identifier of the object.
            /// The values of 0, 1, and 2 are reserved by the frame
            /// specification.
            /// The value 0 is used to partially identify the end of
            /// series of chained objects.
            /// The value 1 is reserved to identify the FrSH class of objects.
            /// The vlaue 2 is reserved to identify the FrSE class of objects.
            /// All other values are at the descretion of the library
            /// implementing the frame specification.
            //-----------------------------------------------------------------
            data_class_type data_class;

            //-----------------------------------------------------------------
            /// \brief Occurence counter.
            ///
            /// Counter for occurrence of this class of object within the
            /// current frame or current file.
            /// It starts from zero (0).
            ///
            /// \note
            /// All instance counters are set to zero (0) after FrEndOfFrame
            /// \b and FrEndOfFile.
            //-----------------------------------------------------------------
            data_instance_type data_instance;

            PTR_STRUCT( IStream& Stream );
            PTR_STRUCT( const PTR_STRUCT& Source );
        };

        //-------------------------------------------------------------------
        //-------------------------------------------------------------------
        template < class DC, class DI >
        inline PTR_STRUCT< DC, DI >::PTR_STRUCT( )
            : data_class( 0 ), data_instance( 0 )
        {
        }

        //-------------------------------------------------------------------
        //-------------------------------------------------------------------
        template < class DC, class DI >
        inline PTR_STRUCT< DC, DI >::PTR_STRUCT( data_class_type    ClassId,
                                                 data_instance_type Instance )
            : data_class( ClassId ), data_instance( Instance )
        {
        }

        //-------------------------------------------------------------------
        //-------------------------------------------------------------------
        template < class DC, class DI >
        inline PTR_STRUCT< DC, DI >::PTR_STRUCT( IStream& Stream )
        {
            Stream >> data_class >> data_instance;
        }

        //-------------------------------------------------------------------
        //-------------------------------------------------------------------
        template < class DC, class DI >
        inline PTR_STRUCT< DC, DI >::PTR_STRUCT( const PTR_STRUCT& Source )
            : PTR_STRUCT_BASE( Source ), data_class( Source.data_class ),
              data_instance( Source.data_instance )
        {
        }

        //-------------------------------------------------------------------
        //-------------------------------------------------------------------
        template < class DC, class DI >
        typename PTR_STRUCT< DC, DI >::class_type
        PTR_STRUCT< DC, DI >::Class( ) const
        {
            return data_class;
        }

        //-------------------------------------------------------------------
        //-------------------------------------------------------------------
        template < class DC, class DI >
        void
        PTR_STRUCT< DC, DI >::Class( class_type Class )
        {
            data_class = Class;
        }

        //-------------------------------------------------------------------
        //-------------------------------------------------------------------
        template < class DC, class DI >
        typename PTR_STRUCT< DC, DI >::instance_type
        PTR_STRUCT< DC, DI >::Instance( ) const
        {
            return data_instance;
        }

        //-------------------------------------------------------------------
        //-------------------------------------------------------------------
        template < class DC, class DI >
        void
        PTR_STRUCT< DC, DI >::Instance( instance_type Instance )
        {
            data_instance = Instance;
        }

        //-------------------------------------------------------------------
        //-------------------------------------------------------------------
        template < class DC, class DI >
        const PTR_STRUCT< DC, DI >&
        PTR_STRUCT< DC, DI >::operator=( const PTR_STRUCT< DC, DI >& RHS )
        {
            data_class = RHS.data_class;
            data_instance = RHS.data_instance;
            return *this;
        }

        //-------------------------------------------------------------------
        //-------------------------------------------------------------------
        template < class DC, class DI >
        inline cmn_streamsize_type
        PTR_STRUCT< DC, DI >::Bytes( )
        {
            return sizeof( data_class_type ) + sizeof( data_instance_type );
        }

        //-------------------------------------------------------------------
        //-------------------------------------------------------------------
        template < class DC, class DI >
        inline cmn_streamsize_type
        PTR_STRUCT< DC, DI >::Bytes( const StreamBase& Stream ) const
        {
            return Bytes( );
        }

        //-------------------------------------------------------------------
        //-------------------------------------------------------------------
        template < class DC, class DI >
        inline PTR_STRUCT< DC, DI >*
        PTR_STRUCT< DC, DI >::Create( IStream& Stream ) const
        {
            return new PTR_STRUCT( Stream );
        }

        //-------------------------------------------------------------------
        //-------------------------------------------------------------------
        template < class DC, class DI >
        inline PTR_STRUCT< DC, DI >*
        PTR_STRUCT< DC, DI >::Clone( ) const
        {
            return new PTR_STRUCT( *this );
        }

        //-------------------------------------------------------------------
        //-------------------------------------------------------------------
        template < class DC, class DI >
        inline FrameSpec::ObjectInterface::demote_ret_type
        PTR_STRUCT< DC, DI >::demote( INT_2U          Target,
                                      demote_arg_type Obj,
                                      IStream*        Stream ) const
        {
            throw Unimplemented( "Object* PTR_STRUCT< DC, DI>* PTR_STRUCT< DC, "
                                 "DI >::Demote( Object* Obj ) const",
                                 0,
                                 __FILE__,
                                 __LINE__ );
        }

        //-------------------------------------------------------------------
        //-------------------------------------------------------------------
        template < class DC, class DI >
        inline FrameSpec::ObjectInterface::promote_ret_type
        PTR_STRUCT< DC, DI >::promote(
            INT_2U                                       Target,
            FrameSpec::ObjectInterface::promote_arg_type Obj,
            IStream*                                     Stream ) const
        {
            throw Unimplemented( "Object* PTR_STRUCT< DC, DI>* PTR_STRUCT< DC, "
                                 "DI >::Promote( Object* Obj ) const",
                                 0,
                                 __FILE__,
                                 __LINE__ );
        }

        //-------------------------------------------------------------------
        //-------------------------------------------------------------------
        template < class DC, class DI >
        inline const char*
        PTR_STRUCT< DC, DI >::ObjectStructName( ) const
        {
            static const char* const name = "PTR_STRUCT";
            return name;
        }

        //-------------------------------------------------------------------
        //-------------------------------------------------------------------
        template < class DC, class DI >
        inline void
        PTR_STRUCT< DC, DI >::Write( OStream& Stream ) const
        {
            Stream << data_class << data_instance;
        }

        //-------------------------------------------------------------------
        //-------------------------------------------------------------------
        template < class DC, class DI >
        inline bool
        PTR_STRUCT< DC, DI >::operator==( const PTR_STRUCT& RHS ) const
        {
            return ( ( data_class == RHS.data_class ) &&
                     ( data_instance == RHS.data_instance ) );
        }

        //-------------------------------------------------------------------
        //-------------------------------------------------------------------
        template < class DC, class DI >
        inline bool
        PTR_STRUCT< DC, DI >::
        operator==( const Common::FrameSpec::Object& Obj ) const
        {
            typedef PTR_STRUCT< DC, DI > data_type;
            try
            {
                const data_type& robj =
                    reinterpret_cast< const data_type& >( Obj );
                return ( *this == robj );
            }
            catch ( ... )
            {
            }
            return ( false );
            return ( *this == Obj );
        }

        //-------------------------------------------------------------------
        //-------------------------------------------------------------------
        template < class DC, class DI >
        inline bool
        PTR_STRUCT< DC, DI >::
        operator!=( const PTR_STRUCT< DC, DI >& RHS ) const
        {
            return !( *this == RHS );
        }

        //-------------------------------------------------------------------
        //-------------------------------------------------------------------
        template < class DC, class DI >
        const PTR_STRUCT< DC, DI >&
            PTR_STRUCT< DC, DI >::NULL_PTR = PTR_STRUCT< DC, DI >( 0, 0 );
    } // namespace Common
} // namespace FrameCPP
#endif /* FrameCPP__COMMON__PTR_STRUCT_HH */
