# TypeList
Reference to Chapter 3. Typelists In Modern C++ Design and implement with c++17

```
template <typename... Types>
struct TypeList;

using NullType = TypeList<>;

template <typename TypeList>
struct Length;

template <typename... Types>
struct Length<TypeList<Types...>>
{
    constexpr static int Result = sizeof...(Types);
};

template <typename TypeList, typename NewType>
struct Append;

template <typename... Types, typename NewType>
struct Append<TypeList<Types...>, NewType>
{
    using Result = TypeList<Types..., NewType>;
};

template <typename... Types, typename... NewTypes>
struct Append<TypeList<Types...>, TypeList<NewTypes...>>
{
    using Result = TypeList<Types..., NewTypes...>;
};

template <>
struct Append<NullType, NullType>
{
    using Result = NullType;
};

template <typename TypeList, std::size_t Index>
struct TypeAt;

template <typename Head, typename... Tail>
struct TypeAt<TypeList<Head, Tail...>, 0>
{
    using Result = Head;
};

template <typename Head, typename... Tail, std::size_t Index>
struct TypeAt<TypeList<Head, Tail...>, Index>
{
    using Result = typename TypeAt<TypeList<Tail...>, Index - 1>::Result;
};

template <>
struct TypeAt<NullType, 0>
{
    using Result = NullType;
};

template <typename TypeList, typename TargetType>
struct IndexOf;

template <typename TargetType>
struct IndexOf<NullType, TargetType>
{
    constexpr static int Result = -1;
};

template <typename... Types, typename TargetType>
struct IndexOf<TypeList<TargetType, Types...>, TargetType>
{
    constexpr static int Result = 0;
};

template <typename Head, typename... Tails, typename TargetType>
struct IndexOf<TypeList<Head, Tails...>, TargetType>
{
private:
    constexpr static int Temp = IndexOf<TypeList<Tails...>, TargetType>::Result;

public:
    constexpr static int Result = Temp == -1 ? -1 : Temp + 1;
};

template <typename TypeList, typename TargetType>
struct Erase;

template <typename TargetType>
struct Erase<NullType, TargetType>
{
    using Result = NullType;
};

template <typename Head, typename... Tails>
struct Erase<TypeList<Head, Tails...>, Head>
{
    using Result = TypeList<Tails...>;
};

template <typename Head, typename... Tails, typename TargetType>
struct Erase<TypeList<Head, Tails...>, TargetType>
{
    using Result = typename Append<TypeList<Head>, typename Erase<TypeList<Tails...>, TargetType>::Result>::Result;
};

template <typename TypeList, typename TargetType>
struct EraseAll;

template <typename TargetType>
struct EraseAll<NullType, TargetType>
{
    using Result = NullType;
};

template <typename Head, typename... Tails, typename TargetType>
struct EraseAll<TypeList<Head, Tails...>, TargetType>
{
    using Result = typename Append<TypeList<Head>, typename EraseAll<TypeList<Tails...>, TargetType>::Result>::Result;
};

template <typename... Types, typename TargetType>
struct EraseAll<TypeList<TargetType, Types...>, TargetType>
{
    using Result = typename EraseAll<TypeList<Types...>, TargetType>::Result;
};

template <typename TypeList>
struct EraseDuplicates;

template <>
struct EraseDuplicates<NullType>
{
    using Result = NullType;
};

template <typename Head, typename... Tails>
struct EraseDuplicates<TypeList<Head, Tails...>>
{
private:
    using Temp = typename EraseDuplicates<TypeList<Tails...>>::Result;
    using Temp2 = typename Erase<Temp, Head>::Result;
public:
    using Result = typename Append<TypeList<Head>, Temp2>::Result;
};

template <typename TypeList, typename ToReplace, typename NewType>
struct Replace;

template <typename ToReplace, typename NewType>
struct Replace<NullType, ToReplace, NewType>
{
    using Result = NullType;
};

template <typename... Tails, typename ToReplace, typename NewType>
struct Replace<TypeList<ToReplace, Tails...>, ToReplace, NewType>
{
    using Result = TypeList<NewType, Tails...>;
};

template <typename Head, typename... Tails, typename ToReplace, typename NewType>
struct Replace<TypeList<Head, Tails...>, ToReplace, NewType>
{
    using Result = typename Append<TypeList<Head>, typename Replace<TypeList<Tails...>, ToReplace, NewType>::Result>::Result;
};

template <typename TypeList, typename BaseType>
struct MostDerived;

template <typename BaseType>
struct MostDerived<NullType, BaseType>
{
    using Result = BaseType;
};

template <typename Head, typename... Tails, typename BaseType>
struct MostDerived<TypeList<Head, Tails...>, BaseType>
{
private:
    using Candidate = typename MostDerived<TypeList<Tails...>, BaseType>::Result;
public:
    using Result = typename std::conditional_t<std::is_base_of_v<Head, Candidate>, Candidate, Head>;
};

template <typename TypeList>
struct DerivedToFront;

template <>
struct DerivedToFront<NullType>
{
    using Result = NullType;
};

template <typename Head, typename... Tails>
struct DerivedToFront<TypeList<Head, Tails...>>
{
private:
    using TheMostDerived = typename MostDerived<TypeList<Head, Tails...>, Head>::Result;
    using Temp = typename Replace<TypeList<Tails...>, TheMostDerived, Head>::Result;
public:
    using Result = typename Append<TypeList<TheMostDerived>, Temp>::Result;
};  

```