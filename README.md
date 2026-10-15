# Wildlife Conservation Connectivity in Southern Africa

## Overview

A C++ console application that models connections between conservation areas in Southern Africa using a weighted, undirected graph. The program stores conservation areas as vertices and travel distances as edges.

## Features

- Represents conservation areas using a graph data structure.
- Stores connections in both an adjacency list and an adjacency matrix.
- Displays connected conservation areas and the distances between them.
- Performs Breadth-First Search (BFS) to explore reachable conservation areas.
- Uses Dijkstra's algorithm to find the shortest route between two conservation areas.
- Reconstructs and displays the shortest route and its total distance.
- Includes a menu-driven interface for selecting operations.

## Conservation Areas

The example network contains six conservation areas:

- Kruger
- Limpopo
- Hwange
- Chobe
- Etosha
- Kgalagadi

The connections are weighted using distances in kilometres.

## Technologies and Concepts

- C++
- Classes and structures
- Vectors and queues
- Graphs and weighted edges
- Adjacency lists and adjacency matrices
- Breadth-First Search (BFS)
- Dijkstra's shortest-path algorithm
- Menu-driven console applications

## How to Compile and Run

Compile using GCC:

```bash
g++ wildlife_conservation_connectivity.cpp -o wildlife_connectivity
```

Run on Linux or Ubuntu:

```bash
./wildlife_connectivity
```

On Windows, run the generated `wildlife_connectivity.exe` executable.

## Learning Objectives

This project demonstrates the implementation of graph representations, graph traversal, weighted shortest-path calculations, and basic interactive menu systems in C++.

## Project Context

Developed as an academic programming project to practise graph algorithms and data structures using a conservation connectivity scenario.
