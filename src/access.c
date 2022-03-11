#include "include/access.h"
#include "include/types.h"

/* class access flags copied from the JVM spec*/

#define ACC_PUBLIC	0x0001	// Declared public; may be accessed from outside its package.
#define ACC_FINAL	0x0010	// Declared final; no subclasses allowed.
#define ACC_SUPER	0x0020	// Treat superclass methods specially when invoked by the invokespecial instruction.
#define ACC_INTERFACE	0x0200	// Is an interface, not a class.
#define ACC_ABSTRACT	0x0400	// Declared abstract; must not be instantiated.
#define ACC_SYNTHETIC	0x1000	// Declared synthetic; not present in the source code.
#define ACC_ANNOTATION	0x2000	// Declared as an annotation type.
#define ACC_ENUM	0x4000	// Declared as an enum type.


flags get_flags(u2_t acc_flags) {
    flags fs = {0};
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
    return fs;
}