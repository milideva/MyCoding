# Concurrency and Synchronization

This directory contains implementations and notes on locks, semaphores, and other synchronization primitives.

## 📝 Theoretical Notes
- **[Mutex, Semaphore, and RCU](./notes_mutex_semaphore_RCU.txt)**: Comprehensive notes on fundamental synchronization mechanisms.
- **[Read-Write Mutex](./notes_rw_mutex.txt)**: Principles and trade-offs of shared vs exclusive locks.
- **[Distributed Locks](./notes_distributed_lock.txt)**: Concepts of locking in a distributed environment.
- **[Barriers](./barriers.txt)**: Synchronization points for multiple threads.
- **[RAII (Resource Acquisition Is Initialization)](./RAII.txt)**: Managing locks using scope-based object lifetimes.
- **[Reentrant vs Thread-Safe](./reentrant_vs_thread_safe.txt)**: Differences and implications for concurrent code.

## 🛠️ Implementations
- **[Producer-Consumer (Mutex)](./mutex_producer_consumer.c)**: Standard synchronization pattern using mutexes.
- **[Producer-Consumer (Semaphore)](./semaphores_producer_consumer.c)**: Alternative implementation using semaphores.
- **[Basic Mutex](./mutex_lock.c)**: Simple mutex usage example.
- **[Fair Mutex](./fair_mutex.c)**: Mutex implementation focusing on fairness.
- **[Assembly-level Locking](./asm_lock_semaphore.c)**: Low-level atomic operations.
