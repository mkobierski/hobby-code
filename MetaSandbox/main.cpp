#include <stdio.h>
#include <typeinfo>

#include "TypeList.hpp"
#include "StaticAssert.hpp"
#include "Conversion.hpp"

typedef TL_4(signed char, short int, int, long int) SignedIntegrals;

class Widget {};
class ScrollBar : public Widget {};
class SmoothScrollBar : public ScrollBar {};
class Button : public Widget {};
class GraphicButton : public Button {};

void convertible() {
    printf("\nConvertible...\n");
    printf("int -> double = %d\n",
        Conversion< int, double >::exists);
    printf("int <--> double = %d\n",
        Conversion< int, double >::exists2way);
    printf("Widget -> ScrollBar = %d\n"
        , Conversion< Widget, ScrollBar >::exists);
    printf("ScrollBar -> Widget = %d\n",
        Conversion< ScrollBar, Widget >::exists);
    printf("Widget * -> ScrollBar * = %d\n",
        Conversion< Widget *, ScrollBar *>::exists);
    printf("ScrollBar * -> Widget * = %d\n"
        , Conversion< ScrollBar *, Widget *>::exists);
    printf("ScrollBar inherits Widget = %d\n",
        SUPERSUBCLASS(Widget, ScrollBar));
    printf("Widget inherits ScrollBar = %d\n",
        SUPERSUBCLASS(ScrollBar, Widget));
    printf("GraphicButton inherits Widget = %d\n",
        SUPERSUBCLASS(Widget, GraphicButton));
    printf("GraphicButton inherits ScrollBar = %d\n",
        SUPERSUBCLASS(ScrollBar, GraphicButton));
}

void len() {
    printf("\nLength...\n");
    printf("%s\n", typeid(SignedIntegrals).name());
    printf("length of %d\n", Length<SignedIntegrals>::value);
    printf("length of NullType: %d\n", Length< NullType >::value);
}

void typeat() {
    typedef TL_3(char, int, double) My3Types;

    printf("TypeAt... %s\n", typeid(My3Types).name());
    printf("0, %s\n", typeid(TypeAt< My3Types, 0 >::Result).name());
    printf("1, %s\n", typeid(TypeAt< My3Types, 1 >::Result).name());
    printf("2, %s\n", typeid(TypeAt< My3Types, 2 >::Result).name());
    //printf("%s\n", typeid(TypeAt< My3Types, 3 >::Result).name());

}

void indexOf() {
    printf("\nIndexOf...\n");
    printf("%s\n", typeid(SignedIntegrals).name());
    printf("float is at index %d\n", IndexOf< SignedIntegrals, float >::value);
    printf("signed char is at index %d\n",
        IndexOf< SignedIntegrals, signed char >::value);
    printf("short is at index %d\n", IndexOf< SignedIntegrals, short >::value);
    printf("int is at index %d\n", IndexOf< SignedIntegrals, int >::value);
    printf("long is at index %d\n", IndexOf< SignedIntegrals, long >::value);
}

void append() {
    printf("\nAppend...\n");

    typedef TL_2(int, char) Integral;
    typedef TL_2(float, double) Floating;
    printf("original, left: %s\n", typeid(Integral).name());
    printf("original, right: %s\n", typeid(Floating).name());
    printf("%s\n", typeid(Append<Integral, Floating>::Result).name());

    typedef TL_1(int) IntList;
    printf("original, left: %s\n", typeid(IntList).name());
    printf("original, right: %s\n", typeid(double).name());
    printf("%s\n", typeid(Append<TL_1(IntList), double>::Result).name());
}

