.PHONY: all build build-msys2 build-android build-ios clean clean-netstandard environment format memcheck sanitize sanitize-asan sanitize-tsan test test-msvc test-netstandard

.EXPORT_ALL_VARIABLES:
ELECTIONGUARD_BINDING_DIR=$(realpath .)/bindings
ELECTIONGUARD_BINDING_LIB_DIR=$(ELECTIONGUARD_BINDING_DIR)/netstandard/ElectionGuard/ElectionGuard.Encryption
ELECTIONGUARD_BINDING_BENCH_DIR=$(ELECTIONGUARD_BINDING_DIR)/netstandard/ElectionGuard/ElectionGuard.Encryption.Bench
ELECTIONGUARD_BINDING_TEST_DIR=$(ELECTIONGUARD_BINDING_DIR)/netstandard/ElectionGuard/ElectionGuard.Encryption.Tests
ELECTIONGUARD_BUILD_DIR=$(subst \,/,$(realpath .))/build
ELECTIONGUARD_BUILD_DIR_WIN=$(subst \c\,C:\,$(subst /,\,$(ELECTIONGUARD_BUILD_DIR)))
ELECTIONGUARD_BUILD_APPS_DIR=$(ELECTIONGUARD_BUILD_DIR)/apps
ELECTIONGUARD_BUILD_BINDING_DIR=$(ELECTIONGUARD_BUILD_DIR)/bindings
ELECTIONGUARD_BUILD_LIBS_DIR=$(ELECTIONGUARD_BUILD_DIR)/libs
CPM_SOURCE_CACHE=$(subst \,/,$(realpath .))/.cache/CPM

# Detect operating system & platform
# These vars can be set from the command line.
# not all platforms can compile all targets.
# valid values:
# OPERATING_SYSTEM: Android, IOS, Linux, Darwin, Windows
# PLATFORM: arm64, x64, x86
ifeq ($(OS),Windows_NT)
	OPERATING_SYSTEM ?= Windows
	ifeq ($(PROCESSOR_ARCHITECTURE),arm)
        PLATFORM?=arm64
    endif
	ifeq ($(PROCESSOR_ARCHITECTURE),AMD64)
        PLATFORM?=x64
    endif
    ifeq ($(PROCESSOR_ARCHITECTURE),x86)
        PLATFORM?=x86
    endif
else
	OPERATING_SYSTEM ?= $(shell uname 2>/dev/null || echo Unknown)
	UNAME_P ?= $(shell uname -p)
    ifeq ($(UNAME_P),x86_64)
        PLATFORM?=x64
    endif
    ifneq ($(filter %86,$(UNAME_P)),)
        PLATFORM?=x86
    endif
    ifneq ($(filter arm%,$(UNAME_P)),)
        PLATFORM?=arm64
    endif
endif

# Default build number
BUILD:=1

# Temporarily disable vale support on x86
ifeq ($(PLATFORM),x86)
TEMP_DISABLE_VALE=ON
else
TEMP_DISABLE_VALE=ON
endif

# Debug or Release (capitalized)
TARGET?=Release

# Set the Android NDK for cross-compilation
ifeq ($(OPERATING_SYSTEM),Darwin)
ANDROID_NDK_PATH?=/Users/$(USER)/Library/Android/sdk/ndk/25.1.8937393
endif
ifeq ($(OPERATING_SYSTEM),Linux)
ANDROID_NDK_PATH?=/usr/local/lib/android/sdk/ndk/25.1.8937393
endif
ifeq ($(OPERATING_SYSTEM),Windows)
ANDROID_NDK_PATH?=C:\Android\android-sdk\ndk-bundle
endif

all: environment build

# Configure Environment

environment:
ifeq ($(OPERATING_SYSTEM),Darwin)
	@echo 🍎 MACOS INSTALL
	brew install wget
	brew install cmake
	brew install cppcheck
	brew install clang-format
	brew install include-what-you-use
	brew install llvm
	brew install ninja
	test -f /usr/local/bin/clang-tidy || sudo ln -s "$(shell brew --prefix llvm)/bin/clang-tidy" "/usr/local/bin/clang-tidy"
