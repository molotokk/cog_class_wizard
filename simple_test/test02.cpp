#ifndef INCLUDED_PROJECTNAME_SINGLE_HEADER_TEST_HPP
#define INCLUDED_PROJECTNAME_SINGLE_HEADER_TEST_HPP

/*[[[cog
  import sys
  sys.path.append('../src')
  import cogflect as cf

  fields = [
      ["name",  "value",     "type",    "tags",            "metadata"],
      ["FOO",   15,          "double",  ["fuzzy"],         cf.typedef("float", "serial_type")],
      ["BAR",   23,          "double",  ["fuzzy", "ugly"]],
      ["BUZZ",  42,          "int",     None,              cf.const("unsigned", "bazz", 3)]
  ]

  cf.Enum("single_header_test", fields)
  cf.CppClass("single_header_test", fields)

  ]]]*/

#ifndef INCLUDED_COGFLECT_COMMON_COMMON_FUNCTIONS
#define INCLUDED_COGFLECT_COMMON_COMMON_FUNCTIONS

namespace cogflect {

// This seemingly useless template is a workaround
// for an oddity of C++ syntax. You can declare an
// array like this:
//
//     double foo[3];
//
// But not like this:
//
//     double[3] foo;
//
// Which means that some of the type information is
// on the left and some is on the right when declaring
// arrays. Cogflect lets you specify an element type of
// "double[3]", which is made possible by this template.
// You can use it to declare the array like this:
//
//     type_passthrough<double[3]>::type foo;
//
// Thus keeping all the type information on the left
// side.
template<typename T>
struct type_passthrough {
    typedef T type;
};

}

#endif


#ifndef INCLUDED_COGFLECT_ENUM_COMMON_FUNCTIONS
#define INCLUDED_COGFLECT_ENUM_COMMON_FUNCTIONS

namespace cogflect {

struct store_index_action
{
    unsigned index;

    // We don't waste an instruction initializing
    // index because the type system guarantees
    // this switch will always succeed.
    inline store_index_action()
    {}

    template<class T>
    inline void action()
    {
        index = T::index;
    }

    inline void default_action()
    {}
};

struct store_string_action
{
    const char* str;

    template<class T>
    inline void action()
    {
        str = T::string();
    }

    inline void default_action()
    {}
};

struct true_t {};
struct false_t {};

}

#endif

namespace single_header_test {

class type;
class data;

template<unsigned i>
struct info_index;

template<>
struct info_index<0>
{
    static const unsigned index = 0;
    static const int value = 15;
    inline static const char* string() { return "single_header_test::FOO"; }
    typedef double type;
    typedef single_header_test::type enum_type;
    typedef single_header_test::data data_type;
    static const unsigned long long name_hash = 18350832446001871987u;
    struct tags
    {
        typedef cogflect::true_t fuzzy;
        typedef cogflect::false_t ugly;
    };
    struct metadata
    {
        typedef float serial_type;
    };
};

typedef info_index<0> FOO_INFO;

template<>
struct info_index<1>
{
    static const unsigned index = 1;
    static const int value = 23;
    inline static const char* string() { return "single_header_test::BAR"; }
    typedef double type;
    typedef single_header_test::type enum_type;
    typedef single_header_test::data data_type;
    static const unsigned long long name_hash = 11949670198037961580u;
    struct tags
    {
        typedef cogflect::true_t fuzzy;
        typedef cogflect::true_t ugly;
    };
};

typedef info_index<1> BAR_INFO;

template<>
struct info_index<2>
{
    static const unsigned index = 2;
    static const int value = 42;
    inline static const char* string() { return "single_header_test::BUZZ"; }
    typedef int type;
    typedef single_header_test::type enum_type;
    typedef single_header_test::data data_type;
    static const unsigned long long name_hash = 17642354279499121380u;
    struct tags
    {
        typedef cogflect::false_t fuzzy;
        typedef cogflect::false_t ugly;
    };
    struct metadata
    {
        static const unsigned bazz = 3;
    };
};

typedef info_index<2> BUZZ_INFO;

class type
{
private:
    int val_;

    explicit inline type(int val) : val_(val) {}

public:
    inline type(type const& other) : val_(other.val_) {}
    inline type& operator=(type other) { val_ = other.val_; }

    template<class Info>
    static inline type make_from_info()
    {
        return type(Info::value);
    }

