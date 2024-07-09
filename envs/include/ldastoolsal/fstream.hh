/*
 * Copyright (c) 1999
 * Silicon Graphics Computer Systems, Inc.
 *
 * Copyright (c) 1999
 * Boris Fomitchev
 *
 * This material is provided "as is", with absolutely no warranty expressed
 * or implied. Any use is at your own risk.
 *
 * Permission to use or copy this software for any purpose is hereby granted
 * without fee, provided the above notices are retained on all copies.
 * Permission to modify the code and to distribute modified code is granted,
 * provided the above notices are retained, and a notice that the code was
 * modified is included with the above copyright notice.
 *
 */
/// This header defines classes basic_filebuf, basic_ifstream,
/// basic_ofstream, and basic_fstream.  These classes represent
/// streambufs and streams whose sources or destinations are files.

#ifndef GENERAL__FSTREAM_HH
#define GENERAL__FSTREAM_HH

#if !defined( SWIGIMPORTED )
#include <stdlib.h>

#include <functional>
#include <iostream>
#include <locale>
#include <streambuf>
#endif /* ! defined(SWIGIMPORTED) */

/* :TODO: Need to write the doxygen documentation for fstream.hh */
//// \cond EXCLUDE

#define _STLP_NO_EXTENSIONS 1
typedef int _STLP_fd;

namespace LDASTools
{

    namespace AL
    {
        //// \cond EXCLUDE
        template < class _Traits >
        struct _Eq_traits
            : public std::binary_function< typename _Traits::char_type,
                                           typename _Traits::char_type,
                                           bool >
        {
            bool
            operator( )( const typename _Traits::char_type& __x,
                         const typename _Traits::char_type& __y ) const
            {
                return _Traits::eq( __x, __y );
            }
        };
        //// \endcond EXCLUDE

        //// \cond EXCLUDE
        //----------------------------------------------------------------------
        /// Class _Filebuf_base, a private base class to factor out the system-
        /// dependent code from basic_filebuf<>.

        class _Filebuf_base
        {
        public: // Opening and closing files.
            static const std::ios_base::openmode m_default_openmode;

            _Filebuf_base( );

            bool
                 _M_open( const char*, std::ios_base::openmode, long __protection );
            bool _M_open( const char*, std::ios_base::openmode );
            bool _M_open( int __id,
                          std::ios_base::openmode = m_default_openmode );
            bool _M_close( );

        public: // Low-level I/O, like Unix read/write
            std::ptrdiff_t _M_read( char* __buf, std::ptrdiff_t __n );
            std::streamoff _M_seek( std::streamoff         __offset,
                                    std::ios_base::seekdir __dir );
            std::streamoff _M_file_size( );
            bool           _M_write( char* __buf, std::ptrdiff_t __n );

        public: // Memory-mapped I/O.
            void* _M_mmap( std::streamoff __offset, std::streamoff __len );
            void  _M_unmap( void* __mmap_base, std::streamoff __len );

        public:
            /// Returns a value n such that, if pos is the file pointer at the
            /// beginning of the range [first, last), pos + n is the file
            /// pointer at the end.  On many operating systems n == __last -
            /// __first. In Unix, writing n characters always bumps the file
            /// position by n. In Windows text mode, however, it bumps the file
            /// position by n + m, where m is the number of newlines in the
            /// range.  That's because an internal \n corresponds to an external
            /// two-character sequence.
            std::streamoff
            _M_get_offset( char* __first, char* __last )
            {
                return __last - __first;
            }

            /// Returns true if we're in binary mode or if we're using an OS or
            /// file system where there is no distinction between text and
            /// binary mode.
            bool
            _M_in_binary_mode( ) const
            {
                return true;
            }

        protected: // Static data members.
            static size_t _M_page_size;

        protected: // Data members.
            _STLP_fd _M_file_id;
#ifdef _STLP_USE_STDIO_IO
            /// for stdio, the whole FILE* is being kept here
            FILE* _M_file;
#endif
#ifdef _STLP_USE_WIN32_IO
            void* _M_view_id;
#endif

            std::ios_base::openmode _M_openmode;
            unsigned char           _M_is_open;
            unsigned char           _M_should_close;
            unsigned char           _M_regular_file;

        public:
            static size_t
            __page_size( )
            {
                return _M_page_size;
            }
            int
            __o_mode( ) const
            {
                return (int)_M_openmode;
            }
            bool
            __is_open( ) const
            {
                return ( _M_is_open != 0 );
            }
            bool
            __should_close( ) const
            {
                return ( _M_should_close != 0 );
            }
            bool
            __regular_file( ) const
            {
                return ( _M_regular_file != 0 );
            }
            _STLP_fd
            __get_fd( ) const
            {
                return _M_file_id;
            }
        };
        //// \endcond EXCLUDE

        //// \cond EXCLUDE
        //----------------------------------------------------------------------
        /// Class basic_filebuf<>.

        /// Forward declaration of two helper classes.
        template < class _Traits >
        class _Noconv_input;
        template <>
        class _Noconv_input< std::char_traits< char > >;

        template < class _Traits >
        class _Noconv_output;
        template <>
        class _Noconv_output< std::char_traits< char > >;

        /// There is a specialized version of underflow, for
        /// basic_filebuf<char>, in fstream.cxx.

        template < class _CharT, class _Traits = std::char_traits< _CharT > >
        class _Underflow;
        //// \endcond EXCLUDE

        template <>
        class _Underflow< char, std::char_traits< char > >;

        /// \brief  Buffer for file streams
        template < class _CharT, class _Traits = std::char_traits< _CharT > >
        class basic_filebuf : public std::basic_streambuf< _CharT, _Traits >
        {
        public:
            /// \brief  character type
            typedef _CharT char_type;
            /// \brief  integer type
            typedef typename _Traits::int_type int_type;
            /// \brief  position type
            typedef typename _Traits::pos_type pos_type;
            /// \brief  offset type
            typedef typename _Traits::off_type off_type;
            /// \brief  traits type
            typedef _Traits traits_type;

            /// \brief  state type
            typedef typename _Traits::state_type _State_type;
            /// \brief  stream buffer type
            typedef std::basic_streambuf< _CharT, _Traits > _Base;
            /// \brief  self reference type
            typedef basic_filebuf< _CharT, _Traits > _Self;

        public:
            /// \brief  Constructor
            basic_filebuf( );
            /// \brief  Destructor
            ~basic_filebuf( );

        public:
            /// \brief  Check if stream is open
            bool
            is_open( ) const
            {
                return _M_base.__is_open( );
            }

            /// \brief  Open a stream
            _Self*
            open( const char* __s, std::ios_base::openmode __m )
            {
                return _M_base._M_open( __s, __m ) ? this : 0;
            }

#ifndef _STLP_NO_EXTENSIONS
            /// \brief  Open a stream
            _Self*
            open( const char*             __s,
                  std::ios_base::openmode __m,
                  long                    __protection )
            {
                return _M_base._M_open( __s, __m, __protection ) ? this : 0;
            }

            /// \brief  Obtain file descriptor
            _STLP_fd
            fd( ) const
            {
                return _M_base.__get_fd( );
            }

            /// \brief  Attach a stream to a file descriptor.
            _Self*
            open( int                     __id,
                  std::ios_base::openmode _Init_mode = m_default_openmode )
            {
                return this->_M_open( __id, _Init_mode );
            }
#endif

