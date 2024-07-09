#ifndef FRAMECPP__COMMON__FrameSpec_HH
#define FRAMECPP__COMMON__FrameSpec_HH

#if defined( __cplusplus )
#if !defined( SWIGIMPORTED )
#include <iostream>
#include <memory>
#include <sstream>
#include <stdexcept>

#include <boost/pointer_cast.hpp>
#include <boost/shared_ptr.hpp>
#endif /* ! defined(SWIGIMPORTED) */

#if !defined( SWIGIMPORTED )
#include "ldastoolsal/gpstime.hh"
#include "ldastoolsal/unordered_map.hh"
#include "ldastoolsal/types.hh"
#endif /* ! defined(SWIGIMPORTED) */

/**
 *  \brief Minimal version of frame specification which is supported.
 *
 *  This define can be used to test the minimal frame specification
 *  that is supported by the library.
 */
#define FRAME_SPEC_MIN 3
/**
 * \brief Default version of frame specification which is supported.
 *
 * This define can be used to test the default frame specification
 * that is supported by the library.
 */
#define FRAME_SPEC_CURRENT 8
/**
 * \brief Maximum version of frame specification which is supported.
 *
 * This define can be used to test the maximum frame specification
 * that is supported by the library.
 */
#define FRAME_SPEC_MAX 8

/**
 * \brief Version number as an ascii string
 */
/* clang-format off */
#define FRAMECPP_VERSION "2.9.3"
/* clang-format on */
/**
 * \brief Version number as a numeric value
 *
 * This is a numeric representation of the package version
 * of the form: [M]Mmmppp
 * where:
 *   - M = Major digit</li>
 *   - m = minor digit</li>
 *   - p = patch digit</li>
 *
 */
/* clang-format off */
#define FRAMECPP_VERSION_NUMBER \
  ( (2 * 100 * 1000)       \
    + (9 * 1000)             \
    + (3) )
/* clang-format on */
/**
 * \brief Date of the build
 *
 * This string contains the date when the library was built.
 * A common use of this information is in FrHistory records.
 */
#define FRAMECPP_BUILD_DATE "2024-04-08T08:23:28"

#if !defined( SWIG )
namespace FrameCPP
{
    /**
     * \brief Routines upon which the version specific layers are built
     */
    namespace Common
    {
        class StreamBase;
        class IStream;
        class OStream;
    } /* namespace Common */

    typedef Common::StreamBase stream_base_type;
    typedef Common::IStream    istream_type;
    typedef Common::OStream    ostream_type;
    typedef INT_8U             streamsize_type;

    namespace Common
    {
        /**
         * \cond ignore
         */
        class IFrameStream;
        class Description;
        class StreamBase;
        class Verify;
        /**
         * \endcond ignore
         */

        /**
         * \brief Description of frame specification information.
         * The information contained here allows for information needed to
         * describe a specific frame specification implementation.
         */
        class FrameSpec
        {
        public:
            /**
             * \brief Version of the frame specification being described.
             */
            typedef INT_2U version_type;
            /*-----------------------------------------------------------------
              -----------------------------------------------------------------*/
            typedef INT_2S class_type;
            /*-----------------------------------------------------------------
              -----------------------------------------------------------------*/
            typedef INT_8U size_type;
            /*-----------------------------------------------------------------
              -----------------------------------------------------------------*/
            typedef INT_4U instance_type;

            static const CHAR_U MINOR_VERSION_BETA = 255;

            /* -----------------------------------------------------------------
               Forward declaration.
               -----------------------------------------------------------------
             */
            class Object;

            /**
             * \brief Interface to Objects
             *
             * This interface should be the base of all frame objects.
             * It allows for generic handling of frame objects.
             */
            class ObjectInterface
            {
            public:
                typedef FrameSpec::version_type frame_spec_version_type;

                typedef boost::shared_ptr< Object > object_type;
                typedef std::unique_ptr< Object >   unique_object_type;
                typedef object_type                 demote_arg_type;
                typedef object_type                 demote_ret_type;
                typedef object_type                 promote_arg_type;
                typedef object_type                 promote_ret_type;

                /**
                 * \brief Destructor
                 */
                virtual ~ObjectInterface( );

