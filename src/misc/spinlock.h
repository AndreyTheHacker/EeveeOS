#ifndef SPINLOCK_H
#define SPINLOCK_H
void spinlock_lock(uint32_t *lock);
void spinlock_unlock(uint32_t *lock);
#endif