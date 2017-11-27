#include <vector>
#include <algorithm>
#include <limits>

class UnionFind
{
public:
    UnionFind(size_t size)
        : unions_(size, HeadValue)
        , sizes_(size, 1u)
        , rank_(size, 0u)
        {
        }

    void unite(unsigned a, unsigned b)
    {
        unsigned aHead = find(a);
        unsigned bHead = find(b);
        if (aHead != bHead)
        {
            if (rank_[aHead] < rank_[bHead])
                std::swap(aHead, bHead);
            unions_[bHead] = aHead;
            sizes_[aHead] += sizes_[bHead];
            if (rank_[aHead] == rank_[bHead])
                ++rank_[aHead];
            // As bhead is not a head anymore, we don't need to update
            // its sizes_ or rank_ value.
        }
        updateHead(a, aHead);
        updateHead(b, aHead);
    }

    unsigned find(unsigned i) const
    {
        unsigned current = i;
        unsigned next = unions_[i];
        while(next != HeadValue)
        {
            current = next;
            next = unions_[current];
        }
        return current;
    }

    unsigned findSize(unsigned a) const
    {
        const unsigned aHead = find(a);
        return sizes_[aHead];
    }

private:
    void updateHead(unsigned i, unsigned newHead)
    {
        unsigned current = i;
        unsigned next = unions_[i];
        while (next != HeadValue)
        {
            unions_[current] = newHead;
            current = next;
            next = unions_[current];
        }
    }

private:
    static constexpr unsigned HeadValue =
        std::numeric_limits<unsigned>::max();

private:
    std::vector<unsigned> unions_;
    std::vector<unsigned> sizes_;
    std::vector<unsigned> rank_;
};