                /**
                 * \brief Return the number of bytes for this object
                 *
                 * \param[in] Stream
                 *     The stream on which the object will be written or read.
                 *
                 * \return
                 *     The number of bytes required by this object for
                 *     the specified stream.
                 */
                virtual streamsize_type
                Bytes( const StreamBase& Stream ) const = 0;

                /**
                 * \brief constructor - virtual
                 */
                virtual Object* Create( ) const;

                /**
                 * \brief constructor - virtual
                 */
                virtual Object* Create( istream_type& Stream ) const = 0;

                /**
                 * \brief constructor - virtual
                 */
                virtual Object* Create( std::istream& Buffer ) const;

                /**
                 * \brief comparison operator
                 */
                virtual bool operator==( const Object& Obj ) const = 0;

                /**
                 * \brief constructor - virtual copy constructor
                 */
                virtual Object* Clone( ) const;

                /**
                 * \brief Down grade an object
                 *
                 * \param[in] Target
                 *      This is the version of the frame specification of
                 *      the demoted object.
                 * \param[in] Obj
                 *      The base object.
                 * \param[in] Stream
                 *      Stream from which Obj was created.
                 *
                 * \return
                 *      A pointer to the objected derived by demoting Obj.
                 */
                static object_type DemoteObject( frame_spec_version_type Target,
                                                 object_type             Obj,
                                                 istream_type* Stream );

                /**
                 * \brief Get FrSH/FrSE description of object
                 */
                virtual const Description* GetDescription( ) const = 0;

                /**
                 * \brief Retrieve the class name of the object
                 *
                 * \return
                 *     The name of the class associated with the object.
                 */
                virtual const char* ObjectStructName( ) const = 0;

                /**
                 * \brief Upgrade an object
                 *
                 * \param[in] Target
                 *     Promote Obj to this version of the frame specification.
                 * \param[in] Source
                 *     Obj conforms to this version of the frame specification.
                 * \param[in] Obj
                 *     Object to be converted
                 * \param[in] Stream
                 *     Originating stream for Obj.
                 *
                 * \return
                 *     A pointer to the objected derived by promoting Obj.
                 */
                static object_type
                PromoteObject( frame_spec_version_type Target,
                               frame_spec_version_type Source,
                               object_type             Obj,
                               istream_type*           Stream );

                /**
                 * \brief Upgrade an object
                 *
                 * \param[in] Target
                 *     Promote Obj to this version of the frame specification.
                 * \param[in] Source
                 *     Obj conforms to this version of the frame specification.
                 * \param[in] Obj
                 *     Object to be converted
                 * \param[in] Stream
                 *     Originating stream for Obj.
                 *
                 * \return
                 *     A pointer to the objected derived by promoting Obj.
                 */
                template < typename PreviousType, typename CurrentType >
                static object_type
                PromoteObject( frame_spec_version_type Target,
                               frame_spec_version_type Source,
                               object_type             Obj,
                               istream_type*           Stream );

                /**
                 * \brief Verify an object.
                 *
                 * \param[in,out] Verifier
                 *     Set of rules to use in verification of the object.
                 *     If an error occurs, the violation is logged here.
                 * \param[in] Stream
                 *     The stream that is being used to read the object.
                 */
                virtual void VerifyObject( Verify&       Verifier,
                                           IFrameStream& Stream ) const;

                /**
                 * \brief Write object to the stream
                 *
                 * \param[in,out] Stream
                 *     The stream being written with the contents of object.
                 */
                virtual void Write( ostream_type& Stream ) const = 0;

            protected:
                /**
                 * \brief Demotes object to previous version of the frame spec
                 *
                 * \param[in] Target
                 *     The version of the frame specification to demote too.
                 * \param[in] Obj
                 *     The version of the object to demote.
                 * \param[in] Stream
                 *     The input stream from which the original object was
                 *     read.
                 *
                 * \return
                 *     An object of the previous generation.
                 */
                virtual demote_ret_type
                demote( frame_spec_version_type Target,
                        demote_arg_type         Obj,
                        istream_type*           Stream ) const = 0;

                /**
                 * \brief Promotes object to another version of the frame spec
                 *
                 * \param[in] Target
                 *     The version of the promoted frame specification.
                 * \param[in] Obj
                 *     The object to be promoted.
                 * \param[in] Stream
                 *     The input stream from which the original object was
                 *     read.
                 *
                 * \return
                 *     An object promoted to the next generation.
                 */
                virtual promote_ret_type
                promote( frame_spec_version_type Target,
                         promote_arg_type        Obj,
                         istream_type*           Stream ) const = 0;

