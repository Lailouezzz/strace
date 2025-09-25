# strace

## notes

Si `-p PID` alors pas de spawn, comportement d'execution identique, si spawn strace se met en background process pour ne pas capturer les signals destine a lenfant

Signals :
- `INT`, `QUIT`, `TERM`: detache le child
- `KILL`: not handled
