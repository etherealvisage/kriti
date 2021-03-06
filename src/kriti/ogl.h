#ifndef FUNCTION_CPP_GENERATED_HEADEROPENGL_HPP
#define FUNCTION_CPP_GENERATED_HEADEROPENGL_HPP

#if defined(__glew_h__) || defined(__GLEW_H__)
#error Attempt to include auto-generated header after including glew.h
#endif
#if defined(__gl_h_) || defined(__GL_H__)
#error Attempt to include auto-generated header after including gl.h
#endif
#if defined(__glext_h_) || defined(__GLEXT_H_)
#error Attempt to include auto-generated header after including glext.h
#endif
#if defined(__gltypes_h_)
#error Attempt to include auto-generated header after gltypes.h
#endif
#if defined(__gl_ATI_h_)
#error Attempt to include auto-generated header after including glATI.h
#endif

#define __glew_h__
#define __GLEW_H__
#define __gl_h_
#define __GL_H__
#define __glext_h_
#define __GLEXT_H_
#define __gltypes_h_
#define __gl_ATI_h_

#ifndef APIENTRY
	#if defined(__MINGW32__)
		#ifndef WIN32_LEAN_AND_MEAN
			#define WIN32_LEAN_AND_MEAN 1
		#endif
		#ifndef NOMINMAX
			#define NOMINMAX
		#endif
		#include <windows.h>
	#elif (_MSC_VER >= 800) || defined(_STDCALL_SUPPORTED) || defined(__BORLANDC__)
		#ifndef WIN32_LEAN_AND_MEAN
			#define WIN32_LEAN_AND_MEAN 1
		#endif
		#ifndef NOMINMAX
			#define NOMINMAX
		#endif
		#include <windows.h>
	#else
		#define APIENTRY
	#endif
#endif /*APIENTRY*/

#ifndef CODEGEN_FUNCPTR
	#define CODEGEN_REMOVE_FUNCPTR
	#if defined(_WIN32)
		#define CODEGEN_FUNCPTR APIENTRY
	#else
		#define CODEGEN_FUNCPTR
	#endif
#endif /*CODEGEN_FUNCPTR*/

#ifndef GLAPI
	#define GLAPI extern
#endif


#ifndef GL_LOAD_GEN_BASIC_OPENGL_TYPEDEFS
#define GL_LOAD_GEN_BASIC_OPENGL_TYPEDEFS


#endif /*GL_LOAD_GEN_BASIC_OPENGL_TYPEDEFS*/

#include <stddef.h>
#ifndef GLEXT_64_TYPES_DEFINED
/* This code block is duplicated in glxext.h, so must be protected */
#define GLEXT_64_TYPES_DEFINED
/* Define int32_t, int64_t, and uint64_t types for UST/MSC */
/* (as used in the GL_EXT_timer_query extension). */
#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
#include <inttypes.h>
#elif defined(__sun__) || defined(__digital__)
#include <inttypes.h>
#if defined(__STDC__)
#if defined(__arch64__) || defined(_LP64)
typedef long int int64_t;
typedef unsigned long int uint64_t;
#else
typedef long long int int64_t;
typedef unsigned long long int uint64_t;
#endif /* __arch64__ */
#endif /* __STDC__ */
#elif defined( __VMS ) || defined(__sgi)
#include <inttypes.h>
#elif defined(__SCO__) || defined(__USLC__)
#include <stdint.h>
#elif defined(__UNIXOS2__) || defined(__SOL64__)
typedef long int int32_t;
typedef long long int int64_t;
typedef unsigned long long int uint64_t;
#elif defined(_WIN32) && defined(__GNUC__)
#include <stdint.h>
#elif defined(_WIN32)
typedef __int32 int32_t;
typedef __int64 int64_t;
typedef unsigned __int64 uint64_t;
#else
/* Fallback if nothing above works */
#include <inttypes.h>
#endif
#endif
	typedef unsigned int GLenum;
	typedef unsigned char GLboolean;
	typedef unsigned int GLbitfield;
	typedef void GLvoid;
	typedef signed char GLbyte;
	typedef short GLshort;
	typedef int GLint;
	typedef unsigned char GLubyte;
	typedef unsigned short GLushort;
	typedef unsigned int GLuint;
	typedef int GLsizei;
	typedef float GLfloat;
	typedef float GLclampf;
	typedef double GLdouble;
	typedef double GLclampd;
	typedef char GLchar;
	typedef char GLcharARB;
	#ifdef __APPLE__
typedef void *GLhandleARB;
#else
typedef unsigned int GLhandleARB;
#endif
		typedef unsigned short GLhalfARB;
		typedef unsigned short GLhalf;
		typedef GLint GLfixed;
		typedef ptrdiff_t GLintptr;
		typedef ptrdiff_t GLsizeiptr;
		typedef int64_t GLint64;
		typedef uint64_t GLuint64;
		typedef ptrdiff_t GLintptrARB;
		typedef ptrdiff_t GLsizeiptrARB;
		typedef int64_t GLint64EXT;
		typedef uint64_t GLuint64EXT;
		typedef struct __GLsync *GLsync;
		struct _cl_context;
		struct _cl_event;
		typedef void (APIENTRY *GLDEBUGPROC)(GLenum source,GLenum type,GLuint id,GLenum severity,GLsizei length,const GLchar *message,const void *userParam);
		typedef void (APIENTRY *GLDEBUGPROCARB)(GLenum source,GLenum type,GLuint id,GLenum severity,GLsizei length,const GLchar *message,const void *userParam);
		typedef void (APIENTRY *GLDEBUGPROCAMD)(GLuint id,GLenum category,GLenum severity,GLsizei length,const GLchar *message,void *userParam);
		typedef unsigned short GLhalfNV;
		typedef GLintptr GLvdpauSurfaceNV;

namespace gl
{
	namespace exts
	{
		class LoadTest
		{
		private:
			//Safe bool idiom. Joy!
			typedef void (LoadTest::*bool_type)() const;
			void big_long_name_that_really_doesnt_matter() const {}
			
		public:
			operator bool_type() const
			{
				return m_isLoaded ? &LoadTest::big_long_name_that_really_doesnt_matter : 0;
			}
			
			int GetNumMissing() const {return m_numMissing;}
			
			LoadTest() : m_isLoaded(false), m_numMissing(0) {}
			LoadTest(bool isLoaded, int numMissing) : m_isLoaded(isLoaded), m_numMissing(numMissing) {}
		private:
			bool m_isLoaded;
			int m_numMissing;
		};
		
		extern LoadTest var_ARB_timer_query;
		extern LoadTest var_ARB_explicit_attrib_location;
		extern LoadTest var_ARB_viewport_array;
		extern LoadTest var_ARB_texture_multisample;
		
	} //namespace exts
	enum
	{
		TIMESTAMP                        = 0x8E28,
		TIME_ELAPSED                     = 0x88BF,
		
		DEPTH_RANGE                      = 0x0B70,
		FIRST_VERTEX_CONVENTION          = 0x8E4D,
		LAST_VERTEX_CONVENTION           = 0x8E4E,
		LAYER_PROVOKING_VERTEX           = 0x825E,
		MAX_VIEWPORTS                    = 0x825B,
		PROVOKING_VERTEX                 = 0x8E4F,
		SCISSOR_BOX                      = 0x0C10,
		SCISSOR_TEST                     = 0x0C11,
		UNDEFINED_VERTEX                 = 0x8260,
		VIEWPORT                         = 0x0BA2,
		VIEWPORT_BOUNDS_RANGE            = 0x825D,
		VIEWPORT_INDEX_PROVOKING_VERTEX  = 0x825F,
		VIEWPORT_SUBPIXEL_BITS           = 0x825C,
		
		INT_SAMPLER_2D_MULTISAMPLE       = 0x9109,
		INT_SAMPLER_2D_MULTISAMPLE_ARRAY = 0x910C,
		MAX_COLOR_TEXTURE_SAMPLES        = 0x910E,
		MAX_DEPTH_TEXTURE_SAMPLES        = 0x910F,
		MAX_INTEGER_SAMPLES              = 0x9110,
		MAX_SAMPLE_MASK_WORDS            = 0x8E59,
		PROXY_TEXTURE_2D_MULTISAMPLE     = 0x9101,
		PROXY_TEXTURE_2D_MULTISAMPLE_ARRAY = 0x9103,
		SAMPLER_2D_MULTISAMPLE           = 0x9108,
		SAMPLER_2D_MULTISAMPLE_ARRAY     = 0x910B,
		SAMPLE_MASK                      = 0x8E51,
		SAMPLE_MASK_VALUE                = 0x8E52,
		SAMPLE_POSITION                  = 0x8E50,
		TEXTURE_2D_MULTISAMPLE           = 0x9100,
		TEXTURE_2D_MULTISAMPLE_ARRAY     = 0x9102,
		TEXTURE_BINDING_2D_MULTISAMPLE   = 0x9104,
		TEXTURE_BINDING_2D_MULTISAMPLE_ARRAY = 0x9105,
		TEXTURE_FIXED_SAMPLE_LOCATIONS   = 0x9107,
		TEXTURE_SAMPLES                  = 0x9106,
		UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE = 0x910A,
		UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE_ARRAY = 0x910D,
		
		_2D                              = 0x0600,
		_2_BYTES                         = 0x1407,
		_3D                              = 0x0601,
		_3D_COLOR                        = 0x0602,
		_3D_COLOR_TEXTURE                = 0x0603,
		_3_BYTES                         = 0x1408,
		_4D_COLOR_TEXTURE                = 0x0604,
		_4_BYTES                         = 0x1409,
		ACCUM                            = 0x0100,
		ACCUM_ALPHA_BITS                 = 0x0D5B,
		ACCUM_BLUE_BITS                  = 0x0D5A,
		ACCUM_BUFFER_BIT                 = 0x00000200,
		ACCUM_CLEAR_VALUE                = 0x0B80,
		ACCUM_GREEN_BITS                 = 0x0D59,
		ACCUM_RED_BITS                   = 0x0D58,
		ADD                              = 0x0104,
		ALL_ATTRIB_BITS                  = 0xFFFFFFFF,
		ALPHA                            = 0x1906,
		ALPHA12                          = 0x803D,
		ALPHA16                          = 0x803E,
		ALPHA4                           = 0x803B,
		ALPHA8                           = 0x803C,
		ALPHA_BIAS                       = 0x0D1D,
		ALPHA_BITS                       = 0x0D55,
		ALPHA_SCALE                      = 0x0D1C,
		ALPHA_TEST                       = 0x0BC0,
		ALPHA_TEST_FUNC                  = 0x0BC1,
		ALPHA_TEST_REF                   = 0x0BC2,
		ALWAYS                           = 0x0207,
		AMBIENT                          = 0x1200,
		AMBIENT_AND_DIFFUSE              = 0x1602,
		AND                              = 0x1501,
		AND_INVERTED                     = 0x1504,
		AND_REVERSE                      = 0x1502,
		ATTRIB_STACK_DEPTH               = 0x0BB0,
		AUTO_NORMAL                      = 0x0D80,
		AUX0                             = 0x0409,
		AUX1                             = 0x040A,
		AUX2                             = 0x040B,
		AUX3                             = 0x040C,
		AUX_BUFFERS                      = 0x0C00,
		BACK                             = 0x0405,
		BACK_LEFT                        = 0x0402,
		BACK_RIGHT                       = 0x0403,
		BITMAP                           = 0x1A00,
		BITMAP_TOKEN                     = 0x0704,
		BLEND                            = 0x0BE2,
		BLEND_DST                        = 0x0BE0,
		BLEND_SRC                        = 0x0BE1,
		BLUE                             = 0x1905,
		BLUE_BIAS                        = 0x0D1B,
		BLUE_BITS                        = 0x0D54,
		BLUE_SCALE                       = 0x0D1A,
		BYTE                             = 0x1400,
		C3F_V3F                          = 0x2A24,
		C4F_N3F_V3F                      = 0x2A26,
		C4UB_V2F                         = 0x2A22,
		C4UB_V3F                         = 0x2A23,
		CCW                              = 0x0901,
		CLAMP                            = 0x2900,
		CLEAR                            = 0x1500,
		CLIENT_ALL_ATTRIB_BITS           = 0xFFFFFFFF,
		CLIENT_ATTRIB_STACK_DEPTH        = 0x0BB1,
		CLIENT_PIXEL_STORE_BIT           = 0x00000001,
		CLIENT_VERTEX_ARRAY_BIT          = 0x00000002,
		CLIP_PLANE0                      = 0x3000,
		CLIP_PLANE1                      = 0x3001,
		CLIP_PLANE2                      = 0x3002,
		CLIP_PLANE3                      = 0x3003,
		CLIP_PLANE4                      = 0x3004,
		CLIP_PLANE5                      = 0x3005,
		COEFF                            = 0x0A00,
		COLOR                            = 0x1800,
		COLOR_ARRAY                      = 0x8076,
		COLOR_ARRAY_POINTER              = 0x8090,
		COLOR_ARRAY_SIZE                 = 0x8081,
		COLOR_ARRAY_STRIDE               = 0x8083,
		COLOR_ARRAY_TYPE                 = 0x8082,
		COLOR_BUFFER_BIT                 = 0x00004000,
		COLOR_CLEAR_VALUE                = 0x0C22,
		COLOR_INDEX                      = 0x1900,
		COLOR_INDEXES                    = 0x1603,
		COLOR_LOGIC_OP                   = 0x0BF2,
		COLOR_MATERIAL                   = 0x0B57,
		COLOR_MATERIAL_FACE              = 0x0B55,
		COLOR_MATERIAL_PARAMETER         = 0x0B56,
		COLOR_WRITEMASK                  = 0x0C23,
		COMPILE                          = 0x1300,
		COMPILE_AND_EXECUTE              = 0x1301,
		CONSTANT_ATTENUATION             = 0x1207,
		COPY                             = 0x1503,
		COPY_INVERTED                    = 0x150C,
		COPY_PIXEL_TOKEN                 = 0x0706,
		CULL_FACE                        = 0x0B44,
		CULL_FACE_MODE                   = 0x0B45,
		CURRENT_BIT                      = 0x00000001,
		CURRENT_COLOR                    = 0x0B00,
		CURRENT_INDEX                    = 0x0B01,
		CURRENT_NORMAL                   = 0x0B02,
		CURRENT_RASTER_COLOR             = 0x0B04,
		CURRENT_RASTER_DISTANCE          = 0x0B09,
		CURRENT_RASTER_INDEX             = 0x0B05,
		CURRENT_RASTER_POSITION          = 0x0B07,
		CURRENT_RASTER_POSITION_VALID    = 0x0B08,
		CURRENT_RASTER_TEXTURE_COORDS    = 0x0B06,
		CURRENT_TEXTURE_COORDS           = 0x0B03,
		CW                               = 0x0900,
		DECAL                            = 0x2101,
		DECR                             = 0x1E03,
		DEPTH                            = 0x1801,
		DEPTH_BIAS                       = 0x0D1F,
		DEPTH_BITS                       = 0x0D56,
		DEPTH_BUFFER_BIT                 = 0x00000100,
		DEPTH_CLEAR_VALUE                = 0x0B73,
		DEPTH_COMPONENT                  = 0x1902,
		DEPTH_FUNC                       = 0x0B74,
		//DEPTH_RANGE taken from ext: ARB_viewport_array
		DEPTH_SCALE                      = 0x0D1E,
		DEPTH_TEST                       = 0x0B71,
		DEPTH_WRITEMASK                  = 0x0B72,
		DIFFUSE                          = 0x1201,
		DITHER                           = 0x0BD0,
		DOMAIN_                          = 0x0A02,
		DONT_CARE                        = 0x1100,
		DOUBLE                           = 0x140A,
		DOUBLEBUFFER                     = 0x0C32,
		DRAW_BUFFER                      = 0x0C01,
		DRAW_PIXEL_TOKEN                 = 0x0705,
		DST_ALPHA                        = 0x0304,
		DST_COLOR                        = 0x0306,
		EDGE_FLAG                        = 0x0B43,
		EDGE_FLAG_ARRAY                  = 0x8079,
		EDGE_FLAG_ARRAY_POINTER          = 0x8093,
		EDGE_FLAG_ARRAY_STRIDE           = 0x808C,
		EMISSION                         = 0x1600,
		ENABLE_BIT                       = 0x00002000,
		EQUAL                            = 0x0202,
		EQUIV                            = 0x1509,
		EVAL_BIT                         = 0x00010000,
		EXP                              = 0x0800,
		EXP2                             = 0x0801,
		EXTENSIONS                       = 0x1F03,
		EYE_LINEAR                       = 0x2400,
		EYE_PLANE                        = 0x2502,
		FALSE_                           = 0,
		FASTEST                          = 0x1101,
		FEEDBACK                         = 0x1C01,
		FEEDBACK_BUFFER_POINTER          = 0x0DF0,
		FEEDBACK_BUFFER_SIZE             = 0x0DF1,
		FEEDBACK_BUFFER_TYPE             = 0x0DF2,
		FILL                             = 0x1B02,
		FLAT                             = 0x1D00,
		FLOAT                            = 0x1406,
		FOG                              = 0x0B60,
		FOG_BIT                          = 0x00000080,
		FOG_COLOR                        = 0x0B66,
		FOG_DENSITY                      = 0x0B62,
		FOG_END                          = 0x0B64,
		FOG_HINT                         = 0x0C54,
		FOG_INDEX                        = 0x0B61,
		FOG_MODE                         = 0x0B65,
		FOG_START                        = 0x0B63,
		FRONT                            = 0x0404,
		FRONT_AND_BACK                   = 0x0408,
		FRONT_FACE                       = 0x0B46,
		FRONT_LEFT                       = 0x0400,
		FRONT_RIGHT                      = 0x0401,
		GEQUAL                           = 0x0206,
		GREATER                          = 0x0204,
		GREEN                            = 0x1904,
		GREEN_BIAS                       = 0x0D19,
		GREEN_BITS                       = 0x0D53,
		GREEN_SCALE                      = 0x0D18,
		HINT_BIT                         = 0x00008000,
		INCR                             = 0x1E02,
		INDEX_ARRAY                      = 0x8077,
		INDEX_ARRAY_POINTER              = 0x8091,
		INDEX_ARRAY_STRIDE               = 0x8086,
		INDEX_ARRAY_TYPE                 = 0x8085,
		INDEX_BITS                       = 0x0D51,
		INDEX_CLEAR_VALUE                = 0x0C20,
		INDEX_LOGIC_OP                   = 0x0BF1,
		INDEX_MODE                       = 0x0C30,
		INDEX_OFFSET                     = 0x0D13,
		INDEX_SHIFT                      = 0x0D12,
		INDEX_WRITEMASK                  = 0x0C21,
		INT                              = 0x1404,
		INTENSITY                        = 0x8049,
		INTENSITY12                      = 0x804C,
		INTENSITY16                      = 0x804D,
		INTENSITY4                       = 0x804A,
		INTENSITY8                       = 0x804B,
		INVALID_ENUM                     = 0x0500,
		INVALID_OPERATION                = 0x0502,
		INVALID_VALUE                    = 0x0501,
		INVERT                           = 0x150A,
		KEEP                             = 0x1E00,
		LEFT                             = 0x0406,
		LEQUAL                           = 0x0203,
		LESS                             = 0x0201,
		LIGHT0                           = 0x4000,
		LIGHT1                           = 0x4001,
		LIGHT2                           = 0x4002,
		LIGHT3                           = 0x4003,
		LIGHT4                           = 0x4004,
		LIGHT5                           = 0x4005,
		LIGHT6                           = 0x4006,
		LIGHT7                           = 0x4007,
		LIGHTING                         = 0x0B50,
		LIGHTING_BIT                     = 0x00000040,
		LIGHT_MODEL_AMBIENT              = 0x0B53,
		LIGHT_MODEL_LOCAL_VIEWER         = 0x0B51,
		LIGHT_MODEL_TWO_SIDE             = 0x0B52,
		LINE                             = 0x1B01,
		LINEAR                           = 0x2601,
		LINEAR_ATTENUATION               = 0x1208,
		LINEAR_MIPMAP_LINEAR             = 0x2703,
		LINEAR_MIPMAP_NEAREST            = 0x2701,
		LINES                            = 0x0001,
		LINE_BIT                         = 0x00000004,
		LINE_LOOP                        = 0x0002,
		LINE_RESET_TOKEN                 = 0x0707,
		LINE_SMOOTH                      = 0x0B20,
		LINE_SMOOTH_HINT                 = 0x0C52,
		LINE_STIPPLE                     = 0x0B24,
		LINE_STIPPLE_PATTERN             = 0x0B25,
		LINE_STIPPLE_REPEAT              = 0x0B26,
		LINE_STRIP                       = 0x0003,
		LINE_TOKEN                       = 0x0702,
		LINE_WIDTH                       = 0x0B21,
		LINE_WIDTH_GRANULARITY           = 0x0B23,
		LINE_WIDTH_RANGE                 = 0x0B22,
		LIST_BASE                        = 0x0B32,
		LIST_BIT                         = 0x00020000,
		LIST_INDEX                       = 0x0B33,
		LIST_MODE                        = 0x0B30,
		LOAD                             = 0x0101,
		LOGIC_OP                         = 0x0BF1,
		LOGIC_OP_MODE                    = 0x0BF0,
		LUMINANCE                        = 0x1909,
		LUMINANCE12                      = 0x8041,
		LUMINANCE12_ALPHA12              = 0x8047,
		LUMINANCE12_ALPHA4               = 0x8046,
		LUMINANCE16                      = 0x8042,
		LUMINANCE16_ALPHA16              = 0x8048,
		LUMINANCE4                       = 0x803F,
		LUMINANCE4_ALPHA4                = 0x8043,
		LUMINANCE6_ALPHA2                = 0x8044,
		LUMINANCE8                       = 0x8040,
		LUMINANCE8_ALPHA8                = 0x8045,
		LUMINANCE_ALPHA                  = 0x190A,
		MAP1_COLOR_4                     = 0x0D90,
		MAP1_GRID_DOMAIN                 = 0x0DD0,
		MAP1_GRID_SEGMENTS               = 0x0DD1,
		MAP1_INDEX                       = 0x0D91,
		MAP1_NORMAL                      = 0x0D92,
		MAP1_TEXTURE_COORD_1             = 0x0D93,
		MAP1_TEXTURE_COORD_2             = 0x0D94,
		MAP1_TEXTURE_COORD_3             = 0x0D95,
		MAP1_TEXTURE_COORD_4             = 0x0D96,
		MAP1_VERTEX_3                    = 0x0D97,
		MAP1_VERTEX_4                    = 0x0D98,
		MAP2_COLOR_4                     = 0x0DB0,
		MAP2_GRID_DOMAIN                 = 0x0DD2,
		MAP2_GRID_SEGMENTS               = 0x0DD3,
		MAP2_INDEX                       = 0x0DB1,
		MAP2_NORMAL                      = 0x0DB2,
		MAP2_TEXTURE_COORD_1             = 0x0DB3,
		MAP2_TEXTURE_COORD_2             = 0x0DB4,
		MAP2_TEXTURE_COORD_3             = 0x0DB5,
		MAP2_TEXTURE_COORD_4             = 0x0DB6,
		MAP2_VERTEX_3                    = 0x0DB7,
		MAP2_VERTEX_4                    = 0x0DB8,
		MAP_COLOR                        = 0x0D10,
		MAP_STENCIL                      = 0x0D11,
		MATRIX_MODE                      = 0x0BA0,
		MAX_ATTRIB_STACK_DEPTH           = 0x0D35,
		MAX_CLIENT_ATTRIB_STACK_DEPTH    = 0x0D3B,
		MAX_CLIP_PLANES                  = 0x0D32,
		MAX_EVAL_ORDER                   = 0x0D30,
		MAX_LIGHTS                       = 0x0D31,
		MAX_LIST_NESTING                 = 0x0B31,
		MAX_MODELVIEW_STACK_DEPTH        = 0x0D36,
		MAX_NAME_STACK_DEPTH             = 0x0D37,
		MAX_PIXEL_MAP_TABLE              = 0x0D34,
		MAX_PROJECTION_STACK_DEPTH       = 0x0D38,
		MAX_TEXTURE_SIZE                 = 0x0D33,
		MAX_TEXTURE_STACK_DEPTH          = 0x0D39,
		MAX_VIEWPORT_DIMS                = 0x0D3A,
		MODELVIEW                        = 0x1700,
		MODELVIEW_MATRIX                 = 0x0BA6,
		MODELVIEW_STACK_DEPTH            = 0x0BA3,
		MODULATE                         = 0x2100,
		MULT                             = 0x0103,
		N3F_V3F                          = 0x2A25,
		NAME_STACK_DEPTH                 = 0x0D70,
		NAND                             = 0x150E,
		NEAREST                          = 0x2600,
		NEAREST_MIPMAP_LINEAR            = 0x2702,
		NEAREST_MIPMAP_NEAREST           = 0x2700,
		NEVER                            = 0x0200,
		NICEST                           = 0x1102,
		NONE                             = 0,
		NOOP                             = 0x1505,
		NOR                              = 0x1508,
		NORMALIZE                        = 0x0BA1,
		NORMAL_ARRAY                     = 0x8075,
		NORMAL_ARRAY_POINTER             = 0x808F,
		NORMAL_ARRAY_STRIDE              = 0x807F,
		NORMAL_ARRAY_TYPE                = 0x807E,
		NOTEQUAL                         = 0x0205,
		NO_ERROR_                        = 0,
		OBJECT_LINEAR                    = 0x2401,
		OBJECT_PLANE                     = 0x2501,
		ONE                              = 1,
		ONE_MINUS_DST_ALPHA              = 0x0305,
		ONE_MINUS_DST_COLOR              = 0x0307,
		ONE_MINUS_SRC_ALPHA              = 0x0303,
		ONE_MINUS_SRC_COLOR              = 0x0301,
		OR                               = 0x1507,
		ORDER                            = 0x0A01,
		OR_INVERTED                      = 0x150D,
		OR_REVERSE                       = 0x150B,
		OUT_OF_MEMORY                    = 0x0505,
		PACK_ALIGNMENT                   = 0x0D05,
		PACK_LSB_FIRST                   = 0x0D01,
		PACK_ROW_LENGTH                  = 0x0D02,
		PACK_SKIP_PIXELS                 = 0x0D04,
		PACK_SKIP_ROWS                   = 0x0D03,
		PACK_SWAP_BYTES                  = 0x0D00,
		PASS_THROUGH_TOKEN               = 0x0700,
		PERSPECTIVE_CORRECTION_HINT      = 0x0C50,
		PIXEL_MAP_A_TO_A                 = 0x0C79,
		PIXEL_MAP_A_TO_A_SIZE            = 0x0CB9,
		PIXEL_MAP_B_TO_B                 = 0x0C78,
		PIXEL_MAP_B_TO_B_SIZE            = 0x0CB8,
		PIXEL_MAP_G_TO_G                 = 0x0C77,
		PIXEL_MAP_G_TO_G_SIZE            = 0x0CB7,
		PIXEL_MAP_I_TO_A                 = 0x0C75,
		PIXEL_MAP_I_TO_A_SIZE            = 0x0CB5,
		PIXEL_MAP_I_TO_B                 = 0x0C74,
		PIXEL_MAP_I_TO_B_SIZE            = 0x0CB4,
		PIXEL_MAP_I_TO_G                 = 0x0C73,
		PIXEL_MAP_I_TO_G_SIZE            = 0x0CB3,
		PIXEL_MAP_I_TO_I                 = 0x0C70,
		PIXEL_MAP_I_TO_I_SIZE            = 0x0CB0,
		PIXEL_MAP_I_TO_R                 = 0x0C72,
		PIXEL_MAP_I_TO_R_SIZE            = 0x0CB2,
		PIXEL_MAP_R_TO_R                 = 0x0C76,
		PIXEL_MAP_R_TO_R_SIZE            = 0x0CB6,
		PIXEL_MAP_S_TO_S                 = 0x0C71,
		PIXEL_MAP_S_TO_S_SIZE            = 0x0CB1,
		PIXEL_MODE_BIT                   = 0x00000020,
		POINT                            = 0x1B00,
		POINTS                           = 0x0000,
		POINT_BIT                        = 0x00000002,
		POINT_SIZE                       = 0x0B11,
		POINT_SIZE_GRANULARITY           = 0x0B13,
		POINT_SIZE_RANGE                 = 0x0B12,
		POINT_SMOOTH                     = 0x0B10,
		POINT_SMOOTH_HINT                = 0x0C51,
		POINT_TOKEN                      = 0x0701,
		POLYGON                          = 0x0009,
		POLYGON_BIT                      = 0x00000008,
		POLYGON_MODE                     = 0x0B40,
		POLYGON_OFFSET_FACTOR            = 0x8038,
		POLYGON_OFFSET_FILL              = 0x8037,
		POLYGON_OFFSET_LINE              = 0x2A02,
		POLYGON_OFFSET_POINT             = 0x2A01,
		POLYGON_OFFSET_UNITS             = 0x2A00,
		POLYGON_SMOOTH                   = 0x0B41,
		POLYGON_SMOOTH_HINT              = 0x0C53,
		POLYGON_STIPPLE                  = 0x0B42,
		POLYGON_STIPPLE_BIT              = 0x00000010,
		POLYGON_TOKEN                    = 0x0703,
		POSITION                         = 0x1203,
		PROJECTION                       = 0x1701,
		PROJECTION_MATRIX                = 0x0BA7,
		PROJECTION_STACK_DEPTH           = 0x0BA4,
		PROXY_TEXTURE_1D                 = 0x8063,
		PROXY_TEXTURE_2D                 = 0x8064,
		Q                                = 0x2003,
		QUADRATIC_ATTENUATION            = 0x1209,
		QUADS                            = 0x0007,
		QUAD_STRIP                       = 0x0008,
		R                                = 0x2002,
		R3_G3_B2                         = 0x2A10,
		READ_BUFFER                      = 0x0C02,
		RED                              = 0x1903,
		RED_BIAS                         = 0x0D15,
		RED_BITS                         = 0x0D52,
		RED_SCALE                        = 0x0D14,
		RENDER                           = 0x1C00,
		RENDERER                         = 0x1F01,
		RENDER_MODE                      = 0x0C40,
		REPEAT                           = 0x2901,
		REPLACE                          = 0x1E01,
		RETURN                           = 0x0102,
		RGB                              = 0x1907,
		RGB10                            = 0x8052,
		RGB10_A2                         = 0x8059,
		RGB12                            = 0x8053,
		RGB16                            = 0x8054,
		RGB4                             = 0x804F,
		RGB5                             = 0x8050,
		RGB5_A1                          = 0x8057,
		RGB8                             = 0x8051,
		RGBA                             = 0x1908,
		RGBA12                           = 0x805A,
		RGBA16                           = 0x805B,
		RGBA2                            = 0x8055,
		RGBA4                            = 0x8056,
		RGBA8                            = 0x8058,
		RGBA_MODE                        = 0x0C31,
		RIGHT                            = 0x0407,
		S                                = 0x2000,
		SCISSOR_BIT                      = 0x00080000,
		//SCISSOR_BOX taken from ext: ARB_viewport_array
		//SCISSOR_TEST taken from ext: ARB_viewport_array
		SELECT                           = 0x1C02,
		SELECTION_BUFFER_POINTER         = 0x0DF3,
		SELECTION_BUFFER_SIZE            = 0x0DF4,
		SET                              = 0x150F,
		SHADE_MODEL                      = 0x0B54,
		SHININESS                        = 0x1601,
		SHORT                            = 0x1402,
		SMOOTH                           = 0x1D01,
		SPECULAR                         = 0x1202,
		SPHERE_MAP                       = 0x2402,
		SPOT_CUTOFF                      = 0x1206,
		SPOT_DIRECTION                   = 0x1204,
		SPOT_EXPONENT                    = 0x1205,
		SRC_ALPHA                        = 0x0302,
		SRC_ALPHA_SATURATE               = 0x0308,
		SRC_COLOR                        = 0x0300,
		STACK_OVERFLOW                   = 0x0503,
		STACK_UNDERFLOW                  = 0x0504,
		STENCIL                          = 0x1802,
		STENCIL_BITS                     = 0x0D57,
		STENCIL_BUFFER_BIT               = 0x00000400,
		STENCIL_CLEAR_VALUE              = 0x0B91,
		STENCIL_FAIL                     = 0x0B94,
		STENCIL_FUNC                     = 0x0B92,
		STENCIL_INDEX                    = 0x1901,
		STENCIL_PASS_DEPTH_FAIL          = 0x0B95,
		STENCIL_PASS_DEPTH_PASS          = 0x0B96,
		STENCIL_REF                      = 0x0B97,
		STENCIL_TEST                     = 0x0B90,
		STENCIL_VALUE_MASK               = 0x0B93,
		STENCIL_WRITEMASK                = 0x0B98,
		STEREO                           = 0x0C33,
		SUBPIXEL_BITS                    = 0x0D50,
		T                                = 0x2001,
		T2F_C3F_V3F                      = 0x2A2A,
		T2F_C4F_N3F_V3F                  = 0x2A2C,
		T2F_C4UB_V3F                     = 0x2A29,
		T2F_N3F_V3F                      = 0x2A2B,
		T2F_V3F                          = 0x2A27,
		T4F_C4F_N3F_V4F                  = 0x2A2D,
		T4F_V4F                          = 0x2A28,
		TEXTURE                          = 0x1702,
		TEXTURE_1D                       = 0x0DE0,
		TEXTURE_2D                       = 0x0DE1,
		TEXTURE_ALPHA_SIZE               = 0x805F,
		TEXTURE_BINDING_1D               = 0x8068,
		TEXTURE_BINDING_2D               = 0x8069,
		TEXTURE_BIT                      = 0x00040000,
		TEXTURE_BLUE_SIZE                = 0x805E,
		TEXTURE_BORDER                   = 0x1005,
		TEXTURE_BORDER_COLOR             = 0x1004,
		TEXTURE_COMPONENTS               = 0x1003,
		TEXTURE_COORD_ARRAY              = 0x8078,
		TEXTURE_COORD_ARRAY_POINTER      = 0x8092,
		TEXTURE_COORD_ARRAY_SIZE         = 0x8088,
		TEXTURE_COORD_ARRAY_STRIDE       = 0x808A,
		TEXTURE_COORD_ARRAY_TYPE         = 0x8089,
		TEXTURE_ENV                      = 0x2300,
		TEXTURE_ENV_COLOR                = 0x2201,
		TEXTURE_ENV_MODE                 = 0x2200,
		TEXTURE_GEN_MODE                 = 0x2500,
		TEXTURE_GEN_Q                    = 0x0C63,
		TEXTURE_GEN_R                    = 0x0C62,
		TEXTURE_GEN_S                    = 0x0C60,
		TEXTURE_GEN_T                    = 0x0C61,
		TEXTURE_GREEN_SIZE               = 0x805D,
		TEXTURE_HEIGHT                   = 0x1001,
		TEXTURE_INTENSITY_SIZE           = 0x8061,
		TEXTURE_INTERNAL_FORMAT          = 0x1003,
		TEXTURE_LUMINANCE_SIZE           = 0x8060,
		TEXTURE_MAG_FILTER               = 0x2800,
		TEXTURE_MATRIX                   = 0x0BA8,
		TEXTURE_MIN_FILTER               = 0x2801,
		TEXTURE_PRIORITY                 = 0x8066,
		TEXTURE_RED_SIZE                 = 0x805C,
		TEXTURE_RESIDENT                 = 0x8067,
		TEXTURE_STACK_DEPTH              = 0x0BA5,
		TEXTURE_WIDTH                    = 0x1000,
		TEXTURE_WRAP_S                   = 0x2802,
		TEXTURE_WRAP_T                   = 0x2803,
		TRANSFORM_BIT                    = 0x00001000,
		TRIANGLES                        = 0x0004,
		TRIANGLE_FAN                     = 0x0006,
		TRIANGLE_STRIP                   = 0x0005,
		TRUE_                            = 1,
		UNPACK_ALIGNMENT                 = 0x0CF5,
		UNPACK_LSB_FIRST                 = 0x0CF1,
		UNPACK_ROW_LENGTH                = 0x0CF2,
		UNPACK_SKIP_PIXELS               = 0x0CF4,
		UNPACK_SKIP_ROWS                 = 0x0CF3,
		UNPACK_SWAP_BYTES                = 0x0CF0,
		UNSIGNED_BYTE                    = 0x1401,
		UNSIGNED_INT                     = 0x1405,
		UNSIGNED_SHORT                   = 0x1403,
		V2F                              = 0x2A20,
		V3F                              = 0x2A21,
		VENDOR                           = 0x1F00,
		VERSION                          = 0x1F02,
		VERTEX_ARRAY                     = 0x8074,
		VERTEX_ARRAY_POINTER             = 0x808E,
		VERTEX_ARRAY_SIZE                = 0x807A,
		VERTEX_ARRAY_STRIDE              = 0x807C,
		VERTEX_ARRAY_TYPE                = 0x807B,
		//VIEWPORT taken from ext: ARB_viewport_array
		VIEWPORT_BIT                     = 0x00000800,
		XOR                              = 0x1506,
		ZERO                             = 0,
		ZOOM_X                           = 0x0D16,
		ZOOM_Y                           = 0x0D17,
		
