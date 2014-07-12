#include <cassert>
#include <cstdlib>
#include <memory>

#include "libfoo.h"

namespace libfoo {

    template<typename T>
    struct traits;

    template<>
    struct traits<foo_thing1_t> {
        typedef foo_thing1_t value_type;
        typedef decltype(&foo_thing1_destroy) deleter_type;
        typedef std::unique_ptr<value_type, deleter_type> unique_ptr;
    };

    template<>
    struct traits<foo_thing2_t> {
        typedef foo_thing2_t value_type;
        typedef decltype(&foo_thing2_destroy) deleter_type;
        typedef std::unique_ptr<value_type, deleter_type> unique_ptr;
    };

    template<typename T>
    using unique_ptr = typename traits<T>::unique_ptr;

} // namespace libfoo

int main(int argc, char* argv[]) {

    libfoo::unique_ptr<foo_thing1_t> thing1{foo_thing1_create(), &foo_thing1_destroy};
    libfoo::unique_ptr<foo_thing2_t> thing2_a{foo_thing2_create(0.0), &foo_thing2_destroy};
    libfoo::unique_ptr<foo_thing2_t> thing2_b{foo_thing2_create(42.0), &foo_thing2_destroy};

    thing2_b->val = thing1->val * thing2_a->val;
    assert(thing2_b->val == 0.0);

    return EXIT_SUCCESS;
}
