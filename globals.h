
//! \file miscellaneous utilities used everywhere...

#ifndef GLOBALS_SkipH
#define GLOBALS_SkipH

#include <iostream>
#include <stdexcept>

///********** \section filesystem utilities

/// mkdir getcwd chdir, #if (__cplusplus >= 201703L) should be true
#include <filesystem>
inline std::string getpwd() { return std::filesystem::current_path().string(); }
inline int mkdirs(const std::string& dir) {std::error_code ec; std::filesystem::create_directories(dir, ec);	 return ec.value(); /*std::filesystem::permissions(dir, filesystem::perms::owner_all, filesystem::perm_options::add);*/}
inline int chdir(const std::string& dir) {std::error_code ec;  std::filesystem::current_path(dir,ec); return ec.value(); }
#define  _TRY_(_syscmnd_) std::string((_syscmnd_==0) ?  " succeed " : " failed ")


///********** \section Lazy Hacks

/// Generate SiRun and VxlPro help messages
#define KeyHint(_args_desc_)  if(ins.peek()=='?') {	ins.str(_args_desc_); return 0; }

//! Non-folding brackets for namespace '{' and '}', to be used in early stages of code development
#define _begins_       {
#define _end_of_(sec)  }

#if defined __has_cpp_attribute
    #if __has_cpp_attribute(fallthrough)
        #define fallThrough [[fallthrough]]
    #else
        #define fallThrough
    #endif
#else
    #define fallThrough
#endif


#ifdef _GeanyHighlighTricKeys
class vector {};  class for_ {};  class for_i {};  class fori0to {};
class iterator {}; class fluidf {}; class Elem{}; class dbl {}; class string {};
class map {}; class T {}; class endl {}; class cout {}; class cerr {};
namespace std {}
#endif


///********** \section String utilities

//using _s = std::to_string  is bad in decimal notation
template<typename T> std::string toStr(const T& n){  std::ostringstream ss;  ss<<n;  return ss.str();  } //outdated
template<typename T> std::string _s(const T& n){  std::ostringstream ss;  ss<<n;  return ss.str();  }
template<typename T> bool hasExt(const T& path, size_t siz, const char* ext) { return path.size()>siz && path.compare(path.size()-siz, siz, ext) == 0; }
template<typename T> bool hasExt(const T& path, const std::string& ext) { return path.size()>ext.size() && path.compare(path.size()-ext.size(), ext. size(),ext) == 0; }

//stringify macro args after (sub)macro expansion
#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)

#define __FILEBASENAME__ std::string(strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__, strcspn (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__,"."))




///********** \section Testing and error handling

/// ensure, alert (and ifnot hack)  runtime checks

// Run-time check and testing macros
inline bool _cerr_(std::string msg="", int xit=0) {
	// for debugger breakpoints: don't optimize out please !!!
 if(xit)
		throw std::runtime_error("\n\n"+msg+"\n");
	else
		std::cerr<< "\n"+msg <<std::endl;
	return true;
}
#ifdef EXPERIMENTAL
	 #define ERR_HDR(xit)  std::string(__FILE__)+":"+_s(__LINE__)+" in "+ std::string(__FUNCTION__)+", "  \
				+std::string(xit?" Error: ":" Warning: ")
#else
	 #define ERR_HDR(xit)  std::string(xit?" Error: ":" Warning: ")
#endif
#define ensure1(isOk)           (!((isOk)|| _cerr_(ERR_HDR(0)  +std::string(#isOk))))
#define ensure2(isOk, msg)      (!((isOk)|| _cerr_(ERR_HDR(0)  +"\""+msg+"\""     )))
#define ensure3(isOk, msg, xit) (!((isOk)|| _cerr_(ERR_HDR(xit)+"\""+msg+"\"", xit)))
#define GET_MACRO3(_1,_2,_3,NAME,...) NAME

//! Validation/production phase ensure/assert. Usage:
//!   \code{.cpp} ensure(condition, "message", int throw_on_error=false); \endcode
#define ensure(...)  GET_MACRO3(__VA_ARGS__, ensure3, ensure2, ensure1, "Only 1 to 3 args please")(__VA_ARGS__)
#define alert(...)  GET_MACRO3(false,__VA_ARGS__, ensure3, ensure2, "Only 1 to 2 args please")(false,__VA_ARGS__)

#define ifnot(isOk, msg)  if(!(isOk)&& std::cout<<msg<<endl)
#define enforce ensure

/// Kinder @xception alternative to exit(-1)
class xception : public std::exception {
	std::string msg_;
 public:
	xception(const std::string& what): msg_(what) {};
	const char* what() const noexcept override { return msg_.c_str(); };
};


///********** \section outdated

#ifdef _debugCompile_ // by default do not use the obsolete debugLevel/dbgAsrt
	template<class T> int debuglevel_(T level) {  static int l_=0;  if (level>=0) { l_=level; }  return l_;  }
	#define debugLevel    debuglevel_(-1)
	#define IN_DBG(...) __VA_ARGS__
	#define dbgAsrt(...) (debugLevel<=0 || ensure(__VA_ARGS__))	//! debug assert with message
#else
	#define debugLevel  0
	#define dbgAsrt(...)
	#define IN_DBG(...)
#endif // _debugCompile_
// Note use addr2line for more debugging...


#endif // GLOBALS_SkipH


/*********** \section Hackish initialization of globals in header files
	Usage: `#define _InitGlobals` in one .cpp file before `#include "globals.h"`
    and then `#include "other.h"` files where global variables are defined like:
		`_Extern thread_local int III _Eq( 1+1+1 );`.
	The "other.h" files shall be included only once after #define _InitGlobals in all .cpp files. */
//#ifndef _Extern
#ifdef _InitGlobals
	#define _Extern
	#define _Eq(...)  = __VA_ARGS__
#else
	#define _Extern extern
	#define _Eq(...)
#endif
