# 📦 Config Managing Handler (CMH)

**Part of the Generative Build System (GBS)**  
Automated Configuration Management for C++ Build Systems

---

## 🧩 Overview

The **Config Managing Handler (CMH)** is a critical component of the **Generative Build System (GBS)**. It manages global and project-specific configuration settings to ensure consistent, reliable, and reproducible builds across different environments and teams. CMH acts as the bridge between user-defined build configurations and the core execution engine of GBS.

---

## 🚀 Key Features

- ✅ Centralized configuration management for global and per-project settings
- 🔍 Automatic validation of compiler, toolchain, and dependency configs
- 🛠 Dynamic resolution based on platform, architecture, or build type
- 🔐 Enforces build rules and organizational policies
- 🔄 Seamless integration with CMake, Conan, and virtual environments

---

## 🏗 How It Works

The CMH processes configuration files (YAML/JSON) or interactive inputs and provides the necessary data to the **Central Unit (CU)** for initiating and executing the build. It ensures:
- Proper compiler and toolchain selection
- Dependency rules are applied correctly
- Environment configurations are isolated and reproducible

---

## 🔗 Component Interactions

| Component         | Interaction Description                                     |
|------------------|-------------------------------------------------------------|
| `Central Unit (CU)` | Requests validated configuration to start builds           |
| `Dependency Resolver (DRE)` | Receives dependency settings for package resolution    |
| `Sandbox Environment (SBE)` | Gets environment definitions and toolchain settings |
| `Forge Build Generator (FBG)` | Uses variables and templates provided by CMH          |

---


## 📁 Example Configuration File

### 🔹 YAML Format

```yaml
project:
  name: MyAwesomeApp
  version: 2.1.0

compiler:
  type: clang
  version: 14
  flags:
    - -Wall
    - -O2

dependencies:
  - name: boost
    version: "1.80.0"
    options:
      shared: true
  - name: fmt
    version: "10.1.0"

toolchain:
  cmake_minimum_required: "3.21"
  conan_profile: default
  build_type: Release

directories:
  - name: third-party
    sub-directories: []
  - name: modules
    sub-directories:
      - name: module1
        sub-directories: []
      - name: module2
        sub-directories: []
  - name: include
    sub-directories: []
  - name: build
    sub-directories: []




## 📁 Example Configuration (JSON)

```json
{
  "project": {
    "name": "MyAwesomeApp",
    "version": "2.1.0"
  },
  "compiler": {
    "type": "clang",
    "version": 14,
    "flags": ["-Wall", "-O2"]
  },
  "dependencies": [
    {
      "name": "boost",
      "version": "1.80.0",
      "options": {
        "shared": true
      }
    },
    {
      "name": "fmt",
      "version": "10.1.0"
    }
  ],
  "toolchain": {
    "cmake_minimum_required": "3.21",
    "conan_profile": "default",
    "build_type": "Release"
  },
  "directories": [
    {
      "name": "third-party",
      "sub-directories": []
    },
    {
      "name": "modules",
      "sub-directories": [
        {
          "name": "module1",
          "sub-directories": []
        },
        {
          "name": "module2",
          "sub-directories": []
        }
      ]
    },
    {
      "name": "include",
      "sub-directories": []
    },
    {
      "name": "build",
      "sub-directories": []
    }
  ]
}