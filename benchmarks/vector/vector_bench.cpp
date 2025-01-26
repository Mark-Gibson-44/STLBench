#include <cstdint>
#include <vector>

int main()
{
    std::vector<uint64_t> test;
    constexpr uint64_t loopNum = 0x7FFFFFF;
    test.reserve(loopNum);
    for(uint64_t i = 1; i < loopNum; i++)
    {
        test.push_back(i);
    }
    
    return 0;

}