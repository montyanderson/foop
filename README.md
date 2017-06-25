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
