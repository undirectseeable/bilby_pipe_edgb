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

#ifndef GENERAL__COMMAND_LINE_OPTIONS
#define GENERAL__COMMAND_LINE_OPTIONS

#include <iostream>
#include <list>
#include <sstream>
#include <stdexcept>
#include <string>

#include <boost/shared_ptr.hpp>

#include "ldastoolsal/unordered_map.hh"

namespace LDASTools
{
    namespace AL
    {
        //=====================================================================
        /// \brief Maintains an ordered container of unparsed command line
        /// options
        //=====================================================================
        class CommandLineOptions : protected std::list< std::string >
        {
        public:
            enum
            {
                OPT_END_OF_OPTIONS = -1
            };
            typedef std::string  option_type;
            typedef std::ostream ostream;
            typedef int          argc_type;
            typedef const char** argv_type;

        private:
            typedef std::list< option_type > option_container_type;

        public:
            struct Validator
            {
            public:
                virtual ~Validator( );
                virtual bool operator( )( const std::string& Arg );

            private:
            };

            struct ValidateBool : public Validator
            {
            public:
                virtual bool operator( )( const std::string& Arg );

            private:
            };

            class Option
            {
            public:
                enum arg_type
                {
                    ARG_NONE,
                    ARG_REQUIRED,
                    ARG_OPTIONAL
                };

                struct acceptor
                {
                public:
                    virtual bool operator( )( ) = 0;

                private:
                };

                Option( int                ArgumentId,
                        const std::string& ArgumentName,
                        arg_type           ArgType,
                        const std::string& Usage,
                        const std::string& ArgumentArg = std::string( "" ),
                        Validator*         V = new Validator( ) );

                Option( const Option& Source );

                const std::string& ArgumentArg( ) const;

                const std::string& ArgumentName( ) const;

                int ArgumentId( ) const;

                arg_type ArgumentType( ) const;

                const std::string& Description( ) const;

                static const char* Prefix( );

                bool ValidateArg( const std::string& Arg ) const;

            private:
                static const char* m_prefix;

                const int                      m_id;
                const std::string              m_name;
                const arg_type                 m_arg_type;
                const std::string              m_usage;
                const std::string              m_argument;
                boost::shared_ptr< Validator > validator;
            };

            class OptionSet
            {
            public:
                typedef Option element_type;

                void Add( const Option& Opt );

                void Add( const OptionSet& Opts );

                void Description( const std::string& Text );

                void Summary( const std::string& Text );

                bool SummaryOnly( ) const;

                void Synopsis( const std::string& Text );

                ostream& Write( ostream& Stream, int Indent = 0 ) const;

                const Option& operator[]( const std::string& Name ) const;

                const Option& operator[]( int ) const;

            protected:
                typedef std::list< Option > option_container_type;
                typedef LDASTools::AL::
                    unordered_map< int, option_container_type::const_iterator >
                        key_container_type;
                typedef LDASTools::AL::unordered_map<
                    std::string,
                    option_container_type::const_iterator >
                    name_container_type;

                typedef std::list< const OptionSet* > subcommand_container_type;

                option_container_type     m_options;
                name_container_type       m_name_mapping;
                key_container_type        m_key_mapping;
                subcommand_container_type m_subcommands;

                std::string m_description;
                std::string m_summary;
                std::string m_synopsis;

                //-------------------------------------------------------------------
                /// \brief Format a paragraph of data
                ///
                /// \param[in] Stream
                ///     Output stream where the paragraph is to be written.
                /// \param[in] Indent
                ///     The number of columns to indent each line of the
                ///     paragraph.
                /// \param[in] Paragraph
                ///     The text of the paragraph.
                //-------------------------------------------------------------------
                static void hanging_par( ostream&           Stream,
                                         size_t             Indent,
                                         const std::string& Paragraph );
            };

            //---------------------------------------------------------------------
            /// \brief Constructor
            ///
            /// \param[in] ArgC
            ///     Number of arguments being passed.
            /// \param[in] ArgV
            ///     Array of parameters
            ///
            /// \return
            ///     New instance of this object.
            //---------------------------------------------------------------------
            CommandLineOptions( argc_type ArgC, argv_type ArgV );

            //---------------------------------------------------------------------
            /// \brief Constructor
            ///
            /// \param[in] ArgC
            ///     Number of arguments being passed.
            /// \param[in] ArgV
            ///     Array of parameters
            ///
            /// \return
            ///     New instance of this object.
            //---------------------------------------------------------------------
            CommandLineOptions( argc_type ArgC, char** ArgV );

            //---------------------------------------------------------------------
            /// \brief Constructor
            ///
            /// \param[in] Args
            ///     Container of arguments
            ///
            /// \return
            ///     New instance of this object.
            //---------------------------------------------------------------------
            template < typename ARGS >
            inline CommandLineOptions( const ARGS& Args )
                : m_program_name( Args.front( ) )
            {
                typename ARGS::const_iterator cur = Args.begin( );

                ++cur;
                for ( typename ARGS::const_iterator last = Args.end( );
                      cur != last;
                      ++cur )
                {
                    //---------------------------------------------------------------
                    // Seed container of unparsed options
                    //---------------------------------------------------------------
                    push_back( *cur );
                }
            }

