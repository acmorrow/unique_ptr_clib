#include "libfoo.h"

#include <stdio.h>
#include <stdlib.h>

foo_thing1_t* foo_thing1_create() {
    foo_thing1_t* new_thing1 = calloc(1U, sizeof(foo_thing1_t));
    printf("libfoo: created a new thing1_t at %p\n", new_thing1);
    new_thing1->val = 42;
    return new_thing1;
}

void foo_thing1_destroy(foo_thing1_t* thing1) {
    printf("libfoo: destroying a thing1_t at %p\n", thing1);
    free(thing1);
}

foo_thing2_t* foo_thing2_create(double value) {
    foo_thing2_t* new_thing2 = calloc(1U, sizeof(foo_thing2_t));
    printf("libfoo: created a new thing2_t at %p\n", new_thing2);
    new_thing2->val = value;
    return new_thing2;
}

void foo_thing2_destroy(foo_thing2_t* thing2) {
    printf("libfoo: destroying a thing2_t at %p\n", thing2);
    free(thing2);
}

void foo_thing2_print(foo_thing2_t const* thing2) {
    printf("libfoo: thing2 at %p has value %f\n", thing2, thing2->val);
}
