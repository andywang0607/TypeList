#include <gtest/gtest.h>

#include "TypeList.hpp"

TEST(TypeListTest, Length)
{
    using TypeList1 = TL::TypeList<int, double, char>;
    using TypeList2 = TL::TypeList<>;
    using TypeList3 = TL::TypeList<int, double, char, int, double, char, int, double, char>;

    EXPECT_EQ(TL::Length<TypeList1>::Result, 3);
    EXPECT_EQ(TL::Length<TypeList2>::Result, 0);
    EXPECT_EQ(TL::Length<TypeList3>::Result, 9);
}

TEST(TypeListTest, AppendOneType)
{
    using TypeList1 = TL::TypeList<int, double, char>;
    using NewType = float;

    using Result = TL::Append<TypeList1, NewType>::Result;
    EXPECT_EQ((std::is_same_v<Result, TL::TypeList<int, double, char, float>>), true);
}

TEST(TypeListTest, AppendToEmptyList)
{
    using TypeList1 = TL::TypeList<>;
    using NewType = float;

    using Result = TL::Append<TypeList1, NewType>::Result;
    EXPECT_EQ((std::is_same_v<Result, TL::TypeList<float>>), true);
}

TEST(TypeListTest, AppendEmptyList)
{
    using TypeList1 = TL::TypeList<>;
    using NewType = TL::TypeList<>;

    using Result = TL::Append<TypeList1, NewType>::Result;
    EXPECT_EQ((std::is_same_v<Result, TL::TypeList<>>), true);
}

TEST(TypeListTest, AppendAList)
{
    using TypeList1 = TL::TypeList<int, double>;
    using NewType = TL::TypeList<float, bool>;

    using Result = TL::Append<TypeList1, NewType>::Result;
    EXPECT_EQ((std::is_same_v<Result, TL::TypeList<int, double, float, bool>>), true);
}

TEST(TypeListTest, TypeAtEmpty)
{
    using TypeList1 = TL::TypeList<>;

    EXPECT_EQ((std::is_same_v<TL::TypeAt<TypeList1, 0>::Result, TL::NullType>), true);
}

TEST(TypeListTest, TypeAtNormal)
{
    using TypeList1 = TL::TypeList<int, double, char>;

    EXPECT_EQ((std::is_same_v<TL::TypeAt<TypeList1, 0>::Result, int>), true);
    EXPECT_EQ((std::is_same_v<TL::TypeAt<TypeList1, 1>::Result, double>), true);
    EXPECT_EQ((std::is_same_v<TL::TypeAt<TypeList1, 2>::Result, char>), true);

    using TypeList2 = TL::TypeList<std::integral_constant<bool, false>, std::integral_constant<bool, true>>;

    constexpr bool value1 = TL::TypeAt<TypeList2, 0>::Result::value;
    constexpr bool value2 = TL::TypeAt<TypeList2, 1>::Result::value;

    EXPECT_EQ(value1, false);
    EXPECT_EQ(value2, true);
}

TEST(TypeListTest, IndexOfNormal)
{
    using TypeList1 = TL::TypeList<int, double, char>;

    constexpr int indexInt = TL::IndexOf<TypeList1, int>::Result;
    constexpr int indexDouble = TL::IndexOf<TypeList1, double>::Result;
    constexpr int indexChar = TL::IndexOf<TypeList1, char>::Result;

    EXPECT_EQ(indexInt, 0);
    EXPECT_EQ(indexDouble, 1);
    EXPECT_EQ(indexChar, 2);
}

TEST(TypeListTest, IndexOfNotFound)
{
    using TypeList1 = TL::TypeList<int, double, char>;

    constexpr int index = TL::IndexOf<TypeList1, float>::Result;

    EXPECT_EQ(index, -1);
}

TEST(TypeListTest, IndexOfDuplicated)
{
    using TypeList1 = TL::TypeList<int, int, int>;

    constexpr int index = TL::IndexOf<TypeList1, int>::Result;

    // Find the first one
    EXPECT_EQ(index, 0);
}

TEST(TypeListTest, Erase)
{
    using TypeList1 = TL::TypeList<int, double, char>;

    using EraseInt = TL::Erase<TypeList1, int>::Result;
    using EraseDouble = TL::Erase<TypeList1, double>::Result;
    using EraseChar = TL::Erase<TypeList1, char>::Result;

    EXPECT_EQ((std::is_same_v<EraseInt, TL::TypeList<double, char>>), true);
    EXPECT_EQ((std::is_same_v<EraseDouble, TL::TypeList<int, char>>), true);
    EXPECT_EQ((std::is_same_v<EraseChar, TL::TypeList<int, double>>), true);
}