		ALIASED_LINE_WIDTH_RANGE         = 0x846E,
		ALIASED_POINT_SIZE_RANGE         = 0x846D,
		BGR                              = 0x80E0,
		BGRA                             = 0x80E1,
		CLAMP_TO_EDGE                    = 0x812F,
		LIGHT_MODEL_COLOR_CONTROL        = 0x81F8,
		MAX_3D_TEXTURE_SIZE              = 0x8073,
		MAX_ELEMENTS_INDICES             = 0x80E9,
		MAX_ELEMENTS_VERTICES            = 0x80E8,
		PACK_IMAGE_HEIGHT                = 0x806C,
		PACK_SKIP_IMAGES                 = 0x806B,
		PROXY_TEXTURE_3D                 = 0x8070,
		RESCALE_NORMAL                   = 0x803A,
		SEPARATE_SPECULAR_COLOR          = 0x81FA,
		SINGLE_COLOR                     = 0x81F9,
		SMOOTH_LINE_WIDTH_GRANULARITY    = 0x0B23,
		SMOOTH_LINE_WIDTH_RANGE          = 0x0B22,
		SMOOTH_POINT_SIZE_GRANULARITY    = 0x0B13,
		SMOOTH_POINT_SIZE_RANGE          = 0x0B12,
		TEXTURE_3D                       = 0x806F,
		TEXTURE_BASE_LEVEL               = 0x813C,
		TEXTURE_BINDING_3D               = 0x806A,
		TEXTURE_DEPTH                    = 0x8071,
		TEXTURE_MAX_LEVEL                = 0x813D,
		TEXTURE_MAX_LOD                  = 0x813B,
		TEXTURE_MIN_LOD                  = 0x813A,
		TEXTURE_WRAP_R                   = 0x8072,
		UNPACK_IMAGE_HEIGHT              = 0x806E,
		UNPACK_SKIP_IMAGES               = 0x806D,
		UNSIGNED_BYTE_2_3_3_REV          = 0x8362,
		UNSIGNED_BYTE_3_3_2              = 0x8032,
		UNSIGNED_INT_10_10_10_2          = 0x8036,
		UNSIGNED_INT_2_10_10_10_REV      = 0x8368,
		UNSIGNED_INT_8_8_8_8             = 0x8035,
		UNSIGNED_INT_8_8_8_8_REV         = 0x8367,
		UNSIGNED_SHORT_1_5_5_5_REV       = 0x8366,
		UNSIGNED_SHORT_4_4_4_4           = 0x8033,
		UNSIGNED_SHORT_4_4_4_4_REV       = 0x8365,
		UNSIGNED_SHORT_5_5_5_1           = 0x8034,
		UNSIGNED_SHORT_5_6_5             = 0x8363,
		UNSIGNED_SHORT_5_6_5_REV         = 0x8364,
		
		ACTIVE_TEXTURE                   = 0x84E0,
		ADD_SIGNED                       = 0x8574,
		CLAMP_TO_BORDER                  = 0x812D,
		CLIENT_ACTIVE_TEXTURE            = 0x84E1,
		COMBINE                          = 0x8570,
		COMBINE_ALPHA                    = 0x8572,
		COMBINE_RGB                      = 0x8571,
		COMPRESSED_ALPHA                 = 0x84E9,
		COMPRESSED_INTENSITY             = 0x84EC,
		COMPRESSED_LUMINANCE             = 0x84EA,
		COMPRESSED_LUMINANCE_ALPHA       = 0x84EB,
		COMPRESSED_RGB                   = 0x84ED,
		COMPRESSED_RGBA                  = 0x84EE,
		COMPRESSED_TEXTURE_FORMATS       = 0x86A3,
		CONSTANT                         = 0x8576,
		DOT3_RGB                         = 0x86AE,
		DOT3_RGBA                        = 0x86AF,
		INTERPOLATE                      = 0x8575,
		MAX_CUBE_MAP_TEXTURE_SIZE        = 0x851C,
		MAX_TEXTURE_UNITS                = 0x84E2,
		MULTISAMPLE                      = 0x809D,
		MULTISAMPLE_BIT                  = 0x20000000,
		NORMAL_MAP                       = 0x8511,
		NUM_COMPRESSED_TEXTURE_FORMATS   = 0x86A2,
		OPERAND0_ALPHA                   = 0x8598,
		OPERAND0_RGB                     = 0x8590,
		OPERAND1_ALPHA                   = 0x8599,
		OPERAND1_RGB                     = 0x8591,
		OPERAND2_ALPHA                   = 0x859A,
		OPERAND2_RGB                     = 0x8592,
		PREVIOUS                         = 0x8578,
		PRIMARY_COLOR                    = 0x8577,
		PROXY_TEXTURE_CUBE_MAP           = 0x851B,
		REFLECTION_MAP                   = 0x8512,
		RGB_SCALE                        = 0x8573,
		SAMPLES                          = 0x80A9,
		SAMPLE_ALPHA_TO_COVERAGE         = 0x809E,
		SAMPLE_ALPHA_TO_ONE              = 0x809F,
		SAMPLE_BUFFERS                   = 0x80A8,
		SAMPLE_COVERAGE                  = 0x80A0,
		SAMPLE_COVERAGE_INVERT           = 0x80AB,
		SAMPLE_COVERAGE_VALUE            = 0x80AA,
		SOURCE0_ALPHA                    = 0x8588,
		SOURCE0_RGB                      = 0x8580,
		SOURCE1_ALPHA                    = 0x8589,
		SOURCE1_RGB                      = 0x8581,
		SOURCE2_ALPHA                    = 0x858A,
		SOURCE2_RGB                      = 0x8582,
		SUBTRACT                         = 0x84E7,
		TEXTURE0                         = 0x84C0,
		TEXTURE1                         = 0x84C1,
		TEXTURE10                        = 0x84CA,
		TEXTURE11                        = 0x84CB,
		TEXTURE12                        = 0x84CC,
		TEXTURE13                        = 0x84CD,
		TEXTURE14                        = 0x84CE,
		TEXTURE15                        = 0x84CF,
		TEXTURE16                        = 0x84D0,
		TEXTURE17                        = 0x84D1,
		TEXTURE18                        = 0x84D2,
		TEXTURE19                        = 0x84D3,
		TEXTURE2                         = 0x84C2,
		TEXTURE20                        = 0x84D4,
		TEXTURE21                        = 0x84D5,
		TEXTURE22                        = 0x84D6,
		TEXTURE23                        = 0x84D7,
		TEXTURE24                        = 0x84D8,
		TEXTURE25                        = 0x84D9,
		TEXTURE26                        = 0x84DA,
		TEXTURE27                        = 0x84DB,
		TEXTURE28                        = 0x84DC,
		TEXTURE29                        = 0x84DD,
		TEXTURE3                         = 0x84C3,
		TEXTURE30                        = 0x84DE,
		TEXTURE31                        = 0x84DF,
		TEXTURE4                         = 0x84C4,
		TEXTURE5                         = 0x84C5,
		TEXTURE6                         = 0x84C6,
		TEXTURE7                         = 0x84C7,
		TEXTURE8                         = 0x84C8,
		TEXTURE9                         = 0x84C9,
		TEXTURE_BINDING_CUBE_MAP         = 0x8514,
		TEXTURE_COMPRESSED               = 0x86A1,
		TEXTURE_COMPRESSED_IMAGE_SIZE    = 0x86A0,
		TEXTURE_COMPRESSION_HINT         = 0x84EF,
		TEXTURE_CUBE_MAP                 = 0x8513,
		TEXTURE_CUBE_MAP_NEGATIVE_X      = 0x8516,
		TEXTURE_CUBE_MAP_NEGATIVE_Y      = 0x8518,
		TEXTURE_CUBE_MAP_NEGATIVE_Z      = 0x851A,
		TEXTURE_CUBE_MAP_POSITIVE_X      = 0x8515,
		TEXTURE_CUBE_MAP_POSITIVE_Y      = 0x8517,
		TEXTURE_CUBE_MAP_POSITIVE_Z      = 0x8519,
		TRANSPOSE_COLOR_MATRIX           = 0x84E6,
		TRANSPOSE_MODELVIEW_MATRIX       = 0x84E3,
		TRANSPOSE_PROJECTION_MATRIX      = 0x84E4,
		TRANSPOSE_TEXTURE_MATRIX         = 0x84E5,
		
		BLEND_COLOR                      = 0x8005,
		BLEND_DST_ALPHA                  = 0x80CA,
		BLEND_DST_RGB                    = 0x80C8,
		BLEND_SRC_ALPHA                  = 0x80CB,
		BLEND_SRC_RGB                    = 0x80C9,
		COLOR_SUM                        = 0x8458,
		COMPARE_R_TO_TEXTURE             = 0x884E,
		CONSTANT_ALPHA                   = 0x8003,
		CONSTANT_COLOR                   = 0x8001,
		CURRENT_FOG_COORDINATE           = 0x8453,
		CURRENT_SECONDARY_COLOR          = 0x8459,
		DECR_WRAP                        = 0x8508,
		DEPTH_COMPONENT16                = 0x81A5,
		DEPTH_COMPONENT24                = 0x81A6,
		DEPTH_COMPONENT32                = 0x81A7,
		DEPTH_TEXTURE_MODE               = 0x884B,
		FOG_COORDINATE                   = 0x8451,
		FOG_COORDINATE_ARRAY             = 0x8457,
		FOG_COORDINATE_ARRAY_POINTER     = 0x8456,
		FOG_COORDINATE_ARRAY_STRIDE      = 0x8455,
		FOG_COORDINATE_ARRAY_TYPE        = 0x8454,
		FOG_COORDINATE_SOURCE            = 0x8450,
		FRAGMENT_DEPTH                   = 0x8452,
		FUNC_ADD                         = 0x8006,
		FUNC_REVERSE_SUBTRACT            = 0x800B,
		FUNC_SUBTRACT                    = 0x800A,
		GENERATE_MIPMAP                  = 0x8191,
		GENERATE_MIPMAP_HINT             = 0x8192,
		INCR_WRAP                        = 0x8507,
		MAX                              = 0x8008,
		MAX_TEXTURE_LOD_BIAS             = 0x84FD,
		MIN                              = 0x8007,
		MIRRORED_REPEAT                  = 0x8370,
		ONE_MINUS_CONSTANT_ALPHA         = 0x8004,
		ONE_MINUS_CONSTANT_COLOR         = 0x8002,
		POINT_DISTANCE_ATTENUATION       = 0x8129,
		POINT_FADE_THRESHOLD_SIZE        = 0x8128,
		POINT_SIZE_MAX                   = 0x8127,
		POINT_SIZE_MIN                   = 0x8126,
		SECONDARY_COLOR_ARRAY            = 0x845E,
		SECONDARY_COLOR_ARRAY_POINTER    = 0x845D,
		SECONDARY_COLOR_ARRAY_SIZE       = 0x845A,
		SECONDARY_COLOR_ARRAY_STRIDE     = 0x845C,
		SECONDARY_COLOR_ARRAY_TYPE       = 0x845B,
		TEXTURE_COMPARE_FUNC             = 0x884D,
		TEXTURE_COMPARE_MODE             = 0x884C,
		TEXTURE_DEPTH_SIZE               = 0x884A,
		TEXTURE_FILTER_CONTROL           = 0x8500,
		TEXTURE_LOD_BIAS                 = 0x8501,
		
		ARRAY_BUFFER                     = 0x8892,
		ARRAY_BUFFER_BINDING             = 0x8894,
		BUFFER_ACCESS                    = 0x88BB,
		BUFFER_MAPPED                    = 0x88BC,
		BUFFER_MAP_POINTER               = 0x88BD,
		BUFFER_SIZE                      = 0x8764,
		BUFFER_USAGE                     = 0x8765,
		COLOR_ARRAY_BUFFER_BINDING       = 0x8898,
		CURRENT_FOG_COORD                = 0x8453,
		CURRENT_QUERY                    = 0x8865,
		DYNAMIC_COPY                     = 0x88EA,
		DYNAMIC_DRAW                     = 0x88E8,
		DYNAMIC_READ                     = 0x88E9,
		EDGE_FLAG_ARRAY_BUFFER_BINDING   = 0x889B,
		ELEMENT_ARRAY_BUFFER             = 0x8893,
		ELEMENT_ARRAY_BUFFER_BINDING     = 0x8895,
		FOG_COORD                        = 0x8451,
		FOG_COORDINATE_ARRAY_BUFFER_BINDING = 0x889D,
		FOG_COORD_ARRAY                  = 0x8457,
		FOG_COORD_ARRAY_BUFFER_BINDING   = 0x889D,
		FOG_COORD_ARRAY_POINTER          = 0x8456,
		FOG_COORD_ARRAY_STRIDE           = 0x8455,
		FOG_COORD_ARRAY_TYPE             = 0x8454,
		FOG_COORD_SRC                    = 0x8450,
		INDEX_ARRAY_BUFFER_BINDING       = 0x8899,
		NORMAL_ARRAY_BUFFER_BINDING      = 0x8897,
		QUERY_COUNTER_BITS               = 0x8864,
		QUERY_RESULT                     = 0x8866,
		QUERY_RESULT_AVAILABLE           = 0x8867,
		READ_ONLY                        = 0x88B8,
		READ_WRITE                       = 0x88BA,
		SAMPLES_PASSED                   = 0x8914,
		SECONDARY_COLOR_ARRAY_BUFFER_BINDING = 0x889C,
		SRC0_ALPHA                       = 0x8588,
		SRC0_RGB                         = 0x8580,
		SRC1_ALPHA                       = 0x8589,
		SRC1_RGB                         = 0x8581,
		SRC2_ALPHA                       = 0x858A,
		SRC2_RGB                         = 0x8582,
		STATIC_COPY                      = 0x88E6,
		STATIC_DRAW                      = 0x88E4,
		STATIC_READ                      = 0x88E5,
		STREAM_COPY                      = 0x88E2,
		STREAM_DRAW                      = 0x88E0,
		STREAM_READ                      = 0x88E1,
		TEXTURE_COORD_ARRAY_BUFFER_BINDING = 0x889A,
		VERTEX_ARRAY_BUFFER_BINDING      = 0x8896,
		VERTEX_ATTRIB_ARRAY_BUFFER_BINDING = 0x889F,
		WEIGHT_ARRAY_BUFFER_BINDING      = 0x889E,
		WRITE_ONLY                       = 0x88B9,
		
		ACTIVE_ATTRIBUTES                = 0x8B89,
		ACTIVE_ATTRIBUTE_MAX_LENGTH      = 0x8B8A,
		ACTIVE_UNIFORMS                  = 0x8B86,
		ACTIVE_UNIFORM_MAX_LENGTH        = 0x8B87,
		ATTACHED_SHADERS                 = 0x8B85,
		BLEND_EQUATION_ALPHA             = 0x883D,
		BLEND_EQUATION_RGB               = 0x8009,
		BOOL                             = 0x8B56,
		BOOL_VEC2                        = 0x8B57,
		BOOL_VEC3                        = 0x8B58,
		BOOL_VEC4                        = 0x8B59,
		COMPILE_STATUS                   = 0x8B81,
		COORD_REPLACE                    = 0x8862,
		CURRENT_PROGRAM                  = 0x8B8D,
		CURRENT_VERTEX_ATTRIB            = 0x8626,
		DELETE_STATUS                    = 0x8B80,
		DRAW_BUFFER0                     = 0x8825,
		DRAW_BUFFER1                     = 0x8826,
		DRAW_BUFFER10                    = 0x882F,
		DRAW_BUFFER11                    = 0x8830,
		DRAW_BUFFER12                    = 0x8831,
		DRAW_BUFFER13                    = 0x8832,
		DRAW_BUFFER14                    = 0x8833,
		DRAW_BUFFER15                    = 0x8834,
		DRAW_BUFFER2                     = 0x8827,
		DRAW_BUFFER3                     = 0x8828,
		DRAW_BUFFER4                     = 0x8829,
		DRAW_BUFFER5                     = 0x882A,
		DRAW_BUFFER6                     = 0x882B,
		DRAW_BUFFER7                     = 0x882C,
		DRAW_BUFFER8                     = 0x882D,
		DRAW_BUFFER9                     = 0x882E,
		FLOAT_MAT2                       = 0x8B5A,
		FLOAT_MAT3                       = 0x8B5B,
		FLOAT_MAT4                       = 0x8B5C,
		FLOAT_VEC2                       = 0x8B50,
		FLOAT_VEC3                       = 0x8B51,
		FLOAT_VEC4                       = 0x8B52,
		FRAGMENT_SHADER                  = 0x8B30,
		FRAGMENT_SHADER_DERIVATIVE_HINT  = 0x8B8B,
		INFO_LOG_LENGTH                  = 0x8B84,
		INT_VEC2                         = 0x8B53,
		INT_VEC3                         = 0x8B54,
		INT_VEC4                         = 0x8B55,
		LINK_STATUS                      = 0x8B82,
		LOWER_LEFT                       = 0x8CA1,
		MAX_COMBINED_TEXTURE_IMAGE_UNITS = 0x8B4D,
		MAX_DRAW_BUFFERS                 = 0x8824,
		MAX_FRAGMENT_UNIFORM_COMPONENTS  = 0x8B49,
		MAX_TEXTURE_COORDS               = 0x8871,
		MAX_TEXTURE_IMAGE_UNITS          = 0x8872,
		MAX_VARYING_FLOATS               = 0x8B4B,
		MAX_VERTEX_ATTRIBS               = 0x8869,
		MAX_VERTEX_TEXTURE_IMAGE_UNITS   = 0x8B4C,
		MAX_VERTEX_UNIFORM_COMPONENTS    = 0x8B4A,
		POINT_SPRITE                     = 0x8861,
		POINT_SPRITE_COORD_ORIGIN        = 0x8CA0,
		SAMPLER_1D                       = 0x8B5D,
		SAMPLER_1D_SHADOW                = 0x8B61,
		SAMPLER_2D                       = 0x8B5E,
		SAMPLER_2D_SHADOW                = 0x8B62,
		SAMPLER_3D                       = 0x8B5F,
		SAMPLER_CUBE                     = 0x8B60,
		SHADER_SOURCE_LENGTH             = 0x8B88,
		SHADER_TYPE                      = 0x8B4F,
		SHADING_LANGUAGE_VERSION         = 0x8B8C,
		STENCIL_BACK_FAIL                = 0x8801,
		STENCIL_BACK_FUNC                = 0x8800,
		STENCIL_BACK_PASS_DEPTH_FAIL     = 0x8802,
		STENCIL_BACK_PASS_DEPTH_PASS     = 0x8803,
		STENCIL_BACK_REF                 = 0x8CA3,
		STENCIL_BACK_VALUE_MASK          = 0x8CA4,
		STENCIL_BACK_WRITEMASK           = 0x8CA5,
		UPPER_LEFT                       = 0x8CA2,
		VALIDATE_STATUS                  = 0x8B83,
		VERTEX_ATTRIB_ARRAY_ENABLED      = 0x8622,
		VERTEX_ATTRIB_ARRAY_NORMALIZED   = 0x886A,
		VERTEX_ATTRIB_ARRAY_POINTER      = 0x8645,
		VERTEX_ATTRIB_ARRAY_SIZE         = 0x8623,
		VERTEX_ATTRIB_ARRAY_STRIDE       = 0x8624,
		VERTEX_ATTRIB_ARRAY_TYPE         = 0x8625,
		VERTEX_PROGRAM_POINT_SIZE        = 0x8642,
		VERTEX_PROGRAM_TWO_SIDE          = 0x8643,
		VERTEX_SHADER                    = 0x8B31,
		
		COMPRESSED_SLUMINANCE            = 0x8C4A,
		COMPRESSED_SLUMINANCE_ALPHA      = 0x8C4B,
		COMPRESSED_SRGB                  = 0x8C48,
		COMPRESSED_SRGB_ALPHA            = 0x8C49,
		CURRENT_RASTER_SECONDARY_COLOR   = 0x845F,
		FLOAT_MAT2x3                     = 0x8B65,
		FLOAT_MAT2x4                     = 0x8B66,
		FLOAT_MAT3x2                     = 0x8B67,
		FLOAT_MAT3x4                     = 0x8B68,
		FLOAT_MAT4x2                     = 0x8B69,
		FLOAT_MAT4x3                     = 0x8B6A,
		PIXEL_PACK_BUFFER                = 0x88EB,
		PIXEL_PACK_BUFFER_BINDING        = 0x88ED,
		PIXEL_UNPACK_BUFFER              = 0x88EC,
		PIXEL_UNPACK_BUFFER_BINDING      = 0x88EF,
		SLUMINANCE                       = 0x8C46,
		SLUMINANCE8                      = 0x8C47,
		SLUMINANCE8_ALPHA8               = 0x8C45,
		SLUMINANCE_ALPHA                 = 0x8C44,
		SRGB                             = 0x8C40,
		SRGB8                            = 0x8C41,
		SRGB8_ALPHA8                     = 0x8C43,
		SRGB_ALPHA                       = 0x8C42,
		
