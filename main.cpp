#include <iostream>
#include "matching_engine.hpp"

void test_market_buy_sweep() {
    std::cout << "\n[TEST] Market BUY sweeps multiple ask levels\n";

    OrderBook book;
    MatchingEngine engine(book);

    // Resting asks
    engine.process_order(Order{1, Side::SELL, OrderType::LIMIT, 100, 5, 1});
    engine.process_order(Order{2, Side::SELL, OrderType::LIMIT, 101, 10, 2});

    // Market BUY
    auto trades = engine.process_order(Order{
        3, Side::BUY, OrderType::MARKET, 0, 12, 3
    });

    for (const auto& t : trades) {
        std::cout << "Trade: buy=" << t.buy_id
                  << ", sell=" << t.sell_id
                  << ", qty=" << t.quantity
                  << ", price=" << t.price << "\n";
    }
}

void test_market_sell_sweep() {
    std::cout << "\n[TEST] Market SELL sweeps multiple bid levels\n";

    OrderBook book;
    MatchingEngine engine(book);

    // Resting bids
    engine.process_order(Order{1, Side::BUY, OrderType::LIMIT, 101, 6, 1});
    engine.process_order(Order{2, Side::BUY, OrderType::LIMIT, 100, 6, 2});

    // Market SELL
    auto trades = engine.process_order(Order{
        3, Side::SELL, OrderType::MARKET, 0, 10, 3
    });

    for (const auto& t : trades) {
        std::cout << "Trade: buy=" << t.buy_id
                  << ", sell=" << t.sell_id
                  << ", qty=" << t.quantity
                  << ", price=" << t.price << "\n";
    }
}

void test_market_order_empty_book() {
    std::cout << "\n[TEST] Market order with empty book\n";

    OrderBook book;
    MatchingEngine engine(book);

    auto trades = engine.process_order(Order{
        1, Side::BUY, OrderType::MARKET, 0, 10, 1
    });

    if (trades.empty()) {
        std::cout << "No trades executed (correct)\n";
    } else {
        std::cout << "ERROR: trades should be empty\n";
    }
}

void test_cancel_after_partial_fill() {
    std::cout << "\n[TEST] Cancel after partial fill\n";

    OrderBook book;
    MatchingEngine engine(book);

    // Step 1: Add resting SELL order (qty 10)
    engine.process_order(Order{
        1, Side::SELL, OrderType::LIMIT,
        100, 10, 1
    });

    // Step 2: Partial fill with BUY (qty 4)
    auto trades1 = engine.process_order(Order{
        2, Side::BUY, OrderType::LIMIT,
        100, 4, 2
    });

    for (const auto& t : trades1) {
        std::cout << "Trade: buy=" << t.buy_id
                  << ", sell=" << t.sell_id
                  << ", qty=" << t.quantity
                  << ", price=" << t.price << "\n";
    }

    // Step 3: Cancel remaining SELL order
    bool cancelled = book.cancel(1);
    std::cout << "Cancel result: "
              << (cancelled ? "success" : "failure") << "\n";

    // Step 4: Attempt another BUY (should not trade)
    auto trades2 = engine.process_order(Order{
        3, Side::BUY, OrderType::LIMIT,
        100, 10, 3
    });

    if (trades2.empty()) {
        std::cout << "No trades after cancel (correct)\n";
    } else {
        std::cout << "ERROR: trades occurred after cancel\n";
    }
}


int main(){
    test_market_buy_sweep();
    test_market_sell_sweep();
    test_market_order_empty_book();
    test_cancel_after_partial_fill();
    return 0;
}