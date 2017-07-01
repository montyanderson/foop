# foop
C Framework for Object-Orientated Programming

* Normal C Code

``` C
struct User user;

user_init(&user);

user_setName(&user, "John");
user_setAge(&user, 37);
user_print(&user, 37);

user_free(&user);
```

* With *foop*

``` C
struct User *user = new(User);

$(user)->setName("John");
$(user)->setAge(37);
$(user)->print();

delete(user);
```

## Features

* Almost non-existent CPU overhead; requires a single extra pointer for a method call.
* Requires only slightly more memory, used for storing reference to the class in an instance and pointers to function methods.
* Very small codebase with large compatibility.

## Documentation

### class_t

Structure for a class definition.

#### Members

* **void (\*constructor)()** - pointer to a function that constructs the object pointed to at *\_this*. Can be NULL.
* **void (\*destructor)()** - pointer to a function that destructs the object pointed to at *\_this*. Can be NULL.
* **size_t size** - size of the object (instance) structure in bytes.

``` C
void UserConstructor() {
	struct User *this = _this;

	strcpy(this->name, "Monty"):
	this->age = 16;
}

void UserDestructor() {
	printf("Deleting User!\n");
}

const class_t _User = {
	&UserConstructor,
	&UserDestructor,
	sizeof(struct User)
};

const class_t *User = &_User;
```

### void \*new(const class_t \*class)

Returns a pointer to the new object (instance) of the passed class.

* Allocates memory for the object structure + reference to original class
* Call the class *constructor*
* Returns the object

``` C
struct User *user = new(User);
```

### void delete(void \*object)

Deletes the passed object pointer.

* Calls the class destructor
* Frees memory allocated to object structure + reference to class

``` C
delete(user);
```

### const class_t \*instanceOf(void \*object)

Returns a pointer to the original class used to create the object (instance).

``` C
instanceOf(user) == User; // true
instanceOf(user) == AnotherClass; // false;
```

### void foop_reconstruct(void \*object)

Destructs the object and creates a new one in it's place.

* Calls the class destructor
* Zeros out associated memory
* Calls the class constructor

### void \*\_this

Pointer to the object about to be acted upon.

``` C
struct User {
	int age;
	void (*birthday)();
}

void UserBirthday() {
	User *this = _this;

	user->age++;
}

void UserConstructor() {
	User *this = _this;

	user->age = 20;
	usser->birthday = &UserBirthday;
}

const class_t _User {
	&UserConstructor,
	NULL, // no destructor needed
	sizeof(struct User)
}

const class_t *User = &_User;

int main() {
	struct User *user = new(User);

	user->age; // 20
	$(user)->birthday();
	user->age; // 21
}
```

### $(void \*object)

Sets *\_this* to the object and returns the object casted to the type it was passed as.