		ALPHA_INTEGER                    = 0x8D97,
		BGRA_INTEGER                     = 0x8D9B,
		BGR_INTEGER                      = 0x8D9A,
		BLUE_INTEGER                     = 0x8D96,
		BUFFER_ACCESS_FLAGS              = 0x911F,
		BUFFER_MAP_LENGTH                = 0x9120,
		BUFFER_MAP_OFFSET                = 0x9121,
		CLAMP_FRAGMENT_COLOR             = 0x891B,
		CLAMP_READ_COLOR                 = 0x891C,
		CLAMP_VERTEX_COLOR               = 0x891A,
		CLIP_DISTANCE0                   = 0x3000,
		CLIP_DISTANCE1                   = 0x3001,
		CLIP_DISTANCE2                   = 0x3002,
		CLIP_DISTANCE3                   = 0x3003,
		CLIP_DISTANCE4                   = 0x3004,
		CLIP_DISTANCE5                   = 0x3005,
		CLIP_DISTANCE6                   = 0x3006,
		CLIP_DISTANCE7                   = 0x3007,
		COLOR_ATTACHMENT0                = 0x8CE0,
		COLOR_ATTACHMENT1                = 0x8CE1,
		COLOR_ATTACHMENT10               = 0x8CEA,
		COLOR_ATTACHMENT11               = 0x8CEB,
		COLOR_ATTACHMENT12               = 0x8CEC,
		COLOR_ATTACHMENT13               = 0x8CED,
		COLOR_ATTACHMENT14               = 0x8CEE,
		COLOR_ATTACHMENT15               = 0x8CEF,
		COLOR_ATTACHMENT16               = 0x8CF0,
		COLOR_ATTACHMENT17               = 0x8CF1,
		COLOR_ATTACHMENT18               = 0x8CF2,
		COLOR_ATTACHMENT19               = 0x8CF3,
		COLOR_ATTACHMENT2                = 0x8CE2,
		COLOR_ATTACHMENT20               = 0x8CF4,
		COLOR_ATTACHMENT21               = 0x8CF5,
		COLOR_ATTACHMENT22               = 0x8CF6,
		COLOR_ATTACHMENT23               = 0x8CF7,
		COLOR_ATTACHMENT24               = 0x8CF8,
		COLOR_ATTACHMENT25               = 0x8CF9,
		COLOR_ATTACHMENT26               = 0x8CFA,
		COLOR_ATTACHMENT27               = 0x8CFB,
		COLOR_ATTACHMENT28               = 0x8CFC,
		COLOR_ATTACHMENT29               = 0x8CFD,
		COLOR_ATTACHMENT3                = 0x8CE3,
		COLOR_ATTACHMENT30               = 0x8CFE,
		COLOR_ATTACHMENT31               = 0x8CFF,
		COLOR_ATTACHMENT4                = 0x8CE4,
		COLOR_ATTACHMENT5                = 0x8CE5,
		COLOR_ATTACHMENT6                = 0x8CE6,
		COLOR_ATTACHMENT7                = 0x8CE7,
		COLOR_ATTACHMENT8                = 0x8CE8,
		COLOR_ATTACHMENT9                = 0x8CE9,
		COMPARE_REF_TO_TEXTURE           = 0x884E,
		COMPRESSED_RED                   = 0x8225,
		COMPRESSED_RED_RGTC1             = 0x8DBB,
		COMPRESSED_RG                    = 0x8226,
		COMPRESSED_RG_RGTC2              = 0x8DBD,
		COMPRESSED_SIGNED_RED_RGTC1      = 0x8DBC,
		COMPRESSED_SIGNED_RG_RGTC2       = 0x8DBE,
		CONTEXT_FLAGS                    = 0x821E,
		CONTEXT_FLAG_FORWARD_COMPATIBLE_BIT = 0x00000001,
		DEPTH24_STENCIL8                 = 0x88F0,
		DEPTH32F_STENCIL8                = 0x8CAD,
		DEPTH_ATTACHMENT                 = 0x8D00,
		DEPTH_COMPONENT32F               = 0x8CAC,
		DEPTH_STENCIL                    = 0x84F9,
		DEPTH_STENCIL_ATTACHMENT         = 0x821A,
		DRAW_FRAMEBUFFER                 = 0x8CA9,
		DRAW_FRAMEBUFFER_BINDING         = 0x8CA6,
		FIXED_ONLY                       = 0x891D,
		FLOAT_32_UNSIGNED_INT_24_8_REV   = 0x8DAD,
		FRAMEBUFFER                      = 0x8D40,
		FRAMEBUFFER_ATTACHMENT_ALPHA_SIZE = 0x8215,
		FRAMEBUFFER_ATTACHMENT_BLUE_SIZE = 0x8214,
		FRAMEBUFFER_ATTACHMENT_COLOR_ENCODING = 0x8210,
		FRAMEBUFFER_ATTACHMENT_COMPONENT_TYPE = 0x8211,
		FRAMEBUFFER_ATTACHMENT_DEPTH_SIZE = 0x8216,
		FRAMEBUFFER_ATTACHMENT_GREEN_SIZE = 0x8213,
		FRAMEBUFFER_ATTACHMENT_OBJECT_NAME = 0x8CD1,
		FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE = 0x8CD0,
		FRAMEBUFFER_ATTACHMENT_RED_SIZE  = 0x8212,
		FRAMEBUFFER_ATTACHMENT_STENCIL_SIZE = 0x8217,
		FRAMEBUFFER_ATTACHMENT_TEXTURE_CUBE_MAP_FACE = 0x8CD3,
		FRAMEBUFFER_ATTACHMENT_TEXTURE_LAYER = 0x8CD4,
		FRAMEBUFFER_ATTACHMENT_TEXTURE_LEVEL = 0x8CD2,
		FRAMEBUFFER_BINDING              = 0x8CA6,
		FRAMEBUFFER_COMPLETE             = 0x8CD5,
		FRAMEBUFFER_DEFAULT              = 0x8218,
		FRAMEBUFFER_INCOMPLETE_ATTACHMENT = 0x8CD6,
		FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER = 0x8CDB,
		FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT = 0x8CD7,
		FRAMEBUFFER_INCOMPLETE_MULTISAMPLE = 0x8D56,
		FRAMEBUFFER_INCOMPLETE_READ_BUFFER = 0x8CDC,
		FRAMEBUFFER_SRGB                 = 0x8DB9,
		FRAMEBUFFER_UNDEFINED            = 0x8219,
		FRAMEBUFFER_UNSUPPORTED          = 0x8CDD,
		GREEN_INTEGER                    = 0x8D95,
		HALF_FLOAT                       = 0x140B,
		INTERLEAVED_ATTRIBS              = 0x8C8C,
		INT_SAMPLER_1D                   = 0x8DC9,
		INT_SAMPLER_1D_ARRAY             = 0x8DCE,
		INT_SAMPLER_2D                   = 0x8DCA,
		INT_SAMPLER_2D_ARRAY             = 0x8DCF,
		INT_SAMPLER_3D                   = 0x8DCB,
		INT_SAMPLER_CUBE                 = 0x8DCC,
		INVALID_FRAMEBUFFER_OPERATION    = 0x0506,
		MAJOR_VERSION                    = 0x821B,
		MAP_FLUSH_EXPLICIT_BIT           = 0x0010,
		MAP_INVALIDATE_BUFFER_BIT        = 0x0008,
		MAP_INVALIDATE_RANGE_BIT         = 0x0004,
		MAP_READ_BIT                     = 0x0001,
		MAP_UNSYNCHRONIZED_BIT           = 0x0020,
		MAP_WRITE_BIT                    = 0x0002,
		MAX_ARRAY_TEXTURE_LAYERS         = 0x88FF,
		MAX_CLIP_DISTANCES               = 0x0D32,
		MAX_COLOR_ATTACHMENTS            = 0x8CDF,
		MAX_PROGRAM_TEXEL_OFFSET         = 0x8905,
		MAX_RENDERBUFFER_SIZE            = 0x84E8,
		MAX_SAMPLES                      = 0x8D57,
		MAX_TRANSFORM_FEEDBACK_INTERLEAVED_COMPONENTS = 0x8C8A,
		MAX_TRANSFORM_FEEDBACK_SEPARATE_ATTRIBS = 0x8C8B,
		MAX_TRANSFORM_FEEDBACK_SEPARATE_COMPONENTS = 0x8C80,
		MAX_VARYING_COMPONENTS           = 0x8B4B,
		MINOR_VERSION                    = 0x821C,
		MIN_PROGRAM_TEXEL_OFFSET         = 0x8904,
		NUM_EXTENSIONS                   = 0x821D,
		PRIMITIVES_GENERATED             = 0x8C87,
		PROXY_TEXTURE_1D_ARRAY           = 0x8C19,
		PROXY_TEXTURE_2D_ARRAY           = 0x8C1B,
		QUERY_BY_REGION_NO_WAIT          = 0x8E16,
		QUERY_BY_REGION_WAIT             = 0x8E15,
		QUERY_NO_WAIT                    = 0x8E14,
		QUERY_WAIT                       = 0x8E13,
		R11F_G11F_B10F                   = 0x8C3A,
		R16                              = 0x822A,
		R16F                             = 0x822D,
		R16I                             = 0x8233,
		R16UI                            = 0x8234,
		R32F                             = 0x822E,
		R32I                             = 0x8235,
		R32UI                            = 0x8236,
		R8                               = 0x8229,
		R8I                              = 0x8231,
		R8UI                             = 0x8232,
		RASTERIZER_DISCARD               = 0x8C89,
		READ_FRAMEBUFFER                 = 0x8CA8,
		READ_FRAMEBUFFER_BINDING         = 0x8CAA,
		RED_INTEGER                      = 0x8D94,
		RENDERBUFFER                     = 0x8D41,
		RENDERBUFFER_ALPHA_SIZE          = 0x8D53,
		RENDERBUFFER_BINDING             = 0x8CA7,
		RENDERBUFFER_BLUE_SIZE           = 0x8D52,
		RENDERBUFFER_DEPTH_SIZE          = 0x8D54,
		RENDERBUFFER_GREEN_SIZE          = 0x8D51,
		RENDERBUFFER_HEIGHT              = 0x8D43,
		RENDERBUFFER_INTERNAL_FORMAT     = 0x8D44,
		RENDERBUFFER_RED_SIZE            = 0x8D50,
		RENDERBUFFER_SAMPLES             = 0x8CAB,
		RENDERBUFFER_STENCIL_SIZE        = 0x8D55,
		RENDERBUFFER_WIDTH               = 0x8D42,
		RG                               = 0x8227,
		RG16                             = 0x822C,
		RG16F                            = 0x822F,
		RG16I                            = 0x8239,
		RG16UI                           = 0x823A,
		RG32F                            = 0x8230,
		RG32I                            = 0x823B,
		RG32UI                           = 0x823C,
		RG8                              = 0x822B,
		RG8I                             = 0x8237,
		RG8UI                            = 0x8238,
		RGB16F                           = 0x881B,
		RGB16I                           = 0x8D89,
		RGB16UI                          = 0x8D77,
		RGB32F                           = 0x8815,
		RGB32I                           = 0x8D83,
		RGB32UI                          = 0x8D71,
		RGB8I                            = 0x8D8F,
		RGB8UI                           = 0x8D7D,
		RGB9_E5                          = 0x8C3D,
		RGBA16F                          = 0x881A,
		RGBA16I                          = 0x8D88,
		RGBA16UI                         = 0x8D76,
		RGBA32F                          = 0x8814,
		RGBA32I                          = 0x8D82,
		RGBA32UI                         = 0x8D70,
		RGBA8I                           = 0x8D8E,
		RGBA8UI                          = 0x8D7C,
		RGBA_INTEGER                     = 0x8D99,
		RGB_INTEGER                      = 0x8D98,
		RG_INTEGER                       = 0x8228,
		SAMPLER_1D_ARRAY                 = 0x8DC0,
		SAMPLER_1D_ARRAY_SHADOW          = 0x8DC3,
		SAMPLER_2D_ARRAY                 = 0x8DC1,
		SAMPLER_2D_ARRAY_SHADOW          = 0x8DC4,
		SAMPLER_CUBE_SHADOW              = 0x8DC5,
		SEPARATE_ATTRIBS                 = 0x8C8D,
		STENCIL_ATTACHMENT               = 0x8D20,
		STENCIL_INDEX1                   = 0x8D46,
		STENCIL_INDEX16                  = 0x8D49,
		STENCIL_INDEX4                   = 0x8D47,
		STENCIL_INDEX8                   = 0x8D48,
		TEXTURE_1D_ARRAY                 = 0x8C18,
		TEXTURE_2D_ARRAY                 = 0x8C1A,
		TEXTURE_ALPHA_TYPE               = 0x8C13,
		TEXTURE_BINDING_1D_ARRAY         = 0x8C1C,
		TEXTURE_BINDING_2D_ARRAY         = 0x8C1D,
		TEXTURE_BLUE_TYPE                = 0x8C12,
		TEXTURE_DEPTH_TYPE               = 0x8C16,
		TEXTURE_GREEN_TYPE               = 0x8C11,
		TEXTURE_RED_TYPE                 = 0x8C10,
		TEXTURE_SHARED_SIZE              = 0x8C3F,
		TEXTURE_STENCIL_SIZE             = 0x88F1,
		TRANSFORM_FEEDBACK_BUFFER        = 0x8C8E,
		TRANSFORM_FEEDBACK_BUFFER_BINDING = 0x8C8F,
		TRANSFORM_FEEDBACK_BUFFER_MODE   = 0x8C7F,
		TRANSFORM_FEEDBACK_BUFFER_SIZE   = 0x8C85,
		TRANSFORM_FEEDBACK_BUFFER_START  = 0x8C84,
		TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN = 0x8C88,
		TRANSFORM_FEEDBACK_VARYINGS      = 0x8C83,
		TRANSFORM_FEEDBACK_VARYING_MAX_LENGTH = 0x8C76,
		UNSIGNED_INT_10F_11F_11F_REV     = 0x8C3B,
		UNSIGNED_INT_24_8                = 0x84FA,
		UNSIGNED_INT_5_9_9_9_REV         = 0x8C3E,
		UNSIGNED_INT_SAMPLER_1D          = 0x8DD1,
		UNSIGNED_INT_SAMPLER_1D_ARRAY    = 0x8DD6,
		UNSIGNED_INT_SAMPLER_2D          = 0x8DD2,
		UNSIGNED_INT_SAMPLER_2D_ARRAY    = 0x8DD7,
		UNSIGNED_INT_SAMPLER_3D          = 0x8DD3,
		UNSIGNED_INT_SAMPLER_CUBE        = 0x8DD4,
		UNSIGNED_INT_VEC2                = 0x8DC6,
		UNSIGNED_INT_VEC3                = 0x8DC7,
		UNSIGNED_INT_VEC4                = 0x8DC8,
		UNSIGNED_NORMALIZED              = 0x8C17,
		VERTEX_ARRAY_BINDING             = 0x85B5,
		VERTEX_ATTRIB_ARRAY_INTEGER      = 0x88FD,
		
		ACTIVE_UNIFORM_BLOCKS            = 0x8A36,
		ACTIVE_UNIFORM_BLOCK_MAX_NAME_LENGTH = 0x8A35,
		COPY_READ_BUFFER                 = 0x8F36,
		COPY_WRITE_BUFFER                = 0x8F37,
		INT_SAMPLER_2D_RECT              = 0x8DCD,
		INT_SAMPLER_BUFFER               = 0x8DD0,
		INVALID_INDEX                    = 0xFFFFFFFF,
		MAX_COMBINED_FRAGMENT_UNIFORM_COMPONENTS = 0x8A33,
		MAX_COMBINED_GEOMETRY_UNIFORM_COMPONENTS = 0x8A32,
		MAX_COMBINED_UNIFORM_BLOCKS      = 0x8A2E,
		MAX_COMBINED_VERTEX_UNIFORM_COMPONENTS = 0x8A31,
		MAX_FRAGMENT_UNIFORM_BLOCKS      = 0x8A2D,
		MAX_GEOMETRY_UNIFORM_BLOCKS      = 0x8A2C,
		MAX_RECTANGLE_TEXTURE_SIZE       = 0x84F8,
		MAX_TEXTURE_BUFFER_SIZE          = 0x8C2B,
		MAX_UNIFORM_BLOCK_SIZE           = 0x8A30,
		MAX_UNIFORM_BUFFER_BINDINGS      = 0x8A2F,
		MAX_VERTEX_UNIFORM_BLOCKS        = 0x8A2B,
		PRIMITIVE_RESTART                = 0x8F9D,
		PRIMITIVE_RESTART_INDEX          = 0x8F9E,
		PROXY_TEXTURE_RECTANGLE          = 0x84F7,
		R16_SNORM                        = 0x8F98,
		R8_SNORM                         = 0x8F94,
		RG16_SNORM                       = 0x8F99,
		RG8_SNORM                        = 0x8F95,
		RGB16_SNORM                      = 0x8F9A,
		RGB8_SNORM                       = 0x8F96,
		RGBA16_SNORM                     = 0x8F9B,
		RGBA8_SNORM                      = 0x8F97,
		SAMPLER_2D_RECT                  = 0x8B63,
		SAMPLER_2D_RECT_SHADOW           = 0x8B64,
		SAMPLER_BUFFER                   = 0x8DC2,
		SIGNED_NORMALIZED                = 0x8F9C,
		TEXTURE_BINDING_BUFFER           = 0x8C2C,
		TEXTURE_BINDING_RECTANGLE        = 0x84F6,
		TEXTURE_BUFFER                   = 0x8C2A,
		TEXTURE_BUFFER_DATA_STORE_BINDING = 0x8C2D,
		TEXTURE_RECTANGLE                = 0x84F5,
		UNIFORM_ARRAY_STRIDE             = 0x8A3C,
		UNIFORM_BLOCK_ACTIVE_UNIFORMS    = 0x8A42,
		UNIFORM_BLOCK_ACTIVE_UNIFORM_INDICES = 0x8A43,
		UNIFORM_BLOCK_BINDING            = 0x8A3F,
		UNIFORM_BLOCK_DATA_SIZE          = 0x8A40,
		UNIFORM_BLOCK_INDEX              = 0x8A3A,
		UNIFORM_BLOCK_NAME_LENGTH        = 0x8A41,
		UNIFORM_BLOCK_REFERENCED_BY_FRAGMENT_SHADER = 0x8A46,
		UNIFORM_BLOCK_REFERENCED_BY_GEOMETRY_SHADER = 0x8A45,
		UNIFORM_BLOCK_REFERENCED_BY_VERTEX_SHADER = 0x8A44,
		UNIFORM_BUFFER                   = 0x8A11,
		UNIFORM_BUFFER_BINDING           = 0x8A28,
		UNIFORM_BUFFER_OFFSET_ALIGNMENT  = 0x8A34,
		UNIFORM_BUFFER_SIZE              = 0x8A2A,
		UNIFORM_BUFFER_START             = 0x8A29,
		UNIFORM_IS_ROW_MAJOR             = 0x8A3E,
		UNIFORM_MATRIX_STRIDE            = 0x8A3D,
		UNIFORM_NAME_LENGTH              = 0x8A39,
		UNIFORM_OFFSET                   = 0x8A3B,
		UNIFORM_SIZE                     = 0x8A38,
		UNIFORM_TYPE                     = 0x8A37,
		UNSIGNED_INT_SAMPLER_2D_RECT     = 0x8DD5,
		UNSIGNED_INT_SAMPLER_BUFFER      = 0x8DD8,
		
	};
	
	namespace _detail
	{
		extern void (CODEGEN_FUNCPTR *GetQueryObjecti64v)(GLuint id, GLenum pname, GLint64 * params);
		extern void (CODEGEN_FUNCPTR *GetQueryObjectui64v)(GLuint id, GLenum pname, GLuint64 * params);
		extern void (CODEGEN_FUNCPTR *QueryCounter)(GLuint id, GLenum target);
		
		
		extern void (CODEGEN_FUNCPTR *DepthRangeArrayv)(GLuint first, GLsizei count, const GLdouble * v);
		extern void (CODEGEN_FUNCPTR *DepthRangeIndexed)(GLuint index, GLdouble n, GLdouble f);
		extern void (CODEGEN_FUNCPTR *GetDoublei_v)(GLenum target, GLuint index, GLdouble * data);
		extern void (CODEGEN_FUNCPTR *GetFloati_v)(GLenum target, GLuint index, GLfloat * data);
		extern void (CODEGEN_FUNCPTR *ScissorArrayv)(GLuint first, GLsizei count, const GLint * v);
		extern void (CODEGEN_FUNCPTR *ScissorIndexed)(GLuint index, GLint left, GLint bottom, GLsizei width, GLsizei height);
		extern void (CODEGEN_FUNCPTR *ScissorIndexedv)(GLuint index, const GLint * v);
		extern void (CODEGEN_FUNCPTR *ViewportArrayv)(GLuint first, GLsizei count, const GLfloat * v);
		extern void (CODEGEN_FUNCPTR *ViewportIndexedf)(GLuint index, GLfloat x, GLfloat y, GLfloat w, GLfloat h);
		extern void (CODEGEN_FUNCPTR *ViewportIndexedfv)(GLuint index, const GLfloat * v);
		
		extern void (CODEGEN_FUNCPTR *GetMultisamplefv)(GLenum pname, GLuint index, GLfloat * val);
		extern void (CODEGEN_FUNCPTR *SampleMaski)(GLuint maskNumber, GLbitfield mask);
		extern void (CODEGEN_FUNCPTR *TexImage2DMultisample)(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations);
		extern void (CODEGEN_FUNCPTR *TexImage3DMultisample)(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations);
		
