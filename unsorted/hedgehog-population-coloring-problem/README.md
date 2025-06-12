# Hedgehog Population Coloring Problem

## Run

```
cd Problem
dotnet run -- --red 8 --green 1 --blue 9 --target red
dotnet run -- -r 8 -g 1 -b 9 -t red
```

```
cd Tests
dotnet test
```

## Measure performance

```
cd Problem
dotnet build -c Release
```

Powershell
```
$psi = New-Object Diagnostics.ProcessStartInfo
$psi.FileName = 'dotnet'
$dllPath = Resolve-Path "./bin/Release/net9.0/Problem.dll"
$psi.Arguments = "$dllPath -r 3 -g 18 -b 9000 -t red"
$psi.UseShellExecute = $false
$psi.RedirectStandardOutput = $true
$psi.CreateNoWindow = $true
$p = New-Object Diagnostics.Process
$p.StartInfo = $psi

$sw = [Diagnostics.Stopwatch]::StartNew()
$p.Start() | Out-Null
$output = $p.StandardOutput.ReadToEnd()
$p.WaitForExit()
$memUsageBytes = $p.WorkingSet64
$sw.Stop()

$memUsageB = $memUsageBytes / 1
$memUsageKB = $memUsageBytes / 1KB
$memUsageMB = $memUsageBytes / 1MB

Write-Output ("Program output: " + $output.Trim())
Write-Output ("Exit code: " + $p.ExitCode.ToString())
Write-Output ("Memory usage (B): " + $memUsageB.ToString())
Write-Output ("Memory usage (KB): " + $memUsageKB.ToString())
Write-Output ("Memory usage (MB): " + $memUsageMB.ToString())
Write-Output ("Elapsed time (ms): " + $sw.Elapsed.TotalMilliseconds.ToString())
```
