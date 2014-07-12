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

    class thing1_t {
    public:
        template<class... Args>
        explicit thing1_t(Args&& ...args)
            : _thing{make_unique<foo_thing1_t>(std::forward<Args>(args)...)} {};

        int value() const {
            return _thing->val;
        }

        void value(int value) const {
            _thing->val = value;
        }

    private:
        unique_ptr<foo_thing1_t> _thing;
    };

    class thing2_t {
    public:
        template<class... Args>
        explicit thing2_t(Args&& ...args)
            : _thing{make_unique<foo_thing2_t>(std::forward<Args>(args)...)} {};

        double value() const {
            return _thing->val;
        }

        void value(double value) const {
            _thing->val = value;
        }

        explicit operator foo_thing2_t* () {
            return base_type();
        }

        explicit operator const foo_thing2_t* () const {
            return base_type();
        }

        void print() const {
            foo_thing2_print(base_type());
        }

    private:
        foo_thing2_t* base_type() { return _thing.get(); }
        foo_thing2_t const* base_type() const { return _thing.get(); }

        unique_ptr<foo_thing2_t> _thing;
    };

} // namespace libfoo

int main(int argc, char* argv[]) {

    libfoo::thing1_t thing1;
    libfoo::thing2_t thing2_a{0.0};
    libfoo::thing2_t thing2_b{42};

    thing2_b.value(thing1.value() * thing2_a.value());
    assert(thing2_b.value() == 0.0);

    foo_thing2_print(static_cast<foo_thing2_t*>(thing2_b));
    thing2_b.print();

    return EXIT_SUCCESS;
}