		extern void (CODEGEN_FUNCPTR *Accum)(GLenum op, GLfloat value);
		extern void (CODEGEN_FUNCPTR *AlphaFunc)(GLenum func, GLfloat ref);
		extern void (CODEGEN_FUNCPTR *Begin)(GLenum mode);
		extern void (CODEGEN_FUNCPTR *Bitmap)(GLsizei width, GLsizei height, GLfloat xorig, GLfloat yorig, GLfloat xmove, GLfloat ymove, const GLubyte * bitmap);
		extern void (CODEGEN_FUNCPTR *BlendFunc)(GLenum sfactor, GLenum dfactor);
		extern void (CODEGEN_FUNCPTR *CallList)(GLuint list);
		extern void (CODEGEN_FUNCPTR *CallLists)(GLsizei n, GLenum type, const void * lists);
		extern void (CODEGEN_FUNCPTR *Clear)(GLbitfield mask);
		extern void (CODEGEN_FUNCPTR *ClearAccum)(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
		extern void (CODEGEN_FUNCPTR *ClearColor)(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
		extern void (CODEGEN_FUNCPTR *ClearDepth)(GLdouble depth);
		extern void (CODEGEN_FUNCPTR *ClearIndex)(GLfloat c);
		extern void (CODEGEN_FUNCPTR *ClearStencil)(GLint s);
		extern void (CODEGEN_FUNCPTR *ClipPlane)(GLenum plane, const GLdouble * equation);
		extern void (CODEGEN_FUNCPTR *Color3b)(GLbyte red, GLbyte green, GLbyte blue);
		extern void (CODEGEN_FUNCPTR *Color3bv)(const GLbyte * v);
		extern void (CODEGEN_FUNCPTR *Color3d)(GLdouble red, GLdouble green, GLdouble blue);
		extern void (CODEGEN_FUNCPTR *Color3dv)(const GLdouble * v);
		extern void (CODEGEN_FUNCPTR *Color3f)(GLfloat red, GLfloat green, GLfloat blue);
		extern void (CODEGEN_FUNCPTR *Color3fv)(const GLfloat * v);
		extern void (CODEGEN_FUNCPTR *Color3i)(GLint red, GLint green, GLint blue);
		extern void (CODEGEN_FUNCPTR *Color3iv)(const GLint * v);
		extern void (CODEGEN_FUNCPTR *Color3s)(GLshort red, GLshort green, GLshort blue);
		extern void (CODEGEN_FUNCPTR *Color3sv)(const GLshort * v);
		extern void (CODEGEN_FUNCPTR *Color3ub)(GLubyte red, GLubyte green, GLubyte blue);
		extern void (CODEGEN_FUNCPTR *Color3ubv)(const GLubyte * v);
		extern void (CODEGEN_FUNCPTR *Color3ui)(GLuint red, GLuint green, GLuint blue);
		extern void (CODEGEN_FUNCPTR *Color3uiv)(const GLuint * v);
		extern void (CODEGEN_FUNCPTR *Color3us)(GLushort red, GLushort green, GLushort blue);
		extern void (CODEGEN_FUNCPTR *Color3usv)(const GLushort * v);
		extern void (CODEGEN_FUNCPTR *Color4b)(GLbyte red, GLbyte green, GLbyte blue, GLbyte alpha);
		extern void (CODEGEN_FUNCPTR *Color4bv)(const GLbyte * v);
		extern void (CODEGEN_FUNCPTR *Color4d)(GLdouble red, GLdouble green, GLdouble blue, GLdouble alpha);
		extern void (CODEGEN_FUNCPTR *Color4dv)(const GLdouble * v);
		extern void (CODEGEN_FUNCPTR *Color4f)(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
		extern void (CODEGEN_FUNCPTR *Color4fv)(const GLfloat * v);
		extern void (CODEGEN_FUNCPTR *Color4i)(GLint red, GLint green, GLint blue, GLint alpha);
		extern void (CODEGEN_FUNCPTR *Color4iv)(const GLint * v);
		extern void (CODEGEN_FUNCPTR *Color4s)(GLshort red, GLshort green, GLshort blue, GLshort alpha);
		extern void (CODEGEN_FUNCPTR *Color4sv)(const GLshort * v);
		extern void (CODEGEN_FUNCPTR *Color4ub)(GLubyte red, GLubyte green, GLubyte blue, GLubyte alpha);
		extern void (CODEGEN_FUNCPTR *Color4ubv)(const GLubyte * v);
		extern void (CODEGEN_FUNCPTR *Color4ui)(GLuint red, GLuint green, GLuint blue, GLuint alpha);
		extern void (CODEGEN_FUNCPTR *Color4uiv)(const GLuint * v);
		extern void (CODEGEN_FUNCPTR *Color4us)(GLushort red, GLushort green, GLushort blue, GLushort alpha);
		extern void (CODEGEN_FUNCPTR *Color4usv)(const GLushort * v);
		extern void (CODEGEN_FUNCPTR *ColorMask)(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha);
		extern void (CODEGEN_FUNCPTR *ColorMaterial)(GLenum face, GLenum mode);
		extern void (CODEGEN_FUNCPTR *CopyPixels)(GLint x, GLint y, GLsizei width, GLsizei height, GLenum type);
		extern void (CODEGEN_FUNCPTR *CullFace)(GLenum mode);
		extern void (CODEGEN_FUNCPTR *DeleteLists)(GLuint list, GLsizei range);
		extern void (CODEGEN_FUNCPTR *DepthFunc)(GLenum func);
		extern void (CODEGEN_FUNCPTR *DepthMask)(GLboolean flag);
		extern void (CODEGEN_FUNCPTR *DepthRange)(GLdouble ren_near, GLdouble ren_far);
		extern void (CODEGEN_FUNCPTR *Disable)(GLenum cap);
		extern void (CODEGEN_FUNCPTR *DrawBuffer)(GLenum buf);
		extern void (CODEGEN_FUNCPTR *DrawPixels)(GLsizei width, GLsizei height, GLenum format, GLenum type, const void * pixels);
		extern void (CODEGEN_FUNCPTR *EdgeFlag)(GLboolean flag);
		extern void (CODEGEN_FUNCPTR *EdgeFlagv)(const GLboolean * flag);
		extern void (CODEGEN_FUNCPTR *Enable)(GLenum cap);
		extern void (CODEGEN_FUNCPTR *End)(void);
		extern void (CODEGEN_FUNCPTR *EndList)(void);
		extern void (CODEGEN_FUNCPTR *EvalCoord1d)(GLdouble u);
		extern void (CODEGEN_FUNCPTR *EvalCoord1dv)(const GLdouble * u);
		extern void (CODEGEN_FUNCPTR *EvalCoord1f)(GLfloat u);
		extern void (CODEGEN_FUNCPTR *EvalCoord1fv)(const GLfloat * u);
		extern void (CODEGEN_FUNCPTR *EvalCoord2d)(GLdouble u, GLdouble v);
		extern void (CODEGEN_FUNCPTR *EvalCoord2dv)(const GLdouble * u);
		extern void (CODEGEN_FUNCPTR *EvalCoord2f)(GLfloat u, GLfloat v);
		extern void (CODEGEN_FUNCPTR *EvalCoord2fv)(const GLfloat * u);
		extern void (CODEGEN_FUNCPTR *EvalMesh1)(GLenum mode, GLint i1, GLint i2);
		extern void (CODEGEN_FUNCPTR *EvalMesh2)(GLenum mode, GLint i1, GLint i2, GLint j1, GLint j2);
		extern void (CODEGEN_FUNCPTR *EvalPoint1)(GLint i);
		extern void (CODEGEN_FUNCPTR *EvalPoint2)(GLint i, GLint j);
		extern void (CODEGEN_FUNCPTR *FeedbackBuffer)(GLsizei size, GLenum type, GLfloat * buffer);
		extern void (CODEGEN_FUNCPTR *Finish)(void);
		extern void (CODEGEN_FUNCPTR *Flush)(void);
		extern void (CODEGEN_FUNCPTR *Fogf)(GLenum pname, GLfloat param);
		extern void (CODEGEN_FUNCPTR *Fogfv)(GLenum pname, const GLfloat * params);
		extern void (CODEGEN_FUNCPTR *Fogi)(GLenum pname, GLint param);
		extern void (CODEGEN_FUNCPTR *Fogiv)(GLenum pname, const GLint * params);
		extern void (CODEGEN_FUNCPTR *FrontFace)(GLenum mode);
		extern void (CODEGEN_FUNCPTR *Frustum)(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble zNear, GLdouble zFar);
		extern GLuint (CODEGEN_FUNCPTR *GenLists)(GLsizei range);
		extern void (CODEGEN_FUNCPTR *GetBooleanv)(GLenum pname, GLboolean * data);
		extern void (CODEGEN_FUNCPTR *GetClipPlane)(GLenum plane, GLdouble * equation);
		extern void (CODEGEN_FUNCPTR *GetDoublev)(GLenum pname, GLdouble * data);
		extern GLenum (CODEGEN_FUNCPTR *GetError)(void);
		extern void (CODEGEN_FUNCPTR *GetFloatv)(GLenum pname, GLfloat * data);
		extern void (CODEGEN_FUNCPTR *GetIntegerv)(GLenum pname, GLint * data);
		extern void (CODEGEN_FUNCPTR *GetLightfv)(GLenum light, GLenum pname, GLfloat * params);
		extern void (CODEGEN_FUNCPTR *GetLightiv)(GLenum light, GLenum pname, GLint * params);
		extern void (CODEGEN_FUNCPTR *GetMapdv)(GLenum target, GLenum query, GLdouble * v);
		extern void (CODEGEN_FUNCPTR *GetMapfv)(GLenum target, GLenum query, GLfloat * v);
		extern void (CODEGEN_FUNCPTR *GetMapiv)(GLenum target, GLenum query, GLint * v);
		extern void (CODEGEN_FUNCPTR *GetMaterialfv)(GLenum face, GLenum pname, GLfloat * params);
		extern void (CODEGEN_FUNCPTR *GetMaterialiv)(GLenum face, GLenum pname, GLint * params);
		extern void (CODEGEN_FUNCPTR *GetPixelMapfv)(GLenum map, GLfloat * values);
		extern void (CODEGEN_FUNCPTR *GetPixelMapuiv)(GLenum map, GLuint * values);
		extern void (CODEGEN_FUNCPTR *GetPixelMapusv)(GLenum map, GLushort * values);
		extern void (CODEGEN_FUNCPTR *GetPolygonStipple)(GLubyte * mask);
		extern const GLubyte * (CODEGEN_FUNCPTR *GetString)(GLenum name);
		extern void (CODEGEN_FUNCPTR *GetTexEnvfv)(GLenum target, GLenum pname, GLfloat * params);
		extern void (CODEGEN_FUNCPTR *GetTexEnviv)(GLenum target, GLenum pname, GLint * params);
		extern void (CODEGEN_FUNCPTR *GetTexGendv)(GLenum coord, GLenum pname, GLdouble * params);
		extern void (CODEGEN_FUNCPTR *GetTexGenfv)(GLenum coord, GLenum pname, GLfloat * params);
		extern void (CODEGEN_FUNCPTR *GetTexGeniv)(GLenum coord, GLenum pname, GLint * params);
		extern void (CODEGEN_FUNCPTR *GetTexImage)(GLenum target, GLint level, GLenum format, GLenum type, void * pixels);
		extern void (CODEGEN_FUNCPTR *GetTexLevelParameterfv)(GLenum target, GLint level, GLenum pname, GLfloat * params);
		extern void (CODEGEN_FUNCPTR *GetTexLevelParameteriv)(GLenum target, GLint level, GLenum pname, GLint * params);
		extern void (CODEGEN_FUNCPTR *GetTexParameterfv)(GLenum target, GLenum pname, GLfloat * params);
		extern void (CODEGEN_FUNCPTR *GetTexParameteriv)(GLenum target, GLenum pname, GLint * params);
		extern void (CODEGEN_FUNCPTR *Hint)(GLenum target, GLenum mode);
		extern void (CODEGEN_FUNCPTR *IndexMask)(GLuint mask);
		extern void (CODEGEN_FUNCPTR *Indexd)(GLdouble c);
		extern void (CODEGEN_FUNCPTR *Indexdv)(const GLdouble * c);
		extern void (CODEGEN_FUNCPTR *Indexf)(GLfloat c);
		extern void (CODEGEN_FUNCPTR *Indexfv)(const GLfloat * c);
		extern void (CODEGEN_FUNCPTR *Indexi)(GLint c);
		extern void (CODEGEN_FUNCPTR *Indexiv)(const GLint * c);
		extern void (CODEGEN_FUNCPTR *Indexs)(GLshort c);
		extern void (CODEGEN_FUNCPTR *Indexsv)(const GLshort * c);
		extern void (CODEGEN_FUNCPTR *InitNames)(void);
		extern GLboolean (CODEGEN_FUNCPTR *IsEnabled)(GLenum cap);
		extern GLboolean (CODEGEN_FUNCPTR *IsList)(GLuint list);
		extern void (CODEGEN_FUNCPTR *LightModelf)(GLenum pname, GLfloat param);
		extern void (CODEGEN_FUNCPTR *LightModelfv)(GLenum pname, const GLfloat * params);
		extern void (CODEGEN_FUNCPTR *LightModeli)(GLenum pname, GLint param);
		extern void (CODEGEN_FUNCPTR *LightModeliv)(GLenum pname, const GLint * params);
		extern void (CODEGEN_FUNCPTR *Lightf)(GLenum light, GLenum pname, GLfloat param);
		extern void (CODEGEN_FUNCPTR *Lightfv)(GLenum light, GLenum pname, const GLfloat * params);
		extern void (CODEGEN_FUNCPTR *Lighti)(GLenum light, GLenum pname, GLint param);
		extern void (CODEGEN_FUNCPTR *Lightiv)(GLenum light, GLenum pname, const GLint * params);
		extern void (CODEGEN_FUNCPTR *LineStipple)(GLint factor, GLushort pattern);
		extern void (CODEGEN_FUNCPTR *LineWidth)(GLfloat width);
		extern void (CODEGEN_FUNCPTR *ListBase)(GLuint base);
		extern void (CODEGEN_FUNCPTR *LoadIdentity)(void);
		extern void (CODEGEN_FUNCPTR *LoadMatrixd)(const GLdouble * m);
		extern void (CODEGEN_FUNCPTR *LoadMatrixf)(const GLfloat * m);
		extern void (CODEGEN_FUNCPTR *LoadName)(GLuint name);
		extern void (CODEGEN_FUNCPTR *LogicOp)(GLenum opcode);
		extern void (CODEGEN_FUNCPTR *Map1d)(GLenum target, GLdouble u1, GLdouble u2, GLint stride, GLint order, const GLdouble * points);
		extern void (CODEGEN_FUNCPTR *Map1f)(GLenum target, GLfloat u1, GLfloat u2, GLint stride, GLint order, const GLfloat * points);
		extern void (CODEGEN_FUNCPTR *Map2d)(GLenum target, GLdouble u1, GLdouble u2, GLint ustride, GLint uorder, GLdouble v1, GLdouble v2, GLint vstride, GLint vorder, const GLdouble * points);
		extern void (CODEGEN_FUNCPTR *Map2f)(GLenum target, GLfloat u1, GLfloat u2, GLint ustride, GLint uorder, GLfloat v1, GLfloat v2, GLint vstride, GLint vorder, const GLfloat * points);
		extern void (CODEGEN_FUNCPTR *MapGrid1d)(GLint un, GLdouble u1, GLdouble u2);
		extern void (CODEGEN_FUNCPTR *MapGrid1f)(GLint un, GLfloat u1, GLfloat u2);
		extern void (CODEGEN_FUNCPTR *MapGrid2d)(GLint un, GLdouble u1, GLdouble u2, GLint vn, GLdouble v1, GLdouble v2);
		extern void (CODEGEN_FUNCPTR *MapGrid2f)(GLint un, GLfloat u1, GLfloat u2, GLint vn, GLfloat v1, GLfloat v2);
		extern void (CODEGEN_FUNCPTR *Materialf)(GLenum face, GLenum pname, GLfloat param);
		extern void (CODEGEN_FUNCPTR *Materialfv)(GLenum face, GLenum pname, const GLfloat * params);
		extern void (CODEGEN_FUNCPTR *Materiali)(GLenum face, GLenum pname, GLint param);
		extern void (CODEGEN_FUNCPTR *Materialiv)(GLenum face, GLenum pname, const GLint * params);
		extern void (CODEGEN_FUNCPTR *MatrixMode)(GLenum mode);
		extern void (CODEGEN_FUNCPTR *MultMatrixd)(const GLdouble * m);
		extern void (CODEGEN_FUNCPTR *MultMatrixf)(const GLfloat * m);
		extern void (CODEGEN_FUNCPTR *NewList)(GLuint list, GLenum mode);
		extern void (CODEGEN_FUNCPTR *Normal3b)(GLbyte nx, GLbyte ny, GLbyte nz);
		extern void (CODEGEN_FUNCPTR *Normal3bv)(const GLbyte * v);
		extern void (CODEGEN_FUNCPTR *Normal3d)(GLdouble nx, GLdouble ny, GLdouble nz);
		extern void (CODEGEN_FUNCPTR *Normal3dv)(const GLdouble * v);
		extern void (CODEGEN_FUNCPTR *Normal3f)(GLfloat nx, GLfloat ny, GLfloat nz);
		extern void (CODEGEN_FUNCPTR *Normal3fv)(const GLfloat * v);
		extern void (CODEGEN_FUNCPTR *Normal3i)(GLint nx, GLint ny, GLint nz);
		extern void (CODEGEN_FUNCPTR *Normal3iv)(const GLint * v);
		extern void (CODEGEN_FUNCPTR *Normal3s)(GLshort nx, GLshort ny, GLshort nz);
		extern void (CODEGEN_FUNCPTR *Normal3sv)(const GLshort * v);
		extern void (CODEGEN_FUNCPTR *Ortho)(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble zNear, GLdouble zFar);
		extern void (CODEGEN_FUNCPTR *PassThrough)(GLfloat token);
		extern void (CODEGEN_FUNCPTR *PixelMapfv)(GLenum map, GLsizei mapsize, const GLfloat * values);
		extern void (CODEGEN_FUNCPTR *PixelMapuiv)(GLenum map, GLsizei mapsize, const GLuint * values);
		extern void (CODEGEN_FUNCPTR *PixelMapusv)(GLenum map, GLsizei mapsize, const GLushort * values);
		extern void (CODEGEN_FUNCPTR *PixelStoref)(GLenum pname, GLfloat param);
		extern void (CODEGEN_FUNCPTR *PixelStorei)(GLenum pname, GLint param);
		extern void (CODEGEN_FUNCPTR *PixelTransferf)(GLenum pname, GLfloat param);
		extern void (CODEGEN_FUNCPTR *PixelTransferi)(GLenum pname, GLint param);
		extern void (CODEGEN_FUNCPTR *PixelZoom)(GLfloat xfactor, GLfloat yfactor);
		extern void (CODEGEN_FUNCPTR *PointSize)(GLfloat size);
		extern void (CODEGEN_FUNCPTR *PolygonMode)(GLenum face, GLenum mode);
		extern void (CODEGEN_FUNCPTR *PolygonStipple)(const GLubyte * mask);
		extern void (CODEGEN_FUNCPTR *PopAttrib)(void);
		extern void (CODEGEN_FUNCPTR *PopMatrix)(void);
		extern void (CODEGEN_FUNCPTR *PopName)(void);
		extern void (CODEGEN_FUNCPTR *PushAttrib)(GLbitfield mask);
		extern void (CODEGEN_FUNCPTR *PushMatrix)(void);
		extern void (CODEGEN_FUNCPTR *PushName)(GLuint name);
		extern void (CODEGEN_FUNCPTR *RasterPos2d)(GLdouble x, GLdouble y);
		extern void (CODEGEN_FUNCPTR *RasterPos2dv)(const GLdouble * v);
		extern void (CODEGEN_FUNCPTR *RasterPos2f)(GLfloat x, GLfloat y);
		extern void (CODEGEN_FUNCPTR *RasterPos2fv)(const GLfloat * v);
		extern void (CODEGEN_FUNCPTR *RasterPos2i)(GLint x, GLint y);
		extern void (CODEGEN_FUNCPTR *RasterPos2iv)(const GLint * v);
		extern void (CODEGEN_FUNCPTR *RasterPos2s)(GLshort x, GLshort y);
		extern void (CODEGEN_FUNCPTR *RasterPos2sv)(const GLshort * v);
		extern void (CODEGEN_FUNCPTR *RasterPos3d)(GLdouble x, GLdouble y, GLdouble z);
		extern void (CODEGEN_FUNCPTR *RasterPos3dv)(const GLdouble * v);
		extern void (CODEGEN_FUNCPTR *RasterPos3f)(GLfloat x, GLfloat y, GLfloat z);
		extern void (CODEGEN_FUNCPTR *RasterPos3fv)(const GLfloat * v);
		extern void (CODEGEN_FUNCPTR *RasterPos3i)(GLint x, GLint y, GLint z);
		extern void (CODEGEN_FUNCPTR *RasterPos3iv)(const GLint * v);
		extern void (CODEGEN_FUNCPTR *RasterPos3s)(GLshort x, GLshort y, GLshort z);
		extern void (CODEGEN_FUNCPTR *RasterPos3sv)(const GLshort * v);
		extern void (CODEGEN_FUNCPTR *RasterPos4d)(GLdouble x, GLdouble y, GLdouble z, GLdouble w);
		extern void (CODEGEN_FUNCPTR *RasterPos4dv)(const GLdouble * v);
		extern void (CODEGEN_FUNCPTR *RasterPos4f)(GLfloat x, GLfloat y, GLfloat z, GLfloat w);
		extern void (CODEGEN_FUNCPTR *RasterPos4fv)(const GLfloat * v);
		extern void (CODEGEN_FUNCPTR *RasterPos4i)(GLint x, GLint y, GLint z, GLint w);
		extern void (CODEGEN_FUNCPTR *RasterPos4iv)(const GLint * v);
		extern void (CODEGEN_FUNCPTR *RasterPos4s)(GLshort x, GLshort y, GLshort z, GLshort w);
		extern void (CODEGEN_FUNCPTR *RasterPos4sv)(const GLshort * v);
		extern void (CODEGEN_FUNCPTR *ReadBuffer)(GLenum src);
		extern void (CODEGEN_FUNCPTR *ReadPixels)(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, void * pixels);
		extern void (CODEGEN_FUNCPTR *Rectd)(GLdouble x1, GLdouble y1, GLdouble x2, GLdouble y2);
		extern void (CODEGEN_FUNCPTR *Rectdv)(const GLdouble * v1, const GLdouble * v2);
		extern void (CODEGEN_FUNCPTR *Rectf)(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2);
		extern void (CODEGEN_FUNCPTR *Rectfv)(const GLfloat * v1, const GLfloat * v2);
		extern void (CODEGEN_FUNCPTR *Recti)(GLint x1, GLint y1, GLint x2, GLint y2);
		extern void (CODEGEN_FUNCPTR *Rectiv)(const GLint * v1, const GLint * v2);
		extern void (CODEGEN_FUNCPTR *Rects)(GLshort x1, GLshort y1, GLshort x2, GLshort y2);
		extern void (CODEGEN_FUNCPTR *Rectsv)(const GLshort * v1, const GLshort * v2);
		extern GLint (CODEGEN_FUNCPTR *RenderMode)(GLenum mode);
		extern void (CODEGEN_FUNCPTR *Rotated)(GLdouble angle, GLdouble x, GLdouble y, GLdouble z);
		extern void (CODEGEN_FUNCPTR *Rotatef)(GLfloat angle, GLfloat x, GLfloat y, GLfloat z);
		extern void (CODEGEN_FUNCPTR *Scaled)(GLdouble x, GLdouble y, GLdouble z);
		extern void (CODEGEN_FUNCPTR *Scalef)(GLfloat x, GLfloat y, GLfloat z);
		extern void (CODEGEN_FUNCPTR *Scissor)(GLint x, GLint y, GLsizei width, GLsizei height);
		extern void (CODEGEN_FUNCPTR *SelectBuffer)(GLsizei size, GLuint * buffer);
		extern void (CODEGEN_FUNCPTR *ShadeModel)(GLenum mode);
		extern void (CODEGEN_FUNCPTR *StencilFunc)(GLenum func, GLint ref, GLuint mask);
		extern void (CODEGEN_FUNCPTR *StencilMask)(GLuint mask);
		extern void (CODEGEN_FUNCPTR *StencilOp)(GLenum fail, GLenum zfail, GLenum zpass);
		extern void (CODEGEN_FUNCPTR *TexCoord1d)(GLdouble s);
		extern void (CODEGEN_FUNCPTR *TexCoord1dv)(const GLdouble * v);
		extern void (CODEGEN_FUNCPTR *TexCoord1f)(GLfloat s);
		extern void (CODEGEN_FUNCPTR *TexCoord1fv)(const GLfloat * v);
		extern void (CODEGEN_FUNCPTR *TexCoord1i)(GLint s);
		extern void (CODEGEN_FUNCPTR *TexCoord1iv)(const GLint * v);
		extern void (CODEGEN_FUNCPTR *TexCoord1s)(GLshort s);
		extern void (CODEGEN_FUNCPTR *TexCoord1sv)(const GLshort * v);
		extern void (CODEGEN_FUNCPTR *TexCoord2d)(GLdouble s, GLdouble t);
		extern void (CODEGEN_FUNCPTR *TexCoord2dv)(const GLdouble * v);
		extern void (CODEGEN_FUNCPTR *TexCoord2f)(GLfloat s, GLfloat t);
		extern void (CODEGEN_FUNCPTR *TexCoord2fv)(const GLfloat * v);
		extern void (CODEGEN_FUNCPTR *TexCoord2i)(GLint s, GLint t);
		extern void (CODEGEN_FUNCPTR *TexCoord2iv)(const GLint * v);
		extern void (CODEGEN_FUNCPTR *TexCoord2s)(GLshort s, GLshort t);
		extern void (CODEGEN_FUNCPTR *TexCoord2sv)(const GLshort * v);
		extern void (CODEGEN_FUNCPTR *TexCoord3d)(GLdouble s, GLdouble t, GLdouble r);
		extern void (CODEGEN_FUNCPTR *TexCoord3dv)(const GLdouble * v);
		extern void (CODEGEN_FUNCPTR *TexCoord3f)(GLfloat s, GLfloat t, GLfloat r);
		extern void (CODEGEN_FUNCPTR *TexCoord3fv)(const GLfloat * v);
		extern void (CODEGEN_FUNCPTR *TexCoord3i)(GLint s, GLint t, GLint r);
		extern void (CODEGEN_FUNCPTR *TexCoord3iv)(const GLint * v);
		extern void (CODEGEN_FUNCPTR *TexCoord3s)(GLshort s, GLshort t, GLshort r);
		extern void (CODEGEN_FUNCPTR *TexCoord3sv)(const GLshort * v);
		extern void (CODEGEN_FUNCPTR *TexCoord4d)(GLdouble s, GLdouble t, GLdouble r, GLdouble q);
		extern void (CODEGEN_FUNCPTR *TexCoord4dv)(const GLdouble * v);
		extern void (CODEGEN_FUNCPTR *TexCoord4f)(GLfloat s, GLfloat t, GLfloat r, GLfloat q);
		extern void (CODEGEN_FUNCPTR *TexCoord4fv)(const GLfloat * v);
		extern void (CODEGEN_FUNCPTR *TexCoord4i)(GLint s, GLint t, GLint r, GLint q);
		extern void (CODEGEN_FUNCPTR *TexCoord4iv)(const GLint * v);
		extern void (CODEGEN_FUNCPTR *TexCoord4s)(GLshort s, GLshort t, GLshort r, GLshort q);
		extern void (CODEGEN_FUNCPTR *TexCoord4sv)(const GLshort * v);
		extern void (CODEGEN_FUNCPTR *TexEnvf)(GLenum target, GLenum pname, GLfloat param);
		extern void (CODEGEN_FUNCPTR *TexEnvfv)(GLenum target, GLenum pname, const GLfloat * params);
		extern void (CODEGEN_FUNCPTR *TexEnvi)(GLenum target, GLenum pname, GLint param);
		extern void (CODEGEN_FUNCPTR *TexEnviv)(GLenum target, GLenum pname, const GLint * params);
		extern void (CODEGEN_FUNCPTR *TexGend)(GLenum coord, GLenum pname, GLdouble param);
		extern void (CODEGEN_FUNCPTR *TexGendv)(GLenum coord, GLenum pname, const GLdouble * params);
		extern void (CODEGEN_FUNCPTR *TexGenf)(GLenum coord, GLenum pname, GLfloat param);
		extern void (CODEGEN_FUNCPTR *TexGenfv)(GLenum coord, GLenum pname, const GLfloat * params);
		extern void (CODEGEN_FUNCPTR *TexGeni)(GLenum coord, GLenum pname, GLint param);
		extern void (CODEGEN_FUNCPTR *TexGeniv)(GLenum coord, GLenum pname, const GLint * params);
		extern void (CODEGEN_FUNCPTR *TexImage1D)(GLenum target, GLint level, GLint internalformat, GLsizei width, GLint border, GLenum format, GLenum type, const void * pixels);
		extern void (CODEGEN_FUNCPTR *TexImage2D)(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const void * pixels);
		extern void (CODEGEN_FUNCPTR *TexParameterf)(GLenum target, GLenum pname, GLfloat param);
		extern void (CODEGEN_FUNCPTR *TexParameterfv)(GLenum target, GLenum pname, const GLfloat * params);
		extern void (CODEGEN_FUNCPTR *TexParameteri)(GLenum target, GLenum pname, GLint param);
		extern void (CODEGEN_FUNCPTR *TexParameteriv)(GLenum target, GLenum pname, const GLint * params);
		extern void (CODEGEN_FUNCPTR *Translated)(GLdouble x, GLdouble y, GLdouble z);
		extern void (CODEGEN_FUNCPTR *Translatef)(GLfloat x, GLfloat y, GLfloat z);
		extern void (CODEGEN_FUNCPTR *Vertex2d)(GLdouble x, GLdouble y);
		extern void (CODEGEN_FUNCPTR *Vertex2dv)(const GLdouble * v);
		extern void (CODEGEN_FUNCPTR *Vertex2f)(GLfloat x, GLfloat y);
		extern void (CODEGEN_FUNCPTR *Vertex2fv)(const GLfloat * v);
		extern void (CODEGEN_FUNCPTR *Vertex2i)(GLint x, GLint y);
		extern void (CODEGEN_FUNCPTR *Vertex2iv)(const GLint * v);
		extern void (CODEGEN_FUNCPTR *Vertex2s)(GLshort x, GLshort y);
		extern void (CODEGEN_FUNCPTR *Vertex2sv)(const GLshort * v);
		extern void (CODEGEN_FUNCPTR *Vertex3d)(GLdouble x, GLdouble y, GLdouble z);
		extern void (CODEGEN_FUNCPTR *Vertex3dv)(const GLdouble * v);
		extern void (CODEGEN_FUNCPTR *Vertex3f)(GLfloat x, GLfloat y, GLfloat z);
		extern void (CODEGEN_FUNCPTR *Vertex3fv)(const GLfloat * v);
		extern void (CODEGEN_FUNCPTR *Vertex3i)(GLint x, GLint y, GLint z);
		extern void (CODEGEN_FUNCPTR *Vertex3iv)(const GLint * v);
		extern void (CODEGEN_FUNCPTR *Vertex3s)(GLshort x, GLshort y, GLshort z);
		extern void (CODEGEN_FUNCPTR *Vertex3sv)(const GLshort * v);
		extern void (CODEGEN_FUNCPTR *Vertex4d)(GLdouble x, GLdouble y, GLdouble z, GLdouble w);
		extern void (CODEGEN_FUNCPTR *Vertex4dv)(const GLdouble * v);
		extern void (CODEGEN_FUNCPTR *Vertex4f)(GLfloat x, GLfloat y, GLfloat z, GLfloat w);
		extern void (CODEGEN_FUNCPTR *Vertex4fv)(const GLfloat * v);
		extern void (CODEGEN_FUNCPTR *Vertex4i)(GLint x, GLint y, GLint z, GLint w);
		extern void (CODEGEN_FUNCPTR *Vertex4iv)(const GLint * v);
		extern void (CODEGEN_FUNCPTR *Vertex4s)(GLshort x, GLshort y, GLshort z, GLshort w);
		extern void (CODEGEN_FUNCPTR *Vertex4sv)(const GLshort * v);
		extern void (CODEGEN_FUNCPTR *Viewport)(GLint x, GLint y, GLsizei width, GLsizei height);
		
		extern GLboolean (CODEGEN_FUNCPTR *AreTexturesResident)(GLsizei n, const GLuint * textures, GLboolean * residences);
		extern void (CODEGEN_FUNCPTR *ArrayElement)(GLint i);
		extern void (CODEGEN_FUNCPTR *BindTexture)(GLenum target, GLuint texture);
		extern void (CODEGEN_FUNCPTR *ColorPointer)(GLint size, GLenum type, GLsizei stride, const void * pointer);
		extern void (CODEGEN_FUNCPTR *CopyTexImage1D)(GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLint border);
		extern void (CODEGEN_FUNCPTR *CopyTexImage2D)(GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border);
		extern void (CODEGEN_FUNCPTR *CopyTexSubImage1D)(GLenum target, GLint level, GLint xoffset, GLint x, GLint y, GLsizei width);
		extern void (CODEGEN_FUNCPTR *CopyTexSubImage2D)(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height);
		extern void (CODEGEN_FUNCPTR *DeleteTextures)(GLsizei n, const GLuint * textures);
		extern void (CODEGEN_FUNCPTR *DisableClientState)(GLenum ren_array);
		extern void (CODEGEN_FUNCPTR *DrawArrays)(GLenum mode, GLint first, GLsizei count);
		extern void (CODEGEN_FUNCPTR *DrawElements)(GLenum mode, GLsizei count, GLenum type, const void * indices);
		extern void (CODEGEN_FUNCPTR *EdgeFlagPointer)(GLsizei stride, const void * pointer);
		extern void (CODEGEN_FUNCPTR *EnableClientState)(GLenum ren_array);
		extern void (CODEGEN_FUNCPTR *GenTextures)(GLsizei n, GLuint * textures);
		extern void (CODEGEN_FUNCPTR *GetPointerv)(GLenum pname, void ** params);
		extern void (CODEGEN_FUNCPTR *IndexPointer)(GLenum type, GLsizei stride, const void * pointer);
		extern void (CODEGEN_FUNCPTR *Indexub)(GLubyte c);
		extern void (CODEGEN_FUNCPTR *Indexubv)(const GLubyte * c);
		extern void (CODEGEN_FUNCPTR *InterleavedArrays)(GLenum format, GLsizei stride, const void * pointer);
		extern GLboolean (CODEGEN_FUNCPTR *IsTexture)(GLuint texture);
		extern void (CODEGEN_FUNCPTR *NormalPointer)(GLenum type, GLsizei stride, const void * pointer);
		extern void (CODEGEN_FUNCPTR *PolygonOffset)(GLfloat factor, GLfloat units);
		extern void (CODEGEN_FUNCPTR *PopClientAttrib)(void);
		extern void (CODEGEN_FUNCPTR *PrioritizeTextures)(GLsizei n, const GLuint * textures, const GLfloat * priorities);
		extern void (CODEGEN_FUNCPTR *PushClientAttrib)(GLbitfield mask);
		extern void (CODEGEN_FUNCPTR *TexCoordPointer)(GLint size, GLenum type, GLsizei stride, const void * pointer);
		extern void (CODEGEN_FUNCPTR *TexSubImage1D)(GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, const void * pixels);
		extern void (CODEGEN_FUNCPTR *TexSubImage2D)(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const void * pixels);
		extern void (CODEGEN_FUNCPTR *VertexPointer)(GLint size, GLenum type, GLsizei stride, const void * pointer);
		
		extern void (CODEGEN_FUNCPTR *CopyTexSubImage3D)(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height);
		extern void (CODEGEN_FUNCPTR *DrawRangeElements)(GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const void * indices);
		extern void (CODEGEN_FUNCPTR *TexImage3D)(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const void * pixels);
		extern void (CODEGEN_FUNCPTR *TexSubImage3D)(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void * pixels);
		
		extern void (CODEGEN_FUNCPTR *ActiveTexture)(GLenum texture);
		extern void (CODEGEN_FUNCPTR *ClientActiveTexture)(GLenum texture);
		extern void (CODEGEN_FUNCPTR *CompressedTexImage1D)(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLint border, GLsizei imageSize, const void * data);
		extern void (CODEGEN_FUNCPTR *CompressedTexImage2D)(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const void * data);
		extern void (CODEGEN_FUNCPTR *CompressedTexImage3D)(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, const void * data);
		extern void (CODEGEN_FUNCPTR *CompressedTexSubImage1D)(GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLsizei imageSize, const void * data);
		extern void (CODEGEN_FUNCPTR *CompressedTexSubImage2D)(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const void * data);
		extern void (CODEGEN_FUNCPTR *CompressedTexSubImage3D)(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const void * data);
		extern void (CODEGEN_FUNCPTR *GetCompressedTexImage)(GLenum target, GLint level, void * img);
		extern void (CODEGEN_FUNCPTR *LoadTransposeMatrixd)(const GLdouble * m);
		extern void (CODEGEN_FUNCPTR *LoadTransposeMatrixf)(const GLfloat * m);
		extern void (CODEGEN_FUNCPTR *MultTransposeMatrixd)(const GLdouble * m);
		extern void (CODEGEN_FUNCPTR *MultTransposeMatrixf)(const GLfloat * m);
		extern void (CODEGEN_FUNCPTR *MultiTexCoord1d)(GLenum target, GLdouble s);
		extern void (CODEGEN_FUNCPTR *MultiTexCoord1dv)(GLenum target, const GLdouble * v);
		extern void (CODEGEN_FUNCPTR *MultiTexCoord1f)(GLenum target, GLfloat s);
		extern void (CODEGEN_FUNCPTR *MultiTexCoord1fv)(GLenum target, const GLfloat * v);
		extern void (CODEGEN_FUNCPTR *MultiTexCoord1i)(GLenum target, GLint s);
		extern void (CODEGEN_FUNCPTR *MultiTexCoord1iv)(GLenum target, const GLint * v);
		extern void (CODEGEN_FUNCPTR *MultiTexCoord1s)(GLenum target, GLshort s);
		extern void (CODEGEN_FUNCPTR *MultiTexCoord1sv)(GLenum target, const GLshort * v);
		extern void (CODEGEN_FUNCPTR *MultiTexCoord2d)(GLenum target, GLdouble s, GLdouble t);
		extern void (CODEGEN_FUNCPTR *MultiTexCoord2dv)(GLenum target, const GLdouble * v);
		extern void (CODEGEN_FUNCPTR *MultiTexCoord2f)(GLenum target, GLfloat s, GLfloat t);
		extern void (CODEGEN_FUNCPTR *MultiTexCoord2fv)(GLenum target, const GLfloat * v);
		extern void (CODEGEN_FUNCPTR *MultiTexCoord2i)(GLenum target, GLint s, GLint t);
		extern void (CODEGEN_FUNCPTR *MultiTexCoord2iv)(GLenum target, const GLint * v);
		extern void (CODEGEN_FUNCPTR *MultiTexCoord2s)(GLenum target, GLshort s, GLshort t);
		extern void (CODEGEN_FUNCPTR *MultiTexCoord2sv)(GLenum target, const GLshort * v);
		extern void (CODEGEN_FUNCPTR *MultiTexCoord3d)(GLenum target, GLdouble s, GLdouble t, GLdouble r);
		extern void (CODEGEN_FUNCPTR *MultiTexCoord3dv)(GLenum target, const GLdouble * v);
		extern void (CODEGEN_FUNCPTR *MultiTexCoord3f)(GLenum target, GLfloat s, GLfloat t, GLfloat r);
		extern void (CODEGEN_FUNCPTR *MultiTexCoord3fv)(GLenum target, const GLfloat * v);
		extern void (CODEGEN_FUNCPTR *MultiTexCoord3i)(GLenum target, GLint s, GLint t, GLint r);
		extern void (CODEGEN_FUNCPTR *MultiTexCoord3iv)(GLenum target, const GLint * v);
		extern void (CODEGEN_FUNCPTR *MultiTexCoord3s)(GLenum target, GLshort s, GLshort t, GLshort r);
		extern void (CODEGEN_FUNCPTR *MultiTexCoord3sv)(GLenum target, const GLshort * v);
		extern void (CODEGEN_FUNCPTR *MultiTexCoord4d)(GLenum target, GLdouble s, GLdouble t, GLdouble r, GLdouble q);
		extern void (CODEGEN_FUNCPTR *MultiTexCoord4dv)(GLenum target, const GLdouble * v);
		extern void (CODEGEN_FUNCPTR *MultiTexCoord4f)(GLenum target, GLfloat s, GLfloat t, GLfloat r, GLfloat q);
		extern void (CODEGEN_FUNCPTR *MultiTexCoord4fv)(GLenum target, const GLfloat * v);
		extern void (CODEGEN_FUNCPTR *MultiTexCoord4i)(GLenum target, GLint s, GLint t, GLint r, GLint q);
		extern void (CODEGEN_FUNCPTR *MultiTexCoord4iv)(GLenum target, const GLint * v);
		extern void (CODEGEN_FUNCPTR *MultiTexCoord4s)(GLenum target, GLshort s, GLshort t, GLshort r, GLshort q);
		extern void (CODEGEN_FUNCPTR *MultiTexCoord4sv)(GLenum target, const GLshort * v);
		extern void (CODEGEN_FUNCPTR *SampleCoverage)(GLfloat value, GLboolean invert);
		
		extern void (CODEGEN_FUNCPTR *BlendColor)(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
		extern void (CODEGEN_FUNCPTR *BlendEquation)(GLenum mode);
		extern void (CODEGEN_FUNCPTR *BlendFuncSeparate)(GLenum sfactorRGB, GLenum dfactorRGB, GLenum sfactorAlpha, GLenum dfactorAlpha);
		extern void (CODEGEN_FUNCPTR *FogCoordPointer)(GLenum type, GLsizei stride, const void * pointer);
		extern void (CODEGEN_FUNCPTR *FogCoordd)(GLdouble coord);
		extern void (CODEGEN_FUNCPTR *FogCoorddv)(const GLdouble * coord);
		extern void (CODEGEN_FUNCPTR *FogCoordf)(GLfloat coord);
		extern void (CODEGEN_FUNCPTR *FogCoordfv)(const GLfloat * coord);
		extern void (CODEGEN_FUNCPTR *MultiDrawArrays)(GLenum mode, const GLint * first, const GLsizei * count, GLsizei drawcount);
		extern void (CODEGEN_FUNCPTR *MultiDrawElements)(GLenum mode, const GLsizei * count, GLenum type, const void *const* indices, GLsizei drawcount);
		extern void (CODEGEN_FUNCPTR *PointParameterf)(GLenum pname, GLfloat param);
		extern void (CODEGEN_FUNCPTR *PointParameterfv)(GLenum pname, const GLfloat * params);
		extern void (CODEGEN_FUNCPTR *PointParameteri)(GLenum pname, GLint param);
		extern void (CODEGEN_FUNCPTR *PointParameteriv)(GLenum pname, const GLint * params);
		extern void (CODEGEN_FUNCPTR *SecondaryColor3b)(GLbyte red, GLbyte green, GLbyte blue);
		extern void (CODEGEN_FUNCPTR *SecondaryColor3bv)(const GLbyte * v);
		extern void (CODEGEN_FUNCPTR *SecondaryColor3d)(GLdouble red, GLdouble green, GLdouble blue);
		extern void (CODEGEN_FUNCPTR *SecondaryColor3dv)(const GLdouble * v);
		extern void (CODEGEN_FUNCPTR *SecondaryColor3f)(GLfloat red, GLfloat green, GLfloat blue);
		extern void (CODEGEN_FUNCPTR *SecondaryColor3fv)(const GLfloat * v);
		extern void (CODEGEN_FUNCPTR *SecondaryColor3i)(GLint red, GLint green, GLint blue);
		extern void (CODEGEN_FUNCPTR *SecondaryColor3iv)(const GLint * v);
		extern void (CODEGEN_FUNCPTR *SecondaryColor3s)(GLshort red, GLshort green, GLshort blue);
		extern void (CODEGEN_FUNCPTR *SecondaryColor3sv)(const GLshort * v);
		extern void (CODEGEN_FUNCPTR *SecondaryColor3ub)(GLubyte red, GLubyte green, GLubyte blue);
		extern void (CODEGEN_FUNCPTR *SecondaryColor3ubv)(const GLubyte * v);
		extern void (CODEGEN_FUNCPTR *SecondaryColor3ui)(GLuint red, GLuint green, GLuint blue);
		extern void (CODEGEN_FUNCPTR *SecondaryColor3uiv)(const GLuint * v);
		extern void (CODEGEN_FUNCPTR *SecondaryColor3us)(GLushort red, GLushort green, GLushort blue);
		extern void (CODEGEN_FUNCPTR *SecondaryColor3usv)(const GLushort * v);
		extern void (CODEGEN_FUNCPTR *SecondaryColorPointer)(GLint size, GLenum type, GLsizei stride, const void * pointer);
		extern void (CODEGEN_FUNCPTR *WindowPos2d)(GLdouble x, GLdouble y);
		extern void (CODEGEN_FUNCPTR *WindowPos2dv)(const GLdouble * v);
		extern void (CODEGEN_FUNCPTR *WindowPos2f)(GLfloat x, GLfloat y);
		extern void (CODEGEN_FUNCPTR *WindowPos2fv)(const GLfloat * v);
		extern void (CODEGEN_FUNCPTR *WindowPos2i)(GLint x, GLint y);
		extern void (CODEGEN_FUNCPTR *WindowPos2iv)(const GLint * v);
		extern void (CODEGEN_FUNCPTR *WindowPos2s)(GLshort x, GLshort y);
		extern void (CODEGEN_FUNCPTR *WindowPos2sv)(const GLshort * v);
		extern void (CODEGEN_FUNCPTR *WindowPos3d)(GLdouble x, GLdouble y, GLdouble z);
		extern void (CODEGEN_FUNCPTR *WindowPos3dv)(const GLdouble * v);
		extern void (CODEGEN_FUNCPTR *WindowPos3f)(GLfloat x, GLfloat y, GLfloat z);
		extern void (CODEGEN_FUNCPTR *WindowPos3fv)(const GLfloat * v);
		extern void (CODEGEN_FUNCPTR *WindowPos3i)(GLint x, GLint y, GLint z);
		extern void (CODEGEN_FUNCPTR *WindowPos3iv)(const GLint * v);
		extern void (CODEGEN_FUNCPTR *WindowPos3s)(GLshort x, GLshort y, GLshort z);
		extern void (CODEGEN_FUNCPTR *WindowPos3sv)(const GLshort * v);
		
		extern void (CODEGEN_FUNCPTR *BeginQuery)(GLenum target, GLuint id);
		extern void (CODEGEN_FUNCPTR *BindBuffer)(GLenum target, GLuint buffer);
		extern void (CODEGEN_FUNCPTR *BufferData)(GLenum target, GLsizeiptr size, const void * data, GLenum usage);
		extern void (CODEGEN_FUNCPTR *BufferSubData)(GLenum target, GLintptr offset, GLsizeiptr size, const void * data);
		extern void (CODEGEN_FUNCPTR *DeleteBuffers)(GLsizei n, const GLuint * buffers);
		extern void (CODEGEN_FUNCPTR *DeleteQueries)(GLsizei n, const GLuint * ids);
		extern void (CODEGEN_FUNCPTR *EndQuery)(GLenum target);
		extern void (CODEGEN_FUNCPTR *GenBuffers)(GLsizei n, GLuint * buffers);
		extern void (CODEGEN_FUNCPTR *GenQueries)(GLsizei n, GLuint * ids);
		extern void (CODEGEN_FUNCPTR *GetBufferParameteriv)(GLenum target, GLenum pname, GLint * params);
		extern void (CODEGEN_FUNCPTR *GetBufferPointerv)(GLenum target, GLenum pname, void ** params);
		extern void (CODEGEN_FUNCPTR *GetBufferSubData)(GLenum target, GLintptr offset, GLsizeiptr size, void * data);
		extern void (CODEGEN_FUNCPTR *GetQueryObjectiv)(GLuint id, GLenum pname, GLint * params);
		extern void (CODEGEN_FUNCPTR *GetQueryObjectuiv)(GLuint id, GLenum pname, GLuint * params);
		extern void (CODEGEN_FUNCPTR *GetQueryiv)(GLenum target, GLenum pname, GLint * params);
		extern GLboolean (CODEGEN_FUNCPTR *IsBuffer)(GLuint buffer);
		extern GLboolean (CODEGEN_FUNCPTR *IsQuery)(GLuint id);
		extern void * (CODEGEN_FUNCPTR *MapBuffer)(GLenum target, GLenum access);
		extern GLboolean (CODEGEN_FUNCPTR *UnmapBuffer)(GLenum target);
		
		extern void (CODEGEN_FUNCPTR *AttachShader)(GLuint program, GLuint shader);
		extern void (CODEGEN_FUNCPTR *BindAttribLocation)(GLuint program, GLuint index, const GLchar * name);
		extern void (CODEGEN_FUNCPTR *BlendEquationSeparate)(GLenum modeRGB, GLenum modeAlpha);
		extern void (CODEGEN_FUNCPTR *CompileShader)(GLuint shader);
		extern GLuint (CODEGEN_FUNCPTR *CreateProgram)(void);
		extern GLuint (CODEGEN_FUNCPTR *CreateShader)(GLenum type);
		extern void (CODEGEN_FUNCPTR *DeleteProgram)(GLuint program);
		extern void (CODEGEN_FUNCPTR *DeleteShader)(GLuint shader);
		extern void (CODEGEN_FUNCPTR *DetachShader)(GLuint program, GLuint shader);
		extern void (CODEGEN_FUNCPTR *DisableVertexAttribArray)(GLuint index);
		extern void (CODEGEN_FUNCPTR *DrawBuffers)(GLsizei n, const GLenum * bufs);
		extern void (CODEGEN_FUNCPTR *EnableVertexAttribArray)(GLuint index);
		extern void (CODEGEN_FUNCPTR *GetActiveAttrib)(GLuint program, GLuint index, GLsizei bufSize, GLsizei * length, GLint * size, GLenum * type, GLchar * name);
		extern void (CODEGEN_FUNCPTR *GetActiveUniform)(GLuint program, GLuint index, GLsizei bufSize, GLsizei * length, GLint * size, GLenum * type, GLchar * name);
		extern void (CODEGEN_FUNCPTR *GetAttachedShaders)(GLuint program, GLsizei maxCount, GLsizei * count, GLuint * shaders);
		extern GLint (CODEGEN_FUNCPTR *GetAttribLocation)(GLuint program, const GLchar * name);
		extern void (CODEGEN_FUNCPTR *GetProgramInfoLog)(GLuint program, GLsizei bufSize, GLsizei * length, GLchar * infoLog);
		extern void (CODEGEN_FUNCPTR *GetProgramiv)(GLuint program, GLenum pname, GLint * params);
		extern void (CODEGEN_FUNCPTR *GetShaderInfoLog)(GLuint shader, GLsizei bufSize, GLsizei * length, GLchar * infoLog);
		extern void (CODEGEN_FUNCPTR *GetShaderSource)(GLuint shader, GLsizei bufSize, GLsizei * length, GLchar * source);
		extern void (CODEGEN_FUNCPTR *GetShaderiv)(GLuint shader, GLenum pname, GLint * params);
		extern GLint (CODEGEN_FUNCPTR *GetUniformLocation)(GLuint program, const GLchar * name);
		extern void (CODEGEN_FUNCPTR *GetUniformfv)(GLuint program, GLint location, GLfloat * params);
		extern void (CODEGEN_FUNCPTR *GetUniformiv)(GLuint program, GLint location, GLint * params);
		extern void (CODEGEN_FUNCPTR *GetVertexAttribPointerv)(GLuint index, GLenum pname, void ** pointer);
		extern void (CODEGEN_FUNCPTR *GetVertexAttribdv)(GLuint index, GLenum pname, GLdouble * params);
		extern void (CODEGEN_FUNCPTR *GetVertexAttribfv)(GLuint index, GLenum pname, GLfloat * params);
		extern void (CODEGEN_FUNCPTR *GetVertexAttribiv)(GLuint index, GLenum pname, GLint * params);
		extern GLboolean (CODEGEN_FUNCPTR *IsProgram)(GLuint program);
		extern GLboolean (CODEGEN_FUNCPTR *IsShader)(GLuint shader);
		extern void (CODEGEN_FUNCPTR *LinkProgram)(GLuint program);
		extern void (CODEGEN_FUNCPTR *ShaderSource)(GLuint shader, GLsizei count, const GLchar *const* string, const GLint * length);
		extern void (CODEGEN_FUNCPTR *StencilFuncSeparate)(GLenum face, GLenum func, GLint ref, GLuint mask);
		extern void (CODEGEN_FUNCPTR *StencilMaskSeparate)(GLenum face, GLuint mask);
		extern void (CODEGEN_FUNCPTR *StencilOpSeparate)(GLenum face, GLenum sfail, GLenum dpfail, GLenum dppass);
		extern void (CODEGEN_FUNCPTR *Uniform1f)(GLint location, GLfloat v0);
		extern void (CODEGEN_FUNCPTR *Uniform1fv)(GLint location, GLsizei count, const GLfloat * value);
		extern void (CODEGEN_FUNCPTR *Uniform1i)(GLint location, GLint v0);
		extern void (CODEGEN_FUNCPTR *Uniform1iv)(GLint location, GLsizei count, const GLint * value);
		extern void (CODEGEN_FUNCPTR *Uniform2f)(GLint location, GLfloat v0, GLfloat v1);
		extern void (CODEGEN_FUNCPTR *Uniform2fv)(GLint location, GLsizei count, const GLfloat * value);
		extern void (CODEGEN_FUNCPTR *Uniform2i)(GLint location, GLint v0, GLint v1);
		extern void (CODEGEN_FUNCPTR *Uniform2iv)(GLint location, GLsizei count, const GLint * value);
		extern void (CODEGEN_FUNCPTR *Uniform3f)(GLint location, GLfloat v0, GLfloat v1, GLfloat v2);
		extern void (CODEGEN_FUNCPTR *Uniform3fv)(GLint location, GLsizei count, const GLfloat * value);
		extern void (CODEGEN_FUNCPTR *Uniform3i)(GLint location, GLint v0, GLint v1, GLint v2);
		extern void (CODEGEN_FUNCPTR *Uniform3iv)(GLint location, GLsizei count, const GLint * value);
		extern void (CODEGEN_FUNCPTR *Uniform4f)(GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
		extern void (CODEGEN_FUNCPTR *Uniform4fv)(GLint location, GLsizei count, const GLfloat * value);
		extern void (CODEGEN_FUNCPTR *Uniform4i)(GLint location, GLint v0, GLint v1, GLint v2, GLint v3);
		extern void (CODEGEN_FUNCPTR *Uniform4iv)(GLint location, GLsizei count, const GLint * value);
		extern void (CODEGEN_FUNCPTR *UniformMatrix2fv)(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);
		extern void (CODEGEN_FUNCPTR *UniformMatrix3fv)(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);
		extern void (CODEGEN_FUNCPTR *UniformMatrix4fv)(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);
		extern void (CODEGEN_FUNCPTR *UseProgram)(GLuint program);
		extern void (CODEGEN_FUNCPTR *ValidateProgram)(GLuint program);
		extern void (CODEGEN_FUNCPTR *VertexAttrib1d)(GLuint index, GLdouble x);
		extern void (CODEGEN_FUNCPTR *VertexAttrib1dv)(GLuint index, const GLdouble * v);
		extern void (CODEGEN_FUNCPTR *VertexAttrib1f)(GLuint index, GLfloat x);
		extern void (CODEGEN_FUNCPTR *VertexAttrib1fv)(GLuint index, const GLfloat * v);
		extern void (CODEGEN_FUNCPTR *VertexAttrib1s)(GLuint index, GLshort x);
		extern void (CODEGEN_FUNCPTR *VertexAttrib1sv)(GLuint index, const GLshort * v);
		extern void (CODEGEN_FUNCPTR *VertexAttrib2d)(GLuint index, GLdouble x, GLdouble y);
		extern void (CODEGEN_FUNCPTR *VertexAttrib2dv)(GLuint index, const GLdouble * v);
		extern void (CODEGEN_FUNCPTR *VertexAttrib2f)(GLuint index, GLfloat x, GLfloat y);
		extern void (CODEGEN_FUNCPTR *VertexAttrib2fv)(GLuint index, const GLfloat * v);
		extern void (CODEGEN_FUNCPTR *VertexAttrib2s)(GLuint index, GLshort x, GLshort y);
		extern void (CODEGEN_FUNCPTR *VertexAttrib2sv)(GLuint index, const GLshort * v);
		extern void (CODEGEN_FUNCPTR *VertexAttrib3d)(GLuint index, GLdouble x, GLdouble y, GLdouble z);
		extern void (CODEGEN_FUNCPTR *VertexAttrib3dv)(GLuint index, const GLdouble * v);
		extern void (CODEGEN_FUNCPTR *VertexAttrib3f)(GLuint index, GLfloat x, GLfloat y, GLfloat z);
		extern void (CODEGEN_FUNCPTR *VertexAttrib3fv)(GLuint index, const GLfloat * v);
		extern void (CODEGEN_FUNCPTR *VertexAttrib3s)(GLuint index, GLshort x, GLshort y, GLshort z);
		extern void (CODEGEN_FUNCPTR *VertexAttrib3sv)(GLuint index, const GLshort * v);
		extern void (CODEGEN_FUNCPTR *VertexAttrib4Nbv)(GLuint index, const GLbyte * v);
		extern void (CODEGEN_FUNCPTR *VertexAttrib4Niv)(GLuint index, const GLint * v);
		extern void (CODEGEN_FUNCPTR *VertexAttrib4Nsv)(GLuint index, const GLshort * v);
		extern void (CODEGEN_FUNCPTR *VertexAttrib4Nub)(GLuint index, GLubyte x, GLubyte y, GLubyte z, GLubyte w);
		extern void (CODEGEN_FUNCPTR *VertexAttrib4Nubv)(GLuint index, const GLubyte * v);
		extern void (CODEGEN_FUNCPTR *VertexAttrib4Nuiv)(GLuint index, const GLuint * v);
		extern void (CODEGEN_FUNCPTR *VertexAttrib4Nusv)(GLuint index, const GLushort * v);
		extern void (CODEGEN_FUNCPTR *VertexAttrib4bv)(GLuint index, const GLbyte * v);
		extern void (CODEGEN_FUNCPTR *VertexAttrib4d)(GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w);
		extern void (CODEGEN_FUNCPTR *VertexAttrib4dv)(GLuint index, const GLdouble * v);
		extern void (CODEGEN_FUNCPTR *VertexAttrib4f)(GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
		extern void (CODEGEN_FUNCPTR *VertexAttrib4fv)(GLuint index, const GLfloat * v);
		extern void (CODEGEN_FUNCPTR *VertexAttrib4iv)(GLuint index, const GLint * v);
		extern void (CODEGEN_FUNCPTR *VertexAttrib4s)(GLuint index, GLshort x, GLshort y, GLshort z, GLshort w);
		extern void (CODEGEN_FUNCPTR *VertexAttrib4sv)(GLuint index, const GLshort * v);
		extern void (CODEGEN_FUNCPTR *VertexAttrib4ubv)(GLuint index, const GLubyte * v);
		extern void (CODEGEN_FUNCPTR *VertexAttrib4uiv)(GLuint index, const GLuint * v);
		extern void (CODEGEN_FUNCPTR *VertexAttrib4usv)(GLuint index, const GLushort * v);
		extern void (CODEGEN_FUNCPTR *VertexAttribPointer)(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void * pointer);
		
		extern void (CODEGEN_FUNCPTR *UniformMatrix2x3fv)(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);
		extern void (CODEGEN_FUNCPTR *UniformMatrix2x4fv)(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);
		extern void (CODEGEN_FUNCPTR *UniformMatrix3x2fv)(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);
		extern void (CODEGEN_FUNCPTR *UniformMatrix3x4fv)(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);
		extern void (CODEGEN_FUNCPTR *UniformMatrix4x2fv)(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);
		extern void (CODEGEN_FUNCPTR *UniformMatrix4x3fv)(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);
		
		extern void (CODEGEN_FUNCPTR *BeginConditionalRender)(GLuint id, GLenum mode);
		extern void (CODEGEN_FUNCPTR *BeginTransformFeedback)(GLenum primitiveMode);
		extern void (CODEGEN_FUNCPTR *BindBufferBase)(GLenum target, GLuint index, GLuint buffer);
		extern void (CODEGEN_FUNCPTR *BindBufferRange)(GLenum target, GLuint index, GLuint buffer, GLintptr offset, GLsizeiptr size);
		extern void (CODEGEN_FUNCPTR *BindFragDataLocation)(GLuint program, GLuint color, const GLchar * name);
		extern void (CODEGEN_FUNCPTR *BindFramebuffer)(GLenum target, GLuint framebuffer);
		extern void (CODEGEN_FUNCPTR *BindRenderbuffer)(GLenum target, GLuint renderbuffer);
		extern void (CODEGEN_FUNCPTR *BindVertexArray)(GLuint ren_array);
		extern void (CODEGEN_FUNCPTR *BlitFramebuffer)(GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter);
		extern GLenum (CODEGEN_FUNCPTR *CheckFramebufferStatus)(GLenum target);
		extern void (CODEGEN_FUNCPTR *ClampColor)(GLenum target, GLenum clamp);
		extern void (CODEGEN_FUNCPTR *ClearBufferfi)(GLenum buffer, GLint drawbuffer, GLfloat depth, GLint stencil);
		extern void (CODEGEN_FUNCPTR *ClearBufferfv)(GLenum buffer, GLint drawbuffer, const GLfloat * value);
		extern void (CODEGEN_FUNCPTR *ClearBufferiv)(GLenum buffer, GLint drawbuffer, const GLint * value);
		extern void (CODEGEN_FUNCPTR *ClearBufferuiv)(GLenum buffer, GLint drawbuffer, const GLuint * value);
		extern void (CODEGEN_FUNCPTR *ColorMaski)(GLuint index, GLboolean r, GLboolean g, GLboolean b, GLboolean a);
		extern void (CODEGEN_FUNCPTR *DeleteFramebuffers)(GLsizei n, const GLuint * framebuffers);
		extern void (CODEGEN_FUNCPTR *DeleteRenderbuffers)(GLsizei n, const GLuint * renderbuffers);
		extern void (CODEGEN_FUNCPTR *DeleteVertexArrays)(GLsizei n, const GLuint * arrays);
		extern void (CODEGEN_FUNCPTR *Disablei)(GLenum target, GLuint index);
		extern void (CODEGEN_FUNCPTR *Enablei)(GLenum target, GLuint index);
		extern void (CODEGEN_FUNCPTR *EndConditionalRender)(void);
		extern void (CODEGEN_FUNCPTR *EndTransformFeedback)(void);
		extern void (CODEGEN_FUNCPTR *FlushMappedBufferRange)(GLenum target, GLintptr offset, GLsizeiptr length);
		extern void (CODEGEN_FUNCPTR *FramebufferRenderbuffer)(GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer);
		extern void (CODEGEN_FUNCPTR *FramebufferTexture1D)(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
		extern void (CODEGEN_FUNCPTR *FramebufferTexture2D)(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
		extern void (CODEGEN_FUNCPTR *FramebufferTexture3D)(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLint zoffset);
		extern void (CODEGEN_FUNCPTR *FramebufferTextureLayer)(GLenum target, GLenum attachment, GLuint texture, GLint level, GLint layer);
		extern void (CODEGEN_FUNCPTR *GenFramebuffers)(GLsizei n, GLuint * framebuffers);
		extern void (CODEGEN_FUNCPTR *GenRenderbuffers)(GLsizei n, GLuint * renderbuffers);
		extern void (CODEGEN_FUNCPTR *GenVertexArrays)(GLsizei n, GLuint * arrays);
		extern void (CODEGEN_FUNCPTR *GenerateMipmap)(GLenum target);
		extern void (CODEGEN_FUNCPTR *GetBooleani_v)(GLenum target, GLuint index, GLboolean * data);
		extern GLint (CODEGEN_FUNCPTR *GetFragDataLocation)(GLuint program, const GLchar * name);
		extern void (CODEGEN_FUNCPTR *GetFramebufferAttachmentParameteriv)(GLenum target, GLenum attachment, GLenum pname, GLint * params);
		extern void (CODEGEN_FUNCPTR *GetIntegeri_v)(GLenum target, GLuint index, GLint * data);
		extern void (CODEGEN_FUNCPTR *GetRenderbufferParameteriv)(GLenum target, GLenum pname, GLint * params);
		extern const GLubyte * (CODEGEN_FUNCPTR *GetStringi)(GLenum name, GLuint index);
		extern void (CODEGEN_FUNCPTR *GetTexParameterIiv)(GLenum target, GLenum pname, GLint * params);
		extern void (CODEGEN_FUNCPTR *GetTexParameterIuiv)(GLenum target, GLenum pname, GLuint * params);
		extern void (CODEGEN_FUNCPTR *GetTransformFeedbackVarying)(GLuint program, GLuint index, GLsizei bufSize, GLsizei * length, GLsizei * size, GLenum * type, GLchar * name);
		extern void (CODEGEN_FUNCPTR *GetUniformuiv)(GLuint program, GLint location, GLuint * params);
		extern void (CODEGEN_FUNCPTR *GetVertexAttribIiv)(GLuint index, GLenum pname, GLint * params);
		extern void (CODEGEN_FUNCPTR *GetVertexAttribIuiv)(GLuint index, GLenum pname, GLuint * params);
		extern GLboolean (CODEGEN_FUNCPTR *IsEnabledi)(GLenum target, GLuint index);
		extern GLboolean (CODEGEN_FUNCPTR *IsFramebuffer)(GLuint framebuffer);
		extern GLboolean (CODEGEN_FUNCPTR *IsRenderbuffer)(GLuint renderbuffer);
		extern GLboolean (CODEGEN_FUNCPTR *IsVertexArray)(GLuint ren_array);
		extern void * (CODEGEN_FUNCPTR *MapBufferRange)(GLenum target, GLintptr offset, GLsizeiptr length, GLbitfield access);
		extern void (CODEGEN_FUNCPTR *RenderbufferStorage)(GLenum target, GLenum internalformat, GLsizei width, GLsizei height);
		extern void (CODEGEN_FUNCPTR *RenderbufferStorageMultisample)(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height);
		extern void (CODEGEN_FUNCPTR *TexParameterIiv)(GLenum target, GLenum pname, const GLint * params);
		extern void (CODEGEN_FUNCPTR *TexParameterIuiv)(GLenum target, GLenum pname, const GLuint * params);
		extern void (CODEGEN_FUNCPTR *TransformFeedbackVaryings)(GLuint program, GLsizei count, const GLchar *const* varyings, GLenum bufferMode);
		extern void (CODEGEN_FUNCPTR *Uniform1ui)(GLint location, GLuint v0);
		extern void (CODEGEN_FUNCPTR *Uniform1uiv)(GLint location, GLsizei count, const GLuint * value);
		extern void (CODEGEN_FUNCPTR *Uniform2ui)(GLint location, GLuint v0, GLuint v1);
		extern void (CODEGEN_FUNCPTR *Uniform2uiv)(GLint location, GLsizei count, const GLuint * value);
		extern void (CODEGEN_FUNCPTR *Uniform3ui)(GLint location, GLuint v0, GLuint v1, GLuint v2);
		extern void (CODEGEN_FUNCPTR *Uniform3uiv)(GLint location, GLsizei count, const GLuint * value);
		extern void (CODEGEN_FUNCPTR *Uniform4ui)(GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3);
		extern void (CODEGEN_FUNCPTR *Uniform4uiv)(GLint location, GLsizei count, const GLuint * value);
		extern void (CODEGEN_FUNCPTR *VertexAttribI1i)(GLuint index, GLint x);
		extern void (CODEGEN_FUNCPTR *VertexAttribI1iv)(GLuint index, const GLint * v);
		extern void (CODEGEN_FUNCPTR *VertexAttribI1ui)(GLuint index, GLuint x);
		extern void (CODEGEN_FUNCPTR *VertexAttribI1uiv)(GLuint index, const GLuint * v);
		extern void (CODEGEN_FUNCPTR *VertexAttribI2i)(GLuint index, GLint x, GLint y);
		extern void (CODEGEN_FUNCPTR *VertexAttribI2iv)(GLuint index, const GLint * v);
		extern void (CODEGEN_FUNCPTR *VertexAttribI2ui)(GLuint index, GLuint x, GLuint y);
		extern void (CODEGEN_FUNCPTR *VertexAttribI2uiv)(GLuint index, const GLuint * v);
		extern void (CODEGEN_FUNCPTR *VertexAttribI3i)(GLuint index, GLint x, GLint y, GLint z);
		extern void (CODEGEN_FUNCPTR *VertexAttribI3iv)(GLuint index, const GLint * v);
		extern void (CODEGEN_FUNCPTR *VertexAttribI3ui)(GLuint index, GLuint x, GLuint y, GLuint z);
		extern void (CODEGEN_FUNCPTR *VertexAttribI3uiv)(GLuint index, const GLuint * v);
		extern void (CODEGEN_FUNCPTR *VertexAttribI4bv)(GLuint index, const GLbyte * v);
		extern void (CODEGEN_FUNCPTR *VertexAttribI4i)(GLuint index, GLint x, GLint y, GLint z, GLint w);
		extern void (CODEGEN_FUNCPTR *VertexAttribI4iv)(GLuint index, const GLint * v);
		extern void (CODEGEN_FUNCPTR *VertexAttribI4sv)(GLuint index, const GLshort * v);
		extern void (CODEGEN_FUNCPTR *VertexAttribI4ubv)(GLuint index, const GLubyte * v);
		extern void (CODEGEN_FUNCPTR *VertexAttribI4ui)(GLuint index, GLuint x, GLuint y, GLuint z, GLuint w);
		extern void (CODEGEN_FUNCPTR *VertexAttribI4uiv)(GLuint index, const GLuint * v);
		extern void (CODEGEN_FUNCPTR *VertexAttribI4usv)(GLuint index, const GLushort * v);
		extern void (CODEGEN_FUNCPTR *VertexAttribIPointer)(GLuint index, GLint size, GLenum type, GLsizei stride, const void * pointer);
		
		extern void (CODEGEN_FUNCPTR *CopyBufferSubData)(GLenum readTarget, GLenum writeTarget, GLintptr readOffset, GLintptr writeOffset, GLsizeiptr size);
		extern void (CODEGEN_FUNCPTR *DrawArraysInstanced)(GLenum mode, GLint first, GLsizei count, GLsizei instancecount);
		extern void (CODEGEN_FUNCPTR *DrawElementsInstanced)(GLenum mode, GLsizei count, GLenum type, const void * indices, GLsizei instancecount);
		extern void (CODEGEN_FUNCPTR *GetActiveUniformBlockName)(GLuint program, GLuint uniformBlockIndex, GLsizei bufSize, GLsizei * length, GLchar * uniformBlockName);
		extern void (CODEGEN_FUNCPTR *GetActiveUniformBlockiv)(GLuint program, GLuint uniformBlockIndex, GLenum pname, GLint * params);
		extern void (CODEGEN_FUNCPTR *GetActiveUniformName)(GLuint program, GLuint uniformIndex, GLsizei bufSize, GLsizei * length, GLchar * uniformName);
		extern void (CODEGEN_FUNCPTR *GetActiveUniformsiv)(GLuint program, GLsizei uniformCount, const GLuint * uniformIndices, GLenum pname, GLint * params);
		extern GLuint (CODEGEN_FUNCPTR *GetUniformBlockIndex)(GLuint program, const GLchar * uniformBlockName);
		extern void (CODEGEN_FUNCPTR *GetUniformIndices)(GLuint program, GLsizei uniformCount, const GLchar *const* uniformNames, GLuint * uniformIndices);
		extern void (CODEGEN_FUNCPTR *PrimitiveRestartIndex)(GLuint index);
		extern void (CODEGEN_FUNCPTR *TexBuffer)(GLenum target, GLenum internalformat, GLuint buffer);
		extern void (CODEGEN_FUNCPTR *UniformBlockBinding)(GLuint program, GLuint uniformBlockIndex, GLuint uniformBlockBinding);
		
	} //namespace _detail
	
	inline void GetQueryObjecti64v(GLuint id, GLenum pname, GLint64 * params){_detail::GetQueryObjecti64v(id, pname, params);}
	inline void GetQueryObjectui64v(GLuint id, GLenum pname, GLuint64 * params){_detail::GetQueryObjectui64v(id, pname, params);}
	inline void QueryCounter(GLuint id, GLenum target){_detail::QueryCounter(id, target);}
	
	
	inline void DepthRangeArrayv(GLuint first, GLsizei count, const GLdouble * v){_detail::DepthRangeArrayv(first, count, v);}
	inline void DepthRangeIndexed(GLuint index, GLdouble n, GLdouble f){_detail::DepthRangeIndexed(index, n, f);}
	inline void GetDoublei_v(GLenum target, GLuint index, GLdouble * data){_detail::GetDoublei_v(target, index, data);}
	inline void GetFloati_v(GLenum target, GLuint index, GLfloat * data){_detail::GetFloati_v(target, index, data);}
	inline void ScissorArrayv(GLuint first, GLsizei count, const GLint * v){_detail::ScissorArrayv(first, count, v);}
	inline void ScissorIndexed(GLuint index, GLint left, GLint bottom, GLsizei width, GLsizei height){_detail::ScissorIndexed(index, left, bottom, width, height);}
	inline void ScissorIndexedv(GLuint index, const GLint * v){_detail::ScissorIndexedv(index, v);}
	inline void ViewportArrayv(GLuint first, GLsizei count, const GLfloat * v){_detail::ViewportArrayv(first, count, v);}
	inline void ViewportIndexedf(GLuint index, GLfloat x, GLfloat y, GLfloat w, GLfloat h){_detail::ViewportIndexedf(index, x, y, w, h);}
	inline void ViewportIndexedfv(GLuint index, const GLfloat * v){_detail::ViewportIndexedfv(index, v);}
	
	inline void GetMultisamplefv(GLenum pname, GLuint index, GLfloat * val){_detail::GetMultisamplefv(pname, index, val);}
	inline void SampleMaski(GLuint maskNumber, GLbitfield mask){_detail::SampleMaski(maskNumber, mask);}
	inline void TexImage2DMultisample(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations){_detail::TexImage2DMultisample(target, samples, internalformat, width, height, fixedsamplelocations);}
	inline void TexImage3DMultisample(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations){_detail::TexImage3DMultisample(target, samples, internalformat, width, height, depth, fixedsamplelocations);}
	
	inline void Accum(GLenum op, GLfloat value){_detail::Accum(op, value);}
	inline void AlphaFunc(GLenum func, GLfloat ref){_detail::AlphaFunc(func, ref);}
	inline void Begin(GLenum mode){_detail::Begin(mode);}
	inline void Bitmap(GLsizei width, GLsizei height, GLfloat xorig, GLfloat yorig, GLfloat xmove, GLfloat ymove, const GLubyte * bitmap){_detail::Bitmap(width, height, xorig, yorig, xmove, ymove, bitmap);}
	inline void BlendFunc(GLenum sfactor, GLenum dfactor){_detail::BlendFunc(sfactor, dfactor);}
	inline void CallList(GLuint list){_detail::CallList(list);}
	inline void CallLists(GLsizei n, GLenum type, const void * lists){_detail::CallLists(n, type, lists);}
	inline void Clear(GLbitfield mask){_detail::Clear(mask);}
	inline void ClearAccum(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha){_detail::ClearAccum(red, green, blue, alpha);}
	inline void ClearColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha){_detail::ClearColor(red, green, blue, alpha);}
	inline void ClearDepth(GLdouble depth){_detail::ClearDepth(depth);}
	inline void ClearIndex(GLfloat c){_detail::ClearIndex(c);}
	inline void ClearStencil(GLint s){_detail::ClearStencil(s);}
	inline void ClipPlane(GLenum plane, const GLdouble * equation){_detail::ClipPlane(plane, equation);}
	inline void Color3b(GLbyte red, GLbyte green, GLbyte blue){_detail::Color3b(red, green, blue);}
	inline void Color3bv(const GLbyte * v){_detail::Color3bv(v);}
	inline void Color3d(GLdouble red, GLdouble green, GLdouble blue){_detail::Color3d(red, green, blue);}
	inline void Color3dv(const GLdouble * v){_detail::Color3dv(v);}
	inline void Color3f(GLfloat red, GLfloat green, GLfloat blue){_detail::Color3f(red, green, blue);}
	inline void Color3fv(const GLfloat * v){_detail::Color3fv(v);}
	inline void Color3i(GLint red, GLint green, GLint blue){_detail::Color3i(red, green, blue);}
	inline void Color3iv(const GLint * v){_detail::Color3iv(v);}
	inline void Color3s(GLshort red, GLshort green, GLshort blue){_detail::Color3s(red, green, blue);}
	inline void Color3sv(const GLshort * v){_detail::Color3sv(v);}
	inline void Color3ub(GLubyte red, GLubyte green, GLubyte blue){_detail::Color3ub(red, green, blue);}
	inline void Color3ubv(const GLubyte * v){_detail::Color3ubv(v);}
	inline void Color3ui(GLuint red, GLuint green, GLuint blue){_detail::Color3ui(red, green, blue);}
	inline void Color3uiv(const GLuint * v){_detail::Color3uiv(v);}
	inline void Color3us(GLushort red, GLushort green, GLushort blue){_detail::Color3us(red, green, blue);}
	inline void Color3usv(const GLushort * v){_detail::Color3usv(v);}
	inline void Color4b(GLbyte red, GLbyte green, GLbyte blue, GLbyte alpha){_detail::Color4b(red, green, blue, alpha);}
	inline void Color4bv(const GLbyte * v){_detail::Color4bv(v);}
	inline void Color4d(GLdouble red, GLdouble green, GLdouble blue, GLdouble alpha){_detail::Color4d(red, green, blue, alpha);}
	inline void Color4dv(const GLdouble * v){_detail::Color4dv(v);}
	inline void Color4f(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha){_detail::Color4f(red, green, blue, alpha);}
	inline void Color4fv(const GLfloat * v){_detail::Color4fv(v);}
	inline void Color4i(GLint red, GLint green, GLint blue, GLint alpha){_detail::Color4i(red, green, blue, alpha);}
	inline void Color4iv(const GLint * v){_detail::Color4iv(v);}
	inline void Color4s(GLshort red, GLshort green, GLshort blue, GLshort alpha){_detail::Color4s(red, green, blue, alpha);}
	inline void Color4sv(const GLshort * v){_detail::Color4sv(v);}
	inline void Color4ub(GLubyte red, GLubyte green, GLubyte blue, GLubyte alpha){_detail::Color4ub(red, green, blue, alpha);}
	inline void Color4ubv(const GLubyte * v){_detail::Color4ubv(v);}
	inline void Color4ui(GLuint red, GLuint green, GLuint blue, GLuint alpha){_detail::Color4ui(red, green, blue, alpha);}
	inline void Color4uiv(const GLuint * v){_detail::Color4uiv(v);}
	inline void Color4us(GLushort red, GLushort green, GLushort blue, GLushort alpha){_detail::Color4us(red, green, blue, alpha);}
	inline void Color4usv(const GLushort * v){_detail::Color4usv(v);}
	inline void ColorMask(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha){_detail::ColorMask(red, green, blue, alpha);}
	inline void ColorMaterial(GLenum face, GLenum mode){_detail::ColorMaterial(face, mode);}
	inline void CopyPixels(GLint x, GLint y, GLsizei width, GLsizei height, GLenum type){_detail::CopyPixels(x, y, width, height, type);}
	inline void CullFace(GLenum mode){_detail::CullFace(mode);}
	inline void DeleteLists(GLuint list, GLsizei range){_detail::DeleteLists(list, range);}
	inline void DepthFunc(GLenum func){_detail::DepthFunc(func);}
	inline void DepthMask(GLboolean flag){_detail::DepthMask(flag);}
	inline void DepthRange(GLdouble ren_near, GLdouble ren_far){_detail::DepthRange(ren_near, ren_far);}
	inline void Disable(GLenum cap){_detail::Disable(cap);}
	inline void DrawBuffer(GLenum buf){_detail::DrawBuffer(buf);}
	inline void DrawPixels(GLsizei width, GLsizei height, GLenum format, GLenum type, const void * pixels){_detail::DrawPixels(width, height, format, type, pixels);}
	inline void EdgeFlag(GLboolean flag){_detail::EdgeFlag(flag);}
	inline void EdgeFlagv(const GLboolean * flag){_detail::EdgeFlagv(flag);}
	inline void Enable(GLenum cap){_detail::Enable(cap);}
	inline void End(void){_detail::End();}
	inline void EndList(void){_detail::EndList();}
	inline void EvalCoord1d(GLdouble u){_detail::EvalCoord1d(u);}
	inline void EvalCoord1dv(const GLdouble * u){_detail::EvalCoord1dv(u);}
	inline void EvalCoord1f(GLfloat u){_detail::EvalCoord1f(u);}
	inline void EvalCoord1fv(const GLfloat * u){_detail::EvalCoord1fv(u);}
	inline void EvalCoord2d(GLdouble u, GLdouble v){_detail::EvalCoord2d(u, v);}
	inline void EvalCoord2dv(const GLdouble * u){_detail::EvalCoord2dv(u);}
	inline void EvalCoord2f(GLfloat u, GLfloat v){_detail::EvalCoord2f(u, v);}
	inline void EvalCoord2fv(const GLfloat * u){_detail::EvalCoord2fv(u);}
	inline void EvalMesh1(GLenum mode, GLint i1, GLint i2){_detail::EvalMesh1(mode, i1, i2);}
	inline void EvalMesh2(GLenum mode, GLint i1, GLint i2, GLint j1, GLint j2){_detail::EvalMesh2(mode, i1, i2, j1, j2);}
	inline void EvalPoint1(GLint i){_detail::EvalPoint1(i);}
	inline void EvalPoint2(GLint i, GLint j){_detail::EvalPoint2(i, j);}
	inline void FeedbackBuffer(GLsizei size, GLenum type, GLfloat * buffer){_detail::FeedbackBuffer(size, type, buffer);}
	inline void Finish(void){_detail::Finish();}
	inline void Flush(void){_detail::Flush();}
	inline void Fogf(GLenum pname, GLfloat param){_detail::Fogf(pname, param);}
	inline void Fogfv(GLenum pname, const GLfloat * params){_detail::Fogfv(pname, params);}
	inline void Fogi(GLenum pname, GLint param){_detail::Fogi(pname, param);}
	inline void Fogiv(GLenum pname, const GLint * params){_detail::Fogiv(pname, params);}
	inline void FrontFace(GLenum mode){_detail::FrontFace(mode);}
	inline void Frustum(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble zNear, GLdouble zFar){_detail::Frustum(left, right, bottom, top, zNear, zFar);}
	inline GLuint GenLists(GLsizei range){return _detail::GenLists(range);}
	inline void GetBooleanv(GLenum pname, GLboolean * data){_detail::GetBooleanv(pname, data);}
	inline void GetClipPlane(GLenum plane, GLdouble * equation){_detail::GetClipPlane(plane, equation);}
	inline void GetDoublev(GLenum pname, GLdouble * data){_detail::GetDoublev(pname, data);}
	inline GLenum GetError(void){return _detail::GetError();}
	inline void GetFloatv(GLenum pname, GLfloat * data){_detail::GetFloatv(pname, data);}
	inline void GetIntegerv(GLenum pname, GLint * data){_detail::GetIntegerv(pname, data);}
	inline void GetLightfv(GLenum light, GLenum pname, GLfloat * params){_detail::GetLightfv(light, pname, params);}
	inline void GetLightiv(GLenum light, GLenum pname, GLint * params){_detail::GetLightiv(light, pname, params);}
	inline void GetMapdv(GLenum target, GLenum query, GLdouble * v){_detail::GetMapdv(target, query, v);}
	inline void GetMapfv(GLenum target, GLenum query, GLfloat * v){_detail::GetMapfv(target, query, v);}
	inline void GetMapiv(GLenum target, GLenum query, GLint * v){_detail::GetMapiv(target, query, v);}
	inline void GetMaterialfv(GLenum face, GLenum pname, GLfloat * params){_detail::GetMaterialfv(face, pname, params);}
	inline void GetMaterialiv(GLenum face, GLenum pname, GLint * params){_detail::GetMaterialiv(face, pname, params);}
	inline void GetPixelMapfv(GLenum map, GLfloat * values){_detail::GetPixelMapfv(map, values);}
	inline void GetPixelMapuiv(GLenum map, GLuint * values){_detail::GetPixelMapuiv(map, values);}
	inline void GetPixelMapusv(GLenum map, GLushort * values){_detail::GetPixelMapusv(map, values);}
	inline void GetPolygonStipple(GLubyte * mask){_detail::GetPolygonStipple(mask);}
	inline const GLubyte * GetString(GLenum name){return _detail::GetString(name);}
	inline void GetTexEnvfv(GLenum target, GLenum pname, GLfloat * params){_detail::GetTexEnvfv(target, pname, params);}
	inline void GetTexEnviv(GLenum target, GLenum pname, GLint * params){_detail::GetTexEnviv(target, pname, params);}
	inline void GetTexGendv(GLenum coord, GLenum pname, GLdouble * params){_detail::GetTexGendv(coord, pname, params);}
	inline void GetTexGenfv(GLenum coord, GLenum pname, GLfloat * params){_detail::GetTexGenfv(coord, pname, params);}
	inline void GetTexGeniv(GLenum coord, GLenum pname, GLint * params){_detail::GetTexGeniv(coord, pname, params);}
	inline void GetTexImage(GLenum target, GLint level, GLenum format, GLenum type, void * pixels){_detail::GetTexImage(target, level, format, type, pixels);}
	inline void GetTexLevelParameterfv(GLenum target, GLint level, GLenum pname, GLfloat * params){_detail::GetTexLevelParameterfv(target, level, pname, params);}
	inline void GetTexLevelParameteriv(GLenum target, GLint level, GLenum pname, GLint * params){_detail::GetTexLevelParameteriv(target, level, pname, params);}
	inline void GetTexParameterfv(GLenum target, GLenum pname, GLfloat * params){_detail::GetTexParameterfv(target, pname, params);}
	inline void GetTexParameteriv(GLenum target, GLenum pname, GLint * params){_detail::GetTexParameteriv(target, pname, params);}
	inline void Hint(GLenum target, GLenum mode){_detail::Hint(target, mode);}
	inline void IndexMask(GLuint mask){_detail::IndexMask(mask);}
	inline void Indexd(GLdouble c){_detail::Indexd(c);}
	inline void Indexdv(const GLdouble * c){_detail::Indexdv(c);}
	inline void Indexf(GLfloat c){_detail::Indexf(c);}
	inline void Indexfv(const GLfloat * c){_detail::Indexfv(c);}
	inline void Indexi(GLint c){_detail::Indexi(c);}
	inline void Indexiv(const GLint * c){_detail::Indexiv(c);}
	inline void Indexs(GLshort c){_detail::Indexs(c);}
	inline void Indexsv(const GLshort * c){_detail::Indexsv(c);}
	inline void InitNames(void){_detail::InitNames();}
	inline GLboolean IsEnabled(GLenum cap){return _detail::IsEnabled(cap);}
	inline GLboolean IsList(GLuint list){return _detail::IsList(list);}
	inline void LightModelf(GLenum pname, GLfloat param){_detail::LightModelf(pname, param);}
	inline void LightModelfv(GLenum pname, const GLfloat * params){_detail::LightModelfv(pname, params);}
	inline void LightModeli(GLenum pname, GLint param){_detail::LightModeli(pname, param);}
	inline void LightModeliv(GLenum pname, const GLint * params){_detail::LightModeliv(pname, params);}
	inline void Lightf(GLenum light, GLenum pname, GLfloat param){_detail::Lightf(light, pname, param);}
	inline void Lightfv(GLenum light, GLenum pname, const GLfloat * params){_detail::Lightfv(light, pname, params);}
	inline void Lighti(GLenum light, GLenum pname, GLint param){_detail::Lighti(light, pname, param);}
	inline void Lightiv(GLenum light, GLenum pname, const GLint * params){_detail::Lightiv(light, pname, params);}
	inline void LineStipple(GLint factor, GLushort pattern){_detail::LineStipple(factor, pattern);}
	inline void LineWidth(GLfloat width){_detail::LineWidth(width);}
	inline void ListBase(GLuint base){_detail::ListBase(base);}
	inline void LoadIdentity(void){_detail::LoadIdentity();}
	inline void LoadMatrixd(const GLdouble * m){_detail::LoadMatrixd(m);}
	inline void LoadMatrixf(const GLfloat * m){_detail::LoadMatrixf(m);}
	inline void LoadName(GLuint name){_detail::LoadName(name);}
	inline void LogicOp(GLenum opcode){_detail::LogicOp(opcode);}
	inline void Map1d(GLenum target, GLdouble u1, GLdouble u2, GLint stride, GLint order, const GLdouble * points){_detail::Map1d(target, u1, u2, stride, order, points);}
	inline void Map1f(GLenum target, GLfloat u1, GLfloat u2, GLint stride, GLint order, const GLfloat * points){_detail::Map1f(target, u1, u2, stride, order, points);}
	inline void Map2d(GLenum target, GLdouble u1, GLdouble u2, GLint ustride, GLint uorder, GLdouble v1, GLdouble v2, GLint vstride, GLint vorder, const GLdouble * points){_detail::Map2d(target, u1, u2, ustride, uorder, v1, v2, vstride, vorder, points);}
	inline void Map2f(GLenum target, GLfloat u1, GLfloat u2, GLint ustride, GLint uorder, GLfloat v1, GLfloat v2, GLint vstride, GLint vorder, const GLfloat * points){_detail::Map2f(target, u1, u2, ustride, uorder, v1, v2, vstride, vorder, points);}
	inline void MapGrid1d(GLint un, GLdouble u1, GLdouble u2){_detail::MapGrid1d(un, u1, u2);}
	inline void MapGrid1f(GLint un, GLfloat u1, GLfloat u2){_detail::MapGrid1f(un, u1, u2);}
	inline void MapGrid2d(GLint un, GLdouble u1, GLdouble u2, GLint vn, GLdouble v1, GLdouble v2){_detail::MapGrid2d(un, u1, u2, vn, v1, v2);}
	inline void MapGrid2f(GLint un, GLfloat u1, GLfloat u2, GLint vn, GLfloat v1, GLfloat v2){_detail::MapGrid2f(un, u1, u2, vn, v1, v2);}
	inline void Materialf(GLenum face, GLenum pname, GLfloat param){_detail::Materialf(face, pname, param);}
	inline void Materialfv(GLenum face, GLenum pname, const GLfloat * params){_detail::Materialfv(face, pname, params);}
	inline void Materiali(GLenum face, GLenum pname, GLint param){_detail::Materiali(face, pname, param);}
	inline void Materialiv(GLenum face, GLenum pname, const GLint * params){_detail::Materialiv(face, pname, params);}
	inline void MatrixMode(GLenum mode){_detail::MatrixMode(mode);}
	inline void MultMatrixd(const GLdouble * m){_detail::MultMatrixd(m);}
	inline void MultMatrixf(const GLfloat * m){_detail::MultMatrixf(m);}
	inline void NewList(GLuint list, GLenum mode){_detail::NewList(list, mode);}
	inline void Normal3b(GLbyte nx, GLbyte ny, GLbyte nz){_detail::Normal3b(nx, ny, nz);}
	inline void Normal3bv(const GLbyte * v){_detail::Normal3bv(v);}
	inline void Normal3d(GLdouble nx, GLdouble ny, GLdouble nz){_detail::Normal3d(nx, ny, nz);}
	inline void Normal3dv(const GLdouble * v){_detail::Normal3dv(v);}
	inline void Normal3f(GLfloat nx, GLfloat ny, GLfloat nz){_detail::Normal3f(nx, ny, nz);}
	inline void Normal3fv(const GLfloat * v){_detail::Normal3fv(v);}
	inline void Normal3i(GLint nx, GLint ny, GLint nz){_detail::Normal3i(nx, ny, nz);}
	inline void Normal3iv(const GLint * v){_detail::Normal3iv(v);}
	inline void Normal3s(GLshort nx, GLshort ny, GLshort nz){_detail::Normal3s(nx, ny, nz);}
	inline void Normal3sv(const GLshort * v){_detail::Normal3sv(v);}
	inline void Ortho(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble zNear, GLdouble zFar){_detail::Ortho(left, right, bottom, top, zNear, zFar);}
	inline void PassThrough(GLfloat token){_detail::PassThrough(token);}
	inline void PixelMapfv(GLenum map, GLsizei mapsize, const GLfloat * values){_detail::PixelMapfv(map, mapsize, values);}
	inline void PixelMapuiv(GLenum map, GLsizei mapsize, const GLuint * values){_detail::PixelMapuiv(map, mapsize, values);}
	inline void PixelMapusv(GLenum map, GLsizei mapsize, const GLushort * values){_detail::PixelMapusv(map, mapsize, values);}
	inline void PixelStoref(GLenum pname, GLfloat param){_detail::PixelStoref(pname, param);}
	inline void PixelStorei(GLenum pname, GLint param){_detail::PixelStorei(pname, param);}
	inline void PixelTransferf(GLenum pname, GLfloat param){_detail::PixelTransferf(pname, param);}
	inline void PixelTransferi(GLenum pname, GLint param){_detail::PixelTransferi(pname, param);}
	inline void PixelZoom(GLfloat xfactor, GLfloat yfactor){_detail::PixelZoom(xfactor, yfactor);}
	inline void PointSize(GLfloat size){_detail::PointSize(size);}
	inline void PolygonMode(GLenum face, GLenum mode){_detail::PolygonMode(face, mode);}
	inline void PolygonStipple(const GLubyte * mask){_detail::PolygonStipple(mask);}
	inline void PopAttrib(void){_detail::PopAttrib();}
	inline void PopMatrix(void){_detail::PopMatrix();}
	inline void PopName(void){_detail::PopName();}
	inline void PushAttrib(GLbitfield mask){_detail::PushAttrib(mask);}
	inline void PushMatrix(void){_detail::PushMatrix();}
	inline void PushName(GLuint name){_detail::PushName(name);}
	inline void RasterPos2d(GLdouble x, GLdouble y){_detail::RasterPos2d(x, y);}
	inline void RasterPos2dv(const GLdouble * v){_detail::RasterPos2dv(v);}
	inline void RasterPos2f(GLfloat x, GLfloat y){_detail::RasterPos2f(x, y);}
	inline void RasterPos2fv(const GLfloat * v){_detail::RasterPos2fv(v);}
	inline void RasterPos2i(GLint x, GLint y){_detail::RasterPos2i(x, y);}
	inline void RasterPos2iv(const GLint * v){_detail::RasterPos2iv(v);}
	inline void RasterPos2s(GLshort x, GLshort y){_detail::RasterPos2s(x, y);}
	inline void RasterPos2sv(const GLshort * v){_detail::RasterPos2sv(v);}
	inline void RasterPos3d(GLdouble x, GLdouble y, GLdouble z){_detail::RasterPos3d(x, y, z);}
	inline void RasterPos3dv(const GLdouble * v){_detail::RasterPos3dv(v);}
	inline void RasterPos3f(GLfloat x, GLfloat y, GLfloat z){_detail::RasterPos3f(x, y, z);}
	inline void RasterPos3fv(const GLfloat * v){_detail::RasterPos3fv(v);}
	inline void RasterPos3i(GLint x, GLint y, GLint z){_detail::RasterPos3i(x, y, z);}
	inline void RasterPos3iv(const GLint * v){_detail::RasterPos3iv(v);}
	inline void RasterPos3s(GLshort x, GLshort y, GLshort z){_detail::RasterPos3s(x, y, z);}
	inline void RasterPos3sv(const GLshort * v){_detail::RasterPos3sv(v);}
	inline void RasterPos4d(GLdouble x, GLdouble y, GLdouble z, GLdouble w){_detail::RasterPos4d(x, y, z, w);}
	inline void RasterPos4dv(const GLdouble * v){_detail::RasterPos4dv(v);}
	inline void RasterPos4f(GLfloat x, GLfloat y, GLfloat z, GLfloat w){_detail::RasterPos4f(x, y, z, w);}
	inline void RasterPos4fv(const GLfloat * v){_detail::RasterPos4fv(v);}
	inline void RasterPos4i(GLint x, GLint y, GLint z, GLint w){_detail::RasterPos4i(x, y, z, w);}
	inline void RasterPos4iv(const GLint * v){_detail::RasterPos4iv(v);}
	inline void RasterPos4s(GLshort x, GLshort y, GLshort z, GLshort w){_detail::RasterPos4s(x, y, z, w);}
	inline void RasterPos4sv(const GLshort * v){_detail::RasterPos4sv(v);}
	inline void ReadBuffer(GLenum src){_detail::ReadBuffer(src);}
	inline void ReadPixels(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, void * pixels){_detail::ReadPixels(x, y, width, height, format, type, pixels);}
	inline void Rectd(GLdouble x1, GLdouble y1, GLdouble x2, GLdouble y2){_detail::Rectd(x1, y1, x2, y2);}
	inline void Rectdv(const GLdouble * v1, const GLdouble * v2){_detail::Rectdv(v1, v2);}
	inline void Rectf(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2){_detail::Rectf(x1, y1, x2, y2);}
	inline void Rectfv(const GLfloat * v1, const GLfloat * v2){_detail::Rectfv(v1, v2);}
	inline void Recti(GLint x1, GLint y1, GLint x2, GLint y2){_detail::Recti(x1, y1, x2, y2);}
	inline void Rectiv(const GLint * v1, const GLint * v2){_detail::Rectiv(v1, v2);}
	inline void Rects(GLshort x1, GLshort y1, GLshort x2, GLshort y2){_detail::Rects(x1, y1, x2, y2);}
	inline void Rectsv(const GLshort * v1, const GLshort * v2){_detail::Rectsv(v1, v2);}
	inline GLint RenderMode(GLenum mode){return _detail::RenderMode(mode);}
	inline void Rotated(GLdouble angle, GLdouble x, GLdouble y, GLdouble z){_detail::Rotated(angle, x, y, z);}
	inline void Rotatef(GLfloat angle, GLfloat x, GLfloat y, GLfloat z){_detail::Rotatef(angle, x, y, z);}
	inline void Scaled(GLdouble x, GLdouble y, GLdouble z){_detail::Scaled(x, y, z);}
	inline void Scalef(GLfloat x, GLfloat y, GLfloat z){_detail::Scalef(x, y, z);}
	inline void Scissor(GLint x, GLint y, GLsizei width, GLsizei height){_detail::Scissor(x, y, width, height);}
	inline void SelectBuffer(GLsizei size, GLuint * buffer){_detail::SelectBuffer(size, buffer);}
	inline void ShadeModel(GLenum mode){_detail::ShadeModel(mode);}
	inline void StencilFunc(GLenum func, GLint ref, GLuint mask){_detail::StencilFunc(func, ref, mask);}
	inline void StencilMask(GLuint mask){_detail::StencilMask(mask);}
	inline void StencilOp(GLenum fail, GLenum zfail, GLenum zpass){_detail::StencilOp(fail, zfail, zpass);}
	inline void TexCoord1d(GLdouble s){_detail::TexCoord1d(s);}
	inline void TexCoord1dv(const GLdouble * v){_detail::TexCoord1dv(v);}
	inline void TexCoord1f(GLfloat s){_detail::TexCoord1f(s);}
	inline void TexCoord1fv(const GLfloat * v){_detail::TexCoord1fv(v);}
	inline void TexCoord1i(GLint s){_detail::TexCoord1i(s);}
	inline void TexCoord1iv(const GLint * v){_detail::TexCoord1iv(v);}
	inline void TexCoord1s(GLshort s){_detail::TexCoord1s(s);}
	inline void TexCoord1sv(const GLshort * v){_detail::TexCoord1sv(v);}
	inline void TexCoord2d(GLdouble s, GLdouble t){_detail::TexCoord2d(s, t);}
	inline void TexCoord2dv(const GLdouble * v){_detail::TexCoord2dv(v);}
	inline void TexCoord2f(GLfloat s, GLfloat t){_detail::TexCoord2f(s, t);}
	inline void TexCoord2fv(const GLfloat * v){_detail::TexCoord2fv(v);}
	inline void TexCoord2i(GLint s, GLint t){_detail::TexCoord2i(s, t);}
	inline void TexCoord2iv(const GLint * v){_detail::TexCoord2iv(v);}
	inline void TexCoord2s(GLshort s, GLshort t){_detail::TexCoord2s(s, t);}
	inline void TexCoord2sv(const GLshort * v){_detail::TexCoord2sv(v);}
	inline void TexCoord3d(GLdouble s, GLdouble t, GLdouble r){_detail::TexCoord3d(s, t, r);}
	inline void TexCoord3dv(const GLdouble * v){_detail::TexCoord3dv(v);}
	inline void TexCoord3f(GLfloat s, GLfloat t, GLfloat r){_detail::TexCoord3f(s, t, r);}
	inline void TexCoord3fv(const GLfloat * v){_detail::TexCoord3fv(v);}
	inline void TexCoord3i(GLint s, GLint t, GLint r){_detail::TexCoord3i(s, t, r);}
	inline void TexCoord3iv(const GLint * v){_detail::TexCoord3iv(v);}
	inline void TexCoord3s(GLshort s, GLshort t, GLshort r){_detail::TexCoord3s(s, t, r);}
	inline void TexCoord3sv(const GLshort * v){_detail::TexCoord3sv(v);}
	inline void TexCoord4d(GLdouble s, GLdouble t, GLdouble r, GLdouble q){_detail::TexCoord4d(s, t, r, q);}
	inline void TexCoord4dv(const GLdouble * v){_detail::TexCoord4dv(v);}
	inline void TexCoord4f(GLfloat s, GLfloat t, GLfloat r, GLfloat q){_detail::TexCoord4f(s, t, r, q);}
	inline void TexCoord4fv(const GLfloat * v){_detail::TexCoord4fv(v);}
	inline void TexCoord4i(GLint s, GLint t, GLint r, GLint q){_detail::TexCoord4i(s, t, r, q);}
	inline void TexCoord4iv(const GLint * v){_detail::TexCoord4iv(v);}
	inline void TexCoord4s(GLshort s, GLshort t, GLshort r, GLshort q){_detail::TexCoord4s(s, t, r, q);}
	inline void TexCoord4sv(const GLshort * v){_detail::TexCoord4sv(v);}
	inline void TexEnvf(GLenum target, GLenum pname, GLfloat param){_detail::TexEnvf(target, pname, param);}
	inline void TexEnvfv(GLenum target, GLenum pname, const GLfloat * params){_detail::TexEnvfv(target, pname, params);}
	inline void TexEnvi(GLenum target, GLenum pname, GLint param){_detail::TexEnvi(target, pname, param);}
	inline void TexEnviv(GLenum target, GLenum pname, const GLint * params){_detail::TexEnviv(target, pname, params);}
	inline void TexGend(GLenum coord, GLenum pname, GLdouble param){_detail::TexGend(coord, pname, param);}
	inline void TexGendv(GLenum coord, GLenum pname, const GLdouble * params){_detail::TexGendv(coord, pname, params);}
	inline void TexGenf(GLenum coord, GLenum pname, GLfloat param){_detail::TexGenf(coord, pname, param);}
	inline void TexGenfv(GLenum coord, GLenum pname, const GLfloat * params){_detail::TexGenfv(coord, pname, params);}
	inline void TexGeni(GLenum coord, GLenum pname, GLint param){_detail::TexGeni(coord, pname, param);}
	inline void TexGeniv(GLenum coord, GLenum pname, const GLint * params){_detail::TexGeniv(coord, pname, params);}
	inline void TexImage1D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLint border, GLenum format, GLenum type, const void * pixels){_detail::TexImage1D(target, level, internalformat, width, border, format, type, pixels);}
	inline void TexImage2D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const void * pixels){_detail::TexImage2D(target, level, internalformat, width, height, border, format, type, pixels);}
	inline void TexParameterf(GLenum target, GLenum pname, GLfloat param){_detail::TexParameterf(target, pname, param);}
	inline void TexParameterfv(GLenum target, GLenum pname, const GLfloat * params){_detail::TexParameterfv(target, pname, params);}
	inline void TexParameteri(GLenum target, GLenum pname, GLint param){_detail::TexParameteri(target, pname, param);}
	inline void TexParameteriv(GLenum target, GLenum pname, const GLint * params){_detail::TexParameteriv(target, pname, params);}
	inline void Translated(GLdouble x, GLdouble y, GLdouble z){_detail::Translated(x, y, z);}
	inline void Translatef(GLfloat x, GLfloat y, GLfloat z){_detail::Translatef(x, y, z);}
	inline void Vertex2d(GLdouble x, GLdouble y){_detail::Vertex2d(x, y);}
	inline void Vertex2dv(const GLdouble * v){_detail::Vertex2dv(v);}
	inline void Vertex2f(GLfloat x, GLfloat y){_detail::Vertex2f(x, y);}
	inline void Vertex2fv(const GLfloat * v){_detail::Vertex2fv(v);}
	inline void Vertex2i(GLint x, GLint y){_detail::Vertex2i(x, y);}
	inline void Vertex2iv(const GLint * v){_detail::Vertex2iv(v);}
	inline void Vertex2s(GLshort x, GLshort y){_detail::Vertex2s(x, y);}
	inline void Vertex2sv(const GLshort * v){_detail::Vertex2sv(v);}
	inline void Vertex3d(GLdouble x, GLdouble y, GLdouble z){_detail::Vertex3d(x, y, z);}
	inline void Vertex3dv(const GLdouble * v){_detail::Vertex3dv(v);}
	inline void Vertex3f(GLfloat x, GLfloat y, GLfloat z){_detail::Vertex3f(x, y, z);}
	inline void Vertex3fv(const GLfloat * v){_detail::Vertex3fv(v);}
	inline void Vertex3i(GLint x, GLint y, GLint z){_detail::Vertex3i(x, y, z);}
	inline void Vertex3iv(const GLint * v){_detail::Vertex3iv(v);}
	inline void Vertex3s(GLshort x, GLshort y, GLshort z){_detail::Vertex3s(x, y, z);}
	inline void Vertex3sv(const GLshort * v){_detail::Vertex3sv(v);}
	inline void Vertex4d(GLdouble x, GLdouble y, GLdouble z, GLdouble w){_detail::Vertex4d(x, y, z, w);}
	inline void Vertex4dv(const GLdouble * v){_detail::Vertex4dv(v);}
	inline void Vertex4f(GLfloat x, GLfloat y, GLfloat z, GLfloat w){_detail::Vertex4f(x, y, z, w);}
	inline void Vertex4fv(const GLfloat * v){_detail::Vertex4fv(v);}
	inline void Vertex4i(GLint x, GLint y, GLint z, GLint w){_detail::Vertex4i(x, y, z, w);}
	inline void Vertex4iv(const GLint * v){_detail::Vertex4iv(v);}
	inline void Vertex4s(GLshort x, GLshort y, GLshort z, GLshort w){_detail::Vertex4s(x, y, z, w);}
	inline void Vertex4sv(const GLshort * v){_detail::Vertex4sv(v);}
	inline void Viewport(GLint x, GLint y, GLsizei width, GLsizei height){_detail::Viewport(x, y, width, height);}
	
	inline GLboolean AreTexturesResident(GLsizei n, const GLuint * textures, GLboolean * residences){return _detail::AreTexturesResident(n, textures, residences);}
	inline void ArrayElement(GLint i){_detail::ArrayElement(i);}
	inline void BindTexture(GLenum target, GLuint texture){_detail::BindTexture(target, texture);}
	inline void ColorPointer(GLint size, GLenum type, GLsizei stride, const void * pointer){_detail::ColorPointer(size, type, stride, pointer);}
	inline void CopyTexImage1D(GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLint border){_detail::CopyTexImage1D(target, level, internalformat, x, y, width, border);}
	inline void CopyTexImage2D(GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border){_detail::CopyTexImage2D(target, level, internalformat, x, y, width, height, border);}
	inline void CopyTexSubImage1D(GLenum target, GLint level, GLint xoffset, GLint x, GLint y, GLsizei width){_detail::CopyTexSubImage1D(target, level, xoffset, x, y, width);}
	inline void CopyTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height){_detail::CopyTexSubImage2D(target, level, xoffset, yoffset, x, y, width, height);}
	inline void DeleteTextures(GLsizei n, const GLuint * textures){_detail::DeleteTextures(n, textures);}
	inline void DisableClientState(GLenum ren_array){_detail::DisableClientState(ren_array);}
	inline void DrawArrays(GLenum mode, GLint first, GLsizei count){_detail::DrawArrays(mode, first, count);}
	inline void DrawElements(GLenum mode, GLsizei count, GLenum type, const void * indices){_detail::DrawElements(mode, count, type, indices);}
	inline void EdgeFlagPointer(GLsizei stride, const void * pointer){_detail::EdgeFlagPointer(stride, pointer);}
	inline void EnableClientState(GLenum ren_array){_detail::EnableClientState(ren_array);}
	inline void GenTextures(GLsizei n, GLuint * textures){_detail::GenTextures(n, textures);}
	inline void GetPointerv(GLenum pname, void ** params){_detail::GetPointerv(pname, params);}
	inline void IndexPointer(GLenum type, GLsizei stride, const void * pointer){_detail::IndexPointer(type, stride, pointer);}
	inline void Indexub(GLubyte c){_detail::Indexub(c);}
	inline void Indexubv(const GLubyte * c){_detail::Indexubv(c);}
	inline void InterleavedArrays(GLenum format, GLsizei stride, const void * pointer){_detail::InterleavedArrays(format, stride, pointer);}
	inline GLboolean IsTexture(GLuint texture){return _detail::IsTexture(texture);}
	inline void NormalPointer(GLenum type, GLsizei stride, const void * pointer){_detail::NormalPointer(type, stride, pointer);}
	inline void PolygonOffset(GLfloat factor, GLfloat units){_detail::PolygonOffset(factor, units);}
	inline void PopClientAttrib(void){_detail::PopClientAttrib();}
	inline void PrioritizeTextures(GLsizei n, const GLuint * textures, const GLfloat * priorities){_detail::PrioritizeTextures(n, textures, priorities);}
	inline void PushClientAttrib(GLbitfield mask){_detail::PushClientAttrib(mask);}
	inline void TexCoordPointer(GLint size, GLenum type, GLsizei stride, const void * pointer){_detail::TexCoordPointer(size, type, stride, pointer);}
	inline void TexSubImage1D(GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, const void * pixels){_detail::TexSubImage1D(target, level, xoffset, width, format, type, pixels);}
	inline void TexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const void * pixels){_detail::TexSubImage2D(target, level, xoffset, yoffset, width, height, format, type, pixels);}
	inline void VertexPointer(GLint size, GLenum type, GLsizei stride, const void * pointer){_detail::VertexPointer(size, type, stride, pointer);}
	
	inline void CopyTexSubImage3D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height){_detail::CopyTexSubImage3D(target, level, xoffset, yoffset, zoffset, x, y, width, height);}
	inline void DrawRangeElements(GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const void * indices){_detail::DrawRangeElements(mode, start, end, count, type, indices);}
	inline void TexImage3D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const void * pixels){_detail::TexImage3D(target, level, internalformat, width, height, depth, border, format, type, pixels);}
	inline void TexSubImage3D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void * pixels){_detail::TexSubImage3D(target, level, xoffset, yoffset, zoffset, width, height, depth, format, type, pixels);}
	
