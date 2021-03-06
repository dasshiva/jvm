/* File : access.c
 * Descrption : defines the access flags and methods to convert the flags of the class file into a *_flags structures
 * Date : 12.3.22
 * Author : dasshiva
 * LICENSE : MIT License (look at the LICENSE file for more details)
 */

#include "include/access.h"
#include "include/types.h"

/* access flags copied from the JVM spec */

#define ACC_PUBLIC	0x0001	// Declared public; may be accessed from outside its package.
#define ACC_FINAL	0x0010	// Declared final; no subclasses allowed or if used for a field then the field can never be directly assigned to after object creation
#define ACC_SUPER	0x0020	// Treat superclass methods specially when invoked by the invokespecial instruction.
#define ACC_INTERFACE	0x0200	// Is an interface, not a class.
#define ACC_ABSTRACT	0x0400	// Declared abstract; must not be instantiated.
#define ACC_PRIVATE	0x0002	// Declared private; usable only within the defining class.
#define ACC_PROTECTED	0x0004	// Declared protected; may be accessed within subclasses.
#define ACC_STATIC	0x0008	// Declared static
#define ACC_VOLATILE	0x0040	// Declared volatile; cannot be cached
#define ACC_TRANSIENT	0x0080	// Declared transient; not written or read by a persistent object manager.
#define ACC_SYNTHETIC	0x1000	// Declared synthetic; not present in the source code.
#define ACC_ANNOTATION	0x2000	// Declared as an annotation type.
#define ACC_ENUM	0x4000	// Declared as an enum type.
#define ACC_SYNCHRONIZED 0x0020	// Declared synchronized; invocation is wrapped by a monitor use.
#define ACC_BRIDGE	0x0040	// A bridge method, generated by the compiler.
#define ACC_VARARGS	0x0080	// Declared with variable number of arguments.
#define ACC_NATIVE	0x0100	// Declared native; implemented in a language other than Java.
#define ACC_STRICT      0x0800 // Declared strictfp; floating-point mode is FP-strict.

cl_flags get_class_flags(u2_t acc_flags) {	
    cl_flags fs = {0};
    if (acc_flags & ACC_PUBLIC)
	    fs.ispublic = 1;
    if (acc_flags & ACC_FINAL) 
	    fs.isfinal = 1;
    if (acc_flags & ACC_INTERFACE)
	    fs.isinterface = 1;
    if (acc_flags & ACC_ABSTRACT)
	    fs.isabstract = 1;
    if (acc_flags & ACC_ENUM)
	    fs.isenum = 1 ;
    if (acc_flags & ACC_ANNOTATION)
	    fs.isannotation = 1;
    if (acc_flags & ACC_SYNTHETIC)
	    fs.issynthetic = 1;
    return fs;
}

fl_flags get_field_flags (u2_t acc_flags) {
	fl_flags fs = {0};
	if (acc_flags & ACC_PUBLIC)
		fs.ispublic = 1;      
	if (acc_flags & ACC_PROTECTED) 
		fs.isprotected = 1;
	if (acc_flags & ACC_PRIVATE)
		fs.isprivate = 1;
	if (acc_flags & ACC_STATIC)
		fs.isstatic = 1;
	if (acc_flags & ACC_FINAL)                            
		fs.isfinal = 1;
	if (acc_flags & ACC_VOLATILE)
		fs.isvolatile = 1;
	if (acc_flags & ACC_TRANSIENT)
		fs.istransient = 1;
	if (acc_flags & ACC_ENUM)                                                     fs.isenum = 1 ; 
	if (acc_flags & ACC_SYNTHETIC)
		fs.issynthetic = 1;
	return fs;
}

mt_flags get_method_flags (u2_t acc_flags) {
	mt_flags fs = {0};
	if (acc_flags & ACC_PUBLIC)
		fs.ispublic = 1;
	if (acc_flags & ACC_PROTECTED)
		fs.isprotected = 1;
	if (acc_flags & ACC_PRIVATE) 
		fs.isprivate = 1;
	if (acc_flags & ACC_STATIC)
		fs.isstatic = 1;
	if (acc_flags & ACC_FINAL)
		fs.isfinal = 1;                                      
	if (acc_flags & ACC_SYNCHRONIZED)
		fs.issync = 1;
	if (acc_flags & ACC_BRIDGE)
		fs.isbridge = 1;
	if (acc_flags & ACC_NATIVE)
		fs.isnative = 1;
	if (acc_flags & ACC_ABSTRACT)
		fs.isabstract = 1;
	if (acc_flags & ACC_STRICT)
		fs.isstrict = 1;
	if (acc_flags & ACC_SYNTHETIC)
		fs.issynthetic = 1;
	return fs;
}

