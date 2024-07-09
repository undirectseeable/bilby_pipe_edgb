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

#ifndef FrameCPP_VERSION_8_FrProcData_PST_HH
#define FrameCPP_VERSION_8_FrProcData_PST_HH

#if defined( __cplusplus )
namespace FrameCPP
{
    namespace Version_6
    {

#define FR_PROC_DATA_PS_NAMESPACE Version_6

        /**
         * \brief Post-Processed Data Structure Definition.
         */
        template < typename DataType,
                   typename AuxType,
                   typename TableType,
                   typename HistoryType >
        class FrProcDataPST
        {
        public:
            typedef AuxType                             aux_value_type;
            typedef Common::Container< aux_value_type > aux_type;
            typedef typename aux_type::const_iterator   const_aux_iterator;
            typedef typename aux_type::iterator         aux_iterator;

            typedef DataType                             data_value_type;
            typedef Common::Container< data_value_type > data_type;
            typedef typename data_type::const_iterator   const_iterator;
            typedef typename data_type::iterator         iterator;

            typedef TableType                             table_value_type;
            typedef Common::Container< table_value_type > table_type;
            typedef typename table_type::const_iterator   const_table_iterator;
            typedef typename table_type::iterator         table_iterator;

            typedef HistoryType                             history_value_type;
            typedef Common::Container< history_value_type > history_type;
            typedef
                typename history_type::const_iterator const_history_iterator;
            typedef typename history_type::iterator   history_iterator;

            /**
             * \brief Identifier for vector for auxilliary data.
             *
             * \return
             *     A constant reference to the auxilliary data.
             */
            const aux_type& RefAux( ) const;

            /**
             * \brief Identifier for vector for auxilliary data.
             *
             * \return
             *     A reference to the auxilliary data.
             */
            aux_type& RefAux( );

            /**
             * \brief Identifier for vector for data vector.
             *
             * \return
             *     A constant reference to the data vector.
             */
            const data_type& RefData( ) const;

            /**
             * \brief Identifier for vector for data vector.
             *
             * \return
             *     A reference to the data vector.
             */
            data_type& RefData( );

            /**
             * \brief Identifier for parameter table.
             *
             * \return
             *     A constant reference to the parameter table.
             */
            const table_type& RefTable( ) const;

            /**
             * \brief Identifier for parameter table.
             *
             * \return
             *     A reference to the parameter table.
             */
            table_type& RefTable( );

            /**
             * \brief Identifier for channel history.
             *
             * \return
             *     A constant reference to the channel history.
             */
            const history_type& RefHistory( ) const;

            /**
             * \brief Identifier for channel history.
             *
             * \return
             *     A reference to the channel history.
             */
            history_type& RefHistory( );

        protected:
            static const INT_2U MAX_REF = 4;

            /**
             * Data vector.
             * The data vector for single dimensional types (t-Series and
             * f-Series) must have a single dimension.
             */
            data_type data;

            /**
             * Aux vector.
             */
            aux_type aux;

            /**
             * Parameter table.
             */
            table_type table;

            /**
             * Channel history.
             * \note
             *     The first FrHistory should describe the processing used
             *     to build this FrProcData channel.
             *     Its name variable should be the FrProcData name.
             *     If the channel(s) used to produce this FrProcData have
             *     prior FrHistory structures,
             *     then in order to not lose this history,
             *     these structures should be copied to the FrHistory
             *     linked list.
             */
            history_type history;

            /**
             * \brief Default constructor
             *
             * \return
             *    A new instance of this object.
             */
            FrProcDataPST( );

            /**
             * \brief Copy Constructor
             *
             * \param[in] Source
             *     The object from which to copy the information.
             * \param[in] Stream
             *     The stream from which the object is being read.
             *
             * \return
             *    A new instance of this object.
             */
            template < typename PreviousType >
            FrProcDataPST( const PreviousType& Source, istream_type* Stream );

            /**
             * \brief Copy Constructor
             *
             * \param[in] Source
             *     The object from which to copy the information.
             *
             * \return
             *    A new instance of this object.
             */
            FrProcDataPST( const FrProcDataPST& Source );

