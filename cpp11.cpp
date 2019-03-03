#include <atomic> //for lockless concurrent programming
#include <clocale>
#include <iostream>
#include <typeinfo>

using namespace std;

void alignasTest()
{
    struct alignedStruct {
        alignas(512) char text[20];
        int num;
    };
    alignas(256) int alignedInt = 10;
    alignedStruct as;
    int normalInt = 19;
    cout << "size of alignedStruct: " << sizeof(as) << endl;
    cout << "align of alignedStruct: " << alignof(as) << endl;
    cout << "size of alignedStruct.text: " << sizeof(as.text) << endl;
    cout << "align of alignedStruct.text: " << alignof(as.text) << endl;
    cout << "size of alignedInt: " << sizeof(alignedInt) << endl;
    cout << "align of alignedInt: " << alignof(alignedInt) << endl;
    cout << "address of alignedInt:    " << &alignedInt << endl;
    cout << "address of alignedStruct: " << &as << endl;
    cout << "address of normalInt:     " << &normalInt << endl;
}
void tprintf(const char* format)
{
    std::cout << format;
}

template <typename T, typename... Targs>
void tprintf(const char* format, T value, Targs... Fargs)
{
    for (; *format != '\0'; format++) {
        if (*format == '%') {
            std::cout << value;
            tprintf(format + 1, Fargs...);
            return;
        }
        std::cout << *format;
    }
}
void parameterPackTest()
{
    tprintf("% world% %\n", "Hello", '!', 123);
}

template<class ForwardIt, class T>
void iota(ForwardIt first, ForwardIt last, T value)
{
    while(first != last) {
        *first++ = value++;
    }
};

int main(int argc, char* argv[])
{
    parameterPackTest();
    alignasTest();
    int arr[5];
    iota(arr,arr+5,0);
    for(int i:arr)
        cout<<i<<endl;
    return 0;
}