endif
ifeq ($(OPERATING_SYSTEM),Linux)
	@echo 🐧 LINUX INSTALL
	sudo apt install -y build-essential
	sudo apt install -y iwyu
	sudo apt install -y llvm
	sudo apt install -y clang-12
	sudo apt install -y cmake
	sudo apt install -y lcov
	sudo apt install -y cppcheck
	sudo apt install -y clang-format
	sudo apt install -y clang-tidy
	sudo apt install -y ninja-build
	sudo apt install -y valgrind
endif
ifeq ($(OPERATING_SYSTEM),Windows)
	@echo 🏁 WINDOWS INSTALL
	choco upgrade wget -y
	choco upgrade unzip -y
	choco upgrade cmake -y
	choco upgrade ninja -y
endif
	wget -O cmake/CPM.cmake https://github.com/cpm-cmake/CPM.cmake/releases/download/v0.35.5/CPM.cmake
	make fetch-sample-data
	dotnet tool restore

environment-ui: environment
ifeq ($(OPERATING_SYSTEM),Windows)
	dotnet workload install maui
	dotnet workload restore ./src/electionguard-ui/ElectionGuard.UI/ElectionGuard.UI.csproj && dotnet restore ./src/electionguard-ui/ElectionGuard.UI.sln
else
	sudo dotnet workload install maui
	sudo dotnet workload restore ./src/electionguard-ui/ElectionGuard.UI/ElectionGuard.UI.csproj && dotnet restore ./src/electionguard-ui/ElectionGuard.UI.sln
endif

# Builds

build:
	@echo 🧱 BUILD $(OPERATING_SYSTEM) $(PLATFORM) $(TARGET)
ifeq ($(OPERATING_SYSTEM),Windows)
	cmake -S . -B $(ELECTIONGUARD_BUILD_LIBS_DIR)/$(OPERATING_SYSTEM)/$(PLATFORM)/$(TARGET) -G "Visual Studio 17 2022" -A $(PLATFORM) \
		-DCMAKE_BUILD_TYPE=$(TARGET) \
		-DBUILD_SHARED_LIBS=ON \
		-DANDROID_NDK_PATH=$(ANDROID_NDK_PATH) \
		-DCPM_SOURCE_CACHE=$(CPM_SOURCE_CACHE)
	cmake --build $(ELECTIONGUARD_BUILD_LIBS_DIR)/$(OPERATING_SYSTEM)/$(PLATFORM)/$(TARGET)/ --config $(TARGET)
else
	cmake -S . -B $(ELECTIONGUARD_BUILD_LIBS_DIR)/$(OPERATING_SYSTEM)/$(PLATFORM)/$(TARGET) \
		-DCMAKE_BUILD_TYPE=$(TARGET) \
		-DBUILD_SHARED_LIBS=ON \
		-DDISABLE_VALE=$(TEMP_DISABLE_VALE) \
		-DANDROID_NDK_PATH=$(ANDROID_NDK_PATH) \
		-DCPM_SOURCE_CACHE=$(CPM_SOURCE_CACHE) \
		-DCMAKE_TOOLCHAIN_FILE=cmake/toolchains/$(PLATFORM)-$(OPERATING_SYSTEM).cmake
	cmake --build $(ELECTIONGUARD_BUILD_LIBS_DIR)/$(OPERATING_SYSTEM)/$(PLATFORM)/$(TARGET)
endif

build-x86:
	PLATFORM=x86 && make build

build-x64:
	PLATFORM=x64 && make build
	
build-msys2:
	@echo 🖥️ BUILD $(OPERATING_SYSTEM) MSYS2 $(PLATFORM)
