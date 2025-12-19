#ifndef MATCHING_ENGINE_HPP
#define MATCHING_ENGINE_HPP

#include <vector>
#include "order.hpp"
#include "order_book.hpp"
#include "trade.hpp"

class MatchingEngine{
public:
    explicit MatchingEngine(OrderBook& order_book);
    std::vector<Trade> process_order(Order order);

private:
    OrderBook& order_book_;

    void match_buy(Order& buy, std::vector<Trade>& trades);
    void match_sell(Order& sell, std::vector<Trade>& trades);
};



#endif // MATCHING_ENGINE_HPP