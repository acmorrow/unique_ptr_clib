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
        using ctor_type = decltype(&foo_thing1_create);
        using dtor_type = decltype(&foo_thing1_destroy);
        static const ctor_type ctor;
        static const dtor_type dtor;
    };
    const typename lifecycle_traits<foo_thing1_t>::ctor_type lifecycle_traits<foo_thing1_t>::ctor = foo_thing1_create;
    const typename lifecycle_traits<foo_thing1_t>::dtor_type lifecycle_traits<foo_thing1_t>::dtor = foo_thing1_destroy;

    template<>
    struct lifecycle_traits<foo_thing2_t> {
        using value_type = foo_thing2_t;
        using ctor_type = decltype(&foo_thing2_create);
        using dtor_type = decltype(&foo_thing2_destroy);
        static const ctor_type ctor;
        static const dtor_type dtor;
    };
    const typename lifecycle_traits<foo_thing2_t>::ctor_type lifecycle_traits<foo_thing2_t>::ctor = foo_thing2_create;
    const typename lifecycle_traits<foo_thing2_t>::dtor_type lifecycle_traits<foo_thing2_t>::dtor = foo_thing2_destroy;

    template<typename T>
    struct traits {
        using lifecycle = lifecycle_traits<T>;
        using deleter_type = decltype(lifecycle::dtor);
        using unique_ptr = std::unique_ptr<typename lifecycle::value_type, deleter_type>;
    };

    template<typename T>
    using unique_ptr = typename traits<T>::unique_ptr;

    template<typename T, class... Args>
    unique_ptr<T> make_unique(Args&& ...args) {
        using lifecycle = typename traits<T>::lifecycle;
        using unique_ptr = unique_ptr<T>;
        return unique_ptr(lifecycle::ctor(std::forward<Args>(args)...), lifecycle::dtor);
    }

    template<typename T, class... Args>
    std::shared_ptr<T> make_shared(Args&& ...args) {
        using lifecycle = typename traits<T>::lifecycle;
        return std::shared_ptr<T>(lifecycle::ctor(std::forward<Args>(args)...), lifecycle::dtor);
    }

} // namespace libfoo

int main(int argc, char* argv[]) {

    auto thing1 = libfoo::make_unique<foo_thing1_t>();
    auto thing2_a = libfoo::make_unique<foo_thing2_t>(0.0);
    auto thing2_b = libfoo::make_shared<foo_thing2_t>(42.0);

    thing2_b->val = thing1->val * thing2_a->val;
    assert(thing2_b->val == 0.0);

    return EXIT_SUCCESS;
}
