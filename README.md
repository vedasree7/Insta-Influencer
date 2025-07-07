# IITM InstaInfluencer Fest (Lab 9 | OOAIA)

A **C++ mini-project** that simulates the **IIT Madras InstaInfluencer Fest** using advanced graph algorithms and clean OOP design.

---

## 🎯 Project Summary

- Models **events as a directed graph**:
  - Nodes = influencer events
  - Edges = event dependencies (an event must occur before another)
  - Each event has a **hype score** indicating its campus popularity

- Supports:
  - **Cycle detection** for conflict resolution
  - **SCC identification** for interdependent event clusters
  - **Topological sorting** for valid scheduling
  - **Max hype path computation** over a condensed DAG

---

## Storyline

It’s March 2025, and after Shaastra, IIT Madras is hosting its first **InstaInfluencer Fest**, a high-energy gathering of:

- Viral dance-offs 🕺
- Meme wars 😂
- Podcast sessions 🎙️
- Livestreaming challenges 🎮

Each influencer wants their event to happen in a specific order, leading to complex dependency chains.

Your system manages these dependencies, detects conflicts, and optimizes hype.

---

## Features Implemented

✅ **Detect Circular Dependencies**  
✅ **Identify Strongly Connected Components (SCCs)**  
✅ **Generate Valid Event Schedule (Topological Sort)**  
✅ **Compute Maximum Total Hype Score (Longest Path in Condensed DAG)**

---

## Input Format

      N = number of events
      M = number of dependencies
      Array of size N for hype scores
      M edges of dependencies
      Q queries (each asking one of 4 types)

      Query Type	Description
        
        1	Check if any cycles (circular dependencies) exist.
        2	Output number of Strongly Connected Components (SCCs) and the size of the largest SCC.
        3	Provide a valid topological order of events (lexicographically sorted if possible). Output "NO" if cycles exist.
        4	Compute the maximum hype score from a valid path in the condensed DAG of SCC

### Query Types

- `1` : Check if any cycles exist
- `2` : Output number of SCCs and size of the largest SCC
- `3` : Provide a valid topological order if possible, else "NO"
- `4` : Compute the maximum hype score over a valid path

---

## 🧩 Algorithms Used

- **Cycle Detection** (DFS)
- **SCC Detection** (Kosaraju’s Algorithm)
- **Topological Sort** (Kahn’s Algorithm with Min-Heap for lex min order)
- **Longest Path in DAG** (Dynamic Programming over topological order)
- **DAG Condensation over SCCs**

---

## OOP Architecture

- **Abstract base class: `GraphAlgorithm`**
  - Pure virtual `query()` method for polymorphic query handling
- **Derived classes:**
  - `isCycle` – detects cycles
  - `indepComponent` – computes SCCs and max component size
  - `validOrder` – computes topological order
  - `maxHype` – computes max hype path in DAG

---

## 🚀 How It Works

✅ Run the program and input the graph and queries as specified.  
✅ The system will:
- Check event dependency conflicts
- Identify event clusters
- Suggest a valid schedule if possible
- Compute the maximum possible hype path for maximum festival buzz

---

## Reference
[IITM InstaInfluencer Fest Problem PDF.pdf](https://github.com/user-attachments/files/21108922/lab9.1.pdf)