            //---------------------------------------------------------------------
            //
            //---------------------------------------------------------------------
            static bool InterpretBoolean( const std::string& Value );

            //---------------------------------------------------------------------
            // \brief Parse off an argument
            //---------------------------------------------------------------------
            int Parse( const OptionSet& Options,
                       std::string&     ArgumentName,
                       std::string&     ArgumentValue );

            //---------------------------------------------------------------------
            /// \brief Obtain the next option from the container.
            ///
            /// This does reduce the size by one.
            //---------------------------------------------------------------------
            const option_type Pop( );

            //---------------------------------------------------------------------
            /// \brief Return the program name associated with this application.
            //---------------------------------------------------------------------
            const option_type ProgramName( ) const;

            //---------------------------------------------------------------------
            // Expose these functions to access the data
            //---------------------------------------------------------------------
            using option_container_type::empty;
            using option_container_type::size;

        private:
            //---------------------------------------------------------------------
            /// \brief The program name associated with this application.
            //---------------------------------------------------------------------
            const option_type m_program_name;
        };

        //-----------------------------------------------------------------------
        //-----------------------------------------------------------------------
        inline const std::string&
        CommandLineOptions::Option::ArgumentArg( ) const
        {
            return m_argument;
        }

        //-----------------------------------------------------------------------
        //-----------------------------------------------------------------------
        inline int
        CommandLineOptions::Option::ArgumentId( ) const
        {
            return m_id;
        }

        //-----------------------------------------------------------------------
        //-----------------------------------------------------------------------
        inline const std::string&
        CommandLineOptions::Option::ArgumentName( ) const
        {
            return m_name;
        }

        //-----------------------------------------------------------------------
        //-----------------------------------------------------------------------
        inline CommandLineOptions::Option::arg_type
        CommandLineOptions::Option::ArgumentType( ) const
        {
            return m_arg_type;
        }

        //-----------------------------------------------------------------------
        //-----------------------------------------------------------------------
        inline const std::string&
        CommandLineOptions::Option::Description( ) const
        {
            return m_usage;
        }

        //-----------------------------------------------------------------------
        //-----------------------------------------------------------------------
        inline const char*
        CommandLineOptions::Option::Prefix( )
        {
            return m_prefix;
        }

        //-----------------------------------------------------------------------
        //-----------------------------------------------------------------------
        inline bool
        CommandLineOptions::Option::ValidateArg( const std::string& Arg ) const
        {
            return ( ( ( validator ) ? validator->operator( )( Arg ) : true ) );
        }

        //=======================================================================
        //=======================================================================

        //-----------------------------------------------------------------------
        //-----------------------------------------------------------------------
        inline void
        CommandLineOptions::OptionSet::Description( const std::string& Text )
        {
            m_description = Text;
        }

        //-----------------------------------------------------------------------
        //-----------------------------------------------------------------------
        inline void
        CommandLineOptions::OptionSet::Summary( const std::string& Text )
        {
            m_summary = Text;
        }

        //-----------------------------------------------------------------------
        //-----------------------------------------------------------------------
        inline bool
        CommandLineOptions::OptionSet::SummaryOnly( ) const
        {
            return ( ( m_synopsis.empty( ) == true ) &&
                     ( m_options.empty( ) == true ) &&
                     ( m_summary.empty( ) == false ) );
        }
        //-----------------------------------------------------------------------
        //-----------------------------------------------------------------------
        inline void
        CommandLineOptions::OptionSet::Synopsis( const std::string& Text )
        {
            m_synopsis = Text;
        }

        //-----------------------------------------------------------------------
        //-----------------------------------------------------------------------
        inline const CommandLineOptions::option_type
        CommandLineOptions::Pop( )
        {
            if ( empty( ) == false )
            {
                //-------------------------------------------------------------------
                // Return the next unparsed option
                //-------------------------------------------------------------------
                option_type retval = front( );
                pop_front( );

                return retval;
            }

            //---------------------------------------------------------------------
            // There are no unparsed options.
            // Throw std::range_error.
            //---------------------------------------------------------------------
            std::ostringstream msg;

            msg << "There are no unparsed options";
            throw std::range_error( msg.str( ) );
        }

        //-----------------------------------------------------------------------
        //-----------------------------------------------------------------------
        inline const CommandLineOptions::option_type
        CommandLineOptions::ProgramName( ) const
        {
            return m_program_name;
        }
    } // namespace AL
} // namespace LDASTools

inline LDASTools::AL::CommandLineOptions::ostream&
operator<<( LDASTools::AL::CommandLineOptions::ostream&         Stream,
            const LDASTools::AL::CommandLineOptions::OptionSet& Opts )
{
    return Opts.Write( Stream );
}

inline std::ostream&
operator<<( std::ostream&                                    Stream,
            const LDASTools::AL::CommandLineOptions::Option& Opt )
{
    Stream << "--" << Opt.ArgumentName( );
    return Stream;
}

#endif /* GENERAL__COMMAND_LINE_OPTIONS */