            /// \brief  Attach a stream to a file descriptor.
            _Self*
            _M_open( int                     __id,
                     std::ios_base::openmode _Init_mode =
                         _Filebuf_base::m_default_openmode )
            {
                return _M_base._M_open( __id, _Init_mode ) ? this : 0;
            }

            /// \brief  Close the stream
            _Self* close( );

            /// \brief  Enable/disable use of memory mapped I/O for stream
            void
            UseMemoryMappedIO( bool Value )
            {
                _M_use_memory_mapped_io = Value;
            }

            /// \brief  Obtain the memory mapped I/O status use for the stream
            bool
            UseMemoryMappedIO( ) const
            {
                return _M_use_memory_mapped_io;
            }

            /// \brief  Set buffer limit
            virtual std::basic_streambuf< _CharT, _Traits >*
            setbuf( char_type*, std::streamsize );

            virtual pos_type
            seekoff( off_type                Off,
                     std::ios_base::seekdir  Way,
                     std::ios_base::openmode Mode = std::ios_base::in |
                         std::ios_base::out );

            virtual pos_type
            seekpos( pos_type                Pos,
                     std::ios_base::openmode Mode = std::ios_base::in |
                         std::ios_base::out );

        protected: // Virtual functions from basic_streambuf.
            virtual int_type underflow( );
            virtual int_type overflow( int_type c = _Traits::eof( ) );

            virtual std::streamsize showmanyc( );

            virtual int_type pbackfail( int_type = traits_type::eof( ) );

            virtual int  sync( );
            virtual void imbue( const std::locale& );

        private: // Helper functions.
            pos_type seekoff_core( off_type,
                                   std::ios_base::seekdir,
                                   std::ios_base::openmode );
            pos_type seekpos_core( pos_type, std::ios_base::openmode );

            virtual int_type underflow_core( );
            virtual int_type overflow_core( int_type = traits_type::eof( ) );

            /// Precondition: we are currently in putback input mode.  Effect:
            /// switches back to ordinary input mode.
            void
            _M_exit_putback_mode( )
            {
                this->setg( _M_saved_eback, _M_saved_gptr, _M_saved_egptr );
                _M_in_putback_mode = false;
            }
            bool _M_switch_to_input_mode( );
            void _M_exit_input_mode( );
            bool _M_switch_to_output_mode( );

            int_type _M_input_error( );
            int_type _M_underflow_aux( );
            ///  friend class _Noconv_input<_Traits>;
            ///  friend class _Noconv_output<_Traits>;
            friend class _Underflow< _CharT, _Traits >;

            int_type _M_output_error( );
            bool     _M_unshift( );

            bool _M_allocate_buffers( _CharT* __buf, std::streamsize __n );
            bool _M_allocate_buffers( );
            void _M_deallocate_buffers( );

            pos_type
            _M_seek_return( off_type __off, _State_type __state )
            {
                if ( __off != -1 )
                {
                    if ( _M_in_input_mode )
                        _M_exit_input_mode( );
                    _M_in_input_mode = false;
                    _M_in_output_mode = false;
                    _M_in_putback_mode = false;
                    _M_in_error_mode = false;
                    this->setg( 0, 0, 0 );
                    this->setp( 0, 0 );
                }

                pos_type __result( __off );
                __result.state( __state );
                return __result;
            }

            bool _M_seek_init( bool __do_unshift );

            void _M_setup_codecvt( const std::locale& );

        private: // Data members used in all modes.
            _Filebuf_base _M_base;

        private: // Locale-related information.
            unsigned char _M_constant_width;
            unsigned char _M_always_noconv;

            /// true unless disabled by user
            bool _M_use_memory_mapped_io; // True if memory mapped io should be
                                          // used

            /// private:                        // Mode flags.
            unsigned char _M_int_buf_dynamic; // True if internal buffer is heap
                                              // allocated,
            /// false if it was supplied by the user.
            unsigned char _M_in_input_mode;
            unsigned char _M_in_output_mode;
            unsigned char _M_in_error_mode;
            unsigned char _M_in_putback_mode;

            /// Internal buffer: characters seen by the filebuf's clients.
            _CharT* _M_int_buf;
            _CharT* _M_int_buf_EOS;

            /// External buffer: characters corresponding to the external file.
            char* _M_ext_buf;
            char* _M_ext_buf_EOS;

            /// The range [_M_ext_buf, _M_ext_buf_converted) contains the
            /// external characters corresponding to the sequence in the
            /// internal buffer.  The range [_M_ext_buf_converted,
            /// _M_ext_buf_end) contains characters that have been read into the
            /// external buffer but have not been converted to an internal
            /// sequence.
            char* _M_ext_buf_converted;
            char* _M_ext_buf_end;

            /// State corresponding to beginning of internal buffer.
            _State_type _M_state;

        private: // Data members used only in input mode.
            /// Similar to _M_state except that it corresponds to
            /// the end of the internal buffer instead of the beginning.
            _State_type _M_end_state;

            /// This is a null pointer unless we are in mmap input mode.
            void*          _M_mmap_base;
            std::streamoff _M_mmap_len;

        private:
            /// For keeping trace of where we are (reduces lseek calls).
            pos_type m_pos;
            pos_type current_pos( std::ios_base::openmode Mode );

        private: // Data members used only in putback mode.
            _CharT* _M_saved_eback;
            _CharT* _M_saved_gptr;
            _CharT* _M_saved_egptr;

            typedef std::codecvt< _CharT, char, _State_type > _Codecvt;
            const _Codecvt*                                   _M_codecvt;

            int _M_width; // Width of the encoding (if constant), else 1
            int _M_max_width; // Largest possible width of single character.

            enum
            {
                _S_pback_buf_size = 8
            };
            _CharT _M_pback_buf[ _S_pback_buf_size ];

            /// for _Noconv_output
        public:
            bool
            _M_write( char* __buf, std::ptrdiff_t __n )
            {
                return _M_base._M_write( __buf, __n );
            }

        public:
            int_type
            _M_do_noconv_input( )
            {
                _M_ext_buf_converted = _M_ext_buf_end;
                this->setg( (char_type*)_M_ext_buf,
                            (char_type*)_M_ext_buf,
                            (char_type*)_M_ext_buf_end );
                return traits_type::to_int_type( *_M_ext_buf );
            }
        };

#if defined( _STLP_USE_TEMPLATE_EXPORT )
        _STLP_EXPORT_TEMPLATE_CLASS
        basic_filebuf< char, std::char_traits< char > >;
#if !defined( _STLP_NO_WCHAR_T )
        _STLP_EXPORT_TEMPLATE_CLASS
        basic_filebuf< wchar_t, std::char_traits< wchar_t > >;
#endif
#endif /* _STLP_USE_TEMPLATE_EXPORT */

        /// public:
        /// helper class.
        template < class _CharT >
        struct _Filebuf_Tmp_Buf
        {
            _CharT* _M_ptr;
            _Filebuf_Tmp_Buf( std::ptrdiff_t __n ) : _M_ptr( 0 )
            {
                _M_ptr = new _CharT[ __n ];
            }
            ~_Filebuf_Tmp_Buf( )
            {
                delete[] _M_ptr;
            }
        };

        /// This class had to be designed very carefully to work
        /// with Visual C++.
        ///
        template < class _Traits >
        class _Noconv_output
        {
        public:
            typedef typename _Traits::char_type char_type;
            static bool
            _M_doit( basic_filebuf< char_type, _Traits >*,
                     char_type*,
                     char_type* )
            {
                return false;
            }
        };

