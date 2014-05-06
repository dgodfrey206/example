#include <iostream>

namespace detail
{
    template<int N>
    struct index { };
    
    template<int N, int... Is>
    struct gen_seq : gen_seq<N - 1, N - 1, Is...> { };
    
    template<int... Is>
    struct gen_seq<0, Is...> : index<Is...> { };
}

template<typename T, typename U>
struct concat_tuple;

template<typename... Ts, typename... Us>
struct concat_tuple<std::tuple<Ts...>, std::tuple<Us...>>
{
    using type = std::tuple<Ts..., Us...>;
};

template<typename T, typename U>
using concat_type = typename concat_tuple<T, U>::type;

template<
    typename... Ts,
    typename... Us,
    int... Is,
    int... Ls
>
auto merge_tuples(std::tuple<Ts...>& t1, std::tuple<Us...>& t2, detail::index<Is...>,
                                                                detail::index<Ls...>)
    -> concat_type<decltype(t1), decltype(t2)>
{
    return { std::get<Is>(t1)..., std::get<Ls>(t2)... };
}

template<typename... Ts, typename... Us>
auto merge_tuples(std::tuple<Ts...>& t1, std::tuple<Us...>& t2)
    -> concat_type<decltype(t1), decltype(t2)>
{
    return add_tuples(t1, t2, detail::gen_seq<sizeof...(Ts)>{},
                              detail::gen_seq<sizeof...(Us)>{});
}