ifeq ($(OPERATING_SYSTEM),Windows)
	cmake -S . -B $(ELECTIONGUARD_BUILD_LIBS_DIR)/$(PLATFORM)/$(TARGET) -G "MSYS Makefiles" \
		-DCMAKE_BUILD_TYPE=$(TARGET) \
		-DBUILD_SHARED_LIBS=ON \
		-DCAN_USE_VECTOR_INTRINSICS=ON \
		-DCPM_SOURCE_CACHE=$(CPM_SOURCE_CACHE) \
		-DCMAKE_TOOLCHAIN_FILE=cmake/toolchains/$(PLATFORM)-$(OPERATING_SYSTEM).cmake
	cmake --build $(ELECTIONGUARD_BUILD_LIBS_DIR)/$(PLATFORM)/$(TARGET)
else
	echo "MSYS2 builds are only supported on Windows"
endif

build-android:
	@echo 🤖 BUILD ANDROID
	PLATFORM=arm64 OPERATING_SYSTEM=Android && make build

build-ios:
	@echo 📱 BUILD IOS
ifeq ($(OPERATING_SYSTEM),Darwin)
	cmake -S . -B $(ELECTIONGUARD_BUILD_LIBS_DIR)/ios/$(TARGET) \
		-DCMAKE_BUILD_TYPE=$(TARGET) \
		-DCPM_SOURCE_CACHE=$(CPM_SOURCE_CACHE) \
		-DCMAKE_SYSTEM_NAME=iOS \
		"-DCMAKE_OSX_ARCHITECTURES=arm64;arm64e;x86_64" \
		-DCMAKE_OSX_DEPLOYMENT_TARGET=12.4 \
		-DCMAKE_INSTALL_PREFIX=$(ELECTIONGUARD_BUILD_LIBS_DIR)/ios/$(TARGET) \
		-DCMAKE_XCODE_ATTRIBUTE_ONLY_ACTIVE_ARCH=NO \
		-DCMAKE_IOS_INSTALL_COMBINED=YES
	cmake --build $(ELECTIONGUARD_BUILD_LIBS_DIR)/ios/$(TARGET) --config $(TARGET) --target install
else
	echo "iOS builds are only supported on MacOS"
endif

build-netstandard:
	@echo 🖥️ BUILD NETSTANDARD $(OPERATING_SYSTEM) $(PLATFORM) $(TARGET)
	make build
	cd ./bindings/netstandard/ElectionGuard && dotnet restore
	dotnet build --configuration $(TARGET) ./bindings/netstandard/ElectionGuard/ElectionGuard.sln /p:Platform=$(PLATFORM)

build-netstandard-x64:
	PLATFORM=x64 && make build-netstandard

# Clean

clean:
	@echo 🗑️ Cleaning Output Directory
ifeq ($(OPERATING_SYSTEM),Windows)
	pwsh -Command "rm -R -Fo $(ELECTIONGUARD_BUILD_DIR_WIN); $$null"
