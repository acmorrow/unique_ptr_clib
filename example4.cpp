#include <cassert>
#include <cstdlib>
#include <memory>

#include "libfoo.h"

namespace libfoo {

    template<typename T>
    struct lifecycle_traits;

    template<>
    struct lifecycle_traits<foo_thing1_t> {
        using value_type = foo_thing1_t;
        using dtor_type = decltype(&foo_thing1_destroy);
    };

    template<>
    struct lifecycle_traits<foo_thing2_t> {
        using value_type = foo_thing2_t;
        using dtor_type = decltype(&foo_thing2_destroy);
    };

    template<typename T>
    struct traits {
        using lifecycle = lifecycle_traits<T>;
        using dtor_type = typename lifecycle::dtor_type;
        using unique_ptr = std::unique_ptr<typename lifecycle::value_type, dtor_type>;
    };

    template<typename T>
    using unique_ptr = typename traits<T>::unique_ptr;

} // namespace lbfoo

int main(int argc, char* argv[]) {

    libfoo::unique_ptr<foo_thing1_t> thing1{foo_thing1_create(), &foo_thing1_destroy};
    libfoo::unique_ptr<foo_thing2_t> thing2_a{foo_thing2_create(0.0), &foo_thing2_destroy};
    libfoo::unique_ptr<foo_thing2_t> thing2_b{foo_thing2_create(42), &foo_thing2_destroy};

    thing2_b->val = thing1->val * thing2_a->val;
    assert(thing2_b->val == 0.0);

    return EXIT_SUCCESS;
}
