#include "reader.h"
#include "error.h"
#include "pool.h"

int check_version (FILE* fptr) {
	/* skip the 2 byte long minor version because now-a-days
	 * its mostly zero anyway
	 */
	skip(fptr,2);

	/* The major class file version actually takes up            
	 * just one byte so we read 2 bytes (to comply with the 
	 * JVM spec which says that it is an unsigned 2 byte integer)
         * and extract the last 2 digits with the bit mask 0x00FF
         */
	
	u2_t ver = read_u2(fptr);
	if ((ver && 0x00FF) > 0x34) 
		return 0;
	return 1;
}

int main (int argc, char* argv[]) {
        FILE* fptr = NULL;
	if (argc<2)
		err_fatal("Expected a filename");
        if ((fptr = fopen(argv[1],"rb")) == NULL)
                err_fatal("File not found");
        u4_t magic = read_u4(fptr);
        if (magic != 0xCAFEBABE)
		err_fatal("Invalid magic number");
	if (!check_version(fptr)) {
		err_fatal("Class file version not supported!");
	}
	init_cp(read_u2(fptr));
	fill_cp(fptr);
	fclose(fptr);
}