else
	if [ -d "$(ELECTIONGUARD_BUILD_DIR)" ]; then rm -rf $(ELECTIONGUARD_BUILD_DIR)/*; fi
	if [ ! -d "$(ELECTIONGUARD_BUILD_DIR)" ]; then mkdir $(ELECTIONGUARD_BUILD_DIR); fi

	if [ -d "$(ELECTIONGUARD_BINDING_LIB_DIR)/bin" ]; then rm -rf $(ELECTIONGUARD_BINDING_LIB_DIR)/bin/*; fi
	if [ ! -d "$(ELECTIONGUARD_BINDING_LIB_DIR)/bin" ]; then mkdir $(ELECTIONGUARD_BINDING_LIB_DIR)/bin; fi
	if [ -d "$(ELECTIONGUARD_BINDING_LIB_DIR)/obj" ]; then rm -rf $(ELECTIONGUARD_BINDING_LIB_DIR)/obj/*; fi
	if [ ! -d "$(ELECTIONGUARD_BINDING_LIB_DIR)/obj" ]; then mkdir $(ELECTIONGUARD_BINDING_LIB_DIR)/obj; fi

	if [ -d "$(ELECTIONGUARD_BINDING_BENCH_DIR)/bin" ]; then rm -rf $(ELECTIONGUARD_BINDING_BENCH_DIR)/bin/*; fi
	if [ ! -d "$(ELECTIONGUARD_BINDING_BENCH_DIR)/bin" ]; then mkdir $(ELECTIONGUARD_BINDING_BENCH_DIR)/bin; fi
	if [ -d "$(ELECTIONGUARD_BINDING_BENCH_DIR)/obj" ]; then rm -rf $(ELECTIONGUARD_BINDING_BENCH_DIR)/obj/*; fi
	if [ ! -d "$(ELECTIONGUARD_BINDING_BENCH_DIR)/obj" ]; then mkdir $(ELECTIONGUARD_BINDING_BENCH_DIR)/obj; fi

	if [ -d "$(ELECTIONGUARD_BINDING_TEST_DIR)/bin" ]; then rm -rf $(ELECTIONGUARD_BINDING_TEST_DIR)/bin/*; fi
	if [ ! -d "$(ELECTIONGUARD_BINDING_TEST_DIR)/bin" ]; then mkdir $(ELECTIONGUARD_BINDING_TEST_DIR)/bin; fi
	if [ -d "$(ELECTIONGUARD_BINDING_TEST_DIR)/obj" ]; then rm -rf $(ELECTIONGUARD_BINDING_TEST_DIR)/obj/*; fi
	if [ ! -d "$(ELECTIONGUARD_BINDING_TEST_DIR)/obj" ]; then mkdir $(ELECTIONGUARD_BINDING_TEST_DIR)/obj; fi

	if [ ! -d "$(ELECTIONGUARD_BUILD_LIBS_DIR)" ]; then mkdir $(ELECTIONGUARD_BUILD_LIBS_DIR); fi
	if [ ! -d "$(ELECTIONGUARD_BUILD_LIBS_DIR)/arm64" ]; then mkdir $(ELECTIONGUARD_BUILD_LIBS_DIR)/arm64; fi
	if [ ! -d "$(ELECTIONGUARD_BUILD_LIBS_DIR)/x86" ]; then mkdir $(ELECTIONGUARD_BUILD_LIBS_DIR)/x86; fi
	if [ ! -d "$(ELECTIONGUARD_BUILD_LIBS_DIR)/x64" ]; then mkdir $(ELECTIONGUARD_BUILD_LIBS_DIR)/x64; fi
	if [ ! -d "$(ELECTIONGUARD_BUILD_LIBS_DIR)/android" ]; then mkdir $(ELECTIONGUARD_BUILD_LIBS_DIR)/android; fi
	if [ ! -d "$(ELECTIONGUARD_BUILD_LIBS_DIR)/ios" ]; then mkdir $(ELECTIONGUARD_BUILD_LIBS_DIR)/ios; fi
endif

clean-netstandard: 
	@echo 🗑️ CLEAN NETSTANDARD
	dotnet clean ./bindings/netstandard/ElectionGuard/ElectionGuard.sln

clean-ui:
	@echo 🗑️ CLEAN UI
	dotnet clean ./src/electionguard-ui/ElectionGuard.UI.sln

# Generate

generate-interop:
	cd ./src/interop-generator/ElectionGuard.InteropGenerator && \
		dotnet run -- ./EgInteropClasses.json ../../../ && \
		cd ../../../

# Lint / Format

format: build
	cd $(ELECTIONGUARD_BUILD_LIBS_DIR)/$(PLATFORM) && $(MAKE) format

lint:
	dotnet jb inspectcode -o="lint-results.xml" -f="Xml" --build --verbosity="WARN" -s="Warning" bindings/netstandard/ElectionGuard/ElectionGuard.sln
	dotnet nvika parsereport "lint-results.xml" --treatwarningsaserrors

# Memcheck

memcheck:
	@echo 🧼 RUN STATIC ANALYSIS
ifeq ($(OPERATING_SYSTEM),Windows)
	@echo "Static analysis is only supported on Linux"
else
	cd $(ELECTIONGUARD_BUILD_LIBS_DIR)/$(PLATFORM) && $(MAKE) memcheck-ElectionGuardTests
endif

# Publish

publish-ui:
	@echo 🧱 BUILD UI
ifeq ($(OPERATING_SYSTEM),Windows)
	dotnet publish -f net7.0-windows10.0.19041.0 -c $(TARGET) /p:ApplicationVersion=$(BUILD) /p:RuntimeIdentifierOverride=win10-x64 src/electionguard-ui/ElectionGuard.UI/ElectionGuard.UI.csproj
endif
ifeq ($(OPERATING_SYSTEM),Darwin)
	dotnet build -f net7.0-maccatalyst -c $(TARGET) /p:CreatePackage=true /p:ApplicationVersion=$(BUILD) src/electionguard-ui/ElectionGuard.UI/ElectionGuard.UI.csproj
endif

# Rebuild

rebuild: clean build

rebuild-ui: clean-ui build-ui

# Sanitizers

sanitize: sanitize-asan sanitize-tsan

sanitize-asan:
	@echo 🧼 SANITIZE ADDRESS AND UNDEFINED $(PLATFORM)
ifeq ($(OPERATING_SYSTEM),Windows)
	cmake -S . -B $(ELECTIONGUARD_BUILD_LIBS_DIR)/$(PLATFORM)/Debug -G "Visual Studio 17 2022" -A $(PLATFORM) \
		-DCPM_SOURCE_CACHE=$(CPM_SOURCE_CACHE) \
		-DCMAKE_TOOLCHAIN_FILE=cmake/toolchains/sanitize.asan.cmake
	cmake --build $(ELECTIONGUARD_BUILD_LIBS_DIR)/$(PLATFORM)/Debug --config Debug
	$(ELECTIONGUARD_BUILD_LIBS_DIR)/$(PLATFORM)/Debug/test/Debug/ElectionGuardTests
	$(ELECTIONGUARD_BUILD_LIBS_DIR)/$(PLATFORM)/Debug/test/Debug/ElectionGuardCTests
else
	cmake -S . -B $(ELECTIONGUARD_BUILD_LIBS_DIR)/$(PLATFORM)/Debug \
		-DCPM_SOURCE_CACHE=$(CPM_SOURCE_CACHE) \
		-DCMAKE_TOOLCHAIN_FILE=cmake/toolchains/sanitize.asan.cmake
	cmake --build $(ELECTIONGUARD_BUILD_LIBS_DIR)/$(PLATFORM)/Debug
	$(ELECTIONGUARD_BUILD_LIBS_DIR)/$(PLATFORM)/Debug/test/ElectionGuardTests
	$(ELECTIONGUARD_BUILD_LIBS_DIR)/$(PLATFORM)/Debug/test/ElectionGuardCTests
endif

sanitize-tsan:
	@echo 🧼 SANITIZE THREADS $(PLATFORM)
ifeq ($(OPERATING_SYSTEM),Windows)
	echo "Thread sanitizer is only supported on Linux & Mac"
else
	cmake -S . -B $(ELECTIONGUARD_BUILD_LIBS_DIR)/$(PLATFORM)/Debug \
		-DCPM_SOURCE_CACHE=$(CPM_SOURCE_CACHE) \
		-DCMAKE_TOOLCHAIN_FILE=cmake/toolchains/sanitize.tsan.cmake
	cmake --build $(ELECTIONGUARD_BUILD_LIBS_DIR)/$(PLATFORM)/Debug
	$(ELECTIONGUARD_BUILD_LIBS_DIR)/$(PLATFORM)/Debug/test/ElectionGuardTests
	$(ELECTIONGUARD_BUILD_LIBS_DIR)/$(PLATFORM)/Debug/test/ElectionGuardCTests
endif

# Start/Stop Docker Services (database)

start-db:
ifeq "${EG_DB_PASSWORD}" ""
	@echo "Set the EG_DB_PASSWORD environment variable"
	exit 1
endif
	docker compose --env-file ./.env -f src/electionguard-db/docker-compose.db.yml up -d

stop-db:
	docker compose --env-file ./.env -f src/electionguard-db/docker-compose.db.yml down

# Benchmarks

bench:
	@echo 🧪 BENCHMARK $(OPERATING_SYSTEM) $(PLATFORM) $(TARGET)
ifeq ($(OPERATING_SYSTEM),Windows)
	cmake -S . -B $(ELECTIONGUARD_BUILD_LIBS_DIR)/$(PLATFORM)/$(TARGET) -G "MSYS Makefiles" \
		-DCMAKE_BUILD_TYPE=$(TARGET) \
		-DCPM_SOURCE_CACHE=$(CPM_SOURCE_CACHE) \
		-DCMAKE_TOOLCHAIN_FILE=cmake/toolchains/benchmark.cmake
else
	cmake -S . -B $(ELECTIONGUARD_BUILD_LIBS_DIR)/$(PLATFORM)/$(TARGET) \
		-DCMAKE_BUILD_TYPE=$(TARGET) \
		-DCPM_SOURCE_CACHE=$(CPM_SOURCE_CACHE) \
		-DCMAKE_TOOLCHAIN_FILE=cmake/toolchains/benchmark.cmake
endif
	cmake --build $(ELECTIONGUARD_BUILD_LIBS_DIR)/$(PLATFORM)/$(TARGET)
ifeq ($(OPERATING_SYSTEM),Windows)
	pwsh -Command "xcopy 'build\libs\$(PLATFORM)\$(TARGET)\_deps\benchmark-build\src\libbenchmark.dll' 'build\libs\$(PLATFORM)\$(TARGET)\test' /Q /Y;  $$null"
endif
	$(ELECTIONGUARD_BUILD_LIBS_DIR)/$(PLATFORM)/$(TARGET)/test/ElectionGuardBenchmark

bench-netstandard: build-netstandard
	@echo 🧪 BENCHMARK
	@echo net 6.0 x64
	./bindings/netstandard/ElectionGuard/ElectionGuard.Encryption.Bench/bin/x64/$(TARGET)/net6.0/ElectionGuard.Encryption.Bench
	@echo net 4.8 x64
	./bindings/netstandard/ElectionGuard/ElectionGuard.Encryption.Bench/bin/x64/$(TARGET)/net48/ElectionGuard.Encryption.Bench

# Test

test:
	@echo 🧪 TEST $(OPERATING_SYSTEM) $(PLATFORM) $(TARGET)
ifeq ($(OPERATING_SYSTEM),Windows)
	cmake -S . -B $(ELECTIONGUARD_BUILD_LIBS_DIR)/$(PLATFORM) -G "Visual Studio 17 2022" -A $(PLATFORM) \
		-DCMAKE_BUILD_TYPE=$(TARGET) \
		-DCPM_SOURCE_CACHE=$(CPM_SOURCE_CACHE) \
		-DCMAKE_TOOLCHAIN_FILE=cmake/toolchains/test.cmake
	cmake --build $(ELECTIONGUARD_BUILD_LIBS_DIR)/$(PLATFORM)/$(TARGET) --config $(TARGET)
	$(ELECTIONGUARD_BUILD_LIBS_DIR)/$(PLATFORM)/test/$(TARGET)/ElectionGuardTests
	$(ELECTIONGUARD_BUILD_LIBS_DIR)/$(PLATFORM)/test/$(TARGET)/ElectionGuardCTests
else
	cmake -S . -B $(ELECTIONGUARD_BUILD_LIBS_DIR)/$(PLATFORM)/$(TARGET) \
		-DCMAKE_BUILD_TYPE=$(TARGET) \
		-DCPM_SOURCE_CACHE=$(CPM_SOURCE_CACHE) \
		-DDISABLE_VALE=$(TEMP_DISABLE_VALE) \
		-DCMAKE_TOOLCHAIN_FILE=cmake/toolchains/test.cmake
	cmake --build $(ELECTIONGUARD_BUILD_LIBS_DIR)/$(PLATFORM)/$(TARGET)
	$(ELECTIONGUARD_BUILD_LIBS_DIR)/$(PLATFORM)/$(TARGET)/test/ElectionGuardTests
	$(ELECTIONGUARD_BUILD_LIBS_DIR)/$(PLATFORM)/$(TARGET)/test/ElectionGuardCTests
endif

test-msys2:
	@echo 🧪 TEST MSYS2 $(OPERATING_SYSTEM) $(PLATFORM) $(TARGET)
ifeq ($(OPERATING_SYSTEM),Windows)
	cmake -S . -B $(ELECTIONGUARD_BUILD_LIBS_DIR)/x86_64/$(TARGET) -G "MSYS Makefiles" \
		-DCMAKE_BUILD_TYPE=$(TARGET) \
		-DCPM_SOURCE_CACHE=$(CPM_SOURCE_CACHE) \
		-DCMAKE_TOOLCHAIN_FILE=cmake/toolchains/test.cmake
	cmake --build $(ELECTIONGUARD_BUILD_LIBS_DIR)/$(PLATFORM)/$(TARGET)
	$(ELECTIONGUARD_BUILD_LIBS_DIR)/$(PLATFORM)/$(TARGET)/test/ElectionGuardTests
	$(ELECTIONGUARD_BUILD_LIBS_DIR)/$(PLATFORM)/$(TARGET)/test/ElectionGuardCTests
endif

test-netstandard: build-netstandard
	@echo 🧪 TEST NETSTANDARD $(PLATFORM) $(TARGET)
	dotnet test -a $(PLATFORM) --configuration $(TARGET) ./bindings/netstandard/ElectionGuard/ElectionGuard.sln

test-netstandard-x64:
	PLATFORM=x64 && make test-netstandard

test-ui:
	@echo 🧪 TEST UI $(PLATFORM) $(TARGET)
	dotnet build -a $(PLATFORM) --configuration $(TARGET) ./src/electionguard-ui/electionGuard.UI.Test/ElectionGuard.UI.Test.csproj
ifeq ($(OPERATING_SYSTEM),Windows)
	dotnet test -a $(PLATFORM) --no-build --configuration $(TARGET) ./src/electionguard-ui/ElectionGuard.UI.sln 	
endif
ifeq ($(OPERATING_SYSTEM),Darwin)
	dotnet test -a $(PLATFORM) --no-build --configuration $(TARGET) ./src/electionguard-ui/ElectionGuard.UI.sln 	
endif

# Coverage

coverage:
	@echo ✅ CHECK COVERAGE $(OPERATING_SYSTEM) $(PLATFORM) $(TARGET)
ifeq ($(OPERATING_SYSTEM),Windows)
	cmake -S . -B $(ELECTIONGUARD_BUILD_LIBS_DIR)/$(PLATFORM)/$(TARGET) -G "MSYS Makefiles" \
		-DCMAKE_BUILD_TYPE=$(TARGET) \
		-DCODE_COVERAGE=ON \
		-DCPM_SOURCE_CACHE=$(CPM_SOURCE_CACHE) \
		-DCMAKE_TOOLCHAIN_FILE=cmake/toolchains/test.cmake
else
	cmake -S . -B $(ELECTIONGUARD_BUILD_LIBS_DIR)/$(PLATFORM)/$(TARGET) \
		-DCMAKE_BUILD_TYPE=$(TARGET) \
		-DCODE_COVERAGE=ON \
		-DUSE_STATIC_ANALYSIS=ON \
		-DDISABLE_VALE=$(TEMP_DISABLE_VALE) \
		-DCPM_SOURCE_CACHE=$(CPM_SOURCE_CACHE) \
		-DCMAKE_TOOLCHAIN_FILE=cmake/toolchains/test.cmake
endif
	cmake --build $(ELECTIONGUARD_BUILD_LIBS_DIR)/$(PLATFORM)/$(TARGET)
	$(ELECTIONGUARD_BUILD_LIBS_DIR)/$(PLATFORM)/$(TARGET)/test/ElectionGuardTests
	$(ELECTIONGUARD_BUILD_LIBS_DIR)/$(PLATFORM)/$(TARGET)/test/ElectionGuardCTests

# Sample Data

fetch-sample-data:
	@echo ⬇️ FETCH Sample Data
	wget -O sample-data-1-0.zip https://github.com/microsoft/electionguard/releases/download/v1.0/sample-data.zip
	unzip -o sample-data-1-0.zip

generate-sample-data:
	@echo Generate Sample Data
