# 1. Automatically change directory to the script's location, then into build_debug
cd "$PSScriptRoot"
if (-not (Test-Path build_debug)) { mkdir build_debug }
cd build_debug

# 2. Clean out old tracking cache files safely
Write-Host "🧹 Clearing old debug build artifacts..." -ForegroundColor Cyan
Remove-Item -Recurse -Force * -ErrorAction SilentlyContinue

# 3. Run the CMake configuration with Debug build flag
Write-Host "⚙️ Configuring CampaignManager (Debug Mode) with MinGW..." -ForegroundColor Cyan
& "C:\Qt\Tools\CMake_64\bin\cmake.exe" -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Debug -DCMAKE_CXX_COMPILER="C:/Qt/Tools/mingw1310_64/bin/g++.exe" -DCMAKE_C_COMPILER="C:/Qt/Tools/mingw1310_64/bin/gcc.exe" -DCMAKE_MAKE_PROGRAM="C:/Qt/Tools/mingw1310_64/bin/mingw32-make.exe" ..

# 4. Compile binary
Write-Host "🚀 Compiling CampaignManager debug binary..." -ForegroundColor Cyan
& "C:\Qt\Tools\CMake_64\bin\cmake.exe" --build .

# 5. Automatically launch executable on success
if ($LASTEXITCODE -eq 0) {
    Write-Host "🎉 Success! Launching CampaignManager (Debug)..." -ForegroundColor Green
    .\CampaignManager.exe
} else {
    Write-Host "❌ Compilation failed. Check errors above." -ForegroundColor Red
}