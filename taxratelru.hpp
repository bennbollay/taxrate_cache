#include <list>
#include <map>

class TaxRateLRUCache
{
protected:
    struct LRUEntry;

    typedef std::map<std::string, LRUEntry *> CacheMap;
    typedef CacheMap::value_type CacheEntry;
    typedef std::list<LRUEntry *> LRUList;

    struct LRUEntry {
        LRUEntry(int r) : rate(r) { }
        int rate;
        LRUList::iterator lru_entry;
        CacheMap::iterator map_entry;
    };

    CacheMap cache;
    LRUList lru;

    const int max_entries;

public:

    /* Create a cache that accepts 'max' number of entries. */
    TaxRateLRUCache(int max) : max_entries(max) {}
    virtual ~TaxRateLRUCache()
    {
        for (auto entry : lru) {
            delete entry;
        }
    }

    /* Find the rate for a given address */
    int rate_lookup(std::string address)
    {
        /* Is the address in the active cache? */
        auto itr = cache.find(address);
        if (itr != cache.end()) {
            /* Success; refresh position in LRU and return. */
            update_entry(itr->second);
            return itr->second->rate;
        }

        /* Has capacity been reached? */
        if (cache.size() == max_entries) {
            /* Remove the oldest entry in the LRU. */
            LRUEntry *old = lru.front();
            lru.pop_front();
            cache.erase(old->map_entry);
            delete old;
        }

        /* Add a new entry for this cached address. */
        return add_entry(address, expensive_tax_lookup(address));
    }

protected:
    /* Incredibly expensive yet blocking tax lookup by address. */
    int expensive_tax_lookup(std::string address)
    {
        return rand();
    }

    /* Convenience function to add a new entry to the cache. */
    int add_entry(std::string address, int rate)
    {
        LRUEntry *entry = new LRUEntry(rate);

        entry->map_entry = cache.insert(CacheEntry(address, entry)).first;
        lru.push_back(entry);
        entry->lru_entry = --lru.end();

        return rate;
    }

    /* Refresh an entry's position in the LRU eviction list. */
    void update_entry(LRUEntry *entry)
    {
        lru.erase(entry->lru_entry);
        lru.push_back(entry);
        entry->lru_entry = --lru.end();
    }
};
