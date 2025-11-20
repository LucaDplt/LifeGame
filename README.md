# GameOfLife

## Conway’s Game of Life Overview

**The Game of Life** is a cellular automaton devised by mathematician **John Conway** in 1970.  
It is a **zero-player game**, meaning the evolution of the system is determined entirely by its initial state, with no further input from players.  
The game simulates the **dynamics of life and death** on a two-dimensional grid of cells.

---

## Representation

- The game board is a **grid of square cells**.
- Each cell can be in **one of two states**:
  - **Alive** (represented as `O`)
  - **Dead** (represented as `.` )
- Time progresses in discrete steps called **generations**.

---

## Rules – Simulating Life and Death

Each generation, the state of a cell is updated based on the number of **alive neighbors** (up to 8 surrounding cells):

1. **Birth**: A dead cell with exactly 3 alive neighbors becomes alive.  
   *Symbolizes the birth of new life.*
2. **Survival**: An alive cell with 2 or 3 alive neighbors remains alive.  
   *Represents sustained life.*
3. **Death by underpopulation**: An alive cell with fewer than 2 alive neighbors dies.  
   *Represents death due to isolation.*
4. **Death by overpopulation**: An alive cell with more than 3 alive neighbors dies.  
   *Represents death due to overcrowding.*

---

## Why it Represents Life

- **Birth** reflects how life emerges from interactions of surrounding elements.  
- **Death** models natural constraints like isolation or overpopulation.  
- **Patterns** can self-organize, oscillate, or propagate, mimicking aspects of biological systems.  
- Despite simple rules, the system can produce **complex, lifelike behavior**, demonstrating how complexity arises from simple local interactions.

---

## Key Takeaways

- A simple mathematical model can **mimic fundamental aspects of life**.  
- Shows **emergence**: complex structures appear from simple rules.  
- Illustrates concepts like **birth, survival, and death** in a purely abstract way.

---

## How to Run

- `./GameOfLife`
- Indicate the Size of the grid : Int -> [Int x Int]
- indicate the number of frames per second : Int