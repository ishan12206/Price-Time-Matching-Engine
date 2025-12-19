#include "order_book.hpp"
#include <algorithm>

void OrderBook::add(const Order& order){
    if(order.side == Side::BUY){
        bids[order.price].push_back(order);
        index[order.id] = {Side::BUY, order.price};
    }
    else if(order.side == Side::SELL){
        asks[order.price].push_back(order);
        index[order.id] = {Side::SELL, order.price};
    }
}

bool OrderBook::cancel(OrderId order_id){
    auto it = index.find(order_id);
    if(it == index.end()){
        return false; //order not found in index
    }
    Side side = it->second.first;
    Price price = it->second.second;

    if(side == Side::BUY){
        auto level_it = bids.find(price);
        if(level_it != bids.end()){
            auto& level = level_it->second;
            auto order_it = std::find_if(level.begin(), level.end(),
                                         [order_id](const Order& o){ return o.id == order_id; });
            if(order_it != level.end()){
                level.erase(order_it);
                if(level.empty()){
                    bids.erase(level_it);
                }
                index.erase(it);
                return true;
            }
        }
    }
    else if(side == Side::SELL){
        auto level_it = asks.find(price);
        if(level_it != asks.end()){
            auto& level = level_it->second;
            auto order_it = std::find_if(level.begin(), level.end(),
                                         [order_id](const Order& o){ return o.id == order_id; });
            if(order_it != level.end()){
                level.erase(order_it);
                if(level.empty()){
                    asks.erase(level_it);
                }
                index.erase(it);
                return true;
            }
        }
    }

    return false; //order not found

}