#ifndef TRADE_HPP
#define TRADE_HPP

#include <cstdint>
#include "order.hpp"


struct Trade
{
    OrderId buy_id;
    OrderId sell_id;
    Price price;
    Quantity quantity;
    Timestamp timestamp;

    // convenience constructor
    Trade(OrderId buy_id, OrderId sell_id, Price p, Quantity qty, Timestamp ts)
        : buy_id(buy_id), sell_id(sell_id), price(p), quantity(qty), timestamp(ts) {}
};


#endif 