$ErrorActionPreference = 'Stop'
$root = Split-Path -Parent $MyInvocation.MyCommand.Path
Set-Location $root
$testDir = Join-Path $root 'tests'
$binDir = Join-Path $testDir 'bin'
New-Item -ItemType Directory -Force -Path $binDir | Out-Null
$failed = 0
function Compile-Run($name, $compiler, $sources, $includes) {
    $out = Join-Path $binDir ($name + '.exe')
    Write-Host "`n=== $name ===" -ForegroundColor Cyan
    $args = @()
    if ($compiler -eq 'gcc') { $args += @('-std=c11','-Wall','-Wextra') } else { $args += @('-std=c++17','-Wall','-Wextra') }
    foreach ($inc in $includes) { $args += @('-I', (Join-Path $root $inc)) }
    $sourcePaths = @()
    foreach ($source in $sources) { $sourcePaths += (Join-Path $root $source) }
    $args += $sourcePaths
    $args += @('-o', $out)
    & $compiler @args
    if ($LASTEXITCODE -ne 0) { Write-Host "COMPILE FAILED: $name" -ForegroundColor Red; $script:failed++; return }
    Push-Location $root
    try { & $out; if ($LASTEXITCODE -ne 0) { Write-Host "TEST FAILED: $name" -ForegroundColor Red; $script:failed++ } }
    finally { Pop-Location }
}
Compile-Run 'test_input_validator' 'g++' @('tests/test_input_validator.cpp','src/InputValidator.cpp','src/UniversityCatalogue.cpp') @('include')
Compile-Run 'test_linkedlist' 'gcc' @('tests/test_linkedlist.c','dsa/linkedlist.c') @('dsa')
Compile-Run 'test_queue' 'gcc' @('tests/test_queue.c','dsa/queue.c') @('dsa')
Compile-Run 'test_stack' 'gcc' @('tests/test_stack.c','dsa/stack.c') @('dsa')
Compile-Run 'test_graph' 'gcc' @('tests/test_graph.c','dsa/graph.c') @('dsa')
Compile-Run 'test_building_room' 'g++' @('tests/test_building_room.cpp','src/Building.cpp','src/Room.cpp') @('include')
Compile-Run 'test_persistence' 'g++' @('tests/test_persistence.cpp','src/FileManager.cpp') @('include')
Compile-Run 'test_integration' 'g++' @('tests/test_integration.cpp','src/Booking.cpp','src/Resource.cpp','src/ServiceRequest.cpp','src/Emergency.cpp') @('include')
Compile-Run 'test_edge_cases' 'g++' @('tests/test_edge_cases.cpp','src/Building.cpp','src/Room.cpp','src/Resource.cpp','src/Booking.cpp','src/ServiceRequest.cpp','src/InputValidator.cpp','src/UniversityCatalogue.cpp') @('include')
Write-Host "`n========================================"
if ($failed -eq 0) { Write-Host 'All test programs passed.' -ForegroundColor Green; exit 0 }
Write-Host "$failed test program(s) failed. See output above." -ForegroundColor Red
exit 1
