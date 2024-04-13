$name = Split-Path $args[0] -Leaf
$outputDirectory = "./dist"
$compiled = "./dist/$name.exe"

New-Item -ItemType Directory $outputDirectory -ErrorAction SilentlyContinue

g++ $args -o $compiled
Start-Process -NoNewWindow -Wait $compiled