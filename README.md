# Template

## Dependencies

OSX users maybe need to run first
```bash
brew install pkg-config
brew install cmake
```

run the command
```bash
git submodule update --init
vcpkg/bootstrap-vcpkg.sh -disableMetrics

export VCPKG_ROOT=`pwd`/vcpkg
vcpkg/vcpkg install --feature-flags=manifests 
```

Windows
```bat
git submodule update --init
vcpkg\bootstrap-vcpkg.bat -disableMetrics

set VCPKG_ROOT=%CD%\vcpkg
vcpkg\vcpkg install --feature-flags=manifests 
```
