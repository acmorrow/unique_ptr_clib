#include <cassert>
#include <cstdlib>
#include <memory>

#include "libfoo.h"

int main(int argc, char* argv[]) {

    std::unique_ptr<foo_thing1_t, decltype(&foo_thing1_destroy)> thing1{foo_thing1_create(), &foo_thing1_destroy};
    std::unique_ptr<foo_thing2_t, decltype(&foo_thing2_destroy)> thing2_a{foo_thing2_create(0.0), &foo_thing2_destroy};

    std::unique_ptr<foo_thing2_t, decltype(&foo_thing2_destroy)> thing2_b{foo_thing2_create(42.0), &foo_thing2_destroy};

    thing2_b->val = thing1->val * thing2_a->val;
    assert(thing2_b->val == 0.0);

    return EXIT_SUCCESS;
}
