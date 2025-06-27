## Flashcard Written in C++

### Features
- CSV database file with semicolon as separator
- Spaced repetition algorithm based on confidence score
- Create and delete cards

### Compile
```bash
git clone https://github.com/seapanda0/ACE6193-Assignment.git
cd ACE6193-Assignment/
mkdir build
```
For Linux
```bash
cmake -S . -B build/
cmake --build build
```
For Windows
```bash
cmake -S . -B build/ -G "MinGW Makefiles"
cmake --build build
```
### Running the Program
```bash
./build/flashCard
```