TEST(TypeListTest, EraseDuplicated)
{
    using TypeList1 = TL::TypeList<int, double, int>;

    using Erase = TL::Erase<TypeList1, int>::Result;

    // Erase the first one
    EXPECT_EQ((std::is_same_v<Erase, TL::TypeList<double, int>>), true);
}

TEST(TypeListTest, EraseEmpty)
{
    using TypeList1 = TL::TypeList<>;

    using Erase = TL::Erase<TypeList1, int>::Result;

    // Erase the first one
    EXPECT_EQ((std::is_same_v<Erase, TL::NullType>), true);
}

TEST(TypeListTest, EraseAll)
{
    using TypeList1 = TL::TypeList<int, double, char, int, double, char>;

    using EraseAllInt = TL::EraseAll<TypeList1, int>::Result;
    using ErasAlleDouble = TL::EraseAll<TypeList1, double>::Result;
    using EraseAllChar = TL::EraseAll<TypeList1, char>::Result;

    EXPECT_EQ((std::is_same_v<EraseAllInt, TL::TypeList<double, char, double, char>>), true);
    EXPECT_EQ((std::is_same_v<ErasAlleDouble, TL::TypeList<int, char, int, char>>), true);
    EXPECT_EQ((std::is_same_v<EraseAllChar, TL::TypeList<int, double, int, double>>), true);
}

TEST(TypeListTest, EraseAllEmpty)
{
    using TypeList1 = TL::TypeList<>;

    using EraseAll = TL::EraseAll<TypeList1, int>::Result;

    EXPECT_EQ((std::is_same_v<EraseAll, TL::NullType>), true);
}

TEST(TypeListTest, EraseDuplicates)
{
    using TypeList1 = TL::TypeList<int, double, char, int, double, char>;

    using EraseDuplicates = TL::EraseDuplicates<TypeList1>::Result;

    EXPECT_EQ((std::is_same_v<EraseDuplicates, TL::TypeList<int, double, char>>), true);
}

TEST(TypeListTest, EraseDuplicatesEmpty)
{
    using TypeList1 = TL::TypeList<>;

    using EraseDuplicates = TL::EraseDuplicates<TypeList1>::Result;

    EXPECT_EQ((std::is_same_v<EraseDuplicates, TL::NullType>), true);
}

TEST(TypeListTest, Replace)
{
    using TypeList1 = TL::TypeList<int, double, char, int, double, char>;

    using ReplaceIntWithFloat = TL::Replace<TypeList1, int, float>::Result;
    using ReplaceDoubleWithFloat = TL::Replace<TypeList1, double, float>::Result;
    using ReplaceCharWithFloat = TL::Replace<TypeList1, char, float>::Result;

    // Replace the first one
    EXPECT_EQ((std::is_same_v<ReplaceIntWithFloat, TL::TypeList<float, double, char, int, double, char>>), true);
    EXPECT_EQ((std::is_same_v<ReplaceDoubleWithFloat, TL::TypeList<int, float, char, int, double, char>>), true);
    EXPECT_EQ((std::is_same_v<ReplaceCharWithFloat, TL::TypeList<int, double, float, int, double, char>>), true);
}

class Widget
{
};

class ScrollBar : public Widget
{
};

class Button : public Widget
{
};

class GraphicButton : public Button
{
};

TEST(TypeListTest, MostDerived)
{
    using TypeList1 = TL::TypeList<Widget, ScrollBar, Button, GraphicButton>;
    using MostDerivedWidget = TL::MostDerived<TypeList1, Widget>::Result;

    EXPECT_EQ((std::is_same_v<MostDerivedWidget, ScrollBar>), true);


    using TypeList2 = TL::TypeList<Widget, Button, GraphicButton>;
    using MostDerivedWidget2 = TL::MostDerived<TypeList2, Widget>::Result;

    EXPECT_EQ((std::is_same_v<MostDerivedWidget2, GraphicButton>), true);
}

TEST(TypeListTest, DerivedToFront)
{
    using TypeList1 = TL::TypeList<Widget, ScrollBar, Button, GraphicButton>;
    using DerivedToFront1 = TL::DerivedToFront<TypeList1>::Result;

    EXPECT_EQ((std::is_same_v<DerivedToFront1, TL::TypeList<ScrollBar, Widget, Button, GraphicButton>>), true);

    using TypeList2 = TL::TypeList<Widget, Button, GraphicButton>;
    using DerivedToFront2 = TL::DerivedToFront<TypeList2>::Result;

    EXPECT_EQ((std::is_same_v<DerivedToFront2, TL::TypeList<GraphicButton, Button, Widget>>), true);
}
