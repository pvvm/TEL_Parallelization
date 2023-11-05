PARALLELIZATION IDEAS:

Assigning threads to EPs:
EP > threads: multiple EPs for each thread
EP = threads: each EP for each thread
EP < threads: each EP may have more than one thread (probably those that process several event)

Locks when data is changed (context):
have a lock for each variable in the context
only allow read-read

One thread for each tx_queue

To lock a ctx variable within the EP:
lock->ctx.variable

Assign a thread for an EP/loop:
thread(id, count) {}
Think about how to assign the threads



SCHEDULE:

Parser done by 11/06
Parallelization analysis done by 11/13
Code generation by 11/20
Create test set by 11/27
Possibly add some other functionalities and write the report (?) 12/06