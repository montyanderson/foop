#include "foop.h"
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

void *foop_new(const class_t *class) {
	void *mem = malloc(class->size + sizeof(void *));
	void *object = ((char *) mem) + sizeof(void *);

	memcpy(mem, &class, sizeof(void *));

	if(class->constructor != NULL) {
		class->constructor(object);
	}

	return object;
}

void foop_delete(void *object) {
	void *mem = ((char *) object) - sizeof(void *);
	class_t *class;

	memcpy(&class, mem, sizeof(void *));

	if(class->destructor != NULL) {
		class->destructor(object);
	}

	free(mem);
}

bool foop_instanceOf(const class_t *class, void *object) {
	class_t *objectClass;
	memcpy(&objectClass, ((char *) object) - sizeof(void *), sizeof(void *));

	return objectClass == class;
}

void foop_reconstruct(void *object) {
	class_t *class;
	memcpy(&class, ((char *) object) - sizeof(void *), sizeof(void *));

	if(class->destructor) {
		class->destructor(object);
	}

	if(class->constructor) {
		class->constructor(object);
	}
}