        template <>
        class _Noconv_output< std::char_traits< char > >
        {
        public:
            static bool
            _M_doit( basic_filebuf< char, std::char_traits< char > >* __buf,
                     char*                                            __first,
                     char*                                            __last )
            {
                std::ptrdiff_t __n = __last - __first;
                if ( __buf->_M_write( __first, __n ) )
                {
                    return true;
                }
                else
                    return false;
            }
        };

        //----------------------------------------------------------------------
        /// basic_filebuf<> helper functions.

        //----------------------------------------
        /// Helper functions for switching between modes.

        /// This class had to be designed very carefully to work
        /// with Visual C++.
        ///
        template < class _Traits >
        class _Noconv_input
        {
        public:
            typedef typename _Traits::int_type  int_type;
            typedef typename _Traits::char_type char_type;

            static inline int_type
            _M_doit( basic_filebuf< char_type, _Traits >* )
            {
                return 0;
            }
        };

        template <>
        class _Noconv_input< std::char_traits< char > >
        {
        public:
            static inline int
            _M_doit( basic_filebuf< char, std::char_traits< char > >* __buf )
            {
                return __buf->_M_do_noconv_input( );
            }
        };

        /// underflow() may be called for one of two reasons.  (1) We've
        /// been going through the special putback buffer, and we need to move
        /// back to the regular internal buffer.  (2) We've exhausted the
        /// internal buffer, and we need to replentish it.
        template < class _CharT, class _Traits >
        class _Underflow
        {
        public:
            typedef typename _Traits::int_type int_type;
            typedef _Traits                    traits_type;

            static int_type _M_doit( basic_filebuf< _CharT, _Traits >* __this );
        };

        /// Specialization of underflow: if the character type is char, maybe
        /// we can use mmap instead of read.
        template <>
        class _Underflow< char, std::char_traits< char > >
        {
        public:
            typedef std::char_traits< char >::int_type int_type;
            typedef std::char_traits< char >           traits_type;
            static int _M_doit( basic_filebuf< char, traits_type >* __this );
        };

        /// There is a specialized version of underflow, for
        /// basic_filebuf<char>, in fstream.cxx.

        template < class _CharT, class _Traits >
        typename _Underflow< _CharT, _Traits >::int_type
        _Underflow< _CharT, _Traits >::_M_doit(
            basic_filebuf< _CharT, _Traits >* __this )
        {
            if ( !__this->_M_in_input_mode )
            {
                if ( !__this->_M_switch_to_input_mode( ) )
                    return traits_type::eof( );
            }

            else if ( __this->_M_in_putback_mode )
            {
                __this->_M_exit_putback_mode( );
                if ( __this->gptr( ) != __this->egptr( ) )
                {
                    int_type __c = traits_type::to_int_type( *__this->gptr( ) );
                    return __c;
                }
            }

            return __this->_M_underflow_aux( );
        }

#if defined( _STLP_USE_TEMPLATE_EXPORT ) && !defined( _STLP_NO_WCHAR_T )
        _STLP_EXPORT_TEMPLATE_CLASS
        _Underflow< wchar_t, std::char_traits< wchar_t > >;
#endif

        //----------------------------------------------------------------------
        /// Class basic_ifstream<>

        template < class _CharT, class _Traits = std::char_traits< _CharT > >
        class basic_ifstream : public std::basic_istream< _CharT, _Traits >
        {
        public: // Types
            typedef _CharT                     char_type;
            typedef typename _Traits::int_type int_type;
            typedef typename _Traits::pos_type pos_type;
            typedef typename _Traits::off_type off_type;
            typedef _Traits                    traits_type;

            typedef std::basic_ios< _CharT, _Traits >     _Basic_ios;
            typedef std::basic_istream< _CharT, _Traits > _Base;
            typedef basic_filebuf< _CharT, _Traits >      _Buf;

        public: // Constructors, destructor.
            basic_ifstream( )
                : std::basic_ios< _CharT, _Traits >( ),
                  std::basic_istream< _CharT, _Traits >( 0 ), _M_buf( )
            {
                this->init( &_M_buf );
            }

            explicit basic_ifstream(
                const char*             __s,
                std::ios_base::openmode __mod = std::ios_base::in )
                : std::basic_ios< _CharT, _Traits >( ),
                  std::basic_istream< _CharT, _Traits >( 0 ), _M_buf( )
            {
                this->init( &_M_buf );
                if ( !_M_buf.open( __s, __mod | std::ios_base::in ) )
                    this->setstate( std::ios_base::failbit );
            }

#ifndef _STLP_NO_EXTENSIONS
            explicit basic_ifstream(
                int __id, std::ios_base::openmode __mod = std::ios_base::in )
                : basic_ios< _CharT, _Traits >( ),
                  basic_istream< _CharT, _Traits >( 0 ), _M_buf( )
            {
                this->init( &_M_buf );
                if ( !_M_buf.open( __id, __mod | std::ios_base::in ) )
                    this->setstate( std::ios_base::failbit );
            }
            basic_ifstream( const char*             __s,
                            std::ios_base::openmode __m,
                            long                    __protection )
                : basic_ios< _CharT, _Traits >( ),
                  basic_istream< _CharT, _Traits >( 0 ), _M_buf( )
            {
                this->init( &_M_buf );
                if ( !_M_buf.open(
                         __s, __m | std::ios_base::in, __protection ) )
                    this->setstate( std::ios_base::failbit );
            }

#endif

            ~basic_ifstream( )
            {
            }

        public: // File and buffer operations.
            basic_filebuf< _CharT, _Traits >*
            rdbuf( ) const
            {
                return const_cast< _Buf* >( &_M_buf );
            }

            bool
            is_open( )
            {
                return this->rdbuf( )->is_open( );
            }

            void
            open( const char*             __s,
                  std::ios_base::openmode __mod = std::ios_base::in )
            {
                if ( !this->rdbuf( )->open( __s, __mod | std::ios_base::in ) )
                    this->setstate( std::ios_base::failbit );
            }

            void
            close( )
            {
                if ( !this->rdbuf( )->close( ) )
                    this->setstate( std::ios_base::failbit );
            }

            void
            setbuf( char_type* Buffer, off_type N )
            {
                _M_buf.setbuf( Buffer, N );
            }

        private:
            basic_filebuf< _CharT, _Traits > _M_buf;
        };

        //----------------------------------------------------------------------
        /// Class basic_ofstream<>

        template < class _CharT, class _Traits = std::char_traits< _CharT > >
        class basic_ofstream : public std::basic_ostream< _CharT, _Traits >
        {
        public: // Types
            typedef _CharT                     char_type;
            typedef typename _Traits::int_type int_type;
            typedef typename _Traits::pos_type pos_type;
            typedef typename _Traits::off_type off_type;
            typedef _Traits                    traits_type;

            typedef std::basic_ios< _CharT, _Traits >     _Basic_ios;
            typedef std::basic_ostream< _CharT, _Traits > _Base;
            typedef basic_filebuf< _CharT, _Traits >      _Buf;

