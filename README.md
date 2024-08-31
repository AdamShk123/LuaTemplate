# Lua Template
By `Adam Shkolnik` and `Liam Murphy`

## Dependencies

- `Make`
- `CMake`
- `VCPKG`
  - Create environment variable `VCPKG_ROOT` that contains the path to the installation directory

## Building

```
cmake --preset debug
cmake --build --target template --preset linux-debug
```

## Running

```
./build/debug/src/template
```