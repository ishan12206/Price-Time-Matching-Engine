#ifndef ORDER_HPP
#define ORDER_HPP

#include <cstdint>


using OrderId = std::uint64_t;
using Price = std::int64_t;
using Quantity = std::uint32_t;
using Timestamp = std::uint64_t;

enum class Side{
    BUY,
    SELL
};

enum class OrderType{
    LIMIT,
    MARKET
};

struct Order{
    OrderId id;
    Side side;
    OrderType type;
    Price price;       // Relevant for LIMIT orders
    Quantity quantity;
    Timestamp timestamp;

    //convinience constructor
    Order(OrderId id_, Side side_, OrderType type_, Price price_, Quantity quantity_, Timestamp timestamp_)
        : id(id_), side(side_), type(type_), price(price_), quantity(quantity_), timestamp(timestamp_) {}
};


#endif // ORDER_HPP
