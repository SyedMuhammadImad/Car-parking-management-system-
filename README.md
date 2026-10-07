# Car parking console system

experimental console project. Compile `main.cpp` with a C++17 compiler and run it. The menu implements the operations shown in the source. Invalid menu input and end-of-input are handled without looping forever.

```sh
g++ -std=c++17 -Wall -Wextra -pedantic main.cpp -o app
./app
```

See `VERIFICATION.json` for functional and boundary checks. Data lives in memory for this example; persistence is outside its project scope. No credentials or media are included.
