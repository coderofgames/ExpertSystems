========================================================================
    CONSOLE APPLICATION : Bayes Project Overview
========================================================================

Software design for expert systems, study of software engineering technique, design philosophy and
what can go wrong etc. Eventual intention is to create neural network based cognitive linguistic expert system.

Artificial Intelligence, a guide to intelligent systems: Michael Negnevitsky.

Note: the code is current printing the output of a set of finite state machine tests.
Currently the state machine is working, although there is slight system instablility
caused by timers and the need for "cin" for user inputs.

NOTE: There are now 2 implementations of a cash machine. The first uses a global loop
to launch std::async calls, this is a C++ 11 feature that is supposed to simplify 
threading applications - the state time out function works and interupts the "std::cin" 
command however in the case of a time-out the thread will still be running and "std::cin" 
is still waiting for input from the first thread, so the input is entered twice for extra
time. 

The second (or the first) uses a threaded timer implementation borrowed from 
Stack Overflow and only works in Windows because of the calls to GetAsyncKeyState
with a blocking read counter implemented to prevent the system from rapidly changing
states when the user presses (rather than holds down) the key. It is still best
to tap the key in this version, because the keyboard input requires a state machine 
and a timer for input too.