            /**
             * \brief Stream Constructor
             *
             * \param[in] Stream
             *     The stream from which the object is being read.
             *
             * \return
             *    A new instance of this object.
             */
            FrProcDataPST( istream_type& Stream );

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
            cmn_streamsize_type bytes( const stream_base_type& Stream ) const;

            /**
             * \brief Write the structure to the stream
             *
             * \param[in] Stream
             *     The output stream where the object is to be written.
             */
            void write( ostream_type& Stream ) const;

            /**
             * \brief Copy core data.
             *
             * \param[in] Source
             *     The source from which to copy the data
             */
            void copy_core( const FrProcDataPST& Source );

            /**
             * \brief equality operator
             *
             * \param[in] RHS
             *     The FrProcData object to be compared.
             *
             * \return
             *     The value true is returned if this object is equivelent
             *     to the RHS instance; false otherwise.
             */
            bool operator==( const FrProcDataPST& RHS ) const;
        };

        template < typename DataType,
                   typename AuxType,
                   typename TableType,
                   typename HistoryType >
        inline const typename FrProcDataPST< DataType,
                                             AuxType,
                                             TableType,
                                             HistoryType >::aux_type&
        FrProcDataPST< DataType, AuxType, TableType, HistoryType >::RefAux( )
            const
        {
            return aux;
        }

        template < typename DataType,
                   typename AuxType,
                   typename TableType,
                   typename HistoryType >
        inline typename FrProcDataPST< DataType,
                                       AuxType,
                                       TableType,
                                       HistoryType >::aux_type&
        FrProcDataPST< DataType, AuxType, TableType, HistoryType >::RefAux( )
        {
            return aux;
        }

        template < typename DataType,
                   typename AuxType,
                   typename TableType,
                   typename HistoryType >
        inline const typename FrProcDataPST< DataType,
                                             AuxType,
                                             TableType,
                                             HistoryType >::data_type&
        FrProcDataPST< DataType, AuxType, TableType, HistoryType >::RefData( )
            const
        {
            return data;
        }

        template < typename DataType,
                   typename AuxType,
                   typename TableType,
                   typename HistoryType >
        inline typename FrProcDataPST< DataType,
                                       AuxType,
                                       TableType,
                                       HistoryType >::data_type&
        FrProcDataPST< DataType, AuxType, TableType, HistoryType >::RefData( )
        {
            return data;
        }

        template < typename DataType,
                   typename AuxType,
                   typename TableType,
                   typename HistoryType >
        inline const typename FrProcDataPST< DataType,
                                             AuxType,
                                             TableType,
                                             HistoryType >::history_type&
        FrProcDataPST< DataType, AuxType, TableType, HistoryType >::
            RefHistory( ) const
        {
            return history;
        }

        template < typename DataType,
                   typename AuxType,
                   typename TableType,
                   typename HistoryType >
        inline typename FrProcDataPST< DataType,
                                       AuxType,
                                       TableType,
                                       HistoryType >::history_type&
        FrProcDataPST< DataType, AuxType, TableType, HistoryType >::
            RefHistory( )
        {
            return history;
        }

        template < typename DataType,
                   typename AuxType,
                   typename TableType,
                   typename HistoryType >
        inline const typename FrProcDataPST< DataType,
                                             AuxType,
                                             TableType,
                                             HistoryType >::table_type&
        FrProcDataPST< DataType, AuxType, TableType, HistoryType >::RefTable( )
            const
        {
            return table;
        }

        template < typename DataType,
                   typename AuxType,
                   typename TableType,
                   typename HistoryType >
        inline typename FrProcDataPST< DataType,
                                       AuxType,
                                       TableType,
                                       HistoryType >::table_type&
        FrProcDataPST< DataType, AuxType, TableType, HistoryType >::RefTable( )
        {
            return table;
        }

