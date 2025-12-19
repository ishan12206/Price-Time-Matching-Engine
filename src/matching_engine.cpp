#include "matching_engine.hpp"
#include <algorithm>

MatchingEngine::MatchingEngine(OrderBook& order_book)
    : order_book_(order_book) {}

std::vector<Trade> MatchingEngine::process_order(Order order) {
    std::vector<Trade> trades;

    if (order.side == Side::BUY){
        match_buy(order,trades);
    }
    else if (order.side == Side::SELL){
        match_sell(order,trades);
    }
    
    if(order.quantity > 0 && order.type == OrderType::LIMIT){
        order_book_.add(order);
    }

    return trades;
}



void MatchingEngine::match_buy(Order& buy, std::vector<Trade>& trades){
    while(buy.quantity > 0 && !order_book_.asks.empty()){
        auto best_ask_it = order_book_.asks.begin();
        Price best_ask_price = best_ask_it->first;

        if(buy.type == OrderType::LIMIT && buy.price < best_ask_price){
            break; // No more matching possible
        }

        auto& ask_level = best_ask_it->second;

        while(buy.quantity > 0 && !ask_level.empty()){
            Order& sell = ask_level.front();

            Quantity trade_qty = std::min(buy.quantity, sell.quantity);
            Price trade_price = sell.price; // Trade at the sell price

            trades.emplace_back(buy.id, sell.id, trade_price, trade_qty, buy.timestamp);

            buy.quantity -= trade_qty;
            sell.quantity -= trade_qty;

            if(sell.quantity == 0){
                ask_level.pop_front();
                order_book_.index.erase(sell.id);
            }
        }

        if(ask_level.empty()){
            order_book_.asks.erase(best_ask_it);
        }
    }
}

void MatchingEngine::match_sell(Order& sell, std::vector<Trade>& trades){
    while(sell.quantity > 0 && !order_book_.bids.empty()){
        auto best_bid_it = order_book_.bids.begin();
        Price best_bid_price = best_bid_it->first;

        if(sell.type == OrderType::LIMIT && sell.price > best_bid_price){
            break; // No more matching possible
        }

        auto& bid_level = best_bid_it->second;

        while(sell.quantity > 0 && !bid_level.empty()){
            Order& buy = bid_level.front();

            Quantity trade_qty = std::min(sell.quantity, buy.quantity);
            Price trade_price = buy.price; // Trade at the buy price

            trades.emplace_back(buy.id, sell.id, trade_price, trade_qty, sell.timestamp);

            sell.quantity -= trade_qty;
            buy.quantity -= trade_qty;

            if(buy.quantity == 0){
                bid_level.pop_front();
                order_book_.index.erase(buy.id);
            }
        }

        if(bid_level.empty()){
            order_book_.bids.erase(best_bid_it);
        }
    }
}