	inline void ActiveTexture(GLenum texture){_detail::ActiveTexture(texture);}
	inline void ClientActiveTexture(GLenum texture){_detail::ClientActiveTexture(texture);}
	inline void CompressedTexImage1D(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLint border, GLsizei imageSize, const void * data){_detail::CompressedTexImage1D(target, level, internalformat, width, border, imageSize, data);}
	inline void CompressedTexImage2D(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const void * data){_detail::CompressedTexImage2D(target, level, internalformat, width, height, border, imageSize, data);}
	inline void CompressedTexImage3D(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, const void * data){_detail::CompressedTexImage3D(target, level, internalformat, width, height, depth, border, imageSize, data);}
	inline void CompressedTexSubImage1D(GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLsizei imageSize, const void * data){_detail::CompressedTexSubImage1D(target, level, xoffset, width, format, imageSize, data);}
	inline void CompressedTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const void * data){_detail::CompressedTexSubImage2D(target, level, xoffset, yoffset, width, height, format, imageSize, data);}
	inline void CompressedTexSubImage3D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const void * data){_detail::CompressedTexSubImage3D(target, level, xoffset, yoffset, zoffset, width, height, depth, format, imageSize, data);}
	inline void GetCompressedTexImage(GLenum target, GLint level, void * img){_detail::GetCompressedTexImage(target, level, img);}
	inline void LoadTransposeMatrixd(const GLdouble * m){_detail::LoadTransposeMatrixd(m);}
	inline void LoadTransposeMatrixf(const GLfloat * m){_detail::LoadTransposeMatrixf(m);}
	inline void MultTransposeMatrixd(const GLdouble * m){_detail::MultTransposeMatrixd(m);}
	inline void MultTransposeMatrixf(const GLfloat * m){_detail::MultTransposeMatrixf(m);}
	inline void MultiTexCoord1d(GLenum target, GLdouble s){_detail::MultiTexCoord1d(target, s);}
	inline void MultiTexCoord1dv(GLenum target, const GLdouble * v){_detail::MultiTexCoord1dv(target, v);}
	inline void MultiTexCoord1f(GLenum target, GLfloat s){_detail::MultiTexCoord1f(target, s);}
	inline void MultiTexCoord1fv(GLenum target, const GLfloat * v){_detail::MultiTexCoord1fv(target, v);}
	inline void MultiTexCoord1i(GLenum target, GLint s){_detail::MultiTexCoord1i(target, s);}
	inline void MultiTexCoord1iv(GLenum target, const GLint * v){_detail::MultiTexCoord1iv(target, v);}
	inline void MultiTexCoord1s(GLenum target, GLshort s){_detail::MultiTexCoord1s(target, s);}
	inline void MultiTexCoord1sv(GLenum target, const GLshort * v){_detail::MultiTexCoord1sv(target, v);}
	inline void MultiTexCoord2d(GLenum target, GLdouble s, GLdouble t){_detail::MultiTexCoord2d(target, s, t);}
	inline void MultiTexCoord2dv(GLenum target, const GLdouble * v){_detail::MultiTexCoord2dv(target, v);}
	inline void MultiTexCoord2f(GLenum target, GLfloat s, GLfloat t){_detail::MultiTexCoord2f(target, s, t);}
	inline void MultiTexCoord2fv(GLenum target, const GLfloat * v){_detail::MultiTexCoord2fv(target, v);}
	inline void MultiTexCoord2i(GLenum target, GLint s, GLint t){_detail::MultiTexCoord2i(target, s, t);}
	inline void MultiTexCoord2iv(GLenum target, const GLint * v){_detail::MultiTexCoord2iv(target, v);}
	inline void MultiTexCoord2s(GLenum target, GLshort s, GLshort t){_detail::MultiTexCoord2s(target, s, t);}
	inline void MultiTexCoord2sv(GLenum target, const GLshort * v){_detail::MultiTexCoord2sv(target, v);}
	inline void MultiTexCoord3d(GLenum target, GLdouble s, GLdouble t, GLdouble r){_detail::MultiTexCoord3d(target, s, t, r);}
	inline void MultiTexCoord3dv(GLenum target, const GLdouble * v){_detail::MultiTexCoord3dv(target, v);}
	inline void MultiTexCoord3f(GLenum target, GLfloat s, GLfloat t, GLfloat r){_detail::MultiTexCoord3f(target, s, t, r);}
	inline void MultiTexCoord3fv(GLenum target, const GLfloat * v){_detail::MultiTexCoord3fv(target, v);}
	inline void MultiTexCoord3i(GLenum target, GLint s, GLint t, GLint r){_detail::MultiTexCoord3i(target, s, t, r);}
	inline void MultiTexCoord3iv(GLenum target, const GLint * v){_detail::MultiTexCoord3iv(target, v);}
	inline void MultiTexCoord3s(GLenum target, GLshort s, GLshort t, GLshort r){_detail::MultiTexCoord3s(target, s, t, r);}
	inline void MultiTexCoord3sv(GLenum target, const GLshort * v){_detail::MultiTexCoord3sv(target, v);}
	inline void MultiTexCoord4d(GLenum target, GLdouble s, GLdouble t, GLdouble r, GLdouble q){_detail::MultiTexCoord4d(target, s, t, r, q);}
	inline void MultiTexCoord4dv(GLenum target, const GLdouble * v){_detail::MultiTexCoord4dv(target, v);}
	inline void MultiTexCoord4f(GLenum target, GLfloat s, GLfloat t, GLfloat r, GLfloat q){_detail::MultiTexCoord4f(target, s, t, r, q);}
	inline void MultiTexCoord4fv(GLenum target, const GLfloat * v){_detail::MultiTexCoord4fv(target, v);}
	inline void MultiTexCoord4i(GLenum target, GLint s, GLint t, GLint r, GLint q){_detail::MultiTexCoord4i(target, s, t, r, q);}
	inline void MultiTexCoord4iv(GLenum target, const GLint * v){_detail::MultiTexCoord4iv(target, v);}
	inline void MultiTexCoord4s(GLenum target, GLshort s, GLshort t, GLshort r, GLshort q){_detail::MultiTexCoord4s(target, s, t, r, q);}
	inline void MultiTexCoord4sv(GLenum target, const GLshort * v){_detail::MultiTexCoord4sv(target, v);}
	inline void SampleCoverage(GLfloat value, GLboolean invert){_detail::SampleCoverage(value, invert);}
	
	inline void BlendColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha){_detail::BlendColor(red, green, blue, alpha);}
	inline void BlendEquation(GLenum mode){_detail::BlendEquation(mode);}
	inline void BlendFuncSeparate(GLenum sfactorRGB, GLenum dfactorRGB, GLenum sfactorAlpha, GLenum dfactorAlpha){_detail::BlendFuncSeparate(sfactorRGB, dfactorRGB, sfactorAlpha, dfactorAlpha);}
	inline void FogCoordPointer(GLenum type, GLsizei stride, const void * pointer){_detail::FogCoordPointer(type, stride, pointer);}
	inline void FogCoordd(GLdouble coord){_detail::FogCoordd(coord);}
	inline void FogCoorddv(const GLdouble * coord){_detail::FogCoorddv(coord);}
	inline void FogCoordf(GLfloat coord){_detail::FogCoordf(coord);}
	inline void FogCoordfv(const GLfloat * coord){_detail::FogCoordfv(coord);}
	inline void MultiDrawArrays(GLenum mode, const GLint * first, const GLsizei * count, GLsizei drawcount){_detail::MultiDrawArrays(mode, first, count, drawcount);}
	inline void MultiDrawElements(GLenum mode, const GLsizei * count, GLenum type, const void *const* indices, GLsizei drawcount){_detail::MultiDrawElements(mode, count, type, indices, drawcount);}
	inline void PointParameterf(GLenum pname, GLfloat param){_detail::PointParameterf(pname, param);}
	inline void PointParameterfv(GLenum pname, const GLfloat * params){_detail::PointParameterfv(pname, params);}
	inline void PointParameteri(GLenum pname, GLint param){_detail::PointParameteri(pname, param);}
	inline void PointParameteriv(GLenum pname, const GLint * params){_detail::PointParameteriv(pname, params);}
	inline void SecondaryColor3b(GLbyte red, GLbyte green, GLbyte blue){_detail::SecondaryColor3b(red, green, blue);}
	inline void SecondaryColor3bv(const GLbyte * v){_detail::SecondaryColor3bv(v);}
	inline void SecondaryColor3d(GLdouble red, GLdouble green, GLdouble blue){_detail::SecondaryColor3d(red, green, blue);}
	inline void SecondaryColor3dv(const GLdouble * v){_detail::SecondaryColor3dv(v);}
	inline void SecondaryColor3f(GLfloat red, GLfloat green, GLfloat blue){_detail::SecondaryColor3f(red, green, blue);}
	inline void SecondaryColor3fv(const GLfloat * v){_detail::SecondaryColor3fv(v);}
	inline void SecondaryColor3i(GLint red, GLint green, GLint blue){_detail::SecondaryColor3i(red, green, blue);}
	inline void SecondaryColor3iv(const GLint * v){_detail::SecondaryColor3iv(v);}
	inline void SecondaryColor3s(GLshort red, GLshort green, GLshort blue){_detail::SecondaryColor3s(red, green, blue);}
	inline void SecondaryColor3sv(const GLshort * v){_detail::SecondaryColor3sv(v);}
	inline void SecondaryColor3ub(GLubyte red, GLubyte green, GLubyte blue){_detail::SecondaryColor3ub(red, green, blue);}
	inline void SecondaryColor3ubv(const GLubyte * v){_detail::SecondaryColor3ubv(v);}
	inline void SecondaryColor3ui(GLuint red, GLuint green, GLuint blue){_detail::SecondaryColor3ui(red, green, blue);}
	inline void SecondaryColor3uiv(const GLuint * v){_detail::SecondaryColor3uiv(v);}
	inline void SecondaryColor3us(GLushort red, GLushort green, GLushort blue){_detail::SecondaryColor3us(red, green, blue);}
	inline void SecondaryColor3usv(const GLushort * v){_detail::SecondaryColor3usv(v);}
	inline void SecondaryColorPointer(GLint size, GLenum type, GLsizei stride, const void * pointer){_detail::SecondaryColorPointer(size, type, stride, pointer);}
	inline void WindowPos2d(GLdouble x, GLdouble y){_detail::WindowPos2d(x, y);}
	inline void WindowPos2dv(const GLdouble * v){_detail::WindowPos2dv(v);}
	inline void WindowPos2f(GLfloat x, GLfloat y){_detail::WindowPos2f(x, y);}
	inline void WindowPos2fv(const GLfloat * v){_detail::WindowPos2fv(v);}
	inline void WindowPos2i(GLint x, GLint y){_detail::WindowPos2i(x, y);}
	inline void WindowPos2iv(const GLint * v){_detail::WindowPos2iv(v);}
	inline void WindowPos2s(GLshort x, GLshort y){_detail::WindowPos2s(x, y);}
	inline void WindowPos2sv(const GLshort * v){_detail::WindowPos2sv(v);}
	inline void WindowPos3d(GLdouble x, GLdouble y, GLdouble z){_detail::WindowPos3d(x, y, z);}
	inline void WindowPos3dv(const GLdouble * v){_detail::WindowPos3dv(v);}
	inline void WindowPos3f(GLfloat x, GLfloat y, GLfloat z){_detail::WindowPos3f(x, y, z);}
	inline void WindowPos3fv(const GLfloat * v){_detail::WindowPos3fv(v);}
	inline void WindowPos3i(GLint x, GLint y, GLint z){_detail::WindowPos3i(x, y, z);}
	inline void WindowPos3iv(const GLint * v){_detail::WindowPos3iv(v);}
	inline void WindowPos3s(GLshort x, GLshort y, GLshort z){_detail::WindowPos3s(x, y, z);}
	inline void WindowPos3sv(const GLshort * v){_detail::WindowPos3sv(v);}
	
	inline void BeginQuery(GLenum target, GLuint id){_detail::BeginQuery(target, id);}
	inline void BindBuffer(GLenum target, GLuint buffer){_detail::BindBuffer(target, buffer);}
	inline void BufferData(GLenum target, GLsizeiptr size, const void * data, GLenum usage){_detail::BufferData(target, size, data, usage);}
	inline void BufferSubData(GLenum target, GLintptr offset, GLsizeiptr size, const void * data){_detail::BufferSubData(target, offset, size, data);}
	inline void DeleteBuffers(GLsizei n, const GLuint * buffers){_detail::DeleteBuffers(n, buffers);}
	inline void DeleteQueries(GLsizei n, const GLuint * ids){_detail::DeleteQueries(n, ids);}
	inline void EndQuery(GLenum target){_detail::EndQuery(target);}
	inline void GenBuffers(GLsizei n, GLuint * buffers){_detail::GenBuffers(n, buffers);}
	inline void GenQueries(GLsizei n, GLuint * ids){_detail::GenQueries(n, ids);}
	inline void GetBufferParameteriv(GLenum target, GLenum pname, GLint * params){_detail::GetBufferParameteriv(target, pname, params);}
	inline void GetBufferPointerv(GLenum target, GLenum pname, void ** params){_detail::GetBufferPointerv(target, pname, params);}
	inline void GetBufferSubData(GLenum target, GLintptr offset, GLsizeiptr size, void * data){_detail::GetBufferSubData(target, offset, size, data);}
	inline void GetQueryObjectiv(GLuint id, GLenum pname, GLint * params){_detail::GetQueryObjectiv(id, pname, params);}
	inline void GetQueryObjectuiv(GLuint id, GLenum pname, GLuint * params){_detail::GetQueryObjectuiv(id, pname, params);}
	inline void GetQueryiv(GLenum target, GLenum pname, GLint * params){_detail::GetQueryiv(target, pname, params);}
	inline GLboolean IsBuffer(GLuint buffer){return _detail::IsBuffer(buffer);}
	inline GLboolean IsQuery(GLuint id){return _detail::IsQuery(id);}
	inline void * MapBuffer(GLenum target, GLenum access){return _detail::MapBuffer(target, access);}
	inline GLboolean UnmapBuffer(GLenum target){return _detail::UnmapBuffer(target);}
	
	inline void AttachShader(GLuint program, GLuint shader){_detail::AttachShader(program, shader);}
	inline void BindAttribLocation(GLuint program, GLuint index, const GLchar * name){_detail::BindAttribLocation(program, index, name);}
	inline void BlendEquationSeparate(GLenum modeRGB, GLenum modeAlpha){_detail::BlendEquationSeparate(modeRGB, modeAlpha);}
	inline void CompileShader(GLuint shader){_detail::CompileShader(shader);}
	inline GLuint CreateProgram(void){return _detail::CreateProgram();}
	inline GLuint CreateShader(GLenum type){return _detail::CreateShader(type);}
	inline void DeleteProgram(GLuint program){_detail::DeleteProgram(program);}
	inline void DeleteShader(GLuint shader){_detail::DeleteShader(shader);}
	inline void DetachShader(GLuint program, GLuint shader){_detail::DetachShader(program, shader);}
	inline void DisableVertexAttribArray(GLuint index){_detail::DisableVertexAttribArray(index);}
	inline void DrawBuffers(GLsizei n, const GLenum * bufs){_detail::DrawBuffers(n, bufs);}
	inline void EnableVertexAttribArray(GLuint index){_detail::EnableVertexAttribArray(index);}
	inline void GetActiveAttrib(GLuint program, GLuint index, GLsizei bufSize, GLsizei * length, GLint * size, GLenum * type, GLchar * name){_detail::GetActiveAttrib(program, index, bufSize, length, size, type, name);}
	inline void GetActiveUniform(GLuint program, GLuint index, GLsizei bufSize, GLsizei * length, GLint * size, GLenum * type, GLchar * name){_detail::GetActiveUniform(program, index, bufSize, length, size, type, name);}
	inline void GetAttachedShaders(GLuint program, GLsizei maxCount, GLsizei * count, GLuint * shaders){_detail::GetAttachedShaders(program, maxCount, count, shaders);}
	inline GLint GetAttribLocation(GLuint program, const GLchar * name){return _detail::GetAttribLocation(program, name);}
	inline void GetProgramInfoLog(GLuint program, GLsizei bufSize, GLsizei * length, GLchar * infoLog){_detail::GetProgramInfoLog(program, bufSize, length, infoLog);}
	inline void GetProgramiv(GLuint program, GLenum pname, GLint * params){_detail::GetProgramiv(program, pname, params);}
	inline void GetShaderInfoLog(GLuint shader, GLsizei bufSize, GLsizei * length, GLchar * infoLog){_detail::GetShaderInfoLog(shader, bufSize, length, infoLog);}
	inline void GetShaderSource(GLuint shader, GLsizei bufSize, GLsizei * length, GLchar * source){_detail::GetShaderSource(shader, bufSize, length, source);}
	inline void GetShaderiv(GLuint shader, GLenum pname, GLint * params){_detail::GetShaderiv(shader, pname, params);}
	inline GLint GetUniformLocation(GLuint program, const GLchar * name){return _detail::GetUniformLocation(program, name);}
	inline void GetUniformfv(GLuint program, GLint location, GLfloat * params){_detail::GetUniformfv(program, location, params);}
	inline void GetUniformiv(GLuint program, GLint location, GLint * params){_detail::GetUniformiv(program, location, params);}
	inline void GetVertexAttribPointerv(GLuint index, GLenum pname, void ** pointer){_detail::GetVertexAttribPointerv(index, pname, pointer);}
	inline void GetVertexAttribdv(GLuint index, GLenum pname, GLdouble * params){_detail::GetVertexAttribdv(index, pname, params);}
	inline void GetVertexAttribfv(GLuint index, GLenum pname, GLfloat * params){_detail::GetVertexAttribfv(index, pname, params);}
	inline void GetVertexAttribiv(GLuint index, GLenum pname, GLint * params){_detail::GetVertexAttribiv(index, pname, params);}
	inline GLboolean IsProgram(GLuint program){return _detail::IsProgram(program);}
	inline GLboolean IsShader(GLuint shader){return _detail::IsShader(shader);}
	inline void LinkProgram(GLuint program){_detail::LinkProgram(program);}
	inline void ShaderSource(GLuint shader, GLsizei count, const GLchar *const* string, const GLint * length){_detail::ShaderSource(shader, count, string, length);}
	inline void StencilFuncSeparate(GLenum face, GLenum func, GLint ref, GLuint mask){_detail::StencilFuncSeparate(face, func, ref, mask);}
	inline void StencilMaskSeparate(GLenum face, GLuint mask){_detail::StencilMaskSeparate(face, mask);}
	inline void StencilOpSeparate(GLenum face, GLenum sfail, GLenum dpfail, GLenum dppass){_detail::StencilOpSeparate(face, sfail, dpfail, dppass);}
	inline void Uniform1f(GLint location, GLfloat v0){_detail::Uniform1f(location, v0);}
	inline void Uniform1fv(GLint location, GLsizei count, const GLfloat * value){_detail::Uniform1fv(location, count, value);}
	inline void Uniform1i(GLint location, GLint v0){_detail::Uniform1i(location, v0);}
	inline void Uniform1iv(GLint location, GLsizei count, const GLint * value){_detail::Uniform1iv(location, count, value);}
	inline void Uniform2f(GLint location, GLfloat v0, GLfloat v1){_detail::Uniform2f(location, v0, v1);}
	inline void Uniform2fv(GLint location, GLsizei count, const GLfloat * value){_detail::Uniform2fv(location, count, value);}
	inline void Uniform2i(GLint location, GLint v0, GLint v1){_detail::Uniform2i(location, v0, v1);}
	inline void Uniform2iv(GLint location, GLsizei count, const GLint * value){_detail::Uniform2iv(location, count, value);}
	inline void Uniform3f(GLint location, GLfloat v0, GLfloat v1, GLfloat v2){_detail::Uniform3f(location, v0, v1, v2);}
	inline void Uniform3fv(GLint location, GLsizei count, const GLfloat * value){_detail::Uniform3fv(location, count, value);}
	inline void Uniform3i(GLint location, GLint v0, GLint v1, GLint v2){_detail::Uniform3i(location, v0, v1, v2);}
	inline void Uniform3iv(GLint location, GLsizei count, const GLint * value){_detail::Uniform3iv(location, count, value);}
	inline void Uniform4f(GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3){_detail::Uniform4f(location, v0, v1, v2, v3);}
	inline void Uniform4fv(GLint location, GLsizei count, const GLfloat * value){_detail::Uniform4fv(location, count, value);}
	inline void Uniform4i(GLint location, GLint v0, GLint v1, GLint v2, GLint v3){_detail::Uniform4i(location, v0, v1, v2, v3);}
	inline void Uniform4iv(GLint location, GLsizei count, const GLint * value){_detail::Uniform4iv(location, count, value);}
	inline void UniformMatrix2fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value){_detail::UniformMatrix2fv(location, count, transpose, value);}
	inline void UniformMatrix3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value){_detail::UniformMatrix3fv(location, count, transpose, value);}
	inline void UniformMatrix4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value){_detail::UniformMatrix4fv(location, count, transpose, value);}
	inline void UseProgram(GLuint program){_detail::UseProgram(program);}
	inline void ValidateProgram(GLuint program){_detail::ValidateProgram(program);}
	inline void VertexAttrib1d(GLuint index, GLdouble x){_detail::VertexAttrib1d(index, x);}
	inline void VertexAttrib1dv(GLuint index, const GLdouble * v){_detail::VertexAttrib1dv(index, v);}
	inline void VertexAttrib1f(GLuint index, GLfloat x){_detail::VertexAttrib1f(index, x);}
	inline void VertexAttrib1fv(GLuint index, const GLfloat * v){_detail::VertexAttrib1fv(index, v);}
	inline void VertexAttrib1s(GLuint index, GLshort x){_detail::VertexAttrib1s(index, x);}
	inline void VertexAttrib1sv(GLuint index, const GLshort * v){_detail::VertexAttrib1sv(index, v);}
	inline void VertexAttrib2d(GLuint index, GLdouble x, GLdouble y){_detail::VertexAttrib2d(index, x, y);}
	inline void VertexAttrib2dv(GLuint index, const GLdouble * v){_detail::VertexAttrib2dv(index, v);}
	inline void VertexAttrib2f(GLuint index, GLfloat x, GLfloat y){_detail::VertexAttrib2f(index, x, y);}
	inline void VertexAttrib2fv(GLuint index, const GLfloat * v){_detail::VertexAttrib2fv(index, v);}
	inline void VertexAttrib2s(GLuint index, GLshort x, GLshort y){_detail::VertexAttrib2s(index, x, y);}
	inline void VertexAttrib2sv(GLuint index, const GLshort * v){_detail::VertexAttrib2sv(index, v);}
	inline void VertexAttrib3d(GLuint index, GLdouble x, GLdouble y, GLdouble z){_detail::VertexAttrib3d(index, x, y, z);}
	inline void VertexAttrib3dv(GLuint index, const GLdouble * v){_detail::VertexAttrib3dv(index, v);}
	inline void VertexAttrib3f(GLuint index, GLfloat x, GLfloat y, GLfloat z){_detail::VertexAttrib3f(index, x, y, z);}
	inline void VertexAttrib3fv(GLuint index, const GLfloat * v){_detail::VertexAttrib3fv(index, v);}
	inline void VertexAttrib3s(GLuint index, GLshort x, GLshort y, GLshort z){_detail::VertexAttrib3s(index, x, y, z);}
	inline void VertexAttrib3sv(GLuint index, const GLshort * v){_detail::VertexAttrib3sv(index, v);}
	inline void VertexAttrib4Nbv(GLuint index, const GLbyte * v){_detail::VertexAttrib4Nbv(index, v);}
	inline void VertexAttrib4Niv(GLuint index, const GLint * v){_detail::VertexAttrib4Niv(index, v);}
	inline void VertexAttrib4Nsv(GLuint index, const GLshort * v){_detail::VertexAttrib4Nsv(index, v);}
	inline void VertexAttrib4Nub(GLuint index, GLubyte x, GLubyte y, GLubyte z, GLubyte w){_detail::VertexAttrib4Nub(index, x, y, z, w);}
	inline void VertexAttrib4Nubv(GLuint index, const GLubyte * v){_detail::VertexAttrib4Nubv(index, v);}
	inline void VertexAttrib4Nuiv(GLuint index, const GLuint * v){_detail::VertexAttrib4Nuiv(index, v);}
	inline void VertexAttrib4Nusv(GLuint index, const GLushort * v){_detail::VertexAttrib4Nusv(index, v);}
	inline void VertexAttrib4bv(GLuint index, const GLbyte * v){_detail::VertexAttrib4bv(index, v);}
	inline void VertexAttrib4d(GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w){_detail::VertexAttrib4d(index, x, y, z, w);}
	inline void VertexAttrib4dv(GLuint index, const GLdouble * v){_detail::VertexAttrib4dv(index, v);}
	inline void VertexAttrib4f(GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w){_detail::VertexAttrib4f(index, x, y, z, w);}
	inline void VertexAttrib4fv(GLuint index, const GLfloat * v){_detail::VertexAttrib4fv(index, v);}
	inline void VertexAttrib4iv(GLuint index, const GLint * v){_detail::VertexAttrib4iv(index, v);}
	inline void VertexAttrib4s(GLuint index, GLshort x, GLshort y, GLshort z, GLshort w){_detail::VertexAttrib4s(index, x, y, z, w);}
	inline void VertexAttrib4sv(GLuint index, const GLshort * v){_detail::VertexAttrib4sv(index, v);}
	inline void VertexAttrib4ubv(GLuint index, const GLubyte * v){_detail::VertexAttrib4ubv(index, v);}
	inline void VertexAttrib4uiv(GLuint index, const GLuint * v){_detail::VertexAttrib4uiv(index, v);}
	inline void VertexAttrib4usv(GLuint index, const GLushort * v){_detail::VertexAttrib4usv(index, v);}
	inline void VertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void * pointer){_detail::VertexAttribPointer(index, size, type, normalized, stride, pointer);}
	
	inline void UniformMatrix2x3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value){_detail::UniformMatrix2x3fv(location, count, transpose, value);}
	inline void UniformMatrix2x4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value){_detail::UniformMatrix2x4fv(location, count, transpose, value);}
	inline void UniformMatrix3x2fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value){_detail::UniformMatrix3x2fv(location, count, transpose, value);}
	inline void UniformMatrix3x4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value){_detail::UniformMatrix3x4fv(location, count, transpose, value);}
	inline void UniformMatrix4x2fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value){_detail::UniformMatrix4x2fv(location, count, transpose, value);}
	inline void UniformMatrix4x3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value){_detail::UniformMatrix4x3fv(location, count, transpose, value);}
	
	inline void BeginConditionalRender(GLuint id, GLenum mode){_detail::BeginConditionalRender(id, mode);}
	inline void BeginTransformFeedback(GLenum primitiveMode){_detail::BeginTransformFeedback(primitiveMode);}
	inline void BindBufferBase(GLenum target, GLuint index, GLuint buffer){_detail::BindBufferBase(target, index, buffer);}
	inline void BindBufferRange(GLenum target, GLuint index, GLuint buffer, GLintptr offset, GLsizeiptr size){_detail::BindBufferRange(target, index, buffer, offset, size);}
	inline void BindFragDataLocation(GLuint program, GLuint color, const GLchar * name){_detail::BindFragDataLocation(program, color, name);}
	inline void BindFramebuffer(GLenum target, GLuint framebuffer){_detail::BindFramebuffer(target, framebuffer);}
	inline void BindRenderbuffer(GLenum target, GLuint renderbuffer){_detail::BindRenderbuffer(target, renderbuffer);}
	inline void BindVertexArray(GLuint ren_array){_detail::BindVertexArray(ren_array);}
	inline void BlitFramebuffer(GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter){_detail::BlitFramebuffer(srcX0, srcY0, srcX1, srcY1, dstX0, dstY0, dstX1, dstY1, mask, filter);}
	inline GLenum CheckFramebufferStatus(GLenum target){return _detail::CheckFramebufferStatus(target);}
	inline void ClampColor(GLenum target, GLenum clamp){_detail::ClampColor(target, clamp);}
	inline void ClearBufferfi(GLenum buffer, GLint drawbuffer, GLfloat depth, GLint stencil){_detail::ClearBufferfi(buffer, drawbuffer, depth, stencil);}
	inline void ClearBufferfv(GLenum buffer, GLint drawbuffer, const GLfloat * value){_detail::ClearBufferfv(buffer, drawbuffer, value);}
	inline void ClearBufferiv(GLenum buffer, GLint drawbuffer, const GLint * value){_detail::ClearBufferiv(buffer, drawbuffer, value);}
	inline void ClearBufferuiv(GLenum buffer, GLint drawbuffer, const GLuint * value){_detail::ClearBufferuiv(buffer, drawbuffer, value);}
	inline void ColorMaski(GLuint index, GLboolean r, GLboolean g, GLboolean b, GLboolean a){_detail::ColorMaski(index, r, g, b, a);}
	inline void DeleteFramebuffers(GLsizei n, const GLuint * framebuffers){_detail::DeleteFramebuffers(n, framebuffers);}
	inline void DeleteRenderbuffers(GLsizei n, const GLuint * renderbuffers){_detail::DeleteRenderbuffers(n, renderbuffers);}
	inline void DeleteVertexArrays(GLsizei n, const GLuint * arrays){_detail::DeleteVertexArrays(n, arrays);}
	inline void Disablei(GLenum target, GLuint index){_detail::Disablei(target, index);}
	inline void Enablei(GLenum target, GLuint index){_detail::Enablei(target, index);}
	inline void EndConditionalRender(void){_detail::EndConditionalRender();}
	inline void EndTransformFeedback(void){_detail::EndTransformFeedback();}
	inline void FlushMappedBufferRange(GLenum target, GLintptr offset, GLsizeiptr length){_detail::FlushMappedBufferRange(target, offset, length);}
	inline void FramebufferRenderbuffer(GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer){_detail::FramebufferRenderbuffer(target, attachment, renderbuffertarget, renderbuffer);}
	inline void FramebufferTexture1D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level){_detail::FramebufferTexture1D(target, attachment, textarget, texture, level);}
	inline void FramebufferTexture2D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level){_detail::FramebufferTexture2D(target, attachment, textarget, texture, level);}
	inline void FramebufferTexture3D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLint zoffset){_detail::FramebufferTexture3D(target, attachment, textarget, texture, level, zoffset);}
	inline void FramebufferTextureLayer(GLenum target, GLenum attachment, GLuint texture, GLint level, GLint layer){_detail::FramebufferTextureLayer(target, attachment, texture, level, layer);}
	inline void GenFramebuffers(GLsizei n, GLuint * framebuffers){_detail::GenFramebuffers(n, framebuffers);}
	inline void GenRenderbuffers(GLsizei n, GLuint * renderbuffers){_detail::GenRenderbuffers(n, renderbuffers);}
	inline void GenVertexArrays(GLsizei n, GLuint * arrays){_detail::GenVertexArrays(n, arrays);}
	inline void GenerateMipmap(GLenum target){_detail::GenerateMipmap(target);}
	inline void GetBooleani_v(GLenum target, GLuint index, GLboolean * data){_detail::GetBooleani_v(target, index, data);}
	inline GLint GetFragDataLocation(GLuint program, const GLchar * name){return _detail::GetFragDataLocation(program, name);}
	inline void GetFramebufferAttachmentParameteriv(GLenum target, GLenum attachment, GLenum pname, GLint * params){_detail::GetFramebufferAttachmentParameteriv(target, attachment, pname, params);}
	inline void GetIntegeri_v(GLenum target, GLuint index, GLint * data){_detail::GetIntegeri_v(target, index, data);}
	inline void GetRenderbufferParameteriv(GLenum target, GLenum pname, GLint * params){_detail::GetRenderbufferParameteriv(target, pname, params);}
	inline const GLubyte * GetStringi(GLenum name, GLuint index){return _detail::GetStringi(name, index);}
	inline void GetTexParameterIiv(GLenum target, GLenum pname, GLint * params){_detail::GetTexParameterIiv(target, pname, params);}
	inline void GetTexParameterIuiv(GLenum target, GLenum pname, GLuint * params){_detail::GetTexParameterIuiv(target, pname, params);}
	inline void GetTransformFeedbackVarying(GLuint program, GLuint index, GLsizei bufSize, GLsizei * length, GLsizei * size, GLenum * type, GLchar * name){_detail::GetTransformFeedbackVarying(program, index, bufSize, length, size, type, name);}
	inline void GetUniformuiv(GLuint program, GLint location, GLuint * params){_detail::GetUniformuiv(program, location, params);}
	inline void GetVertexAttribIiv(GLuint index, GLenum pname, GLint * params){_detail::GetVertexAttribIiv(index, pname, params);}
	inline void GetVertexAttribIuiv(GLuint index, GLenum pname, GLuint * params){_detail::GetVertexAttribIuiv(index, pname, params);}
	inline GLboolean IsEnabledi(GLenum target, GLuint index){return _detail::IsEnabledi(target, index);}
	inline GLboolean IsFramebuffer(GLuint framebuffer){return _detail::IsFramebuffer(framebuffer);}
	inline GLboolean IsRenderbuffer(GLuint renderbuffer){return _detail::IsRenderbuffer(renderbuffer);}
	inline GLboolean IsVertexArray(GLuint ren_array){return _detail::IsVertexArray(ren_array);}
	inline void * MapBufferRange(GLenum target, GLintptr offset, GLsizeiptr length, GLbitfield access){return _detail::MapBufferRange(target, offset, length, access);}
	inline void RenderbufferStorage(GLenum target, GLenum internalformat, GLsizei width, GLsizei height){_detail::RenderbufferStorage(target, internalformat, width, height);}
	inline void RenderbufferStorageMultisample(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height){_detail::RenderbufferStorageMultisample(target, samples, internalformat, width, height);}
	inline void TexParameterIiv(GLenum target, GLenum pname, const GLint * params){_detail::TexParameterIiv(target, pname, params);}
	inline void TexParameterIuiv(GLenum target, GLenum pname, const GLuint * params){_detail::TexParameterIuiv(target, pname, params);}
	inline void TransformFeedbackVaryings(GLuint program, GLsizei count, const GLchar *const* varyings, GLenum bufferMode){_detail::TransformFeedbackVaryings(program, count, varyings, bufferMode);}
	inline void Uniform1ui(GLint location, GLuint v0){_detail::Uniform1ui(location, v0);}
	inline void Uniform1uiv(GLint location, GLsizei count, const GLuint * value){_detail::Uniform1uiv(location, count, value);}
	inline void Uniform2ui(GLint location, GLuint v0, GLuint v1){_detail::Uniform2ui(location, v0, v1);}
	inline void Uniform2uiv(GLint location, GLsizei count, const GLuint * value){_detail::Uniform2uiv(location, count, value);}
	inline void Uniform3ui(GLint location, GLuint v0, GLuint v1, GLuint v2){_detail::Uniform3ui(location, v0, v1, v2);}
	inline void Uniform3uiv(GLint location, GLsizei count, const GLuint * value){_detail::Uniform3uiv(location, count, value);}
	inline void Uniform4ui(GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3){_detail::Uniform4ui(location, v0, v1, v2, v3);}
	inline void Uniform4uiv(GLint location, GLsizei count, const GLuint * value){_detail::Uniform4uiv(location, count, value);}
	inline void VertexAttribI1i(GLuint index, GLint x){_detail::VertexAttribI1i(index, x);}
	inline void VertexAttribI1iv(GLuint index, const GLint * v){_detail::VertexAttribI1iv(index, v);}
	inline void VertexAttribI1ui(GLuint index, GLuint x){_detail::VertexAttribI1ui(index, x);}
	inline void VertexAttribI1uiv(GLuint index, const GLuint * v){_detail::VertexAttribI1uiv(index, v);}
	inline void VertexAttribI2i(GLuint index, GLint x, GLint y){_detail::VertexAttribI2i(index, x, y);}
	inline void VertexAttribI2iv(GLuint index, const GLint * v){_detail::VertexAttribI2iv(index, v);}
	inline void VertexAttribI2ui(GLuint index, GLuint x, GLuint y){_detail::VertexAttribI2ui(index, x, y);}
	inline void VertexAttribI2uiv(GLuint index, const GLuint * v){_detail::VertexAttribI2uiv(index, v);}
	inline void VertexAttribI3i(GLuint index, GLint x, GLint y, GLint z){_detail::VertexAttribI3i(index, x, y, z);}
	inline void VertexAttribI3iv(GLuint index, const GLint * v){_detail::VertexAttribI3iv(index, v);}
	inline void VertexAttribI3ui(GLuint index, GLuint x, GLuint y, GLuint z){_detail::VertexAttribI3ui(index, x, y, z);}
	inline void VertexAttribI3uiv(GLuint index, const GLuint * v){_detail::VertexAttribI3uiv(index, v);}
	inline void VertexAttribI4bv(GLuint index, const GLbyte * v){_detail::VertexAttribI4bv(index, v);}
	inline void VertexAttribI4i(GLuint index, GLint x, GLint y, GLint z, GLint w){_detail::VertexAttribI4i(index, x, y, z, w);}
	inline void VertexAttribI4iv(GLuint index, const GLint * v){_detail::VertexAttribI4iv(index, v);}
	inline void VertexAttribI4sv(GLuint index, const GLshort * v){_detail::VertexAttribI4sv(index, v);}
	inline void VertexAttribI4ubv(GLuint index, const GLubyte * v){_detail::VertexAttribI4ubv(index, v);}
	inline void VertexAttribI4ui(GLuint index, GLuint x, GLuint y, GLuint z, GLuint w){_detail::VertexAttribI4ui(index, x, y, z, w);}
	inline void VertexAttribI4uiv(GLuint index, const GLuint * v){_detail::VertexAttribI4uiv(index, v);}
	inline void VertexAttribI4usv(GLuint index, const GLushort * v){_detail::VertexAttribI4usv(index, v);}
	inline void VertexAttribIPointer(GLuint index, GLint size, GLenum type, GLsizei stride, const void * pointer){_detail::VertexAttribIPointer(index, size, type, stride, pointer);}
	
	inline void CopyBufferSubData(GLenum readTarget, GLenum writeTarget, GLintptr readOffset, GLintptr writeOffset, GLsizeiptr size){_detail::CopyBufferSubData(readTarget, writeTarget, readOffset, writeOffset, size);}
	inline void DrawArraysInstanced(GLenum mode, GLint first, GLsizei count, GLsizei instancecount){_detail::DrawArraysInstanced(mode, first, count, instancecount);}
	inline void DrawElementsInstanced(GLenum mode, GLsizei count, GLenum type, const void * indices, GLsizei instancecount){_detail::DrawElementsInstanced(mode, count, type, indices, instancecount);}
	inline void GetActiveUniformBlockName(GLuint program, GLuint uniformBlockIndex, GLsizei bufSize, GLsizei * length, GLchar * uniformBlockName){_detail::GetActiveUniformBlockName(program, uniformBlockIndex, bufSize, length, uniformBlockName);}
	inline void GetActiveUniformBlockiv(GLuint program, GLuint uniformBlockIndex, GLenum pname, GLint * params){_detail::GetActiveUniformBlockiv(program, uniformBlockIndex, pname, params);}
	inline void GetActiveUniformName(GLuint program, GLuint uniformIndex, GLsizei bufSize, GLsizei * length, GLchar * uniformName){_detail::GetActiveUniformName(program, uniformIndex, bufSize, length, uniformName);}
	inline void GetActiveUniformsiv(GLuint program, GLsizei uniformCount, const GLuint * uniformIndices, GLenum pname, GLint * params){_detail::GetActiveUniformsiv(program, uniformCount, uniformIndices, pname, params);}
	inline GLuint GetUniformBlockIndex(GLuint program, const GLchar * uniformBlockName){return _detail::GetUniformBlockIndex(program, uniformBlockName);}
	inline void GetUniformIndices(GLuint program, GLsizei uniformCount, const GLchar *const* uniformNames, GLuint * uniformIndices){_detail::GetUniformIndices(program, uniformCount, uniformNames, uniformIndices);}
	inline void PrimitiveRestartIndex(GLuint index){_detail::PrimitiveRestartIndex(index);}
	inline void TexBuffer(GLenum target, GLenum internalformat, GLuint buffer){_detail::TexBuffer(target, internalformat, buffer);}
	inline void UniformBlockBinding(GLuint program, GLuint uniformBlockIndex, GLuint uniformBlockBinding){_detail::UniformBlockBinding(program, uniformBlockIndex, uniformBlockBinding);}
	
	
	namespace sys
	{
		
		exts::LoadTest LoadFunctions();
		
		int GetMinorVersion();
		int GetMajorVersion();
		bool IsVersionGEQ(int majorVersion, int minorVersion);
		
	} //namespace sys
} //namespace gl
#endif //FUNCTION_CPP_GENERATED_HEADEROPENGL_HPP