                /**
                 * \brief Retrieve the class name associated with the object
                 */
                virtual class_type getClass( ) const = 0;
            };

            /**
             * \brief Base for all frame objects
             *
             * This is the base class for all frame objects that need to be
             * written to or read from a frame stream.
             */
            class Object : public ObjectInterface
            {
            public:
                /**
                 * \brief constructor
                 *
                 * \param[in] Class
                 *     A unique identifier that identifies the class of object.
                 *
                 * \param[in] Description
                 *     Description of the class
                 */
                Object( class_type Class, const Description* Description );

                /**
                 * \brief copy constructor
                 *
                 * \param[in] Source
                 *     Object to duplicate
                 */
                Object( const Object& Source );

                /**
                 * \brief destructor
                 */
                virtual ~Object( );

                /**
                 * \brief Retrieve the class identifier
                 *
                 * \return
                 *      The class identifier.
                 */
                class_type GetClass( ) const;

                /**
                 * \brief Retrieve FrSH/FrSE description of the parent object
                 *
                 * \return
                 *     The description of the parent class.
                 */
                const Description* GetDescription( ) const;

                /**
                 * \brief Assignement operator
                 *
                 * \param[in] Source
                 *     The instance to replicate.
                 *
                 * \return
                 *     The modified object.
                 */
                const Object& operator=( const Object& Source );

                /**
                 * \brief Write a next pointer to the parent to the stream
                 *
                 * \param[in,out] Stream
                 *     The output stream to receive the next pointer.
                 *
                 * \return
                 *     The output stream.
                 */
                ostream_type& WriteNext( ostream_type& Stream ) const;

            protected:
                /**
                 * \brief Retrieve the class identifier.
                 */
                virtual class_type getClass( ) const;

            private:
                /**
                 * \brief Storage for the class identifier.
                 *
                 * The class identifier uniquely identifies the parent
                 * class within the frame specification.
                 * All instances of parent class will have the same
                 * class identifier.
                 */
                const class_type m_class;
                /**
                 * \brief Description for parent class
                 *
                 * The description for the parent class composed of one
                 * FrSH and one or more FrSE elements.
                 */
                const Description* const m_desc;
            };

            /**
             * \brief Support checksumed objects.
             *
             * \tparam ObjectType
             *      Frame object type
             * \tparam ChecksumType
             *     Object used for checksum calculation
             */
            template < typename ObjectType, typename ChecksumType >
            class ObjectWithChecksum : public ObjectType
            {
            public:
#if 0
                static_assert( !std::is_same< ObjectType, FrDetector >::value,
                               "FrameCPP::Common::FrDetector is not allowed as "
                               "a template parameter" );
#endif /* 0 */
                typedef ObjectWithChecksum< ObjectType, ChecksumType >
                    self_type;

                typedef IStream istream_type;
                typedef OStream ostream_type;

                /**
                 * \brief Constructor - Default
                 */
                ObjectWithChecksum( );

                /**
                 * \brief Constructor
                 */
                ObjectWithChecksum( const Description* Description );

                /**
                 * \brief Constructor
                 */
                ObjectWithChecksum( class_type         Class,
                                    const Description* Description );

                /**
                 * \brief copy constructor
                 */
                ObjectWithChecksum( const ObjectWithChecksum& Source );

                /**
                 * \brief Constructor - Stream
                 */
                ObjectWithChecksum( istream_type& Source );

                /**
                 * \brief destructor
                 */
                virtual ~ObjectWithChecksum( );

                /**
                 * \brief Return the number of bytes for this object
                 *
                 * \param[in] Stream
                 *     Stream characteristics used to determine the number
                 *     of bytes needed to format the object for the
                 *     Stream.
                 *
                 * \return
                 *     The number of bytes for this object
                 */
                virtual streamsize_type Bytes( const StreamBase& Stream ) const;

                /**
                 * \brief Data class to be used in class field of FrSE
                 */
                static const char* CheckSumDataClass( );

                /**
                 * \brief Comment to be used in comment field of FrSE
                 */
                static const char* CheckSumDataComment( );

