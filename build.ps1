$ErrorActionPreference = 'Stop'

# Run this script from the SmartCampus_Phase1 project root.
$root = Split-Path -Parent $MyInvocation.MyCommand.Path
Set-Location $root

Write-Host 'Compiling C DSA files...'
Get-ChildItem '.\dsa\*.c' | ForEach-Object {
    Write-Host "  $($_.Name)"
    gcc -std=c11 -Wall -Wextra -I dsa -c $_.FullName -o (Join-Path $_.DirectoryName ($_.BaseName + '.o'))
    if ($LASTEXITCODE -ne 0) { throw "C compilation failed: $($_.Name)" }
}

Write-Host 'Compiling C++ source files...'
Get-ChildItem '.\src\*.cpp' | ForEach-Object {
    Write-Host "  $($_.Name)"
    g++ -std=c++17 -Wall -Wextra -I include -I dsa -c $_.FullName -o (Join-Path $_.DirectoryName ($_.BaseName + '.o'))
    if ($LASTEXITCODE -ne 0) { throw "C++ compilation failed: $($_.Name)" }
}

Write-Host 'Compiling main.cpp into project-root main.o...'
g++ -std=c++17 -Wall -Wextra -I include -I dsa -c main.cpp -o main.o
if ($LASTEXITCODE -ne 0) { throw 'main.cpp compilation failed' }

Write-Host 'Linking SmartCampus.exe...'
$objects = @('main.o') + @(Get-ChildItem '.\src\*.o' | ForEach-Object { $_.FullName }) + @(Get-ChildItem '.\dsa\*.o' | ForEach-Object { $_.FullName })
g++ $objects -o SmartCampus.exe
if ($LASTEXITCODE -ne 0) { throw 'Linking failed' }

Write-Host 'Build successful: SmartCampus.exe' -ForegroundColor Green