        public: // Constructors, destructor.
            basic_ofstream( )
                : std::basic_ios< _CharT, _Traits >( ),
                  std::basic_ostream< _CharT, _Traits >( 0 ), _M_buf( )
            {
                this->init( &_M_buf );
            }
            explicit basic_ofstream(
                const char*             __s,
                std::ios_base::openmode __mod = std::ios_base::out )
                : std::basic_ios< _CharT, _Traits >( ),
                  std::basic_ostream< _CharT, _Traits >( 0 ), _M_buf( )
            {
                this->init( &_M_buf );
                if ( !_M_buf.open( __s, __mod | std::ios_base::out ) )
                {
                    this->setstate( std::ios_base::failbit );
                }
            }

#ifndef _STLP_NO_EXTENSIONS
            explicit basic_ofstream(
                int __id, std::ios_base::openmode __mod = std::ios_base::out )
                : basic_ios< _CharT, _Traits >( ),
                  basic_ostream< _CharT, _Traits >( 0 ), _M_buf( )
            {
                this->init( &_M_buf );
                if ( !_M_buf.open( __id, __mod | std::ios_base::out ) )
                    this->setstate( std::ios_base::failbit );
            }
            basic_ofstream( const char*             __s,
                            std::ios_base::openmode __m,
                            long                    __protection )
                : basic_ios< _CharT, _Traits >( ),
                  basic_ostream< _CharT, _Traits >( 0 ), _M_buf( )
            {
                this->init( &_M_buf );
                if ( !_M_buf.open(
                         __s, __m | std::ios_base::out, __protection ) )
                    this->setstate( std::ios_base::failbit );
            }
#endif

            ~basic_ofstream( )
            {
            }

        public: // File and buffer operations.
            basic_filebuf< _CharT, _Traits >*
            rdbuf( ) const
            {
                return const_cast< _Buf* >( &_M_buf );
            }

            bool
            is_open( )
            {
                return this->rdbuf( )->is_open( );
            }

            void
            open( const char*             __s,
                  std::ios_base::openmode __mod = std::ios_base::out )
            {
                if ( !this->rdbuf( )->open( __s, __mod | std::ios_base::out ) )
                    this->setstate( std::ios_base::failbit );
            }

            void
            close( )
            {
                if ( !this->rdbuf( )->close( ) )
                    this->setstate( std::ios_base::failbit );
            }

            void
            setbuf( char_type* Buffer, off_type N )
            {
                _M_buf.setbuf( Buffer, N );
            }

        private:
            basic_filebuf< _CharT, _Traits > _M_buf;
        };

        //----------------------------------------------------------------------
        /// Class basic_fstream<>

        template < class _CharT, class _Traits = std::char_traits< _CharT > >
        class basic_fstream : public std::basic_iostream< _CharT, _Traits >
        {
        public: // Types
            typedef _CharT                     char_type;
            typedef typename _Traits::int_type int_type;
            typedef typename _Traits::pos_type pos_type;
            typedef typename _Traits::off_type off_type;
            typedef _Traits                    traits_type;

            typedef std::basic_ios< _CharT, _Traits >      _Basic_ios;
            typedef std::basic_iostream< _CharT, _Traits > _Base;
            typedef basic_filebuf< _CharT, _Traits >       _Buf;

        public: // Constructors, destructor.
            basic_fstream( )
                : std::basic_ios< _CharT, _Traits >( ),
                  std::basic_iostream< _CharT, _Traits >( 0 ), _M_buf( )
            {
                this->init( &_M_buf );
            }

            explicit basic_fstream( const char*             __s,
                                    std::ios_base::openmode __mod =
                                        std::ios_base::in | std::ios_base::out )
                : std::basic_ios< _CharT, _Traits >( ),
                  std::basic_iostream< _CharT, _Traits >( 0 ), _M_buf( )
            {
                this->init( &_M_buf );
                if ( !_M_buf.open( __s, __mod ) )
                    this->setstate( std::ios_base::failbit );
            }

#ifndef _STLP_NO_EXTENSIONS
            explicit basic_fstream( int                     __id,
                                    std::ios_base::openmode __mod =
                                        std::ios_base::in | std::ios_base::out )
                : basic_ios< _CharT, _Traits >( ),
                  basic_iostream< _CharT, _Traits >( 0 ), _M_buf( )
            {
                this->init( &_M_buf );
                if ( !_M_buf.open( __id, __mod ) )
                    this->setstate( std::ios_base::failbit );
            }
            basic_fstream( const char*             __s,
                           std::ios_base::openmode __m,
                           long                    __protection )
                : basic_ios< _CharT, _Traits >( ),
                  basic_iostream< _CharT, _Traits >( 0 ), _M_buf( )
            {
                this->init( &_M_buf );
                if ( !_M_buf.open( __s, __m, __protection ) )
                    this->setstate( std::ios_base::failbit );
            }
#endif
            ~basic_fstream( )
            {
            }

        public: // File and buffer operations.
            basic_filebuf< _CharT, _Traits >*
            rdbuf( ) const
            {
                return const_cast< _Buf* >( &_M_buf );
            }

            bool
            is_open( )
            {
                return this->rdbuf( )->is_open( );
            }

            void
            open( const char*             __s,
                  std::ios_base::openmode __mod = std::ios_base::in |
                      std::ios_base::out )
            {
                if ( !this->rdbuf( )->open( __s, __mod ) )
                    this->setstate( std::ios_base::failbit );
            }

            void
            close( )
            {
                if ( !this->rdbuf( )->close( ) )
                    this->setstate( std::ios_base::failbit );
            }

            void
            setbuf( char_type* Buffer, off_type N )
            {
                _M_buf.setbuf( Buffer, N );
            }

        private:
            basic_filebuf< _CharT, _Traits > _M_buf;
        };

#define __BF_int_type__ typename basic_filebuf< _CharT, _Traits >::int_type
#define __BF_pos_type__ typename basic_filebuf< _CharT, _Traits >::pos_type
#define __BF_off_type__ typename basic_filebuf< _CharT, _Traits >::off_type

        //----------------------------------------------------------------------
        /// Public basic_filebuf<> member functions

        template < class _CharT, class _Traits >
        basic_filebuf< _CharT, _Traits >::basic_filebuf( )
            : std::basic_streambuf< _CharT, _Traits >( ), _M_base( ),
              _M_constant_width( false ), _M_always_noconv( false ),
              _M_use_memory_mapped_io( true ), _M_int_buf_dynamic( false ),
              _M_in_input_mode( false ), _M_in_output_mode( false ),
              _M_in_error_mode( false ), _M_in_putback_mode( false ),
              _M_int_buf( 0 ), _M_int_buf_EOS( 0 ), _M_ext_buf( 0 ),
              _M_ext_buf_EOS( 0 ), _M_ext_buf_converted( 0 ),
              _M_ext_buf_end( 0 ), _M_state( _State_type( ) ),
              _M_end_state( _State_type( ) ), _M_mmap_base( 0 ),
              _M_mmap_len( 0 ), m_pos( (pos_type)0 ), _M_saved_eback( 0 ),
              _M_saved_gptr( 0 ), _M_saved_egptr( 0 ), _M_codecvt( 0 ),
              _M_width( 1 ), _M_max_width( 1 )
        {
            this->_M_setup_codecvt( std::locale( ) );
        }

        template < class _CharT, class _Traits >
        basic_filebuf< _CharT, _Traits >::~basic_filebuf( )
        {
            this->close( );
            _M_deallocate_buffers( );
        }

        template < class _CharT, class _Traits >
        typename basic_filebuf< _CharT, _Traits >::int_type
        basic_filebuf< _CharT, _Traits >::underflow_core( )
        {
            return _Underflow< _CharT, _Traits >::_M_doit( this );
        }

