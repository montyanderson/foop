#ifndef FOOP
#define FOOP

#include <stdio.h>
#include <stdbool.h>

typedef struct {
	void (*constructor)();
	void (*destructor)();
	size_t size;
} class_t;

extern void *_this;

void *foop_new(const class_t *class);
void foop_delete(void *object);
const class_t *foop_instanceOf(void *object);

#define foop_$(object) ((typeof((object))) (_this = (object)))

#ifndef FOOP_NOCONFLICT

#define new foop_new
#define delete foop_delete
#define instanceOf foop_instanceOf
#define reconstruct foop_reconstruct
#define $ foop_$

#endif

#endif
