# advanced_programing_tsk1
https://github.com/yuvaltar/advanced_programing_tsk1.git


# Ex1 – Bloom Filter URL Blacklist

This project implements a URL filtering system using a Bloom Filter.
It was designed following SOLID principles, and Test-Driven Development (TDD)
was used

## How It Works

- After every update, the Bloom filter (its bit array) is saved to `data/bloomfilter.dat`.

## How to Build and Run

A C++17 compiler is needed.

From the project root run:
```bash
g++ -std=c++17 -o ex1 src/*.cpp
./ex1
