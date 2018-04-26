#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

#include "taxratelru.hpp"

void test_eviction()
{
    TaxRateLRUCache cache(3);

    int rates[5];
    rates[0] = cache.rate_lookup("a");
    rates[1] = cache.rate_lookup("b");
    rates[2] = cache.rate_lookup("c");
    rates[3] = cache.rate_lookup("d");
    rates[4] = cache.rate_lookup("e");

    /* Each lookup should cause another call to expensive_tax_lookup. */
    assert(rates[0] != cache.rate_lookup("a"));
    assert(rates[1] != cache.rate_lookup("b"));

    int new_rates[3];
    assert(rates[2] != (new_rates[0] = cache.rate_lookup("c")));
    assert(rates[3] != (new_rates[1] = cache.rate_lookup("d")));
    assert(rates[4] != (new_rates[2] = cache.rate_lookup("e")));

    /* Currently, the LRU holds 'c', 'd', and 'e' */
    assert(new_rates[0] == cache.rate_lookup("c"));
    assert(new_rates[1] == cache.rate_lookup("d"));
    assert(new_rates[2] == cache.rate_lookup("e"));
}

int test_refresh()
{
    TaxRateLRUCache cache(3);

    /* Prime with the last three entries. */
    int rates[3];
    rates[0] = cache.rate_lookup("a");
    rates[1] = cache.rate_lookup("b");
    rates[2] = cache.rate_lookup("c");

    /* Test repeated entries don't cause eviction. */
    // c d e
    assert(rates[2] == cache.rate_lookup("c"));
    assert(rates[2] == cache.rate_lookup("c"));
    assert(rates[2] == cache.rate_lookup("c"));
    assert(rates[2] == cache.rate_lookup("c"));
    assert(rates[2] == cache.rate_lookup("c"));

    /* Validate that the other two entries are still present. */
    assert(rates[0] == cache.rate_lookup("a"));
    assert(rates[1] == cache.rate_lookup("b"));
}

int main()
{
    srand(time(NULL));

    test_eviction();
    test_refresh();

    return 0;
}