                /**
                 * \brief Virtual constructor
                 *
                 * \param[in] Stream
                 *     The input stream from where the object is being read.
                 *
                 * \return
                 *     Return pointer to the newly allocated resource.
                 */
                virtual self_type* Create( istream_type& Stream ) const;

                /**
                 * \brief Write object to the stream
                 */
                virtual void Write( ostream_type& Stream ) const;

            protected:
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
                virtual streamsize_type
                pBytes( const StreamBase& Stream ) const = 0;

                /**
                 * \brief Virtual constructor
                 *
                 * \param[in] Stream
                 *     The input stream from where the object is being read.
                 *
                 * \return
                 *     The newly allocated object.
                 */
                virtual self_type* pCreate( istream_type& Stream ) const = 0;

                /**
                 * \brief Write the structure to the stream
                 *
                 * \param[in] Stream
                 *     The output stream where the object is to be written.
                 */
                virtual void pWrite( ostream_type& Stream ) const = 0;

            private:
                virtual Object*
                Create( ) const
                {
                    return ObjectType::Create( );
                }

                /**
                 * \brief constructor - virtual
                 */
                virtual Object*
                Create( std::istream& Buffer ) const
                {
                    return ObjectType::Create( Buffer );
                }

                /**
                 * \brief Structure checksum
                 *
                 * The checksum for the structure when the structure is
                 * contained in a stream.
                 */
                ChecksumType m_chkSum;
            };

            class Info
            {
            public:
                typedef Verify                      verify_type;
                typedef boost::shared_ptr< Object > object_type;

                enum frame_object_types
                {
                    FSI_PTR_STRUCT = -3,
                    FSI_COMMON_ELEMENTS = -2,
                    FSI_FR_HEADER = -1,
                    FSI_FR_NULL = 0,
                    FSI_FR_SH = 1,
                    FSI_FR_SE = 2,
                    FSI_FRAME_H,
                    FSI_FR_ADC_DATA,
                    FSI_FR_DETECTOR,
                    FSI_FR_END_OF_FILE,
                    FSI_FR_END_OF_FRAME,
                    FSI_FR_EVENT,
                    FSI_FR_HISTORY,
                    FSI_FR_MSG,
                    FSI_FR_PROC_DATA,
                    FSI_FR_RAW_DATA,
                    FSI_FR_SER_DATA,
                    FSI_FR_SIM_DATA,
                    FSI_FR_SIM_EVENT,
                    FSI_FR_STAT_DATA,
                    FSI_FR_SUMMARY,
                    FSI_FR_TABLE,
                    FSI_FR_TOC,
                    FSI_FR_VECT,
                    /*-------------------------------------------------------------
                     * Backwards compatability
                     -------------------------------------------------------------*/
                    FSI_FR_TRIG_DATA = FSI_FR_EVENT
                };

                typedef void ( *verification_func_type )(
                    const FrameSpec::Object*,
                    verify_type&,
                    IFrameStream& Stream );
                Info( version_type           MajorVersion,
                      version_type           MinorVersion,
                      verification_func_type VerificationFunc =
                          (verification_func_type)NULL );

                ~Info( );

                inline verification_func_type
                VerificationFunc( ) const
                {
                    return m_verification_func;
                }

                inline version_type
                Version( ) const
                {
                    return m_version;
                }

                inline version_type
                VersionMinor( ) const
                {
                    return m_version_minor;
                }

                const Object* FrameObject( frame_object_types ObjectId ) const;

                void FrameObject( object_type ObjectTemplate );

                void FrameObject( object_type::element_type* ObjectTemplate );

            private:
                typedef LDASTools::AL::unordered_map< version_type,
                                                      object_type >
                    object_container;

                object_container       m_definitions;
                version_type           m_version;
                version_type           m_version_minor;
                verification_func_type m_verification_func;
            };

            static Info* SpecInfo( version_type Version );

            static void SpecInfo( version_type Version, Info* Info );

            /**
             * \brief Constructor
             */
            FrameSpec( );

        private:
            class frame_spec_container;

            static frame_spec_container& frame_specs( );

            static void cleanup_frame_specs( );
        }; /* class - FrameSpec */

        inline void
        FrameSpec::Info::FrameObject(
            object_type::element_type* ObjectTemplate )
        {
            object_type obj( ObjectTemplate );

            FrameObject( obj );
        }