        template < class _CharT, class _Traits >
        basic_filebuf< _CharT, _Traits >*
        basic_filebuf< _CharT, _Traits >::close( )
        {
            bool __ok = this->is_open( );

            if ( _M_in_output_mode )
            {
                __ok &&
                    ( __ok = !_Traits::eq_int_type(
                          this->overflow( traits_type::eof( ) ),
                          traits_type::eof( ) ) );
                __ok && ( __ok = this->_M_unshift( ) );
            }
            else if ( _M_in_input_mode )
                this->_M_exit_input_mode( );

            /// Note order of arguments.  We close the file even if __ok is
            /// false.
            __ok = _M_base._M_close( ) && __ok;

            /// Restore the initial state, except that we don't deallocate the
            /// buffer or mess with the cached codecvt information.
            _M_state = _M_end_state = _State_type( );
            _M_ext_buf_converted = _M_ext_buf_end = 0;

            _M_mmap_base = 0;
            _M_mmap_len = 0;

            this->setg( 0, 0, 0 );
            this->setp( 0, 0 );

            _M_saved_eback = _M_saved_gptr = _M_saved_egptr = 0;

            _M_in_input_mode = _M_in_output_mode = _M_in_error_mode =
                _M_in_putback_mode = false;

            return __ok ? this : 0;
        }

        /// This member function is called whenever we exit input mode.
        /// It unmaps the memory-mapped file, if any, and sets
        /// _M_in_input_mode to false.
        template < class _CharT, class _Traits >
        void
        basic_filebuf< _CharT, _Traits >::_M_exit_input_mode( )
        {
            if ( _M_mmap_base != 0 )
                _M_base._M_unmap( _M_mmap_base, _M_mmap_len );
            _M_in_input_mode = false;
            _M_mmap_base = 0;
        }

        //----------------------------------------------------------------------
        /// basic_filebuf<> overridden protected virtual member functions

        template < class _CharT, class _Traits >
        std::streamsize
        basic_filebuf< _CharT, _Traits >::showmanyc( )
        {
            /// Is there any possibility that reads can succeed?
            if ( !this->is_open( ) || _M_in_output_mode || _M_in_error_mode )
                return -1;

            else if ( _M_in_putback_mode )
                return this->egptr( ) - this->gptr( );

            else if ( _M_constant_width )
            {
                std::streamoff __pos = _M_base._M_seek( 0, std::ios_base::cur );
                std::streamoff __size = _M_base._M_file_size( );
                return __pos >= 0 && __size > __pos ? __size - __pos : 0;
            }
            return 0;
        }

        /// Make a putback position available, if necessary, by switching to a
        /// special internal buffer used only for putback.  The buffer is
        /// [_M_pback_buf, _M_pback_buf + _S_pback_buf_size), but the base
        /// class only sees a piece of it at a time.  (We want to make sure
        /// that we don't try to read a character that hasn't been initialized.)
        /// The end of the putback buffer is always _M_pback_buf +
        /// _S_pback_buf_size, but the beginning is usually not _M_pback_buf.
        template < class _CharT, class _Traits >
        __BF_int_type__
        basic_filebuf< _CharT, _Traits >::pbackfail( int_type __c )
        {
            const int_type __eof = traits_type::eof( );

            /// If we aren't already in input mode, pushback is impossible.
            if ( !_M_in_input_mode )
                return __eof;

            /// We can use the ordinary get buffer if there's enough space, and
            /// if it's a buffer that we're allowed to write to.
            if ( this->gptr( ) != this->eback( ) &&
                 ( traits_type::eq_int_type( __c, __eof ) ||
                   traits_type::eq( traits_type::to_char_type( __c ),
                                    this->gptr( )[ -1 ] ) ||
                   !_M_mmap_base ) )
            {
                this->gbump( -1 );
                if ( traits_type::eq_int_type( __c, __eof ) ||
                     traits_type::eq( traits_type::to_char_type( __c ),
                                      *this->gptr( ) ) )
                    return traits_type::to_int_type( *this->gptr( ) );
            }
            else if ( !traits_type::eq_int_type( __c, __eof ) )
            {
                /// Are we in the putback buffer already?
                _CharT* __pback_end =
                    _M_pback_buf + static_cast< int >( _S_pback_buf_size );
                if ( _M_in_putback_mode )
                {
                    /// Do we have more room in the putback buffer?
                    if ( this->eback( ) != _M_pback_buf )
                        this->setg( this->egptr( ) - 1,
                                    this->egptr( ) - 1,
                                    __pback_end );
                    else
                        return __eof; // No more room in the buffer, so fail.
                }
                else
                { // We're not yet in the putback buffer.
                    _M_saved_eback = this->eback( );
                    _M_saved_gptr = this->gptr( );
                    _M_saved_egptr = this->egptr( );
                    this->setg( __pback_end - 1, __pback_end - 1, __pback_end );
                    _M_in_putback_mode = true;
                }
            }
            else
                return __eof;

            /// We have made a putback position available.  Assign to it, and
            /// return.
            *this->gptr( ) = traits_type::to_char_type( __c );
            return __c;
        }

        /// This member function flushes the put area, and also outputs the
        /// character __c (unless __c is eof).  Invariant: we always leave room
        /// in the internal buffer for one character more than the base class
        /// knows about.  We see the internal buffer as [_M_int_buf,
        /// _M_int_buf_EOS), but the base class only sees [_M_int_buf,
        /// _M_int_buf_EOS - 1).
        template < class _CharT, class _Traits >
        __BF_int_type__
        basic_filebuf< _CharT, _Traits >::overflow_core( int_type __c )
        {
            /// Switch to output mode, if necessary.
            if ( !_M_in_output_mode )
                if ( !_M_switch_to_output_mode( ) )
                    return traits_type::eof( );

            _CharT* __ibegin = this->_M_int_buf;
            _CharT* __iend = this->pptr( );
            this->setp( _M_int_buf, _M_int_buf_EOS - 1 );

            /// Put __c at the end of the internal buffer.
            if ( !traits_type::eq_int_type( __c, traits_type::eof( ) ) )
                *__iend++ = __c;

            /// For variable-width encodings, output may take more than one
            /// pass.
            while ( __ibegin != __iend )
            {
                const _CharT*             __inext = __ibegin;
                char*                     __enext = _M_ext_buf;
                typename _Codecvt::result __status =
                    _M_codecvt->out( _M_state,
                                     __ibegin,
                                     __iend,
                                     __inext,
                                     _M_ext_buf,
                                     _M_ext_buf_EOS,
                                     __enext );
                if ( __status == _Codecvt::noconv )
                {
                    return _Noconv_output< _Traits >::_M_doit(
                               this, __ibegin, __iend )
                        ? traits_type::not_eof( __c )
                        : _M_output_error( );
                }

                /// For a constant-width encoding we know that the external
                /// buffer is large enough, so failure to consume the entire
                /// internal buffer or to produce the correct number of external
                /// characters, is an error. For a variable-width encoding,
                /// however, we require only that we consume at least one
                /// internal character
                else if ( __status != _Codecvt::error &&
                          ( ( __inext == __iend &&
                              ( __enext - _M_ext_buf ==
                                _M_width * ( __iend - __ibegin ) ) ) ||
                            ( !_M_constant_width && __inext != __ibegin ) ) )
                {
                    /// We successfully converted part or all of the internal
                    /// buffer.
                    std::ptrdiff_t __n = __enext - _M_ext_buf;
                    if ( _M_write( _M_ext_buf, __n ) )
                        __ibegin += __inext - __ibegin;
                    else
                        return _M_output_error( );
                }
                else
                {
                    return _M_output_error( );
                }
            }

            return traits_type::not_eof( __c );
        }

