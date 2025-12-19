# **Price Time Matching Engine** 
### A deterministic, exchange-style price-time priority matching engine for limit and market orders.
---

## Motivation
The motivation behind this project was to understand how orders are executed on exchanges, under real-time, deterministic matching rules. This project builds on my earlier work on **Limit Order Book Simulator**, which focused on modeling order-flow and study how market-making affected market stability and liquidity. While the simulator emphasized stochastic market dynamics and aggregate behaviour of markets under different conditions, this project focuses on execution itself - formalizing how different order types(limit, market, and cancel) are matched using price time priority. Together, the projects complement each other by covering both behavorial and mechanical aspects of electronic markets.

---

## Goals and Objectives
* Implement deterministic matching of limit and market orders in real time under exchange-style execution.
* Enforce price-priority between price-levels and time-priority within each level using FIFO queues.
* Support partial-fills and multi-level sweeps to correctly handle aggressive orders across available liquidity.
* Allow O(1) average time order-cancellation via direct order indexing for better time efficiency.

---
## Core Execution Rules
* Price-priority refers to priority assigned to orders based on price, with the best price orders being executed-first.
* If prices are the same, priority is assigned on the basis of FIFO rules, known as time-priority.
* Price-priority preceeds time-priority.
* Execution prices are determined by resting limit orders in the order-book.
* Each incoming market order consumes liquidity at the specified level, whereas a limit order adds to it.


---

## Data-Structures
- The order book is implemented using **Ordered-Maps**, *decreasing* in price for buy-orders, *increasing* in price for sell-orders. This is to ensure that the best-price is always accessible and traversal respects priorities by construction. The books for bids and asks are seperated due to different matching logics, which allows cleaner execution and prevents accidental mixing.<br>
- A **deque** is used for assigning time-priority in each price-level, as it provides a **First-In-First-Out** (FIFO) execution. A vector is not used as a pop-operation takes O(n) and a vector also risks breaking the FIFO order.<br>
- An **Unordered Map** is used for indexing orders in the order-book. This allows efficient cancellation in average **O(1)** time which would otherwise take O(N) time if a vector were used.<br>
- Price points are taken as integers, to prevent *floating-point ambiguity* and it is also a standard practice across exchanges to use integer-price ticks.

---

## Testing and Edge-Cases
The matching engine was validated against a set of execution-focused tests designed to preserve core market invariants. These include FIFO enforcement at identical price levels, correct handling of partial fills, and market orders sweeping liquidity across multiple price levels.<br>
Additional tests such as market orders on empty books and cancellation of partially filled orders were carried out to ensure correct order lifecycle management. Execution prices were verified to always correspond to resting orders, consistent with continuous double auction market semantics.

---