    template<class Action>
    static inline void value_switcher(int value, Action& action)
    {
        switch(value)
        {
            case FOO_INFO::value:
                action.template action< FOO_INFO >();
                break;
            case BAR_INFO::value:
                action.template action< BAR_INFO >();
                break;
            case BUZZ_INFO::value:
                action.template action< BUZZ_INFO >();
                break;
            default:
                action.default_action();
                break;
        }
    }

    template<class Action>
    static inline void index_switcher(unsigned index, Action& action)
    {
        switch(index)
        {
            case FOO_INFO::index:
                action.template action< FOO_INFO >();
                break;
            case BAR_INFO::index:
                action.template action< BAR_INFO >();
                break;
            case BUZZ_INFO::index:
                action.template action< BUZZ_INFO >();
                break;
            default:
                action.default_action();
                break;
        }
    }

    template<class Action>
    inline void switcher(Action& action) const
    {
        value_switcher(val_, action);
    }

    inline int value() const
    {
        return val_;
    }

    inline unsigned index() const
    {
        cogflect::store_index_action sw;
        switcher(sw);
        return sw.index;
    }

    inline const char* string() const
    {
        cogflect::store_string_action sw;
        switcher(sw);
        return sw.str;
    }

    template<unsigned long long>
    struct info_with_hash
    {
        typedef cogflect::false_t type;
    };

    // This is a constant rather than a function so that it
    // can be used as a template parameter. In C++0x we can change
    // it to be a function using the 'constexpr' keyword.
    static const unsigned size = 3;

};

template<>
struct type::info_with_hash<18350832446001871987u>
{
    typedef FOO_INFO type;
};

template<>
struct type::info_with_hash<11949670198037961580u>
{
    typedef BAR_INFO type;
};

template<>
struct type::info_with_hash<17642354279499121380u>
{
    typedef BUZZ_INFO type;
};

namespace {

const type FOO(type::make_from_info<FOO_INFO>());
const type BAR(type::make_from_info<BAR_INFO>());
const type BUZZ(type::make_from_info<BUZZ_INFO>());

}

}

#ifndef INCLUDED_COGFLECT_CPPCLASS_COMMON_FUNCTIONS
#define INCLUDED_COGFLECT_CPPCLASS_COMMON_FUNCTIONS

namespace cogflect {

template<typename Visitor, typename DataType>
struct pass_member_action
{
    inline pass_member_action(Visitor& v, DataType& d)
        : visitor_(v),
          data_(d)
    {}

    template<typename MemberType>
    inline void action()
    {
        visitor_.
            template process_member<MemberType>(
                data_.template get_member<MemberType>());
    }

    inline void default_action()
    {
        visitor_.unknown_member();
    }

    Visitor& visitor_;
    DataType& data_;
};

/*
TODO: Pull this stuff out and give access to a
get_same_member<T> template that given an info template
from one class gets you the same named T in the other
class.
*/

template<class SourceMemberType, class TargetMemberType>
struct shape_assign_helper
{
    inline static void assign(typename SourceMemberType::type& v,
                              typename TargetMemberType::data_type& d)
    {
        v = d.template get_member<TargetMemberType>();
    }
};

template<class SourceMemberType>
struct shape_assign_helper<SourceMemberType, cogflect::false_t>
{
    // no-op when target doesn't have the same member
    // use ellipses since no sensible type for second argument
    inline static void assign(...)
    {
    }
};

template<class Source, class Target>
struct shape_assign
{
    inline shape_assign(Target& target)
      : target_(target)
    {}

    template<class MemberType>
    void process_member(typename MemberType::type& v) const
    {
        // Check if target type has a member with the same name by checking if
        // it has a member with the same name_hash as the current member type being
        // iterated.

        typedef typename Target::enum_type target_enum_type;
        typedef typename target_enum_type::template info_with_hash<MemberType::name_hash>::type
            potential_type;

        shape_assign_helper<MemberType, potential_type>::assign(v, target_);
    }

    Target& target_;
};

}

#endif

namespace single_header_test {

class data
{
public:
    typedef single_header_test::type enum_type;

    // TODO: iterate public/protected/private independently?
    // TODO: iterate over members with a tag? <-- public/protected/private tags
    // TODO: tag to indicate reflection is available

    template<typename T>
    typename T::type& get_member();

