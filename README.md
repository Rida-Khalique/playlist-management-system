# 🎵 Polymorphic Playlist Management System (C++)

A comprehensive, console-based audio playlist engine built in C++ that showcases advanced object-oriented programming methodologies, memory lifecycle tracking, and dynamic typing structures.

## 🚀 Key Features

- **Diamond Architecture Solution:** Utilizes `virtual public` inheritance to avoid data duplication across multi-tier derived classes.
- **Dynamic Type Casting:** Employs runtime Type Information via `dynamic_cast` to decouple interface pointers and map discrete relationships safely.
- **Robust Exception Handling:** Gracefully captures boundary tracking states (e.g., storage limits, empty playlists, missing queries) via structured numeric exit statuses.
- **Proactive Memory Lifecycle Management:** Implements automated deep-memory trace cleanups within custom destructors to prevent memory leaks and dangling pointer defects.

---

## 🏗️ Class Inheritance Architecture

The data layout is managed through an abstract base structure branching down into specific hybrid entities:

```text
       [ Song ]  (Abstract Base Class)
       /      \
      /        \  (Virtual Inheritance)
 [ LiveSong ]  [ RemixSong ]
      \        /
       \      /
     [ SpecialSong ] (Hybrid Leaf Node)
```

- **`Song`**: The foundational component containing abstract behaviors (`play()`, `display()`) and generic metadata like name, duration, and baseline performer fields.
- **`LiveSong`**: A specialized layer handling recording locations and stadium/venue identities.
- **`RemixSong`**: A specialized layer identifying the modifying track producer/remixer.
- **`SpecialSong`**: A unified hybrid structural type integrating both performance venues and studio remix profiles simultaneously.

---

## 💻 Operations & Menu Mapping

The runtime console environment provides explicit command hooks to control memory collections:

| Option | Command | Functional Responsibility |
|---|---|---|
| **1-3** | `Add Song Types` | Instantiates items dynamically on the heap and adds them to structural track pools. |
| **4** | `Play All` | Evaluates polymorphic overrides dynamically by invoking individual item `.play()` definitions. |
| **5** | `Show Playlist` | Sequentially loops target categories to echo nested state properties. |
| **6-8** | `Delete Subsets` | Wipes target segments cleanly from runtime memory pools and sets arrays back to stable `NULL` states. |
| **9** | `Artist Filter` | Cross-checks distinct tracking arrays to filter songs matching exact string configurations. |
| **10** | `Cartesian Mapping` | Maps a structural Cartesian relation $R \subseteq A \times V$ linking targeted performers to active venue nodes. |

---

## 🛠️ Requirements & Compilation

The source layout is designed using generic constructs, making it compatible with both legacy and current development environments without modern flag dependencies.

### Command Line Build
```bash
# Compile using any generic standard compiler (GCC/Clang)
g++ -o playlist_manager main.cpp

# Execute application
./playlist_manager
```