        /// This member function must be called before any I/O has been
        /// performed on the stream, otherwise it has no effect.
        ///
        /// __buf == 0 && __n == 0 means to make ths stream unbuffered.
        /// __buf != 0 && __n > 0 means to use __buf as the stream's internal
        /// buffer, rather than the buffer that would otherwise be allocated
        /// automatically.  __buf must be a pointer to an array of _CharT whose
        /// size is at least __n.
        template < class _CharT, class _Traits >
        std::basic_streambuf< _CharT, _Traits >*
        basic_filebuf< _CharT, _Traits >::setbuf( _CharT*         __buf,
                                                  std::streamsize __n )
        {
            if ( !_M_in_input_mode && !_M_in_output_mode && !_M_in_error_mode &&
                 _M_int_buf == 0 )
            {
                if ( __buf == 0 && __n == 0 )
                    _M_allocate_buffers( 0, 1 );
                else if ( __n > 0 )
                    _M_allocate_buffers( __buf, __n );
            }
            return this;
        }

        template < class _CharT, class _Traits >
        __BF_pos_type__
        basic_filebuf< _CharT, _Traits >::seekoff_core(
            off_type               __off,
            std::ios_base::seekdir __whence,
            std::ios_base::openmode /* dummy */ )
        {
            if ( this->is_open( ) &&
                 ( __off == 0 ||
                   ( _M_constant_width &&
                     this->_M_base._M_in_binary_mode( ) ) ) )
            {

                if ( !_M_seek_init( __off != 0 ||
                                    __whence != std::ios_base::cur ) )
                {
                    return pos_type( -1 );
                }

                /// Seek to beginning or end, regardless of whether we're in
                /// input mode.
                if ( __whence == std::ios_base::beg ||
                     __whence == std::ios_base::end )
                    return _M_seek_return(
                        _M_base._M_seek( _M_width * __off, __whence ),
                        _State_type( ) );

                /// Seek relative to current position.  Complicated if we're in
                /// input mode.
                else if ( __whence == std::ios_base::cur )
                {

                    if ( !_M_in_input_mode )
                        return _M_seek_return(
                            _M_base._M_seek( _M_width * __off, __whence ),
                            _State_type( ) );
                    else if ( _M_mmap_base != 0 )
                    {
                        /// __off is relative to gptr().  We need to do a bit of
                        /// arithmetic to get an offset relative to the external
                        /// file pointer.
                        std::streamoff __adjust = _M_mmap_len -
                            ( this->gptr( ) - (_CharT*)_M_mmap_base );

                        /// if __off == 0, we do not need to exit input mode and
                        /// to shift file pointer
                        if ( __off == 0 )
                        {
                            return pos_type(
                                _M_base._M_seek( 0, std::ios_base::cur ) -
                                __adjust );
                        }
                        else
                            return _M_seek_return(
                                _M_base._M_seek( __off - __adjust,
                                                 std::ios_base::cur ),
                                _State_type( ) );
                    }
                    else if ( _M_constant_width )
                    { // Get or set the position.

                        std::streamoff __iadj =
                            _M_width * ( this->gptr( ) - this->eback( ) );

                        /// Compensate for offset relative to gptr versus offset
                        /// relative to external pointer.  For a text-oriented
                        /// stream, where the compensation is more than just
                        /// pointer arithmetic, we may get but not set the
                        /// current position.

                        if ( __iadj <= _M_ext_buf_end - _M_ext_buf )
                        {

                            std::streamoff __eadj = _M_base._M_get_offset(
                                _M_ext_buf + __iadj, _M_ext_buf_end );

                            if ( __off == 0 )
                            {
                                return pos_type(
                                    _M_base._M_seek( 0, std::ios_base::cur ) -
                                    __eadj );
                            }
                            else
                            {
                                return _M_seek_return(
                                    _M_base._M_seek( __off - __eadj,
                                                     std::ios_base::cur ),
                                    _State_type( ) );
                            }
                        }
                        else
                            return pos_type( -1 );
                    }
                    else
                    { // Get the position.  Encoding is var width.
                        /// Get position in internal buffer.
                        std::ptrdiff_t __ipos = this->gptr( ) - this->eback( );

                        /// Get corresponding position in external buffer.
                        _State_type __state = _M_state;
                        int         __epos = _M_codecvt->length(
                            __state, _M_ext_buf, _M_ext_buf_end, __ipos );

                        /// Sanity check (expensive): make sure __epos is the
                        /// right answer.
                        _State_type                __tmp_state = _M_state;
                        _Filebuf_Tmp_Buf< _CharT > __buf( __ipos );
                        _CharT*                    __ibegin = __buf._M_ptr;
                        _CharT*                    __inext = __ibegin;

                        const char*               __dummy;
                        typename _Codecvt::result __status =
                            _M_codecvt->in( __tmp_state,
                                            _M_ext_buf,
                                            _M_ext_buf + __epos,
                                            __dummy,
                                            __ibegin,
                                            __ibegin + __ipos,
                                            __inext );
                        if ( __status != _Codecvt::error &&
                             ( __status == _Codecvt::noconv ||
                               ( __inext == __ibegin + __ipos &&
                                 equal( this->gptr( ),
                                        this->eback( ),
                                        __ibegin,
                                        _Eq_traits< traits_type >( ) ) ) ) )
                        {
                            /// Get the current position (at the end of the
                            /// external buffer), then adjust it.  Again, it
                            /// might be a text-oriented stream.
                            std::streamoff __cur =
                                _M_base._M_seek( 0, std::ios_base::cur );
                            std::streamoff __adj =
                                _M_base._M_get_offset( _M_ext_buf,
                                                       _M_ext_buf + __epos ) -
                                _M_base._M_get_offset( _M_ext_buf,
                                                       _M_ext_buf_end );
                            if ( __cur != -1 && __cur + __adj >= 0 )
                                return _M_seek_return( __cur + __adj, __state );
                            else
                                return pos_type( -1 );
                        }
                        else // We failed the sanity check.
                            return pos_type( -1 );
                    }
                }
                else // Unrecognized value for __whence.
                    return pos_type( -1 );
            }
            return pos_type( -1 );
        }

        template < class _CharT, class _Traits >
        __BF_pos_type__
        basic_filebuf< _CharT, _Traits >::seekpos_core(
            pos_type __pos, std::ios_base::openmode /* dummy */ )
        {
            if ( this->is_open( ) )
            {
                if ( !_M_seek_init( true ) )
                    return pos_type( -1 );

                std::streamoff __off = off_type( __pos );
                if ( __off != -1 &&
                     _M_base._M_seek( __off, std::ios_base::beg ) != -1 )
                {
                    _M_state = __pos.state( );
                    return _M_seek_return( __off, __pos.state( ) );
                }
                else
                    return pos_type( -1 );
            }
            return pos_type( -1 );
        }

        template < class _CharT, class _Traits >
        int
        basic_filebuf< _CharT, _Traits >::sync( )
        {
            if ( _M_in_output_mode )
                return traits_type::eq_int_type(
                           this->overflow( traits_type::eof( ) ),
                           traits_type::eof( ) )
                    ? -1
                    : 0;
            return 0;
        }

        /// Change the filebuf's locale.  This member function has no effect
        /// unless it is called before any I/O is performed on the stream.
        template < class _CharT, class _Traits >
        void
        basic_filebuf< _CharT, _Traits >::imbue( const std::locale& __loc )
        {
            if ( !_M_in_input_mode && !_M_in_output_mode && !_M_in_error_mode )
            {
                this->_M_setup_codecvt( __loc );
            }
        }

        //----------------------------------------------------------------------
        /// basic_filebuf<> helper functions.

