#include "pcx/scoped_lock.h"

const pcx::lock pcx::scoped_lock_value<pcx::lock>::locked = pcx::lock(true);
const pcx::lock pcx::scoped_lock_value<pcx::lock>::unlocked = pcx::lock(false);
