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

#ifndef FrameCPP_VERSION_3_FrAdcDataPST_HH
#define FrameCPP_VERSION_3_FrAdcDataPST_HH

#if defined( __cplusplus )
#if !defined( SWIGIMPORTED )
#include <memory>
#include <vector>
#endif /* ! defined(SWIGIMPORTED) */

#if !defined( SWIGIMPORTED )
#include "framecpp/Common/Container.hh"
#include "framecpp/Common/IOStream.hh"

#include "framecpp/Version3/FrameSpec.hh"
#include "framecpp/Version3/Dimension.hh"
#include "framecpp/Version3/FrVect.hh"
#include "framecpp/Version3/STRING.hh"
#endif /* ! defined(SWIGIMPORTED) */
#endif /* defined(__cplusplus) */

#if defined( __cplusplus )
#if !defined( SWIGIMPORTED )
namespace FrameCPP
{
    namespace Version_3
    {

#define FR_ADC_DATA_PS_NAMESPACE Version_3

        /**
         * \brief ADC Data that does reference a pointer
         */
        template < typename DataType, typename AuxType >
        class FrAdcDataPST
        {
        public:
            typedef DataType                             data_value_type;
            typedef Common::Container< data_value_type > data_type;
            typedef typename data_type::const_iterator   const_iterator;
            typedef typename data_type::iterator         iterator;

            typedef Common::Container< AuxType >      aux_type;
            typedef typename aux_type::const_iterator const_aux_iterator;
            typedef typename aux_type::iterator       aux_iterator;

            static const INT_2U MAX_REF = 2;

            /**
             * \brief Identifier for vector for user-provided information.
             *
             * \return
             *     A constant reference to the user-provided information.
             */
            const aux_type& RefAux( ) const;

            /**
             * \brief Identifier for vector for user-provided information.
             *
             * \return
             *     A reference to the user-provided information.
             */
            aux_type& RefAux( );

            /**
             * \brief Identifier for vector of sampled data.
             *
             * \return
             *     A constant reference to the sampled data.
             */
            const data_type& RefData( ) const;

            /**
             * \brief Identifier for vector of sampled data.
             *
             * \return
             *     A reference to the sampled data.
             */
            data_type& RefData( );

        protected:
            /**
             * Identifier for vector of sampled data.
             */
            data_type data;
            /**
             * Identifier fro vector for user-provided information.
             * Its use is generic.
             */
            aux_type aux;

            /**
             * \brief Default constructor
             */
            FrAdcDataPST( );

            /**
             * \brief Initialzie the instance from an input stream
             */
            FrAdcDataPST( Common::IStream& Stream );

            /**
             * \brief Initialzie the instance from an input stream
             */
            template < typename PreviousType >
            FrAdcDataPST( const PreviousType& Source, Common::IStream* Stream );

            /**
             * \brief Number of bytes needed to write this structure
             *
             * \param[in] Stream
             *     The stream from which to the object is being read or
             *     written.
             *
             * \return
             *     The number of bytes need to read or write this object.
             */
            cmn_streamsize_type Bytes( const Common::StreamBase& Stream ) const;

            /**
             * \brief Provide a description of object
             */
            template < typename DescriptionType, typename FrSEType >
            static void
            structDescription( DescriptionType&   Desc,
                               const std::string& FrVectStructName );

            /**
             * \brief Copy key pieces when duplicating the object
             *
             * \param[in] Source
             *     The refence to use as the pattern of information to
             *     copied.
             */
            void copyCore( const FrAdcDataPST& Source );

            /**
             * \brief Write contents to the stream
             */
            void write( Common::OStream& Stream ) const;

            /**
             * \brief Comparison operator
             */
            bool operator==( const FrAdcDataPST& RHS ) const;
        };

        /**
         * The object is contructed using default rules.
         */
        template < typename DataType, typename AuxType >
        inline FrAdcDataPST< DataType, AuxType >::FrAdcDataPST( )
        {
        }

        /**
         * Initialzie the instance from an input stream
         */
        template < typename DataType, typename AuxType >
        inline FrAdcDataPST< DataType, AuxType >::FrAdcDataPST(
            Common::IStream& Stream )
        {
            Stream >> data >> aux;
        }

        template < typename DataType, typename AuxType >
        inline const typename FrAdcDataPST< DataType, AuxType >::aux_type&
        FrAdcDataPST< DataType, AuxType >::RefAux( ) const
        {
            return aux;
        }

        template < typename DataType, typename AuxType >
        inline typename FrAdcDataPST< DataType, AuxType >::aux_type&
        FrAdcDataPST< DataType, AuxType >::RefAux( )
        {
            return aux;
        }

        template < typename DataType, typename AuxType >
        inline const typename FrAdcDataPST< DataType, AuxType >::data_type&
        FrAdcDataPST< DataType, AuxType >::RefData( ) const
        {
            return data;
        }

        template < typename DataType, typename AuxType >
        inline typename FrAdcDataPST< DataType, AuxType >::data_type&
        FrAdcDataPST< DataType, AuxType >::RefData( )
        {
            return data;
        }

        template < typename DataType, typename AuxType >
        template < typename PreviousType >
        inline FrAdcDataPST< DataType, AuxType >::FrAdcDataPST(
            const PreviousType& Source, Common::IStream* Stream )
        {
            if ( Stream )
            {
                /*-------------------------------------------------------------------
                   Modify references
                  -------------------------------------------------------------------*/
                Stream->ReplaceRef( RefData( ), Source.RefData( ), MAX_REF );
                Stream->ReplaceRef( RefAux( ), Source.RefAux( ), MAX_REF );
            }
        }

        /**
         * \brief Number of bytes needed to write this structure
         *
         * \param[in] Stream
         *     The stream from which to the object is being read or
         *     written.
         *
         * \return
         *     The number of bytes need to read or write this object.
         */
        template < typename DataType, typename AuxType >
        inline cmn_streamsize_type
        FrAdcDataPST< DataType, AuxType >::Bytes(
            const Common::StreamBase& Stream ) const
        {
            return Stream.PtrStructBytes( ) /* data */
                + Stream.PtrStructBytes( ) /* aux */
                ;
        }

        template < typename DataType, typename AuxType >
        template < typename DescriptionType, typename FrSEType >
        inline void
        FrAdcDataPST< DataType, AuxType >::structDescription(
            DescriptionType& Desc, const std::string& FrVectStructName )
        {
            Desc( FrSEType( "data", FrVectStructName, "" ) );
            Desc( FrSEType( "aux", FrVectStructName, "" ) );
        }

        template < typename DataType, typename AuxType >
        inline void
        FrAdcDataPST< DataType, AuxType >::copyCore(
            const FrAdcDataPST& Source )
        {
            aux = Source.aux;
        }

        /**
         * \brief Write contents to the stream
         */
        template < typename DataType, typename AuxType >
        inline void
        FrAdcDataPST< DataType, AuxType >::write(
            Common::OStream& Stream ) const
        {
            Stream << data << aux;
        }

        /**
         * \brief Comparison operator
         */
        template < typename DataType, typename AuxType >
        inline bool
        FrAdcDataPST< DataType, AuxType >::
        operator==( const FrAdcDataPST& RHS ) const
        {
            return ( ( data == RHS.data ) && ( aux == RHS.aux ) );
        }

    } /* namespace Version_3 */
} /* namespace FrameCPP */
#endif /* ! defined(SWIGIMPORTED) */

#endif /* defined(__cplusplus) */

#endif /* FrameCPP_VERSION_3_FrAdcDataPST_HH */