    template<typename T>
    typename T::type const& get_member() const;

    template<unsigned index>
    typename single_header_test::info_index<index>::type& get_indexed_member()
    {
        return get_member< info_index<index> >();
    }

    template<unsigned index>
    typename single_header_test::info_index<index>::type const& get_indexed_member() const
    {
        return get_member< info_index<index> >();
    }

    template<typename Processor>
    inline void get_runtime_member(Processor& p, type value)
    {
        cogflect::pass_member_action<Processor, data> tmp(p, *this);
        value.switcher(tmp);
    }

    template<typename Processor>
    inline void get_runtime_member(Processor const& p, type value)
    {
        cogflect::pass_member_action<const Processor, data> tmp(p, *this);
        value.switcher(tmp);
    }

    template<typename Processor>
    inline void get_runtime_member(Processor& p, type value) const
    {
        cogflect::pass_member_action<Processor, const data> tmp(p, *this);
        value.switcher(tmp);
    }

    template<typename Processor>
    inline void get_runtime_member(Processor const& p, type value) const
    {
        cogflect::pass_member_action<const Processor, const data> tmp(p, *this);
        value.switcher(tmp);
    }

    template<typename Processor>
    inline void get_runtime_indexed_member(Processor& p, unsigned index)
    {
        cogflect::pass_member_action<Processor, data> tmp(p, *this);
        type::index_switcher(index, tmp);
    }

    template<typename Processor>
    inline void get_runtime_indexed_member(Processor& p, unsigned index) const
    {
        cogflect::pass_member_action<Processor, const data> tmp(p, *this);
        type::index_switcher(index, tmp);
    }

    template<typename Processor>
    inline void get_runtime_indexed_member(Processor const& p, unsigned index)
    {
        cogflect::pass_member_action<const Processor, data> tmp(p, *this);
        type::index_switcher(index, tmp);
    }

    template<typename Processor>
    inline void get_runtime_indexed_member(Processor const& p, unsigned index) const
    {
        cogflect::pass_member_action<const Processor, const data> tmp(p, *this);
        type::index_switcher(index, tmp);
    }

    template<class VisitorT>
    inline void for_all_members(VisitorT& visitor)
    {
        visitor.
           template process_member<FOO_INFO>(foo_);
        visitor.
           template process_member<BAR_INFO>(bar_);
        visitor.
           template process_member<BUZZ_INFO>(buzz_);
    }

    template<class VisitorT>
    inline void for_all_members(VisitorT& visitor) const
    {
        visitor.
           template process_member<FOO_INFO>(foo_);
        visitor.
           template process_member<BAR_INFO>(bar_);
        visitor.
           template process_member<BUZZ_INFO>(buzz_);
    }

    template<class VisitorT>
    inline void for_all_members(VisitorT const& visitor)
    {
        visitor.
           template process_member<FOO_INFO>(foo_);
        visitor.
           template process_member<BAR_INFO>(bar_);
        visitor.
           template process_member<BUZZ_INFO>(buzz_);
    }

    template<class VisitorT>
    inline void for_all_members(VisitorT const& visitor) const
    {
        visitor.
           template process_member<FOO_INFO>(foo_);
        visitor.
           template process_member<BAR_INFO>(bar_);
        visitor.
           template process_member<BUZZ_INFO>(buzz_);
    }

    template<class TargetType>
    inline void shape_assign(TargetType const& other)
    {
        cogflect::shape_assign<data, TargetType> visitor;
        for_all_members(visitor);
    }


private:
    double foo_;
    double bar_;
    int buzz_;
}; // class data

template<>
inline FOO_INFO::type& data::get_member<FOO_INFO>()
{
    return foo_;
}

template<>
inline BAR_INFO::type& data::get_member<BAR_INFO>()
{
    return bar_;
}

template<>
inline BUZZ_INFO::type& data::get_member<BUZZ_INFO>()
{
    return buzz_;
}

template<>
inline FOO_INFO::type const& data::get_member<FOO_INFO>() const
{
    return foo_;
}

template<>
inline BAR_INFO::type const& data::get_member<BAR_INFO>() const
{
    return bar_;
}

template<>
inline BUZZ_INFO::type const& data::get_member<BUZZ_INFO>() const
{
    return buzz_;
}

} // namespace single_header_test
//[[[end]]]

#endif
