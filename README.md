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

## Documentation

### struct class_t

Structure for a class definition.

#### Members

* **void (\*constructor)()** - pointer to a function that constructs the object pointed to at *\_this*. Can be NULL.
* **void (\*destructor)()** - pointer to a function that destructs the object pointed to at *\_this*. Can be NULL.
* **size_t size** - size of the object (instance) structure in bytes.

### void \*new(const class_t \*class)

Returns a pointer to the new object (instance) of the passed class.

* Allocates memory for the object structure + reference to original class
* Call the class *constructor*
* Returns the object

### void delete(void \*object)

Deletes the passed object pointer.

* Calls the class destructor
* Frees memory allocated to object structure + reference to class

### const class_t \*instanceOf(void \*object)

Returns a pointer to the original class used to create the object (instance).

### void foop_reconstruct(void \*object)

Destructs the object and creates a new one in it's place.

* Calls the class destructor
* Zeros out associated memory
* Calls the class constructor

### void \*\_this

Pointer to the object about to be acted upon.

### $(void \*object)

Sets *\_this* to the object and returns the object casted to the type it was passed as.
