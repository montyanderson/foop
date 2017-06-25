#ifndef FOOP
#define FOOP

#include <stdio.h>

typedef struct {
	void (*constructor)(void *);
	void (*destructor)(void *);
	size_t size;
} class_t;

void *foop_new(class_t *class);
void foop_delete(void *object);

#define new foop_new
#define delete foop_delete

#endif
