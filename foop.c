#include "foop.h"
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

void *foop_new(class_t *class) {
	void *mem = malloc(class->size + sizeof(void *));
	void *object = ((char *) mem) + sizeof(void *);

	memcpy(mem, &class->destructor, sizeof(void *));
	class->constructor(object);

	return object;
}

void foop_delete(void *object) {
	void *mem = ((char *) object) - sizeof(void *);
	void (*destructor)(void *);

	memcpy(&(destructor), mem, sizeof(void *));
	destructor(object);

	free(mem);
}
