#include "foop.h"
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

void *_this;

void *foop_new(const class_t *class) {
	void *mem = calloc(1, class->size + sizeof(void *));
	_this = ((char *) mem) + sizeof(void *);

	memcpy(mem, &class, sizeof(void *));

	if(class->constructor != NULL) {
		class->constructor();
	}

	return _this;
}

void foop_delete(void *object) {
	void *mem = ((char *) object) - sizeof(void *);
	_this = object;

	class_t *class;

	memcpy(&class, mem, sizeof(void *));

	if(class->destructor != NULL) {
		class->destructor();
	}

	free(mem);
}

bool foop_instanceOf(const class_t *class, void *object) {
	class_t *objectClass;
	memcpy(&objectClass, ((char *) object) - sizeof(void *), sizeof(void *));

	return objectClass == class;
}

void foop_reconstruct(void *object) {
	_this = object;

	class_t *class;
	memcpy(&class, ((char *) object) - sizeof(void *), sizeof(void *));

	if(class->destructor) {
		class->destructor();
	}

	if(class->constructor) {
		class->constructor();
	}
}
