#ifndef FOOP
#define FOOP

#include <stdio.h>
#include <stdbool.h>

typedef struct {
	void (*constructor)(void *);
	void (*destructor)(void *);
	size_t size;
} class_t;

void *foop_new(const class_t *class);
void foop_delete(void *object);
bool foop_instanceOf(const class_t *class, void *object);

#define new foop_new
#define delete foop_delete
#define instanceOf foop_instanceOf
#define reconstruct foop_reconstruct

#endif