        /*===================================================================
          ===================================================================*/
        /*-------------------------------------------------------------------
          -------------------------------------------------------------------*/
        inline FrameSpec::class_type
        FrameSpec::Object::GetClass( ) const
        {
            return m_class;
        }

        /*-------------------------------------------------------------------
          -------------------------------------------------------------------*/
        inline const Description*
        FrameSpec::Object::GetDescription( ) const
        {
            return m_desc;
        }

        /**
         * \brief Assignment operator
         */
        inline const FrameSpec::Object&
        FrameSpec::Object::operator=( const Object& Source )
        {
            if ( Source.m_class != m_class )
            {
                throw std::domain_error(
                    "incompatable assignment of FrameSpec::Object" );
            }
            return *this;
        }

        /*-------------------------------------------------------------------
          -------------------------------------------------------------------*/
        template < typename PreviousType, typename CurrentType >
        FrameSpec::ObjectInterface::promote_ret_type
        FrameSpec::ObjectInterface::PromoteObject(
            FrameSpec::ObjectInterface::frame_spec_version_type Target,
            FrameSpec::ObjectInterface::frame_spec_version_type Source,
            FrameSpec::ObjectInterface::promote_arg_type        Obj,
            IStream*                                            Stream )
        {
            if ( Source >= Target )
            {
                /*---------------------------------------------------------------
                  Nothing to do here
                  ---------------------------------------------------------------*/
                return Obj;
            }
            /*-----------------------------------------------------------------
             Promote from the previous level
             -----------------------------------------------------------------*/
            object_type retval;

            object_type previous_object(
                PreviousType::Promote( Source, Obj, Stream ) );
            if ( previous_object )
            {
                /*--------------------------------------------------------------
                   Object is not NULL, need to upconvert
                   --------------------------------------------------------------*/
                boost::shared_ptr< PreviousType > previous =
                    boost::static_pointer_cast< PreviousType >(
                        previous_object );

                retval.reset( new CurrentType( *previous, Stream ) );
            }

            return retval;
        }

        /*===================================================================
         * Templeted functions
         ===================================================================*/
        /**
         * \brief Return the number of bytes for given type
         *
         * \tparam T
         *     Specific type for which to retrieve the number of
         *     bytes.
         *
         * \param[in] Data
         *     The data to be read or written to a stream.
         *
         * \return
         *     The number of bytes needed to read or write Data
         *     from or to a stream.
         */
        template < typename T >
        streamsize_type Bytes( const T& Data );

        /**
         * \brief Verify an object
         *
         * \param[in] Obj
         *     Object to be verified.
         *
         * \param[in,out] Verifier
         *     Storage space to record state of object verification.
         *
         * \param[in] Stream
         *     Stream from which Obj was read.
         */
        template < typename T >
        void VerifyObject( const T&                      Obj,
                           FrameSpec::Info::verify_type& Verifier,
                           IFrameStream&                 Stream );

        /*-------------------------------------------------------------------
          -------------------------------------------------------------------*/
        inline FrameSpec::ObjectInterface::promote_ret_type
        PromoteObject(
            FrameSpec::ObjectInterface::frame_spec_version_type Target,
            FrameSpec::ObjectInterface::frame_spec_version_type Source,
            FrameSpec::ObjectInterface::promote_arg_type        Obj )
        {
            FrameSpec::ObjectInterface::promote_ret_type retval;

            if ( Source >= Target )
            {
                retval = Obj;
            }
            return retval;
        }

    } /* namespace Common */

    typedef CHAR_U version_type;

    typedef Common::FrameSpec::size_type cmn_streamsize_type;

    typedef LDASTools::AL::GPSTime start_time_normalized_type;

    typedef REAL_8 delta_t_normalized_type;

    typedef Common::FrameSpec::Object Object;

    /**
     * \brief LdasException error codes for libframecpp.
     */
    enum CODE
    {
        BAD_FRAME_FILE
    };

    /**
     * \brief enumerated type describing the byte ordering
     */
    enum byte_order_type
    {
        BYTE_ORDER_BIG_ENDIAN,
        BYTE_ORDER_LITTLE_ENDIAN,
    /* clang-format off */
#if 0 /* WORDS_BIGENDIAN */
        /* clang-format on */
        BYTE_ORDER_HOST = BYTE_ORDER_BIG_ENDIAN
#else /* WORDS_BIGENDIAN */
        BYTE_ORDER_HOST = BYTE_ORDER_LITTLE_ENDIAN
#endif /* WORDS_BIGENDIAN */

    };

