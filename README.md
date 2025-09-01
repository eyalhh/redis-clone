# Redis Clone (MVP)

A minimal Redis-like in-memory key-value store built from scratch.  
This project is an **MVP (minimum viable product)** implementation meant for learning how Redis works under the hood.

## ✨ Features
- In-memory key-value storage  
- Basic data structure: **Hashmap**  
- Simple command set:  
  - `SET key value`  
  - `GET key`  
  - `DEL key`  
- REPL-style interface (read-eval-print loop)  
- Written in **C** (fast and lightweight)  

## ⚡ Getting Started

### 1. Clone the repo

git clone https://github.com/your-username/redis-clone.git
cd redis-clone


### 2. Build

make


### 3. Run

./redis-clone


### 4. Try it out

> SET foo bar
OK
> GET foo
bar
> DEL foo
(1)
> GET foo
(nil)

## 🛠 Roadmap

* [ ] Support for more commands (`EXISTS`, `KEYS`, etc.)
* [ ] String expiry with TTL
* [ ] Persistent storage (AOF / RDB-like)
* [ ] Network server mode

