# foop
C Framework for Object-Orientated Programming

## How do I *foop*?

* Include the *foop* library

``` c
#include <stdio.h>
#include <string.h>
#include "foop.h"
```

* Make a class

``` C
struct User {
	char name[20];
	int age;
};

void UserConstructor(void *object) {
	struct User *user = object;

	// set a default name and age
	strcpy(user->name, "John");
	user->age = 23;

	printf("Created a user!\n");
}

void UserDestructor(void *object) {
	struct User *user = object;

	printf("Deleting user '%s'\n", user->name);
}

class_t User = {
	&UserConstructor,
	&UserDestructor,
	sizeof(struct User)
};
```

* Make an instance of your class (an object)

``` C
int main() {
	struct User *user = new(&User);
	strcpy(user->name, "Monty");
}
```

* Delete it

``` C
int main() {
	struct User *user = new(&User);
	strcpy(user->name, "Monty");

	delete(user);
}
```

* You're done!

```
$ ./test
Created a user.
Deleting user 'Monty'.
```

## Type-specific routing in functions

``` C
#include <stdio.h>
#include <string.h>
#include "foop.h"

// make two classes, Guitarist and Bassist

struct Guitarist {
	char name[20];
	char guitar[20];
};

struct Bassist {
	char name[25];
	char bass[25];
};

const class_t Guitarist = {
	NULL,
	NULL,
	sizeof(struct Guitarist)
};

const class_t Bassist = {
	NULL,
	NULL,
	sizeof(struct Bassist)
};

// playInstrument can take either object

void playInstrument(void *player) {
	// behaviour can change based on class using instanceOf()

	if(instanceOf(&Guitarist, player)) {
		struct Guitarist *guitarist = player;

		printf("%s plays their %s guitar!\n", guitarist->name, guitarist->guitar);
	} else if(instanceOf(&Bassist, player)) {
		struct Bassist *bassist = player;

		printf("%s plays their %s bass!\n", bassist->name, bassist->bass);
	}
}

int main() {
	struct Guitarist *jane = new(&Guitarist);

	strcpy(jane->name, "Jane");
	strcpy(jane->guitar, "Les Paul");

	struct Bassist *sam = new(&Bassist);

	strcpy(sam->name, "Sam");
	strcpy(sam->bass, "Mustang");

	playInstrument(jane);
	playInstrument(sam);
}
```