    /**
     * \brief Unimplemeted exception
     *
     * The Unimplemented exception is thrown when some part of the frame
     * specification was not implemented.
     */
    class Unimplemented : public std::exception
    {
    public:
        /**
         * \brief Constructed
         *
         * \param[in] Call
         *     The name of the method or function where the
         *     exception was thrown.
         *
         * \param[in] Line
         *     The line number within Filename where the exception
         *     was thrown.
         *
         * \param[in] Filename
         *     The name of the file where the exception was thrown.
         *
         * \param[in] FrameSpecVersion
         *     The version of the frame specification causing the exception.
         *
         */
        inline Unimplemented( const std::string& Call,
                              CHAR_U             FrameSpecVersion,
                              const char*        Filename,
                              int                Line )
        {
            std::ostringstream m;

            m << "The call \"" << Call << "\""
              << " at line " << Line << " of file " << Filename
              << " is currently not implemented for version "
              << INT_2U( FrameSpecVersion ) << " of the frame specification.";
            msg = m.str( );
        }

        /**
         * \brief Destructor
         *
         * Release resources back to the system.
         */
        inline virtual ~Unimplemented( ) throw( )
        {
        }

        /**
         * \brief Return the generic description of the exception.
         *
         * Returns a null terminated character sequence containing a
         * generic description of the exception.
         *
         * \return
         *     The generic description of the exception.
         */
        inline virtual const char*
        what( ) const throw( )
        {
            return msg.c_str( );
        }

    private:
        /**
         * \brief Storage for the exception message.
         *
         * Storage for the generic description of the message.
         */
        std::string msg;
    };

    /**
     * \brief Compare two frame objects
     *
     * \param[in] LHS
     *     The left hand side of the comparison.
     * \param[in] Obj
     *     The right hand side of the comparison.
     *
     * \return
     *     The value true is returned if the two objects are equivelent;
     *     false otherwise.
     */
    template < typename T >
    inline bool
    compare( const T& LHS, const Common::FrameSpec::Object& Obj )
    {
        bool retval = ( &LHS == &Obj );

        if ( retval == false )
        {
            const T* rhs;
            if ( ( LHS.GetClass( ) == Obj.GetClass( ) ) &&
                 ( ( rhs = dynamic_cast< const T* >( &Obj ) ) ) )
            {
                retval = ( LHS == *rhs );
            }
        }
        return retval;
    }

    /*---------------------------------------------------------------------
      ---------------------------------------------------------------------*/
    template < typename T >
    inline bool
    IsOfType( Common::FrameSpec::Object* Obj )
    {
        if ( dynamic_cast< T* >( Obj ) == (T*)NULL )
        {
            return false;
        }
        return true;
    }

    /**
     * \brief The earliest supported frame specification
     *
     * This is the earliest feature complete implementation of the
     * frame specification.
     */
    const version_type FrameSpecMinimum( FRAME_SPEC_MIN );

    /**
     * \brief Currentently supported frame specification
     *
     * This is the latest version of the frame specification that is
     * fully supported.
     * By default, this version of the frame specification will be
     * used to create memory objects.
     * Also, output data streams will be generated according to this
     * version of the frame specification.
     */
    const version_type FrameSpecCurrent( FRAME_SPEC_CURRENT );

    /**
     * \brief Maximum supported frame spec
     *
     * This represents the maximum frame specification this is at least
     * partially implemented.
     * If it exceeds FrmaeSpecCurrent, it is not guaranteed to be complete.
     * It allows for implementin and testing of Alpha and Beta
     * versions of the frame specification.
     */
    const version_type FrameSpecMaximum( FRAME_SPEC_MAX );

    /**
     * \brief Byte ordering of host
     */
    const int HostByteOrder( BYTE_ORDER_HOST );

    /**
     * \brief Get the version of frameCPP
     */
    std::string GetVersion( );

} /* namespace FrameCPP */
#endif /* ! defined(SWIG) */
#endif /* defined(__cplusplus) */

#endif /* FRAMECPP__COMMON__FrameSpec_HH */