        //----------------------------------------
        /// Helper functions for switching between modes.

        /// This member function is called if we're performing the first I/O
        /// operation on a filebuf, or if we're performing an input operation
        /// immediately after a seek.
        template < class _CharT, class _Traits >
        bool
        basic_filebuf< _CharT, _Traits >::_M_switch_to_input_mode( )
        {

            if ( this->is_open( ) &&
                 ( ( (int)_M_base.__o_mode( ) & (int)std::ios_base::in ) !=
                   0 ) &&
                 ( _M_in_output_mode == 0 ) && ( _M_in_error_mode == 0 ) )
            {
                if ( !_M_int_buf && !_M_allocate_buffers( ) )
                    return false;

                _M_ext_buf_converted = _M_ext_buf;
                _M_ext_buf_end = _M_ext_buf;

                _M_end_state = _M_state;

                _M_in_input_mode = true;
                return true;
            }
            return false;
        }

        /// This member function is called if we're performing the first I/O
        /// operation on a filebuf, or if we're performing an output operation
        /// immediately after a seek.
        template < class _CharT, class _Traits >
        bool
        basic_filebuf< _CharT, _Traits >::_M_switch_to_output_mode( )
        {
            if ( this->is_open( ) &&
                 ( _M_base.__o_mode( ) & (int)std::ios_base::out ) &&
                 _M_in_input_mode == 0 && _M_in_error_mode == 0 )
            {

                if ( !_M_int_buf && !_M_allocate_buffers( ) )
                    return false;

                /// In append mode, every write does an implicit seek to the end
                /// of the file.  Whenever leaving output mode, the end of file
                /// get put in the initial shift state.
                if ( _M_base.__o_mode( ) & std::ios_base::app )
                    _M_state = _State_type( );

                this->setp( _M_int_buf, _M_int_buf_EOS - 1 );
                _M_in_output_mode = true;

                return true;
            }
            return false;
        }

        //----------------------------------------
        /// Helper functions for input

        /// This member function is called if there is an error during input.
        /// It puts the filebuf in error mode, clear the get area buffer, and
        /// returns eof.
        /// returns eof.  Error mode is sticky; it is cleared only by close or
        /// seek.

        template < class _CharT, class _Traits >
        __BF_int_type__
        basic_filebuf< _CharT, _Traits >::_M_input_error( )
        {
            this->_M_exit_input_mode( );
            _M_in_output_mode = false;
            _M_in_error_mode = true;
            this->setg( 0, 0, 0 );
            return traits_type::eof( );
        }

        template < class _CharT, class _Traits >
        __BF_int_type__
        basic_filebuf< _CharT, _Traits >::_M_underflow_aux( )
        {
            /// We have the state and file position from the end of the internal
            /// buffer.  This round, they become the beginning of the internal
            /// buffer.
            _M_state = _M_end_state;

            /// Fill the external buffer.  Start with any leftover characters
            /// that didn't get converted last time.
            if ( _M_ext_buf_end > _M_ext_buf_converted )

                _M_ext_buf_end = std::copy(
                    _M_ext_buf_converted, _M_ext_buf_end, _M_ext_buf );
            /// boris : copy_backward did not work
            ///_M_ext_buf_end = copy_backward(_M_ext_buf_converted,
            ///_M_ext_buf_end, _M_ext_buf+ (_M_ext_buf_end -
            ///_M_ext_buf_converted));
            else
                _M_ext_buf_end = _M_ext_buf;

            /// Now fill the external buffer with characters from the file. This
            /// is a loop because occasonally we don't get enough external
            /// characters to make progress.
            while ( true )
            {
                std::ptrdiff_t __n = _M_base._M_read(
                    _M_ext_buf_end, _M_ext_buf_EOS - _M_ext_buf_end );

                /// Don't enter error mode for a failed read.  Error mode is
                /// sticky, and we might succeed if we try again.
                if ( __n <= 0 )
                    return traits_type::eof( );

                /// Convert the external buffer to internal characters.
                _M_ext_buf_end += __n;
                const char* __enext;
                _CharT*     __inext;

                typename _Codecvt::result __status =
                    _M_codecvt->in( _M_end_state,
                                    _M_ext_buf,
                                    _M_ext_buf_end,
                                    __enext,
                                    _M_int_buf,
                                    _M_int_buf_EOS,
                                    __inext );

                /// Error conditions: (1) Return value of error.  (2) Producing
                /// internal characters without consuming external characters.
                /// (3) In fixed-width encodings, producing an internal sequence
                /// whose length is inconsistent with that of the internal
                /// sequence.  (4) Failure to produce any characters if we have
                /// enough characters in the external buffer, where "enough"
                /// means the largest possible width of a single character.
                if ( __status == _Codecvt::noconv )
                    return _Noconv_input< _Traits >::_M_doit( this );

                else if ( __status == _Codecvt::error ||
                          ( __inext != _M_int_buf && __enext == _M_ext_buf ) ||
                          ( _M_constant_width &&
                            ///         __inext - _M_int_buf != _M_width *
                            ///         (__enext - _M_ext_buf)) ||
                            ( __inext - _M_int_buf ) * _M_width !=
                                ( __enext - _M_ext_buf ) ) ||
                          ( __inext == _M_int_buf &&
                            __enext - _M_ext_buf >= _M_max_width ) )
                    return _M_input_error( );

                else if ( __inext != _M_int_buf )
                {
                    _M_ext_buf_converted =
                        _M_ext_buf + ( __enext - _M_ext_buf );
                    this->setg( _M_int_buf, _M_int_buf, __inext );
                    return traits_type::to_int_type( *_M_int_buf );
                }
                /// We need to go around the loop again to get more external
                /// characters.
            }
        }

        //----------------------------------------
        /// Helper functions for output

        /// This member function is called if there is an error during output.
        /// It puts the filebuf in error mode, clear the put area buffer, and
        /// returns eof.  Error mode is sticky; it is cleared only by close or
        /// seek.
        template < class _CharT, class _Traits >
        __BF_int_type__
        basic_filebuf< _CharT, _Traits >::_M_output_error( )
        {
            _M_in_output_mode = false;
            _M_in_input_mode = false;
            _M_in_error_mode = true;
            this->setp( 0, 0 );
            return traits_type::eof( );
        }

        /// Write whatever sequence of characters is necessary to get back to
        /// the initial shift state.  This function overwrites the external
        /// buffer, changes the external file position, and changes the state.
        /// Precondition: the internal buffer is empty.
        template < class _CharT, class _Traits >
        bool
        basic_filebuf< _CharT, _Traits >::_M_unshift( )
        {
            if ( _M_in_output_mode && !_M_constant_width )
            {
                typename _Codecvt::result __status;
                do
                {
                    char* __enext = _M_ext_buf;
                    __status = _M_codecvt->unshift(
                        _M_state, _M_ext_buf, _M_ext_buf_EOS, __enext );
                    if ( __status == _Codecvt::noconv ||
                         ( __enext == _M_ext_buf && __status == _Codecvt::ok ) )
                        return true;
                    else if ( __status == _Codecvt::error )
                        return false;
                    else if ( !_M_write( _M_ext_buf, __enext - _M_ext_buf ) )
                        return false;
                } while ( __status == _Codecvt::partial );
            }

            return true;
        }

        //----------------------------------------
        /// Helper functions for buffer allocation and deallocation

        /// This member function is called when we're initializing a filebuf's
        /// internal and external buffers.  The argument is the size of the
        /// internal buffer; the external buffer is sized using the character
        /// width in the current encoding.  Preconditions: the buffers are
        /// currently null.  __n >= 1.  __buf is either a null pointer or a
        /// pointer to an array show size is at least __n.

