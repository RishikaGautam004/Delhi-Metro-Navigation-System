# 🚇 Delhi Metro Navigation System

A C++ based interactive simulation of the Delhi Metro, combining **Object-Oriented Programming (OOP)**, **Graph Algorithms**, and real-world metro logic. The system allows users to calculate shortest routes, simulate real-time delays, and enjoy intelligent station name auto-completion—all through a user-friendly terminal interface.

---

## 📌 Project Overview

This project models the Delhi Metro as a **weighted undirected graph**, where stations are vertices and tracks are edges. It utilizes core **Data Structures and Algorithms (DSA)**—such as `unordered_map`, `priority_queue`, `vector`, and `queue`—to simulate realistic metro functionalities including:

- Shortest distance/time path finding (Dijkstra's Algorithm)
- Real-time delay propagation (Breadth-First Search)
- Fare calculation based on distance slabs
- Intelligent station name auto-completion using **prefix** and **fuzzy matching (Levenshtein Distance)**

---

## 🚀 Features & Functionalities

### 1️⃣ Object-Oriented Graph Implementation

- Designed using **C++ classes** encapsulating metro logic.
- Each station is a vertex; connections are edges with weights.
- Modular, reusable code adhering to OOP principles: encapsulation, abstraction, and clear responsibility separation.

### 2️⃣ Shortest Distance and Time Calculation (Dijkstra’s Algorithm)

- Computes:
  - 📏 Shortest Distance (KM)
  - ⏱️ Shortest Time (includes interchanges and fixed delays)
- Efficiently implemented using a **min-priority queue** and custom comparator.

### 3️⃣ Real-Time Delay Simulation (BFS)

- Delays at a station spread to adjacent stations using **Breadth-First Search**.
- Each propagation hop adds +3 minutes.
- Delay effect is **capped within 3 hops**, preventing unrealistic network-wide propagation.

### 4️⃣ Intelligent Auto-Completion of Station Names

**Hybrid Logic:**
- ✅ **Prefix Search**: Quick match based on input beginning.
- ✨ **Levenshtein Distance**: For typo-tolerant fuzzy suggestions (e.g., "neta subh" → "Netaji Subhash Place~PR")

### 5️⃣ Fare Calculation

- Based on actual Delhi Metro slabs:
 ≤2 KM     → ₹10
≤5 KM     → ₹20
≤12 KM    → ₹30
≤21 KM    → ₹40
≤32 KM    → ₹50
### 6️⃣ CLI Interface (Command-Line Menu)

- User-driven menu with options:
  - View stations
  - View metro map
  - Get shortest path (by time or distance)
  - Simulate delay
  - Exit application

- Supports **partial station name entry** and validation.

---

## 🧠 Algorithms & Design Decisions

| Concept           | Used For                            |
|------------------|-------------------------------------|
| `unordered_map`  | Station adjacency, delay mapping    |
| `priority_queue` | Efficient Dijkstra traversal        |
| `queue`          | BFS traversal for delay simulation  |
| `vector`, `tuple`| Data storage & delay metadata       |
| `string`, `sort` | Station list & fuzzy match logic    |

**Design Decisions:**
- OOP-centric `Graph` class abstracts all logic (add stations, find paths, delays).
- Scalable architecture: Can easily extend to multiple cities or metro lines.
- Robust error handling: Handles typos, invalid input, and ambiguous matches gracefully.

---

## 🧪 Sample Stations

| Line        | Stations                                                                 |
|-------------|--------------------------------------------------------------------------|
| Blue        | Noida Sector 62, Botanical Garden, Rajiv Chowk, Moti Nagar               |
| Yellow      | Huda City Center, AIIMS, Vishwavidyalaya, Saket                          |
| Orange      | IGI Airport, DDS Campus, Shivaji Stadium                                 |
| Pink & Red  | Rajouri Garden, Punjabi Bagh West, Netaji Subhash Place                 |

---

## 🧭 How to Use

### 🛠️ Compilation

```bash
g++ metro.cpp -o metro
./metro
1. List All Stations
2. Show Metro Map
3. Get Shortest Distance
4. Get Shortest Time
5. Simulate Delay Propagation
6. Exit
