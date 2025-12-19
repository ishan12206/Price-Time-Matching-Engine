#ifndef ORDER_BOOK_HPP
#define ORDER_BOOK_HPP

#include <map>
#include <deque>
#include <unordered_map>
#include <functional>

#include "order.hpp"

class OrderBook{
    public:
        using PriceLevel = std::deque<Order>;
        //BUY-SIDE, sorted in descending order of price
        using BidBook = std::map<Price, PriceLevel, std::greater<Price>>;

        //SELL-SIDE, sorted in ascending order of price
        using AskBook = std::map<Price, PriceLevel,  std::less<Price>>;

        BidBook bids;
        AskBook asks;

        //for average O(1) cancellation
        std::unordered_map<OrderId, std::pair<Side,Price>> index;

        void add(const Order& order); 

        bool cancel(OrderId order_id);

};

#endif // ORDER_BOOK_HPP