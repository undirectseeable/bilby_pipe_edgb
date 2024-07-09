//
// LDASTools AL - A library collection to provide an abstraction layer
//
// Copyright (C) 2018 California Institute of Technology
//
// LDASTools AL is free software; you may redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 (GPLv2) of the
// License or at your discretion, any later version.
//
// LDASTools AL is distributed in the hope that it will be useful, but
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

#ifndef LDASTOOLSAL__THREAD_POOL_HH
#define LDASTOOLSAL__THREAD_POOL_HH

namespace LDASTools
{
    namespace AL
    {
        class TaskThread;

        //---------------------------------------------------------------------
        /// \brief Maintains a pool of threads
        ///
        /// This is a singleton class that maintains a list of threads that
        /// can be reused to perform asyncronous tasks.
        //---------------------------------------------------------------------
        class ThreadPool
        {
        public:
            //-----------------------------------------------------------------
            /// \brief Base for unary functions to be used in ForEach call
            //-----------------------------------------------------------------
            class UnaryFunction
            {
            public:
                enum state
                {
                    THREAD_POOL_TASK_ACTIVE,
                    THREAD_POOL_TASK_IDLE,
                    THREAD_POOL_TASK_ABANDONED
                };

                typedef TaskThread element_type;

                virtual void operator( )( const element_type& Task,
                                          state               State ) = 0;
            };

            //-------------------------------------------------------------------
            /// \brief Acquire a thread
            ///
            /// \return
            ///     A resouce from the pool.
            //-------------------------------------------------------------------
            static TaskThread* Acquire( );

            //-------------------------------------------------------------------
            /// \brief Check if a Thread is currently active
            ///
            /// \param[in] Resource
            ///     Check a resouce if in the pool.
            //-------------------------------------------------------------------
            static bool Active( TaskThread* Resource );

            //-------------------------------------------------------------------
            /// \brief Iterate over the active threads
            ///
            /// \param[in] Func
            ///     Function to execute.
            //-------------------------------------------------------------------
            static void ForEach( UnaryFunction& Func );

            //-------------------------------------------------------------------
            /// \brief Return a thread to the pool
            ///
            /// \param[in] Resource
            ///     Return a resouce to the pool.
            //-------------------------------------------------------------------
            static void Relinquish( TaskThread* Resource );

            //-------------------------------------------------------------------
            /// \brief Release all resources from the thread pool.
            //-------------------------------------------------------------------
            static void Reset( );

        private:
            //-------------------------------------------------------------------
            /// \brief  Hide default constructor
            ///
            /// Do not want anyone to create a seperate instance of this class.
            //-------------------------------------------------------------------
            ThreadPool( );
            //-------------------------------------------------------------------
            /// \brief  Hide copy constructor
            ///
            /// Do not want to create another instance of the class based on
            /// a priviously created instance.
            //-------------------------------------------------------------------
            ThreadPool( const ThreadPool& Source );
            //-------------------------------------------------------------------
            /// \brief  Hide assignment operator
            ///
            /// Do not want to copy one instance to another.
            //-------------------------------------------------------------------
            ThreadPool operator=( const ThreadPool& Source );
        };
    } // namespace AL
} // namespace LDASTools

#endif /* LDASTOOLSAL__THREAD_POOL_HH */
