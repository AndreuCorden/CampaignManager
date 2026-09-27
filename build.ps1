# 1. Automatically change directory to the script's location, then into build
cd "$PSScriptRoot"
if (-not (Test-Path build)) { mkdir build }
cd build

# 2. Clean out old tracking cache files safely
Write-Host "🧹 Clearing old build artifacts..." -ForegroundColor Cyan
Remove-Item -Recurse -Force * -ErrorAction SilentlyContinue

# 3. Run the CMake configuration
Write-Host "⚙️ Configuring CampaignManager with MinGW..." -ForegroundColor Cyan
& "C:\Qt\Tools\CMake_64\bin\cmake.exe" -G "MinGW Makefiles" -DCMAKE_CXX_COMPILER="C:/Qt/Tools/mingw1310_64/bin/g++.exe" -DCMAKE_C_COMPILER="C:/Qt/Tools/mingw1310_64/bin/gcc.exe" -DCMAKE_MAKE_PROGRAM="C:/Qt/Tools/mingw1310_64/bin/mingw32-make.exe" ..

# 4. Compile binary
Write-Host "🚀 Compiling CampaignManager binary..." -ForegroundColor Cyan
& "C:\Qt\Tools\CMake_64\bin\cmake.exe" --build .

# 5. Automatically launch executable on success
if ($LASTEXITCODE -eq 0) {
    Write-Host "🎉 Success! Launching CampaignManager..." -ForegroundColor Green
    .\CampaignManager.exe
} else {
    Write-Host "❌ Compilation failed. Check errors above." -ForegroundColor Red
}