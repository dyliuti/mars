# sample2

This sample shows how to use a prebuilt static `xlog.lib` with copied headers.

## Layout
- `lib/xlog.lib`: prebuilt static library
- `include/mars/xlog/appender.h`
- `include/mars/comm/xlogger/xloggerbase.h`
- `src/main.cpp`: initialization and logging demo

## Build (Windows/MSVC)
```powershell
cmake -S . -B build
cmake --build build --config Release
.\build\Release\sample2_demo.exe
```

Logs are written to `./log` under the runtime directory.