        /// We need __n >= 1 for two different reasons.  For input, the base
        /// class always needs a buffer because of the sementics of underflow().
        /// For output, we want to have an internal buffer that's larger by one
        /// element than the buffer that the base class knows about.  (See
        /// basic_filebuf<>::overflow() for the reason.)
        template < class _CharT, class _Traits >
        bool
        basic_filebuf< _CharT, _Traits >::_M_allocate_buffers(
            _CharT* __buf, std::streamsize __n )
        {

            if ( __buf == 0 )
            {
                _M_int_buf =
                    static_cast< _CharT* >( malloc( __n * sizeof( _CharT ) ) );
                if ( !_M_int_buf )
                    return false;
                _M_int_buf_dynamic = true;
            }
            else
            {
                _M_int_buf = __buf;
                _M_int_buf_dynamic = false;
            }

            size_t __ebufsiz =
                ( std::max )( __n * ( std::max )( _M_codecvt->encoding( ), 1 ),
                              std::streamsize( _M_codecvt->max_length( ) ) );

            _M_ext_buf = static_cast< char* >( malloc( __ebufsiz ) );
            if ( !_M_ext_buf )
            {
                _M_deallocate_buffers( );
                return false;
            }

            _M_int_buf_EOS = _M_int_buf + __n;
            _M_ext_buf_EOS = _M_ext_buf + __ebufsiz;
            return true;
        }

        /// Abbreviation for the most common case.
        template < class _CharT, class _Traits >
        bool
        basic_filebuf< _CharT, _Traits >::_M_allocate_buffers( )
        {
            /// Choose a buffer that's at least 4096 characters long and that's
            /// a multiple of the page size.
            std::streamsize __default_bufsiz =
                ( ( _M_base.__page_size( ) + 4095UL ) /
                  _M_base.__page_size( ) ) *
                _M_base.__page_size( );
            return _M_allocate_buffers( 0, __default_bufsiz );
        }

        template < class _CharT, class _Traits >
        void
        basic_filebuf< _CharT, _Traits >::_M_deallocate_buffers( )
        {
            if ( _M_int_buf_dynamic )
                free( _M_int_buf );
            free( _M_ext_buf );
            _M_int_buf = 0;
            _M_int_buf_EOS = 0;
            _M_ext_buf = 0;
            _M_ext_buf_EOS = 0;
        }

        //----------------------------------------
        /// Helper functiosn for seek and imbue

        template < class _CharT, class _Traits >
        bool
        basic_filebuf< _CharT, _Traits >::_M_seek_init( bool __do_unshift )
        {
            /// If we're in error mode, leave it.
            _M_in_error_mode = false;

            /// Flush the output buffer if we're in output mode, and
            /// (conditionally) emit an unshift sequence.
            if ( _M_in_output_mode )
            {
                bool __ok = !traits_type::eq_int_type(
                    this->overflow( traits_type::eof( ) ),
                    traits_type::eof( ) );
                if ( __do_unshift )
                    __ok = __ok && this->_M_unshift( );
                if ( !__ok )
                {
                    _M_in_output_mode = false;
                    _M_in_error_mode = true;
                    this->setp( 0, 0 );
                    return false;
                }
            }

            /// Discard putback characters, if any.
            if ( _M_in_input_mode && _M_in_putback_mode )
                _M_exit_putback_mode( );

            return true;
        }

        /// Change the filebuf's locale.  This member function has no effect
        /// unless it is called before any I/O is performed on the stream.
        template < class _CharT, class _Traits >
        void
        basic_filebuf< _CharT, _Traits >::_M_setup_codecvt(
            const std::locale& __loc )
        {
            _M_codecvt = &std::use_facet< _Codecvt >( __loc );
            int __encoding = _M_codecvt->encoding( );

            _M_width = ( std::max )( __encoding, 1 );
            _M_max_width = _M_codecvt->max_length( );
            _M_constant_width = __encoding > 0;
            _M_always_noconv = _M_codecvt->always_noconv( );
        }

#undef __BF_int_type__
#undef __BF_pos_type__
#undef __BF_off_type__

        typedef basic_filebuf< char > filebuf;

        typedef basic_fstream< char >  fstream;
        typedef basic_ifstream< char > ifstream;
        typedef basic_ofstream< char > ofstream;

        template < typename CharT, typename Traits >
        typename basic_filebuf< CharT, Traits >::pos_type
        basic_filebuf< CharT, Traits >::seekoff( off_type                Off,
                                                 std::ios_base::seekdir  Way,
                                                 std::ios_base::openmode Mode )
        {
            if ( !( ( Off == 0 ) && ( Way == std::ios_base::cur ) ) )
            {
                m_pos = this->seekoff_core( Off, Way, Mode );
                if ( Mode & std::ios_base::in )
                {
                    m_pos -= ( pos_type )( this->gptr( ) - this->eback( ) );
                }
                else
                {
                    m_pos -= ( pos_type )( this->pptr( ) - this->pbase( ) );
                }
            }
            return current_pos( Mode );
        }

        template < typename CharT, typename Traits >
        typename basic_filebuf< CharT, Traits >::pos_type
        basic_filebuf< CharT, Traits >::seekpos( pos_type                Pos,
                                                 std::ios_base::openmode Mode )
        {
            m_pos = this->seekpos_core( Pos, Mode );
            if ( Mode & std::ios_base::in )
            {
                m_pos -= ( pos_type )( this->gptr( ) - this->eback( ) );
            }
            else
            {
                m_pos -= ( pos_type )( this->pptr( ) - this->pbase( ) );
            }
            return current_pos( Mode );
        }

        template < typename CharT, typename Traits >
        typename basic_filebuf< CharT, Traits >::pos_type
        basic_filebuf< CharT, Traits >::current_pos(
            std::ios_base::openmode Mode )
        {
            if ( m_pos == (pos_type)-1 )
            {
                return m_pos;
            }
            pos_type retval = m_pos;

            if ( Mode & std::ios_base::in )
            {
                retval += ( pos_type )( this->gptr( ) - this->eback( ) );
            }
            else
            {
                retval += ( pos_type )( this->pptr( ) - this->pbase( ) );
            }
            return retval;
        }

        template < typename CharT, typename Traits >
        typename basic_filebuf< CharT, Traits >::int_type
        basic_filebuf< CharT, Traits >::underflow( )
        {
            pos_type bufsize = ( pos_type )( this->gptr( ) - this->eback( ) );
            int_type retval = this->underflow_core( );

            if ( Traits::eof( ) == retval )
            {
                m_pos = -1;
            }
            else
            {
                m_pos += bufsize;
                m_pos -= ( pos_type )( this->gptr( ) - this->eback( ) );
            }
            return retval;
        }

        template < typename CharT, typename Traits >
        typename basic_filebuf< CharT, Traits >::int_type
        basic_filebuf< CharT, Traits >::overflow( int_type C )
        {
            pos_type bufsize = ( pos_type )( this->pptr( ) - this->pbase( ) );

            int_type retval = this->overflow_core( C );

            if ( retval != Traits::eof( ) )
            {
                m_pos += bufsize;
                if ( C != Traits::eof( ) )
                {
                    m_pos += (pos_type)1;
                }
            }
            return retval;
        }
    } // namespace AL
} // namespace LDASTools
//// \endcond EXCLUDE

#endif /* GENERAL__FSTREAM_HH */