void erase() {
    typedef TL_5(char, unsigned char, short, int, short) Dupes;

    printf("\nErase... %s\n", typeid(Dupes).name());

    printf("char: %s\n", typeid(Erase<Dupes, char>::Result).name());
    printf("unsigned char: %s\n",
        typeid(Erase<Dupes, unsigned char>::Result).name());
    printf("short: %s\n", typeid(Erase<Dupes, short>::Result).name());
    printf("int: %s\n", typeid(Erase<Dupes, int>::Result).name());
    printf("float: %s\n", typeid(Erase<Dupes, float>::Result).name());


    printf("\nEraseAll... %s\n", typeid(Dupes).name());
    printf("char: %s\n", typeid(EraseAll<Dupes, char>::Result).name());
    printf("unsigned char: %s\n",
        typeid(EraseAll<Dupes, unsigned char>::Result).name());
    printf("short: %s\n", typeid(EraseAll<Dupes, short>::Result).name());
    printf("int: %s\n", typeid(EraseAll<Dupes, int>::Result).name());
    printf("float: %s\n", typeid(EraseAll<Dupes, float>::Result).name());

}

void noduplicates() {
    printf ("\nNoDuplicates...\n");
    typedef TL_5(char, unsigned char, short, int, long) NoDupes;
    printf("%s\n", typeid(NoDupes).name());
    printf("-> %s\n", typeid(NoDuplicates<NoDupes>::Result).name());


    typedef TL_5(char, unsigned char, short, int, short) Dupes1;
    printf("%s\n", typeid(Dupes1).name());
    printf("-> %s\n", typeid(NoDuplicates<Dupes1>::Result).name());

    typedef TL_5(int, char, short, int, short) Dupes2;
    printf("%s\n", typeid(Dupes2).name());
    printf("-> %s\n", typeid(NoDuplicates<Dupes2>::Result).name());
}

void replace() {
    printf ("\nReplace...\n");
    typedef TL_5(char, unsigned char, short, int, long) List1;
    printf("%s\n", typeid(List1).name());
    printf("char by float\n");
    printf("-> %s\n", typeid(Replace<List1, char, float>::Result).name());
    printf("int by float\n");
    printf("-> %s\n", typeid(Replace<List1, int, float>::Result).name());

    typedef TL_5(char, unsigned char, short, int, short) Dupes1;
    printf("%s\n", typeid(Dupes1).name());
    printf("unsigned char by float\n");
    printf("-> %s\n",
        typeid(Replace<Dupes1, unsigned char, float>::Result).name());
    printf("short by float\n");
    printf("-> %s\n", typeid(Replace<Dupes1, short, float>::Result).name());

    printf("\nReplaceAll...\n");
    printf("unsigned char by float\n");
    printf("-> %s\n",
        typeid(ReplaceAll<Dupes1, unsigned char, float>::Result).name());
    printf("short by float\n");
    printf("-> %s\n", typeid(ReplaceAll<Dupes1, short, float>::Result).name());
}

void insertbefore() {
    typedef TL_3(char, int, long) SomeInts;
    printf("\nInsertBefore...\n");
    printf("original %s\n", typeid(SomeInts).name());
    printf("unsigned char before char: %s\n",
        typeid(InsertBefore<SomeInts, unsigned char, char>::Result).name());
    printf("short before int: %s\n",
        typeid(InsertBefore<SomeInts, short, int>::Result).name());
    printf("float before long long: %s\n",
        typeid(InsertBefore<SomeInts, float, long long>::Result).name());
}

void orderDerived() {
    typedef TL_4(Widget, ScrollBar, Button, GraphicButton) Items1;
    typedef TL_5(Widget, ScrollBar, Button, GraphicButton, SmoothScrollBar)
        Items2;

    printf("\nMostDerived...\n");
    printf("%s\n", typeid(Items1).name());
    printf("from Widget: %s\n",
        typeid(MostDerived<Items1, Widget>::Result).name());
    printf("from ScrollBar: %s\n",
        typeid(MostDerived< Items1, ScrollBar>::Result).name());

    printf("\nDerivedToFront...\n");
    printf("original: %s\n", typeid(Items1).name());
    printf("%s\n", typeid(DerivedToFront< Items1 >::Result).name());
    printf("original: %s\n", typeid(Items2).name());
    printf("%s\n", typeid(DerivedToFront< Items2 >::Result).name());
}

int main() {
    printf("Begin...\n");
    convertible();
    len();
    typeat();
    indexOf();
    append();
    erase();
    noduplicates();
    replace();
    insertbefore();
    orderDerived();

    getchar();
    return 0;
}