        template < typename DataType,
                   typename AuxType,
                   typename TableType,
                   typename HistoryType >
        inline FrProcDataPST< DataType, AuxType, TableType, HistoryType >::
            FrProcDataPST( )
        {
        }

#if 0
    template< typename DataType, typename AuxType,
	      typename TableType, typename HistoryType >
    template< >
    FrProcDataPST< DataType, AuxType, TableType, HistoryType >::
    FrProcDataPST( const FrameCPP::Version_4::FrProcData& Source, istream_type* Stream )
    {
      if ( Stream )
      {
        /*-------------------------------------------------------------------
         Modify references
         ------------------------------------------------------------------- */
	Stream->ReplaceRef( RefData( ), Source.RefData( ), MAX_REF );
	Stream->ReplaceRef( RefAux( ), Source.RefAux( ), MAX_REF );
	Stream->ReplaceRef( RefTable( ), Source.RefTable( ), MAX_REF );
      }
    }
#endif /* 0 */

        template < typename DataType,
                   typename AuxType,
                   typename TableType,
                   typename HistoryType >
        template < typename PreviousType >
        FrProcDataPST< DataType, AuxType, TableType, HistoryType >::
            FrProcDataPST( const PreviousType& Source, istream_type* Stream )
        {
            if ( Stream )
            {
                /*-------------------------------------------------------------------
                   Modify references
                   -------------------------------------------------------------------*/
                Stream->ReplaceRef( RefData( ), Source.RefData( ), MAX_REF );
                Stream->ReplaceRef( RefAux( ), Source.RefAux( ), MAX_REF );
                Stream->ReplaceRef( RefTable( ), Source.RefTable( ), MAX_REF );
                Stream->ReplaceRef(
                    RefHistory( ), Source.RefHistory( ), MAX_REF );
            }
        }

        template < typename DataType,
                   typename AuxType,
                   typename TableType,
                   typename HistoryType >
        inline FrProcDataPST< DataType, AuxType, TableType, HistoryType >::
            FrProcDataPST( const FrProcDataPST& Source )
            : data( Source.data ), aux( Source.aux ), table( Source.table ),
              history( Source.history )
        {
        }

        template < typename DataType,
                   typename AuxType,
                   typename TableType,
                   typename HistoryType >
        inline FrProcDataPST< DataType, AuxType, TableType, HistoryType >::
            FrProcDataPST( istream_type& Stream )
        {
            Stream >> data >> aux >> table >> history;
        }

        template < typename DataType,
                   typename AuxType,
                   typename TableType,
                   typename HistoryType >
        inline cmn_streamsize_type
        FrProcDataPST< DataType, AuxType, TableType, HistoryType >::bytes(
            const stream_base_type& Stream ) const
        {
            return Stream.PtrStructBytes( ) /* data */
                + Stream.PtrStructBytes( ) /* aux */
                + Stream.PtrStructBytes( ) /* table */
                + Stream.PtrStructBytes( ) /* history */
                ;
        }

        template < typename DataType,
                   typename AuxType,
                   typename TableType,
                   typename HistoryType >
        inline void
        FrProcDataPST< DataType, AuxType, TableType, HistoryType >::write(
            ostream_type& Stream ) const
        {
            Stream << data << aux << table << history;
        }

        template < typename DataType,
                   typename AuxType,
                   typename TableType,
                   typename HistoryType >
        inline void
        FrProcDataPST< DataType, AuxType, TableType, HistoryType >::copy_core(
            const FrProcDataPST& Source )
        {
            aux = Source.aux;
            table = Source.table;
            history = Source.history;
        }
        template < typename DataType,
                   typename AuxType,
                   typename TableType,
                   typename HistoryType >
        inline bool
        FrProcDataPST< DataType, AuxType, TableType, HistoryType >::
        operator==( const FrProcDataPST& RHS ) const
        {
            return ( ( this == &RHS ) ||
                     ( ( data == RHS.data ) && ( aux == RHS.aux ) &&
                       ( table == RHS.table ) && ( history == RHS.history ) ) );
        }

    } /* namespace Version_6 */
} /* namespace FrameCPP */

#endif /* defined(__cplusplus) */

#endif /* FrameCPP_VERSION_8_FrProcData_HH */
