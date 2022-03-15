/* File : fields.c
 * Description : contains methods for creating and managing fields
 * Date : 14.3.22
 * Author : Shivashish Das
 */

#include "include/fields.h"
#include "include/mem.h"
#include "include/reader.h"

static void fill_fields(fields**, u2_t, FILE*);

void init_fields(fields** fd, u2_t sz, FILE* fptr) {
	*fd = (fields*) mem_alloc(sizeof (fields) * sz);
	fill_fields(fd,sz,fptr);
}

static void fill_fields(fields** fd, u2_t sz, FILE* fptr) {
	fields* field = *fd;
	for (int i = 0; i < sz; i++) {
		field[i].acc = get_field_flags(read_u2(fptr));
		field[i].n_index = read_u2(fptr);
		field[i].desc_index = read_u2(fptr);
		field[i].attr = create_attr(fptr);
	}
}


